/*
 * list_init_copy_array.c
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t*         plist = create_list(int);
    list_iterator_t it;
    int             array[] = {1, 10, 100, 1000, 10000};

    if (plist == NULL) {
        return -1;
    }

    list_init_copy_array(plist, array, 5);

    printf("The list is : ");
    for (it = list_begin(plist);
         !iterator_equal(it, list_end(plist));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    list_destroy(plist);

    return 0;
}
