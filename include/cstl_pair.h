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
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
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
 * Create, initialization and destroy functions.
 */
extern pair_t _create_pair(
    size_t t_firsttypesize, const char* s_firsttypename,
    size_t t_secondtypesize, const char* s_secondtypename);
extern void _pair_make_first(pair_t* pt_pair, ...);
extern void _pair_make_second(pair_t* pt_pair, ...);
extern void pair_init(pair_t* pt_pair);
extern void pair_destroy(pair_t* pt_pair);
extern void pair_init_copy(pair_t* pt_pairdest, const pair_t* cpt_pairsrc);

/*
 * Assign operator function.
 */
extern void pair_assign(pair_t* pt_pairdest, const pair_t* cpt_pairsrc);

/*
 * Relationship operator functions.
 */
extern bool_t pair_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
extern bool_t pair_not_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
extern bool_t pair_less(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
extern bool_t pair_great(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
extern bool_t pair_less_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
extern bool_t pair_great_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_PAIR_H */
/** eof **/

