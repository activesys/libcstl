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
#include <cstl/cstl_iterator.h>
#include <cstl/cstl_iterator_private.h>
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
        size_t       i = 0;
        slistnode_t* pt_node = NULL;

        for(i = 0; i < t_count; ++i)
        {
            pt_node = _alloc_allocate(&pslist_slist->_t_allocater, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
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
            ((slistnode_t*)_GET_SLIST_COREPOS(it_dest))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(it_src))->_pc_data, &b_result);
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
    _GET_CONTAINER(it_begin) = (slist_t*)cpslist_slist;
    _GET_SLIST_COREPOS(it_begin) = (char*)(cpslist_slist->_t_head._pt_next);

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
    _GET_CONTAINER(it_end) = (slist_t*)cpslist_slist;
    _GET_SLIST_COREPOS(it_end) = NULL;

    return it_end;
}

/**
 * Return the number of elements in a slist.
 */
size_t slist_size(const slist_t* cpslist_slist)
{
    slistnode_t* pt_node = NULL;
    size_t       t_size = 0;

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
            ((slistnode_t*)_GET_SLIST_COREPOS(it_dest))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(it_src))->_pc_data, &b_result);
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
        return (char*)string_c_str((string_t*)cpslist_slist->_t_head._pt_next->_pc_data);
    }
    else
    {
        return cpslist_slist->_t_head._pt_next->_pc_data;
    }
}


void slist_pop_front(slist_t* pt_slist)
{
    slistnode_t* pt_slistnode = NULL;
    bool_t       t_result = false;

    assert(pt_slist != NULL);
    assert(slist_size(pt_slist) > 0);

    /* take out the front slist node */
    pt_slistnode = pt_slist->_t_head._pt_next;
    assert(pt_slistnode != NULL);
    pt_slist->_t_head._pt_next = pt_slistnode->_pt_next;

    t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
    _GET_SLIST_TYPE_DESTROY_FUNCTION(pt_slist)(pt_slistnode->_pc_data, &t_result);
    assert(t_result);
    _alloc_deallocate(&pt_slist->_t_allocater, pt_slistnode, 
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
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
        slistnode_t*     pt_begin = NULL;
        slistnode_t*     pt_end = NULL;
        slistnode_t*     pt_node = NULL;
        slist_iterator_t it_iter;
        bool_t           b_result = false;

        for(it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter))
        {
            pt_node = _alloc_allocate(&pslist_slist->_t_allocater, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
            assert(pt_node != NULL);
            _slist_init_node_auxiliary(pslist_slist, pt_node);

            /* copy value form range [it_begin, it_end) */
            b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
            _GET_SLIST_TYPE_COPY_FUNCTION(pslist_slist)(
                pt_node->_pc_data, ((slistnode_t*)_GET_SLIST_COREPOS(it_iter))->_pc_data, &b_result);
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
    slistnode_t*     pt_begin = NULL;    /* the first node of duplicate list */
    slistnode_t*     pt_end = NULL;      /* the last node of duplicate list */
    slistnode_t*     pt_node = NULL;
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
        pt_node = _alloc_allocate(&pslist_slist->_t_allocater, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
        assert(pt_node != NULL);
        _slist_init_node_auxiliary(pslist_slist, pt_node);

        /* copy value from [it_begin, it_end) */
        b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
        _GET_SLIST_TYPE_COPY_FUNCTION(pslist_slist)(
            pt_node->_pc_data, ((slistnode_t*)_GET_SLIST_COREPOS(it_iter))->_pc_data, &b_result);
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
        pt_end->_pt_next = ((slistnode_t*)_GET_SLIST_COREPOS(it_pos))->_pt_next;
        ((slistnode_t*)_GET_SLIST_COREPOS(it_pos))->_pt_next = pt_begin;
    }
}

slist_iterator_t slist_erase_after(slist_t* pt_slist, slist_iterator_t t_pos)
{
    slistnode_t* pt_slistnode = NULL; /* for erase */
    bool_t       t_result = false;

    /* test the slist pointer and the pos is valid */
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(!iterator_equal(t_pos, slist_end(pt_slist)));

    /* get the next iterator */
    /* test the pos is valid */
    pt_slistnode = ((slistnode_t*)_GET_SLIST_COREPOS(t_pos))->_pt_next;
    /* t_pos is the last element(not end iterator) */
    if(pt_slistnode != NULL)
    {
        /* take out the element node */
        ((slistnode_t*)_GET_SLIST_COREPOS(t_pos))->_pt_next = pt_slistnode->_pt_next;
        /* destroy the element and destroy the node */
        t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
        _GET_SLIST_TYPE_DESTROY_FUNCTION(pt_slist)(pt_slistnode->_pc_data, &t_result);
        assert(t_result);
        _alloc_deallocate(&pt_slist->_t_allocater, pt_slistnode, 
            _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);

        t_pos = iterator_next(t_pos);
        return t_pos;
    }
    else
    {
        return slist_end(pt_slist);
    }
}

slist_iterator_t slist_erase(slist_t* pt_slist, slist_iterator_t t_pos)
{
    /* if the pos is the begin iterator of slist */
    if(iterator_equal(t_pos, slist_begin(pt_slist)))
    {
        /* call the pop front */
        slist_pop_front(pt_slist);
        return slist_begin(pt_slist);
    }
    /* else get the previous iterator */
    else
    {
        /* call erase after */
        return slist_erase_after(pt_slist, slist_previous(pt_slist, t_pos));
    }
}

slist_iterator_t slist_erase_range(
    slist_t* pt_slist, slist_iterator_t t_begin, slist_iterator_t t_end)
{
    /* test the pointer and range is valid */
    assert(_slist_iterator_belong_to_slist(pt_slist, t_begin));
    assert(iterator_equal(t_begin, t_end) || _slist_iterator_before(t_begin, t_end));

    /* if the t_begin is equal begin iterator */
    if(iterator_equal(t_begin, slist_begin(pt_slist)))
    {
        size_t t_index = 0;
        size_t t_count = iterator_distance(t_begin, t_end);

        /* call pop front n_elemcount times */
        for(t_index = 0; t_index < t_count; ++t_index)
        {
            slist_pop_front(pt_slist);
        }
        assert(iterator_equal(t_end, slist_begin(pt_slist)));

        return t_end;
    }
    /* else get the previous */
    else
    {
        /* call erase after range */
        return slist_erase_after_range(
            pt_slist, slist_previous(pt_slist, t_begin), t_end);
    }
}

slist_iterator_t slist_erase_after_range(
    slist_t* pt_slist, slist_iterator_t t_begin, slist_iterator_t t_end)
{
    /* test the range t_begin, t_end is valid */
    assert(_slist_iterator_belong_to_slist(pt_slist, t_begin));
    assert(iterator_equal(t_begin, t_end) || _slist_iterator_before(t_begin, t_end));

    if(!iterator_equal(t_begin, t_end) &&
       ((slistnode_t*)_GET_SLIST_COREPOS(t_begin))->_pt_next !=
       ((slistnode_t*)_GET_SLIST_COREPOS(t_end)))
    {
        slistnode_t*     pt_begin = NULL;
        slistnode_t*     pt_end = NULL;
        slistnode_t*     pt_iter = NULL;
        slist_iterator_t t_endprevious = slist_previous(pt_slist, t_end);
        bool_t           t_result = false;

        /* take out the range [t_begin+1, t_end) */
        pt_begin = ((slistnode_t*)_GET_SLIST_COREPOS(t_begin))->_pt_next;
        pt_end = (slistnode_t*)_GET_SLIST_COREPOS(t_endprevious);
        ((slistnode_t*)_GET_SLIST_COREPOS(t_begin))->_pt_next = pt_end->_pt_next;
        pt_end->_pt_next = NULL;
        /* destroy all elements and destroy all nodes */
        pt_iter = pt_begin;
        while(pt_iter != NULL)
        {
            pt_begin = pt_iter->_pt_next;
            t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
            _GET_SLIST_TYPE_DESTROY_FUNCTION(pt_slist)(pt_iter->_pc_data, &t_result);
            assert(t_result);
            _alloc_deallocate(&pt_slist->_t_allocater, pt_iter,
                _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);

            pt_iter = pt_begin;
        }
    }

    return t_end;
}

void slist_splice(
    slist_t* pt_slist, slist_iterator_t t_pos, slist_t* pt_slistsrc)
{
#ifdef NDEBUG
    slist_t* pt_avoidwarning = NULL;
    pt_avoidwarning = pt_slist;
#endif

    assert(_slist_same_type(pt_slist, pt_slistsrc));
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(pt_slist != pt_slistsrc);

    if(!slist_empty(pt_slistsrc))
    {
        _slist_transfer(t_pos, slist_begin(pt_slistsrc), slist_end(pt_slistsrc));
    }
}

void slist_splice_pos(
    slist_t* pt_slist, slist_iterator_t t_pos,
    slist_t* pt_slistsrc, slist_iterator_t t_possrc)
{
    slist_iterator_t t_possrcnext;

#ifdef NDEBUG
    slist_t* pt_avoidwarning = NULL;
    pt_avoidwarning = pt_slist;
#endif

    assert(_slist_same_type(pt_slist, pt_slistsrc));
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(_slist_iterator_belong_to_slist(pt_slistsrc, t_possrc));
    assert(pt_slist != pt_slistsrc);

    t_possrcnext = t_possrc;
    t_possrcnext = iterator_next(t_possrcnext);
    if(!slist_empty(pt_slistsrc) &&
       !iterator_equal(t_possrc, slist_end(pt_slistsrc)))
    {
        _slist_transfer(t_pos, t_possrc, t_possrcnext);
    }
}

void slist_splice_range(
    slist_t* pt_slist, slist_iterator_t t_pos,
    slist_t* pt_slistsrc, slist_iterator_t t_begin, slist_iterator_t t_end)
{
#ifdef NDEBUG
    slist_t* pt_avoidwarning1 = NULL;
    slist_t* pt_avoidwarning2 = NULL;
    pt_avoidwarning1 = pt_slist;
    pt_avoidwarning2 = pt_slistsrc;
#endif

    assert(_slist_same_type(pt_slist, pt_slistsrc));
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(_slist_iterator_belong_to_slist(pt_slistsrc, t_begin));
    assert(iterator_equal(t_begin, t_end) || _slist_iterator_before(t_begin, t_end));
    assert(pt_slist != pt_slistsrc);

    _slist_transfer(t_pos, t_begin, t_end);
}

void slist_splice_after_pos(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_t* pt_slistsrc, slist_iterator_t t_prev)
{
    slist_iterator_t t_prevnext;

#ifdef NDEBUG
    slist_t* pt_avoidwarning1 = NULL;
    slist_t* pt_avoidwarning2 = NULL;
    pt_avoidwarning1 = pt_slist;
    pt_avoidwarning2 = pt_slistsrc;
#endif

    assert(_slist_same_type(pt_slist, pt_slistsrc));
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(_slist_iterator_belong_to_slist(pt_slistsrc, t_prev));
    assert(pt_slist != pt_slistsrc);

    t_prev = iterator_next(t_prev);
    t_prevnext = t_prev;
    t_prevnext = iterator_next(t_prevnext);
    _slist_transfer_after(t_pos, t_prev, t_prevnext);
}

void slist_splice_after_range(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_t* pt_slistsrc, slist_iterator_t t_beforefirst, slist_iterator_t t_beforelast)
{
#ifdef NDEBUG
    slist_t* pt_avoidwarning1 = NULL;
    slist_t* pt_avoidwarning2 = NULL;
    pt_avoidwarning1 = pt_slist;
    pt_avoidwarning2 = pt_slistsrc;
#endif

    assert(_slist_same_type(pt_slist, pt_slistsrc));
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(_slist_iterator_belong_to_slist(pt_slistsrc, t_beforefirst));
    assert(iterator_equal(t_beforefirst, t_beforelast) || 
           _slist_iterator_before(t_beforefirst, t_beforelast));
    assert(pt_slist != pt_slistsrc);

    t_beforefirst = iterator_next(t_beforefirst);
    t_beforelast = iterator_next(t_beforelast);
    _slist_transfer_after(t_pos, t_beforefirst, t_beforelast);
}


void slist_remove_if(slist_t* pt_slist, unary_function_t t_unary_op)
{
    slist_iterator_t t_pos;
    bool_t           t_result = false;

    assert(pt_slist != NULL);

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    t_pos = slist_begin(pt_slist);
    /* iterate the slist from begin to end */
    while(!iterator_equal(t_pos, slist_end(pt_slist)))
    {
        /* operate each element use pufn_op, if it yield true */
        (*t_unary_op)(iterator_get_pointer(t_pos), &t_result);
        if(t_result)
        {
            /* erase element */
            t_pos = slist_erase(pt_slist, t_pos);
        }
        else
        {
            t_pos = iterator_next(t_pos);
        }
    }
}

void slist_unique(slist_t* pt_slist)
{
    slist_iterator_t t_poscur;
    slist_iterator_t t_posnext;
    bool_t           t_less = false;
    bool_t           t_greater = false;

    /* test the slist is valid */
    assert(pt_slist != NULL);

    /* if the size greater then 1 */
    if(slist_size(pt_slist) > 1)
    {
        t_poscur = slist_begin(pt_slist);
        t_posnext = iterator_next(t_poscur);
        while(!iterator_equal(t_posnext, slist_end(pt_slist)))
        {
            t_less = t_greater = _GET_SLIST_TYPE_SIZE(pt_slist);
            _GET_SLIST_TYPE_LESS_FUNCTION(pt_slist)(
                ((slistnode_t*)_GET_SLIST_COREPOS(t_poscur))->_pc_data,
                ((slistnode_t*)_GET_SLIST_COREPOS(t_posnext))->_pc_data, &t_less);
            _GET_SLIST_TYPE_LESS_FUNCTION(pt_slist)(
                ((slistnode_t*)_GET_SLIST_COREPOS(t_posnext))->_pc_data,
                ((slistnode_t*)_GET_SLIST_COREPOS(t_poscur))->_pc_data, &t_greater);
            if(t_less || t_greater)
            {
                t_poscur = iterator_next(t_poscur);
                t_posnext = iterator_next(t_posnext);
            }
            else
            {
                /* then erase next */
                t_posnext = slist_erase(pt_slist, t_posnext);
            }
        }
    }
}

void slist_unique_if(slist_t* pt_slist, binary_function_t t_binary_op)
{
    slist_iterator_t t_poscur;
    slist_iterator_t t_posnext;
    bool_t           t_result = false;

    assert(pt_slist != NULL);

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    if(slist_size(pt_slist) > 1)
    {
        t_poscur = slist_begin(pt_slist);
        t_posnext = iterator_next(t_poscur);

        while(!iterator_equal(t_posnext, slist_end(pt_slist)))
        {
            (*t_binary_op)(iterator_get_pointer(t_poscur),
                iterator_get_pointer(t_posnext), &t_result);
            if(t_result)
            {
                t_posnext = slist_erase(pt_slist, t_posnext);
            }
            else
            {
                t_poscur = iterator_next(t_poscur);
                t_posnext = iterator_next(t_posnext);
            }
        }
    }
}

void slist_reverse(slist_t* pt_slist)
{
    slist_iterator_t t_poscur;
    slist_iterator_t t_posnext;

    assert(pt_slist != NULL);

    if(slist_size(pt_slist) > 1)
    {
        t_poscur = slist_begin(pt_slist);
        t_poscur = iterator_next(t_poscur);

        while(!iterator_equal(t_poscur, slist_end(pt_slist)))
        {
            t_posnext = iterator_next(t_poscur);
            _slist_transfer(slist_begin(pt_slist), t_poscur, t_posnext);
            t_poscur = t_posnext;
        }
    }
}

void slist_sort(slist_t* pt_slist)
{
    /* 
     * sort the slist use insert sort algorithm (O(N^2))instead of 
     * quick sort algorithm (O(NlogN)). because the quick sort need 
     * the previous iterator each step, so the efficiency in quick 
     * sort used in slist is more slow then O(NlogN).
     */

    slist_iterator_t t_pos;       /* iterating for insert */
    slist_iterator_t t_disorder;  /* the first pos of disorder element */
    slist_iterator_t t_insert;    /* the insert node */
    bool_t           t_result = false;

    assert(pt_slist != NULL);

    t_disorder = slist_begin(pt_slist);
    while(!iterator_equal(t_disorder, slist_end(pt_slist)))
    {
        for(t_pos = slist_begin(pt_slist);
            !iterator_equal(t_pos, t_disorder);
            t_pos = iterator_next(t_pos))
        {
            t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
            _GET_SLIST_TYPE_LESS_FUNCTION(pt_slist)(
                ((slistnode_t*)_GET_SLIST_COREPOS(t_disorder))->_pc_data,
                ((slistnode_t*)_GET_SLIST_COREPOS(t_pos))->_pc_data, &t_result);
            if(t_result)
            {
                t_insert = t_disorder;
                t_disorder = iterator_next(t_disorder);
                _slist_transfer(t_pos, t_insert, t_disorder);
                break;
            }
        }

        if(iterator_equal(t_pos, t_disorder))
        {
            t_disorder = iterator_next(t_disorder);
        }
    }
}

void slist_sort_if(slist_t* pt_slist, binary_function_t t_binary_op)
{
    slist_iterator_t t_pos;       /* iterating for insert */
    slist_iterator_t t_disorder;  /* the first pos of disorder element */
    slist_iterator_t t_insert;    /* the insert node */
    bool_t           t_result = false;

    assert(pt_slist != NULL);

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    t_disorder = slist_begin(pt_slist);
    while(!iterator_equal(t_disorder, slist_end(pt_slist)))
    {
        for(t_pos = slist_begin(pt_slist);
            !iterator_equal(t_pos, t_disorder);
            t_pos = iterator_next(t_pos))
        {
            (*t_binary_op)(iterator_get_pointer(t_disorder),
                iterator_get_pointer(t_pos), &t_result);
            if(t_result)
            {
                t_insert = t_disorder;
                t_disorder = iterator_next(t_disorder);
                _slist_transfer(t_pos, t_insert, t_disorder);
                break;
            }
        }

        if(iterator_equal(t_pos, t_disorder))
        {
            t_disorder = iterator_next(t_disorder);
        }
    }
}

void slist_merge(slist_t* pt_slistdest, slist_t* pt_slistsrc)
{
    slist_iterator_t t_dest;
    slist_iterator_t t_src;
    slist_iterator_t t_srcnext;
    bool_t           t_result = false;

    /* test the dest and src slist is valid */
    assert(_slist_same_type(pt_slistdest, pt_slistsrc));

    /* iterate dest and src slist */
    t_dest = slist_begin(pt_slistdest); 
    while(!iterator_equal(t_dest, slist_end(pt_slistdest)) && !slist_empty(pt_slistsrc))
    {
        t_src = slist_begin(pt_slistsrc);
        t_result = _GET_SLIST_TYPE_SIZE(pt_slistdest);
        _GET_SLIST_TYPE_LESS_FUNCTION(pt_slistdest)(
            ((slistnode_t*)_GET_SLIST_COREPOS(t_src))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(t_dest))->_pc_data, &t_result);
        if(t_result)
        {
            /* transfer the element fromt src to dest */
            t_srcnext = t_src;
            t_srcnext = iterator_next(t_srcnext);
            _slist_transfer(t_dest, t_src, t_srcnext);
        }
        else
        {
            t_dest = iterator_next(t_dest);
        }
    }
    
    /* if the src is not ended */
    t_src = slist_begin(pt_slistsrc);
    if(!iterator_equal(t_src, slist_end(pt_slistsrc)))
    {
        assert(iterator_equal(t_dest, slist_end(pt_slistdest)));
        /* transfer the remain elements in src slist to dest */
        _slist_transfer(t_dest, t_src, slist_end(pt_slistsrc));
    }
}

void slist_merge_if(
    slist_t* pt_slistdest, slist_t* pt_slistsrc, 
    binary_function_t t_binary_op)
{
    slist_iterator_t t_dest;
    slist_iterator_t t_src;
    slist_iterator_t t_srcnext;
    bool_t           t_result = false;

    assert(_slist_same_type(pt_slistdest, pt_slistsrc));

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    /* iterate dest and src slist */
    t_dest = slist_begin(pt_slistdest); 
    while(!iterator_equal(t_dest, slist_end(pt_slistdest)) && !slist_empty(pt_slistsrc))
    {
        t_src = slist_begin(pt_slistsrc);
        /* if src slist less then dest */
        (*t_binary_op)(iterator_get_pointer(t_src),
            iterator_get_pointer(t_dest), &t_result);
        if(t_result)
        {
            /* transfer the element fromt src to dest */
            t_srcnext = t_src;
            t_srcnext = iterator_next(t_srcnext);
            _slist_transfer(t_dest, t_src, t_srcnext);
        }
        else
        {
            t_dest = iterator_next(t_dest);
        }
    }

    /* if the src is not ended */
    t_src = slist_begin(pt_slistsrc);
    if(!iterator_equal(t_src, slist_end(pt_slistsrc)))
    {
        assert(iterator_equal(t_dest, slist_end(pt_slistdest)));
        /* transfer the remain elements in src slist to dest */
        _slist_transfer(t_dest, t_src, slist_end(pt_slistsrc));
    }
}

void slist_clear(slist_t* pt_slist)
{
    slist_erase_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
}


void slist_resize(slist_t* pt_slist, size_t t_resize)
{
    slist_iterator_t t_pos;
    size_t           t_index = 0;

    assert(pt_slist != NULL);

    for(t_index = 0, t_pos = slist_begin(pt_slist);
        t_index < t_resize && !iterator_equal(t_pos, slist_end(pt_slist));
        ++t_index, t_pos = iterator_next(t_pos))
    {
        continue;
    }

    if(t_index == t_resize)
    {
        if(!iterator_equal(t_pos, slist_end(pt_slist)))
        {
            slist_erase_range(pt_slist, t_pos, slist_end(pt_slist));
        }
    }
    else
    {
        slist_iterator_t t_slistlast;
        slistnode_t*     pt_slistnode = NULL;
        size_t           t_slistsize = slist_size(pt_slist);

        if(!slist_empty(pt_slist))
        {
            t_slistlast = slist_previous(pt_slist, slist_end(pt_slist));
        }
        else
        {
            _GET_SLIST_COREPOS(t_slistlast) = (char*)&pt_slist->_t_head;
        }

        for(t_index = 0; t_index < t_resize - t_slistsize; ++t_index)
        {
            pt_slistnode = _alloc_allocate(&pt_slist->_t_allocater,
                _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
            assert(pt_slistnode != NULL);
            _slist_init_node_auxiliary(pt_slist, pt_slistnode);

            pt_slistnode->_pt_next = ((slistnode_t*)_GET_SLIST_COREPOS(t_slistlast))->_pt_next;
            ((slistnode_t*)_GET_SLIST_COREPOS(t_slistlast))->_pt_next = pt_slistnode;
            pt_slistnode = NULL;
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
            ((slistnode_t*)_GET_SLIST_COREPOS(it_first))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(it_second))->_pc_data, &b_less);
        _GET_SLIST_TYPE_LESS_FUNCTION(cpslist_first)(
            ((slistnode_t*)_GET_SLIST_COREPOS(it_second))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(it_first))->_pc_data, &b_greater);
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
            ((slistnode_t*)_GET_SLIST_COREPOS(it_first))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(it_second))->_pc_data, &b_result);
        if(b_result)
        {
            return true;
        }

        b_result = _GET_SLIST_TYPE_SIZE(cpslist_first);
        _GET_SLIST_TYPE_LESS_FUNCTION(cpslist_first)(
            ((slistnode_t*)_GET_SLIST_COREPOS(it_second))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(it_first))->_pc_data, &b_result);
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

