/*
 * list_assign.c
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t*         plist1 = NULL;
    list_t*         plist2 = NULL;
    list_iterator_t it;

    if ((plist1 = create_list(int)) == NULL) {
        return -1;
    }
    if ((plist2 = create_list(int)) == NULL) {
        list_destroy(plist1);
        return -1;
    }

    list_init(plist1);
    list_push_back(plist1, 10);
    list_push_back(plist1, 20);
    list_push_back(plist1, 30);

    list_init(plist2);
    list_push_back(plist2, 40);
    list_push_back(plist2, 50);
    list_push_back(plist2, 60);

    printf("l1 =");
    for (it = list_begin(plist1);
         !iterator_equal(it, list_end(plist1));
         it = iterator_next(it)) {
        printf(" %d", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    printf("l2 =");
    for (it = list_begin(plist2);
         !iterator_equal(it, list_end(plist2));
         it = iterator_next(it)) {
        printf(" %d", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    list_assign(plist1, plist2);

    printf("l1 =");
    for (it = list_begin(plist1);
         !iterator_equal(it, list_end(plist1));
         it = iterator_next(it)) {
        printf(" %d", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    printf("l2 =");
    for (it = list_begin(plist2);
         !iterator_equal(it, list_end(plist2));
         it = iterator_next(it)) {
        printf(" %d", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    list_destroy(plist1);
    list_destroy(plist2);

    return 0;
}

