/*
 *  The interface of pair.
 *  Copyright (C)  2008 - 2012  Wangbo
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
/**
 * Create pair container.
 * @param ...        element type name.
 * @return if create pair successfully return pair pointer, otherwise return NULL.
 * @remarks element type name should be C builtin type name, libcstl builtin typename or registed user defined type name,
 *          otherwise the function will return NULL.
 */
#define create_pair(...) _create_pair(#__VA_ARGS__)

/**
 * Initialize pair container with sepcifical element.
 * @param ppair_pair           destination pair.
 * @param first_elem           first element.
 * @param second_elem          second elemeent.
 * @return void.
 * @remarks if ppair_pair == NULL, then the behavior is undefined, ppair_pair must be created by create_pair().
 */
#define pair_init_elem(ppair_pair, first_elem, second_elem)\
    do\
    {\
        pair_init((ppair_pair));\
        pair_make((ppair_pair), (first_elem), (second_elem));\
    }while(false)

/**
 * Assign pair container with specifical element.
 * @param ppair_pair           destination pair container.
 * @param first_elem           first element.
 * @param second_elem          second element.
 * @return void.
 * @remarks if ppair_pair == NULL, the the behavior is undefined. pair must be initialized, otherwise the behavior is undefined. 
 */
#define pair_make(ppair_pair, first_elem, second_elem)\
    _pair_make_first((ppair_pair),(first_elem)),_pair_make_second((ppair_pair),(second_elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize pair container.
 * @param ppair_pair          pair container.
 * @return void.
 * @remarks if ppair_pair == NULL, then the behavior is undefined, ppair_pair must be created by create_pair(), otherwise
 *          the behavior is undefined.
 */
extern void pair_init(pair_t* ppair_pair);

/**
 * Initialize pair container with pair.
 * @param ppair_dest           destination pair.
 * @param cppair_src           source pair.
 * @return void.
 * @remarks if ppair_dest == NULL or cppair_src == NULL, then the behavior is undefined, ppair_dest must be created by
 *          create_pair(), cppair_src must be initialized, otherwise the behavior is undefined. the element type of
 *          ppair_dest and cppair_src must be same, otherwise the behavior is undefine.
 */
extern void pair_init_copy(pair_t* ppair_dest, const pair_t* cppair_src);

/**
 * Destroy pair.
 * @param ppair_pair       pair container.
 * @return void.
 * @remarks if ppair_pair == NULL, then the behavior is undefined, the pair must be initialized or created by create_pair(),
 *          otherwise the behavior is undefined.
 */
extern void pair_destroy(pair_t* ppair_pair);

/**
 * Assign pair container.
 * @param ppair_dest           destination pair container.
 * @param cppair_src           source pair container.
 * @return void.
 * @remarks if ppair_dest == NULL or cppair_src == NULL, the the behavior is undefined. two pair must be initialized, otherwise
 *          the behavior is undefined. if pair_equal(ppair_dest, cppair_src), the function dest nothing.
 */
extern void pair_assign(pair_t* ppair_dest, const pair_t* cppair_src);

/**
 * Access pair first element.
 * @param cppair_pair       pair container.
 * @return the pointer to the first element.
 * @remarks if cppair_pair == NULL, then the behavior is undefined, the pair must be initialized, otherwise the
 *          behavior is undefined.
 */
extern void* pair_first(const pair_t* cppair_pair);

/**
 * Access pair second element.
 * @param cppair_pair       pair container.
 * @return the pointer to the first element.
 * @remarks if cppair_pair == NULL, then the behavior is undefined, the pair must be initialized, otherwise the
 *          behavior is undefined.
 */
extern void* pair_second(const pair_t* cppair_pair);

/**
 * Tests if the two pair are equal.
 * @param cppair_first         first pair container.
 * @param cppair_second        second pair container.
 * @return if first pair equal to second pair, then return true, else return false.
 * @remarks if cppair_first == NULL or cppair_second == NULL, then the behavior is undefined. the two pair must be
 *          initialized, otherwise the behavior is undefined. if the two pair are not same type, the behavior is undefined.
 *          if cppair_first == cppair_second, then return true.
 */
extern bool_t pair_equal(const pair_t* cppair_first, const pair_t* cppair_second);

/**
 * Tests if the two pair are not equal.
 * @param cppair_first         first pair container.
 * @param cppair_second        second pair container.
 * @return if first pair not equal to second pair, then return true, else return false.
 * @remarks if cppair_first == NULL or cppair_second == NULL, then the behavior is undefined. the two pair must be
 *          initialized, otherwise the behavior is undefined. if the two pair are not same type, the behavior is undefined.
 *          if cppair_first == cppair_second, then return false.
 */
extern bool_t pair_not_equal(const pair_t* cppair_first, const pair_t* cppair_second);

/**
 * Tests if the first pair is less than the second pair.
 * @param cppair_first         first pair container.
 * @param cppair_second        second pair container.
 * @return if first pair is less than the second pair, then return true, else return false.
 * @remarks if cppair_first == NULL or cppair_second == NULL, then the behavior is undefined. the two pair must be
 *          initialized, otherwise the behavior is undefined. if the two pair are not same type, the behavior is
 *          undefined. if cppair_first == cppair_second, then return false.
 */
extern bool_t pair_less(const pair_t* cppair_first, const pair_t* cppair_second);

/**
 * Tests if the first pair is less than or equal to the second pair.
 * @param cppair_first         first pair container.
 * @param cppair_second        second pair container.
 * @return if first pair is less than or equal to the second pair, then return true, else return false.
 * @remarks if cppair_first == NULL or cppair_second == NULL, then the behavior is undefined. the two pair must be
 *          initialized, otherwise the behavior is undefined. if the two pair are not same type, the behavior is
 *          undefined. if cppair_first == cppair_second, then return true.
 */
extern bool_t pair_less_equal(const pair_t* cppair_first, const pair_t* cppair_second);

/**
 * Tests if the first pair is greater than the second pair.
 * @param cppair_first         first pair container.
 * @param cppair_second        second pair container.
 * @return if first pair is greater than the second pair, then return true, else return false.
 * @remarks if cppair_first == NULL or cppair_second == NULL, then the behavior is undefined. the two pair must be
 *          initialized, otherwise the behavior is undefined. if the two pair are not same type, the behavior is
 *          undefined. if cppair_first == cppair_second, then return false.
 */
extern bool_t pair_greater(const pair_t* cppair_first, const pair_t* cppair_second);

/**
 * Tests if the first pair is greater than or equal to the second pair.
 * @param cppair_first         first pair container.
 * @param cppair_second        second pair container.
 * @return if first pair is greater than or equal to the second pair, then return true, else return false.
 * @remarks if cppair_first == NULL or cppair_second == NULL, then the behavior is undefined. the two pair must be
 *          initialized, otherwise the behavior is undefined. if the two pair are not same type, the behavior is
 *          undefined. if cppair_first == cppair_second, then return true.
 */
extern bool_t pair_greater_equal(const pair_t* cppair_first, const pair_t* cppair_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_PAIR_H_ */
/** eof **/

