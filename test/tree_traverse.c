/*
 *  The implementation of tree.
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
#include <string.h>
#include <time.h>
#include <stdarg.h>
#ifndef _WIN32
#include <unistd.h>
#endif

#include "citerator.h"
#include "cvector.h"
#include "clist.h"
#include "cdeque.h"
#include "cstack.h"
#include "cqueue.h"
#include "cslist.h"
#include "cutility.h"
#include "cset.h"
#include "cmap.h"
#include "chash_set.h"
#include "chash_map.h"

#include "cstl_avl_tree_iterator.h"
#include "cstl_avl_tree_private.h"

#include "cstl_rb_tree_iterator.h"
#include "cstl_rb_tree_private.h"

#include "cstl_hashtable_iterator.h"
#include "cstl_hashtable_private.h"

#include "tree_traverse.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_travel_avl_tree(
    avlnode_t* pt_root, size_t t_indentsize, void (*pfun_op)(avlnode_t*))
{
    int i = 0;

    if(pt_root != NULL)
    {
        test_travel_avl_tree(pt_root->_pt_right, t_indentsize+4, pfun_op);

        for(i = 0; i < (int)t_indentsize; ++i)
        {
            printf(" ");
        }

        if(pfun_op != NULL)
        {
            (*pfun_op)(pt_root);
        }

        test_travel_avl_tree(pt_root->_pt_left, t_indentsize+4, pfun_op);
    }
}

void test_travel_rb_tree(
    rbnode_t* pt_root, size_t t_indentsize, void (*pfun_op)(rbnode_t*))
{
    int i = 0;

    if(pt_root != NULL)
    {
        test_travel_rb_tree(pt_root->_pt_right, t_indentsize+4, pfun_op);

        for(i = 0; i < (int)t_indentsize; ++i)
        {
            printf(" ");
        }

        if(pfun_op != NULL)
        {
            (*pfun_op)(pt_root);
        }

        test_travel_rb_tree(pt_root->_pt_left, t_indentsize+4, pfun_op);
    }
}

void show_avlnode_info(avlnode_t* pt_root)
{
    assert(pt_root != NULL);
    printf("%d : %d\n", *(int*)pt_root->_pc_data, pt_root->_un_height);
}

void show_rbnode_info(rbnode_t* pt_root)
{
    assert(pt_root != NULL);
    printf("%lf : ", *(double*)pt_root->_pc_data);
    if(pt_root->_t_color == red)
    {
        printf("r\n");
    }
    else
    {
        printf("b\n");
    }
}

void show_map_rbnode_info(rbnode_t* pt_root)
{
    assert(pt_root != NULL);
    printf("<%d,%f> : ",
        *(int*)(pair_first((pair_t*)(pt_root->_pc_data))),
        *(double*)(pair_second((pair_t*)(pt_root->_pc_data))));
    if(pt_root->_t_color == red)
    {
        printf("r\n");
    }
    else
    {
        printf("b\n");
    }
}

void test_travel_hashtable(vector_t* pt_vector)
{
    int i = 0;
    hashnode_t** ppt_bucket = NULL;
    hashnode_t*  pt_node = NULL;

    assert(pt_vector != NULL);

    for(i = 0; (size_t)i < vector_size(pt_vector); ++i)
    {
        printf("#%d:", i);
        ppt_bucket = (hashnode_t**)vector_at(pt_vector, i);
        pt_node = *ppt_bucket;
        while(pt_node != NULL)
        {
            printf(" %d,", *(int*)pt_node->_pc_data);
            pt_node = pt_node->_pt_next;
        }
        printf("\n");
    }
}

void test_travel_hashtable_pair(vector_t* pt_vector)
{
    int i = 0;
    hashnode_t** ppt_bucket = NULL;
    hashnode_t*  pt_node = NULL;

    assert(pt_vector != NULL);

    for(i = 0; (size_t)i < vector_size(pt_vector); ++i)
    {
        printf("#%d:", i);
        ppt_bucket = (hashnode_t**)vector_at(pt_vector, i);
        pt_node = *ppt_bucket;
        while(pt_node != NULL)
        {
            printf(" <%d,%f>,", 
                *(int*)pair_first(((pair_t*)pt_node->_pc_data)),
                *(double*)pair_second(((pair_t*)pt_node->_pc_data)));
            pt_node = pt_node->_pt_next;
        }
        printf("\n");
    }
}
/** local function implementation section **/
/** eof **/

