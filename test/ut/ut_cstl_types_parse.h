#ifndef _UT_CSTL_TYPES_PARSE_H_
#define _UT_CSTL_TYPES_PARSE_H_

UT_SUIT_DECLARATION(cstl_types_parse)

/*
 * test _type_get_token
 */
UT_CASE_DECLARATION(_type_get_token)
void test__type_get_token__sign_left_bracket(void** state);
void test__type_get_token__sign_right_bracket(void** state);
void test__type_get_token__sign_comma(void** state);
void test__type_get_token__sign_space_and_eoi(void** state);
void test__type_get_token__sign_invalid(void** state);
void test__type_get_token__identifier(void** state);
void test__type_get_token__identifier_with_underline(void** state);
void test__type_get_token__identifier_pointer(void** state);
void test__type_get_token__identifier_multipointer(void** state);
void test__type_get_token__key_char(void** state);
void test__type_get_token__key_char_pointer(void** state);
void test__type_get_token__key_short(void** state);
void test__type_get_token__key_int(void** state);
void test__type_get_token__key_long(void** state);
void test__type_get_token__key_double(void** state);
void test__type_get_token__key_float(void** state);
void test__type_get_token__key_signed(void** state);
void test__type_get_token__key_unsigned(void** state);
void test__type_get_token__key_bool(void** state);
void test__type_get_token__key_struct(void** state);
void test__type_get_token__key_enum(void** state);
void test__type_get_token__key_union(void** state);
void test__type_get_token__key_vector(void** state);
void test__type_get_token__key_list(void** state);
void test__type_get_token__key_slist(void** state);
void test__type_get_token__key_deque(void** state);
void test__type_get_token__key_stack(void** state);
void test__type_get_token__key_queue(void** state);
void test__type_get_token__key_priority_queue(void** state);
void test__type_get_token__key_set(void** state);
void test__type_get_token__key_map(void** state);
void test__type_get_token__key_multiset(void** state);
void test__type_get_token__key_multimap(void** state);
void test__type_get_token__key_hash_set(void** state);
void test__type_get_token__key_hash_map(void** state);
void test__type_get_token__key_hash_multiset(void** state);
void test__type_get_token__key_hash_multimap(void** state);
void test__type_get_token__key_pair(void** state);
void test__type_get_token__key_string(void** state);
void test__type_get_token__key_iterator(void** state);
void test__type_get_token__key_vector_iterator(void** state);
void test__type_get_token__key_list_iterator(void** state);
void test__type_get_token__key_slist_iterator(void** state);
void test__type_get_token__key_deque_iterator(void** state);
void test__type_get_token__key_set_iterator(void** state);
void test__type_get_token__key_map_iterator(void** state);
void test__type_get_token__key_multiset_iterator(void** state);
void test__type_get_token__key_multimap_iterator(void** state);
void test__type_get_token__key_hash_set_iterator(void** state);
void test__type_get_token__key_hash_map_iterator(void** state);
void test__type_get_token__key_hash_multiset_iterator(void** state);
void test__type_get_token__key_hash_multimap_iterator(void** state);
void test__type_get_token__key_string_iterator(void** state);
void test__type_get_token__key_input_iterator(void** state);
void test__type_get_token__key_output_iterator(void** state);
void test__type_get_token__key_forward_iterator(void** state);
void test__type_get_token__key_bidirectional_iterator(void** state);
void test__type_get_token__key_random_access_iterator(void** state);

#define UT_CSTL_TYPES_PARSE_CASE\
    UT_SUIT_BEGIN(cstl_types_parse, test__type_get_token__sign_left_bracket),\
    UT_CASE(test__type_get_token__sign_right_bracket),\
    UT_CASE(test__type_get_token__sign_comma),\
    UT_CASE(test__type_get_token__sign_space_and_eoi),\
    UT_CASE(test__type_get_token__sign_invalid),\
    UT_CASE(test__type_get_token__identifier),\
    UT_CASE(test__type_get_token__identifier_with_underline),\
    UT_CASE(test__type_get_token__identifier_pointer),\
    UT_CASE(test__type_get_token__identifier_multipointer),\
    UT_CASE(test__type_get_token__key_char),\
    UT_CASE(test__type_get_token__key_char_pointer),\
    UT_CASE(test__type_get_token__key_short),\
    UT_CASE(test__type_get_token__key_int),\
    UT_CASE(test__type_get_token__key_long),\
    UT_CASE(test__type_get_token__key_double),\
    UT_CASE(test__type_get_token__key_float),\
    UT_CASE(test__type_get_token__key_signed),\
    UT_CASE(test__type_get_token__key_unsigned),\
    UT_CASE(test__type_get_token__key_bool),\
    UT_CASE(test__type_get_token__key_struct),\
    UT_CASE(test__type_get_token__key_enum),\
    UT_CASE(test__type_get_token__key_union),\
    UT_CASE(test__type_get_token__key_vector),\
    UT_CASE(test__type_get_token__key_list),\
    UT_CASE(test__type_get_token__key_slist),\
    UT_CASE(test__type_get_token__key_deque),\
    UT_CASE(test__type_get_token__key_stack),\
    UT_CASE(test__type_get_token__key_queue),\
    UT_CASE(test__type_get_token__key_priority_queue),\
    UT_CASE(test__type_get_token__key_set),\
    UT_CASE(test__type_get_token__key_map),\
    UT_CASE(test__type_get_token__key_multiset),\
    UT_CASE(test__type_get_token__key_multimap),\
    UT_CASE(test__type_get_token__key_hash_set),\
    UT_CASE(test__type_get_token__key_hash_map),\
    UT_CASE(test__type_get_token__key_hash_multiset),\
    UT_CASE(test__type_get_token__key_hash_multimap),\
    UT_CASE(test__type_get_token__key_pair),\
    UT_CASE(test__type_get_token__key_string),\
    UT_CASE(test__type_get_token__key_iterator),\
    UT_CASE(test__type_get_token__key_vector_iterator),\
    UT_CASE(test__type_get_token__key_list_iterator),\
    UT_CASE(test__type_get_token__key_slist_iterator),\
    UT_CASE(test__type_get_token__key_deque_iterator),\
    UT_CASE(test__type_get_token__key_set_iterator),\
    UT_CASE(test__type_get_token__key_map_iterator),\
    UT_CASE(test__type_get_token__key_multiset_iterator),\
    UT_CASE(test__type_get_token__key_multimap_iterator),\
    UT_CASE(test__type_get_token__key_hash_set_iterator),\
    UT_CASE(test__type_get_token__key_hash_map_iterator),\
    UT_CASE(test__type_get_token__key_hash_multiset_iterator),\
    UT_CASE(test__type_get_token__key_hash_multimap_iterator),\
    UT_CASE(test__type_get_token__key_string_iterator),\
    UT_CASE(test__type_get_token__key_input_iterator),\
    UT_CASE(test__type_get_token__key_output_iterator),\
    UT_CASE(test__type_get_token__key_forward_iterator),\
    UT_CASE(test__type_get_token__key_bidirectional_iterator),\
    UT_CASE(test__type_get_token__key_random_access_iterator),\

#endif /* _UT_CSTL_TYPES_PARSE_H_ */

