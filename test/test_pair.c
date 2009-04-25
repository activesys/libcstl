/*
 *  The implementation of pair test.
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
#include <stdio.h>

#include "cutility.h"
#include "test_pair.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_pair(void)
{
    pair_t t_p1 = create_pair(int, double);
    pair_t t_p2 = create_pair(int, double);
    pair_t t_p3 = create_pair(int, double);

    pair_init(&t_p1);
    printf("p1(%d, %f)\n", *(int*)t_p1.first, *(double*)t_p1.second);

    pair_init_elem(&t_p2, 10, 1.1e-2);
    printf("p2(%d, %f)\n", *(int*)t_p2.first, *(double*)t_p2.second);

    pair_init_copy(&t_p3, &t_p2);
    printf("p3(%d, %f)\n", *(int*)t_p3.first, *(double*)t_p3.second);

    pair_make(&t_p1, 10, 2.222);
    printf("p1(%d, %f)\n", *(int*)t_p1.first, *(double*)t_p1.second);

    pair_assign(&t_p3, &t_p1);
    printf("p3(%d, %f)\n", *(int*)t_p3.first, *(double*)t_p3.second);

    if(pair_equal(&t_p1, &t_p3))
    {
        printf("p1(%d, %f) == p3(%d, %f)\n",
            *(int*)t_p1.first, *(double*)t_p1.second,
            *(int*)t_p3.first, *(double*)t_p3.second);
    }
    else
    {
        printf("p1(%d, %f) != p3(%d, %f)\n",
            *(int*)t_p1.first, *(double*)t_p1.second,
            *(int*)t_p3.first, *(double*)t_p3.second);
    }

    if(pair_not_equal(&t_p1, &t_p2))
    {
        printf("p1(%d, %f) != p2(%d, %f)\n",
            *(int*)t_p1.first, *(double*)t_p1.second,
            *(int*)t_p2.first, *(double*)t_p2.second);
    }
    else
    {
        printf("p1(%d, %f) == p2(%d, %f)\n",
            *(int*)t_p1.first, *(double*)t_p1.second,
            *(int*)t_p2.first, *(double*)t_p2.second);
    }

    pair_make(&t_p1, 22, 35.2);
    pair_make(&t_p2, 62, 35.2);
    pair_make(&t_p3, 22, 70.0);
    if(pair_less(&t_p1, &t_p2))
    {
        printf("p1(%d, %f) < p2(%d, %f)\n",
            *(int*)t_p1.first, *(double*)t_p1.second,
            *(int*)t_p2.first, *(double*)t_p2.second);
    }
    else
    {
        printf("p1(%d, %f) >= p2(%d, %f)\n",
            *(int*)t_p1.first, *(double*)t_p1.second,
            *(int*)t_p2.first, *(double*)t_p2.second);
    }
    if(pair_less(&t_p1, &t_p3))
    {
        printf("p1(%d, %f) < p3(%d, %f)\n",
            *(int*)t_p1.first, *(double*)t_p1.second,
            *(int*)t_p3.first, *(double*)t_p3.second);
    }
    else
    {
        printf("p1(%d, %f) >= p3(%d, %f)\n",
            *(int*)t_p1.first, *(double*)t_p1.second,
            *(int*)t_p3.first, *(double*)t_p3.second);
    }

    pair_destroy(&t_p1);
    pair_destroy(&t_p2);
    pair_destroy(&t_p3);
}

/** local function implementation section **/

/** eof **/

