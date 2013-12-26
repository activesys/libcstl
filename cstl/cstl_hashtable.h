/*
 *  The interface of hashtable.
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
 * @param ufun_hash         hash function.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if pt_hashtable == NULL, then the behavior is undefined, pt_hashtable must be created by _create_hashtable(),
 *          otherwise the behavior is undefined. if ufun_hash == NULL or bfun_compare == NULL, then the default hash function is used,
 *          and the default compare function is used.
 */
extern void _hashtable_init(_hashtable_t* pt_hashtable, size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare);

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
 * @param ufun_hash         hash function.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_hashtable(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pt_dest must be same, otherwise the behavior
 *          is undefined. if ufun_hash == NULL or bfun_compare == NULL, then the default hash function is used and the 
 *          default compare function is used.
 */
extern void _hashtable_init_copy_equal_range(
    _hashtable_t* pt_dest, iterator_t it_begin, iterator_t it_end, size_t t_bucketcount,
    ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Initialize hashtable container with specific array.
 * @param pt_dest           destination hashtable.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @param t_bucketcount     bucket count.
 * @param ufun_hash         hash function.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_hashtable(), otherwise
 *          the behavior is undefined. the type of array and pt_dest must be same, otherwise the behavior is undefined. 
 *          if ufun_hash == NULL or bfun_compare == NULL, then the default hash function is used and the default compare 
 *          function is used.
 */
extern void _hashtable_init_copy_equal_array(
    _hashtable_t* pt_dest, const void* cpv_array, size_t t_count, size_t t_bucketcount,
    ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Initialize hashtable container with specific range.
 * @param pt_dest           destination hashtable.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param t_bucketcount     bucket count.
 * @param ufun_hash         hash function.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_hashtable(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pt_dest must be same, otherwise the behavior
 *          is undefined. if ufun_hash == NULL or bfun_compare == NULL, then the default hash function is used and the 
 *          default compare function is used.
 */
extern void _hashtable_init_copy_unique_range(
    _hashtable_t* pt_dest, iterator_t it_begin, iterator_t it_end, size_t t_bucketcount,
    ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Initialize hashtable container with specific array.
 * @param pt_dest           destination hashtable.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @param t_bucketcount     bucket count.
 * @param ufun_hash         hash function.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_hashtable(), otherwise
 *          the behavior is undefined. the type of array and pt_dest must be same, otherwise the behavior is undefined. 
 *          if ufun_hash == NULL or bfun_compare == NULL, then the default hash function is used and the default compare 
 *          function is used.
 */
extern void _hashtable_init_copy_unique_array(
    _hashtable_t* pt_dest, const void* cpv_array, size_t t_count, size_t t_bucketcount,
    ufun_t ufun_hash, bfun_t bfun_compare);

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
extern ufun_t _hashtable_hash(const _hashtable_t* cpt_hashtable);

/**
 * Return the compare function of key.
 * @param cpt_hashtable      hashtable container.
 * @return compare function.
 * @remarks if cpt_hashtable == NULL, the behavior is undefined. cpt_hashtable must be initialized, otherwise the behavior
 *          is undefined.
 */
extern bfun_t _hashtable_key_comp(const _hashtable_t* cpt_hashtable);

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
 * @param cpt_hashtable      hashtable container.
 * @param cpv_value         specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpt_hashtable == NULL or cpv_value == NULL then the behavior is undefined. cpt_hashtable must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_hashtable must be same, otherwise the
 *          behavior is undefined.
 */
extern range_t _hashtable_equal_range(const _hashtable_t* cpt_hashtable, const void* cpv_value);

/**
 * Tests if the two hashtable are equal.
 * @param cpt_first         first hashtable container.
 * @param cpt_second        second hashtable container.
 * @return if first hashtable equal to second hashtable, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two hashtable must be
 *          initialized, otherwise the behavior is undefined. if the two hashtable are not same type, then return false.
 *          if cpt_first == cpt_second, then return true.
 */
extern bool_t _hashtable_equal(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second);

/**
 * Tests if the two hashtable are not equal.
 * @param cpt_first         first hashtable container.
 * @param cpt_second        second hashtable container.
 * @return if first hashtable not equal to second hashtable, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two hashtable must be
 *          initialized, otherwise the behavior is undefined. if the two hashtable are not same type, then return false.
 *          if cpt_first == cpt_second, then return false.
 */
extern bool_t _hashtable_not_equal(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second);

/**
 * Tests if the first hashtable is less than the second hashtable.
 * @param cpt_first         first hashtable container.
 * @param cpt_second        second hashtable container.
 * @return if first hashtable is less than the second hashtable, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two hashtable must be
 *          initialized, otherwise the behavior is undefined. if the two hashtable are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return false.
 */
extern bool_t _hashtable_less(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second);

/**
 * Tests if the first hashtable is less than or equal to the second hashtable.
 * @param cpt_first         first hashtable container.
 * @param cpt_second        second hashtable container.
 * @return if first hashtable is less than or equal to the second hashtable, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two hashtable must be
 *          initialized, otherwise the behavior is undefined. if the two hashtable are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return true.
 */
extern bool_t _hashtable_less_equal(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second);

/**
 * Tests if the first hashtable is greater than the second hashtable.
 * @param cpt_first         first hashtable container.
 * @param cpt_second        second hashtable container.
 * @return if first hashtable is greater than the second hashtable, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two hashtable must be
 *          initialized, otherwise the behavior is undefined. if the two hashtable are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return false.
 */
extern bool_t _hashtable_greater(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second);

/**
 * Tests if the first hashtable is greater than or equal to the second hashtable.
 * @param cpt_first         first hashtable container.
 * @param cpt_second        second hashtable container.
 * @return if first hashtable is greater than or equal to the second hashtable, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two hashtable must be
 *          initialized, otherwise the behavior is undefined. if the two hashtable are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return true.
 */
extern bool_t _hashtable_greater_equal(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second);

/**
 * Resize.
 * @param pt_hashtable      hashtable container.
 * @param t_resize          resize hashtable bucket count.
 * @return void.
 * @remarks if pt_hashtable == NULL, the behavior is undefined, pt_hashtable must be initialized,otherwise the behavior
 *          is undefined.
 */
extern void _hashtable_resize(_hashtable_t* pt_hashtable, size_t t_resize);

/**
 * Inserts an unique element into a hashtable.
 * @param pt_hashtable       hashtable container.
 * @param cpv_value         specific element.
 * @return an iterator addresses the inserted element, or hashtable end if insert failed.
 * @remarks if pt_hashtable == NULL or cpv_value == NULL then the behavior is undefined. cpt_hashtable must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_hashtable must be same, otherwise the
 *          behavior is undefined.
 */
extern _hashtable_iterator_t _hashtable_insert_unique(_hashtable_t* pt_hashtable, const void* cpv_value);

/**
 * Inserts an element into a hashtable.
 * @param pt_hashtable       hashtable container.
 * @param cpv_value         specific element.
 * @return an iterator addresses the inserted element, or hashtable end if insert failed.
 * @remarks if pt_hashtable == NULL or cpv_value == NULL then the behavior is undefined. cpt_hashtable must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_hashtable must be same, otherwise the
 *          behavior is undefined.
 */
extern _hashtable_iterator_t _hashtable_insert_equal(_hashtable_t* pt_hashtable, const void* cpv_value);

/**
 * Inserts an range of unique element into a hashtable.
 * @param pt_hashtable      hashtable container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pt_hashtable == NULL then the behavior is undefined. pt_hashtable must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cpt_hashtable must be same, otherwise the behavior is undefined.
 *          [it_begin, it_end) must be valid range, otherwise the behavior is undefine.
 */
extern void _hashtable_insert_unique_range(_hashtable_t* pt_hashtable, iterator_t it_begin, iterator_t it_end);

/**
 * Inserts an array of unique element into a hashtable.
 * @param pt_hashtable      hashtable container.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pt_hashtable == NULL then the behavior is undefined. pt_hashtable must be initialized, otherwise the behavior
 *          is undefined. the type of array and cpt_hashtable must be same, otherwise the behavior is undefined. array must 
 *          be valid array, otherwise the behavior is undefine.
 */
extern void _hashtable_insert_unique_array(_hashtable_t* pt_hashtable, const void* cpv_array, size_t t_count);

/**
 * Inserts an range into a hashtable.
 * @param pt_hashtable      hashtable container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pt_hashtable == NULL then the behavior is undefined. pt_hashtable must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cpt_hashtable must be same, otherwise the behavior is undefined.
 *          [it_begin, it_end) must be valid range, otherwise the behavior is undefine.
 */
extern void _hashtable_insert_equal_range(_hashtable_t* pt_hashtable, iterator_t it_begin, iterator_t it_end);

/**
 * Inserts an array into a hashtable.
 * @param pt_hashtable      hashtable container.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pt_hashtable == NULL then the behavior is undefined. pt_hashtable must be initialized, otherwise the behavior
 *          is undefined. the type of array and cpt_hashtable must be same, otherwise the behavior is undefined. array must 
 *          be valid range, otherwise the behavior is undefine.
 */
extern void _hashtable_insert_equal_array(_hashtable_t* pt_hashtable, const void* cpv_array, size_t t_count);

/*
 * Erase an element in an hashtable from specificed position.
 * @param pt_hashtable       hashtable container.
 * @param it_pos            specificed position.
 * @return void.
 * @remarks if pt_hashtable == NULL then the behavior is undefined. pt_hashtable must be initialized, otherwise the behavior
 *          is undefined. it_pos must be valid iterator, otherwise the behavior is undefined.
 */
extern void _hashtable_erase_pos(_hashtable_t* pt_hashtable, _hashtable_iterator_t it_pos);

/*
 * Erase a range of element in an hashtable.
 * @param pt_hashtable       hashtable container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pt_hashtable == NULL then the behavior is undefined. pt_hashtable must be initialized, otherwise the behavior
 *          is undefined. [it_begin, it_end) must be valid range for pt_hashtable, otherwise the behavior is undefine.
 */
extern void _hashtable_erase_range(
    _hashtable_t* pt_hashtable, _hashtable_iterator_t it_begin, _hashtable_iterator_t it_end);

/**
 * Erase an element from a hashtable that match a specified element.
 * @param pt_hashtable       hashtable container.
 * @param cpv_value         specific element.
 * @return the number of erased elements.
 * @remarks if pt_hashtable == NULL or cpv_value == NULL then the behavior is undefined. cpt_hashtable must be initialized,
 *          otherwise the behavior is undefined. 
 */
extern size_t _hashtable_erase(_hashtable_t* pt_hashtable, const void* cpv_value);

/**
 * Swap the datas of first hashtable and second hashtable.
 * @param pt_first          first hashtable container.
 * @param pt_second         second hashtable container.
 * @return void.
 * @remarks if pt_first == NULL or pt_second == NULL, then the behavior is undefined. the two hashtable must be
 *          initialized, otherwise the behavior is undefined. if the two hashtable are not same type, the behavior is
 *          undefined. if _hashtable_equal(cpt_first, cpt_second), then the function do nothing.
 */
extern void _hashtable_swap(_hashtable_t* pt_first, _hashtable_t* pt_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASHTABLE_H_ */
/** eof **/

