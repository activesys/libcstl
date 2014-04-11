#include <stdio.h>
#include <cstl/clist.h>

typedef struct _user {
    int n_first;
    int n_second;
} user_t;

static void _user_init(const void* cpv_input, void* pv_output)
{
    ((user_t*)cpv_input)->n_first = 0;
    ((user_t*)cpv_input)->n_second = 0;
    *(bool_t*)pv_output = true;
}

static void _user_destroy(const void* cpv_input, void* pv_output)
{
    ((user_t*)cpv_input)->n_first = 0;
    ((user_t*)cpv_input)->n_second = 0;
    *(bool_t*)pv_output = true;
}

static void _user_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    ((user_t*)cpv_first)->n_first = ((user_t*)cpv_second)->n_first;
    ((user_t*)cpv_first)->n_second = ((user_t*)cpv_second)->n_second;
    *(bool_t*)pv_output = true;
}

static void _user_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = 
        ((user_t*)cpv_first)->n_first < ((user_t*)cpv_second)->n_first ? true : false;
}

int main(int argc, char* argv[])
{
    list_t*     plist = NULL;
    iterator_t  it;
    user_t      t_sample;

    type_register(user_t, _user_init, _user_copy, _user_less, _user_destroy);

    plist = create_list(user_t);
    if (plist == NULL) {
        return -1;
    }

    list_init(plist);
    t_sample.n_first = 100;
    t_sample.n_second = 45;
    list_push_back(plist, &t_sample);
    t_sample.n_first = 400;
    t_sample.n_second = -234;
    list_push_back(plist, &t_sample);
    t_sample.n_first = 0;
    t_sample.n_second = 1024;
    list_push_back(plist, &t_sample);
    t_sample.n_first = 300;
    t_sample.n_second = -444;
    list_push_back(plist, &t_sample);
    t_sample.n_first = 200;
    t_sample.n_second = 0;
    list_push_back(plist, &t_sample);

    printf("before sorting: ");
    for (it = list_begin(plist);
         !iterator_equal(it, list_end(plist));
         it = iterator_next(it)) {
        iterator_get_value(it, &t_sample);
        printf("(%d, %d), ", t_sample.n_first, t_sample.n_second);
    }
    printf("\n");

    list_sort(plist);

    printf("after sorting: ");
    for (it = list_begin(plist);
         !iterator_equal(it, list_end(plist));
         it = iterator_next(it)) {
        iterator_get_value(it, &t_sample);
        printf("(%d, %d), ", t_sample.n_first, t_sample.n_second);
    }
    printf("\n");

    return 0;
}
