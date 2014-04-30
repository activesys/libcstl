/*
 * list_assign_range.c
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    list_t*            plist_dest = NULL;
    list_t*            plist_src = NULL;
    set_t*             pset = NULL;
    list_iterator_t    it;
    int                i;

    if ((plist_dest = create_list(int)) == NULL) {
        return -1;
    }
    if ((plist_src = create_list(int)) == NULL) {
        list_destroy(plist_dest);
        return -1;
    }
    if ((pset = create_set(int)) == NULL) {
        list_destroy(plist_dest);
        list_destroy(plist_src);
        return -1;
    }

    list_init(plist_dest);
    for (i = 0; i < 10; ++i) {
        list_push_back(plist_dest, i);
    }

    printf("plist = ");
    for (it = list_begin(plist_dest);
         !iterator_equal(it, list_end(plist_dest));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    list_init(plist_src);
    for (i = 100; i < 1000; i += 100) {
        list_push_front(plist_src, i);
    }

    list_assign_range(plist_dest, list_begin(plist_src), list_end(plist_src));

    printf("plist = ");
    for (it = list_begin(plist_dest);
         !iterator_equal(it, list_end(plist_dest));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    set_init(pset);
    for (i = -10; i < 11; ++i) {
        set_insert(pset, i);
    }

    list_assign_range(plist_dest, set_begin(pset), set_end(pset));

    printf("plist = ");
    for (it = list_begin(plist_dest);
         !iterator_equal(it, list_end(plist_dest));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    list_destroy(plist_dest);
    list_destroy(plist_src);
    set_destroy(pset);

    return 0;
}

