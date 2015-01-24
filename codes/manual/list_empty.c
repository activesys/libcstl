/*
 * list_empty.c
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t* plist = create_list(int);

    if (plist == NULL) {
        return -1;
    }

    list_init(plist);

    list_push_back(plist, 10);
    if (list_empty(plist)) {
        printf("The list is empty.\n");
    } else {
        printf("The list is not empty.\n");
    }

    list_destroy(plist);

    return 0;
}
