/*
 *  The vector iterator interface for iterator module.
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

#ifndef _CSTL_VECTOR_ITERATOR_H
#define _CSTL_VECTOR_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t vector_iterator_t;
typedef iterator_t vector_reverse_iterator_t;
struct _tagvector;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create new iterator_t of vector_t.
 */
extern vector_iterator_t create_vector_iterator(void);

/*
 * The relationship operator of iterator_t.
 */
extern bool_t _vector_iterator_equal(
    const struct _tagvector* cpt_vector, const vector_iterator_t* cpt_iterator,
    vector_iterator_t t_iterator);
extern bool_t _vector_iterator_less(
    const struct _tagvector* cpt_vector, const vector_iterator_t* cpt_iterator,
    vector_iterator_t t_iterator);
extern bool_t _vector_iterator_before(
    const vector_iterator_t* cpt_iteratorfirst, const vector_iterator_t* cpt_iteratorsecond);

/*
 * Get and Set element that is referenced by iterator_t.
 */
extern void _vector_iterator_get_value(
    const struct _tagvector* cpt_vector, const vector_iterator_t* cpt_iterator,
    void* pv_value);
extern void _vector_iterator_set_value(
    const struct _tagvector* cpt_vector, const vector_iterator_t* cpt_iterator,
    const void* cpv_value);
extern const void* _vector_iterator_get_pointer(
    const struct _tagvector* cpt_vector, const vector_iterator_t* cpt_iterator); 

/*
 * Increase or decrease operator of iterator_t.
 */
extern void _vector_iterator_next(
    const struct _tagvector* cpt_vector, vector_iterator_t* pt_iterator);
extern void _vector_iterator_prev(
    const struct _tagvector* cpt_vector, vector_iterator_t* pt_iterator);
extern void _vector_iterator_next_n(
    const struct _tagvector* cpt_vector, vector_iterator_t* pt_iterator, int n_step);
extern void _vector_iterator_prev_n(
    const struct _tagvector* cpt_vector, vector_iterator_t* pt_iterator, int n_step);

/*
 * Access element randomly through iterator_t.
 */
extern void* _vector_iterator_at(
    const struct _tagvector* cpt_vector, const vector_iterator_t* cpt_iterator,
    unsigned int un_index);

/*
 * Subaction operator of iterator_t.
 */
extern int _vector_iterator_minus(
    const struct _tagvector* cpt_vector, const vector_iterator_t* cpt_iterator, 
    vector_iterator_t t_iterator);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_VECTOR_ITERATOR_H */
/** eof **/

