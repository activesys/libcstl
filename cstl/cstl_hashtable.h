/*
 *  The interface of hashtable.
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

#ifndef _CSTL_HASHTABLE_H_
#define _CSTL_HASHTABLE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/* for the result of equal_range and insert_unique function */

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create hashtable container.
 * @param s_typename        element type name.
 * @return if create hashtable successfully return hashtable pointer, otherwise return NULL.
 * @remarks s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name, libcstl builtin
 *          typename or registed user defined type name, otherwise the function will return NULL.
 */
extern _hashtable_t* _create_hashtable(const char* s_typename);

/**
 * Initialize hashtable container.
 * @param pt_hashtable      hashtable container.
 * @param t_bucketcount     bucket count.
 * @param t_hash            hash function.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pt_hashtable == NULL, then the behavior is undefined, pt_hashtable must be created by _create_hashtable(),
 *          otherwise the behavior is undefined. if t_hash == NULL or t_compare == NULL, then the default hash function is used,
 *          and the default compare function is used.
 */
extern void _hashtable_init(_hashtable_t* pt_hashtable, size_t t_bucketcount, unary_function_t t_hash, binary_function_t t_compare);

/**
 * Initialize hashtable container with hashtable.
 * @param pt_dest           destination hashtable.
 * @param cpt_src           source hashtable.
 * @return void.
 * @remarks if pt_dest == NULL or cpt_src == NULL, then the behavior is undefined, pt_dest must be created by
 *          _create_hashtable(), cpt_src must be initialized, otherwise the behavior is undefined. the element type of
 *          pt_dest and cpt_src must be same, otherwise the behavior is undefine.
 */
extern void _hashtable_init_copy(_hashtable_t* pt_dest, const _hashtable_t* cpt_src);

/**
 * Initialize hashtable container with specific range.
 * @param pt_dest           destination hashtable.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param t_bucketcount     bucket count.
 * @param t_hash            hash function.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_hashtable(), otherwise
 *          the behavior is undefined. [it_begin, it_end) must be belong to a initialized hashtable, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and pt_dest must be same, otherwise the behavior is undefined.
 *          if t_hash == NULL or t_compare == NULL, then the default hash function is used and the default compare function
 *          is used.
 */
extern void _hashtable_init_copy_range(
    _hashtable_t* pt_dest, _hashtable_iterator_t it_begin, _hashtable_iterator_t it_end,
    size_t t_bucketcount, unary_function_t t_hash, binary_function_t t_compare);

/**
 * Destroy hashtable.
 * @param pt_hashtable       hashtable container.
 * @return void.
 * @remarks if pt_hashtable == NULL, then the behavior is undefined, the hashtable must be initialized or created by
 *          _create_hashtable(), otherwise the behavior is undefined.
 */
extern void _hashtable_destroy(_hashtable_t* pt_hashtable);

/**
 * Assign hashtable container.
 * @param pt_dest           destination hashtable container.
 * @param cpt_src           source hashtable container.
 * @return void.
 * @remarks if pt_dest == NULL or cpt_src == NULL, the the behavior is undefined. two hashtable must be initialized, otherwise
 *          the behavior is undefined. if _hashtable_equal(pt_dest, cpt_src), the function dest nothing.
 */
extern void _hashtable_assign(_hashtable_t* pt_dest, const _hashtable_t* cpt_src);

/**
 * Get the number of elements int the hashtable.
 * @param cpt_hashtable      hashtable container.
 * @return the number of elements in the hashtable.
 * @remarks if cpt_hashtable == NULL, then the behavior is undefined, the cpt_hashtable must be initialized, otherwise the
 *          behavior is undefined.
 */
extern size_t _hashtable_size(const _hashtable_t* cpt_hashtable);

/**
 * Test if an hashtable is empty.
 * @param cpt_hashtable      hashtable container.
 * @return true if the hashtable is empty, otherwise return false.
 * @remarks if cpt_hashtable == NULL, then the behavior is undefined, the cpt_hashtable must be initialized, otherwise the
 *          behavior is undefined.
 */
extern bool_t _hashtable_empty(const _hashtable_t* cpt_hashtable);

/**
 * Get the maximum number of elements int the hashtable.
 * @param cpt_hashtable      hashtable container.
 * @return the maximum number of elements in the hashtable.
 * @remarks if cpt_hashtable == NULL, then the behavior is undefined, the cpt_hashtable must be initialized, otherwise the
 *          behavior is undefined.
 */
extern size_t _hashtable_max_size(const _hashtable_t* cpt_hashtable);

/**
 * Get the bucket count of elements int the hashtable.
 * @param cpt_hashtable      hashtable container.
 * @return the bucket count of elements in the hashtable.
 * @remarks if cpt_hashtable == NULL, then the behavior is undefined, the cpt_hashtable must be initialized, otherwise the
 *          behavior is undefined.
 */
extern size_t _hashtable_bucket_count(const _hashtable_t* cpt_hashtable);

/**
 * Return an iterator that addresses the first element in the hashtable.
 * @param cpt_hashtable      hashtable container.
 * @return an iterator that addresses the first element in the hashtable.
 * @remarks if cpt_hashtable == NULL, the behavior is undefined. cpt_hashtable must be initialized, otherwise the behavior
 *          is undefined. return _hashtable_end(), if the hashtable is empty.
 */
extern _hashtable_iterator_t _hashtable_begin(const _hashtable_t* cpt_hashtable);

/**
 * Return an iterator that addresses the location succeeding the last element in the hashtable.
 * @param cpt_hashtable      hashtable container.
 * @return an iterator that addresses location succeeding the last element in the hashtable.
 * @remarks if cpt_hashtable == NULL, the behavior is undefined. cpt_hashtable must be initialized, otherwise the behavior
 *          is undefined.
 */
extern _hashtable_iterator_t _hashtable_end(const _hashtable_t* cpt_hashtable);

/**
 * Return the hash function.
 * @param cpt_hashtable      hashtable container.
 * @return hash function.
 * @remarks if cpt_hashtable == NULL, the behavior is undefined. cpt_hashtable must be initialized, otherwise the behavior
 *          is undefined.
 */
extern unary_function_t _hashtable_hash(const _hashtable_t* cpt_hashtable);

/**
 * Return the compare function of key.
 * @param cpt_hashtable      hashtable container.
 * @return compare function.
 * @remarks if cpt_hashtable == NULL, the behavior is undefined. cpt_hashtable must be initialized, otherwise the behavior
 *          is undefined.
 */
extern binary_function_t _hashtable_key_comp(const _hashtable_t* cpt_hashtable);

/**
 * Find specific element.
 * @param cpt_hashtable      hashtable container.
 * @param cpv_value         specific element.
 * @return iterator addresses the sprcific element in the hashtable, otherwise return _hashtable_end().
 * @remarks if cpt_hashtable == NULL or cpv_value == NULL then the behavior is undefined. cpt_hashtable must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_hashtable must be same, otherwise the
 *          behavior is undefined.
 */
extern _hashtable_iterator_t _hashtable_find(const _hashtable_t* cpt_hashtable, const void* cpv_value);

/**
 * Erases all the elements of an hashtable.
 * @param pt_hashtable       hashtable container.
 * @return void.
 * @remarks if pt_hashtable == NULL, the behavior is undefined. pt_hashtable must be initialized, otherwise the behavior
 *          is undefined.
 */
extern void _hashtable_clear(_hashtable_t* pt_hashtable);

/**
 * Return the number of specific elements in an hashtable
 * @param cpt_hashtable       hashtable container.
 * @param cpv_value         specific element.
 * @return the number of specific elements.
 * @remarks if cpt_hashtable == NULL or cpv_value == NULL then the behavior is undefined. cpt_hashtable must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_hashtable must be same, otherwise the
 *          behavior is undefined.
 */
extern size_t _hashtable_count(const _hashtable_t* cpt_hashtable, const void* cpv_value);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpt_rb_tree      rb tree container.
 * @param cpv_value         specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpt_rb_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_rb_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_rb_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern range_t _hashtable_equal_range(const _hashtable_t* cpt_hashtable, const void* cpv_value);

/**
 * Tests if the two rb tree are equal.
 * @param cpt_first         first rb tree container.
 * @param cpt_second        second rb tree container.
 * @return if first rb tree equal to second rb tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two rb tree must be
 *          initialized, otherwise the behavior is undefined. if the two rb tree are not same type, then return false.
 *          if cpt_first == cpt_second, then return true.
 */
extern bool_t _hashtable_equal(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second);

/**
 * Tests if the two rb tree are not equal.
 * @param cpt_first         first rb tree container.
 * @param cpt_second        second rb tree container.
 * @return if first rb tree not equal to second rb tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two rb tree must be
 *          initialized, otherwise the behavior is undefined. if the two rb tree are not same type, then return false.
 *          if cpt_first == cpt_second, then return false.
 */
extern bool_t _hashtable_not_equal(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second);

/**
 * Tests if the first rb tree is less than the second rb tree.
 * @param cpt_first         first rb tree container.
 * @param cpt_second        second rb tree container.
 * @return if first rb tree is less than the second rb tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two rb tree must be
 *          initialized, otherwise the behavior is undefined. if the two rb tree are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return false.
 */
extern bool_t _hashtable_less(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second);

/**
 * Tests if the first rb tree is less than or equal to the second rb tree.
 * @param cpt_first         first rb tree container.
 * @param cpt_second        second rb tree container.
 * @return if first rb tree is less than or equal to the second rb tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two rb tree must be
 *          initialized, otherwise the behavior is undefined. if the two rb tree are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return true.
 */
extern bool_t _hashtable_less_equal(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second);

/**
 * Tests if the first rb tree is greater than the second rb tree.
 * @param cpt_first         first rb tree container.
 * @param cpt_second        second rb tree container.
 * @return if first rb tree is greater than the second rb tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two rb tree must be
 *          initialized, otherwise the behavior is undefined. if the two rb tree are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return false.
 */
extern bool_t _hashtable_greater(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second);

/**
 * Tests if the first rb tree is greater than or equal to the second rb tree.
 * @param cpt_first         first rb tree container.
 * @param cpt_second        second rb tree container.
 * @return if first rb tree is greater than or equal to the second rb tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two rb tree must be
 *          initialized, otherwise the behavior is undefined. if the two rb tree are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return true.
 */
extern bool_t _hashtable_greater_equal(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second);

/*
 * Resize operation function.
 */
extern void _hashtable_resize(_hashtable_t* pt_hashtable, size_t t_resize);

/*
 * Insert operation functions.
 */
extern _hashtable_iterator_t _hashtable_insert_unique(
    _hashtable_t* pt_hashtable, const void* cpv_value);
extern _hashtable_iterator_t _hashtable_insert_equal(
    _hashtable_t* pt_hashtable, const void* cpv_value);
extern void _hashtable_insert_unique_range(
    _hashtable_t* pt_hashtable, _hashtable_iterator_t it_begin, _hashtable_iterator_t it_end);
extern void _hashtable_insert_equal_range(
    _hashtable_t* pt_hashtable, _hashtable_iterator_t it_begin, _hashtable_iterator_t it_end);

/*
 * Erase operation functions.
 */
extern void _hashtable_erase_pos(_hashtable_t* pt_hashtable, _hashtable_iterator_t t_pos);
extern void _hashtable_erase_range(
    _hashtable_t* pt_hashtable, _hashtable_iterator_t it_begin, _hashtable_iterator_t it_end);
extern size_t _hashtable_erase(_hashtable_t* pt_hashtable, const void* cpv_value);

/*
 * Swap the datas of first hashtable and second hashtable.
 */
extern void _hashtable_swap(
    _hashtable_t* pt_first, _hashtable_t* pt_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASHTABLE_H_ */
/** eof **/

