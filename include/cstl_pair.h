/*
 *  The interface of pair.
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

#ifndef _CSTL_PAIR_H
#define _CSTL_PAIR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define create_pair(first_type, second_type)\
    _create_pair(\
        sizeof(first_type), #first_type, \
        sizeof(second_type), #second_type)

#define pair_make(pt_pair, first_elem, second_elem)\
    _pair_make_first((pt_pair),(first_elem)),_pair_make_second((pt_pair),(second_elem))

#define pair_init_elem(pt_pair, first_elem, second_elem)\
    do\
    {\
        pair_init((pt_pair));\
        pair_make((pt_pair), (first_elem), (second_elem));\
    }while(false)

/** data type declaration and struct, union, enum section **/
typedef struct _tagpair
{
    /* element identify */
    size_t           _t_firsttypesize;
    char             _sz_firsttypename[_ELEM_TYPE_NAME_SIZE+1];
    size_t           _t_secondtypesize;
    char             _sz_secondtypename[_ELEM_TYPE_NAME_SIZE+1];

    void*            first;
    void*            second;

    /* 
     * the compare function :
     * < 0  : element first < element second.
     * == 0 : element first == element second.
     * > 0  : element first > element second. 
     */
    int (*_pfun_first_cmp)(const void*, const void*);
    /* 
     * the compare function :
     * < 0  : element first < element second.
     * == 0 : element first == element second.
     * > 0  : element first > element second. 
     */
    int (*_pfun_second_cmp)(const void*, const void*);
}pair_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_pair
 *        Parameters: in) t_firsttypesize: size_t
 *                          the first element type size.
 *                    in) s_firsttypename: const char*
 *                          the first element type name.
 *                    in) t_secondtypesize: size_t
 *                          the second element type size.
 *                    in) s_secondtypename: const char*
 *                          the second element type name.
 *           Returns: pair_t
 *                          new pair.
 *       Description: create the new pair.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _create_pair(
    size_t t_firsttypesize, const char* s_firsttypename,
    size_t t_secondtypesize, const char* s_secondtypename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _make_first
 *        Parameters: in) pt_pair: pair_t*
 *                    in) first elemen.
 *           Returns: void
 *       Description: make the first element of pair.
 *
 * ----------------------------------------------------------------------------
 */
extern void _pair_make_first(pair_t* pt_pair, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _make_second
 *        Parameters: in) pt_pair: pair_t*
 *                    in) first elemen.
 *           Returns: void
 *       Description: make the second element of pair.
 *
 * ----------------------------------------------------------------------------
 */
extern void _pair_make_second(pair_t* pt_pair, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: pair_init
 *        Parameters: in) pt_pair: pair_t*
 *           Returns: void
 *       Description: initialize the pair.
 *
 * ----------------------------------------------------------------------------
 */
extern void pair_init(pair_t* pt_pair);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: pair_destroy
 *        Parameters: in) pt_pair: pair_t*
 *           Returns: void
 *       Description: destroy the pair.
 *
 * ----------------------------------------------------------------------------
 */
extern void pair_destroy(pair_t* pt_pair);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: pair_init_copy
 *        Parameters: in) pt_pairdest: pair_t*
 *                          the dest pair.
 *                    in) cpt_pairsrc: const pair_t*
 *                          the source pair.
 *           Returns: void
 *       Description: copy the pair.
 *
 * ----------------------------------------------------------------------------
 */
extern void pair_init_copy(pair_t* pt_pairdest, const pair_t* cpt_pairsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: pair_assign
 *        Parameters: in) pt_pairdest: pair_t*
 *                          the dest pair.
 *                    in) cpt_pairsrc: const pair_t*
 *                          the source pair.
 *           Returns: void
 *       Description: copy the pair.
 *
 * ----------------------------------------------------------------------------
 */
extern void pair_assign(pair_t* pt_pairdest, const pair_t* cpt_pairsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: pair_equal
 *        Parameters: in) cpt_pairfirst: const pair_t*
 *                          the first pair.
 *                    in) cpt_pairsecond: const pair_t*
 *                          the second pair.
 *           Returns: bool_t
 *       Description: return whether first pair equal to second pair.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t pair_equal(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: pair_not_equal
 *        Parameters: in) cpt_pairfirst: const pair_t*
 *                          the first pair.
 *                    in) cpt_pairsecond: const pair_t*
 *                          the second pair.
 *           Returns: bool_t
 *       Description: return whether first pair not equal to second pair.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t pair_not_equal(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: pair_less
 *        Parameters: in) cpt_pairfirst: const pair_t*
 *                          the first pair.
 *                    in) cpt_pairsecond: const pair_t*
 *                          the second pair.
 *           Returns: bool_t
 *       Description: return whether first pair less then second pair.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t pair_less(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: pair_great
 *        Parameters: in) cpt_pairfirst: const pair_t*
 *                          the first pair.
 *                    in) cpt_pairsecond: const pair_t*
 *                          the second pair.
 *           Returns: bool_t
 *       Description: return whether first pair greater then second pair.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t pair_great(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: pair_less_equal
 *        Parameters: in) cpt_pairfirst: const pair_t*
 *                          the first pair.
 *                    in) cpt_pairsecond: const pair_t*
 *                          the second pair.
 *           Returns: bool_t
 *       Description: return whether first pair less then or equal to the 
 *                    second pair.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t pair_less_equal(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: pair_great_equal
 *        Parameters: in) cpt_pairfirst: const pair_t*
 *                          the first pair.
 *                    in) cpt_pairsecond: const pair_t*
 *                          the second pair.
 *           Returns: bool_t
 *       Description: return whether first pair greater then or equal to the
 *                    second pair.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t pair_great_equal(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_PAIR_H */
/** eof **/

