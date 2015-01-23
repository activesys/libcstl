/*
 * list_clear.c
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
    list_push_back(plist, 20);
    list_push_back(plist, 30);

    printf("The size of the list is initially %d\n", list_size(plist));
    list_clear(plist);
    printf("The size of the list after clearing is %d\n", list_size(plist));

    list_destroy(plist);

    return 0;
}
