/*
 *  The interface of hashtable test.
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

#ifndef _TEST_HASHTABLE_H
#define _TEST_HASHTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/
#include "chash_set.h"

/** constant declaration and macro section **/
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
extern void _print_hash_sample(const hash_set_t* cpt_hset);
extern void _hash_sample_init(const void* cpv_input, void* pv_output);
extern void _hash_sample_copy(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _hash_sample_less(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _hash_sample_destroy(const void* cpv_input, void* pv_output);
extern void _hash_sample_great(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _hash_set_sample_hash(const void* cpv_input, void* pv_output);
extern void _print_hash_set_cstl(const hash_set_t* cpt_hset);
extern void _hash_set_cstl_hash(const void* cpv_input, void* pv_output);
extern void _hash_set_int_hash(const void* cpv_input, void* pv_output);

#ifdef __cplusplus
}
#endif

#endif /* _TEST_HASHTABLE_H */
/** eof **/

