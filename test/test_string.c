/*
 *  The implementation of string test.
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
#include "cstring.h"
#include "test_string.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_basic_string(void)
{
    basic_string_t t_str = create_basic_string(char);
    basic_string_t t_str2 = create_basic_string(char);
    char ac_buffer[100] = "abcdefghij";
    basic_string_iterator_t t_begin;
    basic_string_iterator_t t_end;
    basic_string_iterator_t t_iterator;
    char c_char;
    basic_string_t t_str3;
    string_t t_str4;
    FILE* fp_stream = NULL;

    basic_string_init_cstr(&t_str, ac_buffer);

    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------------\n");

    t_begin = basic_string_begin(&t_str);
    t_end = basic_string_end(&t_str);
    for(t_iterator = t_begin;
        !iterator_equal(t_iterator, t_end);
        t_iterator = iterator_next(t_iterator))
    {
        iterator_get_value(t_iterator, &c_char);
        printf("%c ", c_char);
    }
    printf("\n");
    t_end = iterator_prev_n(t_end, 3);
    t_begin = iterator_next_n(t_begin, 2);
    c_char = 'z';
    for(t_iterator = t_end;
        !iterator_equal(t_iterator, t_begin);
        t_iterator = iterator_prev(t_iterator))
    {
        iterator_set_value(t_iterator, &c_char);
        c_char--;
    }
    t_begin = basic_string_begin(&t_str);
    t_end = basic_string_end(&t_str);
    for(t_iterator = t_begin;
        !iterator_equal(t_iterator, t_end);
        t_iterator = iterator_next(t_iterator))
    {
        printf("%c ", *(char*)iterator_get_pointer(t_iterator));
    }
    printf("\n");

    printf("------------------------------------------\n");
    basic_string_init_copy_substring(&t_str2, &t_str, 0, 1);
    printf("str2 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str2),
        basic_string_length(&t_str2),
        basic_string_max_size(&t_str2),
        basic_string_capacity(&t_str2),
        basic_string_empty(&t_str2));
    if(basic_string_c_str(&t_str2) != NULL)
    {
        printf("str2 - c_str: %s\n", (char*)basic_string_c_str(&t_str2));
    }
    else
    {
        printf("str2 - c_str: NULL\n");
    }
    printf("str2 - data: %s\n", (char*)basic_string_data(&t_str2));

    printf("------------------------------------------\n");
    basic_string_copy(&t_str, ac_buffer, 10, 0);
    printf("buffer:%s\n", ac_buffer);
    basic_string_copy(&t_str, ac_buffer, 5, 3);
    printf("buffer:%s\n", ac_buffer);
    basic_string_copy(&t_str, ac_buffer, 0, 9);
    printf("buffer:%s\n", ac_buffer);
    basic_string_copy(&t_str, ac_buffer, NPOS, 5);
    printf("buffer:%s\n", ac_buffer);

    printf("------------------------------------------\n");
    printf("t_str[0]:%s\n", (const char*)basic_string_at(&t_str, 0));
    printf("t_str[3]:%s\n", (const char*)basic_string_at(&t_str, 3));
    printf("t_str[9]:%s\n", (const char*)basic_string_at(&t_str, 9));

    printf("------------------------------------------\n");
    printf("compare result:%d\n", 
        basic_string_compare_substring_subcstr(&t_str, 0, NPOS, "abcvwxyzij", NPOS));
    printf("compare result:%d\n", 
        basic_string_compare_substring_subcstr(&t_str, 0, NPOS, "abcvw", NPOS));
    printf("compare result:%d\n", 
        basic_string_compare_substring_subcstr(&t_str, 0, NPOS, "abcvwxyzijl", NPOS));
    printf("compare result:%d\n", 
        basic_string_compare_substring_subcstr(&t_str, 0, 5, "abcvwxyzij", NPOS));
    printf("compare result:%d\n", 
        basic_string_compare_substring_subcstr(&t_str, 0, 5, "abcvwxyzij", 4));
    printf("compare result:%d\n", 
        basic_string_compare_substring_subcstr(&t_str, 0, 5, "abcvwxyzij", 5));
    printf("compare result:%d\n", 
        basic_string_compare_substring_subcstr(&t_str, 5, 3, "abcvwxyzij", NPOS));
    printf("compare result:%d\n", 
        basic_string_compare_substring_subcstr(&t_str, 5, 3, "xyzij", NPOS));
    printf("compare result:%d\n", 
        basic_string_compare_substring_subcstr(&t_str, 5, 3, "xyzij", 3));
    printf("compare result:%d\n", 
        basic_string_compare_substring_subcstr(&t_str, 5, 3, "zij", 2));
    printf("compare result:%d\n", 
        basic_string_compare_substring_subcstr(&t_str, 5, 3, "zij", 0));
    printf("compare result:%d\n", 
        basic_string_compare_substring_subcstr(&t_str, 5, 0, "zij", 0));
    printf("------------------------------------------\n");
    printf("compare result:%d\n", 
        basic_string_compare_cstr(&t_str, "abcvwxyzij"));
    printf("compare result:%d\n", 
        basic_string_compare_cstr(&t_str, "abcvwxyzi"));
    printf("compare result:%d\n", 
        basic_string_compare_cstr(&t_str, "abcvwxyziju"));
    printf("compare result:%d\n", 
        basic_string_compare_cstr(&t_str, "Abcvwxyziju"));
    printf("compare result:%d\n", 
        basic_string_compare_cstr(&t_str, "{bcvw"));
    printf("------------------------------------------\n");
    basic_string_destroy(&t_str2);
    basic_string_init_copy(&t_str2, &t_str);
    printf("compare result:%d\n", 
        basic_string_compare_substring_substring(&t_str, 0, NPOS, &t_str2, 0, NPOS));
    printf("compare result:%d\n", 
        basic_string_compare_substring_substring(&t_str, 4, NPOS, &t_str2, 0, NPOS));
    printf("compare result:%d\n", 
        basic_string_compare_substring_substring(&t_str, 0, 3, &t_str2, 0, NPOS));
    printf("compare result:%d\n", 
        basic_string_compare_substring_substring(&t_str, 0, NPOS, &t_str2, 5, NPOS));
    printf("compare result:%d\n", 
        basic_string_compare_substring_substring(&t_str, 0, NPOS, &t_str2, 0, 7));
    printf("compare result:%d\n", 
        basic_string_compare_substring_substring(&t_str, 6, 2, &t_str2, 6, 2));
    printf("------------------------------------------\n");
    basic_string_destroy(&t_str2);
    basic_string_init_copy_substring(&t_str2, &t_str, 3, 5);
    printf("compare result:%d\n", 
        basic_string_compare_substring_string(&t_str, 0, NPOS, &t_str2));
    printf("compare result:%d\n", 
        basic_string_compare_substring_string(&t_str, 3, NPOS, &t_str2));
    printf("compare result:%d\n", 
        basic_string_compare_substring_string(&t_str, 3, 3, &t_str2));
    printf("compare result:%d\n", 
        basic_string_compare_substring_string(&t_str, 3, 5, &t_str2));
    printf("compare result:%d\n", 
        basic_string_compare_substring_string(&t_str, 5, 5, &t_str2));
    printf("------------------------------------------\n");
    basic_string_destroy(&t_str2);
    basic_string_init_copy(&t_str2, &t_str);
    printf("compare result:%d\n", 
        basic_string_compare(&t_str, &t_str2));
    *(char*)basic_string_at(&t_str2, 0) = 'm';
    printf("compare result:%d\n", 
        basic_string_compare(&t_str, &t_str2));
    *(char*)basic_string_at(&t_str2, 0) = 'A';
    printf("compare result:%d\n", 
        basic_string_compare(&t_str, &t_str2));
    printf("------------------------------------------\n");
    basic_string_destroy(&t_str2);
    basic_string_init_copy(&t_str2, &t_str);
    printf("equal:%d, not equal:%d, less:%d, less equal:%d, great:%d, great equal:%d\n",
        basic_string_equal(&t_str, &t_str2),
        basic_string_not_equal(&t_str, &t_str2),
        basic_string_less(&t_str, &t_str2),
        basic_string_less_equal(&t_str, &t_str2),
        basic_string_great(&t_str, &t_str2),
        basic_string_great_equal(&t_str, &t_str2));
    basic_string_push_back(&t_str, 'e');
    printf("equal:%d, not equal:%d, less:%d, less equal:%d, great:%d, great equal:%d\n",
        basic_string_equal(&t_str, &t_str2),
        basic_string_not_equal(&t_str, &t_str2),
        basic_string_less(&t_str, &t_str2),
        basic_string_less_equal(&t_str, &t_str2),
        basic_string_great(&t_str, &t_str2),
        basic_string_great_equal(&t_str, &t_str2));
    basic_string_push_back(&t_str2, 'e');
    basic_string_push_back(&t_str2, 'f');
    printf("equal:%d, not equal:%d, less:%d, less equal:%d, great:%d, great equal:%d\n",
        basic_string_equal(&t_str, &t_str2),
        basic_string_not_equal(&t_str, &t_str2),
        basic_string_less(&t_str, &t_str2),
        basic_string_less_equal(&t_str, &t_str2),
        basic_string_great(&t_str, &t_str2),
        basic_string_great_equal(&t_str, &t_str2));
    *(char*)basic_string_at(&t_str, 0) = 'A';
    printf("equal:%d, not equal:%d, less:%d, less equal:%d, great:%d, great equal:%d\n",
        basic_string_equal(&t_str, &t_str2),
        basic_string_not_equal(&t_str, &t_str2),
        basic_string_less(&t_str, &t_str2),
        basic_string_less_equal(&t_str, &t_str2),
        basic_string_great(&t_str, &t_str2),
        basic_string_great_equal(&t_str, &t_str2));
    *(char*)basic_string_at(&t_str2, 0) = 'A';
    *(char*)basic_string_at(&t_str2, 5) = 'Z';
    printf("equal:%d, not equal:%d, less:%d, less equal:%d, great:%d, great equal:%d\n",
        basic_string_equal(&t_str, &t_str2),
        basic_string_not_equal(&t_str, &t_str2),
        basic_string_less(&t_str, &t_str2),
        basic_string_less_equal(&t_str, &t_str2),
        basic_string_great(&t_str, &t_str2),
        basic_string_great_equal(&t_str, &t_str2));
    printf("str1:%s\n", (char*)basic_string_at(&t_str, 0));
    printf("str2:%s\n", (char*)basic_string_at(&t_str2, 0));
    printf("------------------------------------------\n");
    printf("equal:%d, not equal:%d, less:%d, less equal:%d, great:%d, great equal:%d\n",
        basic_string_equal_cstr(&t_str, "Abcvwxyzije"),
        basic_string_not_equal_cstr(&t_str, "Abcvwxyzije"),
        basic_string_less_cstr(&t_str, "Abcvwxyzije"),
        basic_string_less_equal_cstr(&t_str, "Abcvwxyzije"),
        basic_string_great_cstr(&t_str, "Abcvwxyzije"),
        basic_string_great_equal_cstr(&t_str, "Abcvwxyzije"));
    printf("equal:%d, not equal:%d, less:%d, less equal:%d, great:%d, great equal:%d\n",
        basic_string_equal_cstr(&t_str, "Abcvwxyzij"),
        basic_string_not_equal_cstr(&t_str, "Abcvwxyzij"),
        basic_string_less_cstr(&t_str, "Abcvwxyzij"),
        basic_string_less_equal_cstr(&t_str, "Abcvwxyzij"),
        basic_string_great_cstr(&t_str, "Abcvwxyzij"),
        basic_string_great_equal_cstr(&t_str, "Abcvwxyzij"));
    printf("equal:%d, not equal:%d, less:%d, less equal:%d, great:%d, great equal:%d\n",
        basic_string_equal_cstr(&t_str, "Abcvwxyzijef"),
        basic_string_not_equal_cstr(&t_str, "Abcvwxyzijef"),
        basic_string_less_cstr(&t_str, "Abcvwxyzijef"),
        basic_string_less_equal_cstr(&t_str, "Abcvwxyzijef"),
        basic_string_great_cstr(&t_str, "Abcvwxyzijef"),
        basic_string_great_equal_cstr(&t_str, "Abcvwxyzijef"));
    printf("equal:%d, not equal:%d, less:%d, less equal:%d, great:%d, great equal:%d\n",
        basic_string_equal_cstr(&t_str, "abcvwxyzije"),
        basic_string_not_equal_cstr(&t_str, "abcvwxyzije"),
        basic_string_less_cstr(&t_str, "abcvwxyzije"),
        basic_string_less_equal_cstr(&t_str, "abcvwxyzije"),
        basic_string_great_cstr(&t_str, "abcvwxyzije"),
        basic_string_great_equal_cstr(&t_str, "abcvwxyzije"));
    printf("equal:%d, not equal:%d, less:%d, less equal:%d, great:%d, great equal:%d\n",
        basic_string_equal_cstr(&t_str, "AbcvwZyzije"),
        basic_string_not_equal_cstr(&t_str, "AbcvwZyzije"),
        basic_string_less_cstr(&t_str, "AbcvwZyzije"),
        basic_string_less_equal_cstr(&t_str, "AbcvwZyzije"),
        basic_string_great_cstr(&t_str, "AbcvwZyzije"),
        basic_string_great_equal_cstr(&t_str, "AbcvwZyzije"));
    printf("------------------------------------------\n");
    t_str3 = basic_string_substr(&t_str, 5, NPOS);
    printf("str3:%s\n", (char*)basic_string_at(&t_str3, 0));
    printf("------------------------------------------\n");
    basic_string_connect(&t_str, &t_str3);
    printf("str:%s\n", (char*)basic_string_at(&t_str, 0));
    printf("%d, %d\n", basic_string_size(&t_str), vector_size(&t_str._t_vector));
    basic_string_connect_cstr(&t_str, "[]{}()<>");
    printf("str:%s\n", (char*)basic_string_at(&t_str, 0));
    printf("%d, %d\n", basic_string_size(&t_str), vector_size(&t_str._t_vector));
    basic_string_connect_cstr(&t_str, "");
    printf("str:%s\n", (char*)basic_string_at(&t_str, 0));
    printf("%d, %d\n", basic_string_size(&t_str), vector_size(&t_str._t_vector));
    basic_string_connect_elem(&t_str, '$');
    printf("str:%s\n", (char*)basic_string_at(&t_str, 0));
    printf("%d, %d\n", basic_string_size(&t_str), vector_size(&t_str._t_vector));
    basic_string_connect_elem(&t_str, '\0');
    printf("str:%s\n", (char*)basic_string_at(&t_str, 0));
    printf("%d, %d\n", basic_string_size(&t_str), vector_size(&t_str._t_vector));
    printf("------------------------------------------\n");
    printf("find position:%u\n", basic_string_find_subcstr(&t_str, "zijexy", 0, NPOS));
    printf("find position:%u\n", basic_string_find_subcstr(&t_str, "zijexy", 8, NPOS));
    printf("find position:%u\n", basic_string_find_subcstr(&t_str, "zijexy", 8, 4));
    printf("find position:%u\n", basic_string_find_subcstr(&t_str, "zijexy", 8, 0));
    printf("find position:%u\n", basic_string_find_subcstr(&t_str, "zijexy", 24, 5));
    printf("find position:%u\n", basic_string_find_subcstr(&t_str, "zijexy", 4, 100));
    printf("find position:%u\n", basic_string_find_subcstr(&t_str, "", 4, 7));
    printf("find position:%u\n", basic_string_find_subcstr(&t_str, "", 0, 7));
    printf("------------------------------------------\n");
    printf("find position:%u\n", basic_string_find_cstr(&t_str, "zije", 0));
    printf("find position:%u\n", basic_string_find_cstr(&t_str, "zije", 8));
    printf("find position:%u\n", basic_string_find_cstr(&t_str, "zije", 18));
    printf("find position:%u\n", basic_string_find_cstr(&t_str, "", 0));
    printf("------------------------------------------\n");
    printf("find position:%u\n", basic_string_find(&t_str, &t_str3, 0));
    printf("find position:%u\n", basic_string_find(&t_str, &t_str3, 8));
    printf("find position:%u\n", basic_string_find(&t_str, &t_str3, 18));
    printf("------------------------------------------\n");
    printf("find position:%u\n", basic_string_find_elem(&t_str, 'x', 0));
    printf("find position:%u\n", basic_string_find_elem(&t_str, 'x', 8));
    printf("find position:%u\n", basic_string_find_elem(&t_str, 'x', 18));
    printf("find position:%u\n", basic_string_find_elem(&t_str, 'p', 0));
    printf("find position:%u\n", basic_string_find_elem(&t_str, '\0', 0));
    printf("find position:%u\n", basic_string_find_elem(&t_str, 'j', 26));
    printf("------------------------------------------\n");
    printf("find position:%u\n", basic_string_rfind_subcstr(&t_str, "ije", NPOS, NPOS));
    printf("find position:%u\n", basic_string_rfind_subcstr(&t_str, "ije", 13, NPOS));
    printf("find position:%u\n", basic_string_rfind_subcstr(&t_str, "ije", NPOS, 5));
    printf("find position:%u\n", basic_string_rfind_subcstr(&t_str, "zijexy", NPOS, NPOS));
    printf("find position:%u\n", basic_string_rfind_subcstr(&t_str, "zijexy", NPOS, 0));
    printf("find position:%u\n", basic_string_rfind_subcstr(&t_str, "zijexy", 0, NPOS));
    printf("find position:%u\n", basic_string_rfind_subcstr(&t_str, "", 20, 7));
    printf("find position:%u\n", basic_string_rfind_subcstr(&t_str, "ufo", NPOS, NPOS));
    printf("------------------------------------------\n");
    printf("find position:%u\n", basic_string_rfind_cstr(&t_str, "zije", 0));
    printf("find position:%u\n", basic_string_rfind_cstr(&t_str, "zije", 8));
    printf("find position:%u\n", basic_string_rfind_cstr(&t_str, "zije", 18));
    printf("find position:%u\n", basic_string_rfind_cstr(&t_str, "ufo", NPOS));
    printf("find position:%u\n", basic_string_rfind_cstr(&t_str, "", 0));
    printf("------------------------------------------\n");
    printf("find position:%u\n", basic_string_rfind(&t_str, &t_str3, 0));
    printf("find position:%u\n", basic_string_rfind(&t_str, &t_str3, 8));
    printf("find position:%u\n", basic_string_rfind(&t_str, &t_str3, 18));
    printf("------------------------------------------\n");
    printf("find position:%u\n", basic_string_rfind_elem(&t_str, 'x', 0));
    printf("find position:%u\n", basic_string_rfind_elem(&t_str, 'x', 8));
    printf("find position:%u\n", basic_string_rfind_elem(&t_str, 'x', 18));
    printf("find position:%u\n", basic_string_rfind_elem(&t_str, 'p', NPOS));
    printf("find position:%u\n", basic_string_rfind_elem(&t_str, '\0', NPOS));
    printf("find position:%u\n", basic_string_rfind_elem(&t_str, 'j', 3));
    printf("------------------------------------------\n");
    printf("find position:%u\n", 
        basic_string_find_first_of_subcstr(&t_str, "j?{>", 0, NPOS));
    printf("find position:%u\n", 
        basic_string_find_first_of_subcstr(&t_str, "j?{>", 16, NPOS));
    printf("find position:%u\n", 
        basic_string_find_first_of_subcstr(&t_str, "j?{>", 20, NPOS));
    printf("find position:%u\n", 
        basic_string_find_first_of_subcstr(&t_str, "+?r$@0~\\", 0, NPOS));
    printf("find position:%u\n", 
        basic_string_find_first_of_subcstr(&t_str, "+?r@0~\\", 0, NPOS));
    printf("find position:%u\n", 
        basic_string_find_first_of_subcstr(&t_str, "", 0, NPOS));
    printf("find position:%u\n", 
        basic_string_find_first_of_subcstr(&t_str, "j?{>", 20, 2));
    printf("------------------------------------------\n");
    printf("find position:%u\n", 
        basic_string_find_first_of_cstr(&t_str, "j?{>", 0));
    printf("find position:%u\n", 
        basic_string_find_first_of_cstr(&t_str, "j?{>", 16));
    printf("find position:%u\n", 
        basic_string_find_first_of_cstr(&t_str, "j?{>", 20));
    printf("find position:%u\n", 
        basic_string_find_first_of_cstr(&t_str, "+?r$@0~\\", 0));
    printf("find position:%u\n", 
        basic_string_find_first_of_cstr(&t_str, "+?r@0~\\", 0));
    printf("find position:%u\n", 
        basic_string_find_first_of_cstr(&t_str, "", 0));
    printf("------------------------------------------\n");
    basic_string_destroy(&t_str3);
    basic_string_init_cstr(&t_str3, "j?{>");
    printf("find position:%u\n", 
        basic_string_find_first_of(&t_str, &t_str3, 0));
    printf("find position:%u\n", 
        basic_string_find_first_of(&t_str, &t_str3, 10));
    printf("find position:%u\n", 
        basic_string_find_first_of(&t_str, &t_str3, 18));
    printf("find position:%u\n", 
        basic_string_find_first_of(&t_str, &t_str3, 20));
    printf("------------------------------------------\n");
    printf("find position:%u\n", 
        basic_string_find_first_not_of_subcstr(&t_str, "j?{>", 0, NPOS));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_subcstr(&t_str, "Abcj?{>", 0, NPOS));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_subcstr(&t_str, "j?{>", 9, NPOS));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_subcstr(&t_str, "+?r$i@0~\\", 8, 4));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_subcstr(&t_str, "", 0, NPOS));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_subcstr(&t_str, "j?{>", 20, 0));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_subcstr(&t_str, "70oiwa$", 25, NPOS));
    printf("------------------------------------------\n");
    printf("find position:%u\n", 
        basic_string_find_first_not_of_cstr(&t_str, "j?{>", 0));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_cstr(&t_str, "Abcj?{>", 0));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_cstr(&t_str, "j?{>", 9));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_cstr(&t_str, "+?r$i@0~\\", 8));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_cstr(&t_str, "", 0));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_cstr(&t_str, "j?{>", 20));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_cstr(&t_str, "70oiwa$", 25));
    printf("------------------------------------------\n");
    printf("find position:%u\n", 
        basic_string_find_first_not_of(&t_str, &t_str3, 0));
    printf("find position:%u\n", 
        basic_string_find_first_not_of(&t_str, &t_str3, 15));
    printf("find position:%u\n", 
        basic_string_find_first_not_of(&t_str, &t_str3, 19));
    printf("find position:%u\n", 
        basic_string_find_first_not_of(&t_str, &t_str3, 25));
    printf("------------------------------------------\n");
    printf("find position:%u\n", 
        basic_string_find_first_not_of_elem(&t_str, '?', 0));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_elem(&t_str, 'j', 15));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_elem(&t_str, '{', 19));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_elem(&t_str, '$', 25));
    printf("find position:%u\n", 
        basic_string_find_first_not_of_elem(&t_str, '\0', 20));
    printf("------------------------------------------\n");
    printf("find position:%u\n", 
        basic_string_find_last_of_subcstr(&t_str, "j?{>", NPOS, NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_of_subcstr(&t_str, "j?{>", 22, NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_of_subcstr(&t_str, "j?{>", 18, NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_of_subcstr(&t_str, "+?r$@0~\\", NPOS, NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_of_subcstr(&t_str, "+?r@0~\\", NPOS, NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_of_subcstr(&t_str, "", NPOS, NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_of_subcstr(&t_str, "j?{>", 20, 2));
    printf("------------------------------------------\n");
    printf("find position:%u\n", 
        basic_string_find_last_of_cstr(&t_str, "j?{>", NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_of_cstr(&t_str, "j?{>", 22));
    printf("find position:%u\n", 
        basic_string_find_last_of_cstr(&t_str, "j?{>", 18));
    printf("find position:%u\n", 
        basic_string_find_last_of_cstr(&t_str, "+?r$@0~\\", NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_of_cstr(&t_str, "+?r@0~\\", NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_of_cstr(&t_str, "", NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_of_cstr(&t_str, "j?{>", 20));
    printf("------------------------------------------\n");
    printf("find position:%u\n", 
        basic_string_find_last_of(&t_str, &t_str3, NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_of(&t_str, &t_str3, 22));
    printf("find position:%u\n", 
        basic_string_find_last_of(&t_str, &t_str3, 18));
    printf("find position:%u\n", 
        basic_string_find_last_of(&t_str, &t_str3, 26));
    printf("------------------------------------------\n");
    printf("find position:%u\n", 
        basic_string_find_last_not_of_subcstr(&t_str, "j?{>", NPOS, NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_subcstr(&t_str, "$bcj?{>", NPOS, NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_subcstr(&t_str, "j?{>", 9, NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_subcstr(&t_str, "+?r$i@0~\\", 8, 4));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_subcstr(&t_str, "", NPOS, NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_subcstr(&t_str, "j?{>", 20, 0));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_subcstr(&t_str, "70oiwa$", 25, NPOS));
    printf("------------------------------------------\n");
    printf("find position:%u\n", 
        basic_string_find_last_not_of_cstr(&t_str, "j?{>", NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_cstr(&t_str, "$bcj?{>", NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_cstr(&t_str, "j?{>", 9));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_cstr(&t_str, "+?r$i@0~\\", 8));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_cstr(&t_str, "", NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_cstr(&t_str, "j?{>", 20));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_cstr(&t_str, "70oiwa$", 25));
    printf("------------------------------------------\n");
    printf("find position:%u\n", 
        basic_string_find_last_not_of(&t_str, &t_str3, NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_not_of(&t_str, &t_str3, 24));
    printf("find position:%u\n", 
        basic_string_find_last_not_of(&t_str, &t_str3, 18));
    printf("find position:%u\n", 
        basic_string_find_last_not_of(&t_str, &t_str3, 9));
    printf("------------------------------------------\n");
    printf("find position:%u\n", 
        basic_string_find_last_not_of_elem(&t_str, 'A', 0));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_elem(&t_str, 'j', 15));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_elem(&t_str, '{', 19));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_elem(&t_str, '$', NPOS));
    printf("find position:%u\n", 
        basic_string_find_last_not_of_elem(&t_str, '\0', 15));

    printf("------------------------------------------\n");
    printf("str3 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str3),
        basic_string_length(&t_str3),
        basic_string_max_size(&t_str3),
        basic_string_capacity(&t_str3),
        basic_string_empty(&t_str3));
    if(basic_string_c_str(&t_str3) != NULL)
    {
        printf("str3 - c_str: %s\n", (char*)basic_string_c_str(&t_str3));
    }
    else
    {
        printf("str3 - c_str: NULL\n");
    }
    printf("str3 - data: %s\n", (char*)basic_string_data(&t_str3));

    basic_string_clear(&t_str3);
    printf("\n");
    printf("str3 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str3),
        basic_string_length(&t_str3),
        basic_string_max_size(&t_str3),
        basic_string_capacity(&t_str3),
        basic_string_empty(&t_str3));
    if(basic_string_c_str(&t_str3) != NULL)
    {
        printf("str3 - c_str: %s\n", (char*)basic_string_c_str(&t_str3));
    }
    else
    {
        printf("str3 - c_str: NULL\n");
    }
    printf("str3 - data: %s\n", (char*)basic_string_data(&t_str3));

    printf("------------------------------------------\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("\n");
    printf("str2 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str2),
        basic_string_length(&t_str2),
        basic_string_max_size(&t_str2),
        basic_string_capacity(&t_str2),
        basic_string_empty(&t_str2));
    if(basic_string_c_str(&t_str2) != NULL)
    {
        printf("str2 - c_str: %s\n", (char*)basic_string_c_str(&t_str2));
    }
    else
    {
        printf("str2 - c_str: NULL\n");
    }
    printf("str2 - data: %s\n", (char*)basic_string_data(&t_str2));

    basic_string_swap(&t_str, &t_str2);
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("\n");
    printf("str2 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str2),
        basic_string_length(&t_str2),
        basic_string_max_size(&t_str2),
        basic_string_capacity(&t_str2),
        basic_string_empty(&t_str2));
    if(basic_string_c_str(&t_str2) != NULL)
    {
        printf("str2 - c_str: %s\n", (char*)basic_string_c_str(&t_str2));
    }
    else
    {
        printf("str2 - c_str: NULL\n");
    }
    printf("str2 - data: %s\n", (char*)basic_string_data(&t_str2));

    basic_string_reserve(&t_str, 10);
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    basic_string_reserve(&t_str, 50);
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    basic_string_resize(&t_str, 5, '*');
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    basic_string_resize(&t_str, 15, '?');
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));

    basic_string_push_back(&t_str, 'B');
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    basic_string_push_back(&t_str, '\0');
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));

    basic_string_assign(&t_str, &t_str2);
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    basic_string_assign_substring(&t_str, &t_str2, 10, NPOS);
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));

    basic_string_assign_subcstr(&t_str, "ABCKEFGHIJKLMN", 7);
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    basic_string_assign_subcstr(&t_str, "", 7);
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    basic_string_assign_cstr(&t_str, "Fedora 9");
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));

    basic_string_assign_elem(&t_str, 5, 'M');
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    basic_string_assign_elem(&t_str, 0, 'J');
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));

    t_begin = basic_string_begin(&t_str2);
    t_end = basic_string_rbegin(&t_str2);
    t_begin = iterator_next_n(t_begin, 12);
    basic_string_assign_range(&t_str, t_begin, t_end);
    printf("\n");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));

    printf("------------------------------------\n");
    basic_string_append_subcstr(&t_str, "Redhat Fedora 9", 7);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_append_cstr(&t_str, "Fedora 10");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_append_substring(&t_str, &t_str2, 4, 9);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_append(&t_str, &t_str2);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_begin = basic_string_begin(&t_str2);
    t_end = basic_string_rbegin(&t_str2);
    t_begin = iterator_next(t_begin);
    t_end = iterator_prev_n(t_end, 4);
    basic_string_append_range(&t_str, t_begin, t_end);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
        basic_string_size(&t_str),
        basic_string_length(&t_str),
        basic_string_max_size(&t_str),
        basic_string_capacity(&t_str),
        basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_clear(&t_str);
    basic_string_append_elem(&t_str, 3, '%');
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_iterator = basic_string_insert(&t_str, basic_string_end(&t_str), 'H');
    /*printf("%c\n", *(char*)iterator_get_pointer(&t_iterator));*/
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_begin = basic_string_begin(&t_str);
    t_begin = iterator_next(t_begin);
    t_iterator = basic_string_insert(&t_str, t_begin, 'N');
    printf("%c\n", *(char*)iterator_get_pointer(t_iterator));
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_insert_elem(&t_str, 1, 4, 'U');
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_insert_elem(&t_str, 2, 4, '+');
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_insert_elem(&t_str, 3, 0, '&');
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_insert_elem(&t_str, basic_string_size(&t_str), 3, '$');
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_iterator = basic_string_begin(&t_str);
    t_begin = basic_string_begin(&t_str2);
    t_end = basic_string_end(&t_str2);
    basic_string_insert_range(&t_str, t_iterator, t_begin, t_end);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_iterator = basic_string_begin(&t_str);
    t_iterator = iterator_next_n(t_iterator, 10);
    t_begin = basic_string_begin(&t_str2);
    t_begin = iterator_next_n(t_begin, 10);
    t_end = basic_string_end(&t_str2);
    basic_string_insert_range(&t_str, t_iterator, t_begin, t_end);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_iterator = basic_string_end(&t_str);
    t_begin = basic_string_begin(&t_str2);
    t_begin = iterator_next_n(t_begin, 10);
    t_end = basic_string_end(&t_str2);
    t_end = iterator_prev_n(t_end, 10);
    basic_string_insert_range(&t_str, t_iterator, t_begin, t_end);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_clear(&t_str);
    basic_string_insert_string(&t_str, 0, &t_str2);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_insert_string(&t_str, 4, &t_str2);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_insert_string(&t_str, basic_string_size(&t_str), &t_str2);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_clear(&t_str);
    basic_string_insert_substring(&t_str, 0, &t_str2, 0, 4);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_insert_substring(&t_str, 3, &t_str2, 20, NPOS);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_insert_substring(&t_str, basic_string_size(&t_str), &t_str2, 10, 6);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_clear(&t_str);
    basic_string_insert_subcstr(&t_str, 0, "XYZNOY LLPPLWO", 8);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_insert_subcstr(&t_str, 7, "XYZNOY LLPPLWO", 4);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_insert_subcstr(&t_str, basic_string_size(&t_str), "XYZNOY LLPPLWO", 10);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_clear(&t_str);
    basic_string_insert_cstr(&t_str, 0, "XYZNOY LLPPLWO");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_insert_cstr(&t_str, 6, "<XML>");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_insert_cstr(&t_str, basic_string_size(&t_str), "(unix)");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_iterator = basic_string_erase(&t_str, basic_string_begin(&t_str));
    printf("%c\n", *(char*)iterator_get_pointer(t_iterator));
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_begin = basic_string_begin(&t_str);
    t_begin = iterator_next_n(t_begin, 4);
    t_iterator = basic_string_erase(&t_str, t_begin);
    printf("%c\n", *(char*)iterator_get_pointer(t_iterator));
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_iterator = basic_string_erase(&t_str, basic_string_rbegin(&t_str));
    printf("%d\n", iterator_equal(t_iterator, basic_string_end(&t_str)));
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_begin = basic_string_begin(&t_str);
    t_end = basic_string_begin(&t_str);
    t_end = iterator_next_n(t_end, 3);
    t_iterator = basic_string_erase_range(&t_str, t_begin, t_end);
    printf("%c\n", *(char*)iterator_get_pointer(t_iterator));
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_begin = basic_string_begin(&t_str);
    t_end = basic_string_rbegin(&t_str);
    t_begin = iterator_next_n(t_begin, 6);
    t_iterator = basic_string_erase_range(&t_str, t_begin, t_end);
    printf("%c\n", *(char*)iterator_get_pointer(t_iterator));
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_begin = basic_string_begin(&t_str);
    t_end = basic_string_end(&t_str);
    t_begin = iterator_next_n(t_begin, 2);
    t_iterator = basic_string_erase_range(&t_str, t_begin, t_end);
    printf("%d\n", iterator_equal(t_iterator, basic_string_end(&t_str)));
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_append_cstr(&t_str, "Windows 7, Fedora 10, Mac OS X");
    basic_string_erase_substring(&t_str, 0, 2);
    printf("%d\n", iterator_equal(t_iterator, basic_string_end(&t_str)));
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_erase_substring(&t_str, 5, 12);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_erase_substring(&t_str, 9, NPOS);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_erase_substring(&t_str, 0, NPOS);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_append_cstr(&t_str, "Windows 7, Fedora 10, Mac OS X");
    t_begin = basic_string_begin(&t_str);
    t_end = basic_string_end(&t_str);
    t_begin = iterator_next_n(t_begin, 9);
    basic_string_replace_range(
        &t_str, t_begin, t_end, basic_string_begin(&t_str2), basic_string_end(&t_str2));
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_begin = basic_string_begin(&t_str);
    t_end = basic_string_begin(&t_str);
    t_begin = iterator_next_n(t_begin, 3);
    t_end = iterator_next_n(t_end, 9);
    basic_string_range_replace_subcstr(
        &t_str, t_begin, t_end, "Redhat Linux 9.0", NPOS);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_begin = basic_string_begin(&t_str);
    t_end = basic_string_end(&t_str);
    t_begin = iterator_next_n(t_begin, 3);
    basic_string_range_replace_cstr(
        &t_str, t_begin, t_end, "IBM OS2");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_begin = basic_string_begin(&t_str);
    t_end = basic_string_end(&t_str);
    basic_string_range_replace_substring(
        &t_str, t_begin, t_end, &t_str2, 17, 8);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    t_begin = basic_string_begin(&t_str);
    t_end = basic_string_end(&t_str);
    t_begin = iterator_next_n(t_begin, 3);
    t_end = iterator_prev_n(t_end, 3);
    basic_string_range_replace(
        &t_str, t_begin, t_end, &t_str2);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_replace_subcstr(&t_str, 10, NPOS, "GNU is not unix", NPOS);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_replace_cstr(&t_str, 0, 13, "GNU/LINUX");
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_replace_substring(&t_str, 4, NPOS, &t_str2, 0, NPOS);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));
    printf("------------------------------------\n");
    basic_string_replace(&t_str, 0, NPOS, &t_str2);
    printf("str1 - size:%u, length:%u, max_size:%u, capacity:%u, empty:%d\n", 
            basic_string_size(&t_str),
            basic_string_length(&t_str),
            basic_string_max_size(&t_str),
            basic_string_capacity(&t_str),
            basic_string_empty(&t_str));
    if(basic_string_c_str(&t_str) != NULL)
    {
        printf("str1 - c_str: %s\n", (char*)basic_string_c_str(&t_str));
    }
    else
    {
        printf("str1 - c_str: NULL\n");
    }
    printf("str1 - data: %s\n", (char*)basic_string_data(&t_str));

    basic_string_destroy(&t_str);
    basic_string_destroy(&t_str2);
    basic_string_destroy(&t_str3);

    printf("------------------------------------\n");
    string_init(&t_str4);
    string_output(&t_str4, stdout);
    string_assign_cstr(&t_str4, "CSTL");
    string_output(&t_str4, stdout);
    printf("\n");
    string_connect_cstr(&t_str4, " ActiveSys.Wangbo");
    string_output(&t_str4, stderr);
    printf("\n");

    fp_stream = fopen("./test.d", "r");
    string_input(&t_str4, fp_stream);
    string_output(&t_str4, stdout);
    printf("\n");

    rewind(fp_stream);
    string_getline(&t_str4, fp_stream);
    string_output(&t_str4, stdout);
    printf("\n");

    rewind(fp_stream);
    string_getline_delimiter(&t_str4, fp_stream, ' ');
    string_output(&t_str4, stdout);
    printf("\n");

    fclose(fp_stream);
    string_destroy(&t_str4);
}

void test_string(int argc, char* argv[])
{
    string_t t_basename, t_filename, t_extname, t_tmpname, t_sffuix;
    int i = 0;
    size_t t_pos = 0;

    string_init_cstr(&t_sffuix, "tmp");
    string_init(&t_basename);
    string_init(&t_filename);
    string_init(&t_extname);
    string_init(&t_tmpname);

    for(i = 1; i < argc; ++i)
    {
        string_assign_cstr(&t_filename, argv[i]);

        t_pos = string_find_char(&t_filename, '.', 0);
        if(t_pos == NPOS)
        {
            string_assign(&t_tmpname, &t_filename);
            string_connect_char(&t_tmpname, '.');
            string_connect(&t_tmpname, &t_sffuix);
        }
        else
        {
            string_assign_substring(&t_basename, &t_filename, 0, t_pos);
            string_assign_substring(&t_extname, &t_filename, t_pos + 1, NPOS);

            string_assign(&t_tmpname, &t_filename);
            if(string_empty(&t_extname))
            {
                string_connect(&t_tmpname, &t_sffuix);
            }
            else if(string_equal(&t_extname, &t_sffuix))
            {
                string_replace_cstr(&t_tmpname, t_pos + 1, NPOS, "xxx");
            }
            else
            {
                string_replace(&t_tmpname, t_pos + 1, NPOS, &t_sffuix);
            }
        }

        printf("%s => %s\n", string_c_str(&t_filename), string_c_str(&t_tmpname));
    }

    string_destroy(&t_sffuix);
    string_destroy(&t_basename);
    string_destroy(&t_filename);
    string_destroy(&t_extname);
    string_destroy(&t_tmpname);
}

void test_string_getline(void)
{
    string_t t_delims, t_str;

    string_init_cstr(&t_delims, " \t,.:");
    string_init(&t_str);

    while(string_getline(&t_str, stdin))
    {
        size_t t_beginx, t_endinx;
        int i = 0;

        t_beginx = string_find_first_not_of(&t_str, &t_delims, 0);
        while(t_beginx != NPOS)
        {
            t_endinx = string_find_first_of(&t_str, &t_delims, t_beginx);
            if(t_endinx == NPOS)
            {
                t_endinx = string_length(&t_str);
            }

            for(i = t_endinx - 1; i >= (int)t_beginx; --i)
            {
                printf("%c", *string_at(&t_str, i));
            }
            printf(" ");

            t_beginx = string_find_first_not_of(&t_str, &t_delims, t_endinx);
        }
        printf("\n");
    }

    string_destroy(&t_delims);
    string_destroy(&t_str);
}

/** local function implementation section **/

/** eof **/

