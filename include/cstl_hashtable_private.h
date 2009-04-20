/*
 *  The private interface of hashtable.
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

#ifndef _CSTL_HASHTABLE_PRIVATE_H
#define _CSTL_HASHTABLE_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _taghashnode
{
    struct _taghashnode* _pt_next;
    char                 _pc_data[1];
}hashnode_t;

typedef struct _taghashtable
{
    /* element identify */
    size_t          _t_typesize;                          /* element size */
    char            _sz_typename[_ELEM_TYPE_NAME_SIZE+1]; /* element name */

    /* memory allocate */
    alloc_t         _t_allocater;

    /* buckets and node */
    vector_t        _t_bucket;
    size_t          _t_nodecount;

    /* 
     * the hash function:
     * parameter 1: element pointer.
     * parameter 2: element type size.
     * parameter 3: bucket count.
     */
    int (*_pfun_hash)(const void*, size_t, size_t);
    /* 
     * the equal function
     */
    int (*_pfun_cmp)(const void*, const void*);
    /* the element destroy function */
    void (*_pfun_destroy_elem)(void*);
}hashtable_t;

/* for the result of equal_range and insert_unique function */
typedef struct _taghashtableresultpair
{
    hashtable_iterator_t _t_first;
    union
    {
        hashtable_iterator_t _t_iterator; /* for equal_range */
        bool_t              _t_bool;     /* for insert_unique */
    }_t_second;
}hashtable_result_pair_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_hashtable
 *        Parameters: in) t_typesize: size_t
 *                          the element type size.
 *                    in) s_typename: const char*
 *                          the element type name.
 *           Returns: hashtable_t
 *                          new hashtable.
 *       Description: create the new hashtable.
 *
 * ----------------------------------------------------------------------------
 */
extern hashtable_t _create_hashtable(size_t t_typesize, const char* s_typename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_init
 *        Parameters: in) pt_hashtable: hashtable_t*
 *                    in) t_bucketcount: size_t
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *                          the hash function.
 *                    in) pfun_cmp: int (*pfun)(const void*, const void*)
 *                          the function for element compare:
 *                          < 0  : element first < element second.
 *                          == 0 : element first == element second.
 *                          > 0  : element first > element second. 
 *                    in) pfun_destroy_elem: void (*pfun)(void*)
 *                          the destroy element function.
 *           Returns: void
 *       Description: initialize the hashtable.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hashtable_init(
    hashtable_t* pt_hashtable,
    size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t),
    int (*pfun_cmp)(const void*, const void*),
    void (*pfun_destroy_elem)(void*));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_destroy
 *        Parameters: in) pt_hashtable: hashtable_t*
 *           Returns: void
 *       Description: destroy the hashtable.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hashtable_destroy(hashtable_t* pt_hashtable);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_init_copy
 *        Parameters: in) pt_hashtabledest: hashtable_t*
 *                        the dest hashtable pointer.
 *                    in) cpt_hashtablesrc: hashtable_t*
 *                        the source hashtable pointer.
 *           Returns: void
 *       Description: copy the hashtable_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hashtable_init_copy(
    hashtable_t* pt_hashtabledest, const hashtable_t* cpt_hashtablesrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_init_copy_range
 *        Parameters: in) pt_hashtabledest: hashtable_t*
 *                        the dest hashtable pointer.
 *                    in) t_begin: hashtable_iterator_t
 *                        range begin.
 *                    in) t_end: hashtable_iterator_t
 *                        range end.
 *                    in) t_bucketcount: size_t
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *                    in) pfun_cmp: int (*)(const void*, const void*)
 *           Returns: void
 *       Description: copy the hashtable_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hashtable_init_copy_range(
    hashtable_t* pt_hashtabledest,
    hashtable_iterator_t t_begin,
    hashtable_iterator_t t_end,
    size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t),
    int (*pfun_cmp)(const void*, const void*));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_assign
 *        Parameters: in) pt_hashtabledest: hashtable_t*
 *                        the dest avl tree pointer.
 *                    in) cpt_hashtablesrc: const hashtable_t*
 *                        the src avl tree pointer.
 *           Returns: void
 *       Description: assign the hashtable_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hashtable_assign(
    hashtable_t* pt_hashtabledest, const hashtable_t* cpt_hashtablesrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_size
 *        Parameters: in) cpt_hashtable: const hashtable_t*
 *                          the dest hashtable.
 *           Returns: size_t
 *       Description: get the hashtable size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _hashtable_size(const hashtable_t* cpt_hashtable);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_empty
 *        Parameters: in) cpt_hashtable: const hashtable_t*
 *                          the dest hashtable.
 *           Returns: bool_t
 *       Description: if the hashtable is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _hashtable_empty(const hashtable_t* cpt_hashtable);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_max_size
 *        Parameters: in) cpt_hashtable: const hashtable_t*
 *                          the dest hashtable.
 *           Returns: size_t
 *       Description: get the maximum capacity of hashtable.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _hashtable_max_size(const hashtable_t* cpt_hashtable);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_bucket_count
 *        Parameters: in) cpt_hashtable: const hashtable_t*
 *                          the dest hashtable.
 *           Returns: size_t
 *       Description: get the bucket count of hast table.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _hashtable_bucket_count(const hashtable_t* cpt_hashtable);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_begin
 *        Parameters: in) cpt_hashtable: const hashtable_t*
 *                          the hashtable.
 *           Returns: hashtable_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern hashtable_iterator_t _hashtable_begin(const hashtable_t* cpt_hashtable);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_end
 *        Parameters: in) cpt_hashtable: const hashtable_t*
 *                          the hashtable.
 *           Returns: hashtable_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern hashtable_iterator_t _hashtable_end(const hashtable_t* cpt_hashtable);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_clear
 *        Parameters: in) pt_hashtable: hashtable_t*
 *                          the hashtable.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hashtable_clear(hashtable_t* pt_hashtable);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_hash_func
 *        Parameters: in) cpt_hashtable: const hashtable_t*
 *                          the hashtable.
 *           Returns: int (*)(const void*, size_t, size_t);
 *       Description: return the hash function.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*_hashtable_hash_func(const hashtable_t* cpt_hashtable))(
    const void*, size_t, size_t);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_key_comp
 *        Parameters: in) cpt_hashtable: const hashtable_t*
 *                          the hashtable.
 *           Returns: int (*)(const void*, const void*);
 *       Description: return the compare function.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*_hashtable_key_comp(const hashtable_t* cpt_hashtable))(
    const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_equal
 *        Parameters: in) cpt_hashtablefirst: const hashtable_t*
 *                          the first hashtable.
 *                    in) cpt_hashtablesecond: const hashtable_t*
 *                          the second hashtable.
 *           Returns: bool_t
 *       Description: return whether first hashtable equal to second hashtable.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _hashtable_equal(
    const hashtable_t* cpt_hashtablefirst, 
    const hashtable_t* cpt_hashtablesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_not_equal
 *        Parameters: in) cpt_hashtablefirst: const hashtable_t*
 *                          the first hashtable.
 *                    in) cpt_hashtablesecond: const hashtable_t*
 *                          the second hashtable.
 *           Returns: bool_t
 *       Description: return whether first hashtable not equal to second hashtable.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _hashtable_not_equal(
    const hashtable_t* cpt_hashtablefirst, 
    const hashtable_t* cpt_hashtablesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_resize
 *        Parameters: in) pt_hashtable: hashtable_t*
 *                          the _hashtable.
 *                    in) t_resize: size_t
 *                          the new size of _hashtable.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default 0.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hashtable_resize(hashtable_t* pt_hashtable, size_t t_resize);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_insert_unique
 *        Parameters: in) pt_hashtable: hashtable_t*
 *                        the avl tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: hashtable_iterator_t
 *                        the target iterator or end iterator.
 *       Description: insert unique value into avl tree.
 *
 * ----------------------------------------------------------------------------
 */
extern hashtable_result_pair_t _hashtable_insert_unique(
    hashtable_t* pt_hashtable, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_insert_equal
 *        Parameters: in) pt_hashtable: hashtable_t*
 *                        the avl tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: hashtable_iterator_t
 *                        the target iterator or end iterator.
 *       Description: insert equal value into avl tree.
 *
 * ----------------------------------------------------------------------------
 */
extern hashtable_iterator_t _hashtable_insert_equal(
    hashtable_t* pt_hashtable, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_insert_unique_range
 *        Parameters: in) pt_hashtable: hashtable_t*
 *                        the avl tree pointer.
 *                    in) t_begin: hashtable_iterator_t
 *                        the begin iterator
 *                    in0 t_end: hashtable_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: insert a range into the val tree.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hashtable_insert_unique_range(
    hashtable_t* pt_hashtable, 
    hashtable_iterator_t t_begin, 
    hashtable_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_insert_equal_range
 *        Parameters: in) pt_hashtable: hashtable_t*
 *                        the avl tree pointer.
 *                    in) t_begin: hashtable_iterator_t
 *                        the begin iterator.
 *                    in) t_end: hashtable_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: insert a range into avl tree.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hashtable_insert_equal_range(
    hashtable_t* pt_hashtable, 
    hashtable_iterator_t t_begin,
    hashtable_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_find
 *        Parameters: in) cpt_hashtable: const hashtable_t*
 *                        the avl tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: hashtable_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in avl tree.
 *
 * ----------------------------------------------------------------------------
 */
extern hashtable_iterator_t _hashtable_find(
    const hashtable_t* cpt_hashtable, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_equal_range
 *        Parameters: in) cpt_hashtable: const hashtable_t*
 *                        the avl tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: hashtable_result_pair_t
 *                        the result pair.
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern hashtable_result_pair_t _hashtable_equal_range(
    const hashtable_t* cpt_hashtable, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_count
 *        Parameters: in) cpt_hashtable: const hashtable_t*
 *                        the avl tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _hashtable_count(
    const hashtable_t* cpt_hashtable, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_erase_pos
 *        Parameters: in) pt_hashtable: hashtable_t*
 *                        the avl tree pointer.
 *                    in) t_pos: hashtable_iterator_t
 *                        the erase iterator.
 *           Returns: void
 *       Description: erase the element pointed by t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hashtable_erase_pos(
    hashtable_t* pt_hashtable, hashtable_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_erase_range
 *        Parameters: in) pt_hashtable: hashtable_t*
 *                        the avl tree pointer.
 *                    in) t_begin: hashtable_iterator_t
 *                        the begin iterator.
 *                    in) t_end: hashtable_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: erase the all elements in the range.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hashtable_erase_range(
    hashtable_t* pt_hashtable, 
    hashtable_iterator_t t_begin, 
    hashtable_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_erase
 *        Parameters: in) pt_hashtable: hashtable_t*
 *                        the avl tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _hashtable_erase(hashtable_t* pt_hashtable, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hashtable_swap
 *        Parameters: in) pt_hashtablefirst: hashtable_t*
 *                          the first hashtable.
 *                    in) pt_hashtablesecond: hashtable_t*
 *                          the second hashtable.
 *           Returns: void
 *       Description: swap the datas of first hashtable and second hashtable.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hashtable_swap(
    hashtable_t* pt_hashtablefirst, hashtable_t* pt_hashtablesecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASHTABLE_PRIVATE_H */
/** eof **/

