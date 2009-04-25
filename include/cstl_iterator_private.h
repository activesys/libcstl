/*
 *  The private interface of iterator.
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

#ifndef _CSTL_ITERATOR_PRIVATE_H
#define _CSTL_ITERATOR_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _iterator_same_type
 *        Parameters: in) t_iterator: iterator_t
 *                            the first iterator for distance.
 *                    in) t_iteratorsrc: iterator_t
 *                            the second iterator for distance.
 *           Returns: bool_t
 *       Description: check the first iterator is same the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _iterator_same_type(
    iterator_t t_iteratorfirst, iterator_t t_iteratorsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _iterator_before
 *        Parameters: in) t_iterator: iterator_t
 *                            the first iterator for distance.
 *                    in) t_iteratorsrc: iterator_t
 *                            the second iterator for distance.
 *           Returns: bool_t
 *       Description: check the first iterator is before the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _iterator_before(
    iterator_t t_iteratorfirst, iterator_t t_iteratorsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _iterator_limit_type
 *        Parameters: in) t_iterator: iterator_t
 *                            the iterator.
 *                    in) t_limittype: iteratortype_t
 *                            the iterator type.
 *           Returns: bool_t
 *       Description: check the iterator type.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _iterator_limit_type(
    iterator_t t_iterator, iteratortype_t t_limittype);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ITERATOR_PRIVATE_H */
/** eof **/

