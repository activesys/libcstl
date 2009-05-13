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
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
 */

/** include section **/
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "cstl_alloc.h"
#include "cstl_types.h"
#include "cstl_iterator.h"
#include "cstl_iterator_private.h"

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
    const vector_t* cpt_vector, vector_iterator_t t_iter);
static bool_t _same_vector_iterator_type(
    const vector_t* cpt_vector, vector_iterator_t t_iter);
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

    _GET_VECTOR_COREPOS(t_newiterator) = NULL;
    _GET_CONTAINER(t_newiterator) = NULL;
    _GET_VECTOR_CONTAINER_TYPE(t_newiterator) = _VECTOR_CONTAINER;
    _GET_VECTOR_ITERATOR_TYPE(t_newiterator) = _RANDOM_ACCESS_ITERATOR;

    return t_newiterator;
}

bool_t _vector_iterator_equal(
    vector_iterator_t t_iterfirst, vector_iterator_t t_itersecond)
{
    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_VECTOR_CONTAINER(t_iterfirst) == _GET_VECTOR_CONTAINER(t_itersecond));
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_itersecond), t_itersecond));

    if(_GET_VECTOR_COREPOS(t_iterfirst) == _GET_VECTOR_COREPOS(t_itersecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void _vector_iterator_get_value(vector_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, vector_end(_GET_VECTOR_CONTAINER(t_iter))));

    memcpy(
        pv_value, _GET_VECTOR_COREPOS(t_iter),
        _GET_VECTOR_CONTAINER(t_iter)->_t_typesize);
}

void _vector_iterator_set_value(vector_iterator_t t_iter, const void* cpv_value)
{
    assert(cpv_value != NULL);
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, vector_end(_GET_VECTOR_CONTAINER(t_iter))));

    memcpy(
        _GET_VECTOR_COREPOS(t_iter), cpv_value,
        _GET_VECTOR_CONTAINER(t_iter)->_t_typesize);
}

const void* _vector_iterator_get_pointer(vector_iterator_t t_iter)
{
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, vector_end(_GET_VECTOR_CONTAINER(t_iter))));

    return _GET_VECTOR_COREPOS(t_iter);
}

vector_iterator_t _vector_iterator_next(vector_iterator_t t_iter)
{
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) += _GET_VECTOR_CONTAINER(t_iter)->_t_typesize;
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    return t_iter;
}

vector_iterator_t _vector_iterator_prev(vector_iterator_t t_iter)
{
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) -= _GET_VECTOR_CONTAINER(t_iter)->_t_typesize;
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    return t_iter;
}

void* _vector_iterator_at(vector_iterator_t t_iter, int n_index)
{
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) += _GET_VECTOR_CONTAINER(t_iter)->_t_typesize * n_index;
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    return _GET_VECTOR_COREPOS(t_iter);
}

vector_iterator_t _vector_iterator_next_n(vector_iterator_t t_iter, int n_step)
{
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) += _GET_VECTOR_CONTAINER(t_iter)->_t_typesize * n_step;
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    return t_iter;
}

vector_iterator_t _vector_iterator_prev_n(vector_iterator_t t_iter, int n_step)
{
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) -= _GET_VECTOR_CONTAINER(t_iter)->_t_typesize * n_step;
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    return t_iter;
}

int _vector_iterator_minus(vector_iterator_t t_iterfirst, vector_iterator_t t_itersecond)
{
    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_VECTOR_CONTAINER(t_iterfirst) == _GET_VECTOR_CONTAINER(t_itersecond));
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_itersecond), t_itersecond));

    return (_GET_VECTOR_COREPOS(t_iterfirst) - _GET_VECTOR_COREPOS(t_itersecond)) / 
           (int)_GET_VECTOR_CONTAINER(t_iterfirst)->_t_typesize;
}

bool_t _vector_iterator_less(vector_iterator_t t_iterfirst, vector_iterator_t t_itersecond)
{
    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_VECTOR_CONTAINER(t_iterfirst) == _GET_VECTOR_CONTAINER(t_itersecond));
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_itersecond), t_itersecond));

    if(_GET_VECTOR_COREPOS(t_iterfirst) < _GET_VECTOR_COREPOS(t_itersecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t _vector_iterator_before(
    vector_iterator_t t_iterfirst, vector_iterator_t t_itersecond)
{
    return _vector_iterator_less(t_iterfirst, t_itersecond);
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
void _vector_init_elem_varg(vector_t* pt_vector, size_t t_count, va_list val_elemlist)
{
    size_t t_index = 0;
    void*  pv_init_elem = NULL;

    assert(pt_vector != NULL);
    assert(pt_vector->_pc_start == NULL && pt_vector->_pc_finish == NULL &&
           pt_vector->_pc_endofstorage == NULL && pt_vector->_pfun_cmp == NULL);

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

        /* get varg value only once */
        pv_init_elem = allocate(&pt_vector->_t_allocater, pt_vector->_t_typesize, 1);
        assert(pv_init_elem != NULL);
        _get_varg_value(
            pv_init_elem, val_elemlist, pt_vector->_t_typesize, pt_vector->_sz_typename);
        for(t_index = 0; t_index < t_count; ++ t_index)
        {
            memcpy(
                pt_vector->_pc_start + t_index * pt_vector->_t_typesize,
                pv_init_elem, pt_vector->_t_typesize);
        }
        deallocate(&pt_vector->_t_allocater, pv_init_elem, pt_vector->_t_typesize, 1);
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
    assert(pt_vector->_t_typesize == _GET_VECTOR_CONTAINER(t_begin)->_t_typesize &&
        strncmp(pt_vector->_sz_typename, _GET_VECTOR_CONTAINER(t_begin)->_sz_typename,
                _ELEM_TYPE_NAME_SIZE) == 0);
    assert(pt_vector->_pc_start == NULL && pt_vector->_pc_finish == NULL &&
           pt_vector->_pc_endofstorage == NULL && pt_vector->_pfun_cmp == NULL);
    assert(iterator_equal(t_begin, t_end) || _vector_iterator_before(t_begin, t_end));

    vector_init_n(pt_vector, iterator_distance(t_begin, t_end));

    for(t_dest = vector_begin(pt_vector), t_src = t_begin;
        !iterator_equal(t_dest, vector_end(pt_vector)) && !iterator_equal(t_src, t_end);
        t_dest = iterator_next(t_dest), t_src = iterator_next(t_src))
    {
        memcpy(
            _GET_VECTOR_COREPOS(t_dest), _GET_VECTOR_COREPOS(t_src),
            pt_vector->_t_typesize);
    }
    assert(iterator_equal(t_dest, vector_end(pt_vector)) && iterator_equal(t_src, t_end));
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
       strncmp(cpt_vectorfirst->_sz_typename, cpt_vectorsecond->_sz_typename, 
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
        if(memcmp(cpt_vectorfirst->_pc_start, cpt_vectorsecond->_pc_start,
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
    size_t t_index = 0;

    assert(_same_vector_type(cpt_vectorfirst, cpt_vectorsecond));

    t_firstsize = vector_size(cpt_vectorfirst);
    t_secondsize = vector_size(cpt_vectorsecond);
    t_shortsize = t_firstsize < t_secondsize ? t_firstsize : t_secondsize;

    /* if have the user defined compare function */
    /* compare each element with short length of vector */
    for(t_index = 0; t_index < t_shortsize; ++t_index)
    {
        pc_second = cpt_vectorsecond->_pc_start + t_index * cpt_vectorsecond->_t_typesize;
        pc_first = cpt_vectorfirst->_pc_start + t_index * cpt_vectorfirst->_t_typesize;
        /* if vector has the user defined compare function */
        if(cpt_vectorfirst->_pfun_cmp != NULL)
        {
            n_cmpresult = (*cpt_vectorfirst->_pfun_cmp)(pc_first, pc_second);
            /* 
             * if any element in first vector are less then the second return true
             */
            if(n_cmpresult < 0)
            {
                return true;
            }
            /* 
             * if any element in first vector are great then the second return false
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
    assert(_same_vector_iterator_type(pt_vector, t_begin));
    assert(iterator_equal(t_begin, t_end) || _vector_iterator_before(t_begin, t_end));

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
    _GET_CONTAINER(t_newiterator) = (vector_t*)cpt_vector;
    _GET_VECTOR_COREPOS(t_newiterator) = cpt_vector->_pc_start;

    return t_newiterator;
}

vector_iterator_t vector_end(const vector_t* cpt_vector)
{
    vector_iterator_t t_newiterator;

    assert(cpt_vector != NULL);

    t_newiterator = create_vector_iterator();
    _GET_CONTAINER(t_newiterator) = (vector_t*)cpt_vector;
    _GET_VECTOR_COREPOS(t_newiterator) = cpt_vector->_pc_finish;

    return t_newiterator;
}

vector_reverse_iterator_t vector_rbegin(const vector_t* cpt_vector)
{
    vector_reverse_iterator_t t_newiterator;

    assert(cpt_vector != NULL);

    t_newiterator = create_vector_iterator();
    _GET_CONTAINER(t_newiterator) = (vector_t*)cpt_vector;
    _GET_VECTOR_COREPOS(t_newiterator) = cpt_vector->_pc_finish - cpt_vector->_t_typesize;

    return t_newiterator;
}

vector_reverse_iterator_t vector_rend(const vector_t* cpt_vector)
{
    vector_reverse_iterator_t t_newiterator;

    assert(cpt_vector != NULL);

    t_newiterator = create_vector_iterator();
    _GET_CONTAINER(t_newiterator) = (vector_t*)cpt_vector;
    _GET_VECTOR_COREPOS(t_newiterator) = cpt_vector->_pc_start - cpt_vector->_t_typesize;

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
    void* pv_init_elem = NULL;

    /* test the vector and iterator is valid */
    assert(_iterator_belong_to_vector(pt_vector, t_pos));

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
            t_pos = iterator_next_n(t_pos, t_insertpos);
        }

        /* insert the element counts of element to the position */
        /* move the elements from pos to the finish of vector to the 
         * memory that after the pos element count*/
        memmove(
            _GET_VECTOR_COREPOS(t_pos) + t_count * pt_vector->_t_typesize,
            _GET_VECTOR_COREPOS(t_pos),
            pt_vector->_pc_finish - _GET_VECTOR_COREPOS(t_pos)); 
        pt_vector->_pc_finish += t_count * pt_vector->_t_typesize;
        /* insert element counts copys to the pos */

        /* get varg value only once */
        pv_init_elem = allocate(&pt_vector->_t_allocater, pt_vector->_t_typesize, 1);
        assert(pv_init_elem != NULL);
        _get_varg_value(
            pv_init_elem, val_elemlist, pt_vector->_t_typesize, pt_vector->_sz_typename);
        for(t_index = 0; t_index < t_count; ++t_index)
        {
            memcpy(
                _GET_VECTOR_COREPOS(t_pos) + t_index * pt_vector->_t_typesize,
                pv_init_elem,
                pt_vector->_t_typesize);
        }
        deallocate(&pt_vector->_t_allocater, pv_init_elem, pt_vector->_t_typesize, 1);

        t_pos = iterator_next_n(t_pos, t_count);
    }

    return t_pos;
}

void vector_insert_range(
    vector_t* pt_vector, vector_iterator_t t_pos,
    vector_iterator_t t_begin, vector_iterator_t t_end)
{
    size_t t_count = 0; /* the element count */

    /* test the vector and iterator is valid */
    assert(_iterator_belong_to_vector(pt_vector, t_pos));
    assert(iterator_equal(t_begin, t_end) || _vector_iterator_before(t_begin, t_end));
    assert(_same_vector_iterator_type(pt_vector, t_begin));

    t_count = iterator_distance(t_begin, t_end);
    /* if the remain capacity is less then the element count */
    if(vector_size(pt_vector) + t_count > vector_capacity(pt_vector))
    {
        size_t t_iteratordistance = _GET_VECTOR_COREPOS(t_pos) - pt_vector->_pc_start;
        /* reserve the new size */
        /* new size = old size + 2 * element count */
        vector_reserve(pt_vector, vector_size(pt_vector) + 2 * t_count);
        _GET_VECTOR_COREPOS(t_pos) = pt_vector->_pc_start + t_iteratordistance;
    }

    /* insert the element counts of element to the position */
    /* move the elements from pos to the finish of vector to the 
     * memory that after the pos element count*/
    memmove(
        _GET_VECTOR_COREPOS(t_pos) + t_count * pt_vector->_t_typesize,
        _GET_VECTOR_COREPOS(t_pos),
        pt_vector->_pc_finish - _GET_VECTOR_COREPOS(t_pos)); 
    pt_vector->_pc_finish += t_count * pt_vector->_t_typesize;
    /* insert element counts copys to the pos */
    memcpy(
        _GET_VECTOR_COREPOS(t_pos), _GET_VECTOR_COREPOS(t_begin),
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
    assert(_iterator_belong_to_vector(pt_vector, t_pos));
    assert(!iterator_equal(t_pos, vector_end(pt_vector)));

    memmove(
        _GET_VECTOR_COREPOS(t_pos),
        _GET_VECTOR_COREPOS(t_pos) + pt_vector->_t_typesize,
        pt_vector->_pc_finish - _GET_VECTOR_COREPOS(t_pos) - pt_vector->_t_typesize);
    pt_vector->_pc_finish -= pt_vector->_t_typesize;

    return t_pos;
}

vector_iterator_t vector_erase_range(
    vector_t* pt_vector, vector_iterator_t t_begin, vector_iterator_t t_end)
{
    size_t t_erasesize = 0;

    assert(_iterator_belong_to_vector(pt_vector, t_begin));
    assert(iterator_equal(t_begin, t_end) || _vector_iterator_before(t_begin, t_end));
    assert(!iterator_equal(t_begin, vector_end(pt_vector)));

    /* move the element */
    t_erasesize = iterator_distance(t_begin, t_end);
    memmove(
        _GET_VECTOR_COREPOS(t_begin),
        _GET_VECTOR_COREPOS(t_end),
        pt_vector->_pc_finish - _GET_VECTOR_COREPOS(t_end));
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
    void*             pv_init_elem = NULL;

    assert(pt_vector != NULL);

    if(t_resize < vector_size(pt_vector))
    {
        t_cutpos = vector_begin(pt_vector);
        t_cutpos = iterator_next_n(t_cutpos, t_resize);
        vector_erase_range(pt_vector, t_cutpos, vector_end(pt_vector));
    }
    else
    {
        t_expsize = t_resize - vector_size(pt_vector);
        if(t_resize > vector_capacity(pt_vector))
        {
            vector_reserve(pt_vector, vector_size(pt_vector) + 2 * t_expsize);
        }

        /* get varg value only once */
        pv_init_elem = allocate(&pt_vector->_t_allocater, pt_vector->_t_typesize, 1);
        assert(pv_init_elem != NULL);
        _get_varg_value(
            pv_init_elem, val_elemlist, pt_vector->_t_typesize, pt_vector->_sz_typename);
        for(t_index = 0; t_index < t_expsize; ++t_index)
        {
            memcpy(
                pt_vector->_pc_finish + t_index * pt_vector->_t_typesize,
                pv_init_elem,
                pt_vector->_t_typesize);
        }
        deallocate(&pt_vector->_t_allocater, pv_init_elem, pt_vector->_t_typesize, 1);
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
    const vector_t* cpt_vector, vector_iterator_t t_iter)
{
    assert(cpt_vector != NULL);
    assert(_GET_VECTOR_CONTAINER(t_iter) == cpt_vector);

    if(_GET_VECTOR_COREPOS(t_iter) >= cpt_vector->_pc_start &&
       _GET_VECTOR_COREPOS(t_iter) <= cpt_vector->_pc_finish)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool_t _same_vector_iterator_type(
    const vector_t* cpt_vector, vector_iterator_t t_iter)
{
    assert(cpt_vector != NULL && _GET_VECTOR_CONTAINER(t_iter) != NULL);
    assert(_GET_VECTOR_CONTAINER_TYPE(t_iter) == _VECTOR_CONTAINER &&
           _GET_VECTOR_ITERATOR_TYPE(t_iter) == _RANDOM_ACCESS_ITERATOR);
    assert(cpt_vector->_t_typesize == _GET_VECTOR_CONTAINER(t_iter)->_t_typesize &&
           strncmp(cpt_vector->_sz_typename, _GET_VECTOR_CONTAINER(t_iter)->_sz_typename,
                   _ELEM_TYPE_NAME_SIZE) == 0);
    assert(cpt_vector->_pfun_cmp == _GET_VECTOR_CONTAINER(t_iter)->_pfun_cmp);

    return true;
}

static bool_t _same_vector_type(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    assert(cpt_vectorfirst != NULL && cpt_vectorsecond != NULL);
    assert(cpt_vectorfirst->_pc_start != NULL &&
           cpt_vectorfirst->_pc_finish != NULL &&
           cpt_vectorfirst->_pc_endofstorage != NULL &&
           cpt_vectorsecond->_pc_start != NULL &&
           cpt_vectorsecond->_pc_finish != NULL &&
           cpt_vectorsecond->_pc_endofstorage != NULL);
    assert(cpt_vectorfirst->_t_typesize == cpt_vectorsecond->_t_typesize &&
           strncmp(cpt_vectorfirst->_sz_typename, cpt_vectorsecond->_sz_typename,
                   _ELEM_TYPE_NAME_SIZE) == 0);
    assert(cpt_vectorfirst->_pfun_cmp == cpt_vectorsecond->_pfun_cmp);

    return true;
}
#endif /* NDEBUG */

/** eof **/

