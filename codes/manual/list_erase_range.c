/*
 * list_erase_range.c
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t*         plist = create_list(int);
    list_iterator_t it;

    if (plist == NULL) {
        return -1;
    }

    list_init(plist);

    list_push_back(plist, 10);
    list_push_back(plist, 20);
    list_push_back(plist, 30);
    list_push_back(plist, 40);
    list_push_back(plist, 50);

    printf("The initial list is:");
    for (it = list_begin(plist);
         !iterator_equal(it, list_end(plist));
         it = iterator_next(it)) {
        printf(" %d", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    list_erase_range(plist, list_begin(plist), iterator_next(list_begin(plist)));
    printf("After erasing the first element, the list becomes:");
    for (it = list_begin(plist);
         !iterator_equal(it, list_end(plist));
         it = iterator_next(it)) {
        printf(" %d", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    list_erase_range(plist, list_begin(plist), list_end(plist));
    printf("After erasing all elements, the size of list is %d.\n", list_size(plist));

    list_destroy(plist);

    return 0;
}
