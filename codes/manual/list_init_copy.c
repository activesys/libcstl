/*
 * list_init_copy.c
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t*         plist_l1 = NULL;
    list_t*         plist_l2 = NULL;
    list_t*         plist_src = NULL;
    list_iterator_t it;

    /* init src list */
    plist_src = create_list(int);
    if (plist_src == NULL) {
        return -1;
    }
    list_init(plist_src);

    /* init list l1 */
    plist_l1 = create_list(int);
    if (plist_l1 == NULL) {
        list_destroy(plist_src);
        return -1;
    }

    list_init_copy(plist_l1, plist_src);

    if (list_empty(plist_l1)) {
        printf("The list l1 is empty.\n");
    } else {
        printf("The list l1 is not empty.\n");
    }

    /* init list l2 */
    list_push_back(plist_src, 1);
    list_push_back(plist_src, 2);
    list_push_back(plist_src, 3);

    plist_l2 = create_list(int);
    if (plist_l2 == NULL) {
        list_destroy(plist_src);
        list_destroy(plist_l1);
        return -1;
    }

    list_init_copy(plist_l2, plist_src);
    if (list_empty(plist_l2)) {
        printf("The list l2 is empty.\n");
    } else {
        printf("The list l2 is not empty.\n");
        printf("list l2: ");
        for (it = list_begin(plist_l2);
             !iterator_equal(it, list_end(plist_l2));
             it = iterator_next(it)) {
            printf("%d ", *(int*)iterator_get_pointer(it));
        }
        printf("\n");
    }

    list_destroy(plist_src);
    list_destroy(plist_l1);
    list_destroy(plist_l2);

    return 0;
}
