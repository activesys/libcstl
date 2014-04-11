#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    vector_t*   pvec = create_vector(int);
    iterator_t  it;

    if (pvec == NULL) {
        return -1;
    }

    vector_init(pvec);
    vector_push_back(pvec, 500);
    vector_push_back(pvec, 300);
    vector_push_back(pvec, 0);
    vector_push_back(pvec, 600);
    vector_push_back(pvec, 900);
    vector_push_back(pvec, 100);
    vector_push_back(pvec, 800);
    vector_push_back(pvec, 400);
    vector_push_back(pvec, 700);
    vector_push_back(pvec, 200);

    printf("before sorting: ");
    for (it = vector_begin(pvec);
         !iterator_equal(it, vector_end(pvec)); 
         it = iterator_next(it)) {
        printf("%d, ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    algo_sort(vector_begin(pvec), vector_end(pvec));

    printf("after sorting: ");
    for (it = vector_begin(pvec);
         !iterator_equal(it, vector_end(pvec)); 
         it = iterator_next(it)) {
        printf("%d, ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    vector_destroy(pvec);

    return 0;
}
