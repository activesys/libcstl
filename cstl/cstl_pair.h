/*
 *  The interface of pair.
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

#ifndef _CSTL_PAIR_H_
#define _CSTL_PAIR_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define create_pair(...) _create_pair(#__VA_ARGS__)

#define pair_make(pt_pair, first_elem, second_elem)\
    _pair_make_first((pt_pair),(first_elem)),_pair_make_second((pt_pair),(second_elem))

#define pair_init_elem(pt_pair, first_elem, second_elem)\
    do\
    {\
        pair_init((pt_pair));\
        pair_make((pt_pair), (first_elem), (second_elem));\
    }while(false)

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create, initialization and destroy functions.
 */
extern void pair_init(pair_t* pt_pair);
extern void pair_destroy(pair_t* pt_pair);
extern void pair_init_copy(pair_t* pt_pairdest, const pair_t* cpt_pairsrc);

/*
 * Assign operator function.
 */
extern void pair_assign(pair_t* pt_pairdest, const pair_t* cpt_pairsrc);

/*
 * Access pair first and second element.
 */
extern void* pair_first(const pair_t* cpt_pair);
extern void* pair_second(const pair_t* cpt_pair);

/*
 * Relationship operator functions.
 */
extern bool_t pair_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
extern bool_t pair_not_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
extern bool_t pair_less(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
extern bool_t pair_greater(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
extern bool_t pair_less_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
extern bool_t pair_greater_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_PAIR_H_ */
/** eof **/

