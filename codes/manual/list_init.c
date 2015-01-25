/*
 * list_init.c
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t* plist = create_list(int);

    if (plist == NULL) {
        return -1;
    }

    /* Create an empty list l0 */
    list_init(plist);

    if (list_empty(plist)) {
        printf("The list is empty.\n");
    } else {
        printf("The list is not empty.\n");
    }

    list_destroy(plist);

    return 0;
}
