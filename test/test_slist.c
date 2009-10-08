/*
 *  The implementation of slist test.
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
#include <stdlib.h>
#include "cslist.h"
#include "test_slist.h"

/** local constant declaration and local macro section **/
#define _printslist_c(pt_slist, fmt, type)\
    do{\
        iterator_t t_iter;\
        printf("==================================\n");\
        for(t_iter = slist_begin(pt_slist);\
            !iterator_equal(t_iter, slist_end(pt_slist));\
            t_iter = iterator_next(t_iter)){\
            printf(fmt, *(type*)iterator_get_pointer(t_iter));\
        }printf("\n");\
    }while(false)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_slist(void)
{
    /* c built-in type */
    {
        /*create_slist            */
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_init              */
        /*slist_init_n            */
        {
            slist_t* pt_slist = create_slist(double);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 21);
            _printslist_c(pt_slist, "%lf, ", double);
            slist_destroy(pt_slist);
        }
        /*slist_init_elem         */
        {
            slist_t* pt_slist = create_slist(double);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_elem(pt_slist, 21, 45.9801);
            _printslist_c(pt_slist, "%lf, ", double);
            slist_destroy(pt_slist);
        }
        /*slist_init_copy         */
        {
            slist_t* pt_slist = create_slist(long);
            slist_t* pt_slistex = create_slist(signed long int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init_elem(pt_slistex, 8, 23097);
            slist_init_copy(pt_slist, pt_slistex);
            _printslist_c(pt_slist, "%ld, ", long);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_init_copy_range   */
        {
            slist_t* pt_slist = create_slist(int);
            slist_t* pt_slistex = create_slist(signed int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slistex);
            slist_push_front(pt_slistex, 39);
            slist_push_front(pt_slistex, 88);
            slist_push_front(pt_slistex, 212);
            slist_push_front(pt_slistex, 999);
            slist_push_front(pt_slistex, 90);
            slist_init_copy_range(pt_slist,
                slist_begin(pt_slistex), iterator_advance(slist_begin(pt_slistex), 3));
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_destroy           */
        /*slist_size              */
        /*slist_empty             */
        /*slist_max_size          */
        /*slist_begin             */
        /*slist_end               */
        /*slist_previous          */
        /*slist_equal             */
        /*slist_not_equal         */
        /*slist_less              */
        /*slist_less_equal        */
        /*slist_great             */
        /*slist_great_equal       */
        /*slist_assign            */
        /*_slist_assign_elem      */
        /*slist_assign_range      */
        /*slist_swap              */
        /*slist_front             */
        /*_slist_push_front       */
        /*slist_pop_front         */
        /*_slist_insert           */
        /*_slist_insert_n         */
        /*slist_insert_range      */
        /*_slist_insert_after     */
        /*_slist_insert_after_n   */
        /*slist_insert_after_range*/
        /*slist_erase             */
        /*slist_erase_range       */
        /*slist_erase_after       */
        /*slist_erase_after_range */
        /*slist_splice            */
        /*slist_splice_pos        */
        /*slist_splice_range      */
        /*slist_splice_after_pos  */
        /*slist_splice_after_range*/
        /*_slist_remove           */
        /*slist_remove_if         */
        /*slist_unique            */
        /*slist_unique_if         */
        /*slist_reverse           */
        /*slist_sort              */
        /*slist_sort_if           */
        /*slist_merge             */
        /*slist_merge_if          */
        /*slist_resize            */
        /*_slist_resize_elem      */
        /*slist_clear             */
    }
    /* user defined type */
    {
    }
    /* cstl built-in type */
    {
    }
    /* c-string type */
    {
    }
    /*_create_slist           */
    /*slist_init              */
    /*slist_init_n            */
    /*_slist_init_elem        */
    /*slist_init_copy         */
    /*slist_init_copy_range   */
    /*slist_destroy           */
    /*slist_size              */
    /*slist_empty             */
    /*slist_max_size          */
    /*slist_begin             */
    /*slist_end               */
    /*slist_previous          */
    /*slist_equal             */
    /*slist_not_equal         */
    /*slist_less              */
    /*slist_less_equal        */
    /*slist_great             */
    /*slist_great_equal       */
    /*slist_assign            */
    /*_slist_assign_elem      */
    /*slist_assign_range      */
    /*slist_swap              */
    /*slist_front             */
    /*_slist_push_front       */
    /*slist_pop_front         */
    /*_slist_insert           */
    /*_slist_insert_n         */
    /*slist_insert_range      */
    /*_slist_insert_after     */
    /*_slist_insert_after_n   */
    /*slist_insert_after_range*/
    /*slist_erase             */
    /*slist_erase_range       */
    /*slist_erase_after       */
    /*slist_erase_after_range */
    /*slist_splice            */
    /*slist_splice_pos        */
    /*slist_splice_range      */
    /*slist_splice_after_pos  */
    /*slist_splice_after_range*/
    /*_slist_remove           */
    /*slist_remove_if         */
    /*slist_unique            */
    /*slist_unique_if         */
    /*slist_reverse           */
    /*slist_sort              */
    /*slist_sort_if           */
    /*slist_merge             */
    /*slist_merge_if          */
    /*slist_resize            */
    /*_slist_resize_elem      */
    /*slist_clear             */
}

/** local function implementation section **/

/** eof **/

