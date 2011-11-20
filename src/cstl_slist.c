/*
 *  The implementation of slist.
 *  Copyright (C)  2008,2009,2010,2011  Wangbo
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
#include <cstl/citerator.h>
#include <cstl/cfunctional.h>

#include <cstl/cstl_slist_iterator.h>
#include <cstl/cstl_slist_private.h>
#include <cstl/cstl_slist.h>

#include <cstl/cstring.h>

#include "cstl_slist_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/

/**
 * Initialize an empty slist container
 */
void slist_init(slist_t* pslist_slist)
{
    assert(pslist_slist != NULL);
    assert(_slist_is_created(pslist_slist));

    slist_init_n(pslist_slist, 0);
}

/**
 * Initialize slist container with specific size.
 */
void slist_init_n(slist_t* pslist_slist, size_t t_count)
{
    assert(pslist_slist != NULL);
    assert(_slist_is_created(pslist_slist));

    /* allocate memory for n_elemcount slist node */
    if(t_count > 0)
    {
        size_t        i = 0;
        _slistnode_t* pt_node = NULL;

        for(i = 0; i < t_count; ++i)
        {
            pt_node = _alloc_allocate(&pslist_slist->_t_allocator, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
            assert(pt_node != NULL);
            _slist_init_node_auxiliary(pslist_slist, pt_node);

            /* insert the new slist node after the head */
            pt_node->_pt_next = pslist_slist->_t_head._pt_next;
            pslist_slist->_t_head._pt_next = pt_node;
            pt_node = NULL;
        }
    }
}

/**
 * Initialize slist container with exist slist container.
 */
void slist_init_copy(slist_t* pslist_dest, const slist_t* cpslist_src)
{
    assert(pslist_dest != NULL);
    assert(cpslist_src != NULL);
    assert(_slist_is_created(pslist_dest));
    assert(_slist_is_inited(cpslist_src));
    assert(_slist_same_type(pslist_dest, cpslist_src));

    slist_init_copy_range(pslist_dest, slist_begin(cpslist_src), slist_end(cpslist_src));
}

/**
 * Initialize slist container with specific range.
 */
void slist_init_copy_range(slist_t* pslist_dest, slist_iterator_t it_begin, slist_iterator_t it_end)
{
    slist_iterator_t it_dest;
    slist_iterator_t it_src;
    bool_t           b_result = false;

    /* test the dest slist and [it_begin, it_end) is valid */
    assert(pslist_dest != NULL);
    assert(_slist_is_created(pslist_dest));
    assert(_slist_same_slist_iterator_type(pslist_dest, it_begin));
    assert(_slist_same_slist_iterator_type(pslist_dest, it_end));
    assert(iterator_equal(it_begin, it_end) || _slist_iterator_before(it_begin, it_end));

    /* initialize the dest slist use the iterator slist */
    slist_init_n(pslist_dest, iterator_distance(it_begin, it_end));
    /* copy the element from range [it_begin, it_end) to dest slist */
    for(it_dest = slist_begin(pslist_dest), it_src = it_begin;
        !iterator_equal(it_dest, slist_end(pslist_dest)) && !iterator_equal(it_src, it_end);
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        b_result = _GET_SLIST_TYPE_SIZE(pslist_dest);
        _GET_SLIST_TYPE_COPY_FUNCTION(pslist_dest)(
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_dest))->_pby_data,
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_src))->_pby_data, &b_result);
        assert(b_result);
    } 
    assert(iterator_equal(it_dest, slist_end(pslist_dest)) && iterator_equal(it_src, it_end));
}

/**
 * Destroy slist container.
 */
void slist_destroy(slist_t* pslist_slist)
{
    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist) || _slist_is_created(pslist_slist));

    _slist_destroy_auxiliary(pslist_slist);
    free(pslist_slist);
}

/**
 * Return a iterator to the first element in the slist container.
 */
slist_iterator_t slist_begin(const slist_t* cpslist_slist)
{
    slist_iterator_t it_begin;

    assert(cpslist_slist != NULL);
    assert(_slist_is_inited(cpslist_slist));

    it_begin = _create_slist_iterator();
    _ITERATOR_CONTAINER(it_begin) = (slist_t*)cpslist_slist;
    _SLIST_ITERATOR_COREPOS(it_begin) = (_byte_t*)(cpslist_slist->_t_head._pt_next);

    return it_begin;
}

/**
 * Return a iterator that points just beyond the end of slist container.
 */
slist_iterator_t slist_end(const slist_t* cpslist_slist)
{
    slist_iterator_t it_end;

    assert(cpslist_slist != NULL);
    assert(_slist_is_inited(cpslist_slist));

    it_end = _create_slist_iterator();
    _ITERATOR_CONTAINER(it_end) = (slist_t*)cpslist_slist;
    _SLIST_ITERATOR_COREPOS(it_end) = NULL;

    return it_end;
}

/**
 * Return the number of elements in a slist.
 */
size_t slist_size(const slist_t* cpslist_slist)
{
    _slistnode_t* pt_node = NULL;
    size_t        t_size = 0;

    assert(cpslist_slist != NULL);
    assert(_slist_is_inited(cpslist_slist));

    /* iterate all element and count the size */
    for(pt_node = cpslist_slist->_t_head._pt_next; pt_node != NULL; pt_node = pt_node->_pt_next)
    {
        t_size++;
    }

    return t_size;
}

/**
 * Tests if a slist is empty.
 */
bool_t slist_empty(const slist_t* cpslist_slist)
{
    assert(cpslist_slist != NULL);
    assert(_slist_is_inited(cpslist_slist));

    return cpslist_slist->_t_head._pt_next == NULL ? true : false;
}

/**
 * Return the maximum number of elements in a slist.
 */
size_t slist_max_size(const slist_t* cpslist_slist)
{
    assert(cpslist_slist != NULL);
    assert(_slist_is_inited(cpslist_slist));

    return (size_t)(-1) / _GET_SLIST_TYPE_SIZE(cpslist_slist);
}

/**
 * Assign slist element with an exist slist container.
 */
void slist_assign(slist_t* pslist_dest, const slist_t* cpslist_src)
{
    assert(pslist_dest != NULL);
    assert(cpslist_src != NULL);
    assert(_slist_is_inited(pslist_dest));
    assert(_slist_is_inited(cpslist_src));
    assert(_slist_same_type(pslist_dest, cpslist_src));

    if(slist_equal(pslist_dest, cpslist_src))
    {
        return;
    }

    slist_assign_range(pslist_dest, slist_begin(cpslist_src), slist_end(cpslist_src));
}

/**
 * Assign slist element with an exist slist container range.
 */
void slist_assign_range(slist_t* pslist_slist, slist_iterator_t it_begin, slist_iterator_t it_end)
{
    slist_iterator_t it_dest;
    slist_iterator_t it_src;
    bool_t           b_result = false;

    /* test the dest slist and [it_begin, it_end) is valid */
    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_same_slist_iterator_type(pslist_slist, it_begin));
    assert(_slist_same_slist_iterator_type(pslist_slist, it_end));
    /*assert(!_slist_iterator_belong_to_slist(pslist_slist, it_begin));*/
    /*assert(!_slist_iterator_belong_to_slist(pslist_slist, it_end));*/
    assert(iterator_equal(it_begin, it_end) || _slist_iterator_before(it_begin, it_end));

    slist_resize(pslist_slist, iterator_distance(it_begin, it_end));

    /* copy value from [it_begin, it_end) */
    for(it_dest = slist_begin(pslist_slist), it_src = it_begin;
        !iterator_equal(it_dest, slist_end(pslist_slist)) && !iterator_equal(it_src, it_end);
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
        _GET_SLIST_TYPE_COPY_FUNCTION(pslist_slist)(
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_dest))->_pby_data,
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_src))->_pby_data, &b_result);
        assert(b_result);
    }
}

/**
 * Swap slist datas.
 */
void slist_swap(slist_t* pslist_first, slist_t* pslist_second)
{
    slist_t slist_tmp;  /* for swap */

    assert(pslist_first != NULL);
    assert(pslist_second != NULL);
    assert(_slist_is_inited(pslist_first));
    assert(_slist_is_inited(pslist_second));
    assert(_slist_same_type(pslist_first, pslist_second));

    if(slist_equal(pslist_first, pslist_second))
    {
        return;
    }

    slist_tmp = *pslist_first;
    *pslist_first = *pslist_second;
    *pslist_second = slist_tmp;
}

/**
 * Access first slist data.
 */
void* slist_front(const slist_t* cpslist_slist)
{
    assert(cpslist_slist != NULL);
    assert(_slist_is_inited(cpslist_slist));
    assert(!slist_empty(cpslist_slist));

    /* char* */
    if(strncmp(_GET_SLIST_TYPE_BASENAME(cpslist_slist), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (char*)string_c_str((string_t*)cpslist_slist->_t_head._pt_next->_pby_data);
    }
    else
    {
        return cpslist_slist->_t_head._pt_next->_pby_data;
    }
}

/**
 * Delete the element at the begin of slist.
 */
void slist_pop_front(slist_t* pslist_slist)
{
    _slistnode_t* pt_node = NULL;
    bool_t        b_result = false;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(!slist_empty(pslist_slist));

    /* take out the front slist node */
    pt_node = pslist_slist->_t_head._pt_next;
    assert(pt_node != NULL);
    pslist_slist->_t_head._pt_next = pt_node->_pt_next;

    b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
    _GET_SLIST_TYPE_DESTROY_FUNCTION(pslist_slist)(pt_node->_pby_data, &b_result);
    assert(b_result);
    _alloc_deallocate(&pslist_slist->_t_allocator, pt_node, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
}

/**
 * Return a iterator that points position before current position.
 */
slist_iterator_t slist_previous(const slist_t* cpslist_slist, slist_iterator_t it_pos)
{
    slist_iterator_t it_prev;
    slist_iterator_t it_iter;

    /* test slist pointer and it_pos is valid */
    assert(cpslist_slist != NULL);
    assert(_slist_is_inited(cpslist_slist));
    assert(_slist_iterator_belong_to_slist(cpslist_slist, it_pos));
    assert(!iterator_equal(it_pos, slist_begin(cpslist_slist)));

    it_prev = slist_begin(cpslist_slist);
    it_iter = iterator_next(it_prev);
    while(!iterator_equal(it_iter, it_pos))
    {
        it_iter = iterator_next(it_iter);
        it_prev = iterator_next(it_prev);
    }

    return it_prev;
}

/**
 * Insert a range of elements into slist at a specificed position.
 */
void slist_insert_range(slist_t* pslist_slist, slist_iterator_t it_pos, slist_iterator_t it_begin, slist_iterator_t it_end)
{
    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_pos));
    /*assert(!_slist_iterator_belong_to_slist(pslist_slist, it_begin));*/
    /*assert(!_slist_iterator_belong_to_slist(pslist_slist, it_end));*/
    assert(_slist_same_slist_iterator_type(pslist_slist, it_begin));
    assert(_slist_same_slist_iterator_type(pslist_slist, it_end));
    assert(iterator_equal(it_begin, it_end) || _slist_iterator_before(it_begin, it_end));

    /* if pos is equal to slist begin iterator */
    if(iterator_equal(it_pos, slist_begin(pslist_slist)))
    {
        _slistnode_t*    pt_begin = NULL;
        _slistnode_t*    pt_end = NULL;
        _slistnode_t*    pt_node = NULL;
        slist_iterator_t it_iter;
        bool_t           b_result = false;

        for(it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter))
        {
            pt_node = _alloc_allocate(&pslist_slist->_t_allocator, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
            assert(pt_node != NULL);
            _slist_init_node_auxiliary(pslist_slist, pt_node);

            /* copy value form range [it_begin, it_end) */
            b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
            _GET_SLIST_TYPE_COPY_FUNCTION(pslist_slist)(
                pt_node->_pby_data, ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pby_data, &b_result);
            assert(b_result);

            /* make new node link */
            if(pt_begin == NULL)
            {
                assert(pt_end == NULL);
                pt_begin = pt_end = pt_node;
            }
            else
            {
                assert(pt_end != NULL);
                pt_end->_pt_next = pt_node;
                pt_end = pt_node;
            }
            pt_node = NULL;
        }

        /* insert the range into front pos */
        if(pt_begin != NULL && pt_end != NULL)
        {
            pt_end->_pt_next = pslist_slist->_t_head._pt_next;
            pslist_slist->_t_head._pt_next = pt_begin;
        }
    }
    else
    {
        /* call slist insert after range */
        slist_insert_after_range(pslist_slist, slist_previous(pslist_slist, it_pos), it_begin, it_end);
    }
}

/**
 * Insert a range of elements into slist at position following specific position.
 */
void slist_insert_after_range(
    slist_t* pslist_slist, slist_iterator_t it_pos, slist_iterator_t it_begin, slist_iterator_t it_end)
{
    _slistnode_t*    pt_begin = NULL;    /* the first node of duplicate list */
    _slistnode_t*    pt_end = NULL;      /* the last node of duplicate list */
    _slistnode_t*    pt_node = NULL;
    slist_iterator_t it_iter;
    bool_t           b_result = false;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_pos));
    assert(!iterator_equal(it_pos, slist_end(pslist_slist)));
    /*assert(!_slist_iterator_belong_to_slist(pslist_slist, it_begin));*/
    /*assert(!_slist_iterator_belong_to_slist(pslist_slist, it_end));*/
    assert(_slist_same_slist_iterator_type(pslist_slist, it_begin));
    assert(_slist_same_slist_iterator_type(pslist_slist, it_end));
    assert(iterator_equal(it_begin, it_end) || _slist_iterator_before(it_begin, it_end));

    /* allocate new elements and copy the element from range */
    for(it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter))
    {
        pt_node = _alloc_allocate(&pslist_slist->_t_allocator, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
        assert(pt_node != NULL);
        _slist_init_node_auxiliary(pslist_slist, pt_node);

        /* copy value from [it_begin, it_end) */
        b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
        _GET_SLIST_TYPE_COPY_FUNCTION(pslist_slist)(
            pt_node->_pby_data, ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pby_data, &b_result);
        assert(b_result);

        /* make new node link */
        if(pt_begin == NULL)
        {
            assert(pt_end == NULL);
            pt_begin = pt_end = pt_node;
        }
        else
        {
            assert(pt_end != NULL);
            pt_end->_pt_next = pt_node;
            pt_end = pt_node;
        }
        pt_node = NULL;
    }

    /* insert the range into the pos */
    if(pt_begin != NULL && pt_end != NULL)
    {
        pt_end->_pt_next = ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_pos))->_pt_next;
        ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_pos))->_pt_next = pt_begin;
    }
}

/**
 * Removes an element in slist after specificed position.
 */
slist_iterator_t slist_erase_after(slist_t* pslist_slist, slist_iterator_t it_pos)
{
    _slistnode_t* pt_node = NULL; /* for erase */
    bool_t        b_result = false;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_pos));
    assert(!iterator_equal(it_pos, slist_end(pslist_slist)));

    pt_node = ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_pos))->_pt_next;
    if(pt_node != NULL)
    {
        ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_pos))->_pt_next = pt_node->_pt_next;
        b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
        _GET_SLIST_TYPE_DESTROY_FUNCTION(pslist_slist)(pt_node->_pby_data, &b_result);
        assert(b_result);
        _alloc_deallocate(&pslist_slist->_t_allocator, pt_node, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);

        return iterator_next(it_pos);
    }
    else
    {
        return slist_end(pslist_slist);
    }
}

/**
 * Removes an element in slist from specificed position.
 */
slist_iterator_t slist_erase(slist_t* pslist_slist, slist_iterator_t it_pos)
{
    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_pos));
    assert(!iterator_equal(it_pos, slist_end(pslist_slist)));

    if(iterator_equal(it_pos, slist_begin(pslist_slist)))
    {
        slist_pop_front(pslist_slist);
        return slist_begin(pslist_slist);
    }
    else
    {
        return slist_erase_after(pslist_slist, slist_previous(pslist_slist, it_pos));
    }
}

/**
 * Removes a range of elements in slist from specificed position.
 */
slist_iterator_t slist_erase_range(slist_t* pslist_slist, slist_iterator_t it_begin, slist_iterator_t it_end)
{
    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_begin));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_end));
    assert(iterator_equal(it_begin, it_end) || _slist_iterator_before(it_begin, it_end));

    if(iterator_equal(it_begin, slist_begin(pslist_slist)))
    {
        size_t i = 0;
        size_t t_count = iterator_distance(it_begin, it_end);

        for(i = 0; i < t_count; ++i)
        {
            slist_pop_front(pslist_slist);
        }
        assert(iterator_equal(it_end, slist_begin(pslist_slist)));

        return it_end;
    }
    else
    {
        return slist_erase_after_range(pslist_slist, slist_previous(pslist_slist, it_begin), it_end);
    }
}

/**
 * Removes a range of elements in slist after specificed range.
 */
slist_iterator_t slist_erase_after_range(slist_t* pslist_slist, slist_iterator_t it_begin, slist_iterator_t it_end)
{
    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_begin));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_end));
    assert(iterator_equal(it_begin, it_end) || _slist_iterator_before(it_begin, it_end));
    assert(!iterator_equal(it_begin, slist_end(pslist_slist)));

    if(!iterator_equal(it_begin, it_end) && !iterator_equal(iterator_next(it_begin), it_end))
    {
        _slistnode_t*    pt_begin = NULL;
        _slistnode_t*    pt_end = NULL;
        _slistnode_t*    pt_node = NULL;
        slist_iterator_t it_endprev = slist_previous(pslist_slist, it_end);
        bool_t           b_result = false;

        /* take out the range [it_begin+1, it_end) */
        pt_begin = ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_begin))->_pt_next;
        pt_end = (_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_endprev);
        ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_begin))->_pt_next = pt_end->_pt_next;
        pt_end->_pt_next = NULL;
        /* destroy all elements and destroy all nodes */
        pt_node = pt_begin;
        while(pt_node != NULL)
        {
            pt_begin = pt_node->_pt_next;

            b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
            _GET_SLIST_TYPE_DESTROY_FUNCTION(pslist_slist)(pt_node->_pby_data, &b_result);
            assert(b_result);
            _alloc_deallocate(&pslist_slist->_t_allocator, pt_node, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);

            pt_node = pt_begin;
        }
    }

    return it_end;
}

/**
 * Removes elements from the source slist and insert into the target slist.
 */
void slist_splice(slist_t* pslist_slist, slist_iterator_t it_pos, slist_t* pslist_src)
{
    assert(pslist_slist != NULL);
    assert(pslist_src != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_is_inited(pslist_src));
    assert(_slist_same_type(pslist_slist, pslist_src));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_pos));

    if(pslist_slist != pslist_src)
    {
        _slist_transfer(it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    }
}

/**
 * Removes element from the source slist and insert into the target slist.
 */
void slist_splice_pos(slist_t* pslist_slist, slist_iterator_t it_pos, slist_t* pslist_src, slist_iterator_t it_src)
{
#ifdef NDEBUG
    slist_t* pslist_avoidwarning1 = NULL;
    slist_t* pslist_avoidwarning2 = NULL;
    pslist_avoidwarning1 = pslist_slist;
    pslist_avoidwarning2 = pslist_src;
#endif

    assert(pslist_slist != NULL);
    assert(pslist_src != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_is_inited(pslist_src));
    assert(_slist_same_type(pslist_slist, pslist_src));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_pos));
    assert(_slist_iterator_belong_to_slist(pslist_src, it_src));
    assert(!iterator_equal(it_src, slist_end(pslist_src)));

    _slist_transfer(it_pos, it_src, iterator_next(it_src));
}

/**
 * Removes elements from the source slist range and insert into the target slist.
 */
void slist_splice_range(
    slist_t* pslist_slist, slist_iterator_t it_pos, slist_t* pslist_src, slist_iterator_t it_begin, slist_iterator_t it_end)
{
#ifdef NDEBUG
    slist_t* pslist_avoidwarning1 = NULL;
    slist_t* pslist_avoidwarning2 = NULL;
    pslist_avoidwarning1 = pslist_slist;
    pslist_avoidwarning2 = pslist_src;
#endif

    assert(pslist_slist != NULL);
    assert(pslist_src != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_is_inited(pslist_src));
    assert(_slist_same_type(pslist_slist, pslist_src));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_pos));
    assert(_slist_iterator_belong_to_slist(pslist_src, it_begin));
    assert(_slist_iterator_belong_to_slist(pslist_src, it_end));
    assert(iterator_equal(it_begin, it_end) || _slist_iterator_before(it_begin, it_end));

    _slist_transfer(it_pos, it_begin, it_end);
}

/**
 * Removes element from the source slist and insert into the target slist.
 */
void slist_splice_after_pos(slist_t* pslist_slist, slist_iterator_t it_pos, slist_t* pslist_src, slist_iterator_t it_prev)
{
#ifdef NDEBUG
    slist_t* pslist_avoidwarning1 = NULL;
    slist_t* pslist_avoidwarning2 = NULL;
    pslist_avoidwarning1 = pslist_slist;
    pslist_avoidwarning2 = pslist_src;
#endif

    assert(pslist_slist != NULL);
    assert(pslist_src != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_is_inited(pslist_src));
    assert(_slist_same_type(pslist_slist, pslist_src));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_pos));
    assert(_slist_iterator_belong_to_slist(pslist_src, it_prev));
    assert(!iterator_equal(it_pos, slist_end(pslist_slist)));
    assert(!iterator_equal(it_prev, slist_end(pslist_src)));

    it_prev = iterator_next(it_prev);
    if(!iterator_equal(it_prev, slist_end(pslist_src)))
    {
        _slist_transfer_after(it_pos, it_prev, iterator_next(it_prev));
    }
}

/**
 * Removes elements from the source slist range and insert into the target slist.
 */
void slist_splice_after_range(
    slist_t* pslist_slist, slist_iterator_t it_pos, slist_t* pslist_src, slist_iterator_t it_begin, slist_iterator_t it_end)
{
#ifdef NDEBUG
    slist_t* pslist_avoidwarning1 = NULL;
    slist_t* pslist_avoidwarning2 = NULL;
    pslist_avoidwarning1 = pslist_slist;
    pslist_avoidwarning2 = pslist_src;
#endif

    assert(pslist_slist != NULL);
    assert(pslist_src != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_is_inited(pslist_src));
    assert(_slist_same_type(pslist_slist, pslist_src));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_pos));
    assert(_slist_iterator_belong_to_slist(pslist_src, it_begin));
    assert(_slist_iterator_belong_to_slist(pslist_src, it_end));
    assert(iterator_equal(it_begin, it_end) || _slist_iterator_before(it_begin, it_end));
    assert(!iterator_equal(it_pos, slist_end(pslist_slist)));
    assert(!iterator_equal(it_begin, slist_end(pslist_src)));
    assert(!iterator_equal(it_end, slist_end(pslist_src)));

    _slist_transfer_after(it_pos, iterator_next(it_begin), iterator_next(it_end));
}

/**
 * Remove elements from a slist for which a specificed predicate is satisfied.
 */
void slist_remove_if(slist_t* pslist_slist, unary_function_t ufun_op)
{
    slist_iterator_t it_pos;
    bool_t           b_result = false;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    if(ufun_op == NULL)
    {
        ufun_op = fun_default_unary;
    }

    it_pos = slist_begin(pslist_slist);
    while(!iterator_equal(it_pos, slist_end(pslist_slist)))
    {
        (*ufun_op)(iterator_get_pointer(it_pos), &b_result);
        if(b_result)
        {
            it_pos = slist_erase(pslist_slist, it_pos);
        }
        else
        {
            it_pos = iterator_next(it_pos);
        }
    }
}

/**
 * Removes adjacent duplicate elements from a slist.
 */
void slist_unique(slist_t* pslist_slist)
{
    slist_iterator_t it_iter;
    slist_iterator_t it_next;
    bool_t           b_less = false;
    bool_t           b_greater = false;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    if(slist_size(pslist_slist) > 1)
    {
        it_iter = slist_begin(pslist_slist);
        it_next = iterator_next(it_iter);
        while(!iterator_equal(it_next, slist_end(pslist_slist)))
        {
            b_less = b_greater = _GET_SLIST_TYPE_SIZE(pslist_slist);
            _GET_SLIST_TYPE_LESS_FUNCTION(pslist_slist)(
                ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pby_data,
                ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_next))->_pby_data, &b_less);
            _GET_SLIST_TYPE_LESS_FUNCTION(pslist_slist)(
                ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_next))->_pby_data,
                ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pby_data, &b_greater);
            if(b_less || b_greater)
            {
                it_iter = iterator_next(it_iter);
                it_next = iterator_next(it_next);
            }
            else
            {
                it_next = slist_erase(pslist_slist, it_next);
            }
        }
    }
}

/**
 * Removes adjacent elements that satisfy some other binary predicate from a slist.
 */
void slist_unique_if(slist_t* pslist_slist, binary_function_t bfun_op)
{
    slist_iterator_t it_iter;
    slist_iterator_t it_next;
    bool_t           b_result = false;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    if(bfun_op == NULL)
    {
        bfun_op = fun_default_binary;
    }

    if(slist_size(pslist_slist) > 1)
    {
        it_iter = slist_begin(pslist_slist);
        it_next = iterator_next(it_iter);

        while(!iterator_equal(it_next, slist_end(pslist_slist)))
        {
            (*bfun_op)(iterator_get_pointer(it_iter), iterator_get_pointer(it_next), &b_result);
            if(b_result)
            {
                it_next = slist_erase(pslist_slist, it_next);
            }
            else
            {
                it_iter = iterator_next(it_iter);
                it_next = iterator_next(it_next);
            }
        }
    }
}

/**
 * Reverse the order of all elements.
 */
void slist_reverse(slist_t* pslist_slist)
{
    slist_iterator_t it_iter;
    slist_iterator_t it_next;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    if(slist_size(pslist_slist) > 1)
    {
        it_iter = iterator_next(slist_begin(pslist_slist));

        while(!iterator_equal(it_iter, slist_end(pslist_slist)))
        {
            it_next = iterator_next(it_iter);
            _slist_transfer(slist_begin(pslist_slist), it_iter, it_next);
            it_iter = it_next;
        }
    }
}

/**
 * Sort elements of slist container.
 */
void slist_sort(slist_t* pslist_slist)
{
    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    slist_sort_if(pslist_slist, NULL);
}

/**
 * Sort elements of slist container with user-specifide order relation.
 */
void slist_sort_if(slist_t* pslist_slist, binary_function_t bfun_op)
{
    /* 
     * sort the slist use insert sort algorithm (O(N^2))instead of 
     * quick sort algorithm (O(NlogN)). because the quick sort need 
     * the previous iterator each step, so the efficiency in quick 
     * sort used in slist is more slow then O(NlogN).
     */

    slist_iterator_t it_pos;       /* iterating for insert */
    slist_iterator_t it_disorder;  /* the first pos of disorder element */
    slist_iterator_t it_insert;    /* the insert node */
    bool_t           b_result = false;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    if(bfun_op == NULL)
    {
        bfun_op = _GET_SLIST_TYPE_LESS_FUNCTION(pslist_slist);
        it_disorder = slist_begin(pslist_slist);
        while(!iterator_equal(it_disorder, slist_end(pslist_slist)))
        {
            for(it_pos = slist_begin(pslist_slist); !iterator_equal(it_pos, it_disorder); it_pos = iterator_next(it_pos))
            {
                (*bfun_op)(
                    ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_disorder))->_pby_data,
                    ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_pos))->_pby_data, &b_result);
                if(b_result)
                {
                    it_insert = it_disorder;
                    it_disorder = iterator_next(it_disorder);
                    _slist_transfer(it_pos, it_insert, it_disorder);
                    break;
                }
            }

            if(iterator_equal(it_pos, it_disorder))
            {
                it_disorder = iterator_next(it_disorder);
            }
        }
    }
    else
    {
        it_disorder = slist_begin(pslist_slist);
        while(!iterator_equal(it_disorder, slist_end(pslist_slist)))
        {
            for(it_pos = slist_begin(pslist_slist); !iterator_equal(it_pos, it_disorder); it_pos = iterator_next(it_pos))
            {
                (*bfun_op)(iterator_get_pointer(it_disorder), iterator_get_pointer(it_pos), &b_result);
                if(b_result)
                {
                    it_insert = it_disorder;
                    it_disorder = iterator_next(it_disorder);
                    _slist_transfer(it_pos, it_insert, it_disorder);
                    break;
                }
            }

            if(iterator_equal(it_pos, it_disorder))
            {
                it_disorder = iterator_next(it_disorder);
            }
        }
    }
}

/**
 * Merge two sorted slist.
 */
void slist_merge(slist_t* pslist_dest, slist_t* pslist_src)
{
    assert(pslist_dest != NULL);
    assert(pslist_src != NULL);
    assert(_slist_is_inited(pslist_dest));
    assert(_slist_is_inited(pslist_src));
    assert(_slist_same_type(pslist_dest, pslist_src));

    slist_merge_if(pslist_dest, pslist_src, NULL);
}

/**
 * Merge two sorted slist.
 */
void slist_merge_if(slist_t* pslist_dest, slist_t* pslist_src, binary_function_t bfun_op)
{
    slist_iterator_t it_dest;
    slist_iterator_t it_src;
    bool_t           b_result = false;

    assert(pslist_dest != NULL);
    assert(pslist_src != NULL);
    assert(_slist_is_inited(pslist_dest));
    assert(_slist_is_inited(pslist_src));
    assert(_slist_same_type(pslist_dest, pslist_src));

    /* same slist */
    if(pslist_dest == pslist_src)
    {
        return;
    }

    if(bfun_op == NULL)
    {
        bfun_op = _GET_SLIST_TYPE_LESS_FUNCTION(pslist_dest);
        it_dest = slist_begin(pslist_dest); 
        while(!iterator_equal(it_dest, slist_end(pslist_dest)) && !slist_empty(pslist_src))
        {
            it_src = slist_begin(pslist_src);
            (*bfun_op)(
                ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_src))->_pby_data,
                ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_dest))->_pby_data, &b_result);
            if(b_result)
            {
                _slist_transfer(it_dest, it_src, iterator_next(it_src));
            }
            else
            {
                it_dest = iterator_next(it_dest);
            }
        }
    }
    else
    {
        it_dest = slist_begin(pslist_dest); 
        while(!iterator_equal(it_dest, slist_end(pslist_dest)) && !slist_empty(pslist_src))
        {
            it_src = slist_begin(pslist_src);
            (*bfun_op)(iterator_get_pointer(it_src), iterator_get_pointer(it_dest), &b_result);
            if(b_result)
            {
                _slist_transfer(it_dest, it_src, iterator_next(it_src));
            }
            else
            {
                it_dest = iterator_next(it_dest);
            }
        }
    }

    /* if the src is not empty */
    it_src = slist_begin(pslist_src);
    if(!iterator_equal(it_src, slist_end(pslist_src)))
    {
        assert(iterator_equal(it_dest, slist_end(pslist_dest)));
        _slist_transfer(it_dest, it_src, slist_end(pslist_src));
    }
}

/**
 * Erases the elements of slist.
 */
void slist_clear(slist_t* pslist_slist)
{
    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    slist_erase_range(pslist_slist, slist_begin(pslist_slist), slist_end(pslist_slist));
}

/**
 * Specifies a new size of a slist.
 */
void slist_resize(slist_t* pslist_slist, size_t t_resize)
{
    slist_iterator_t it_pos;
    _slistnode_t*    pt_node = NULL;
    _slistnode_t*    pt_pos = NULL;
    size_t           i = 0;
    size_t           t_size = 0;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    t_size = slist_size(pslist_slist);
    if(t_resize <= t_size)
    {
        it_pos = iterator_advance(slist_begin(pslist_slist), t_resize);
        slist_erase_range(pslist_slist, it_pos, slist_end(pslist_slist));
    }
    else
    {
        if(!slist_empty(pslist_slist))
        {
            it_pos = slist_previous(pslist_slist, slist_end(pslist_slist));
            pt_pos = (_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_pos);
        }
        else
        {
            pt_pos = &pslist_slist->_t_head;
        }

        for(i = 0; i < t_resize - t_size; ++i)
        {
            pt_node = _alloc_allocate(&pslist_slist->_t_allocator, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
            assert(pt_node != NULL);
            _slist_init_node_auxiliary(pslist_slist, pt_node);

            pt_node->_pt_next = pt_pos->_pt_next;
            pt_pos->_pt_next = pt_node;
            pt_node = NULL;
        }
    }
}

/**
 * Tests if the two slists are equal.
 */
bool_t slist_equal(const slist_t* cpslist_first, const slist_t* cpslist_second)
{
    slist_iterator_t it_first;  /* iterator for first slist */
    slist_iterator_t it_second; /* iterator for second slist */
    bool_t           b_less = false;
    bool_t           b_greater = false;

    assert(cpslist_first != NULL);
    assert(cpslist_second != NULL);
    assert(_slist_is_inited(cpslist_first));
    assert(_slist_is_inited(cpslist_second));

    /* same slist */
    if(cpslist_first == cpslist_second)
    {
        return true;
    }

    /* test element type */
    if(!_slist_same_type(cpslist_first, cpslist_second))
    {
        return false;
    }

    /* test slist size */
    if(slist_size(cpslist_first) != slist_size(cpslist_second))
    {
        return false;
    }

    for(it_first = slist_begin(cpslist_first), it_second = slist_begin(cpslist_second);
        !iterator_equal(it_first, slist_end(cpslist_first)) && !iterator_equal(it_second, slist_end(cpslist_second));
        it_first = iterator_next(it_first), it_second = iterator_next(it_second))
    {
        b_less = b_greater = _GET_SLIST_TYPE_SIZE(cpslist_first);
        _GET_SLIST_TYPE_LESS_FUNCTION(cpslist_first)(
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_first))->_pby_data,
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_second))->_pby_data, &b_less);
        _GET_SLIST_TYPE_LESS_FUNCTION(cpslist_first)(
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_second))->_pby_data,
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_first))->_pby_data, &b_greater);
        if(b_less || b_greater)
        {
            return false;
        }
    }
    assert(iterator_equal(it_first, slist_end(cpslist_first)) && iterator_equal(it_second, slist_end(cpslist_second)));

    return true;
}

/**
 * Test the two slists are unequal.
 */
bool_t slist_not_equal(const slist_t* cpslist_first, const slist_t* cpslist_second)
{
    return !slist_equal(cpslist_first, cpslist_second);
}

/**
 * Test the first slist is less than the second slist.
 */
bool_t slist_less(const slist_t* cpslist_first, const slist_t* cpslist_second)
{
    slist_iterator_t it_first;  /* iterator for first slist */
    slist_iterator_t it_second; /* iterator for second slist */
    bool_t           b_result = false;

    assert(cpslist_first != NULL);
    assert(cpslist_second != NULL);
    assert(_slist_is_inited(cpslist_first));
    assert(_slist_is_inited(cpslist_second));
    assert(_slist_same_type(cpslist_first, cpslist_second));

    /* same slist */
    if(cpslist_first == cpslist_second)
    {
        return false;
    }

    for(it_first = slist_begin(cpslist_first), it_second = slist_begin(cpslist_second);
        !iterator_equal(it_first, slist_end(cpslist_first)) && !iterator_equal(it_second, slist_end(cpslist_second));
        it_first = iterator_next(it_first), it_second = iterator_next(it_second))
    {
        b_result = _GET_SLIST_TYPE_SIZE(cpslist_first);
        _GET_SLIST_TYPE_LESS_FUNCTION(cpslist_first)(
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_first))->_pby_data,
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_second))->_pby_data, &b_result);
        if(b_result)
        {
            return true;
        }

        b_result = _GET_SLIST_TYPE_SIZE(cpslist_first);
        _GET_SLIST_TYPE_LESS_FUNCTION(cpslist_first)(
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_second))->_pby_data,
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_first))->_pby_data, &b_result);
        if(b_result)
        {
            return false;
        }
    }

    return slist_size(cpslist_first) < slist_size(cpslist_second) ? true : false;
}

/**
 * Test the first slist is less than or equal to the second slist.
 */
bool_t slist_less_equal(const slist_t* cpslist_first, const slist_t* cpslist_second)
{
    return (slist_less(cpslist_first, cpslist_second) || slist_equal(cpslist_first, cpslist_second)) ? true : false;
}

/**
 * Test the first slist is greater than the second slist.
 */
bool_t slist_greater(const slist_t* cpslist_first, const slist_t* cpslist_second)
{
    return slist_less(cpslist_second, cpslist_first);
}

/**
 * Test the first slist is greater than or equal to the second slist.
 */
bool_t slist_greater_equal(const slist_t* cpslist_first, const slist_t* cpslist_second)
{
    return (slist_greater(cpslist_first, cpslist_second) || slist_equal(cpslist_first, cpslist_second)) ? true : false;
}

/** local function implementation section **/

/** eof **/

