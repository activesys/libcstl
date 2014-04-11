#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    vector_t* pvec = create_vector(int);
    size_t    i = 0;

    if (pvec == NULL) {
        return -1;
    }

    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec, i * 100);
    }

    for (i = 0; i < vector_size(pvec); ++i) {
        printf("%d, ", *(int*)vector_at(pvec, i));
    }
    printf("\n");

    vector_destroy(pvec);

    return 0;
}
