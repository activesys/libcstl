/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     multiset
 *  Filename:   cstl_multiset_private.h
 *
 *  The private interface of multiset.
 *
 *  2009-01-08 10:44:23
 * =============================================================================
 */

#ifndef _CSTL_MULTISET_PRIVATE_H
#define _CSTL_MULTISET_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define _GET_MULTISET_AVL_TREE(pt_multiset)\
    (&((pt_multiset)->_t_tree._t_avl))
#define _GET_MULTISET_RB_TREE(pt_multiset)\
    (&((pt_multiset)->_t_tree._t_rb))

/** data type declaration and struct, union, enum section **/
/* the multiset use rb tree default */
typedef struct _tagmultiset
{
    union
    {
        avl_tree_t _t_avl;
        rb_tree_t  _t_rb;
    }_t_tree;
}multiset_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_multiset
 *        Parameters: in) t_typesize: size_t
 *                          the element type size.
 *                    in) s_typename: const char*
 *                          the element type name.
 *           Returns: multiset_t
 *                          new multiset.
 *       Description: create the new multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_t _create_multiset(size_t t_typesize, const char* s_typename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_find
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                        the multiset pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: multiset_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_iterator_t _multiset_find(const multiset_t* cpt_multiset, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_find_varg
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                        the multiset pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: multiset_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_iterator_t _multiset_find_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_count
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                        the multiset pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _multiset_count(const multiset_t* cpt_multiset, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_count_varg
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                        the multiset pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _multiset_count_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_lower_bound
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                        the multiset pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: multiset_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is not less then value.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_iterator_t _multiset_lower_bound(
    const multiset_t* cpt_multiset, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_lower_bound_varg
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                        the multiset pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: multiset_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is not less then value.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_iterator_t _multiset_lower_bound_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_upper_bound
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                        the multiset pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: multiset_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is greater then value.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_iterator_t _multiset_upper_bound(
    const multiset_t* cpt_multiset, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_upper_bound_varg
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                        the multiset pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: multiset_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is greater then value.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_iterator_t _multiset_upper_bound_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_equal_range
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                        the multiset pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: pair_t(multiset_iterator_t, multiset_iterator_t)
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _multiset_equal_range(const multiset_t* cpt_multiset, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_equal_range_varg
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                        the multiset pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: pair_t(multiset_iterator_t, multiset_iterator_t).
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _multiset_equal_range_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_erase
 *        Parameters: in) pt_multiset: multiset_t*
 *                        the rb tree pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _multiset_erase(multiset_t* pt_multiset, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_erase_varg
 *        Parameters: in) pt_multiset: multiset_t*
 *                        the rb tree pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _multiset_erase_varg(multiset_t* pt_multiset, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_insert
 *        Parameters: in) pt_multiset: multiset_t*
 *                        the multiset pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: multiset_iterator_t
 *                        the insert result.
 *       Description: insert value into multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_iterator_t _multiset_insert(multiset_t* pt_multiset, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_insert_varg
 *        Parameters: in) pt_multiset: multiset_t*
 *                        the multiset pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: multiset_iterator_t
 *                        the insert result.
 *       Description: insert value into multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_iterator_t _multiset_insert_varg(
    multiset_t* pt_multiset, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_insert_hint
 *        Parameters: in) pt_multiset: multiset_t*
 *                        the multiset pointer.
 *                    in) t_hint: multiset_iterator_t
 *                        the hint iterator.
 *                    in) ...
 *                        the target value.
 *           Returns: multiset_iterator_t
 *                        the iterator of new element.
 *       Description: insert value into multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_iterator_t _multiset_insert_hint(
    multiset_t* pt_multiset, multiset_iterator_t t_hint, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_insert_hint_varg
 *        Parameters: in) pt_multiset: multiset_t*
 *                        the multiset pointer.
 *                    in) t_hint: multiset_iterator_t
 *                        the hint iterator.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: multiset_iterator_t
 *                        the iterator of new element.
 *       Description: insert value into multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_iterator_t _multiset_insert_hint_varg(
    multiset_t* pt_multiset, multiset_iterator_t t_hint, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTISET_PRIVATE_H */
/** eof **/

