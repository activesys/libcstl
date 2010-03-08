/*
 *  The interface of hashtable test.
 *  Copyright (C)  2008,2009,2010  Wangbo
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

#ifndef _TEST_HASHTABLE_H
#define _TEST_HASHTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/
#include "chash_set.h"
#include "chash_map.h"

/** constant declaration and macro section **/
#define _print_hash_map_c(pt_hmap, fmt, key_type, value_type)\
    do{\
        iterator_t t_iter;\
        printf("=======================================\n");\
        printf("empty: %u, size: %u, max_size: %u, bucket count: %u\n",\
            hash_map_empty(pt_hmap), hash_map_size(pt_hmap),\
            hash_map_max_size(pt_hmap), hash_map_bucket_count(pt_hmap));\
        for(t_iter = hash_map_begin(pt_hmap);\
            !iterator_equal(t_iter, hash_map_end(pt_hmap));\
            t_iter = iterator_next(t_iter))\
        {\
            printf(fmt,\
                *(key_type*)pair_first((pair_t*)iterator_get_pointer(t_iter)),\
                *(value_type*)pair_second((pair_t*)iterator_get_pointer(t_iter)));\
        }\
        printf("\n");\
    }while(false)

#define _print_hash_multimap_c(pt_hmmap, fmt, key_type, value_type)\
    do{\
        iterator_t t_iter;\
        printf("=======================================\n");\
        printf("empty: %u, size: %u, max_size: %u, bucket count: %u\n",\
            hash_multimap_empty(pt_hmmap), hash_multimap_size(pt_hmmap),\
            hash_multimap_max_size(pt_hmmap), hash_multimap_bucket_count(pt_hmmap));\
        for(t_iter = hash_multimap_begin(pt_hmmap);\
            !iterator_equal(t_iter, hash_multimap_end(pt_hmmap));\
            t_iter = iterator_next(t_iter))\
        {\
            printf(fmt,\
                *(key_type*)pair_first((pair_t*)iterator_get_pointer(t_iter)),\
                *(value_type*)pair_second((pair_t*)iterator_get_pointer(t_iter)));\
        }\
        printf("\n");\
    }while(false)

#define _print_hash_set_c(pt_hset, fmt, type)\
    do{\
        iterator_t t_iter;\
        printf("=======================================\n");\
        printf("empty: %u, size: %u, max_size: %u, bucket count: %u\n",\
            hash_set_empty(pt_hset), hash_set_size(pt_hset),\
            hash_set_max_size(pt_hset), hash_set_bucket_count(pt_hset));\
        for(t_iter = hash_set_begin(pt_hset);\
            !iterator_equal(t_iter, hash_set_end(pt_hset));\
            t_iter = iterator_next(t_iter))\
        {\
            printf(fmt, *(type*)iterator_get_pointer(t_iter));\
        }\
        printf("\n");\
    }while(false)

#define _debug_hash_set_c(pt_hset, fmt, type)\
    do{\
        size_t t_index = 0;\
        printf("=======================================\n");\
        printf("empty: %u, size: %u, max_size: %u, bucket count: %u\n",\
            hash_set_empty(pt_hset), hash_set_size(pt_hset),\
            hash_set_max_size(pt_hset), hash_set_bucket_count(pt_hset));\
        for(t_index = 0; t_index < hash_set_bucket_count(pt_hset); ++t_index)\
        {\
            hashnode_t** ppt_bucket = (hashnode_t**)vector_at(&pt_hset->_t_hashtable._t_bucket, t_index);\
            hashnode_t*  pt_node = *ppt_bucket;\
            printf("[%u]", t_index);\
            while(pt_node != NULL)\
            {\
                printf("->[");\
                printf(fmt, *(type*)(pt_node->_pc_data));\
                printf("]");\
                pt_node = pt_node->_pt_next;\
            }\
            printf("\n");\
        }\
        printf("=======================================\n");\
    }while(false)

#define _print_hash_multiset_c(pt_hmset, fmt, type)\
    do{\
        iterator_t t_iter;\
        printf("=======================================\n");\
        printf("empty: %u, size: %u, max_size: %u, bucket count: %u\n",\
            hash_multiset_empty(pt_hmset), hash_multiset_size(pt_hmset),\
            hash_multiset_max_size(pt_hmset), hash_multiset_bucket_count(pt_hmset));\
        for(t_iter = hash_multiset_begin(pt_hmset);\
            !iterator_equal(t_iter, hash_multiset_end(pt_hmset));\
            t_iter = iterator_next(t_iter))\
        {\
            printf(fmt, *(type*)iterator_get_pointer(t_iter));\
        }\
        printf("\n");\
    }while(false)

#define _debug_hash_multiset_c(pt_hmset, fmt, type)\
    do{\
        size_t t_index = 0;\
        printf("=======================================\n");\
        printf("empty: %u, size: %u, max_size: %u, bucket count: %u\n",\
            hash_multiset_empty(pt_hmset), hash_multiset_size(pt_hmset),\
            hash_multiset_max_size(pt_hmset), hash_multiset_bucket_count(pt_hmset));\
        for(t_index = 0; t_index < hash_multiset_bucket_count(pt_hmset); ++t_index)\
        {\
            hashnode_t** ppt_bucket = (hashnode_t**)vector_at(&pt_hmset->_t_hashtable._t_bucket, t_index);\
            hashnode_t*  pt_node = *ppt_bucket;\
            printf("[%u]", t_index);\
            while(pt_node != NULL)\
            {\
                printf("->[");\
                printf(fmt, *(type*)(pt_node->_pc_data));\
                printf("]");\
                pt_node = pt_node->_pt_next;\
            }\
            printf("\n");\
        }\
        printf("=======================================\n");\
    }while(false)
/** data type declaration and struct, union, enum section **/
typedef struct _taghashsample
{
    double _d_first;
    long   _l_second;
}hash_sample_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
extern void test_hashtable(void);
extern void _debug_hash_set_user(const hash_set_t* cpt_hset);
extern void _debug_hash_multiset_user(const hash_multiset_t* cpt_hmset);
extern void _print_hash_set_sample(const hash_set_t* cpt_hset);
extern void _print_hash_map_sample(const hash_map_t* cpt_hmap);
extern void _print_hash_multimap_sample(const hash_multimap_t* cpt_hmmap);
extern void _print_hash_multiset_sample(const hash_multiset_t* cpt_hmset);
extern void _hash_sample_init(const void* cpv_input, void* pv_output);
extern void _hash_sample_copy(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _hash_sample_less(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _hash_sample_destroy(const void* cpv_input, void* pv_output);
extern void _hash_sample_great(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _hash_set_sample_hash(const void* cpv_input, void* pv_output);
extern void _hash_map_sample_hash(const void* cpv_input, void* pv_output);
extern void _hash_multimap_sample_hash(const void* cpv_input, void* pv_output);
extern void _print_hash_set_cstl(const hash_set_t* cpt_hset);
extern void _print_hash_multiset_cstl(const hash_multiset_t* cpt_hmset);
extern void _hash_set_cstl_hash(const void* cpv_input, void* pv_output);
extern void _hash_multiset_cstl_hash(const void* cpv_input, void* pv_output);
extern void _hash_set_int_hash(const void* cpv_input, void* pv_output);
extern void _print_hash_set_cstr(const hash_set_t* cpt_hset);
extern void _hash_set_cstr_hash(const void* cpv_input, void* pv_output);
extern void _hash_set_cstr_less(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _print_hash_multiset_cstr(const hash_multiset_t* cpt_hmset);
extern void _hash_multiset_cstr_hash(const void* cpv_input, void* pv_output);
extern void _hash_multiset_cstr_less(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _hash_map_int_key_hash(const void* cpv_input, void* pv_output);
extern void _hash_multimap_int_key_hash(const void* cpv_input, void* pv_output);
extern void _hash_map_cstl_hash(const void* cpv_input, void* pv_output);
extern void _hash_multimap_cstl_hash(const void* cpv_input, void* pv_output);
extern void _print_hash_map_cstl(const hash_map_t* cpt_hmap);
extern void _print_hash_multimap_cstl(const hash_multimap_t* cpt_hmmap);
extern void _print_hash_map_cstr(const hash_map_t* cpt_hmap);
extern void _print_hash_multimap_cstr(const hash_multimap_t* cpt_hmmap);
extern void _hash_map_cstr_hash(const void* cpv_input, void* pv_output);
extern void _hash_map_cstr_less(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _hash_multimap_cstr_hash(const void* cpv_input, void* pv_output);
extern void _hash_multimap_cstr_less(
    const void* cpv_first, const void* cpv_second, void* pv_output);

#ifdef __cplusplus
}
#endif

#endif /* _TEST_HASHTABLE_H */
/** eof **/

