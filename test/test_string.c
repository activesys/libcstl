/*
 *  The implementation of string test.
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

/** include section **/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "cstring.h"
#include "test_string.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _printstring(const string_t* cpt_string);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_basic_string(void)
{
}

void test_string(int argc, char* argv[])
{
    /*create_string                     */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        _printstring(pt_string);
        string_destroy(pt_string);
    }
    /*string_init                       */
    /*string_init_cstr                  */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init_cstr(pt_string, "libcstl-2.0.0");
        _printstring(pt_string);
        string_destroy(pt_string);
    }
    /*string_init_subcstr               */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init_subcstr(pt_string, "libcstl-2.0.0", NPOS);
        _printstring(pt_string);
        string_destroy(pt_string);
    }
    /*string_init_char                  */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init_char(pt_string, 8, 'h');
        _printstring(pt_string);
        string_destroy(pt_string);
    }
    /*string_init_copy                  */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init_cstr(pt_stringex, "activesys.wb@gmail.com");
        _printstring(pt_stringex);
        string_init_copy(pt_string, pt_stringex);
        _printstring(pt_string);
        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_init_copy_substring        */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init_cstr(pt_stringex, "China");
        _printstring(pt_stringex);
        string_init_copy_substring(pt_string, pt_stringex, 1, NPOS);
        _printstring(pt_string);
        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_init_copy_range            */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init_cstr(pt_stringex, "CHINA");
        _printstring(pt_stringex);
        string_init_copy_range(pt_string, string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);
        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_destroy                    */
    /*string_c_str                      */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init_cstr(pt_string, "LIBCSTL-CSTRING");
        _printstring(pt_string);
        printf("c_str : %s\n", string_c_str(pt_string));
        printf("data  : %s\n", string_data(pt_string));
        string_destroy(pt_string);
    }
    /*string_data                       */
    /*string_copy                       */
    {
        string_t* pt_string = create_string();
        char sz_buf[31] = {'\0'};
        if(pt_string == NULL)
        {
            return;
        }
        string_init_cstr(pt_string, "test_string.c");
        _printstring(pt_string);
        string_copy(pt_string, sz_buf, 0, 0);
        puts(sz_buf);
        string_copy(pt_string, sz_buf, 5, 0);
        puts(sz_buf);
        memset(sz_buf, '\0', 31);
        string_copy(pt_string, sz_buf, 13, 0);
        puts(sz_buf);
        memset(sz_buf, '\0', 31);
        string_copy(pt_string, sz_buf, 40, 0);
        puts(sz_buf);
        memset(sz_buf, '\0', 31);
        string_copy(pt_string, sz_buf, NPOS, 0);
        puts(sz_buf);

        memset(sz_buf, '\0', 31);
        string_copy(pt_string, sz_buf, 0, 5);
        puts(sz_buf);
        memset(sz_buf, '\0', 31);
        string_copy(pt_string, sz_buf, 6, 5);
        puts(sz_buf);
        memset(sz_buf, '\0', 31);
        string_copy(pt_string, sz_buf, 8, 5);
        puts(sz_buf);
        memset(sz_buf, '\0', 31);
        string_copy(pt_string, sz_buf, 40, 5);
        puts(sz_buf);
        memset(sz_buf, '\0', 31);
        string_copy(pt_string, sz_buf, NPOS, 5);
        puts(sz_buf);
        string_destroy(pt_string);
    }
    /*string_size                       */
    /*string_length                     */
    /*string_empty                      */
    /*string_max_size                   */
    /*string_capacity                   */
    /*string_at                         */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init_cstr(pt_string, "CHINA");
        _printstring(pt_string);
        printf("%c\n", *string_at(pt_string, 0));
        printf("%c\n", *string_at(pt_string, 4));
        printf("%c\n", *string_at(pt_string, string_length(pt_string)));
        *string_at(pt_string, 4) = 'K';
        _printstring(pt_string);
        string_destroy(pt_string);
    }
    /*string_equal                      */
    {
        string_t* pt_string1 = create_string();
        string_t* pt_string2 = create_string();
        if(pt_string1 == NULL || pt_string2 == NULL)
        {
            return;
        }
        string_init(pt_string1);
        string_init(pt_string2);
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("equal : %d, not equal : %d, ",
            string_equal(pt_string1, pt_string2), string_not_equal(pt_string1, pt_string2));
        printf("less : %d, less equal : %d, ",
            string_less(pt_string1, pt_string2), string_less_equal(pt_string1, pt_string2));
        printf("greater : %d, greater equal : %d\n",
            string_greater(pt_string1, pt_string2), string_greater_equal(pt_string1, pt_string2));

        string_assign_cstr(pt_string1, "abc");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("equal : %d, not equal : %d, ",
            string_equal(pt_string1, pt_string2), string_not_equal(pt_string1, pt_string2));
        printf("less : %d, less equal : %d, ",
            string_less(pt_string1, pt_string2), string_less_equal(pt_string1, pt_string2));
        printf("greater : %d, greater equal : %d\n",
            string_greater(pt_string1, pt_string2), string_greater_equal(pt_string1, pt_string2));

        string_assign_cstr(pt_string2, "abc");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("equal : %d, not equal : %d, ",
            string_equal(pt_string1, pt_string2), string_not_equal(pt_string1, pt_string2));
        printf("less : %d, less equal : %d, ",
            string_less(pt_string1, pt_string2), string_less_equal(pt_string1, pt_string2));
        printf("greater : %d, greater equal : %d\n",
            string_greater(pt_string1, pt_string2), string_greater_equal(pt_string1, pt_string2));

        string_assign_cstr(pt_string1, "opq");
        string_assign_cstr(pt_string2, "xyz");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("equal : %d, not equal : %d, ",
            string_equal(pt_string1, pt_string2), string_not_equal(pt_string1, pt_string2));
        printf("less : %d, less equal : %d, ",
            string_less(pt_string1, pt_string2), string_less_equal(pt_string1, pt_string2));
        printf("greater : %d, greater equal : %d\n",
            string_greater(pt_string1, pt_string2), string_greater_equal(pt_string1, pt_string2));

        string_assign_cstr(pt_string1, "mn");
        string_assign_cstr(pt_string2, "mno");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("equal : %d, not equal : %d, ",
            string_equal(pt_string1, pt_string2), string_not_equal(pt_string1, pt_string2));
        printf("less : %d, less equal : %d, ",
            string_less(pt_string1, pt_string2), string_less_equal(pt_string1, pt_string2));
        printf("greater : %d, greater equal : %d\n",
            string_greater(pt_string1, pt_string2), string_greater_equal(pt_string1, pt_string2));

        string_assign_cstr(pt_string1, "u");
        string_assign_cstr(pt_string2, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("equal : %d, not equal : %d, ",
            string_equal(pt_string1, pt_string2), string_not_equal(pt_string1, pt_string2));
        printf("less : %d, less equal : %d, ",
            string_less(pt_string1, pt_string2), string_less_equal(pt_string1, pt_string2));
        printf("greater : %d, greater equal : %d\n",
            string_greater(pt_string1, pt_string2), string_greater_equal(pt_string1, pt_string2));

        string_destroy(pt_string1);
        string_destroy(pt_string2);
    }
    /*string_not_equal                  */
    /*string_less                       */
    /*string_less_equal                 */
    /*string_greater                      */
    /*string_greater_equal                */
    /*string_equal_cstr                 */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        _printstring(pt_string);
        puts("");
        printf("equal : %d, not equal : %d, ",
            string_equal_cstr(pt_string, ""), string_not_equal_cstr(pt_string, ""));
        printf("less : %d, less equal : %d, ",
            string_less_cstr(pt_string, ""), string_less_equal_cstr(pt_string, ""));
        printf("greater : %d, greater equal : %d\n",
            string_greater_cstr(pt_string, ""), string_greater_equal_cstr(pt_string, ""));

        string_assign_cstr(pt_string, "abc");
        _printstring(pt_string);
        puts("");
        printf("equal : %d, not equal : %d, ",
            string_equal_cstr(pt_string, ""), string_not_equal_cstr(pt_string, ""));
        printf("less : %d, less equal : %d, ",
            string_less_cstr(pt_string, ""), string_less_equal_cstr(pt_string, ""));
        printf("greater : %d, greater equal : %d\n",
            string_greater_cstr(pt_string, ""), string_greater_equal_cstr(pt_string, ""));

        _printstring(pt_string);
        puts("abc");
        printf("equal : %d, not equal : %d, ",
            string_equal_cstr(pt_string, "abc"), string_not_equal_cstr(pt_string, "abc"));
        printf("less : %d, less equal : %d, ",
            string_less_cstr(pt_string, "abc"), string_less_equal_cstr(pt_string, "abc"));
        printf("greater : %d, greater equal : %d\n",
            string_greater_cstr(pt_string, "abc"), string_greater_equal_cstr(pt_string, "abc"));

        string_assign_cstr(pt_string, "opq");
        _printstring(pt_string);
        puts("xyz");
        printf("equal : %d, not equal : %d, ",
            string_equal_cstr(pt_string, "xyz"), string_not_equal_cstr(pt_string, "xyz"));
        printf("less : %d, less equal : %d, ",
            string_less_cstr(pt_string, "xyz"), string_less_equal_cstr(pt_string, "xyz"));
        printf("greater : %d, greater equal : %d\n",
            string_greater_cstr(pt_string, "xyz"), string_greater_equal_cstr(pt_string, "xyz"));

        string_assign_cstr(pt_string, "mn");
        _printstring(pt_string);
        puts("mno");
        printf("equal : %d, not equal : %d, ",
            string_equal_cstr(pt_string, "mno"), string_not_equal_cstr(pt_string, "mno"));
        printf("less : %d, less equal : %d, ",
            string_less_cstr(pt_string, "mno"), string_less_equal_cstr(pt_string, "mno"));
        printf("greater : %d, greater equal : %d\n",
            string_greater_cstr(pt_string, "mno"), string_greater_equal_cstr(pt_string, "mno"));

        string_assign_cstr(pt_string, "u");
        _printstring(pt_string);
        puts("abcdefghijklmnopqrstuvwxyz");
        printf("equal : %d, not equal : %d, ",
            string_equal_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz"),
            string_not_equal_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz"));
        printf("less : %d, less equal : %d, ",
            string_less_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz"),
            string_less_equal_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz"));
        printf("greater : %d, greater equal : %d\n",
            string_greater_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz"),
            string_greater_equal_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz"));

        string_destroy(pt_string);
    }
    /*string_not_equal_cstr             */
    /*string_less_cstr                  */
    /*string_less_equal_cstr            */
    /*string_greater_cstr                 */
    /*string_greater_equal_cstr           */
    /*string_compare                    */
    {
        string_t* pt_string1 = create_string();
        string_t* pt_string2 = create_string();
        if(pt_string1 == NULL || pt_string2 == NULL)
        {
            return;
        }
        string_init(pt_string1);
        string_init(pt_string2);
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n", string_compare(pt_string1, pt_string2));

        string_assign_cstr(pt_string1, "abc");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n", string_compare(pt_string1, pt_string2));

        string_assign_cstr(pt_string2, "abc");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n", string_compare(pt_string1, pt_string2));

        string_assign_cstr(pt_string1, "opq");
        string_assign_cstr(pt_string2, "xyz");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n", string_compare(pt_string1, pt_string2));

        string_assign_cstr(pt_string1, "mn");
        string_assign_cstr(pt_string2, "mno");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n", string_compare(pt_string1, pt_string2));

        string_assign_cstr(pt_string1, "u");
        string_assign_cstr(pt_string2, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n", string_compare(pt_string1, pt_string2));
        string_destroy(pt_string1);
        string_destroy(pt_string2);
    }
    /*string_compare_substring_string   */
    {
        string_t* pt_string1 = create_string();
        string_t* pt_string2 = create_string();
        if(pt_string1 == NULL || pt_string2 == NULL)
        {
            return;
        }
        string_init(pt_string1);
        string_init(pt_string2);
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n",
            string_compare_substring_string(pt_string1, 0, NPOS, pt_string2));

        string_assign_cstr(pt_string1, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n",
            string_compare_substring_string(pt_string1, 0, 0, pt_string2));

        string_assign_cstr(pt_string2, "abc");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n",
            string_compare_substring_string(pt_string1, 0, 1, pt_string2));

        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n",
            string_compare_substring_string(pt_string1, 0, 3, pt_string2));

        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n",
            string_compare_substring_string(pt_string1, 0, 5, pt_string2));

        string_assign_cstr(pt_string2, "xyz");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n",
            string_compare_substring_string(pt_string1, 15, 3, pt_string2));

        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n",
            string_compare_substring_string(pt_string1, 23, 3, pt_string2));

        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n",
            string_compare_substring_string(pt_string1, 23, NPOS, pt_string2));

        string_assign_cstr(pt_string2, "u");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n",
            string_compare_substring_string(pt_string1, 0, NPOS, pt_string2));

        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n",
            string_compare_substring_string(pt_string1, 20, NPOS, pt_string2));

        string_destroy(pt_string1);
        string_destroy(pt_string2);
    }
    /*string_compare_substring_substring*/
    {
        string_t* pt_string1 = create_string();
        string_t* pt_string2 = create_string();
        if(pt_string1 == NULL || pt_string2 == NULL)
        {
            return;
        }
        string_init(pt_string1);
        string_init(pt_string2);
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n",
            string_compare_substring_substring(pt_string1, 0, NPOS, pt_string2, 0, NPOS));

        string_assign_cstr(pt_string1, "abcdefghijklmnopqrstuvwxyz");
        string_assign_cstr(pt_string2, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("compare : %d\n",
            string_compare_substring_substring(pt_string1, 0, 0, pt_string2, 0, 0));
        printf("compare : %d\n",
            string_compare_substring_substring(pt_string1, 0, 3, pt_string2, 0, 0));
        printf("compare : %d\n",
            string_compare_substring_substring(pt_string1, 0, NPOS, pt_string2, 0, 0));
        printf("compare : %d\n",
            string_compare_substring_substring(pt_string1, 0, 0, pt_string2, 0, 12));
        printf("compare : %d\n",
            string_compare_substring_substring(pt_string1, 0, 0, pt_string2, 0, NPOS));
        printf("compare : %d\n",
            string_compare_substring_substring(pt_string1, 3, 5, pt_string2, 3, 5));
        printf("compare : %d\n",
            string_compare_substring_substring(pt_string1, 3, NPOS, pt_string2, 3, 5));
        printf("compare : %d\n",
            string_compare_substring_substring(pt_string1, 20, 5, pt_string2, 20, NPOS));
        printf("compare : %d\n",
            string_compare_substring_substring(pt_string1, 20, NPOS, pt_string2, 20, 100));

        string_destroy(pt_string1);
        string_destroy(pt_string2);
    }
    /*string_compare_cstr               */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        _printstring(pt_string);
        puts("");
        printf("compare : %d\n", string_compare_cstr(pt_string, ""));

        string_assign_cstr(pt_string, "abc");
        _printstring(pt_string);
        puts("");
        printf("compare : %d\n", string_compare_cstr(pt_string, ""));

        _printstring(pt_string);
        puts("abc");
        printf("compare : %d\n", string_compare_cstr(pt_string, "abc"));

        string_assign_cstr(pt_string, "opq");
        _printstring(pt_string);
        puts("xyz");
        printf("compare : %d\n", string_compare_cstr(pt_string, "xyz"));

        string_assign_cstr(pt_string, "mn");
        _printstring(pt_string);
        puts("mno");
        printf("compare : %d\n", string_compare_cstr(pt_string, "mno"));

        string_assign_cstr(pt_string, "u");
        _printstring(pt_string);
        puts("abcdefghijklmnopqrstuvwxyz");
        printf("compare : %d\n", string_compare_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz"));
        string_destroy(pt_string);
    }
    /*string_compare_substring_cstr     */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        _printstring(pt_string);
        puts("");
        printf("compare : %d\n",
            string_compare_substring_cstr(pt_string, 0, NPOS, ""));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("");
        printf("compare : %d\n",
            string_compare_substring_cstr(pt_string, 0, 0, ""));

        _printstring(pt_string);
        puts("abc");
        printf("compare : %d\n",
            string_compare_substring_cstr(pt_string, 0, 1, "abc"));

        _printstring(pt_string);
        puts("abc");
        printf("compare : %d\n",
            string_compare_substring_cstr(pt_string, 0, 3, "abc"));

        _printstring(pt_string);
        puts("abc");
        printf("compare : %d\n",
            string_compare_substring_cstr(pt_string, 0, 5, "abc"));

        _printstring(pt_string);
        puts("xyz");
        printf("compare : %d\n",
            string_compare_substring_cstr(pt_string, 15, 3, "xyz"));

        _printstring(pt_string);
        puts("xyz");
        printf("compare : %d\n",
            string_compare_substring_cstr(pt_string, 23, 3, "xyz"));

        _printstring(pt_string);
        puts("xyz");
        printf("compare : %d\n",
            string_compare_substring_cstr(pt_string, 23, NPOS, "xyz"));

        _printstring(pt_string);
        puts("u");
        printf("compare : %d\n",
            string_compare_substring_cstr(pt_string, 0, NPOS, "u"));

        _printstring(pt_string);
        puts("u");
        printf("compare : %d\n",
            string_compare_substring_cstr(pt_string, 20, NPOS, "u"));

        string_destroy(pt_string);
    }
    /*string_compare_substring_subcstr  */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        _printstring(pt_string);
        puts("");
        printf("compare : %d\n",
            string_compare_substring_subcstr(pt_string, 0, NPOS, "", NPOS));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("abcdefghijklmnopqrstuvwxyz");
        printf("compare : %d\n",
            string_compare_substring_subcstr(pt_string, 0, 0, "abcdefghijklmnopqrstuvwxyz", 0));
        printf("compare : %d\n",
            string_compare_substring_subcstr(pt_string, 0, 3, "abcdefghijklmnopqrstuvwxyz", 0));
        printf("compare : %d\n",
            string_compare_substring_subcstr(pt_string, 0, NPOS, "abcdefghijklmnopqrstuvwxyz", 0));
        printf("compare : %d\n",
            string_compare_substring_subcstr(pt_string, 0, 0, "abcdefghijklmnopqrstuvwxyz", 12));
        printf("compare : %d\n",
            string_compare_substring_subcstr(pt_string, 0, 0, "abcdefghijklmnopqrstuvwxyz", NPOS));
        printf("compare : %d\n",
            string_compare_substring_subcstr(pt_string, 3, 5, "defghijklmnopqrstuvwxyz", 5));
        printf("compare : %d\n",
            string_compare_substring_subcstr(pt_string, 3, NPOS, "defghijklmnopqrstuvwxyz", 5));
        printf("compare : %d\n",
            string_compare_substring_subcstr(pt_string, 20, 5, "uvwxyz", NPOS));
        printf("compare : %d\n",
            string_compare_substring_subcstr(pt_string, 20, NPOS, "uvwxyz", 100));

        string_destroy(pt_string);
    }
    /*string_substr                     */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = NULL;
        if(pt_string == NULL)
        {
            return;
        }
        string_init_cstr(pt_string, "abcdef");
        _printstring(pt_string);
        pt_stringex = string_substr(pt_string, 0, NPOS);
        _printstring(pt_stringex);
        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_connect                    */
    {
        string_t* pt_string1 = create_string();
        string_t* pt_string2 = create_string();
        if(pt_string1 == NULL || pt_string2 == NULL)
        {
            return;
        }
        string_init(pt_string1);
        string_init(pt_string2);
        _printstring(pt_string1);
        _printstring(pt_string2);
        string_connect(pt_string1, pt_string2);
        _printstring(pt_string1);
        string_assign_cstr(pt_string2, "abc");
        _printstring(pt_string2);
        string_connect(pt_string1, pt_string2);
        _printstring(pt_string1);
        string_assign_cstr(pt_string2, "");
        _printstring(pt_string2);
        string_connect(pt_string1, pt_string2);
        _printstring(pt_string1);
        string_assign_cstr(pt_string2, "xyz");
        _printstring(pt_string2);
        string_connect(pt_string1, pt_string2);
        _printstring(pt_string1);
        string_destroy(pt_string1);
        string_destroy(pt_string2);
    }
    /*string_connect_cstr               */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_connect_cstr(pt_string, "");
        _printstring(pt_string);
        string_connect_cstr(pt_string, "abc");
        _printstring(pt_string);
        string_connect_cstr(pt_string, "");
        _printstring(pt_string);
        string_connect_cstr(pt_string, "xyz");
        _printstring(pt_string);
        string_destroy(pt_string);
    }
    /*string_connect_char               */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_connect_char(pt_string, 'a');
        _printstring(pt_string);
        string_connect_char(pt_string, 'b');
        _printstring(pt_string);
        string_connect_char(pt_string, 'c');
        _printstring(pt_string);
        string_destroy(pt_string);
    }
    /*string_find                       */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL ||pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);
        _printstring(pt_string);
        _printstring(pt_stringex);
        printf("%u\n", string_find(pt_string, pt_stringex, 0));
        printf("%u\n", string_find(pt_string, pt_stringex, 1));
        printf("%u\n", string_find(pt_string, pt_stringex, 4));

        string_assign_cstr(pt_stringex, "abc");
        _printstring(pt_string);
        _printstring(pt_stringex);
        printf("%u\n", string_find(pt_string, pt_stringex, 0));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_assign_cstr(pt_stringex, "");
        _printstring(pt_string);
        _printstring(pt_stringex);
        printf("%u\n", string_find(pt_string, pt_stringex, 0));
        printf("%u\n", string_find(pt_string, pt_stringex, 10));
        printf("%u\n", string_find(pt_string, pt_stringex, 100));

        string_assign_cstr(pt_stringex, "mno");
        _printstring(pt_string);
        _printstring(pt_stringex);
        printf("%u\n", string_find(pt_string, pt_stringex, 0));
        printf("%u\n", string_find(pt_string, pt_stringex, 5));
        printf("%u\n", string_find(pt_string, pt_stringex, 20));
        printf("%u\n", string_find(pt_string, pt_stringex, 100));
        printf("%u\n", string_find(pt_string, pt_stringex, NPOS));

        string_assign_cstr(pt_string, "aaa");
        string_assign_cstr(pt_stringex, "aaaaa");
        _printstring(pt_string);
        _printstring(pt_stringex);
        printf("%u\n", string_find(pt_string, pt_stringex, 0));
        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_find_cstr                  */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        _printstring(pt_string);
        puts("");
        printf("%u\n", string_find_cstr(pt_string, "", 0));
        printf("%u\n", string_find_cstr(pt_string, "", 1));
        printf("%u\n", string_find_cstr(pt_string, "", 5));

        _printstring(pt_string);
        puts("abc");
        printf("%u\n", string_find_cstr(pt_string, "abc", 0));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("");
        printf("%u\n", string_find_cstr(pt_string, "", 0));
        printf("%u\n", string_find_cstr(pt_string, "", 10));
        printf("%u\n", string_find_cstr(pt_string, "", 100));

        _printstring(pt_string);
        puts("mno");
        printf("%u\n", string_find_cstr(pt_string, "mno", 0));
        printf("%u\n", string_find_cstr(pt_string, "mno", 5));
        printf("%u\n", string_find_cstr(pt_string, "mno", 20));
        printf("%u\n", string_find_cstr(pt_string, "mno", 100));
        printf("%u\n", string_find_cstr(pt_string, "mno", NPOS));

        string_assign_cstr(pt_string, "aaa");
        _printstring(pt_string);
        puts("aaaaa");
        printf("%u\n", string_find_cstr(pt_string, "aaaaa", 0));

        string_destroy(pt_string);
    }
    /*string_find_subcstr               */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        _printstring(pt_string);
        puts("");
        printf("%u\n", string_find_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_subcstr(pt_string, "", 0, 3));
        printf("%u\n", string_find_subcstr(pt_string, "", 0, NPOS));
        printf("%u\n", string_find_subcstr(pt_string, "", 1, 0));
        printf("%u\n", string_find_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_subcstr(pt_string, "", 1, 3));
        printf("%u\n", string_find_subcstr(pt_string, "", NPOS, 3));
        _printstring(pt_string);
        puts("abcdefghijklmnopqrstrvwxyz");
        printf("%u\n", string_find_subcstr(pt_string, "abcdefghijklmnopqrstrvwxyz", 0, 0));
        printf("%u\n", string_find_subcstr(pt_string, "abcdefghijklmnopqrstrvwxyz", 0, 3));
        printf("%u\n", string_find_subcstr(pt_string, "abcdefghijklmnopqrstrvwxyz", 0, NPOS));
        printf("%u\n", string_find_subcstr(pt_string, "abcdefghijklmnopqrstrvwxyz", 1, 0));
        printf("%u\n", string_find_subcstr(pt_string, "abcdefghijklmnopqrstrvwxyz", NPOS, 0));
        printf("%u\n", string_find_subcstr(pt_string, "abcdefghijklmnopqrstrvwxyz", 1, 3));
        printf("%u\n", string_find_subcstr(pt_string, "abcdefghijklmnopqrstrvwxyz", NPOS, 3));
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstrvwxyz");
        _printstring(pt_string);
        puts("abcdefghijklmnopqrstrvwxyz");
        printf("%u\n", string_find_subcstr(pt_string, "abcdefghijklmnopqrstrvwxyz", 0, 0));
        printf("%u\n", string_find_subcstr(pt_string, "abcdefghijklmnopqrstrvwxyz", 0, 3));
        printf("%u\n", string_find_subcstr(pt_string, "abcdefghijklmnopqrstrvwxyz", 0, NPOS));
        printf("%u\n", string_find_subcstr(pt_string, "abcdefghijklmnopqrstrvwxyz", 1, 0));
        printf("%u\n", string_find_subcstr(pt_string, "abcdefghijklmnopqrstrvwxyz", NPOS, 0));
        printf("%u\n", string_find_subcstr(pt_string, "abcdefghijklmnopqrstrvwxyz", 1, 3));
        printf("%u\n", string_find_subcstr(pt_string, "abcdefghijklmnopqrstrvwxyz", NPOS, 3));
        string_destroy(pt_string);
    }
    /*string_find_char                  */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        _printstring(pt_string);
        puts("o");
        printf("%u\n", string_find_char(pt_string, 'o', 0));
        printf("%u\n", string_find_char(pt_string, 'o', 10));
        printf("%u\n", string_find_char(pt_string, 'o', NPOS));
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("o");
        printf("%u\n", string_find_char(pt_string, 'o', 0));
        printf("%u\n", string_find_char(pt_string, 'o', 10));
        printf("%u\n", string_find_char(pt_string, 'o', 20));
        printf("%u\n", string_find_char(pt_string, 'o', NPOS));
        string_destroy(pt_string);
    }
    /*string_rfind                      */
    {
        string_t* pt_string1 = create_string();
        string_t* pt_string2 = create_string();
        if(pt_string1 == NULL || pt_string2 == NULL)
        {
            return;
        }
        string_init(pt_string1);
        string_init(pt_string2);

        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("%u\n", string_rfind(pt_string1, pt_string2, NPOS));
        printf("%u\n", string_rfind(pt_string1, pt_string2, 100));
        printf("%u\n", string_rfind(pt_string1, pt_string2, 0));

        string_assign_cstr(pt_string2, "abc");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("%u\n", string_rfind(pt_string1, pt_string2, NPOS));
        printf("%u\n", string_rfind(pt_string1, pt_string2, 100));
        printf("%u\n", string_rfind(pt_string1, pt_string2, 0));

        string_assign_cstr(pt_string1, "abcdefghijklmnopqrstuvwxyz");
        string_assign_cstr(pt_string2, "");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("%u\n", string_rfind(pt_string1, pt_string2, NPOS));
        printf("%u\n", string_rfind(pt_string1, pt_string2, 100));
        printf("%u\n", string_rfind(pt_string1, pt_string2, 20));
        printf("%u\n", string_rfind(pt_string1, pt_string2, 0));

        string_assign_cstr(pt_string1, "abcdefghijabcklmnopabcqrstuvwxyzabc");
        string_assign_cstr(pt_string2, "abc");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("%u\n", string_rfind(pt_string1, pt_string2, NPOS));
        printf("%u\n", string_rfind(pt_string1, pt_string2, 100));
        printf("%u\n", string_rfind(pt_string1, pt_string2, 20));
        printf("%u\n", string_rfind(pt_string1, pt_string2, 0));

        string_assign_cstr(pt_string1, "aaa");
        string_assign_cstr(pt_string2, "aaaaa");
        _printstring(pt_string1);
        _printstring(pt_string2);
        printf("%u\n", string_rfind(pt_string1, pt_string2, NPOS));
        printf("%u\n", string_rfind(pt_string1, pt_string2, 100));
        printf("%u\n", string_rfind(pt_string1, pt_string2, 1));
        printf("%u\n", string_rfind(pt_string1, pt_string2, 0));

        string_destroy(pt_string1);
        string_destroy(pt_string2);
    }
    /*string_rfind_cstr                 */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        _printstring(pt_string);
        puts("");
        printf("%u\n", string_rfind_cstr(pt_string, "", NPOS));
        printf("%u\n", string_rfind_cstr(pt_string, "", 100));
        printf("%u\n", string_rfind_cstr(pt_string, "", 0));

        _printstring(pt_string);
        puts("abc");
        printf("%u\n", string_rfind_cstr(pt_string, "abc", NPOS));
        printf("%u\n", string_rfind_cstr(pt_string, "abc", 100));
        printf("%u\n", string_rfind_cstr(pt_string, "abc", 0));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("");
        printf("%u\n", string_rfind_cstr(pt_string, "", NPOS));
        printf("%u\n", string_rfind_cstr(pt_string, "", 100));
        printf("%u\n", string_rfind_cstr(pt_string, "", 20));
        printf("%u\n", string_rfind_cstr(pt_string, "", 0));

        string_assign_cstr(pt_string, "abcdefghijabcklmnopabcqrstuvwxyzabc");
        _printstring(pt_string);
        puts("abc");
        printf("%u\n", string_rfind_cstr(pt_string, "abc", NPOS));
        printf("%u\n", string_rfind_cstr(pt_string, "abc", 100));
        printf("%u\n", string_rfind_cstr(pt_string, "abc", 20));
        printf("%u\n", string_rfind_cstr(pt_string, "abc", 0));

        string_assign_cstr(pt_string, "aaa");
        _printstring(pt_string);
        puts("aaaaa");
        printf("%u\n", string_rfind_cstr(pt_string, "aaaaa", NPOS));
        printf("%u\n", string_rfind_cstr(pt_string, "aaaaa", 100));
        printf("%u\n", string_rfind_cstr(pt_string, "aaaaa", 1));
        printf("%u\n", string_rfind_cstr(pt_string, "aaaaa", 0));

        string_destroy(pt_string);
    }
    /*string_rfind_subcstr              */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        _printstring(pt_string);
        puts("");
        printf("%u\n", string_rfind_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "", NPOS, NPOS));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 100, NPOS));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 0, NPOS));

        _printstring(pt_string);
        puts("abcdefghijklmnopqrstuvwxyz");
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", NPOS, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", NPOS, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", NPOS, 20));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", NPOS, NPOS));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 100, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 100, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 100, 20));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 100, NPOS));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 0, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 0, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 0, 20));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 0, NPOS));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("abcdefghijklmnopqrstuvwxyz");
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", NPOS, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", NPOS, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", NPOS, 20));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", NPOS, NPOS));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 100, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 100, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 100, 20));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 100, NPOS));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 20, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 20, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 20, 20));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 20, NPOS));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 0, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 0, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 0, 20));
        printf("%u\n", string_rfind_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 0, NPOS));

        string_destroy(pt_string);
    }
    /*string_rfind_char                 */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        _printstring(pt_string);
        puts("m");
        printf("%u\n", string_rfind_char(pt_string, 'm', NPOS));
        printf("%u\n", string_rfind_char(pt_string, 'm', 100));
        printf("%u\n", string_rfind_char(pt_string, 'm', 0));

        string_assign_cstr(pt_string, "abcdefghijklnopqrstuvwxyz");
        _printstring(pt_string);
        puts("m");
        printf("%u\n", string_rfind_char(pt_string, 'm', NPOS));
        printf("%u\n", string_rfind_char(pt_string, 'm', 100));
        printf("%u\n", string_rfind_char(pt_string, 'm', 20));
        printf("%u\n", string_rfind_char(pt_string, 'm', 0));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxmyz");
        _printstring(pt_string);
        puts("m");
        printf("%u\n", string_rfind_char(pt_string, 'm', NPOS));
        printf("%u\n", string_rfind_char(pt_string, 'm', 100));
        printf("%u\n", string_rfind_char(pt_string, 'm', 20));
        printf("%u\n", string_rfind_char(pt_string, 'm', 0));

        string_destroy(pt_string);
    }
    /*string_find_first_of              */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        _printstring(pt_string);
        _printstring(pt_stringex);
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, NPOS));

        string_assign_cstr(pt_stringex, "bmw");
        _printstring(pt_string);
        _printstring(pt_stringex);
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, NPOS));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_assign_cstr(pt_stringex, "");
        _printstring(pt_string);
        _printstring(pt_stringex);
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 20));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, NPOS));

        string_assign_cstr(pt_stringex, "bmw");
        _printstring(pt_string);
        _printstring(pt_stringex);
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 20));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, NPOS));

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_find_first_of_cstr         */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        _printstring(pt_string);
        puts("");
        printf("%u\n", string_find_first_of_cstr(pt_string, "", 0));
        printf("%u\n", string_find_first_of_cstr(pt_string, "", 100));
        printf("%u\n", string_find_first_of_cstr(pt_string, "", NPOS));

        _printstring(pt_string);
        puts("bmw");
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", NPOS));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("");
        printf("%u\n", string_find_first_of_cstr(pt_string, "", 0));
        printf("%u\n", string_find_first_of_cstr(pt_string, "", 100));
        printf("%u\n", string_find_first_of_cstr(pt_string, "", 20));
        printf("%u\n", string_find_first_of_cstr(pt_string, "", NPOS));

        _printstring(pt_string);
        puts("bmw");
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", 20));
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", NPOS));

        string_destroy(pt_string);
    }
    /*string_find_first_of_subcstr      */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        _printstring(pt_string);
        puts("");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 0, NPOS));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 100, NPOS));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", NPOS, NPOS));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 0, NPOS));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 100, NPOS));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 20, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 20, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 20, NPOS));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", NPOS, NPOS));

        string_assign_cstr(pt_string, "");
        _printstring(pt_string);
        puts("bmw");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 0, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 0, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 0, 1));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 0, NPOS));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 100, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 100, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 100, 1));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 100, NPOS));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", NPOS, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", NPOS, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", NPOS, 1));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", NPOS, NPOS));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("mwb");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", 0, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", 0, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", 0, 1));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", 0, NPOS));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", 100, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", 100, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", 100, 1));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", 100, NPOS));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", 20, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", 20, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", 20, 2));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", 20, NPOS));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", NPOS, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", NPOS, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", NPOS, 1));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "mwb", NPOS, NPOS));

        string_destroy(pt_string);
    }
    /*string_find_first_of_char         */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        _printstring(pt_string);
        puts("m");
        printf("%u\n", string_find_first_of_char(pt_string, 'm', 0));
        printf("%u\n", string_find_first_of_char(pt_string, 'm', 100));
        printf("%u\n", string_find_first_of_char(pt_string, 'm', NPOS));

        string_assign_cstr(pt_string, "abcmdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("m");
        printf("%u\n", string_find_first_of_char(pt_string, 'm', 0));
        printf("%u\n", string_find_first_of_char(pt_string, 'm', 10));
        printf("%u\n", string_find_first_of_char(pt_string, 'm', 20));
        printf("%u\n", string_find_first_of_char(pt_string, 'm', 100));
        printf("%u\n", string_find_first_of_char(pt_string, 'm', NPOS));

        string_destroy(pt_string);
    }
    /*string_find_first_not_of          */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        _printstring(pt_string);
        _printstring(pt_stringex);
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, NPOS));

        string_assign_cstr(pt_stringex, "bmw");
        _printstring(pt_string);
        _printstring(pt_stringex);
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, NPOS));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_assign_cstr(pt_stringex, "");
        _printstring(pt_string);
        _printstring(pt_stringex);
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 20));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, NPOS));

        string_assign_cstr(pt_stringex, "bmw");
        _printstring(pt_string);
        _printstring(pt_stringex);
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 12));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, NPOS));

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_find_first_not_of_cstr     */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        _printstring(pt_string);
        puts("");
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", 0));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", 100));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", NPOS));

        _printstring(pt_string);
        puts("bmw");
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", NPOS));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("");
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", 0));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", 100));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", 20));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", NPOS));

        _printstring(pt_string);
        puts("bmw");
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", 12));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", NPOS));

        string_destroy(pt_string);
    }
    /*string_find_first_not_of_subcstr  */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        _printstring(pt_string);
        puts("");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 0, NPOS));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 100, NPOS));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", NPOS, NPOS));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 0, NPOS));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 100, NPOS));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 20, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 20, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 20, NPOS));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", NPOS, NPOS));

        string_assign_cstr(pt_string, "");
        _printstring(pt_string);
        puts("bmw");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 0, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 0, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 0, 1));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 0, NPOS));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 100, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 100, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 100, 1));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 100, NPOS));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", NPOS, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", NPOS, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", NPOS, 1));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", NPOS, NPOS));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("mwb");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", 0, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", 0, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", 0, 1));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", 0, NPOS));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", 100, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", 100, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", 100, 1));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", 100, NPOS));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", 12, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", 12, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", 12, 1));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", 12, NPOS));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", NPOS, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", NPOS, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", NPOS, 1));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "mwb", NPOS, NPOS));

        string_destroy(pt_string);
    }
    /*string_find_first_not_of_char     */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        _printstring(pt_string);
        puts("a");
        printf("%u\n", string_find_first_not_of_char(pt_string, 'a', 0));
        printf("%u\n", string_find_first_not_of_char(pt_string, 'a', 100));
        printf("%u\n", string_find_first_not_of_char(pt_string, 'a', NPOS));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("m");
        printf("%u\n", string_find_first_not_of_char(pt_string, 'm', 0));
        printf("%u\n", string_find_first_not_of_char(pt_string, 'm', 100));
        printf("%u\n", string_find_first_not_of_char(pt_string, 'm', 12));
        printf("%u\n", string_find_first_not_of_char(pt_string, 'm', 20));
        printf("%u\n", string_find_first_not_of_char(pt_string, 'm', NPOS));

        string_destroy(pt_string);
    }
    /*string_find_last_of               */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        _printstring(pt_string);
        _printstring(pt_stringex);

        printf("\nstring_find: 0, 100, NPOS\n");
        printf("%u\n", string_find(pt_string, pt_stringex, 0));
        printf("%u\n", string_find(pt_string, pt_stringex, 100));
        printf("%u\n", string_find(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_first_of: 0, 100, NPOS\n");
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_first_not_of: 0, 100, NPOS\n");
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, NPOS));

        printf("\nstring_rfind: 0, 100, NPOS\n");
        printf("%u\n", string_rfind(pt_string, pt_stringex, 0));
        printf("%u\n", string_rfind(pt_string, pt_stringex, 100));
        printf("%u\n", string_rfind(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_last_of: 0, 100, NPOS\n");
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_last_not_of: 0, 100, NPOS\n");
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, NPOS));

        /************************************************************/
        string_assign_cstr(pt_stringex, "bmw");
        _printstring(pt_string);
        _printstring(pt_stringex);

        printf("\nstring_find: 0, 100, NPOS\n");
        printf("%u\n", string_find(pt_string, pt_stringex, 0));
        printf("%u\n", string_find(pt_string, pt_stringex, 100));
        printf("%u\n", string_find(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_first_of: 0, 100, NPOS\n");
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_first_not_of: 0, 100, NPOS\n");
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, NPOS));

        printf("\nstring_rfind: 0, 100, NPOS\n");
        printf("%u\n", string_rfind(pt_string, pt_stringex, 0));
        printf("%u\n", string_rfind(pt_string, pt_stringex, 100));
        printf("%u\n", string_rfind(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_last_of: 0, 100, NPOS\n");
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_last_not_of: 0, 100, NPOS\n");
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "abcdefgbmhijklbmwnopqrstuvwxyz");
        string_assign_cstr(pt_stringex, "");
        _printstring(pt_string);
        _printstring(pt_stringex);

        printf("\nstring_find: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find(pt_string, pt_stringex, 0));
        printf("%u\n", string_find(pt_string, pt_stringex, 10));
        printf("%u\n", string_find(pt_string, pt_stringex, 20));
        printf("%u\n", string_find(pt_string, pt_stringex, 100));
        printf("%u\n", string_find(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_first_of: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 10));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 20));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_first_not_of: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 10));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 20));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, NPOS));

        printf("\nstring_rfind: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_rfind(pt_string, pt_stringex, 0));
        printf("%u\n", string_rfind(pt_string, pt_stringex, 10));
        printf("%u\n", string_rfind(pt_string, pt_stringex, 20));
        printf("%u\n", string_rfind(pt_string, pt_stringex, 100));
        printf("%u\n", string_rfind(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_last_of: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, 10));
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, 20));
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_last_not_of: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, 10));
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, 20));
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "abcdefgbmhijklbmwnopqrstuvwxyz");
        string_assign_cstr(pt_stringex, "bmw");
        _printstring(pt_string);
        _printstring(pt_stringex);

        printf("\nstring_find: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find(pt_string, pt_stringex, 0));
        printf("%u\n", string_find(pt_string, pt_stringex, 10));
        printf("%u\n", string_find(pt_string, pt_stringex, 20));
        printf("%u\n", string_find(pt_string, pt_stringex, 100));
        printf("%u\n", string_find(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_first_of: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 10));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 20));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_of(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_first_not_of: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 16));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 20));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_first_not_of(pt_string, pt_stringex, NPOS));

        printf("\nstring_rfind: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_rfind(pt_string, pt_stringex, 0));
        printf("%u\n", string_rfind(pt_string, pt_stringex, 10));
        printf("%u\n", string_rfind(pt_string, pt_stringex, 20));
        printf("%u\n", string_rfind(pt_string, pt_stringex, 100));
        printf("%u\n", string_rfind(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_last_of: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, 10));
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, 20));
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_last_of(pt_string, pt_stringex, NPOS));

        printf("\nstring_find_last_not_of: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, 0));
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, 16));
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, 20));
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, 100));
        printf("%u\n", string_find_last_not_of(pt_string, pt_stringex, NPOS));

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_find_last_of_cstr          */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        _printstring(pt_string);
        puts("");

        printf("\nstring_find_cstr: 0, 100, NPOS\n");
        printf("%u\n", string_find_cstr(pt_string, "", 0));
        printf("%u\n", string_find_cstr(pt_string, "", 100));
        printf("%u\n", string_find_cstr(pt_string, "", NPOS));

        printf("\nstring_find_first_of_cstr: 0, 100, NPOS\n");
        printf("%u\n", string_find_first_of_cstr(pt_string, "", 0));
        printf("%u\n", string_find_first_of_cstr(pt_string, "", 100));
        printf("%u\n", string_find_first_of_cstr(pt_string, "", NPOS));

        printf("\nstring_find_first_not_of_cstr: 0, 100, NPOS\n");
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", 0));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", 100));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", NPOS));

        printf("\nstring_rfind_cstr: 0, 100, NPOS\n");
        printf("%u\n", string_rfind_cstr(pt_string, "", 0));
        printf("%u\n", string_rfind_cstr(pt_string, "", 100));
        printf("%u\n", string_rfind_cstr(pt_string, "", NPOS));

        printf("\nstring_find_last_of_cstr: 0, 100, NPOS\n");
        printf("%u\n", string_find_last_of_cstr(pt_string, "", 0));
        printf("%u\n", string_find_last_of_cstr(pt_string, "", 100));
        printf("%u\n", string_find_last_of_cstr(pt_string, "", NPOS));

        printf("\nstring_find_last_not_of_cstr: 0, 100, NPOS\n");
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "", 0));
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "", 100));
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "", NPOS));

        /************************************************************/
        _printstring(pt_string);
        puts("bmw");

        printf("\nstring_find_cstr: 0, 100, NPOS\n");
        printf("%u\n", string_find_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_find_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_find_cstr(pt_string, "bmw", NPOS));

        printf("\nstring_find_first_of_cstr: 0, 100, NPOS\n");
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", NPOS));

        printf("\nstring_find_first_not_of_cstr: 0, 100, NPOS\n");
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", NPOS));

        printf("\nstring_rfind_cstr: 0, 100, NPOS\n");
        printf("%u\n", string_rfind_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_rfind_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_rfind_cstr(pt_string, "bmw", NPOS));

        printf("\nstring_find_last_of_cstr: 0, 100, NPOS\n");
        printf("%u\n", string_find_last_of_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_find_last_of_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_find_last_of_cstr(pt_string, "bmw", NPOS));

        printf("\nstring_find_last_not_of_cstr: 0, 100, NPOS\n");
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "bmw", NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "abcdefgbmhijklbmwnopqrstuvwxyz");
        _printstring(pt_string);
        puts("");

        printf("\nstring_find_cstr: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_cstr(pt_string, "", 0));
        printf("%u\n", string_find_cstr(pt_string, "", 10));
        printf("%u\n", string_find_cstr(pt_string, "", 20));
        printf("%u\n", string_find_cstr(pt_string, "", 100));
        printf("%u\n", string_find_cstr(pt_string, "", NPOS));

        printf("\nstring_find_first_of_cstr: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_first_of_cstr(pt_string, "", 0));
        printf("%u\n", string_find_first_of_cstr(pt_string, "", 10));
        printf("%u\n", string_find_first_of_cstr(pt_string, "", 20));
        printf("%u\n", string_find_first_of_cstr(pt_string, "", 100));
        printf("%u\n", string_find_first_of_cstr(pt_string, "", NPOS));

        printf("\nstring_find_first_not_of_cstr: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", 0));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", 10));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", 20));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", 100));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "", NPOS));

        printf("\nstring_rfind_cstr: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_rfind_cstr(pt_string, "", 0));
        printf("%u\n", string_rfind_cstr(pt_string, "", 10));
        printf("%u\n", string_rfind_cstr(pt_string, "", 20));
        printf("%u\n", string_rfind_cstr(pt_string, "", 100));
        printf("%u\n", string_rfind_cstr(pt_string, "", NPOS));

        printf("\nstring_find_last_of_cstr: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_last_of_cstr(pt_string, "", 0));
        printf("%u\n", string_find_last_of_cstr(pt_string, "", 10));
        printf("%u\n", string_find_last_of_cstr(pt_string, "", 20));
        printf("%u\n", string_find_last_of_cstr(pt_string, "", 100));
        printf("%u\n", string_find_last_of_cstr(pt_string, "", NPOS));

        printf("\nstring_find_last_not_of_cstr: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "", 0));
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "", 10));
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "", 20));
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "", 100));
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "", NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "abcdefgbmhijklbmwnopqrstuvwxyz");
        _printstring(pt_string);
        puts("bmw");

        printf("\nstring_find_cstr: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_find_cstr(pt_string, "bmw", 10));
        printf("%u\n", string_find_cstr(pt_string, "bmw", 20));
        printf("%u\n", string_find_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_find_cstr(pt_string, "bmw", NPOS));

        printf("\nstring_find_first_of_cstr: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", 10));
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", 20));
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_find_first_of_cstr(pt_string, "bmw", NPOS));

        printf("\nstring_find_first_not_of_cstr: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", 16));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", 20));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_find_first_not_of_cstr(pt_string, "bmw", NPOS));

        printf("\nstring_rfind_cstr: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_rfind_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_rfind_cstr(pt_string, "bmw", 10));
        printf("%u\n", string_rfind_cstr(pt_string, "bmw", 20));
        printf("%u\n", string_rfind_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_rfind_cstr(pt_string, "bmw", NPOS));

        printf("\nstring_find_last_of_cstr: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_last_of_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_find_last_of_cstr(pt_string, "bmw", 10));
        printf("%u\n", string_find_last_of_cstr(pt_string, "bmw", 20));
        printf("%u\n", string_find_last_of_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_find_last_of_cstr(pt_string, "bmw", NPOS));

        printf("\nstring_find_last_not_of_cstr: 0, 10, 20, 100, NPOS\n");
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "bmw", 0));
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "bmw", 16));
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "bmw", 20));
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "bmw", 100));
        printf("%u\n", string_find_last_not_of_cstr(pt_string, "bmw", NPOS));

        string_destroy(pt_string);
    }
    /*string_find_last_of_subcstr       */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        _printstring(pt_string);
        puts("");
        printf("\nstring_find_subcstr: (0,0), (0,100), (0,npos)\n");
        printf("%u\n", string_find_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_find_subcstr(pt_string, "", 0, NPOS));

        printf("\nstring_find_first_of_subcstr: (0,0), (0,100), (0,npos)\n");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 0, NPOS));

        printf("\nstring_find_first_not_of_subcstr: (0,0), (0,100), (0,npos)\n");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 0, NPOS));

        printf("\nstring_rfind_subcstr: (0,0), (0,100), (0,npos)\n");
        printf("%u\n", string_rfind_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 0, NPOS));

        printf("\nstring_find_last_of_subcstr: (0,0), (0,100), (0,npos)\n");
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 0, NPOS));

        printf("\nstring_find_last_not_of_subcstr: (0,0), (0,100), (0,npos)\n");
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 0, NPOS));

        /************************************************************/
        _printstring(pt_string);
        puts("");
        printf("\nstring_find_subcstr: (100,0), (100,100), (100,npos)\n");
        printf("%u\n", string_find_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_find_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_find_subcstr(pt_string, "", 100, NPOS));

        printf("\nstring_find_first_of_subcstr: (100,0), (100,100), (100,npos)\n");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 100, NPOS));

        printf("\nstring_find_first_not_of_subcstr: (100,0), (100,100), (100,npos)\n");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 100, NPOS));

        printf("\nstring_rfind_subcstr: (100,0), (100,100), (100,npos)\n");
        printf("%u\n", string_rfind_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 100, NPOS));

        printf("\nstring_find_last_of_subcstr: (100,0), (100,100), (100,npos)\n");
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 100, NPOS));

        printf("\nstring_find_last_not_of_subcstr: (100,0), (100,100), (100,npos)\n");
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 100, NPOS));

        /************************************************************/
        _printstring(pt_string);
        puts("");
        printf("\nstring_find_subcstr: (NPOS,0), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_find_subcstr(pt_string, "", NPOS, NPOS));

        printf("\nstring_find_first_of_subcstr: (NPOS,0), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", NPOS, NPOS));

        printf("\nstring_find_first_not_of_subcstr: (NPOS,0), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", NPOS, NPOS));

        printf("\nstring_rfind_subcstr: (NPOS,0), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_rfind_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "", NPOS, NPOS));

        printf("\nstring_find_last_of_subcstr: (NPOS,0), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", NPOS, NPOS));

        printf("\nstring_find_last_not_of_subcstr: (NPOS,0), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", NPOS, NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("");
        printf("\nstring_find_subcstr: (0,0), (0,100), (0,npos)\n");
        printf("%u\n", string_find_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_find_subcstr(pt_string, "", 0, NPOS));

        printf("\nstring_find_first_of_subcstr: (0,0), (0,100), (0,npos)\n");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 0, NPOS));

        printf("\nstring_find_first_not_of_subcstr: (0,0), (0,100), (0,npos)\n");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 0, NPOS));

        printf("\nstring_rfind_subcstr: (0,0), (0,100), (0,npos)\n");
        printf("%u\n", string_rfind_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 0, NPOS));

        printf("\nstring_find_last_of_subcstr: (0,0), (0,100), (0,npos)\n");
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 0, NPOS));

        printf("\nstring_find_last_not_of_subcstr: (0,0), (0,100), (0,npos)\n");
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 0, 0));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 0, 100));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 0, NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("");
        printf("\nstring_find_subcstr: (20,0), (20,100), (20,npos)\n");
        printf("%u\n", string_find_subcstr(pt_string, "", 20, 0));
        printf("%u\n", string_find_subcstr(pt_string, "", 20, 100));
        printf("%u\n", string_find_subcstr(pt_string, "", 20, NPOS));

        printf("\nstring_find_first_of_subcstr: (20,0), (20,100), (20,npos)\n");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 20, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 20, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 20, NPOS));

        printf("\nstring_find_first_not_of_subcstr: (20,0), (20,100), (20,npos)\n");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 20, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 20, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 20, NPOS));

        printf("\nstring_rfind_subcstr: (20,0), (20,100), (20,npos)\n");
        printf("%u\n", string_rfind_subcstr(pt_string, "", 20, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 20, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 20, NPOS));

        printf("\nstring_find_last_of_subcstr: (20,0), (20,100), (20,npos)\n");
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 20, 0));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 20, 100));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 20, NPOS));

        printf("\nstring_find_last_not_of_subcstr: (20,0), (20,100), (20,npos)\n");
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 20, 0));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 20, 100));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 20, NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("");
        printf("\nstring_find_subcstr: (100,0), (100,100), (100,npos)\n");
        printf("%u\n", string_find_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_find_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_find_subcstr(pt_string, "", 100, NPOS));

        printf("\nstring_find_first_of_subcstr: (100,0), (100,100), (100,npos)\n");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", 100, NPOS));

        printf("\nstring_find_first_not_of_subcstr: (100,0), (100,100), (100,npos)\n");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", 100, NPOS));

        printf("\nstring_rfind_subcstr: (100,0), (100,100), (100,npos)\n");
        printf("%u\n", string_rfind_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "", 100, NPOS));

        printf("\nstring_find_last_of_subcstr: (100,0), (100,100), (100,npos)\n");
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", 100, NPOS));

        printf("\nstring_find_last_not_of_subcstr: (100,0), (100,100), (100,npos)\n");
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 100, 0));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 100, 100));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", 100, NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("");
        printf("\nstring_find_subcstr: (NPOS,0), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_find_subcstr(pt_string, "", NPOS, NPOS));

        printf("\nstring_find_first_of_subcstr: (NPOS,0), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "", NPOS, NPOS));

        printf("\nstring_find_first_not_of_subcstr: (NPOS,0), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "", NPOS, NPOS));

        printf("\nstring_rfind_subcstr: (NPOS,0), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_rfind_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "", NPOS, NPOS));

        printf("\nstring_find_last_of_subcstr: (NPOS,0), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "", NPOS, NPOS));

        printf("\nstring_find_last_not_of_subcstr: (NPOS,0), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", NPOS, 0));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", NPOS, 100));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "", NPOS, NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "");
        _printstring(pt_string);
        puts("bmw");
        printf("\nstring_find_subcstr: (0,0), (0,1), (0,100), (0,npos)\n");
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 0, 0));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 0, 1));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 0, 100));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 0, NPOS));

        printf("\nstring_find_first_of_subcstr: (0,0), (0,1), (0,100), (0,npos)\n");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 0, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 0, 1));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 0, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 0, NPOS));

        printf("\nstring_find_first_not_of_subcstr: (0,0), (0,1), (0,100), (0,npos)\n");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 0, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 0, 1));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 0, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 0, NPOS));

        printf("\nstring_rfind_subcstr: (0,0), (0,1), (0,100), (0,npos)\n");
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 0, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 0, 1));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 0, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 0, NPOS));

        printf("\nstring_find_last_of_subcstr: (0,0), (0,1), (0,100), (0,npos)\n");
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 0, 0));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 0, 1));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 0, 100));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 0, NPOS));

        printf("\nstring_find_last_not_of_subcstr: (0,0), (0,1), (0,100), (0,npos)\n");
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 0, 0));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 0, 1));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 0, 100));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 0, NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "");
        _printstring(pt_string);
        puts("bmw");
        printf("\nstring_find_subcstr: (100,0), (100,1), (100,100), (100,npos)\n");
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 100, 0));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 100, 1));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 100, 100));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 100, NPOS));

        printf("\nstring_find_first_of_subcstr: (100,0), (100,1), (100,100), (100,npos)\n");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 100, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 100, 1));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 100, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 100, NPOS));

        printf("\nstring_find_first_not_of_subcstr: (100,0), (100,1), (100,100), (100,npos)\n");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 100, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 100, 1));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 100, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 100, NPOS));

        printf("\nstring_rfind_subcstr: (100,0), (100,1), (100,100), (100,npos)\n");
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 100, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 100, 1));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 100, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 100, NPOS));

        printf("\nstring_find_last_of_subcstr: (100,0), (100,1), (100,100), (100,npos)\n");
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 100, 0));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 100, 1));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 100, 100));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 100, NPOS));

        printf("\nstring_find_last_not_of_subcstr: (100,0), (100,1), (100,100), (100,npos)\n");
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 100, 0));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 100, 1));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 100, 100));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 100, NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "");
        _printstring(pt_string);
        puts("bmw");
        printf("\nstring_find_subcstr: (NPOS,0), (NPOS,1), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_subcstr(pt_string, "bmw", NPOS, 0));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", NPOS, 1));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", NPOS, 100));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", NPOS, NPOS));

        printf("\nstring_find_first_of_subcstr: (NPOS,0), (NPOS,1), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", NPOS, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", NPOS, 1));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", NPOS, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", NPOS, NPOS));

        printf("\nstring_find_first_not_of_subcstr: (NPOS,0), (NPOS,1), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", NPOS, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", NPOS, 1));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", NPOS, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", NPOS, NPOS));

        printf("\nstring_rfind_subcstr: (NPOS,0), (NPOS,1), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", NPOS, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", NPOS, 1));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", NPOS, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", NPOS, NPOS));

        printf("\nstring_find_last_of_subcstr: (NPOS,0), (NPOS,1), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", NPOS, 0));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", NPOS, 1));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", NPOS, 100));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", NPOS, NPOS));

        printf("\nstring_find_last_not_of_subcstr: (NPOS,0), (NPOS,1), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", NPOS, 0));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", NPOS, 1));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", NPOS, 100));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", NPOS, NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "abcdefgbmhijklbmwnopqrstuvbmwxyz");
        _printstring(pt_string);
        puts("bmw");
        printf("\nstring_find_subcstr: (0,0), (0,1), (0,100), (0,npos)\n");
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 0, 0));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 0, 1));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 0, 100));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 0, NPOS));

        printf("\nstring_find_first_of_subcstr: (0,0), (0,1), (0,100), (0,npos)\n");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 0, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 0, 1));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 0, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 0, NPOS));

        printf("\nstring_find_first_not_of_subcstr: (0,0), (0,1), (0,100), (0,npos)\n");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 0, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 0, 1));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 0, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 0, NPOS));

        printf("\nstring_rfind_subcstr: (0,0), (0,1), (0,100), (0,npos)\n");
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 0, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 0, 1));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 0, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 0, NPOS));

        printf("\nstring_find_last_of_subcstr: (0,0), (0,1), (0,100), (0,npos)\n");
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 0, 0));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 0, 1));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 0, 100));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 0, NPOS));

        printf("\nstring_find_last_not_of_subcstr: (0,0), (0,1), (0,100), (0,npos)\n");
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 0, 0));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 0, 1));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 0, 100));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 0, NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "abcdefgbmhijklbmwnopqrstuvbmwxyz");
        _printstring(pt_string);
        puts("bmw");
        printf("\nstring_find_subcstr: (15,0), (15,1), (15,100), (15,npos)\n");
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 15, 0));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 15, 1));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 15, 100));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 15, NPOS));

        printf("\nstring_find_first_of_subcstr: (15,0), (15,1), (15,100), (15,npos)\n");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 15, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 15, 1));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 15, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 15, NPOS));

        printf("\nstring_find_first_not_of_subcstr: (15,0), (15,1), (15,100), (15,npos)\n");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 15, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 15, 1));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 15, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 15, NPOS));

        printf("\nstring_rfind_subcstr: (15,0), (15,1), (15,100), (15,npos)\n");
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 15, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 15, 1));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 15, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 15, NPOS));

        printf("\nstring_find_last_of_subcstr: (15,0), (15,1), (15,100), (15,npos)\n");
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 15, 0));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 15, 1));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 15, 100));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 15, NPOS));

        printf("\nstring_find_last_not_of_subcstr: (15,0), (15,1), (15,100), (15,npos)\n");
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 15, 0));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 15, 1));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 15, 100));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 15, NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "abcdefgbmhijklbmwnopqrstuvbmwxyz");
        _printstring(pt_string);
        puts("bmw");
        printf("\nstring_find_subcstr: (100,0), (100,1), (100,100), (100,npos)\n");
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 100, 0));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 100, 1));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 100, 100));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", 100, NPOS));

        printf("\nstring_find_first_of_subcstr: (100,0), (100,1), (100,100), (100,npos)\n");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 100, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 100, 1));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 100, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", 100, NPOS));

        printf("\nstring_find_first_not_of_subcstr: (100,0), (100,1), (100,100), (100,npos)\n");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 100, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 100, 1));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 100, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", 100, NPOS));

        printf("\nstring_rfind_subcstr: (100,0), (100,1), (100,100), (100,npos)\n");
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 100, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 100, 1));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 100, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", 100, NPOS));

        printf("\nstring_find_last_of_subcstr: (100,0), (100,1), (100,100), (100,npos)\n");
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 100, 0));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 100, 1));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 100, 100));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", 100, NPOS));

        printf("\nstring_find_last_not_of_subcstr: (100,0), (100,1), (100,100), (100,npos)\n");
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 100, 0));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 100, 1));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 100, 100));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", 100, NPOS));

        /************************************************************/
        string_assign_cstr(pt_string, "abcdefgbmhijklbmwnopqrstuvbmwxyz");
        _printstring(pt_string);
        puts("bmw");
        printf("\nstring_find_subcstr: (NPOS,0), (NPOS,1), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_subcstr(pt_string, "bmw", NPOS, 0));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", NPOS, 1));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", NPOS, 100));
        printf("%u\n", string_find_subcstr(pt_string, "bmw", NPOS, NPOS));

        printf("\nstring_find_first_of_subcstr: (NPOS,0), (NPOS,1), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", NPOS, 0));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", NPOS, 1));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", NPOS, 100));
        printf("%u\n", string_find_first_of_subcstr(pt_string, "bmw", NPOS, NPOS));

        printf("\nstring_find_first_not_of_subcstr: (NPOS,0), (NPOS,1), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", NPOS, 0));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", NPOS, 1));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", NPOS, 100));
        printf("%u\n", string_find_first_not_of_subcstr(pt_string, "bmw", NPOS, NPOS));

        printf("\nstring_rfind_subcstr: (NPOS,0), (NPOS,1), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", NPOS, 0));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", NPOS, 1));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", NPOS, 100));
        printf("%u\n", string_rfind_subcstr(pt_string, "bmw", NPOS, NPOS));

        printf("\nstring_find_last_of_subcstr: (NPOS,0), (NPOS,1), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", NPOS, 0));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", NPOS, 1));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", NPOS, 100));
        printf("%u\n", string_find_last_of_subcstr(pt_string, "bmw", NPOS, NPOS));

        printf("\nstring_find_last_not_of_subcstr: (NPOS,0), (NPOS,1), (NPOS,100), (NPOS,npos)\n");
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", NPOS, 0));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", NPOS, 1));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", NPOS, 100));
        printf("%u\n", string_find_last_not_of_subcstr(pt_string, "bmw", NPOS, NPOS));

        string_destroy(pt_string);
    }
    /*string_find_last_of_char          */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        _printstring(pt_string);
        puts("o");
        printf("\nstring_find_char: 0, 100, NPOS\n");
        printf("%u\n", string_find_char(pt_string, 'o', 0));
        printf("%u\n", string_find_char(pt_string, 'o', 100));
        printf("%u\n", string_find_char(pt_string, 'o', NPOS));

        printf("\nstring_find_first_of_char: 0, 100, NPOS\n");
        printf("%u\n", string_find_first_of_char(pt_string, 'o', 0));
        printf("%u\n", string_find_first_of_char(pt_string, 'o', 100));
        printf("%u\n", string_find_first_of_char(pt_string, 'o', NPOS));

        printf("\nstring_find_first_not_of_char: 0, 100, NPOS\n");
        printf("%u\n", string_find_first_not_of_char(pt_string, 'o', 0));
        printf("%u\n", string_find_first_not_of_char(pt_string, 'o', 100));
        printf("%u\n", string_find_first_not_of_char(pt_string, 'o', NPOS));

        printf("\nstring_rfind_char: 0, 100, NPOS\n");
        printf("%u\n", string_rfind_char(pt_string, 'o', 0));
        printf("%u\n", string_rfind_char(pt_string, 'o', 100));
        printf("%u\n", string_rfind_char(pt_string, 'o', NPOS));

        printf("\nstring_find_last_of_char: 0, 100, NPOS\n");
        printf("%u\n", string_find_last_of_char(pt_string, 'o', 0));
        printf("%u\n", string_find_last_of_char(pt_string, 'o', 100));
        printf("%u\n", string_find_last_of_char(pt_string, 'o', NPOS));

        printf("\nstring_find_last_not_of_char: 0, 100, NPOS\n");
        printf("%u\n", string_find_last_not_of_char(pt_string, 'o', 0));
        printf("%u\n", string_find_last_not_of_char(pt_string, 'o', 100));
        printf("%u\n", string_find_last_not_of_char(pt_string, 'o', NPOS));

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);
        puts("o");
        printf("\nstring_find_char: 0, 20, 100, NPOS\n");
        printf("%u\n", string_find_char(pt_string, 'o', 0));
        printf("%u\n", string_find_char(pt_string, 'o', 20));
        printf("%u\n", string_find_char(pt_string, 'o', 100));
        printf("%u\n", string_find_char(pt_string, 'o', NPOS));

        printf("\nstring_find_first_of_char: 0, 20, 100, NPOS\n");
        printf("%u\n", string_find_first_of_char(pt_string, 'o', 0));
        printf("%u\n", string_find_first_of_char(pt_string, 'o', 20));
        printf("%u\n", string_find_first_of_char(pt_string, 'o', 100));
        printf("%u\n", string_find_first_of_char(pt_string, 'o', NPOS));

        printf("\nstring_find_first_not_of_char: 0, 20, 100, NPOS\n");
        printf("%u\n", string_find_first_not_of_char(pt_string, 'o', 0));
        printf("%u\n", string_find_first_not_of_char(pt_string, 'o', 20));
        printf("%u\n", string_find_first_not_of_char(pt_string, 'o', 100));
        printf("%u\n", string_find_first_not_of_char(pt_string, 'o', NPOS));

        printf("\nstring_rfind_char: 0, 20, 100, NPOS\n");
        printf("%u\n", string_rfind_char(pt_string, 'o', 0));
        printf("%u\n", string_rfind_char(pt_string, 'o', 20));
        printf("%u\n", string_rfind_char(pt_string, 'o', 100));
        printf("%u\n", string_rfind_char(pt_string, 'o', NPOS));

        printf("\nstring_find_last_of_char: 0, 20, 100, NPOS\n");
        printf("%u\n", string_find_last_of_char(pt_string, 'o', 0));
        printf("%u\n", string_find_last_of_char(pt_string, 'o', 20));
        printf("%u\n", string_find_last_of_char(pt_string, 'o', 100));
        printf("%u\n", string_find_last_of_char(pt_string, 'o', NPOS));

        printf("\nstring_find_last_not_of_char: 0, 20, 100, NPOS\n");
        printf("%u\n", string_find_last_not_of_char(pt_string, 'o', 0));
        printf("%u\n", string_find_last_not_of_char(pt_string, 'o', 20));
        printf("%u\n", string_find_last_not_of_char(pt_string, 'o', 100));
        printf("%u\n", string_find_last_not_of_char(pt_string, 'o', NPOS));

        string_destroy(pt_string);
    }
    /*string_find_last_not_of           */
    /*string_find_last_not_of_cstr      */
    /*string_find_last_not_of_subcstr   */
    /*string_find_last_not_of_char      */
    /*string_begin                      */
    {
        string_t* pt_string = create_string();
        iterator_t t_iter;
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        _printstring(pt_string);
        for(t_iter = string_begin(pt_string);
            !iterator_equal(t_iter, string_end(pt_string));
            t_iter = iterator_next(t_iter))
        {
            printf("%s\n", (char*)iterator_get_pointer(t_iter));
        }
        string_assign_cstr(pt_string, "China");
        _printstring(pt_string);
        for(t_iter = string_begin(pt_string);
            !iterator_equal(t_iter, string_end(pt_string));
            t_iter = iterator_next(t_iter))
        {
            printf("%s\n", (char*)iterator_get_pointer(t_iter));
        }
        string_destroy(pt_string);
    }
    /*string_end                        */
    /*string_clear                      */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        _printstring(pt_string);
        string_clear(pt_string);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "China");
        _printstring(pt_string);
        string_clear(pt_string);
        _printstring(pt_string);
        string_destroy(pt_string);
    }
    /*string_swap                       */
    {
        string_t* pt_string1 = create_string();
        string_t* pt_string2 = create_string();
        if(pt_string1 == NULL || pt_string2 == NULL)
        {
            return;
        }
        string_init(pt_string1);
        string_init(pt_string2);

        _printstring(pt_string1);
        _printstring(pt_string2);
        string_swap(pt_string1, pt_string2);
        _printstring(pt_string1);
        _printstring(pt_string2);

        string_assign_cstr(pt_string2, "Shenyang");
        _printstring(pt_string1);
        _printstring(pt_string2);
        string_swap(pt_string1, pt_string2);
        _printstring(pt_string1);
        _printstring(pt_string2);

        string_assign_cstr(pt_string2, "DaLian");
        _printstring(pt_string1);
        _printstring(pt_string2);
        string_swap(pt_string1, pt_string2);
        _printstring(pt_string1);
        _printstring(pt_string2);

        string_clear(pt_string2);
        _printstring(pt_string1);
        _printstring(pt_string2);
        string_swap(pt_string1, pt_string2);
        _printstring(pt_string1);
        _printstring(pt_string2);

        string_destroy(pt_string1);
        string_destroy(pt_string2);
    }
    /*string_reserve                    */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        _printstring(pt_string);
        string_reserve(pt_string, 20);
        _printstring(pt_string);
        string_reserve(pt_string, 100);
        _printstring(pt_string);
        string_reserve(pt_string, 8);
        _printstring(pt_string);
        string_reserve(pt_string, 0);
        _printstring(pt_string);
        string_destroy(pt_string);
    }
    /*string_resize                     */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        _printstring(pt_string);
        string_resize(pt_string, 10, 'u');
        _printstring(pt_string);
        string_resize(pt_string, 83, 'A');
        _printstring(pt_string);
        string_resize(pt_string, 17, 'b');
        _printstring(pt_string);
        string_resize(pt_string, 0, 'm');
        _printstring(pt_string);
        string_destroy(pt_string);
    }
    /*string_push_back                  */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        _printstring(pt_string);
        string_push_back(pt_string, 'C');
        _printstring(pt_string);
        string_push_back(pt_string, 'H');
        _printstring(pt_string);
        string_push_back(pt_string, 'N');
        _printstring(pt_string);
        string_destroy(pt_string);
    }
    /*string_assign                     */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        _printstring(pt_string);
        _printstring(pt_stringex);
        string_assign(pt_string, pt_stringex);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_assign_cstr(pt_stringex, "alkdiebv");
        _printstring(pt_string);
        _printstring(pt_stringex);
        string_assign(pt_string, pt_stringex);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_assign_cstr(pt_stringex, "#$$#@%^*(*&^%#~!##$$%^&*&&^%$#@#$^*(");
        _printstring(pt_string);
        _printstring(pt_stringex);
        string_assign(pt_string, pt_stringex);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_assign_cstr(pt_stringex, "8734763984");
        _printstring(pt_string);
        _printstring(pt_stringex);
        string_assign(pt_string, pt_stringex);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_clear(pt_stringex);
        _printstring(pt_string);
        _printstring(pt_stringex);
        string_assign(pt_string, pt_stringex);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_assign_substring           */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        printf("================================\n");
        _printstring(pt_string);
        _printstring(pt_stringex);
        string_assign_substring(pt_string, pt_stringex, 0, 0);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_assign_substring(pt_string, pt_stringex, 0, 100);
        _printstring(pt_string);
        _printstring(pt_stringex);
        string_assign_substring(pt_string, pt_stringex, 0, NPOS);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_assign_cstr(pt_stringex, "abcdefghijklmnopqrstuvwxyz");
        string_assign_substring(pt_string, pt_stringex, 0, 0);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_clear(pt_string);
        string_assign_substring(pt_string, pt_stringex, 0, 10);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_clear(pt_string);
        string_assign_substring(pt_string, pt_stringex, 0, 100);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_clear(pt_string);
        string_assign_substring(pt_string, pt_stringex, 0, NPOS);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_clear(pt_string);
        string_assign_substring(pt_string, pt_stringex, 10, 0);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_clear(pt_string);
        string_assign_substring(pt_string, pt_stringex, 10, 10);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_clear(pt_string);
        string_assign_substring(pt_string, pt_stringex, 10, 100);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_clear(pt_string);
        string_assign_substring(pt_string, pt_stringex, 10, NPOS);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_assign_cstr(pt_string, "1234567890");
        string_assign_substring(pt_string, pt_stringex, 5, 0);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_assign_cstr(pt_string, "1234567890");
        string_assign_substring(pt_string, pt_stringex, 5, 5);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_assign_cstr(pt_string, "1234567890");
        string_assign_substring(pt_string, pt_stringex, 5, 500);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_assign_cstr(pt_string, "1234567890");
        string_assign_substring(pt_string, pt_stringex, 5, NPOS);
        _printstring(pt_string);
        _printstring(pt_stringex);

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_assign_cstr                */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_assign_cstr(pt_string, "");
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        _printstring(pt_string);

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Shenyang");
        _printstring(pt_string);

        string_assign_cstr(pt_string, "");
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_assign_subcstr             */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_assign_subcstr(pt_string, "", 0);
        _printstring(pt_string);
        string_assign_subcstr(pt_string, "", 100);
        _printstring(pt_string);
        string_assign_subcstr(pt_string, "", NPOS);
        _printstring(pt_string);

        string_assign_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 0);
        _printstring(pt_string);
        string_assign_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 10);
        _printstring(pt_string);
        string_assign_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 100);
        _printstring(pt_string);
        string_assign_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", NPOS);
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_assign_char                */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_assign_char(pt_string, 0, 'v');
        _printstring(pt_string);
        string_assign_char(pt_string, 10, 'q');
        _printstring(pt_string);
        string_assign_char(pt_string, 100, 'm');
        _printstring(pt_string);
        string_assign_char(pt_string, 2, 'c');
        _printstring(pt_string);
        string_assign_char(pt_string, 0, 'r');
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_assign_range               */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        string_assign_range(pt_string, string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_stringex);
        string_assign_range(pt_string, string_begin(pt_stringex), string_begin(pt_stringex));
        _printstring(pt_string);

        string_assign_range(pt_string,
            string_begin(pt_stringex), iterator_next_n(string_begin(pt_stringex), 4));
        _printstring(pt_string);

        string_assign_range(pt_string, iterator_next_n(string_begin(pt_stringex), 5),
            iterator_next_n(string_begin(pt_stringex), 20));
        _printstring(pt_string);

        string_assign_range(pt_string,
            iterator_next_n(string_begin(pt_stringex), 20), string_end(pt_stringex));
        _printstring(pt_string);

        string_assign_range(pt_string, string_end(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_append                     */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        string_append(pt_string, pt_stringex);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "CHINA");
        _printstring(pt_stringex);

        string_append(pt_string, pt_stringex);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, " - Shenyang");
        _printstring(pt_stringex);

        string_append(pt_string, pt_stringex);
        _printstring(pt_string);

        string_clear(pt_stringex);
        _printstring(pt_stringex);

        string_append(pt_string, pt_stringex);
        _printstring(pt_string);

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_append_substring           */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        string_append_substring(pt_string, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_append_substring(pt_string, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_append_substring(pt_string, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_stringex);
        string_append_substring(pt_string, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_append_substring(pt_string, pt_stringex, 0, 11);
        _printstring(pt_string);
        string_clear(pt_string);
        string_append_substring(pt_string, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_clear(pt_string);
        string_append_substring(pt_string, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_append_substring(pt_string, pt_stringex, 5, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_append_substring(pt_string, pt_stringex, 5, 10);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_append_substring(pt_string, pt_stringex, 5, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_append_substring(pt_string, pt_stringex, 5, NPOS);
        _printstring(pt_string);

        string_clear(pt_stringex);
        string_assign_cstr(pt_string, "1234567890");
        string_append_substring(pt_string, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_append_substring(pt_string, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_append_substring(pt_string, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_append_cstr                */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_append_cstr(pt_string, "");
        _printstring(pt_string);
        string_append_cstr(pt_string, "Fedora 9");
        _printstring(pt_string);
        string_append_cstr(pt_string, " Linux");
        _printstring(pt_string);
        string_append_cstr(pt_string, "");
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_append_subcstr             */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_append_subcstr(pt_string, "", 0);
        _printstring(pt_string);
        string_append_subcstr(pt_string, "", 100);
        _printstring(pt_string);
        string_append_subcstr(pt_string, "", NPOS);
        _printstring(pt_string);

        string_append_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 0);
        _printstring(pt_string);
        string_append_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 10);
        _printstring(pt_string);
        string_clear(pt_string);
        string_append_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 100);
        _printstring(pt_string);
        string_clear(pt_string);
        string_append_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_append_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_append_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 10);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_append_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_append_subcstr(pt_string, "abcdefghijklmnopqrstuvwxyz", NPOS);
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_append_char                */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_append_char(pt_string, 0, 'A');
        _printstring(pt_string);
        string_append_char(pt_string, 10, 'B');
        _printstring(pt_string);
        string_append_char(pt_string, 20, 'C');
        _printstring(pt_string);
        string_append_char(pt_string, 0, 'D');
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_append_range               */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        string_append_range(pt_string, string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "abcdefghijklmnopqrstuvwxyz");
        _printstring(pt_stringex);
        string_append_range(pt_string, string_begin(pt_stringex), string_begin(pt_stringex));
        _printstring(pt_string);
        string_append_range(pt_string, string_begin(pt_stringex),
            iterator_next_n(string_begin(pt_stringex), 5));
        _printstring(pt_string);

        string_append_range(pt_string, iterator_next_n(string_begin(pt_stringex), 10),
            iterator_next_n(string_begin(pt_stringex), 20));
        _printstring(pt_string);

        string_append_range(pt_string, iterator_next_n(string_begin(pt_stringex), 23),
            string_end(pt_stringex));
        _printstring(pt_string);

        string_append_range(pt_string, string_end(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_insert                     */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_insert(pt_string, string_begin(pt_string), 'A');
        _printstring(pt_string);
        string_insert(pt_string, string_begin(pt_string), 'B');
        _printstring(pt_string);
        string_insert(pt_string, string_end(pt_string), 'C');
        _printstring(pt_string);
        string_insert(pt_string, iterator_next(string_begin(pt_string)), 'D');
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_insert_n                   */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_insert_n(pt_string, string_end(pt_string), 0, 'A');
        _printstring(pt_string);
        string_insert_n(pt_string, string_end(pt_string), 3, 'B');
        _printstring(pt_string);
        string_insert_n(pt_string, string_end(pt_string), 5, 'C');
        _printstring(pt_string);
        string_insert_n(pt_string, string_begin(pt_string), 10, 'D');
        _printstring(pt_string);
        string_insert_n(pt_string, iterator_next_n(string_begin(pt_string), 5), 7, 'E');
        _printstring(pt_string);
        string_insert_n(pt_string, iterator_prev_n(string_end(pt_string), 2), 2, 'F');
        _printstring(pt_string);
        string_insert_n(pt_string, iterator_prev_n(string_end(pt_string), 5), 0, 'G');
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_insert_string              */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        string_insert_string(pt_string, 0, pt_stringex);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, " Enterprise");
        string_insert_string(pt_string, 0, pt_stringex);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "Redhat");
        string_insert_string(pt_string, 0, pt_stringex);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, " 5");
        string_insert_string(pt_string, string_length(pt_string), pt_stringex);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, " Linux");
        string_insert_string(pt_string,  string_length(pt_string) - 2, pt_stringex);
        _printstring(pt_string);

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_insert_substring           */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        string_insert_substring(pt_string, 0, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_insert_substring(pt_string, 0, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_insert_substring(pt_string, 0, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "abcdefghijklmnopqrstuvwxyz");
        string_clear(pt_string);
        string_insert_substring(pt_string, 0, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_clear(pt_string);
        string_insert_substring(pt_string, 0, pt_stringex, 0, 10);
        _printstring(pt_string);
        string_clear(pt_string);
        string_insert_substring(pt_string, 0, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_clear(pt_string);
        string_insert_substring(pt_string, 0, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "abcdefghijklmnopqrstuvwxyz");
        string_clear(pt_string);
        string_insert_substring(pt_string, 0, pt_stringex, 5, 0);
        _printstring(pt_string);
        string_clear(pt_string);
        string_insert_substring(pt_string, 0, pt_stringex, 5, 10);
        _printstring(pt_string);
        string_clear(pt_string);
        string_insert_substring(pt_string, 0, pt_stringex, 5, 100);
        _printstring(pt_string);
        string_clear(pt_string);
        string_insert_substring(pt_string, 0, pt_stringex, 5, NPOS);
        _printstring(pt_string);
        string_clear(pt_string);
        string_insert_substring(pt_string, 0, pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "abcdefghijklmnopqrstuvwxyz");
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, 0, pt_stringex, 5, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, 0, pt_stringex, 5, 10);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, 0, pt_stringex, 5, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, 0, pt_stringex, 5, NPOS);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, 0, pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "abcdefghijklmnopqrstuvwxyz");
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, 5, pt_stringex, 5, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, 5, pt_stringex, 5, 10);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, 5, pt_stringex, 5, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, 5, pt_stringex, 5, NPOS);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, 5, pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "abcdefghijklmnopqrstuvwxyz");
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, string_length(pt_string), pt_stringex, 5, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, string_length(pt_string), pt_stringex, 5, 10);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, string_length(pt_string), pt_stringex, 5, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, string_length(pt_string), pt_stringex, 5, NPOS);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_substring(pt_string, string_length(pt_string),
            pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_insert_cstr                */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_insert_cstr(pt_string, 0, "");
        _printstring(pt_string);

        string_insert_cstr(pt_string, 0, "1234567890");
        _printstring(pt_string);

        string_insert_cstr(pt_string, 0, "Linux");
        _printstring(pt_string);

        string_insert_cstr(pt_string, 10, "Fedora");
        _printstring(pt_string);

        string_insert_cstr(pt_string, string_length(pt_string), "Redhat");
        _printstring(pt_string);

        string_insert_cstr(pt_string, 10, "");
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_insert_subcstr             */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_insert_subcstr(pt_string, 0, "", 0);
        _printstring(pt_string);
        string_insert_subcstr(pt_string, 0, "", 100);
        _printstring(pt_string);
        string_insert_subcstr(pt_string, 0, "", NPOS);
        _printstring(pt_string);

        string_clear(pt_string);
        string_insert_subcstr(pt_string, 0, "abcdefghijklmnopqrstuvwxyz", 0);
        _printstring(pt_string);
        string_clear(pt_string);
        string_insert_subcstr(pt_string, 0, "abcdefghijklmnopqrstuvwxyz", 10);
        _printstring(pt_string);
        string_clear(pt_string);
        string_insert_subcstr(pt_string, 0, "abcdefghijklmnopqrstuvwxyz", 100);
        _printstring(pt_string);
        string_clear(pt_string);
        string_insert_subcstr(pt_string, 0, "abcdefghijklmnopqrstuvwxyz", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_insert_subcstr(pt_string, 0, "abcdefghijklmnopqrstuvwxyz", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_subcstr(pt_string, 0, "abcdefghijklmnopqrstuvwxyz", 10);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_subcstr(pt_string, 0, "abcdefghijklmnopqrstuvwxyz", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_subcstr(pt_string, 0, "abcdefghijklmnopqrstuvwxyz", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_insert_subcstr(pt_string, 5, "abcdefghijklmnopqrstuvwxyz", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_subcstr(pt_string, 5, "abcdefghijklmnopqrstuvwxyz", 10);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_subcstr(pt_string, 5, "abcdefghijklmnopqrstuvwxyz", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_subcstr(pt_string, 5, "abcdefghijklmnopqrstuvwxyz", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_insert_subcstr(pt_string, string_length(pt_string), "abcdefghijklmnopqrstuvwxyz", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_subcstr(pt_string, string_length(pt_string), "abcdefghijklmnopqrstuvwxyz", 10);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_subcstr(pt_string, string_length(pt_string), "abcdefghijklmnopqrstuvwxyz", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_insert_subcstr(pt_string, string_length(pt_string), "abcdefghijklmnopqrstuvwxyz", NPOS);
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_insert_char                */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_insert_char(pt_string, 0, 0, 'A');
        _printstring(pt_string);
        string_insert_char(pt_string, 0, 4, 'B');
        _printstring(pt_string);
        string_insert_char(pt_string, 0, 9, 'C');
        _printstring(pt_string);
        string_insert_char(pt_string, 10, 10, 'D');
        _printstring(pt_string);
        string_insert_char(pt_string, string_length(pt_string), 3, 'E');
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_insert_range               */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        string_insert_range(pt_string, string_begin(pt_string),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "abcdefghijklmnopqrstuvwxyz");
        string_insert_range(pt_string, string_begin(pt_string),
            string_begin(pt_stringex), string_begin(pt_stringex));
        _printstring(pt_string);
        string_insert_range(pt_string, string_begin(pt_string),
            string_begin(pt_stringex), iterator_next_n(string_begin(pt_stringex), 4));
        _printstring(pt_string);
        string_insert_range(pt_string, string_end(pt_string),
            iterator_next_n(string_begin(pt_stringex), 10),
            iterator_next_n(string_begin(pt_stringex), 20));
        _printstring(pt_string);
        string_insert_range(pt_string, iterator_next_n(string_begin(pt_string), 5),
            iterator_prev_n(string_end(pt_stringex), 5), string_end(pt_stringex));
        _printstring(pt_string);

        string_insert_range(pt_string, string_end(pt_string),
            string_end(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_erase                      */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_assign_cstr(pt_string, "CHINA");
        _printstring(pt_string);
        string_erase(pt_string, string_begin(pt_string));
        _printstring(pt_string);
        string_erase(pt_string, iterator_next(string_begin(pt_string)));
        _printstring(pt_string);
        string_erase(pt_string, iterator_prev(string_end(pt_string)));
        _printstring(pt_string);
        while(!string_empty(pt_string))
        {
            string_erase(pt_string, string_begin(pt_string));
            _printstring(pt_string);
        }

        string_destroy(pt_string);
    }
    /*string_erase_range                */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_erase_range(pt_string, string_begin(pt_string), string_end(pt_string));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Redhat Enterprise Linux 5");
        _printstring(pt_string);
        string_erase_range(pt_string, string_begin(pt_string), string_begin(pt_string));
        _printstring(pt_string);
        string_erase_range(pt_string,
            string_begin(pt_string), iterator_next_n(string_begin(pt_string), 7));
        _printstring(pt_string);
        string_erase_range(pt_string,
            iterator_next_n(string_begin(pt_string), 10),
            iterator_next_n(string_begin(pt_string), 17));
        _printstring(pt_string);
        string_erase_range(pt_string, iterator_prev(string_end(pt_string)), string_end(pt_string));
        _printstring(pt_string);
        string_erase_range(pt_string, string_end(pt_string), string_end(pt_string));
        _printstring(pt_string);
        string_erase_range(pt_string, string_begin(pt_string), string_end(pt_string));
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_erase_substring            */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_erase_substring(pt_string, 0, 0);
        _printstring(pt_string);
        string_erase_substring(pt_string, 0, 100);
        _printstring(pt_string);
        string_erase_substring(pt_string, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_erase_substring(pt_string, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_erase_substring(pt_string, 0, 10);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_erase_substring(pt_string, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_erase_substring(pt_string, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_erase_substring(pt_string, 5, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_erase_substring(pt_string, 5, 10);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_erase_substring(pt_string, 5, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_erase_substring(pt_string, 5, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_erase_substring(pt_string, string_length(pt_string), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_erase_substring(pt_string, string_length(pt_string), 10);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_erase_substring(pt_string, string_length(pt_string), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "abcdefghijklmnopqrstuvwxyz");
        string_erase_substring(pt_string, string_length(pt_string), NPOS);
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_replace                    */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        string_replace(pt_string, 0, 0, pt_stringex);
        _printstring(pt_string);
        string_replace(pt_string, 0, 100, pt_stringex);
        _printstring(pt_string);
        string_replace(pt_string, 0, NPOS, pt_stringex);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "CHINA");
        string_replace(pt_string, 0, 0, pt_stringex);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace(pt_string, 0, 100, pt_stringex);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace(pt_string, 0, NPOS, pt_stringex);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, 0, 0, pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, 0, 2, pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, 0, 100, pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, 0, NPOS, pt_stringex);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, 2, 0, pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, 2, 7, pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, 2, 100, pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, 2, NPOS, pt_stringex);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, string_length(pt_string), 0, pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, string_length(pt_string), 100, pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, string_length(pt_string), NPOS, pt_stringex);
        _printstring(pt_string);

        string_clear(pt_stringex);
        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, 2, 0, pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, 2, 7, pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, 2, 100, pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace(pt_string, 2, NPOS, pt_stringex);
        _printstring(pt_string);

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_replace_substring          */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        string_replace_substring(pt_string, 0, 0, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_replace_substring(pt_string, 0, 100, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "Shenyang");
        string_clear(pt_string);
        string_replace_substring(pt_string, 0, 0, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_substring(pt_string, 0, 100, pt_stringex, 0, 4);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_substring(pt_string, 0, 0, pt_stringex, 0, NPOS);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_substring(pt_string, 0, 100, pt_stringex, 2, 0);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, 2, 2);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_substring(pt_string, 0, 0, pt_stringex, 2, 100);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_substring(pt_string, 0, 100, pt_stringex, 2, NPOS);
        _printstring(pt_string);

        string_clear(pt_stringex);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 0, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 5, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 100, pt_stringex, 0, NPOS);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 6, 0, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 6, 2, pt_stringex, 0, NPOS);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 6, 100, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 6, NPOS, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 0, pt_stringex, 0, NPOS);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 100, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), NPOS, pt_stringex, 0, 100);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "Shenyang");
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 0, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 0, pt_stringex, 0, 4);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 0, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 0, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 0, pt_stringex, 4, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 0, pt_stringex, 4, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 0, pt_stringex, 4, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 0, pt_stringex, 4, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 0, pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 0, pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 0, pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 5, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 5, pt_stringex, 0, 4);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 5, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 5, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 5, pt_stringex, 4, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 5, pt_stringex, 4, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 5, pt_stringex, 4, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 5, pt_stringex, 4, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 5, pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 5, pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 5, pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 100, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 100, pt_stringex, 0, 4);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 100, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 100, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 100, pt_stringex, 4, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 100, pt_stringex, 4, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 100, pt_stringex, 4, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 100, pt_stringex, 4, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 100, pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 100, pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, 100, pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, 0, 4);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, 4, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, 4, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, 4, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, 4, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 0, NPOS, pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 0, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 0, pt_stringex, 0, 4);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 0, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 0, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 0, pt_stringex, 4, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 0, pt_stringex, 4, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 0, pt_stringex, 4, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 0, pt_stringex, 4, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 0, pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 0, pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 0, pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 3, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 3, pt_stringex, 0, 4);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 3, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 3, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 3, pt_stringex, 4, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 3, pt_stringex, 4, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 3, pt_stringex, 4, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 3, pt_stringex, 4, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 3, pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 3, pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 3, pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 100, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 100, pt_stringex, 0, 4);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 100, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 100, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 100, pt_stringex, 4, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 100, pt_stringex, 4, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 100, pt_stringex, 4, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 100, pt_stringex, 4, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 100, pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 100, pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, 100, pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, NPOS, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, NPOS, pt_stringex, 0, 4);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, NPOS, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, NPOS, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, NPOS, pt_stringex, 4, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, NPOS, pt_stringex, 4, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, NPOS, pt_stringex, 4, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, NPOS, pt_stringex, 4, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, NPOS, pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, NPOS, pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, 3, NPOS, pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 0, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 0, pt_stringex, 0, 4);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 0, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 0, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 0, pt_stringex, 4, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 0, pt_stringex, 4, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 0, pt_stringex, 4, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 0, pt_stringex, 4, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 0,
            pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 0,
            pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 0,
            pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 100, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 100, pt_stringex, 0, 4);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 100, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 100, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 100, pt_stringex, 4, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 100, pt_stringex, 4, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 100, pt_stringex, 4, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 100, pt_stringex, 4, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 100,
            pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 100,
            pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), 100,
            pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), NPOS, pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), NPOS, pt_stringex, 0, 4);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), NPOS, pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), NPOS, pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), NPOS, pt_stringex, 4, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), NPOS, pt_stringex, 4, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), NPOS, pt_stringex, 4, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), NPOS, pt_stringex, 4, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), NPOS,
            pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), NPOS,
            pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_substring(pt_string, string_length(pt_string), NPOS,
            pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_replace_cstr               */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_replace_cstr(pt_string, 0, 0, "");
        _printstring(pt_string);
        string_replace_cstr(pt_string, 0, 100, "");
        _printstring(pt_string);
        string_replace_cstr(pt_string, 0, NPOS, "");
        _printstring(pt_string);

        string_replace_cstr(pt_string, 0, 0, "Linux");
        _printstring(pt_string);
        string_replace_cstr(pt_string, 0, 100, "Linux");
        _printstring(pt_string);
        string_replace_cstr(pt_string, 0, NPOS, "Linux");
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_cstr(pt_string, 0, 0, "Linux");
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_cstr(pt_string, 0, 8, "Linux");
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_cstr(pt_string, 0, 100, "Linux");
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_cstr(pt_string, 0, NPOS, "Linux");
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_cstr(pt_string, 3, 0, "Linux");
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_cstr(pt_string, 3, 4, "Linux");
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_cstr(pt_string, 3, 100, "Linux");
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_cstr(pt_string, 3, NPOS, "Linux");
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_cstr(pt_string, string_length(pt_string), 0, "Linux");
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_cstr(pt_string, string_length(pt_string), 100, "Linux");
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_cstr(pt_string, string_length(pt_string), NPOS, "Linux");
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_replace_subcstr            */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_replace_subcstr(pt_string, 0, 0, "", 0);
        _printstring(pt_string);
        string_replace_subcstr(pt_string, 0, 0, "", 100);
        _printstring(pt_string);
        string_replace_subcstr(pt_string, 0, 0, "", NPOS);
        _printstring(pt_string);

        string_replace_subcstr(pt_string, 0, 100, "", 0);
        _printstring(pt_string);
        string_replace_subcstr(pt_string, 0, 100, "", 100);
        _printstring(pt_string);
        string_replace_subcstr(pt_string, 0, 100, "", NPOS);

        string_replace_subcstr(pt_string, 0, NPOS, "", 0);
        _printstring(pt_string);
        string_replace_subcstr(pt_string, 0, NPOS, "", 100);
        _printstring(pt_string);
        string_replace_subcstr(pt_string, 0, NPOS, "", NPOS);
        _printstring(pt_string);

        string_clear(pt_string);
        string_replace_subcstr(pt_string, 0, 0, "Linux", 0);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_subcstr(pt_string, 0, 0, "Linux", 3);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_subcstr(pt_string, 0, 0, "Linux", 100);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_subcstr(pt_string, 0, 0, "Linux", NPOS);
        _printstring(pt_string);

        string_clear(pt_string);
        string_replace_subcstr(pt_string, 0, 100, "Linux", 0);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_subcstr(pt_string, 0, 100, "Linux", 3);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_subcstr(pt_string, 0, 100, "Linux", 100);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_subcstr(pt_string, 0, 100, "Linux", NPOS);
        _printstring(pt_string);

        string_clear(pt_string);
        string_replace_subcstr(pt_string, 0, NPOS, "Linux", 0);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_subcstr(pt_string, 0, NPOS, "Linux", 3);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_subcstr(pt_string, 0, NPOS, "Linux", 100);
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_subcstr(pt_string, 0, NPOS, "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 0, "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 0, "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 0, "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 3, "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 3, "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 3, "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 100, "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 100, "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 100, "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, NPOS, "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, NPOS, "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, NPOS, "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 0, "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 0, "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 0, "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 3, "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 3, "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 3, "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 100, "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 100, "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 100, "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, NPOS, "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, NPOS, "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, NPOS, "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), 0, "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), 0, "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), 0, "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), 100, "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), 100, "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), 100, "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), NPOS, "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), NPOS, "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), NPOS, "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 0, "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 0, "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 0, "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 0, "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 3, "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 3, "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 3, "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 3, "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 100, "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 100, "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 100, "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, 100, "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, NPOS, "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, NPOS, "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, NPOS, "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 0, NPOS, "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 0, "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 0, "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 0, "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 0, "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 1, "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 1, "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 1, "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 1, "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 100, "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 100, "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 100, "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, 100, "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, NPOS, "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, NPOS, "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, NPOS, "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, 3, NPOS, "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), 0, "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), 0, "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), 0, "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), 0, "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), 100, "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), 100, "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), 100, "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), 100, "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), NPOS, "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), NPOS, "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), NPOS, "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_subcstr(pt_string, string_length(pt_string), NPOS, "Linux", NPOS);
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_replace_char               */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_replace_char(pt_string, 0, 0, 0, 'A');
        _printstring(pt_string);
        string_replace_char(pt_string, 0, 100, 0, 'B');
        _printstring(pt_string);
        string_replace_char(pt_string, 0, NPOS, 0, 'C');
        _printstring(pt_string);

        string_clear(pt_string);
        string_replace_char(pt_string, 0, 0, 10, 'D');
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_char(pt_string, 0, 100, 10, 'E');
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_char(pt_string, 0, NPOS, 10, 'F');
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 0, 0, 0, 'G');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 0, 4, 0, 'H');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 0, 100, 0, 'I');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 0, NPOS, 0, 'J');
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 0, 0, 10, 'K');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 0, 4, 10, 'L');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 0, 100, 10, 'M');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 0, NPOS, 10, 'N');
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 4, 0, 0, 'O');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 4, 4, 0, 'P');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 4, 100, 0, 'Q');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 4, NPOS, 0, 'R');
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 4, 0, 10, 'S');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 4, 4, 10, 'T');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 4, 100, 10, 'U');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, 4, NPOS, 10, 'V');
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, string_length(pt_string), 0, 0, 'W');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, string_length(pt_string), 100, 0, 'X');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, string_length(pt_string), NPOS, 0, 'Y');
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, string_length(pt_string), 0, 10, 'Z');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, string_length(pt_string), 100, 10, '$');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_replace_char(pt_string, string_length(pt_string), NPOS, 10, '&');
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_range_replace              */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        string_range_replace(pt_string, string_begin(pt_string), string_end(pt_string), pt_stringex);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "1234567890");
        string_range_replace(pt_string, string_begin(pt_string), string_begin(pt_string), pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_range_replace(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 4), pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_range_replace(pt_string, iterator_next_n(string_begin(pt_string), 4),
            iterator_next_n(string_begin(pt_string), 7), pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_range_replace(pt_string, iterator_next_n(string_begin(pt_string), 6),
            string_end(pt_string), pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_range_replace(pt_string, string_end(pt_string), string_end(pt_string), pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_range_replace(pt_string, string_begin(pt_string), string_end(pt_string), pt_stringex);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "Linux");
        string_assign_cstr(pt_string, "1234567890");
        string_range_replace(pt_string, string_begin(pt_string), string_begin(pt_string), pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_range_replace(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 4), pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_range_replace(pt_string, iterator_next_n(string_begin(pt_string), 4),
            iterator_next_n(string_begin(pt_string), 7), pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_range_replace(pt_string, iterator_next_n(string_begin(pt_string), 6),
            string_end(pt_string), pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_range_replace(pt_string, string_end(pt_string), string_end(pt_string), pt_stringex);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "1234567890");
        string_range_replace(pt_string, string_begin(pt_string), string_end(pt_string), pt_stringex);
        _printstring(pt_string);

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_range_replace_substring    */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        string_range_replace_substring(pt_string, string_begin(pt_string), string_end(pt_string),
            pt_stringex, 0, 0);
        _printstring(pt_string);
        string_range_replace_substring(pt_string, string_begin(pt_string), string_end(pt_string),
            pt_stringex, 0, 100);
        _printstring(pt_string);
        string_range_replace_substring(pt_string, string_begin(pt_string), string_end(pt_string),
            pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "Linux");
        string_clear(pt_string);
        string_range_replace_substring(pt_string, string_begin(pt_string), string_end(pt_string),
            pt_stringex, 0, 0);
        _printstring(pt_string);
        string_clear(pt_string);
        string_range_replace_substring(pt_string, string_begin(pt_string), string_end(pt_string),
            pt_stringex, 0, 4);
        _printstring(pt_string);
        string_clear(pt_string);
        string_range_replace_substring(pt_string, string_begin(pt_string), string_end(pt_string),
            pt_stringex, 0, 100);
        _printstring(pt_string);
        string_clear(pt_string);
        string_range_replace_substring(pt_string, string_begin(pt_string), string_end(pt_string),
            pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_clear(pt_stringex);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_begin(pt_string),
            pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_begin(pt_string),
            pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_begin(pt_string),
            pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_end(pt_string), string_end(pt_string),
            pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_end(pt_string), string_end(pt_string),
            pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_end(pt_string), string_end(pt_string),
            pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_end(pt_string),
            pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_end(pt_string),
            pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_end(pt_string),
            pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "Linux");
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_begin(pt_string),
            pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_begin(pt_string),
            pt_stringex, 0, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_begin(pt_string),
            pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_begin(pt_string),
            pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_begin(pt_string),
            pt_stringex, 2, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_begin(pt_string),
            pt_stringex, 2, 2);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_begin(pt_string),
            pt_stringex, 2, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_begin(pt_string),
            pt_stringex, 2, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_begin(pt_string),
            pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_begin(pt_string),
            pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string), string_begin(pt_string),
            pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), pt_stringex, 0, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), pt_stringex, 2, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), pt_stringex, 2, 2);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), pt_stringex, 2, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), pt_stringex, 2, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3),
            pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3),
            pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3),
            pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), pt_stringex, 0, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), pt_stringex, 2, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), pt_stringex, 2, 2);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), pt_stringex, 2, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), pt_stringex, 2, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5),
            pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5),
            pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5),
            pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), pt_stringex, 0, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), pt_stringex, 2, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), pt_stringex, 2, 2);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), pt_stringex, 2, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), pt_stringex, 2, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_end(pt_string),
            string_end(pt_string), pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_end(pt_string),
            string_end(pt_string), pt_stringex, 0, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_end(pt_string),
            string_end(pt_string), pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_end(pt_string),
            string_end(pt_string), pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_end(pt_string),
            string_end(pt_string), pt_stringex, 2, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_end(pt_string),
            string_end(pt_string), pt_stringex, 2, 2);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_end(pt_string),
            string_end(pt_string), pt_stringex, 2, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_end(pt_string),
            string_end(pt_string), pt_stringex, 2, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_end(pt_string),
            string_end(pt_string), pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_end(pt_string),
            string_end(pt_string), pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_end(pt_string),
            string_end(pt_string), pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            string_end(pt_string), pt_stringex, 0, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            string_end(pt_string), pt_stringex, 0, 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            string_end(pt_string), pt_stringex, 0, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            string_end(pt_string), pt_stringex, 0, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            string_end(pt_string), pt_stringex, 2, 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            string_end(pt_string), pt_stringex, 2, 2);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            string_end(pt_string), pt_stringex, 2, 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            string_end(pt_string), pt_stringex, 2, NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            string_end(pt_string), pt_stringex, string_length(pt_stringex), 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            string_end(pt_string), pt_stringex, string_length(pt_stringex), 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_substring(pt_string, string_begin(pt_string),
            string_end(pt_string), pt_stringex, string_length(pt_stringex), NPOS);
        _printstring(pt_string);

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_range_replace_cstr         */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_range_replace_cstr(pt_string, string_begin(pt_string), string_end(pt_string), "");
        _printstring(pt_string);

        string_range_replace_cstr(pt_string,
            string_begin(pt_string), string_end(pt_string), "Linux");
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_cstr(pt_string,
            string_begin(pt_string), string_begin(pt_string), "Linux");
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_cstr(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), "Linux");
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_cstr(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), "Linux");
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_cstr(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), "Linux");
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_cstr(pt_string, string_end(pt_string),
            string_end(pt_string), "Linux");
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_cstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "Linux");
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_range_replace_subcstr      */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "", 0);
        _printstring(pt_string);
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "", 100);
        _printstring(pt_string);
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "", NPOS);
        _printstring(pt_string);

        string_clear(pt_string);
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "Linux", 0);
        _printstring(pt_string);
        string_clear(pt_string);
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "Linux", 3);
        _printstring(pt_string);
        string_clear(pt_string);
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "Linux", 100);
        _printstring(pt_string);
        string_clear(pt_string);
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_begin(pt_string), "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_begin(pt_string), "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_begin(pt_string), "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_end(pt_string),
            string_end(pt_string), "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_end(pt_string),
            string_end(pt_string), "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_end(pt_string),
            string_end(pt_string), "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_begin(pt_string), "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_begin(pt_string), "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_begin(pt_string), "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_begin(pt_string), "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_end(pt_string),
            string_end(pt_string), "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_end(pt_string),
            string_end(pt_string), "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_end(pt_string),
            string_end(pt_string), "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_end(pt_string),
            string_end(pt_string), "Linux", NPOS);
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "Linux", 0);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "Linux", 3);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "Linux", 100);
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_subcstr(pt_string, string_begin(pt_string),
            string_end(pt_string), "Linux", NPOS);
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_range_replace_char         */
    {
        string_t* pt_string = create_string();
        if(pt_string == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_clear(pt_string);
        string_range_replace_char(pt_string, string_begin(pt_string),
            string_end(pt_string), 0, 'A');
        _printstring(pt_string);
        string_clear(pt_string);
        string_range_replace_char(pt_string, string_begin(pt_string),
            string_end(pt_string), 10, 'B');
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_char(pt_string, string_begin(pt_string),
            string_begin(pt_string), 0, 'C');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_char(pt_string, string_begin(pt_string),
            string_begin(pt_string), 10, 'D');
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_char(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), 0, 'E');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_char(pt_string, string_begin(pt_string),
            iterator_next_n(string_begin(pt_string), 3), 10, 'F');
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_char(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), 0, 'G');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_char(pt_string, iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5), 10, 'H');
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_char(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), 0, 'I');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_char(pt_string, iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_string), 10, 'J');
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_char(pt_string, string_end(pt_string),
            string_end(pt_string), 0, 'K');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_char(pt_string, string_end(pt_string),
            string_end(pt_string), 10, 'L');
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_range_replace_char(pt_string, string_begin(pt_string),
            string_end(pt_string), 0, 'M');
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_range_replace_char(pt_string, string_begin(pt_string),
            string_end(pt_string), 10, 'N');
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_replace_range              */
    {
        string_t* pt_string = create_string();
        string_t* pt_stringex = create_string();
        if(pt_string == NULL || pt_stringex == NULL)
        {
            return;
        }
        string_init(pt_string);
        string_init(pt_stringex);

        string_replace_range(pt_string, string_begin(pt_string), string_end(pt_string),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "Linux");
        string_clear(pt_string);
        string_replace_range(pt_string, string_begin(pt_string), string_end(pt_string),
            string_begin(pt_stringex), string_begin(pt_stringex));
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_range(pt_string, string_begin(pt_string), string_end(pt_string),
            string_begin(pt_stringex), iterator_next_n(string_begin(pt_stringex), 2));
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_range(pt_string, string_begin(pt_string), string_end(pt_string),
            iterator_next_n(string_begin(pt_stringex), 2),
            iterator_next_n(string_begin(pt_stringex), 4));
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_range(pt_string, string_begin(pt_string), string_end(pt_string),
            iterator_next_n(string_begin(pt_stringex), 3), string_end(pt_stringex));
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_range(pt_string, string_begin(pt_string), string_end(pt_string),
            string_end(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);
        string_clear(pt_string);
        string_replace_range(pt_string, string_begin(pt_string), string_end(pt_string),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_clear(pt_stringex);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string, string_begin(pt_string), string_begin(pt_string),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_begin(pt_string), iterator_next_n(string_begin(pt_string), 3),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            iterator_next_n(string_begin(pt_string), 5), string_end(pt_string),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string, string_end(pt_string), string_end(pt_string),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string, string_begin(pt_string), string_end(pt_string),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_assign_cstr(pt_stringex, "Linux");
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string, string_begin(pt_string), string_begin(pt_string),
            string_begin(pt_stringex), string_begin(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string, string_begin(pt_string), string_begin(pt_string),
            string_begin(pt_stringex), iterator_next_n(string_begin(pt_stringex), 2));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string, string_begin(pt_string), string_begin(pt_string),
            iterator_next_n(string_begin(pt_stringex), 2),
            iterator_next_n(string_begin(pt_stringex), 4));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string, string_begin(pt_string), string_begin(pt_string),
            iterator_next_n(string_begin(pt_stringex), 3), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string, string_begin(pt_string), string_begin(pt_string),
            string_end(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string, string_begin(pt_string), string_begin(pt_string),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_begin(pt_string), iterator_next_n(string_begin(pt_string), 3),
            string_begin(pt_stringex), string_begin(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_begin(pt_string), iterator_next_n(string_begin(pt_string), 3),
            string_begin(pt_stringex), iterator_next_n(string_begin(pt_stringex), 2));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_begin(pt_string), iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_stringex), 2),
            iterator_next_n(string_begin(pt_stringex), 4));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_begin(pt_string), iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_stringex), 3), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_begin(pt_string), iterator_next_n(string_begin(pt_string), 3),
            string_end(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_begin(pt_string), iterator_next_n(string_begin(pt_string), 3),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5),
            string_begin(pt_stringex), string_begin(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5),
            string_begin(pt_stringex), iterator_next_n(string_begin(pt_stringex), 2));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5),
            iterator_next_n(string_begin(pt_stringex), 2),
            iterator_next_n(string_begin(pt_stringex), 4));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5),
            iterator_next_n(string_begin(pt_stringex), 3), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5),
            string_end(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            iterator_next_n(string_begin(pt_string), 3),
            iterator_next_n(string_begin(pt_string), 5),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            iterator_next_n(string_begin(pt_string), 5), string_end(pt_string),
            string_begin(pt_stringex), string_begin(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            iterator_next_n(string_begin(pt_string), 5), string_end(pt_string),
            string_begin(pt_stringex), iterator_next_n(string_begin(pt_stringex), 2));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            iterator_next_n(string_begin(pt_string), 5), string_end(pt_string),
            iterator_next_n(string_begin(pt_stringex), 2),
            iterator_next_n(string_begin(pt_stringex), 4));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            iterator_next_n(string_begin(pt_string), 5), string_end(pt_string),
            iterator_next_n(string_begin(pt_stringex), 3), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            iterator_next_n(string_begin(pt_string), 5), string_end(pt_string),
            string_end(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            iterator_next_n(string_begin(pt_string), 5), string_end(pt_string),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_end(pt_string), string_end(pt_string),
            string_begin(pt_stringex), string_begin(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_end(pt_string), string_end(pt_string),
            string_begin(pt_stringex), iterator_next_n(string_begin(pt_stringex), 2));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_end(pt_string), string_end(pt_string),
            iterator_next_n(string_begin(pt_stringex), 2),
            iterator_next_n(string_begin(pt_stringex), 4));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_end(pt_string), string_end(pt_string),
            iterator_next_n(string_begin(pt_stringex), 3), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_end(pt_string), string_end(pt_string),
            string_end(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_end(pt_string), string_end(pt_string),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_begin(pt_string), string_end(pt_string),
            string_begin(pt_stringex), string_begin(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_begin(pt_string), string_end(pt_string),
            string_begin(pt_stringex), iterator_next_n(string_begin(pt_stringex), 2));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_begin(pt_string), string_end(pt_string),
            iterator_next_n(string_begin(pt_stringex), 2),
            iterator_next_n(string_begin(pt_stringex), 4));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_begin(pt_string), string_end(pt_string),
            iterator_next_n(string_begin(pt_stringex), 3), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_begin(pt_string), string_end(pt_string),
            string_end(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);
        string_assign_cstr(pt_string, "Windows");
        string_replace_range(pt_string,
            string_begin(pt_string), string_end(pt_string),
            string_begin(pt_stringex), string_end(pt_stringex));
        _printstring(pt_string);

        string_destroy(pt_string);
        string_destroy(pt_stringex);
    }
    /*string_output                     */
    {
        string_t* pt_string = create_string();
        FILE* fp_str = fopen("string_output.txt", "w");
        if(pt_string == NULL || fp_str == NULL)
        {
            return;
        }

        string_init(pt_string);

        string_output(pt_string, stdout);
        string_output(pt_string, fp_str);

        string_assign_cstr(pt_string, "Windows\nLinux\nUnix\n");
        string_output(pt_string, stderr);
        string_output(pt_string, fp_str);

        fclose(fp_str);
        string_destroy(pt_string);
    }
    /*string_input                      */
    {
        string_t* pt_string = create_string();
        FILE* fp_str = fopen("string_output.txt", "r");
        if(pt_string == NULL || fp_str == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_input(pt_string, stdin);
        _printstring(pt_string);
        string_input(pt_string, fp_str);
        _printstring(pt_string);

        fclose(fp_str);
        string_destroy(pt_string);
    }
    /*string_getline                    */
    {
        string_t* pt_string = create_string();
        FILE* fp_str = fopen("string_output.txt", "r");
        if(pt_string == NULL || fp_str == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_getline(pt_string, stdin);
        _printstring(pt_string);
        string_getline(pt_string, fp_str);
        _printstring(pt_string);

        string_destroy(pt_string);
    }
    /*string_getline_delimiter          */
    {
        string_t* pt_string = create_string();
        FILE* fp_str = fopen("string_output.txt", "r");
        if(pt_string == NULL || fp_str == NULL)
        {
            return;
        }
        string_init(pt_string);

        string_getline_delimiter(pt_string, stdin, 'p');
        _printstring(pt_string);
        string_getline_delimiter(pt_string, fp_str, 'n');
        _printstring(pt_string);

        string_destroy(pt_string);
    }

    argc = 0;
    argv = NULL;
}

void test_string_getline(void)
{
}

/** local function implementation section **/
static void _printstring(const string_t* cpt_string)
{
    assert(cpt_string != NULL);
    printf("===================================\n");
    printf("empty : %d, size : %d, length : %d, capacity : %d, max size : %u\nc_str : %s\n",
        string_empty(cpt_string), string_size(cpt_string), string_length(cpt_string),
        string_capacity(cpt_string), string_max_size(cpt_string), string_c_str(cpt_string));
}

/** eof **/

