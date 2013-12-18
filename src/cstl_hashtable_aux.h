/*
 *  The interface of hashtable auxiliary function.
 *  Copyright (C)  2008 - 2014  Wangbo
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

#ifndef _CSTL_HASHTABLE_AUX_H_
#define _CSTL_HASHTABLE_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_HASHTABLE_TYPE_SIZE(pt_hashtable)             ((pt_hashtable)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_HASHTABLE_TYPE_NAME(pt_hashtable)             ((pt_hashtable)->_t_typeinfo._s_typename)
#define _GET_HASHTABLE_TYPE_BASENAME(pt_hashtable)         ((pt_hashtable)->_t_typeinfo._pt_type->_s_typename)
#define _GET_HASHTABLE_TYPE_INIT_FUNCTION(pt_hashtable)    ((pt_hashtable)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_HASHTABLE_TYPE_COPY_FUNCTION(pt_hashtable)    ((pt_hashtable)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_HASHTABLE_TYPE_LESS_FUNCTION(pt_hashtable)    ((pt_hashtable)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_HASHTABLE_TYPE_DESTROY_FUNCTION(pt_hashtable) ((pt_hashtable)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_HASHTABLE_TYPE_STYLE(pt_hashtable)            ((pt_hashtable)->_t_typeinfo._t_style)

typedef _hashnode_t*                    _hashnode_pointer_t;

#define _HASHTABLE_NODE_NAME            "_hashnode_pointer_t"
#define _HASHTABLE_DEFAULT_BUCKET_COUNT 50
#define _HASHTABLE_PRIME_LIST_COUNT     28

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
#ifndef NDEBUG
/**
 * Test hashtable is created by _create_hashtable.
 * @param cpt_hashtable           hashtable container.
 * @return if hashtable is created by create_hashtable, then return true, else return false.
 * @remarks if cpt_hashtable == NULL, then the behavior is undefined.
 */
extern bool_t _hashtable_is_created(const _hashtable_t* cpt_hashtable);

/**
 * Test hashtable is initialized by hashtable initialization functions.
 * @param cpt_hashtable           hashtable container.
 * @return if hashtable is initialized by hashtable initialization functions, then return true, else return false.
 * @remarks if cpt_hashtable == NULL, then the behavior is undefined.
 */
extern bool_t _hashtable_is_inited(const _hashtable_t* cpt_hashtable);

/**
 * Test iterator referenced data is within the hashtable.
 * @param cpt_hashtable         point to hashtable.
 * @param it_iter               hashtable iterator.
 * @return if iterator referenced is within the hashtable, then return true, otherwise return false.
 * @remarks if cpt_hashtable == NULL, then the behavior is undefined, cpt_hashtable must be initialized, otherwise the
 *          behavior is undefined. the it_iter must be valie hashtable iterator, otherwist the behavior is undefined. 
 */
extern bool_t _hashtable_iterator_belong_to_hashtable(const _hashtable_t* cpt_hashtable, _hashtable_iterator_t it_iter);

/**
 * Test the type that saved in the hashtable container and referenced by it_iter are same.
 * @param cpt_hashtable         hashtable container.
 * @param it_iter               hashtable iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_hashtable == NULL or it_iter is not hashtable iterator, then the behavior is undefined.
 */
extern bool_t _hashtable_same_hashtable_iterator_type(const _hashtable_t* cpt_hashtable, _hashtable_iterator_t it_iter);

/**
 * Test the type that saved in the hashtable container and referenced by it_iter are same.
 * @param cpt_hashtable         hashtable container.
 * @param it_iter               iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_hashtable == NULL, then the behavior is undefined.
 */
extern bool_t _hashtable_same_iterator_type(const _hashtable_t* cpt_hashtable, iterator_t it_iter);

/**
 * Test the type that saved in the hashtable container and referenced by it_iter are same.
 * @param cpt_hashtable         hashtable container.
 * @param it_iter               hashtable iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_hashtable == NULL or it_iter is not hashtable iterator, then the behavior is undefined.
 */
extern bool_t _hashtable_same_hashtable_iterator_type_ex(const _hashtable_t* cpt_hashtable, _hashtable_iterator_t it_iter);

#endif /* NDEBUG */

/**
 * Test the type that saved in the hashtable container is same.
 * @param cpt_first             first hashtable.
 * @param cpt_second            second hashtable.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, the behavior is undefined. the two hashtable must be initialized
 *          or created by _create_hashtable(), otherwise the behavior is undefined. if cpt_first == cpt_second then
 *          return true.
 */
extern bool_t _hashtable_same_type(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second);

/**
 * Test the type and compare function that saved in the hashtable container is same.
 * @param cpt_first             first hashtable.
 * @param cpt_second            second hashtable.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, the behavior is undefined. the two hashtable must be initialized
 *          or created by _create_hashtable(), otherwise the behavior is undefined. if cpt_first == cpt_second then
 *          return true.
 */
extern bool_t _hashtable_same_type_ex(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second);

/* init, copy, less and destroy function for _hashnode_t* type */
/*
extern void _hashnode_init(const void* cpv_input, void* pv_output);
extern void _hashnode_copy(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _hashnode_less(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _hashnode_destroy(const void* cpv_input, void* pv_output);
*/

/**
 * The default hash function.
 * @param cpv_input             input parameter.
 * @param pv_output             output parameter.
 * @return void.
 * @remarks if cpv_input == NULL or pv_output == NULL, the behavior is undefined.
 */
extern void _hashtable_default_hash(const void* cpv_input, void* pv_output);

/**
 * Get the next prime base the ul_basenum.
 * @param ul_basenum            specifical base number.
 * @return the next prime base the ul_basenum.
 * @remarks if the base number greater than the max prime number, then return ul_basenum.
 */
extern unsigned long _hashtable_get_prime(unsigned long ul_basenum);

/**
 * Initialize element auxiliary function
 * @param pt_hashtable          hashtable.
 * @param pt_node               hashnode.
 * @return void.
 * @remarks if pt_hashtable == NULL or pt_node == NULL, then the behavior is undefined. pt_hashtable must be initialized or
 *          created by _create_hashtable(), otherwise the behavior is undefined.
 */
extern void _hashtable_init_elem_auxiliary(_hashtable_t* pt_hashtable, _hashnode_t* pt_node);

/**
 * hash auxiliary
 * @param cpt_hashtable         hashtable.
 * @param cpv_input             input parameter.
 * @param pv_output             output parameter.
 * @return void.
 * @remarks if cpt_hashtable == NULL, cpv_input == NULL or pv_output == NULL, then the behavior is undefined. cpt_hashtable
 *          must be initialized, otherwise the behavior is undefined.
 */
extern void _hashtable_hash_auxiliary(const _hashtable_t* cpt_hashtable, const void* cpv_input, void* pv_output);

/**
 * Element compare function auxiliary
 * @param cpt_hashtable         hashtable.
 * @param cpv_first             first element.
 * @param cpv_second            second element.
 * @param pv_output             output.
 * @return void.
 * @remarks if cpt_hashtable == NULL or cpv_first == NULL or cpv_second == NULL or pv_output == NULL, the behavior is
 *          undefined. cpt_hashtable must be initialized or created by _create_hashtable(), otherwise the behavior is
 *          undefined.
 */
extern void _hashtable_elem_compare_auxiliary(
    const _hashtable_t* cpt_hashtable, const void* cpv_first, const void* cpv_second, void* pv_output);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASHTABLE_AUX_H_ */
/** eof **/

