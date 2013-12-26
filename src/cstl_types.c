/*
 *  The implementation of cstl types.
 *  Copyright (C)  2008 - 2014  Wangbo
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
 */

/** include section **/
#include <cstl/cstl_def.h>
#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>

#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/cslist.h>
#include <cstl/cdeque.h>
#include <cstl/cstack.h>
#include <cstl/cqueue.h>
#include <cstl/cset.h>
#include <cstl/cmap.h>
#include <cstl/chash_set.h>
#include <cstl/chash_map.h>
#include <cstl/cstring.h>
#include <cstl/cutility.h>

#include "cstl_types_aux.h"
#include "cstl_types_builtin.h"
#include "cstl_types_parse.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void _type_debug(void)
{
    size_t       i = 0;
    size_t       j = 0;
    _typenode_t* pt_node = NULL;
    _type_t*     pt_type = NULL;
    _type_t*     apt_type[1024] = {NULL};

    for (j = 0; j < 1024; ++j) {
        apt_type[j] = NULL;
    }

    for (i = 0; i < _TYPE_REGISTER_BUCKET_COUNT; ++i) {
        printf("[%lu]", (unsigned long)i);
        pt_node = _gt_typeregister._apt_bucket[i];
        while (pt_node != NULL) {
            printf("->[%s,%p]", pt_node->_s_typename, (void*)pt_node->_pt_type);
            for (j = 0; j < 1024; ++j) {
                if (apt_type[j] == pt_node->_pt_type) {
                    break;
                } else if (apt_type[j] == NULL) {
                    apt_type[j] = pt_node->_pt_type;
                    break;
                }
            }
            pt_node = pt_node->_pt_next;
        }
        printf("\n");
    }

    for (j = 0; j < 1024; ++j) {
        pt_type = apt_type[j];
        if (pt_type != NULL) {
            printf("%p\n----------\n%lu,%s,%p,%p,%p,%p\n========================\n",
                pt_type, (unsigned long)pt_type->_t_typesize, pt_type->_s_typename,
                pt_type->_t_typecopy, pt_type->_t_typeless,
                pt_type->_t_typeinit, pt_type->_t_typedestroy);
        }
    }
}

bool_t _type_register(
    size_t t_typesize, const char* s_typename,
    ufun_t t_typeinit, bfun_t t_typecopy,
    bfun_t t_typeless, ufun_t t_typedestroy)
{
    char         s_formalname[_TYPE_NAME_SIZE + 1];
    _typestyle_t t_style = _TYPE_INVALID;

    if (!_gt_typeregister._t_isinit) {
        _type_init();
    }

    /* the main aim is getting formal name */
    t_style = _type_get_style(s_typename, s_formalname);
    if (t_style == _TYPE_INVALID || _type_is_registered(s_formalname) != NULL || strlen(s_typename) > _TYPE_NAME_SIZE) {
         return false;
    } else {
        size_t       t_pos = 0;
        _typenode_t* pt_node = (_typenode_t*)_alloc_allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
        _type_t*     pt_type = (_type_t*)_alloc_allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);

        memset(pt_node->_s_typename, '\0', _TYPE_NAME_SIZE + 1);
        memset(pt_type->_s_typename, '\0', _TYPE_NAME_SIZE + 1);

        /* register the new type */
        strncpy(pt_node->_s_typename, s_formalname, _TYPE_NAME_SIZE);
        strncpy(pt_type->_s_typename, s_formalname, _TYPE_NAME_SIZE);
        pt_type->_t_typesize = t_typesize;
        pt_type->_t_style = t_style; /* save type style for type duplication between different type style */
        pt_type->_t_typeinit = t_typeinit != NULL ? t_typeinit : _type_init_default;
        pt_type->_t_typecopy = t_typecopy != NULL ? t_typecopy : _type_copy_default;
        pt_type->_t_typeless = t_typeless != NULL ? t_typeless : _type_less_default;
        pt_type->_t_typedestroy = t_typedestroy != NULL ? t_typedestroy : _type_destroy_default;

        pt_node->_pt_type = pt_type;
        t_pos = _type_hash(s_formalname);
        pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
        _gt_typeregister._apt_bucket[t_pos] = pt_node;

        return true;
    }
}

bool_t _type_duplicate(
    size_t t_typesize1, const char* s_typename1,
    size_t t_typesize2, const char* s_typename2)
{
    _type_t* pt_registered1 = NULL;
    _type_t* pt_registered2 = false;
    char     s_formalname1[_TYPE_NAME_SIZE + 1];
    char     s_formalname2[_TYPE_NAME_SIZE + 1];

    assert(s_typename1 != NULL);
    assert(s_typename2 != NULL);

    if (!_gt_typeregister._t_isinit) {
        _type_init();
    }

    if (strlen(s_typename1) > _TYPE_NAME_SIZE ||
        strlen(s_typename2) > _TYPE_NAME_SIZE ||
        t_typesize1 != t_typesize2) {
        return false;
    }

    _type_get_style(s_typename1, s_formalname1);
    _type_get_style(s_typename2, s_formalname2);
    /* test the type1 and type2 is registered or not */
    pt_registered1 = _type_is_registered(s_formalname1);
    pt_registered2 = _type_is_registered(s_formalname2);

    if (pt_registered1 == NULL && pt_registered2 == NULL) {
        /* type1 and type2 all unregistered */
        return false;
    } else if (pt_registered1 != NULL && pt_registered2 != NULL) {
        /* type1 and type2 all registered */
        return pt_registered1 == pt_registered2 ? true : false;
    } else {
        /* only one type is registered */
        size_t       t_pos = 0;
        char*        s_duplicatename = NULL;
        _typenode_t* pt_duplicate = NULL;
        _type_t*     pt_type = NULL;

        if (pt_registered1 != NULL && pt_registered2 == NULL) {
            /* type1 is registered and type2 is unregistered */
            pt_type = pt_registered1;
            s_duplicatename = s_formalname2;
        } else {
            /* type1 is unregistered and type2 is registered */
            pt_type = pt_registered2;
            s_duplicatename = s_formalname1;
        }

        /* malloc typenode for unregistered type */
        pt_duplicate = (_typenode_t*)_alloc_allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
        memset(pt_duplicate->_s_typename, '\0', _TYPE_NAME_SIZE + 1);
        strncpy(pt_duplicate->_s_typename, s_duplicatename, _TYPE_NAME_SIZE);

        pt_duplicate->_pt_type = pt_type;

        t_pos = _type_hash(s_duplicatename);
        pt_duplicate->_pt_next = _gt_typeregister._apt_bucket[t_pos];
        _gt_typeregister._apt_bucket[t_pos] = pt_duplicate;

        return true;
    }
}

void _type_get_type_pair(_typeinfo_t* pt_typeinfofirst, _typeinfo_t* pt_typeinfosecond, const char* s_typename)
{
    /* this function get type information for pair_t and relation container */
    char  s_firsttypename[_TYPE_NAME_SIZE + 1];
    char  s_secondtypename[_TYPE_NAME_SIZE + 1];
    char* pc_commapos = NULL;
    char* pc_newstart = NULL;

    assert(pt_typeinfofirst != NULL);
    assert(pt_typeinfosecond != NULL);
    assert(s_typename != NULL);

    pt_typeinfofirst->_t_style = _TYPE_INVALID;
    pt_typeinfofirst->_pt_type = NULL;
    pt_typeinfosecond->_t_style = _TYPE_INVALID;
    pt_typeinfosecond->_pt_type = NULL;

    /* the type name is separated in two section by comma */
    pc_newstart = (char*)s_typename;
    while ((pc_commapos = strchr(pc_newstart, _CSTL_COMMA)) != NULL) {
        s_firsttypename[0] = s_firsttypename[_TYPE_NAME_SIZE] = '\0';
        s_secondtypename[0] = s_secondtypename[_TYPE_NAME_SIZE] = '\0';
        strncpy(s_firsttypename, s_typename, pc_commapos - s_typename);
        s_firsttypename[pc_commapos - s_typename] = '\0';
        strncpy(s_secondtypename, pc_commapos + 1, _TYPE_NAME_SIZE);

        _type_get_type(pt_typeinfofirst, s_firsttypename);
        _type_get_type(pt_typeinfosecond, s_secondtypename);
        if (pt_typeinfofirst->_t_style != _TYPE_INVALID && pt_typeinfofirst->_pt_type != NULL &&
            pt_typeinfosecond->_t_style != _TYPE_INVALID && pt_typeinfosecond->_pt_type != NULL) {
            return;
        }

        pt_typeinfofirst->_t_style = _TYPE_INVALID;
        pt_typeinfofirst->_pt_type = NULL;
        pt_typeinfosecond->_t_style = _TYPE_INVALID;
        pt_typeinfosecond->_pt_type = NULL;

        pc_newstart = pc_commapos + 1;
    }
}

static inline bool_t _type_cstl_builtin_special(const char* s_typename)
{
    /*
     * Judging the special cstl-builtin type.
     */
    size_t t_length = 0;
    bool_t b_result = false;

    assert(s_typename != NULL);

    t_length = strlen(s_typename);
    switch (t_length) {
        case 7:
            if (strncmp(s_typename, _RANGE_TYPE, _TYPE_NAME_SIZE) == 0) {
                b_result = true;
            }
            break;
        case 8:
            if (strncmp(s_typename, _STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
                b_result = true;
            }
            break;
        case 10:
            if (strncmp(s_typename, _ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0) {
                b_result = true;
            }
            break;
        case 14:
            if (strncmp(s_typename, _SET_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0 ||
                strncmp(s_typename, _MAP_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0) {
                b_result = true;
            }
            break;
        case 15:
            if (strncmp(s_typename, _LIST_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0) {
                b_result = true;
            }
            break;
        case 16:
            if (strncmp(s_typename, _INPUT_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0 ||
                strncmp(s_typename, _SLIST_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0 ||
                strncmp(s_typename, _DEQUE_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0) {
                b_result = true;
            }
            break;
        case 17:
            if (strncmp(s_typename, _STRING_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0 ||
                strncmp(s_typename, _OUTPUT_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0 ||
                strncmp(s_typename, _VECTOR_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0) {
                b_result = true;
            }
            break;
        case 18:
            if (strncmp(s_typename, _FORWARD_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0) {
                b_result = true;
            }
            break;
        case 19:
            if (strncmp(s_typename, _MULTISET_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0 ||
                strncmp(s_typename, _MULTIMAP_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0 ||
                strncmp(s_typename, _HASH_SET_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0 ||
                strncmp(s_typename, _HASH_MAP_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0) {
                b_result = true;
            }
            break;
        case 23:
            if (strncmp(s_typename, _BASIC_STRING_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0) {
                b_result = true;
            }
            break;
        case 24:
            if (strncmp(s_typename, _HASH_MULTISET_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0 ||
                strncmp(s_typename, _HASH_MULTIMAP_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0 ||
                strncmp(s_typename, _BIDIRECTIONAL_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0 ||
                strncmp(s_typename, _RANDOM_ACCESS_ITERATOR_TYPE, _TYPE_NAME_SIZE) == 0) {
                b_result = true;
            }
            break;
        default:
            b_result = false;
            break;
    }

    return b_result;
}

void _type_get_type(_typeinfo_t* pt_typeinfo, const char* s_typename)
{
    char s_registeredname[_TYPE_NAME_SIZE + 1];

    assert(pt_typeinfo != NULL);
    assert(s_typename != NULL);

    if (!_gt_typeregister._t_isinit) {
        _type_init();
    }

    s_registeredname[0] = s_registeredname[_TYPE_NAME_SIZE] = '\0';
    pt_typeinfo->_t_style = _type_get_style(s_typename, pt_typeinfo->_s_typename);
    if (pt_typeinfo->_t_style == _TYPE_INVALID) {
        pt_typeinfo->_pt_type = NULL;
        return;
    } else if (pt_typeinfo->_t_style == _TYPE_C_BUILTIN ||
               pt_typeinfo->_t_style == _TYPE_USER_DEFINE) {
        strncpy(s_registeredname, pt_typeinfo->_s_typename, _TYPE_NAME_SIZE);
    } else {
        /* the string_t , range_t and iterator types are special codition */
        if (_type_cstl_builtin_special(pt_typeinfo->_s_typename)) {
            strncpy(s_registeredname, pt_typeinfo->_s_typename, _TYPE_NAME_SIZE);
        } else {
            size_t t_length = 0;
            char* pc_leftbracket = strchr(pt_typeinfo->_s_typename, _CSTL_LEFT_BRACKET);
            assert(pc_leftbracket != NULL);
            t_length = pc_leftbracket - pt_typeinfo->_s_typename;
            assert(t_length <= _TYPE_NAME_SIZE);
            strncpy(s_registeredname, pt_typeinfo->_s_typename, t_length);
            s_registeredname[t_length] = '\0';
        }
    }

    if ((pt_typeinfo->_pt_type = _type_is_registered(s_registeredname)) == NULL) {
        pt_typeinfo->_t_style = _TYPE_INVALID;
    } else {
        /*
         * types that duplicate between different type style has same type style that saved by type struct.
         */
        pt_typeinfo->_t_style = pt_typeinfo->_pt_type->_t_style;
    }
}

bool_t _type_is_same(const char* s_typename1, const char* s_typename2)
{
    /* s_typename1 and s_typename2 is formal name */
    char  s_elemname1[_TYPE_NAME_SIZE + 1];
    char  s_prefix1[_TYPE_NAME_SIZE + 1];
    char  s_elemname2[_TYPE_NAME_SIZE + 1];
    char  s_prefix2[_TYPE_NAME_SIZE + 1];
    char* pc_index1 = NULL;
    char* pc_leftbracket1 = NULL;
    char* pc_rightbracket1 = NULL;
    char* pc_comma1 = NULL;
    char* pc_index2 = NULL;
    char* pc_leftbracket2 = NULL;
    char* pc_rightbracket2 = NULL;
    char* pc_comma2 = NULL;

    assert(s_typename1 != NULL);
    assert(s_typename2 != NULL);

    s_elemname1[0] = s_elemname1[_TYPE_NAME_SIZE] = '\0';
    s_elemname2[0] = s_elemname2[_TYPE_NAME_SIZE] = '\0';
    strncpy(s_elemname1, s_typename1, _TYPE_NAME_SIZE);
    strncpy(s_elemname2, s_typename2, _TYPE_NAME_SIZE);

    do {
        pc_leftbracket1 = strchr(s_elemname1, _CSTL_LEFT_BRACKET);
        pc_comma1 = strchr(s_elemname1, _CSTL_COMMA);
        pc_rightbracket1 = strchr(s_elemname1, _CSTL_RIGHT_BRACKET);
        pc_leftbracket2 = strchr(s_elemname2, _CSTL_LEFT_BRACKET);
        pc_comma2 = strchr(s_elemname2, _CSTL_COMMA);
        pc_rightbracket2 = strchr(s_elemname2, _CSTL_RIGHT_BRACKET);

        /* int vs vector<int> or list_t<double> vs string_t */
        if ((pc_leftbracket1 != NULL && pc_leftbracket2 == NULL) || 
            (pc_leftbracket1 == NULL && pc_leftbracket2 != NULL)) {
            return false;
        }

        pc_index1 = 
            pc_leftbracket1 != NULL ?
                pc_comma1 != NULL ?
                    pc_rightbracket1 != NULL ?
                        pc_leftbracket1 < pc_comma1 ?
                            pc_leftbracket1 < pc_rightbracket1 ? pc_leftbracket1 : pc_rightbracket1
                            :
                            pc_comma1 < pc_rightbracket1 ? pc_comma1 : pc_rightbracket1
                        :
                        pc_leftbracket1 < pc_comma1 ? pc_leftbracket1 : pc_comma1
                    :
                    pc_rightbracket1 != NULL ?
                        pc_leftbracket1 < pc_rightbracket1 ? pc_leftbracket1 : pc_rightbracket1
                        :
                        pc_leftbracket1
                :
                pc_comma1 != NULL ?
                    pc_rightbracket1 != NULL ?
                        pc_comma1 < pc_rightbracket1 ? pc_comma1 : pc_rightbracket1
                        :
                        pc_comma1
                    :
                    pc_rightbracket1;

        pc_index2 = 
            pc_leftbracket2 != NULL ?
                pc_comma2 != NULL ?
                    pc_rightbracket2 != NULL ?
                        pc_leftbracket2 < pc_comma2 ?
                            pc_leftbracket2 < pc_rightbracket2 ? pc_leftbracket2 : pc_rightbracket2
                            :
                            pc_comma2 < pc_rightbracket2 ? pc_comma2 : pc_rightbracket2
                        :
                        pc_leftbracket2 < pc_comma2 ? pc_leftbracket2 : pc_comma2
                    :
                    pc_rightbracket2 != NULL ?
                        pc_leftbracket2 < pc_rightbracket2 ? pc_leftbracket2 : pc_rightbracket2
                        :
                        pc_leftbracket2
                :
                pc_comma2 != NULL ?
                    pc_rightbracket2 != NULL ?
                        pc_comma2 < pc_rightbracket2 ? pc_comma2 : pc_rightbracket2
                        :
                        pc_comma2
                    :
                    pc_rightbracket2;

        if (pc_index1 != NULL && pc_index2 != NULL) {
            s_prefix1[0] = s_prefix1[_TYPE_NAME_SIZE] = '\0';
            s_prefix2[0] = s_prefix2[_TYPE_NAME_SIZE] = '\0';
            strncpy(s_prefix1, s_elemname1, pc_index1 - s_elemname1);
            s_prefix1[pc_index1 - s_elemname1] = '\0';
            strncpy(s_prefix2, s_elemname2, pc_index2 - s_elemname2);
            s_prefix2[pc_index2 - s_elemname2] = '\0';

            if (_type_is_registered(s_prefix1) != _type_is_registered(s_prefix2)) {
                return false;
            }

            s_prefix1[0] = s_prefix1[_TYPE_NAME_SIZE] = '\0';
            s_prefix2[0] = s_prefix2[_TYPE_NAME_SIZE] = '\0';
            strncpy(s_prefix1, pc_index1 + 1, _TYPE_NAME_SIZE);
            strncpy(s_prefix2, pc_index2 + 1, _TYPE_NAME_SIZE);
            s_elemname1[0] = s_elemname1[_TYPE_NAME_SIZE] = '\0';
            s_elemname2[0] = s_elemname2[_TYPE_NAME_SIZE] = '\0';
            strncpy(s_elemname1, s_prefix1, _TYPE_NAME_SIZE);
            strncpy(s_elemname2, s_prefix2, _TYPE_NAME_SIZE);
        } else {
            assert(pc_index1 == NULL && pc_index2 == NULL);
            if (_type_is_registered(s_elemname1) != _type_is_registered(s_elemname2)) {
                return false;
            }
        }
    } while ((pc_leftbracket1 != NULL || pc_comma1 != NULL || pc_rightbracket1 != NULL) &&
            (pc_leftbracket2 != NULL || pc_comma2 != NULL || pc_rightbracket2 != NULL));
    assert(pc_leftbracket1 == NULL && pc_comma1 == NULL && pc_rightbracket1 == NULL &&
           pc_leftbracket2 == NULL && pc_comma2 == NULL && pc_rightbracket2 == NULL);

    return true;
}

bool_t _type_is_same_ex(const _typeinfo_t* pt_first, const _typeinfo_t* pt_second)
{
    assert(pt_first != NULL);
    assert(pt_second != NULL);

    if (pt_first == pt_second) {
        return true;
    }

    return pt_first->_pt_type == pt_second->_pt_type &&
           pt_first->_t_style == pt_second->_t_style &&
           _type_is_same(pt_first->_s_typename, pt_second->_s_typename);
}

void _type_get_elem_typename(const char* s_typename, char* s_elemtypename)
{
    char* pc_left = NULL;   /* left bracket position */
    char* pc_right = NULL;  /* right bracket position */

    assert(s_typename != NULL);
    assert(s_elemtypename != NULL);

    memset(s_elemtypename, '\0', _TYPE_NAME_SIZE + 1);

    /* the string_t and iterator types are special condition */
    if (_type_cstl_builtin_special(s_typename)) {
        strncpy(s_elemtypename, s_typename, _TYPE_NAME_SIZE);
    } else {
        /* e.g. "vector_t<map_t<int,long>>" */
        pc_left = strchr(s_typename, _CSTL_LEFT_BRACKET);
        pc_right = strrchr(s_typename, _CSTL_RIGHT_BRACKET);
        assert(pc_left != NULL && pc_right != NULL && pc_left < pc_right &&
               pc_right == s_typename + strlen(s_typename) - 1);

        strncpy(s_elemtypename, pc_left + 1, pc_right - pc_left - 1);
    }
}

void _type_get_varg_value(_typeinfo_t* pt_typeinfo, va_list val_elemlist, void* pv_output)
{
    assert(pt_typeinfo != NULL && pt_typeinfo->_pt_type != NULL);
    assert(pt_typeinfo->_t_style != _TYPE_INVALID);
    assert(pv_output != NULL);

    /*
     * Note: the va_arg align at byte doundary for char, short and float type,
     * so those type, which are char, short and float, can't be used in va_arg function.
     * Note: instead "long double" type with "double" in var_arg function.
     */
    if (pt_typeinfo->_t_style == _TYPE_C_BUILTIN) {
        if (strncmp(pt_typeinfo->_pt_type->_s_typename, _CHAR_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* char and shigned char */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(char));
            *(char*)pv_output = (char)va_arg(val_elemlist, int);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _UNSIGNED_CHAR_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* unsigned char */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(unsigned char));
            *(unsigned char*)pv_output = (unsigned char)va_arg(val_elemlist, int);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _SHORT_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* short, short int, signed short, signed short int */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(short));
            *(short*)pv_output = (short)va_arg(val_elemlist, int);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _UNSIGNED_SHORT_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* unsigned short, unsigned short int */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(unsigned short));
            *(unsigned short*)pv_output = (unsigned short)va_arg(val_elemlist, int);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _INT_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* int, signed, signed int */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(int));
            *(int*)pv_output = va_arg(val_elemlist, int);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _UNSIGNED_INT_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* unsigned int, unsigned */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(unsigned int));
            *(unsigned int*)pv_output = va_arg(val_elemlist, unsigned int);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _LONG_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* long, long int, signed long, signed long int */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(long));
            *(long*)pv_output = va_arg(val_elemlist, long);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _UNSIGNED_LONG_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* unsigned long, unsigned long int */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(unsigned long));
            *(unsigned long*)pv_output = va_arg(val_elemlist, unsigned long);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _FLOAT_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* float */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(float));
            *(float*)pv_output = (float)va_arg(val_elemlist, double);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _DOUBLE_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* double */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(double));
            *(double*)pv_output = va_arg(val_elemlist, double);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _LONG_DOUBLE_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* long double */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(long double));
            *(long double*)pv_output = va_arg(val_elemlist, double);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _CSTL_BOOL_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* bool_t */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(bool_t));
            *(bool_t*)pv_output = va_arg(val_elemlist, bool_t);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _POINTER_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* void* */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(void*));
            *(void**)pv_output = va_arg(val_elemlist, void*);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* char* */
            char* s_str = va_arg(val_elemlist, char*);
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(string_t));

            if (s_str != NULL) {
                string_assign_cstr((string_t*)pv_output, s_str);
            } else {
                bool_t b_result = pt_typeinfo->_pt_type->_t_typesize;
                (*pt_typeinfo->_pt_type->_t_typedestroy)(pv_output, &b_result);
                assert(b_result);
                memset(pv_output, 0x00, pt_typeinfo->_pt_type->_t_typesize);
            }
#ifndef _MSC_VER
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _BOOL_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* _Bool */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(_Bool));
            *(_Bool*)pv_output = va_arg(val_elemlist, int);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _LONG_LONG_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* long long */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(long long));
            *(long long*)pv_output = va_arg(val_elemlist, long long);
        } else if (strncmp(pt_typeinfo->_pt_type->_s_typename, _UNSIGNED_LONG_LONG_TYPE, _TYPE_NAME_SIZE) == 0) {
            /* unsigned long long */
            assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(unsigned long long));
            *(unsigned long long*)pv_output = va_arg(val_elemlist, unsigned long long);
#endif
        } else {
            /* invalid c builtin style */
            assert(false);
        }
    } else if (pt_typeinfo->_t_style == _TYPE_USER_DEFINE || pt_typeinfo->_t_style == _TYPE_CSTL_BUILTIN) {
        /*
         * other type include cstl built in type and user define type passed type pointer.
         * the pv_output must be initialized.
         */
        bool_t b_result = pt_typeinfo->_pt_type->_t_typesize;
        void*  pv_elem = va_arg(val_elemlist, void*);

        /* set terminator to pv_output when input pointer is NULL. */
        if (pv_elem != NULL) {
            (*pt_typeinfo->_pt_type->_t_typecopy)(pv_output, pv_elem, &b_result);
        } else {
            (*pt_typeinfo->_pt_type->_t_typedestroy)(pv_output, &b_result);
            memset(pv_output, 0x00, pt_typeinfo->_pt_type->_t_typesize);
        }
        assert(b_result);
    } else {
        /* invalid type style */
        assert(false);
    }
}

/* default copy, less, and destroy function */
void _type_init_default(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    memset((void*)cpv_input, 0x00, *(size_t*)pv_output);
    *(bool_t*)pv_output = true;
}
void _type_copy_default(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    memcpy((void*)cpv_first, cpv_second, *(size_t*)pv_output);
    *(bool_t*)pv_output = true;
}
void _type_less_default(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, *(size_t*)pv_output) < 0 ? true : false;
}
void _type_destroy_default(const void* cpv_input, void* pv_output)
{
    void* pv_avoidwarning = NULL;
    assert(cpv_input != NULL && pv_output != NULL);
    pv_avoidwarning = (void*)cpv_input;
    *(bool_t*)pv_output = true;
}

/** local function implementation section **/

/** eof **/

