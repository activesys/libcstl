#include <stdio.h>
#include <stdlib.h>
#include <cstl/clist.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    list_t*     plist = NULL;
    vector_t*   pvec = NULL;
    iterator_t  it_list;
    iterator_t  it_vec;
    size_t      i = 0;
    size_t      j = 0;
    size_t      count = 0;

    pvec = create_vector(int);
    if (pvec == NULL) {
        return -1;
    }
    plist = create_list(vector_t<int>);
    if (plist == NULL) {
        vector_destroy(pvec);
        return -1;
    }

    list_init(plist);
    vector_init(pvec);

    srand((unsigned)time(NULL));
    for (i = 0; i < 10; ++i) {
        count = rand() % 10;
        vector_clear(pvec);
        for (j = 0; j < count; ++j) {
            vector_push_back(pvec, rand() - rand());
        }
        list_push_back(plist, pvec);
    }

    printf("before sorting:\n");
    for (it_list = list_begin(plist);
         !iterator_equal(it_list, list_end(plist));
         it_list = iterator_next(it_list)) {
        printf("[");
        for (it_vec = vector_begin(iterator_get_pointer(it_list));
             !iterator_equal(it_vec, vector_end(iterator_get_pointer(it_list)));
             it_vec = iterator_next(it_vec)) {
            printf("%d, ", *(int*)iterator_get_pointer(it_vec));
        }
        printf("]\n");
    }

    list_sort(plist);

    printf("after sorting:\n");
    for (it_list = list_begin(plist);
         !iterator_equal(it_list, list_end(plist));
         it_list = iterator_next(it_list)) {
        printf("[");
        for (it_vec = vector_begin(iterator_get_pointer(it_list));
             !iterator_equal(it_vec, vector_end(iterator_get_pointer(it_list)));
             it_vec = iterator_next(it_vec)) {
            printf("%d, ", *(int*)iterator_get_pointer(it_vec));
        }
        printf("]\n");
    }

    return 0;
}
