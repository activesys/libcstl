/*
 * list_end.c
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t* plist = create_list(int);
    list_iterator_t it;

    if (plist == NULL) {
        return -1;
    }

    list_init(plist);

    list_push_back(plist, 10);
    list_push_back(plist, 20);
    list_push_back(plist, 30);

    it = list_end(plist);
    it = iterator_prev(it);
    printf("The last integer of l1 is %d\n", *(int*)iterator_get_pointer(it));

    it = iterator_prev(it);
    *(int*)iterator_get_pointer(it) = 400;
    printf("The new nex-to-last integer of l1 is %d\n", *(int*)iterator_get_pointer(it));

    printf("The list is now:");
    for (it = list_begin(plist);
         !iterator_equal(it, list_end(plist));
         it = iterator_next(it)) {
        printf(" %d", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    list_destroy(plist);

    return 0;
}
