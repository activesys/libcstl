/*
 * list_begin.c
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

    list_push_back(plist, 1);
    list_push_back(plist, 2);

    it = list_begin(plist);
    printf("The first element of l1 is %d\n", *(int*)iterator_get_pointer(it));

    *(int*)iterator_get_pointer(it) = 20;
    printf("The first element of l1 is now %d\n", *(int*)iterator_get_pointer(it));

    list_destroy(plist);

    return 0;
}
