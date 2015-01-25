/*
 * list_init_copy_range.c
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    list_t*     plist = NULL;
    vector_t*   pvector = NULL;
    iterator_t  it;

    pvector = create_vector(int);
    if (pvector == NULL) {
        return -1;
    }

    vector_init(pvector);
    vector_push_back(pvector, 1);
    vector_push_back(pvector, 3);
    vector_push_back(pvector, 5);

    plist = create_list(int);
    if (plist == NULL) {
        vector_destroy(pvector);
        return -1;
    }

    list_init_copy_range(plist, vector_begin(pvector), vector_end(pvector));

    printf("The list is : ");
    for (it = list_begin(plist);
         !iterator_equal(it, list_end(plist));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    list_destroy(plist);
    vector_destroy(pvector);

    return 0;
}
