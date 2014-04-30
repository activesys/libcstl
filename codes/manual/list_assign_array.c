/*
 * list_assign_array.c
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t*         plist = create_list(int);
    list_iterator_t it;
    int             array[] = {99, -76, 201, 444, -9, 9120, 243, -5562, 1, -91};

    if (plist == NULL) {
        return -1;
    }

    list_init(plist);
    list_push_back(plist, 10);
    list_push_back(plist, 20);
    list_push_back(plist, 30);

    printf("list = ");
    for (it = list_begin(plist);
         !iterator_equal(it, list_end(plist));
         it = iterator_next(it)) {
        printf("%d, ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    list_assign_array(plist, array, 10);

    printf("list = ");
    for (it = list_begin(plist);
         !iterator_equal(it, list_end(plist));
         it = iterator_next(it)) {
        printf("%d, ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    list_destroy(plist);

    return 0;
}

