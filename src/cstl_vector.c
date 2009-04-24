/*
 *  The implement of vector module.
 *  Copyright (C)  2008 2009  Wangbo
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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

/** include section **/
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "cstl_types.h"
#include "cstl_alloc.h"
#include "cstl_iterator.h"

#include "cstl_vector_iterator.h"
#include "cstl_vector_private.h"
#include "cstl_vector.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Private function for assert.
 */
static bool_t _iterator_belong_to_vector(
    const vector_t* cpt_vector, const vector_iterator_t* cpt_iterator);
static bool_t _same_vector_iterator_type(
    const vector_t* cpt_vector, const vector_iterator_t* cpt_iterator);
static bool_t _iterator_for_one_and_the_same_vector(
    const vector_iterator_t* cpt_iteratorfirst, const vector_iterator_t* cpt_iteratorsecond);
static bool_t _same_vector_type(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond);
#endif /* NDEBUG */

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* vector iterator function */
vector_iterator_t create_vector_iterator(void)
{
    vector_iterator_t t_newiterator;

    _GET_VECTOR_COREPOS(&t_newiterator) = NULL;
    _GET_CONTAINER(&t_newiterator) = NULL;
    _GET_VECTOR_CONTAINER_TYPE(&t_newiterator) = _VECTOR_CONTAINER;
    _GET_VECTOR_ITERATOR_TYPE(&t_newiterator) = _RANDOM_ACCESS_ITERATOR;

    return t_newiterator;
}

bool_t _vector_iterator_equal(
    const struct _tagvector* cpt_vector, const vector_iterator_t* cpt_iterator,
    vector_iterator_t t_iterator)
{
#ifdef NDEBUG
    vector_t* pt_avoidwarning = NULL;
    pt_avoidwarning = (vector_t*)cpt_vector;
#endif

    assert(
        _iterator_belong_to_vector(cpt_vector, cpt_iterator) &&
        _iterator_belong_to_vector(cpt_vector, &t_iterator));

    if(_GET_VECTOR_COREPOS(cpt_iterator) == _GET_VECTOR_COREPOS(&t_iterator))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void _vector_iterator_get_value(
    const vector_t* cpt_vector, const vector_iterator_t* cpt_iterator,
    void* pv_value)
{
    assert(_iterator_belong_to_vector(cpt_vector, cpt_iterator));
    assert(pv_value != NULL);
    assert(vector_size(cpt_vector) > 0);
    assert(!iterator_equal(cpt_iterator, vector_end(cpt_vector)));

    memcpy(pv_value, _GET_VECTOR_COREPOS(cpt_iterator), cpt_vector->_t_typesize);
}

void _vector_iterator_set_value(
    const struct _tagvector* cpt_vector, const vector_iterator_t* cpt_iterator, 
    const void* cpv_value)
{
    assert(_iterator_belong_to_vector(cpt_vector, cpt_iterator));
    assert(cpv_value != NULL);
    assert(vector_size(cpt_vector) > 0);
    assert(!iterator_equal(cpt_iterator, vector_end(cpt_vector)));

    memcpy(
        _GET_VECTOR_COREPOS(cpt_iterator), cpv_value, cpt_vector->_t_typesize);
}

const void* _vector_iterator_get_pointer(
    const struct _tagvector* cpt_vector, const vector_iterator_t* cpt_iterator)
{
#ifdef NDEBUG
    vector_t* pt_avoidwarning = NULL;
    pt_avoidwarning = (vector_t*)cpt_vector;
#endif

    assert(_iterator_belong_to_vector(cpt_vector, cpt_iterator));
    assert(!iterator_equal(cpt_iterator, vector_end(cpt_vector)));

    return _GET_VECTOR_COREPOS(cpt_iterator);
}

void _vector_iterator_next(
    const struct _tagvector* cpt_vector, vector_iterator_t* pt_iterator)
{
    assert(_iterator_belong_to_vector(cpt_vector, pt_iterator));

    _GET_VECTOR_COREPOS(pt_iterator) += cpt_vector->_t_typesize;

    assert(_iterator_belong_to_vector(cpt_vector, pt_iterator));
}

void _vector_iterator_prev(
    const struct _tagvector* cpt_vector, vector_iterator_t* pt_iterator)
{
    assert(_iterator_belong_to_vector(cpt_vector, pt_iterator));
    
    _GET_VECTOR_COREPOS(pt_iterator) -= cpt_vector->_t_typesize;

    assert(_iterator_belong_to_vector(cpt_vector, pt_iterator));
}

void* _vector_iterator_at(
    const struct _tagvector* cpt_vector, const vector_iterator_t* cpt_iterator,
    unsigned int un_index)
{
    char* pc_indexpos = NULL;

    assert(_iterator_belong_to_vector(cpt_vector, cpt_iterator));

    pc_indexpos = _GET_VECTOR_COREPOS(cpt_iterator) + cpt_vector->_t_typesize * un_index;
    assert(
        pc_indexpos >= cpt_vector->_pc_start &&
        pc_indexpos < cpt_vector->_pc_finish);

    return pc_indexpos;
}

void _vector_iterator_next_n(
    const struct _tagvector* cpt_vector, vector_iterator_t* pt_iterator, int n_step)
{
    assert(_iterator_belong_to_vector(cpt_vector, pt_iterator));

    _GET_VECTOR_COREPOS(pt_iterator) += cpt_vector->_t_typesize * n_step;

    assert(_iterator_belong_to_vector(cpt_vector, pt_iterator));
}

void _vector_iterator_prev_n(
    const struct _tagvector* cpt_vector, vector_iterator_t* pt_iterator, int n_step)
{
    assert(_iterator_belong_to_vector(cpt_vector, pt_iterator));

    _GET_VECTOR_COREPOS(pt_iterator) -= cpt_vector->_t_typesize * n_step;

    assert(_iterator_belong_to_vector(cpt_vector, pt_iterator));
}

int _vector_iterator_minus(
    const struct _tagvector* cpt_vector, const vector_iterator_t* cpt_iterator,
    vector_iterator_t t_iterator)
{
    assert(
        _iterator_belong_to_vector(cpt_vector, cpt_iterator) &&
        _iterator_belong_to_vector(cpt_vector, &t_iterator));

    return (_GET_VECTOR_COREPOS(cpt_iterator) - _GET_VECTOR_COREPOS(&t_iterator)) / 
           (int)cpt_vector->_t_typesize;
}

bool_t _vector_iterator_less(
    const struct _tagvector* cpt_vector, const vector_iterator_t* cpt_iterator,
    vector_iterator_t t_iterator)
{
#ifdef NDEBUG
    vector_t* pt_avoidwarning = NULL;
    pt_avoidwarning = (vector_t*)cpt_vector;
#endif

    assert(
        _iterator_belong_to_vector(cpt_vector, cpt_iterator) &&
        _iterator_belong_to_vector(cpt_vector, &t_iterator));

    if(_GET_VECTOR_COREPOS(cpt_iterator) < _GET_VECTOR_COREPOS(&t_iterator))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t _vector_iterator_before(
    const vector_iterator_t* cpt_iteratorfirst, const vector_iterator_t* cpt_iteratorsecond)
{
    assert(_iterator_for_one_and_the_same_vector(cpt_iteratorfirst, cpt_iteratorsecond));
    assert(
        _iterator_belong_to_vector(
            _GET_VECTOR_CONTAINER(cpt_iteratorfirst), cpt_iteratorfirst) &&
        _iterator_belong_to_vector(
            _GET_VECTOR_CONTAINER(cpt_iteratorsecond), cpt_iteratorsecond));
    assert(
        _GET_VECTOR_COREPOS(cpt_iteratorfirst) != NULL &&
        _GET_VECTOR_COREPOS(cpt_iteratorsecond) != NULL &&
        _GET_VECTOR_CONTAINER(cpt_iteratorfirst) != NULL &&
        _GET_VECTOR_CONTAINER(cpt_iteratorsecond) != NULL);

    if(_GET_VECTOR_COREPOS(cpt_iteratorfirst) < 
       _GET_VECTOR_COREPOS(cpt_iteratorsecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}


/* private vector function */
vector_t _create_vector(size_t t_typesize, const char* s_typename)
{
    vector_t t_newvector;

    assert(t_typesize > 0);
    assert(s_typename != NULL);

    t_newvector._t_typesize = t_typesize;
    memset(t_newvector._sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(t_newvector._sz_typename, s_typename, _ELEM_TYPE_NAME_SIZE);
    _unify_types(t_newvector._t_typesize, t_newvector._sz_typename);
    t_newvector._pc_start = NULL;
    t_newvector._pc_finish = NULL;
    t_newvector._pc_endofstorage = NULL;
    t_newvector._pfun_cmp = NULL;

    return t_newvector;
}

void _vector_push_back_varg(vector_t* pt_vector, va_list val_elemlist)
{
    assert(pt_vector != NULL);

    /* if the remain capacity is less then the element count */
    if(vector_capacity(pt_vector) == vector_size(pt_vector)) 
    {
        /* reserve the new size */
        /* new size = old size + 2 */
        vector_reserve(pt_vector, vector_size(pt_vector) + 2);
    }

    /* append the element to the end of vector */
    _get_varg_value(
        pt_vector->_pc_finish, val_elemlist,
        pt_vector->_t_typesize, pt_vector->_sz_typename);
    pt_vector->_pc_finish += pt_vector->_t_typesize;
}

/* vector function */
/* initialize and destroy */
void _vector_init_elem_varg(
    vector_t* pt_vector, size_t t_count, va_list val_elemlist)
{
    size_t t_index = 0;

    assert(pt_vector != NULL);
    assert(
        pt_vector->_pc_start == NULL && 
        pt_vector->_pc_finish == NULL &&
        pt_vector->_pc_endofstorage == NULL &&
        pt_vector->_pfun_cmp == NULL);

    allocate_init(&pt_vector->_t_allocater);
    if(t_count > 0)
    {
        pt_vector->_pc_start = allocate(
            &pt_vector->_t_allocater, pt_vector->_t_typesize, (2 * t_count));
        assert(pt_vector->_pc_start != NULL);
        pt_vector->_pc_finish =
            pt_vector->_pc_start + pt_vector->_t_typesize * t_count;
        pt_vector->_pc_endofstorage = 
            pt_vector->_pc_start + pt_vector->_t_typesize * (2 * t_count);

        for(t_index = 0; t_index < t_count; ++ t_index)
        {
            _get_varg_value(
                pt_vector->_pc_start + t_index * pt_vector->_t_typesize, val_elemlist,
                pt_vector->_t_typesize, pt_vector->_sz_typename);
        }
    }

    pt_vector->_pfun_cmp = _get_cmp_function(pt_vector->_sz_typename);
}

void _vector_init_elem(vector_t* pt_vector, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _vector_init_elem_varg(pt_vector, t_count, val_elemlist);
}

void vector_init_n(vector_t* pt_vector, size_t t_count)
{
    _vector_init_elem(pt_vector, t_count, 0x00);
}

void vector_init(vector_t* pt_vector)
{
    vector_init_n(pt_vector, 0);
}

void vector_destroy(vector_t* pt_vector)
{
    assert(pt_vector != NULL);
    assert(pt_vector->_pc_finish - pt_vector->_pc_start >= 0);
    assert(pt_vector->_pc_endofstorage - pt_vector->_pc_start >= 0);
    
    /* free vector memory */
    if(pt_vector->_pc_start != NULL)
    {
        deallocate(
            &pt_vector->_t_allocater, pt_vector->_pc_start, pt_vector->_t_typesize, 
            (pt_vector->_pc_endofstorage - pt_vector->_pc_start) / pt_vector->_t_typesize);
    }
    allocate_destroy(&pt_vector->_t_allocater);

    pt_vector->_pc_start = NULL;
    pt_vector->_pc_finish = NULL;
    pt_vector->_pc_endofstorage = NULL;
    pt_vector->_pfun_cmp = NULL;
}

void vector_init_copy(vector_t* pt_vectordest, const vector_t* cpt_vectorsrc)
{
    vector_init_copy_range(
        pt_vectordest, vector_begin(cpt_vectorsrc), vector_end(cpt_vectorsrc));
}

void vector_init_copy_range(
    vector_t* pt_vector, vector_iterator_t t_begin, vector_iterator_t t_end)
{
    vector_iterator_t t_dest;
    vector_iterator_t t_src;

    assert(pt_vector != NULL);
    assert(
        pt_vector->_t_typesize == _GET_VECTOR_CONTAINER(&t_begin)->_t_typesize &&
        strncmp(
            pt_vector->_sz_typename, 
            _GET_VECTOR_CONTAINER(&t_begin)->_sz_typename,
            _ELEM_TYPE_NAME_SIZE) == 0);
    assert(
        pt_vector->_pc_start == NULL && 
        pt_vector->_pc_finish == NULL &&
        pt_vector->_pc_endofstorage == NULL &&
        pt_vector->_pfun_cmp == NULL);
    assert(iterator_equal(&t_begin, t_end) || _vector_iterator_before(&t_begin, &t_end));

    vector_init_n(pt_vector, iterator_distance(t_begin, t_end));

    for(t_dest = vector_begin(pt_vector), t_src = t_begin;
        !iterator_equal(&t_dest, vector_end(pt_vector)) && !iterator_equal(&t_src, t_end);
        iterator_next(&t_dest), iterator_next(&t_src))
    {
        memcpy(
            _GET_VECTOR_COREPOS(&t_dest), _GET_VECTOR_COREPOS(&t_src),
            pt_vector->_t_typesize);
    }
    assert(
        iterator_equal(&t_dest, vector_end(pt_vector)) &&
        iterator_equal(&t_src, t_end));
}

size_t vector_size(const vector_t* cpt_vector)
{
    assert(cpt_vector != NULL);
    return (cpt_vector->_pc_finish - cpt_vector->_pc_start) / 
            cpt_vector->_t_typesize;
}

bool_t vector_empty(const vector_t* cpt_vector)
{
    assert(cpt_vector != NULL);
    
    if(cpt_vector->_pc_start == cpt_vector->_pc_finish)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t vector_max_size(const vector_t* cpt_vector)
{
    assert(cpt_vector != NULL);

    return (size_t)(-1) / cpt_vector->_t_typesize;
}

size_t vector_capacity(const vector_t* cpt_vector)
{
    assert(cpt_vector != NULL);

    return (cpt_vector->_pc_endofstorage - cpt_vector->_pc_start) /
            cpt_vector->_t_typesize;
}

void vector_reserve(vector_t* pt_vector, size_t t_reservesize)
{
    char*  pc_reservemem = NULL; /* new memory for reserve */
    size_t t_oldsize = 0;
    size_t t_oldcapacitysize = 0;

    assert(pt_vector != NULL);

    if(vector_capacity(pt_vector) < t_reservesize)
    {
        /* allocate the new vector with reserve size */
        pc_reservemem = allocate(
            &pt_vector->_t_allocater, pt_vector->_t_typesize, t_reservesize);
        assert(pc_reservemem != NULL);
        /* copy the vector element to new vector */
        t_oldsize = pt_vector->_pc_finish - pt_vector->_pc_start;
        t_oldcapacitysize = pt_vector->_pc_endofstorage - pt_vector->_pc_start;
        memcpy(pc_reservemem, pt_vector->_pc_start, t_oldsize);
        /* free the old vector element */
        if(pt_vector->_pc_start != NULL)
        {
            deallocate(
                &pt_vector->_t_allocater, pt_vector->_pc_start, pt_vector->_t_typesize, 
                t_oldcapacitysize / pt_vector->_t_typesize);
        }
        pt_vector->_pc_start = pc_reservemem;
        pt_vector->_pc_finish = pt_vector->_pc_start + t_oldsize;
        pt_vector->_pc_endofstorage = 
            pt_vector->_pc_start + (pt_vector->_t_typesize * t_reservesize);
    }
}

bool_t vector_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    int i = 0;
    char* pc_first = NULL;      /* the first vector core pointer */
    char* pc_second = NULL;     /* the second vector core pointer */

    assert(cpt_vectorfirst != NULL && cpt_vectorsecond != NULL);

    /* the element type is equal */
    if(cpt_vectorfirst->_t_typesize != cpt_vectorsecond->_t_typesize ||
       strncmp(
           cpt_vectorfirst->_sz_typename, 
           cpt_vectorsecond->_sz_typename, 
           _ELEM_TYPE_NAME_SIZE) != 0)
    {
        return false;
    }
    /* the function pointer is equal */
    if(cpt_vectorfirst->_pfun_cmp != cpt_vectorsecond->_pfun_cmp)
    {
        return false;
    }
    /* the element count is equal */
    if(vector_size(cpt_vectorfirst) != vector_size(cpt_vectorsecond))
    {
        return false;
    }

    /* if have the user equal function for each element */
    if(cpt_vectorfirst->_pfun_cmp != NULL)
    {
        /* each element is equal */
        for(i = 0; i < (int)vector_size(cpt_vectorfirst); ++i)
        {
            pc_first = cpt_vectorfirst->_pc_start + cpt_vectorfirst->_t_typesize * i;
            pc_second = cpt_vectorsecond->_pc_start + cpt_vectorsecond->_t_typesize * i;

            if((*cpt_vectorfirst->_pfun_cmp)(pc_first, pc_second) != 0)
            {
                return false;
            }
        }
    }
    else
    {
        /* compare the memory for test */
        if(memcmp(
                cpt_vectorfirst->_pc_start, cpt_vectorsecond->_pc_start,
                cpt_vectorfirst->_pc_finish - cpt_vectorfirst->_pc_start) != 0)
        {
            return false;
        }
    }

    return true;
}

bool_t vector_not_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    return !vector_equal(cpt_vectorfirst, cpt_vectorsecond);
}

bool_t vector_less(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    size_t t_firstsize = 0;     /* the first vector size */
    size_t t_secondsize = 0;    /* the second vector size */
    size_t t_shortsize = 0;     /* the short length within first and second */
    char*  pc_first = NULL;     /* the first vector pointer */
    char*  pc_second = NULL;    /* the second vector pointer */
    int    n_cmpresult = 0;     /* element compare result */
    int    i = 0;

    assert(_same_vector_type(cpt_vectorfirst, cpt_vectorsecond));

    t_firstsize = vector_size(cpt_vectorfirst);
    t_secondsize = vector_size(cpt_vectorsecond);
    t_shortsize = t_firstsize < t_secondsize ? t_firstsize : t_secondsize;

    /* if have the user defined compare function */
    /* compare each element with short length of vector */
    for(i = 0; i < (int)t_shortsize; ++i)
    {
        pc_second = cpt_vectorsecond->_pc_start + i * cpt_vectorsecond->_t_typesize;
        pc_first = cpt_vectorfirst->_pc_start + i * cpt_vectorfirst->_t_typesize;
        /* if vector has the user defined compare function */
        if(cpt_vectorfirst->_pfun_cmp != NULL)
        {
            n_cmpresult = (*cpt_vectorfirst->_pfun_cmp)(pc_first, pc_second);
            /* 
             * if any element in first vector are less then the second 
             * return true
             */
            if(n_cmpresult < 0)
            {
                return true;
            }
            /* 
             * if any element in first vector are great then the second 
             * return false
             */
            else if(n_cmpresult > 0)
            {
                return false;
            }
        }
        else /* use memory compare */
        {
            n_cmpresult = memcmp(pc_first, pc_second, cpt_vectorfirst->_t_typesize);
            if(n_cmpresult < 0)
            {
                return true;
            }
            else if(n_cmpresult > 0)
            {
                return false;
            }
        }
    }

    if(t_firstsize < t_secondsize)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t vector_great(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    return vector_less(cpt_vectorsecond, cpt_vectorfirst);
}

bool_t vector_less_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    if(vector_less(cpt_vectorfirst, cpt_vectorsecond) == true ||
       vector_equal(cpt_vectorfirst, cpt_vectorsecond) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t vector_great_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    if(vector_great(cpt_vectorfirst, cpt_vectorsecond) == true ||
       vector_equal(cpt_vectorfirst, cpt_vectorsecond) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* assign */
void vector_assign(vector_t* pt_vectordest, const vector_t* cpt_vectorsrc)
{
    assert(_same_vector_type(pt_vectordest, cpt_vectorsrc));

    /* destroy vector */
    vector_destroy(pt_vectordest);
    /* initialize vector copy */
    vector_init_copy(pt_vectordest, cpt_vectorsrc);
}

void _vector_assign_elem_varg(
    vector_t* pt_vector, size_t t_count, va_list val_elemlist)
{
    int (*pfun_cmp)(const void*, const void*);

    assert(pt_vector != NULL);

    pfun_cmp = pt_vector->_pfun_cmp;

    /* destroy vector */
    vector_destroy(pt_vector);
    /* initialzie vector */
    _vector_init_elem_varg(pt_vector, t_count, val_elemlist);
}

void _vector_assign_elem(vector_t* pt_vector, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _vector_assign_elem_varg(pt_vector, t_count, val_elemlist);
}

void vector_assign_range(
    vector_t* pt_vector, vector_iterator_t t_begin, vector_iterator_t t_end)
{
    /* assign the two iterator is as the same type as pt_vector */
    assert(_same_vector_iterator_type(pt_vector, &t_begin));
    assert(iterator_equal(&t_begin, t_end) || _vector_iterator_before(&t_begin, &t_end));

    /*destroy vector*/
    vector_destroy(pt_vector);
    /* initialize copy range */
    vector_init_copy_range(pt_vector, t_begin, t_end);
}

void vector_swap(vector_t* pt_vectorfirst, vector_t* pt_vectorsecond)
{
    vector_t t_swapvector;  /* the swap temporary vector */

    /* test the two vector has the same type */
    assert(_same_vector_type(pt_vectorfirst, pt_vectorsecond));

    t_swapvector = *pt_vectorfirst;
    *pt_vectorfirst = *pt_vectorsecond;
    *pt_vectorsecond = t_swapvector;
}

void* vector_at(const vector_t* cpt_vector, size_t t_pos)
{
    assert(cpt_vector != NULL);
    assert(t_pos < vector_size(cpt_vector));

    return cpt_vector->_pc_start + t_pos * cpt_vector->_t_typesize;
}

void* vector_front(const vector_t* cpt_vector)
{
    if(vector_empty(cpt_vector))
    {
        return NULL;
    }
    else
    {
        return vector_at(cpt_vector, 0);
    }
}

void* vector_back(const vector_t* cpt_vector)
{
    if(vector_empty(cpt_vector))
    {
        return NULL;
    }
    else
    {
        return vector_at(cpt_vector, vector_size(cpt_vector) - 1);
    }
}

vector_iterator_t vector_begin(const vector_t* cpt_vector)
{
    vector_iterator_t t_newiterator; /* new vector iterator */

    assert(cpt_vector != NULL);

    t_newiterator = create_vector_iterator();
    _GET_CONTAINER(&t_newiterator) = (vector_t*)cpt_vector;
    _GET_VECTOR_COREPOS(&t_newiterator) = cpt_vector->_pc_start;

    return t_newiterator;
}

vector_iterator_t vector_end(const vector_t* cpt_vector)
{
    vector_iterator_t t_newiterator;

    assert(cpt_vector != NULL);

    t_newiterator = create_vector_iterator();
    _GET_CONTAINER(&t_newiterator) = (vector_t*)cpt_vector;
    _GET_VECTOR_COREPOS(&t_newiterator) = cpt_vector->_pc_finish;

    return t_newiterator;
}

vector_reverse_iterator_t vector_rbegin(const vector_t* cpt_vector)
{
    vector_reverse_iterator_t t_newiterator;

    assert(cpt_vector != NULL);

    t_newiterator = create_vector_iterator();
    _GET_CONTAINER(&t_newiterator) = (vector_t*)cpt_vector;
    _GET_VECTOR_COREPOS(&t_newiterator) = cpt_vector->_pc_finish - cpt_vector->_t_typesize;

    return t_newiterator;
}

vector_reverse_iterator_t vector_rend(const vector_t* cpt_vector)
{
    vector_reverse_iterator_t t_newiterator;

    assert(cpt_vector != NULL);

    t_newiterator = create_vector_iterator();
    _GET_CONTAINER(&t_newiterator) = (vector_t*)cpt_vector;
    _GET_VECTOR_COREPOS(&t_newiterator) = cpt_vector->_pc_start - cpt_vector->_t_typesize;

    return t_newiterator;
}

vector_iterator_t _vector_insert_n(
    vector_t* pt_vector, vector_iterator_t t_pos, size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    return _vector_insert_n_varg(pt_vector, t_pos, t_count, val_elemlist);
}

vector_iterator_t _vector_insert_n_varg(
    vector_t* pt_vector, vector_iterator_t t_pos, size_t t_count, va_list val_elemlist)
{
    /* test the vector and iterator is valid */
    assert(_iterator_belong_to_vector(pt_vector, &t_pos));

    if(t_count > 0)
    {
        size_t t_index = 0;

        /* if the remain capacity is less then the element count */
        if(vector_size(pt_vector) + t_count > vector_capacity(pt_vector))
        {
            size_t t_insertpos = iterator_distance(vector_begin(pt_vector), t_pos);
            /* reserve the new size */
            /* new size = old size + 2 * element count */
            vector_reserve(pt_vector, vector_size(pt_vector) + 2 * t_count);
            t_pos = vector_begin(pt_vector);
            iterator_next_n(&t_pos, t_insertpos);
        }

        /* insert the element counts of element to the position */
        /* move the elements from pos to the finish of vector to the 
         * memory that after the pos element count*/
        memmove(
            _GET_VECTOR_COREPOS(&t_pos) + t_count * pt_vector->_t_typesize,
            _GET_VECTOR_COREPOS(&t_pos),
            pt_vector->_pc_finish - _GET_VECTOR_COREPOS(&t_pos)); 
        pt_vector->_pc_finish += t_count * pt_vector->_t_typesize;
        /* insert element counts copys to the pos */
        for(t_index = 0; t_index < t_count; ++t_index)
        {
            _get_varg_value(
                _GET_VECTOR_COREPOS(&t_pos) + t_index * pt_vector->_t_typesize,
                val_elemlist, pt_vector->_t_typesize, pt_vector->_sz_typename);
        }

        iterator_next_n(&t_pos, t_count);
    }

    return t_pos;
}

void vector_insert_range(
    vector_t* pt_vector, vector_iterator_t t_pos,
    vector_iterator_t t_begin, vector_iterator_t t_end)
{
    size_t t_count = 0; /* the element count */

    /* test the vector and iterator is valid */
    assert(_iterator_belong_to_vector(pt_vector, &t_pos));
    assert(iterator_equal(&t_begin, t_end) || _vector_iterator_before(&t_begin, &t_end));
    assert(_same_vector_iterator_type(pt_vector, &t_begin));

    t_count = iterator_distance(t_begin, t_end);
    /* if the remain capacity is less then the element count */
    if(vector_size(pt_vector) + t_count > vector_capacity(pt_vector))
    {
        size_t t_iteratordistance = _GET_VECTOR_COREPOS(&t_pos) - pt_vector->_pc_start;
        /* reserve the new size */
        /* new size = old size + 2 * element count */
        vector_reserve(pt_vector, vector_size(pt_vector) + 2 * t_count);
        _GET_VECTOR_COREPOS(&t_pos) = pt_vector->_pc_start + t_iteratordistance;
    }

    /* insert the element counts of element to the position */
    /* move the elements from pos to the finish of vector to the 
     * memory that after the pos element count*/
    memmove(
        _GET_VECTOR_COREPOS(&t_pos) + t_count * pt_vector->_t_typesize,
        _GET_VECTOR_COREPOS(&t_pos),
        pt_vector->_pc_finish - _GET_VECTOR_COREPOS(&t_pos)); 
    pt_vector->_pc_finish += t_count * pt_vector->_t_typesize;
    /* insert element counts copys to the pos */
    memcpy(
        _GET_VECTOR_COREPOS(&t_pos), _GET_VECTOR_COREPOS(&t_begin),
        t_count * pt_vector->_t_typesize);
}

void _vector_push_back(vector_t* pt_vector, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_vector);
    _vector_push_back_varg(pt_vector, val_elemlist);
}

void vector_pop_back(vector_t* pt_vector)
{
    assert(pt_vector != NULL);
    assert(vector_size(pt_vector) > 0);

    pt_vector->_pc_finish -= pt_vector->_t_typesize;
}

vector_iterator_t vector_erase(vector_t* pt_vector, vector_iterator_t t_pos)
{
    assert(_iterator_belong_to_vector(pt_vector, &t_pos));
    assert(!iterator_equal(&t_pos, vector_end(pt_vector)));

    memmove(
        _GET_VECTOR_COREPOS(&t_pos),
        _GET_VECTOR_COREPOS(&t_pos) + pt_vector->_t_typesize,
        pt_vector->_pc_finish - _GET_VECTOR_COREPOS(&t_pos) - pt_vector->_t_typesize);
    pt_vector->_pc_finish -= pt_vector->_t_typesize;

    return t_pos;
}

vector_iterator_t vector_erase_range(
    vector_t* pt_vector, vector_iterator_t t_begin, vector_iterator_t t_end)
{
    size_t t_erasesize = 0;

    assert(_iterator_belong_to_vector(pt_vector, &t_begin));
    assert(iterator_equal(&t_begin, t_end) || _vector_iterator_before(&t_begin, &t_end));
    assert(!iterator_equal(&t_begin, vector_end(pt_vector)));

    /* move the element */
    t_erasesize = iterator_distance(t_begin, t_end);
    memmove(
        _GET_VECTOR_COREPOS(&t_begin),
        _GET_VECTOR_COREPOS(&t_end),
        pt_vector->_pc_finish - _GET_VECTOR_COREPOS(&t_end));
    pt_vector->_pc_finish -= t_erasesize * pt_vector->_t_typesize;

    return t_begin;
}

void vector_resize(vector_t* pt_vector, size_t t_resize)
{
    vector_resize_elem(pt_vector, t_resize, 0x00);
}

void _vector_resize_elem_varg(
    vector_t* pt_vector, size_t t_resize, va_list val_elemlist)
{
    vector_iterator_t t_cutpos;     /* the cut position */
    size_t            t_expsize = 0;
    size_t            t_index = 0;

    assert(pt_vector != NULL);

    if(t_resize < vector_size(pt_vector))
    {
        t_cutpos = vector_begin(pt_vector);
        iterator_next_n(&t_cutpos, t_resize);
        vector_erase_range(pt_vector, t_cutpos, vector_end(pt_vector));
    }
    else
    {
        t_expsize = t_resize - vector_size(pt_vector);
        if(t_resize > vector_capacity(pt_vector))
        {
            vector_reserve(pt_vector, vector_size(pt_vector) + 2 * t_expsize);
        }
        for(t_index = 0; t_index < t_expsize; ++t_index)
        {
            _get_varg_value(
                pt_vector->_pc_finish + t_index * pt_vector->_t_typesize,
                val_elemlist, pt_vector->_t_typesize, pt_vector->_sz_typename);
        }
        pt_vector->_pc_finish += t_expsize * pt_vector->_t_typesize;
    }
}

void _vector_resize_elem(vector_t* pt_vector, size_t t_resize, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_resize);
    _vector_resize_elem_varg(pt_vector, t_resize, val_elemlist);
}

void vector_clear(vector_t* pt_vector)
{
    vector_erase_range(pt_vector, vector_begin(pt_vector), vector_end(pt_vector));
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _iterator_belong_to_vector(
    const vector_t* cpt_vector, const vector_iterator_t* cpt_iterator)
{
    assert(cpt_vector != NULL);
    assert(cpt_iterator != NULL);
    assert(_GET_VECTOR_CONTAINER(cpt_iterator) == cpt_vector);

    if(_GET_VECTOR_COREPOS(cpt_iterator) >= cpt_vector->_pc_start &&
       _GET_VECTOR_COREPOS(cpt_iterator) <= cpt_vector->_pc_finish)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool_t _same_vector_iterator_type(
    const vector_t* cpt_vector, const vector_iterator_t* cpt_iterator)
{
    assert(
        cpt_vector != NULL &&
        cpt_iterator != NULL &&
        _GET_VECTOR_CONTAINER(cpt_iterator) != NULL);
    assert(
        _GET_VECTOR_CONTAINER_TYPE(cpt_iterator) == _VECTOR_CONTAINER &&
        _GET_VECTOR_ITERATOR_TYPE(cpt_iterator) == _RANDOM_ACCESS_ITERATOR);
    assert(
        cpt_vector->_t_typesize == _GET_VECTOR_CONTAINER(cpt_iterator)->_t_typesize &&
        strncmp(
            cpt_vector->_sz_typename, 
            _GET_VECTOR_CONTAINER(cpt_iterator)->_sz_typename, 
            _ELEM_TYPE_NAME_SIZE) == 0);
    assert(
        cpt_vector->_pfun_cmp == _GET_VECTOR_CONTAINER(cpt_iterator)->_pfun_cmp);

    return true;
}

static bool_t _iterator_for_one_and_the_same_vector(
    const vector_iterator_t* cpt_iteratorfirst, 
    const vector_iterator_t* cpt_iteratorsecond)
{
    assert(cpt_iteratorfirst != NULL && cpt_iteratorsecond != NULL);
    assert(
        _GET_VECTOR_CONTAINER(cpt_iteratorfirst) == 
        _GET_VECTOR_CONTAINER(cpt_iteratorsecond));
    assert(
        _GET_VECTOR_CONTAINER_TYPE(cpt_iteratorfirst) == _VECTOR_CONTAINER &&
        _GET_VECTOR_CONTAINER_TYPE(cpt_iteratorsecond) == _VECTOR_CONTAINER);
    assert(
        _GET_VECTOR_ITERATOR_TYPE(cpt_iteratorfirst) == _RANDOM_ACCESS_ITERATOR &&
        _GET_VECTOR_ITERATOR_TYPE(cpt_iteratorsecond) == _RANDOM_ACCESS_ITERATOR);

    return true;
}

static bool_t _same_vector_type(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    assert(cpt_vectorfirst != NULL && cpt_vectorsecond != NULL);
    assert(
        cpt_vectorfirst->_pc_start != NULL &&
        cpt_vectorfirst->_pc_finish != NULL &&
        cpt_vectorfirst->_pc_endofstorage != NULL &&
        cpt_vectorsecond->_pc_start != NULL &&
        cpt_vectorsecond->_pc_finish != NULL &&
        cpt_vectorsecond->_pc_endofstorage != NULL);
    assert(
        cpt_vectorfirst->_t_typesize == cpt_vectorsecond->_t_typesize &&
        strncmp(
            cpt_vectorfirst->_sz_typename,
            cpt_vectorsecond->_sz_typename,
            _ELEM_TYPE_NAME_SIZE) == 0);
    assert(cpt_vectorfirst->_pfun_cmp == cpt_vectorsecond->_pfun_cmp);

    return true;
}
#endif /* NDEBUG */

/** eof **/

