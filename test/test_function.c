/*
 *  The implementation of function test.
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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

/** include section **/
#include <stdio.h>
#include <stdarg.h>

#include "cfunctional.h"

#include "test_function.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_function(void)
{
    /* test plus */
    printf("***** test plus function *****\n");
    {
        char c_first = 'a';
        char c_second = 'b';
        char c_output = '\0';
        fun_plus_char(&c_first, &c_second, &c_output);
        printf("first:%c(%d), second:%c(%d), output:%c(%d)\n", 
            c_first, c_first, c_second, c_second, c_output, c_output);
    }
    {
        unsigned char uc_first = 'a';
        unsigned char uc_second = 'b';
        unsigned char uc_output = '\0';
        fun_plus_uchar(&uc_first, &uc_second, &uc_output);
        printf("first:%c(%d), second:%c(%d), output:%c(%d)\n", 
            uc_first, uc_first, uc_second, uc_second, uc_output, uc_output);
    }
    {
        short h_first = 90;
        short h_second = -230;
        short h_output = 0;
        fun_plus_short(&h_first, &h_second, &h_output);
        printf("first:%hd, second:%hd, output:%hd\n", 
            h_first, h_second, h_output);
    }
    {
        unsigned short uh_first = -90;
        unsigned short uh_second = 230;
        unsigned short uh_output = 0;
        fun_plus_ushort(&uh_first, &uh_second, &uh_output);
        printf("first:%hu, second:%hu, output:%hu\n", 
            uh_first, uh_second, uh_output);
    }
    {
        int n_first = 90;
        int n_second = -230;
        int n_output = 0;
        fun_plus_int(&n_first, &n_second, &n_output);
        printf("first:%d, second:%d, output:%d\n", 
            n_first, n_second, n_output);
    }
    {
        unsigned int un_first = 90;
        unsigned int un_second = -230;
        unsigned int un_output = 0;
        fun_plus_uint(&un_first, &un_second, &un_output);
        printf("first:%u, second:%u, output:%u\n", 
            un_first, un_second, un_output);
    }
    {
        long l_first = 90;
        long l_second = -230;
        long l_output = 0;
        fun_plus_long(&l_first, &l_second, &l_output);
        printf("first:%ld, second:%ld, output:%ld\n", 
            l_first, l_second, l_output);
    }
    {
        unsigned long ul_first = 90;
        unsigned long ul_second = -230;
        unsigned long ul_output = 0;
        fun_plus_ulong(&ul_first, &ul_second, &ul_output);
        printf("first:%lu, second:%lu, output:%lu\n", 
            ul_first, ul_second, ul_output);
    }
    {
        float f_first = 39.4509;
        float f_second = -32.445;
        float f_output = 0.0;
        fun_plus_float(&f_first, &f_second, &f_output);
        printf("first:%f, second:%f, output:%f\n", 
            f_first, f_second, f_output);
    }
    {
        double d_first = 39.4509;
        double d_second = -32.445;
        double d_output = 0.0;
        fun_plus_double(&d_first, &d_second, &d_output);
        printf("first:%f, second:%f, output:%f\n", 
            d_first, d_second, d_output);
    }

    /* test minus */
    printf("***** test minus function *****\n");
    {
        char c_first = 'a';
        char c_second = 'b';
        char c_output = '\0';
        fun_minus_char(&c_first, &c_second, &c_output);
        printf("first:%c(%d), second:%c(%d), output:%c(%d)\n", 
            c_first, c_first, c_second, c_second, c_output, c_output);
    }
    {
        unsigned char uc_first = 'a';
        unsigned char uc_second = 'b';
        unsigned char uc_output = '\0';
        fun_minus_uchar(&uc_first, &uc_second, &uc_output);
        printf("first:%c(%d), second:%c(%d), output:%c(%d)\n", 
            uc_first, uc_first, uc_second, uc_second, uc_output, uc_output);
    }
    {
        short h_first = 90;
        short h_second = -230;
        short h_output = 0;
        fun_minus_short(&h_first, &h_second, &h_output);
        printf("first:%hd, second:%hd, output:%hd\n", 
            h_first, h_second, h_output);
    }
    {
        unsigned short uh_first = -90;
        unsigned short uh_second = 230;
        unsigned short uh_output = 0;
        fun_minus_ushort(&uh_first, &uh_second, &uh_output);
        printf("first:%hu, second:%hu, output:%hu\n", 
            uh_first, uh_second, uh_output);
    }
    {
        int n_first = 90;
        int n_second = -230;
        int n_output = 0;
        fun_minus_int(&n_first, &n_second, &n_output);
        printf("first:%d, second:%d, output:%d\n", 
            n_first, n_second, n_output);
    }
    {
        unsigned int un_first = 90;
        unsigned int un_second = -230;
        unsigned int un_output = 0;
        fun_minus_uint(&un_first, &un_second, &un_output);
        printf("first:%u, second:%u, output:%u\n", 
            un_first, un_second, un_output);
    }
    {
        long l_first = 90;
        long l_second = -230;
        long l_output = 0;
        fun_minus_long(&l_first, &l_second, &l_output);
        printf("first:%ld, second:%ld, output:%ld\n", 
            l_first, l_second, l_output);
    }
    {
        unsigned long ul_first = 90;
        unsigned long ul_second = -230;
        unsigned long ul_output = 0;
        fun_minus_ulong(&ul_first, &ul_second, &ul_output);
        printf("first:%lu, second:%lu, output:%lu\n", 
            ul_first, ul_second, ul_output);
    }
    {
        float f_first = 39.4509;
        float f_second = -32.445;
        float f_output = 0.0;
        fun_minus_float(&f_first, &f_second, &f_output);
        printf("first:%f, second:%f, output:%f\n", 
            f_first, f_second, f_output);
    }
    {
        double d_first = 39.4509;
        double d_second = -32.445;
        double d_output = 0.0;
        fun_minus_double(&d_first, &d_second, &d_output);
        printf("first:%f, second:%f, output:%f\n", 
            d_first, d_second, d_output);
    }

    /* test multiplies */
    printf("***** test multiplies function *****\n");
    {
        char c_first = 'a';
        char c_second = 'b';
        char c_output = '\0';
        fun_multiplies_char(&c_first, &c_second, &c_output);
        printf("first:%c(%d), second:%c(%d), output:%c(%d)\n", 
            c_first, c_first, c_second, c_second, c_output, c_output);
    }
    {
        unsigned char uc_first = 'a';
        unsigned char uc_second = 'b';
        unsigned char uc_output = '\0';
        fun_multiplies_uchar(&uc_first, &uc_second, &uc_output);
        printf("first:%c(%d), second:%c(%d), output:%c(%d)\n", 
            uc_first, uc_first, uc_second, uc_second, uc_output, uc_output);
    }
    {
        short h_first = 90;
        short h_second = -230;
        short h_output = 0;
        fun_multiplies_short(&h_first, &h_second, &h_output);
        printf("first:%hd, second:%hd, output:%hd\n", 
            h_first, h_second, h_output);
    }
    {
        unsigned short uh_first = -90;
        unsigned short uh_second = 230;
        unsigned short uh_output = 0;
        fun_multiplies_ushort(&uh_first, &uh_second, &uh_output);
        printf("first:%hu, second:%hu, output:%hu\n", 
            uh_first, uh_second, uh_output);
    }
    {
        int n_first = 90;
        int n_second = -230;
        int n_output = 0;
        fun_multiplies_int(&n_first, &n_second, &n_output);
        printf("first:%d, second:%d, output:%d\n", 
            n_first, n_second, n_output);
    }
    {
        unsigned int un_first = 90;
        unsigned int un_second = -230;
        unsigned int un_output = 0;
        fun_multiplies_uint(&un_first, &un_second, &un_output);
        printf("first:%u, second:%u, output:%u\n", 
            un_first, un_second, un_output);
    }
    {
        long l_first = 90;
        long l_second = -230;
        long l_output = 0;
        fun_multiplies_long(&l_first, &l_second, &l_output);
        printf("first:%ld, second:%ld, output:%ld\n", 
            l_first, l_second, l_output);
    }
    {
        unsigned long ul_first = 90;
        unsigned long ul_second = -230;
        unsigned long ul_output = 0;
        fun_multiplies_ulong(&ul_first, &ul_second, &ul_output);
        printf("first:%lu, second:%lu, output:%lu\n", 
            ul_first, ul_second, ul_output);
    }
    {
        float f_first = 39.4509;
        float f_second = -32.445;
        float f_output = 0.0;
        fun_multiplies_float(&f_first, &f_second, &f_output);
        printf("first:%f, second:%f, output:%f\n", 
            f_first, f_second, f_output);
    }
    {
        double d_first = 39.4509;
        double d_second = -32.445;
        double d_output = 0.0;
        fun_multiplies_double(&d_first, &d_second, &d_output);
        printf("first:%f, second:%f, output:%f\n", 
            d_first, d_second, d_output);
    }

    /* test divides */
    printf("***** test divides function *****\n");
    {
        char c_first = 'a';
        char c_second = 'b';
        char c_output = '\0';
        fun_divides_char(&c_first, &c_second, &c_output);
        printf("first:%c(%d), second:%c(%d), output:%c(%d)\n", 
            c_first, c_first, c_second, c_second, c_output, c_output);
    }
    {
        unsigned char uc_first = 'a';
        unsigned char uc_second = 'b';
        unsigned char uc_output = '\0';
        fun_divides_uchar(&uc_first, &uc_second, &uc_output);
        printf("first:%c(%d), second:%c(%d), output:%c(%d)\n", 
            uc_first, uc_first, uc_second, uc_second, uc_output, uc_output);
    }
    {
        short h_first = 90;
        short h_second = -230;
        short h_output = 0;
        fun_divides_short(&h_first, &h_second, &h_output);
        printf("first:%hd, second:%hd, output:%hd\n", 
            h_first, h_second, h_output);
    }
    {
        unsigned short uh_first = -90;
        unsigned short uh_second = 230;
        unsigned short uh_output = 0;
        fun_divides_ushort(&uh_first, &uh_second, &uh_output);
        printf("first:%hu, second:%hu, output:%hu\n", 
            uh_first, uh_second, uh_output);
    }
    {
        int n_first = 90;
        int n_second = -230;
        int n_output = 0;
        fun_divides_int(&n_first, &n_second, &n_output);
        printf("first:%d, second:%d, output:%d\n", 
            n_first, n_second, n_output);
    }
    {
        unsigned int un_first = 90;
        unsigned int un_second = -230;
        unsigned int un_output = 0;
        fun_divides_uint(&un_first, &un_second, &un_output);
        printf("first:%u, second:%u, output:%u\n", 
            un_first, un_second, un_output);
    }
    {
        long l_first = 90;
        long l_second = -230;
        long l_output = 0;
        fun_divides_long(&l_first, &l_second, &l_output);
        printf("first:%ld, second:%ld, output:%ld\n", 
            l_first, l_second, l_output);
    }
    {
        unsigned long ul_first = 90;
        unsigned long ul_second = -230;
        unsigned long ul_output = 0;
        fun_divides_ulong(&ul_first, &ul_second, &ul_output);
        printf("first:%lu, second:%lu, output:%lu\n", 
            ul_first, ul_second, ul_output);
    }
    {
        float f_first = 39.4509;
        float f_second = -0.1;
        float f_output = 0.0;
        fun_divides_float(&f_first, &f_second, &f_output);
        printf("first:%f, second:%f, output:%f\n", 
            f_first, f_second, f_output);
    }
    {
        double d_first = 39.4509;
        double d_second = -32.445;
        double d_output = 0.0;
        fun_divides_double(&d_first, &d_second, &d_output);
        printf("first:%f, second:%f, output:%f\n", 
            d_first, d_second, d_output);
    }

    /* test modulus */
    printf("***** test modulus function *****\n");
    {
        char c_first = 'a';
        char c_second = 'b';
        char c_output = '\0';
        fun_modulus_char(&c_first, &c_second, &c_output);
        printf("first:%c(%d), second:%c(%d), output:%c(%d)\n", 
            c_first, c_first, c_second, c_second, c_output, c_output);
    }
    {
        unsigned char uc_first = 'a';
        unsigned char uc_second = 'b';
        unsigned char uc_output = '\0';
        fun_modulus_uchar(&uc_first, &uc_second, &uc_output);
        printf("first:%c(%d), second:%c(%d), output:%c(%d)\n", 
            uc_first, uc_first, uc_second, uc_second, uc_output, uc_output);
    }
    {
        short h_first = 90;
        short h_second = -230;
        short h_output = 0;
        fun_modulus_short(&h_first, &h_second, &h_output);
        printf("first:%hd, second:%hd, output:%hd\n", 
            h_first, h_second, h_output);
    }
    {
        unsigned short uh_first = -90;
        unsigned short uh_second = 230;
        unsigned short uh_output = 0;
        fun_modulus_ushort(&uh_first, &uh_second, &uh_output);
        printf("first:%hu, second:%hu, output:%hu\n", 
            uh_first, uh_second, uh_output);
    }
    {
        int n_first = 90;
        int n_second = -230;
        int n_output = 0;
        fun_modulus_int(&n_first, &n_second, &n_output);
        printf("first:%d, second:%d, output:%d\n", 
            n_first, n_second, n_output);
    }
    {
        unsigned int un_first = 90;
        unsigned int un_second = -230;
        unsigned int un_output = 0;
        fun_modulus_uint(&un_first, &un_second, &un_output);
        printf("first:%u, second:%u, output:%u\n", 
            un_first, un_second, un_output);
    }
    {
        long l_first = 90;
        long l_second = -230;
        long l_output = 0;
        fun_modulus_long(&l_first, &l_second, &l_output);
        printf("first:%ld, second:%ld, output:%ld\n", 
            l_first, l_second, l_output);
    }
    {
        unsigned long ul_first = 90;
        unsigned long ul_second = -230;
        unsigned long ul_output = 0;
        fun_modulus_ulong(&ul_first, &ul_second, &ul_output);
        printf("first:%lu, second:%lu, output:%lu\n", 
            ul_first, ul_second, ul_output);
    }

    /* test negation */
    printf("***** test negation function *****\n");
    {
        char c_input = 'a';
        char c_output = '\0';
        fun_negate_char(&c_input, &c_output);
        printf("input:%c(%d), output:%c(%d)\n", 
            c_input, c_input, c_output, c_output);
    }
    {
        short h_input = 90;
        short h_output = 0;
        fun_negate_short(&h_input, &h_output);
        printf("input:%hd, output:%hd\n", 
            h_input, h_output);
    }
    {
        int n_input = -90;
        int n_output = 0;
        fun_negate_int(&n_input, &n_output);
        printf("input:%d, output:%d\n", 
            n_input, n_output);
    }
    {
        long l_input = 90;
        long l_output = 0;
        fun_negate_long(&l_input, &l_output);
        printf("input:%ld, output:%ld\n", 
            l_input, l_output);
    }
    {
        float f_input = 0.0;
        float f_output = 0;
        fun_negate_float(&f_input, &f_output);
        printf("input:%f, output:%f\n", 
            f_input, f_output);
    }
    {
        double d_input = 1.0e-23;
        double d_output = 0;
        fun_negate_double(&d_input, &d_output);
        printf("input:%g, output:%g\n", 
            d_input, d_output);
    }

    /* comparisons */
    /* equality */
    printf("***** test equal_to function *****\n");
    {
        char c_first = 'c';
        char c_second = 'd';
        bool_t t_output = false;
        fun_equal_char(&c_first, &c_second, &t_output);
        printf("first:%c, second:%c, equal:%d\n", c_first, c_second, t_output);
        c_second = 'c';
        fun_equal_char(&c_first, &c_second, &t_output);
        printf("first:%c, second:%c, equal:%d\n", c_first, c_second, t_output);
    }
    {
        unsigned char uc_first = 0x45;
        unsigned char uc_second = 0x49;
        bool_t t_output = false;
        fun_equal_uchar(&uc_first, &uc_second, &t_output);
        printf("first:%c, second:%c, equal:%d\n", uc_first, uc_second, t_output);
        uc_second = 0x45;
        fun_equal_uchar(&uc_first, &uc_second, &t_output);
        printf("first:%c, second:%c, equal:%d\n", uc_first, uc_second, t_output);
    }
    {
        short h_first = 90;
        short h_second = 80;
        bool_t t_output = false;
        fun_equal_short(&h_first, &h_second, &t_output);
        printf("first:%hd, second:%hd, equal:%d\n", h_first, h_second, t_output);
        h_second = 90;
        fun_equal_short(&h_first, &h_second, &t_output);
        printf("first:%hd, second:%hd, equal:%d\n", h_first, h_second, t_output);
    }
    {
        unsigned short uh_first = 90;
        unsigned short uh_second = 80;
        bool_t t_output = false;
        fun_equal_ushort(&uh_first, &uh_second, &t_output);
        printf("first:%hu, second:%hu, equal:%d\n", uh_first, uh_second, t_output);
        uh_second = 90;
        fun_equal_ushort(&uh_first, &uh_second, &t_output);
        printf("first:%hu, second:%hu, equal:%d\n", uh_first, uh_second, t_output);
    }
    {
        int n_first = 90;
        int n_second = 80;
        bool_t t_output = false;
        fun_equal_int(&n_first, &n_second, &t_output);
        printf("first:%d, second:%d, equal:%d\n", n_first, n_second, t_output);
        n_second = 90;
        fun_equal_int(&n_first, &n_second, &t_output);
        printf("first:%d, second:%d, equal:%d\n", n_first, n_second, t_output);
    }
    {
        unsigned int un_first = 90;
        unsigned int un_second = 80;
        bool_t t_output = false;
        fun_equal_uint(&un_first, &un_second, &t_output);
        printf("first:%u, second:%u, equal:%d\n", un_first, un_second, t_output);
        un_second = 90;
        fun_equal_uint(&un_first, &un_second, &t_output);
        printf("first:%u, second:%u, equal:%d\n", un_first, un_second, t_output);
    }
    {
        long l_first = 90;
        long l_second = 80;
        bool_t t_output = false;
        fun_equal_long(&l_first, &l_second, &t_output);
        printf("first:%ld, second:%ld, equal:%d\n", l_first, l_second, t_output);
        l_second = 90;
        fun_equal_long(&l_first, &l_second, &t_output);
        printf("first:%ld, second:%ld, equal:%d\n", l_first, l_second, t_output);
    }
    {
        unsigned long ul_first = 90;
        unsigned long ul_second = 80;
        bool_t t_output = false;
        fun_equal_ulong(&ul_first, &ul_second, &t_output);
        printf("first:%lu, second:%lu, equal:%d\n", ul_first, ul_second, t_output);
        ul_second = 90;
        fun_equal_ulong(&ul_first, &ul_second, &t_output);
        printf("first:%lu, second:%lu, equal:%d\n", ul_first, ul_second, t_output);
    }
    {
        float f_first = 90;
        float f_second = 80;
        bool_t t_output = false;
        fun_equal_float(&f_first, &f_second, &t_output);
        printf("first:%f, second:%f, equal:%d\n", f_first, f_second, t_output);
        f_second = 90;
        fun_equal_float(&f_first, &f_second, &t_output);
        printf("first:%f, second:%f, equal:%d\n", f_first, f_second, t_output);
    }
    {
        double d_first = 90;
        double d_second = 80;
        bool_t t_output = false;
        fun_equal_double(&d_first, &d_second, &t_output);
        printf("first:%f, second:%f, equal:%d\n", d_first, d_second, t_output);
        d_second = 90;
        fun_equal_double(&d_first, &d_second, &t_output);
        printf("first:%f, second:%f, equal:%d\n", d_first, d_second, t_output);
    }
    /* inequality */
    printf("***** test not_equal_to function *****\n");
    {
        char c_first = 'c';
        char c_second = 'd';
        bool_t t_output = false;
        fun_not_equal_char(&c_first, &c_second, &t_output);
        printf("first:%c, second:%c, not equal:%d\n", c_first, c_second, t_output);
        c_second = 'c';
        fun_not_equal_char(&c_first, &c_second, &t_output);
        printf("first:%c, second:%c, not equal:%d\n", c_first, c_second, t_output);
    }
    {
        unsigned char uc_first = 0x45;
        unsigned char uc_second = 0x49;
        bool_t t_output = false;
        fun_not_equal_uchar(&uc_first, &uc_second, &t_output);
        printf("first:%c, second:%c, not equal:%d\n", uc_first, uc_second, t_output);
        uc_second = 0x45;
        fun_not_equal_uchar(&uc_first, &uc_second, &t_output);
        printf("first:%c, second:%c, not equal:%d\n", uc_first, uc_second, t_output);
    }
    {
        short h_first = 90;
        short h_second = 80;
        bool_t t_output = false;
        fun_not_equal_short(&h_first, &h_second, &t_output);
        printf("first:%hd, second:%hd, not equal:%d\n", h_first, h_second, t_output);
        h_second = 90;
        fun_not_equal_short(&h_first, &h_second, &t_output);
        printf("first:%hd, second:%hd, not equal:%d\n", h_first, h_second, t_output);
    }
    {
        unsigned short uh_first = 90;
        unsigned short uh_second = 80;
        bool_t t_output = false;
        fun_not_equal_ushort(&uh_first, &uh_second, &t_output);
        printf("first:%hu, second:%hu, not equal:%d\n", uh_first, uh_second, t_output);
        uh_second = 90;
        fun_not_equal_ushort(&uh_first, &uh_second, &t_output);
        printf("first:%hu, second:%hu, not equal:%d\n", uh_first, uh_second, t_output);
    }
    {
        int n_first = 90;
        int n_second = 80;
        bool_t t_output = false;
        fun_not_equal_int(&n_first, &n_second, &t_output);
        printf("first:%d, second:%d, not equal:%d\n", n_first, n_second, t_output);
        n_second = 90;
        fun_not_equal_int(&n_first, &n_second, &t_output);
        printf("first:%d, second:%d, not equal:%d\n", n_first, n_second, t_output);
    }
    {
        unsigned int un_first = 90;
        unsigned int un_second = 80;
        bool_t t_output = false;
        fun_not_equal_uint(&un_first, &un_second, &t_output);
        printf("first:%u, second:%u, not equal:%d\n", un_first, un_second, t_output);
        un_second = 90;
        fun_not_equal_uint(&un_first, &un_second, &t_output);
        printf("first:%u, second:%u, not equal:%d\n", un_first, un_second, t_output);
    }
    {
        long l_first = 90;
        long l_second = 80;
        bool_t t_output = false;
        fun_not_equal_long(&l_first, &l_second, &t_output);
        printf("first:%ld, second:%ld, not equal:%d\n", l_first, l_second, t_output);
        l_second = 90;
        fun_not_equal_long(&l_first, &l_second, &t_output);
        printf("first:%ld, second:%ld, not equal:%d\n", l_first, l_second, t_output);
    }
    {
        unsigned long ul_first = 90;
        unsigned long ul_second = 80;
        bool_t t_output = false;
        fun_not_equal_ulong(&ul_first, &ul_second, &t_output);
        printf("first:%lu, second:%lu, not equal:%d\n", ul_first, ul_second, t_output);
        ul_second = 90;
        fun_not_equal_ulong(&ul_first, &ul_second, &t_output);
        printf("first:%lu, second:%lu, not equal:%d\n", ul_first, ul_second, t_output);
    }
    {
        float f_first = 90;
        float f_second = 80;
        bool_t t_output = false;
        fun_not_equal_float(&f_first, &f_second, &t_output);
        printf("first:%f, second:%f, not equal:%d\n", f_first, f_second, t_output);
        f_second = 90;
        fun_not_equal_float(&f_first, &f_second, &t_output);
        printf("first:%f, second:%f, not equal:%d\n", f_first, f_second, t_output);
    }
    {
        double d_first = 90;
        double d_second = 80;
        bool_t t_output = false;
        fun_not_equal_double(&d_first, &d_second, &t_output);
        printf("first:%f, second:%f, not equal:%d\n", d_first, d_second, t_output);
        d_second = 90;
        fun_not_equal_double(&d_first, &d_second, &t_output);
        printf("first:%f, second:%f, not equal:%d\n", d_first, d_second, t_output);
    }
    /* greater */
    printf("***** test greater function *****\n");
    {
        char c_first = 'z';
        char c_second = 'd';
        bool_t t_output = false;
        fun_great_char(&c_first, &c_second, &t_output);
        printf("first:%c, second:%c, greater:%d\n", c_first, c_second, t_output);
        c_second = 'z';
        fun_great_char(&c_first, &c_second, &t_output);
        printf("first:%c, second:%c, greater:%d\n", c_first, c_second, t_output);
    }
    {
        unsigned char uc_first = 0x49;
        unsigned char uc_second = 0x45;
        bool_t t_output = false;
        fun_great_uchar(&uc_first, &uc_second, &t_output);
        printf("first:%c, second:%c, greater:%d\n", uc_first, uc_second, t_output);
        uc_second = 0x49;
        fun_great_uchar(&uc_first, &uc_second, &t_output);
        printf("first:%c, second:%c, greater:%d\n", uc_first, uc_second, t_output);
    }
    {
        short h_first = 90;
        short h_second = 80;
        bool_t t_output = false;
        fun_great_short(&h_first, &h_second, &t_output);
        printf("first:%hd, second:%hd, greater:%d\n", h_first, h_second, t_output);
        h_second = 90;
        fun_great_short(&h_first, &h_second, &t_output);
        printf("first:%hd, second:%hd, greater:%d\n", h_first, h_second, t_output);
    }
    {
        unsigned short uh_first = 90;
        unsigned short uh_second = 80;
        bool_t t_output = false;
        fun_great_ushort(&uh_first, &uh_second, &t_output);
        printf("first:%hu, second:%hu, greater:%d\n", uh_first, uh_second, t_output);
        uh_second = 90;
        fun_great_ushort(&uh_first, &uh_second, &t_output);
        printf("first:%hu, second:%hu, greater:%d\n", uh_first, uh_second, t_output);
    }
    {
        int n_first = 90;
        int n_second = 80;
        bool_t t_output = false;
        fun_great_int(&n_first, &n_second, &t_output);
        printf("first:%d, second:%d, greater:%d\n", n_first, n_second, t_output);
        n_second = 90;
        fun_great_int(&n_first, &n_second, &t_output);
        printf("first:%d, second:%d, greater:%d\n", n_first, n_second, t_output);
    }
    {
        unsigned int un_first = 90;
        unsigned int un_second = 80;
        bool_t t_output = false;
        fun_great_uint(&un_first, &un_second, &t_output);
        printf("first:%u, second:%u, greater:%d\n", un_first, un_second, t_output);
        un_second = 90;
        fun_great_uint(&un_first, &un_second, &t_output);
        printf("first:%u, second:%u, greater:%d\n", un_first, un_second, t_output);
    }
    {
        long l_first = 90;
        long l_second = 80;
        bool_t t_output = false;
        fun_great_long(&l_first, &l_second, &t_output);
        printf("first:%ld, second:%ld, greater:%d\n", l_first, l_second, t_output);
        l_second = 90;
        fun_great_long(&l_first, &l_second, &t_output);
        printf("first:%ld, second:%ld, greater:%d\n", l_first, l_second, t_output);
    }
    {
        unsigned long ul_first = 90;
        unsigned long ul_second = 80;
        bool_t t_output = false;
        fun_great_ulong(&ul_first, &ul_second, &t_output);
        printf("first:%lu, second:%lu, greater:%d\n", ul_first, ul_second, t_output);
        ul_second = 90;
        fun_great_ulong(&ul_first, &ul_second, &t_output);
        printf("first:%lu, second:%lu, greater:%d\n", ul_first, ul_second, t_output);
    }
    {
        float f_first = 90;
        float f_second = 80;
        bool_t t_output = false;
        fun_great_float(&f_first, &f_second, &t_output);
        printf("first:%f, second:%f, greater:%d\n", f_first, f_second, t_output);
        f_second = 90;
        fun_great_float(&f_first, &f_second, &t_output);
        printf("first:%f, second:%f, greater:%d\n", f_first, f_second, t_output);
    }
    {
        double d_first = 90;
        double d_second = 80;
        bool_t t_output = false;
        fun_great_double(&d_first, &d_second, &t_output);
        printf("first:%f, second:%f, greater:%d\n", d_first, d_second, t_output);
        d_second = 90;
        fun_great_double(&d_first, &d_second, &t_output);
        printf("first:%f, second:%f, greater:%d\n", d_first, d_second, t_output);
    }
    /* greater_equal */
    printf("***** test greater_equal function *****\n");
    {
        char c_first = 'z';
        char c_second = 'd';
        bool_t t_output = false;
        fun_great_equal_char(&c_first, &c_second, &t_output);
        printf("first:%c, second:%c, greater_equal:%d\n", c_first, c_second, t_output);
        c_second = 'z';
        fun_great_equal_char(&c_first, &c_second, &t_output);
        printf("first:%c, second:%c, greater_equal:%d\n", c_first, c_second, t_output);
    }
    {
        unsigned char uc_first = 0x49;
        unsigned char uc_second = 0x45;
        bool_t t_output = false;
        fun_great_equal_uchar(&uc_first, &uc_second, &t_output);
        printf("first:%c, second:%c, greater_equal:%d\n", uc_first, uc_second, t_output);
        uc_second = 0x49;
        fun_great_equal_uchar(&uc_first, &uc_second, &t_output);
        printf("first:%c, second:%c, greater_equal:%d\n", uc_first, uc_second, t_output);
    }
    {
        short h_first = 90;
        short h_second = 80;
        bool_t t_output = false;
        fun_great_equal_short(&h_first, &h_second, &t_output);
        printf("first:%hd, second:%hd, greater_equal:%d\n", h_first, h_second, t_output);
        h_second = 90;
        fun_great_equal_short(&h_first, &h_second, &t_output);
        printf("first:%hd, second:%hd, greater_equal:%d\n", h_first, h_second, t_output);
    }
    {
        unsigned short uh_first = 90;
        unsigned short uh_second = 80;
        bool_t t_output = false;
        fun_great_equal_ushort(&uh_first, &uh_second, &t_output);
        printf("first:%hu, second:%hu, greater_equal:%d\n", uh_first, uh_second, t_output);
        uh_second = 90;
        fun_great_equal_ushort(&uh_first, &uh_second, &t_output);
        printf("first:%hu, second:%hu, greater_equal:%d\n", uh_first, uh_second, t_output);
    }
    {
        int n_first = 90;
        int n_second = 80;
        bool_t t_output = false;
        fun_great_equal_int(&n_first, &n_second, &t_output);
        printf("first:%d, second:%d, greater_equal:%d\n", n_first, n_second, t_output);
        n_second = 90;
        fun_great_equal_int(&n_first, &n_second, &t_output);
        printf("first:%d, second:%d, greater_equal:%d\n", n_first, n_second, t_output);
    }
    {
        unsigned int un_first = 90;
        unsigned int un_second = 80;
        bool_t t_output = false;
        fun_great_equal_uint(&un_first, &un_second, &t_output);
        printf("first:%u, second:%u, greater_equal:%d\n", un_first, un_second, t_output);
        un_second = 90;
        fun_great_equal_uint(&un_first, &un_second, &t_output);
        printf("first:%u, second:%u, greater_equal:%d\n", un_first, un_second, t_output);
    }
    {
        long l_first = 90;
        long l_second = 80;
        bool_t t_output = false;
        fun_great_equal_long(&l_first, &l_second, &t_output);
        printf("first:%ld, second:%ld, greater_equal:%d\n", l_first, l_second, t_output);
        l_second = 90;
        fun_great_equal_long(&l_first, &l_second, &t_output);
        printf("first:%ld, second:%ld, greater_equal:%d\n", l_first, l_second, t_output);
    }
    {
        unsigned long ul_first = 90;
        unsigned long ul_second = 80;
        bool_t t_output = false;
        fun_great_equal_ulong(&ul_first, &ul_second, &t_output);
        printf("first:%lu, second:%lu, greater_equal:%d\n", ul_first, ul_second, t_output);
        ul_second = 90;
        fun_great_equal_ulong(&ul_first, &ul_second, &t_output);
        printf("first:%lu, second:%lu, greater_equal:%d\n", ul_first, ul_second, t_output);
    }
    {
        float f_first = 90;
        float f_second = 80;
        bool_t t_output = false;
        fun_great_equal_float(&f_first, &f_second, &t_output);
        printf("first:%f, second:%f, greater_equal:%d\n", f_first, f_second, t_output);
        f_second = 90;
        fun_great_equal_float(&f_first, &f_second, &t_output);
        printf("first:%f, second:%f, greater_equal:%d\n", f_first, f_second, t_output);
    }
    {
        double d_first = 90;
        double d_second = 80;
        bool_t t_output = false;
        fun_great_equal_double(&d_first, &d_second, &t_output);
        printf("first:%f, second:%f, greater_equal:%d\n", d_first, d_second, t_output);
        d_second = 90;
        fun_great_equal_double(&d_first, &d_second, &t_output);
        printf("first:%f, second:%f, greater_equal:%d\n", d_first, d_second, t_output);
    }
    /* less */
    printf("***** test less function *****\n");
    {
        char c_first = 'z';
        char c_second = '{';
        bool_t t_output = false;
        fun_less_char(&c_first, &c_second, &t_output);
        printf("first:%c, second:%c, less:%d\n", c_first, c_second, t_output);
        c_second = 'z';
        fun_less_char(&c_first, &c_second, &t_output);
        printf("first:%c, second:%c, less:%d\n", c_first, c_second, t_output);
    }
    {
        unsigned char uc_first = 0x49;
        unsigned char uc_second = 0x50;
        bool_t t_output = false;
        fun_less_uchar(&uc_first, &uc_second, &t_output);
        printf("first:%c, second:%c, less:%d\n", uc_first, uc_second, t_output);
        uc_second = 0x49;
        fun_less_uchar(&uc_first, &uc_second, &t_output);
        printf("first:%c, second:%c, less:%d\n", uc_first, uc_second, t_output);
    }
    {
        short h_first = 90;
        short h_second = 888;
        bool_t t_output = false;
        fun_less_short(&h_first, &h_second, &t_output);
        printf("first:%hd, second:%hd, less:%d\n", h_first, h_second, t_output);
        h_second = 90;
        fun_less_short(&h_first, &h_second, &t_output);
        printf("first:%hd, second:%hd, less:%d\n", h_first, h_second, t_output);
    }
    {
        unsigned short uh_first = 90;
        unsigned short uh_second = 888;
        bool_t t_output = false;
        fun_less_ushort(&uh_first, &uh_second, &t_output);
        printf("first:%hu, second:%hu, less:%d\n", uh_first, uh_second, t_output);
        uh_second = 90;
        fun_less_ushort(&uh_first, &uh_second, &t_output);
        printf("first:%hu, second:%hu, less:%d\n", uh_first, uh_second, t_output);
    }
    {
        int n_first = 90;
        int n_second = 888;
        bool_t t_output = false;
        fun_less_int(&n_first, &n_second, &t_output);
        printf("first:%d, second:%d, less:%d\n", n_first, n_second, t_output);
        n_second = 90;
        fun_less_int(&n_first, &n_second, &t_output);
        printf("first:%d, second:%d, less:%d\n", n_first, n_second, t_output);
    }
    {
        unsigned int un_first = 90;
        unsigned int un_second = 888;
        bool_t t_output = false;
        fun_less_uint(&un_first, &un_second, &t_output);
        printf("first:%u, second:%u, less:%d\n", un_first, un_second, t_output);
        un_second = 90;
        fun_less_uint(&un_first, &un_second, &t_output);
        printf("first:%u, second:%u, less:%d\n", un_first, un_second, t_output);
    }
    {
        long l_first = 90;
        long l_second = 888;
        bool_t t_output = false;
        fun_less_long(&l_first, &l_second, &t_output);
        printf("first:%ld, second:%ld, less:%d\n", l_first, l_second, t_output);
        l_second = 90;
        fun_less_long(&l_first, &l_second, &t_output);
        printf("first:%ld, second:%ld, less:%d\n", l_first, l_second, t_output);
    }
    {
        unsigned long ul_first = 90;
        unsigned long ul_second = 888;
        bool_t t_output = false;
        fun_less_ulong(&ul_first, &ul_second, &t_output);
        printf("first:%lu, second:%lu, less:%d\n", ul_first, ul_second, t_output);
        ul_second = 90;
        fun_less_ulong(&ul_first, &ul_second, &t_output);
        printf("first:%lu, second:%lu, less:%d\n", ul_first, ul_second, t_output);
    }
    {
        float f_first = 90;
        float f_second = 888;
        bool_t t_output = false;
        fun_less_float(&f_first, &f_second, &t_output);
        printf("first:%f, second:%f, less:%d\n", f_first, f_second, t_output);
        f_second = 90;
        fun_less_float(&f_first, &f_second, &t_output);
        printf("first:%f, second:%f, less:%d\n", f_first, f_second, t_output);
    }
    {
        double d_first = 90;
        double d_second = 888;
        bool_t t_output = false;
        fun_less_double(&d_first, &d_second, &t_output);
        printf("first:%f, second:%f, less:%d\n", d_first, d_second, t_output);
        d_second = 90;
        fun_less_double(&d_first, &d_second, &t_output);
        printf("first:%f, second:%f, less:%d\n", d_first, d_second, t_output);
    }
    /* less_equal */
    printf("***** test less_equal function *****\n");
    {
        char c_first = 'z';
        char c_second = '{';
        bool_t t_output = false;
        fun_less_equal_char(&c_first, &c_second, &t_output);
        printf("first:%c, second:%c, less_equal:%d\n", c_first, c_second, t_output);
        c_second = 'z';
        fun_less_equal_char(&c_first, &c_second, &t_output);
        printf("first:%c, second:%c, less_equal:%d\n", c_first, c_second, t_output);
    }
    {
        unsigned char uc_first = 0x49;
        unsigned char uc_second = 0x50;
        bool_t t_output = false;
        fun_less_equal_uchar(&uc_first, &uc_second, &t_output);
        printf("first:%c, second:%c, less_equal:%d\n", uc_first, uc_second, t_output);
        uc_second = 0x49;
        fun_less_equal_uchar(&uc_first, &uc_second, &t_output);
        printf("first:%c, second:%c, less_equal:%d\n", uc_first, uc_second, t_output);
    }
    {
        short h_first = 90;
        short h_second = 888;
        bool_t t_output = false;
        fun_less_equal_short(&h_first, &h_second, &t_output);
        printf("first:%hd, second:%hd, less_equal:%d\n", h_first, h_second, t_output);
        h_second = 90;
        fun_less_equal_short(&h_first, &h_second, &t_output);
        printf("first:%hd, second:%hd, less_equal:%d\n", h_first, h_second, t_output);
    }
    {
        unsigned short uh_first = 90;
        unsigned short uh_second = 888;
        bool_t t_output = false;
        fun_less_equal_ushort(&uh_first, &uh_second, &t_output);
        printf("first:%hu, second:%hu, less_equal:%d\n", uh_first, uh_second, t_output);
        uh_second = 90;
        fun_less_equal_ushort(&uh_first, &uh_second, &t_output);
        printf("first:%hu, second:%hu, less_equal:%d\n", uh_first, uh_second, t_output);
    }
    {
        int n_first = 90;
        int n_second = 888;
        bool_t t_output = false;
        fun_less_equal_int(&n_first, &n_second, &t_output);
        printf("first:%d, second:%d, less_equal:%d\n", n_first, n_second, t_output);
        n_second = 90;
        fun_less_equal_int(&n_first, &n_second, &t_output);
        printf("first:%d, second:%d, less_equal:%d\n", n_first, n_second, t_output);
    }
    {
        unsigned int un_first = 90;
        unsigned int un_second = 888;
        bool_t t_output = false;
        fun_less_equal_uint(&un_first, &un_second, &t_output);
        printf("first:%u, second:%u, less_equal:%d\n", un_first, un_second, t_output);
        un_second = 90;
        fun_less_equal_uint(&un_first, &un_second, &t_output);
        printf("first:%u, second:%u, less_equal:%d\n", un_first, un_second, t_output);
    }
    {
        long l_first = 90;
        long l_second = 888;
        bool_t t_output = false;
        fun_less_equal_long(&l_first, &l_second, &t_output);
        printf("first:%ld, second:%ld, less_equal:%d\n", l_first, l_second, t_output);
        l_second = 90;
        fun_less_equal_long(&l_first, &l_second, &t_output);
        printf("first:%ld, second:%ld, less_equal:%d\n", l_first, l_second, t_output);
    }
    {
        unsigned long ul_first = 90;
        unsigned long ul_second = 888;
        bool_t t_output = false;
        fun_less_equal_ulong(&ul_first, &ul_second, &t_output);
        printf("first:%lu, second:%lu, less_equal:%d\n", ul_first, ul_second, t_output);
        ul_second = 90;
        fun_less_equal_ulong(&ul_first, &ul_second, &t_output);
        printf("first:%lu, second:%lu, less_equal:%d\n", ul_first, ul_second, t_output);
    }
    {
        float f_first = 90;
        float f_second = 888;
        bool_t t_output = false;
        fun_less_equal_float(&f_first, &f_second, &t_output);
        printf("first:%f, second:%f, less_equal:%d\n", f_first, f_second, t_output);
        f_second = 90;
        fun_less_equal_float(&f_first, &f_second, &t_output);
        printf("first:%f, second:%f, less_equal:%d\n", f_first, f_second, t_output);
    }
    {
        double d_first = 90;
        double d_second = 888;
        bool_t t_output = false;
        fun_less_equal_double(&d_first, &d_second, &t_output);
        printf("first:%f, second:%f, less_equal:%d\n", d_first, d_second, t_output);
        d_second = 90;
        fun_less_equal_double(&d_first, &d_second, &t_output);
        printf("first:%f, second:%f, less_equal:%d\n", d_first, d_second, t_output);
    }

    /* logical */
    printf("***** test logical and function *****\n");
    {
        bool_t t_first = false;
        bool_t t_second = false;
        bool_t t_output = false;
        fun_logical_and_bool(&t_first, &t_second, &t_output);
        printf("first:%d, second:%d, output:%d\n", t_first, t_second, t_output);
        t_first = true;
        t_second = false;
        t_output = false;
        fun_logical_and_bool(&t_first, &t_second, &t_output);
        printf("first:%d, second:%d, output:%d\n", t_first, t_second, t_output);
        t_first = false;
        t_second = true;
        t_output = false;
        fun_logical_and_bool(&t_first, &t_second, &t_output);
        printf("first:%d, second:%d, output:%d\n", t_first, t_second, t_output);
        t_first = true;
        t_second = true;
        t_output = false;
        fun_logical_and_bool(&t_first, &t_second, &t_output);
        printf("first:%d, second:%d, output:%d\n", t_first, t_second, t_output);
    }
    printf("***** test logical or function *****\n");
    {
        bool_t t_first = false;
        bool_t t_second = false;
        bool_t t_output = false;
        fun_logical_or_bool(&t_first, &t_second, &t_output);
        printf("first:%d, second:%d, output:%d\n", t_first, t_second, t_output);
        t_first = true;
        t_second = false;
        t_output = false;
        fun_logical_or_bool(&t_first, &t_second, &t_output);
        printf("first:%d, second:%d, output:%d\n", t_first, t_second, t_output);
        t_first = false;
        t_second = true;
        t_output = false;
        fun_logical_or_bool(&t_first, &t_second, &t_output);
        printf("first:%d, second:%d, output:%d\n", t_first, t_second, t_output);
        t_first = true;
        t_second = true;
        t_output = false;
        fun_logical_or_bool(&t_first, &t_second, &t_output);
        printf("first:%d, second:%d, output:%d\n", t_first, t_second, t_output);
    }
    {
        bool_t t_input = false;
        bool_t t_output = false;
        fun_logical_not_bool(&t_input, &t_output);
        printf("input:%d, output:%d\n", t_input, t_output);
        t_input = true;
        t_output = true;
        fun_logical_not_bool(&t_input, &t_output);
        printf("input:%d, output:%d\n", t_input, t_output);
    }
}

/** local function implementation section **/

/** eof **/

