/*
 *  The implementation of hashtable test.
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

/** include section **/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "cstl_types.h"
#include "cstl_alloc.h"
#include "cstl_iterator.h"

#include "cvector.h"
#include "cstl_hashtable_iterator.h"
#include "cstl_hashtable_private.h"
#include "chash_set.h"

#include "test_hashtable.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_hashtable(void)
{
    {
        hashtable_t t_ht = _create_hashtable(sizeof(int), "int");
        hashtable_t t_ht2 = _create_hashtable(sizeof(int), "int");
        int n_value = 200;

        _hashtable_init(&t_ht, 0, NULL, NULL, NULL);
        _hashtable_insert_equal(&t_ht, &n_value);
        printf("hashtable1 - size:%u, max_size:%u, bucket count:%u, empty:%d\n",
            _hashtable_size(&t_ht), _hashtable_max_size(&t_ht),
            _hashtable_bucket_count(&t_ht), _hashtable_empty(&t_ht));
        _hashtable_init_copy_range(
            &t_ht2, _hashtable_begin(&t_ht), _hashtable_begin(&t_ht), 0, NULL, NULL);
        printf("hashtable2 - size:%u, max_size:%u, bucket count:%u, empty:%d\n",
            _hashtable_size(&t_ht2), _hashtable_max_size(&t_ht2),
            _hashtable_bucket_count(&t_ht2), _hashtable_empty(&t_ht2));
        _hashtable_insert_equal_range(
            &t_ht2, _hashtable_end(&t_ht), _hashtable_end(&t_ht));
        printf("hashtable2 - size:%u, max_size:%u, bucket count:%u, empty:%d\n",
            _hashtable_size(&t_ht2), _hashtable_max_size(&t_ht2),
            _hashtable_bucket_count(&t_ht2), _hashtable_empty(&t_ht2));
        _hashtable_insert_unique_range(
            &t_ht2, _hashtable_end(&t_ht), _hashtable_end(&t_ht));
        printf("hashtable2 - size:%u, max_size:%u, bucket count:%u, empty:%d\n",
            _hashtable_size(&t_ht2), _hashtable_max_size(&t_ht2),
            _hashtable_bucket_count(&t_ht2), _hashtable_empty(&t_ht2));
        _hashtable_erase_range(
            &t_ht2, _hashtable_begin(&t_ht2), _hashtable_end(&t_ht2));
        printf("hashtable2 - size:%u, max_size:%u, bucket count:%u, empty:%d\n",
            _hashtable_size(&t_ht2), _hashtable_max_size(&t_ht2),
            _hashtable_bucket_count(&t_ht2), _hashtable_empty(&t_ht2));

        _hashtable_destroy(&t_ht);
        _hashtable_destroy(&t_ht2);
    }
    {
        hash_set_t t_hs = create_hash_set(int);
        iterator_t t_i;
        int i;

        hash_set_init(&t_hs, NULL);
        hash_set_insert(&t_hs, 59);
        hash_set_insert(&t_hs, 63);
        hash_set_insert(&t_hs, 108);
        hash_set_insert(&t_hs, 2);
        hash_set_insert(&t_hs, 53);
        hash_set_insert(&t_hs, 55);

        for(t_i = hash_set_begin(&t_hs);
            !iterator_equal(&t_i, hash_set_end(&t_hs));
            iterator_next(&t_i))
        {
            printf("%d ", *(int*)iterator_get_pointer(&t_i));
        }
        printf("\n");

        for(i = 0; i < 47; ++i)
        {
            hash_set_insert(&t_hs, i);
        }
        for(t_i = hash_set_begin(&t_hs);
            !iterator_equal(&t_i, hash_set_end(&t_hs));
            iterator_next(&t_i))
        {
            printf("%d ", *(int*)iterator_get_pointer(&t_i));
        }
        printf("\n");

        hash_set_destroy(&t_hs);
    }
}

/** local function implementation section **/

/** eof **/

