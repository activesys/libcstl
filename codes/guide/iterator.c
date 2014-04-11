#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    vector_t*   pvec = create_vector(int);
    iterator_t  it;
    size_t      i = 0;

    if (pvec == NULL) {
        return -1;
    }

    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec, i * 100);
    }

    for (it = vector_begin(pvec);
         !iterator_equal(it, vector_end(pvec)); 
         it = iterator_next(it)) {
        printf("%d, ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    vector_destroy(pvec);

    return 0;
}
