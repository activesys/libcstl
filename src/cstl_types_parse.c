/*
 *  The implementation of cstl types parse functions.
 *  Copyright (C)  2008 - 2014  Wangbo
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
 */

/** include section **/
#include <cstl/cstl_def.h>
#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>

#include "cstl_types_aux.h"
#include "cstl_types_parse.h"
#include "cstl_types_builtin.h"

/** local constant declaration and local macro section **/
#define _TOKEN_MATCH(s_tokentext, s_formalname)\
    do {\
        assert(strncmp(_gt_typeanalysis._s_tokentext, s_tokentext, _TYPE_NAME_SIZE) == 0);\
        strncat(s_formalname, _gt_typeanalysis._s_tokentext, _TYPE_NAME_SIZE);\
    } while (false)
#define _TOKEN_MATCH_SPACE(s_formalname)\
    strncat(s_formalname, _TOKEN_TEXT_SPACE, _TYPE_NAME_SIZE)
#define _TOKEN_MATCH_IDENTIFIER(s_formalname)\
    strncat(s_formalname, _gt_typeanalysis._s_tokentext, _TYPE_NAME_SIZE)

#define _TOKEN_TEXT_CHAR                           "char"
#define _TOKEN_TEXT_SHORT                          "short"
#define _TOKEN_TEXT_INT                            "int"
#define _TOKEN_TEXT_LONG                           "long"
#define _TOKEN_TEXT_FLOAT                          "float"
#define _TOKEN_TEXT_DOUBLE                         "double"
#define _TOKEN_TEXT_SIGNED                         "signed"
#define _TOKEN_TEXT_UNSIGNED                       "unsigned"
#define _TOKEN_TEXT_VOID                           "void"
#define _TOKEN_TEXT_CSTL_BOOL                      "bool_t"
#define _TOKEN_TEXT_BOOL                           "_Bool"
#define _TOKEN_TEXT_STRUCT                         "struct"
#define _TOKEN_TEXT_ENUM                           "enum"
#define _TOKEN_TEXT_UNION                          "union"
#define _TOKEN_TEXT_VECTOR                         "vector_t"
#define _TOKEN_TEXT_LIST                           "list_t"
#define _TOKEN_TEXT_SLIST                          "slist_t"
#define _TOKEN_TEXT_DEQUE                          "deque_t"
#define _TOKEN_TEXT_STACK                          "stack_t"
#define _TOKEN_TEXT_QUEUE                          "queue_t"
#define _TOKEN_TEXT_PRIORITY_QUEUE                 "priority_queue_t"
#define _TOKEN_TEXT_SET                            "set_t"
#define _TOKEN_TEXT_MAP                            "map_t"
#define _TOKEN_TEXT_MULTISET                       "multiset_t"
#define _TOKEN_TEXT_MULTIMAP                       "multimap_t"
#define _TOKEN_TEXT_HASH_SET                       "hash_set_t"
#define _TOKEN_TEXT_HASH_MAP                       "hash_map_t"
#define _TOKEN_TEXT_HASH_MULTISET                  "hash_multiset_t"
#define _TOKEN_TEXT_HASH_MULTIMAP                  "hash_multimap_t"
#define _TOKEN_TEXT_PAIR                           "pair_t"
#define _TOKEN_TEXT_STRING                         "string_t"
#define _TOKEN_TEXT_RANGE                          "range_t"
#define _TOKEN_TEXT_BASIC_STRING                   "basic_string_t"
#define _TOKEN_TEXT_ITERATOR                       "iterator_t"
#define _TOKEN_TEXT_VECTOR_ITERATOR                "vector_iterator_t"
#define _TOKEN_TEXT_LIST_ITERATOR                  "list_iterator_t"
#define _TOKEN_TEXT_SLIST_ITERATOR                 "slist_iterator_t"
#define _TOKEN_TEXT_DEQUE_ITERATOR                 "deque_iterator_t"
#define _TOKEN_TEXT_SET_ITERATOR                   "set_iterator_t"
#define _TOKEN_TEXT_MAP_ITERATOR                   "map_iterator_t"
#define _TOKEN_TEXT_MULTISET_ITERATOR              "multiset_iterator_t"
#define _TOKEN_TEXT_MULTIMAP_ITERATOR              "multimap_iterator_t"
#define _TOKEN_TEXT_HASH_SET_ITERATOR              "hash_set_iterator_t"
#define _TOKEN_TEXT_HASH_MAP_ITERATOR              "hash_map_iterator_t"
#define _TOKEN_TEXT_HASH_MULTISET_ITERATOR         "hash_multiset_iterator_t"
#define _TOKEN_TEXT_HASH_MULTIMAP_ITERATOR         "hash_multimap_iterator_t"
#define _TOKEN_TEXT_STRING_ITERATOR                "string_iterator_t"
#define _TOKEN_TEXT_INPUT_ITERATOR                 "input_iterator_t"
#define _TOKEN_TEXT_OUTPUT_ITERATOR                "output_iterator_t"
#define _TOKEN_TEXT_FORWARD_ITERATOR               "forward_iterator_t"
#define _TOKEN_TEXT_BIDIRECTIONAL_ITERATOR         "bidirectional_iterator_t"
#define _TOKEN_TEXT_RANDOM_ACCESS_ITERATOR         "random_access_iterator_t"
#define _TOKEN_TEXT_BASIC_STRING_ITERATOR          "basic_string_iterator_t"
#define _TOKEN_TEXT_SPACE                          " "
#define _TOKEN_TEXT_LEFT_BRACKET                   "<"
#define _TOKEN_TEXT_RIGHT_BRACKET                  ">"
#define _TOKEN_TEXT_COMMA                          ","
#define _TOKEN_TEXT_POINTER                        "*"
#define _TOKEN_TEXT_EMPTY                          ""
#define _TOKEN_CHARACTER_BLANK                     ' '
#define _TOKEN_CHARACTER_LEFT_BRACKET              '<'
#define _TOKEN_CHARACTER_RIGHT_BRACKET             '>'
#define _TOKEN_CHARACTER_COMMA                     ','
#define _TOKEN_CHARACTER_POINTER                   '*'
#define _TOKEN_CHARACTER_UNDERLINE                 '_'
#define _TOKEN_CHARACTER_END_OF_INPUT              '\0'

/** local data type declaration and local struct, union, enum section **/
typedef struct _tagkeytable
{
    _typetoken_t _t_token;
    const char*  _s_tokentext;
}keytable_t;

/** local function prototype section **/

/** exported global variable definition section **/
_typeanalysis_t _gt_typeanalysis = {{'\0'}, {'\0'}, 0, _TOKEN_INVALID};

/** local global variable definition section **/
static keytable_t _sgt_table[] = {
    {_TOKEN_KEY_CHAR,                   _TOKEN_TEXT_CHAR},
    {_TOKEN_KEY_SHORT,                  _TOKEN_TEXT_SHORT},
    {_TOKEN_KEY_INT,                    _TOKEN_TEXT_INT},
    {_TOKEN_KEY_LONG,                   _TOKEN_TEXT_LONG},
    {_TOKEN_KEY_FLOAT,                  _TOKEN_TEXT_FLOAT},
    {_TOKEN_KEY_DOUBLE,                 _TOKEN_TEXT_DOUBLE},
    {_TOKEN_KEY_SIGNED,                 _TOKEN_TEXT_SIGNED},
    {_TOKEN_KEY_UNSIGNED,               _TOKEN_TEXT_UNSIGNED},
    {_TOKEN_KEY_VOID,                   _TOKEN_TEXT_VOID},
    {_TOKEN_KEY_CSTL_BOOL,              _TOKEN_TEXT_CSTL_BOOL},
    {_TOKEN_KEY_BOOL,                   _TOKEN_TEXT_BOOL},
    {_TOKEN_KEY_STRUCT,                 _TOKEN_TEXT_STRUCT},
    {_TOKEN_KEY_ENUM,                   _TOKEN_TEXT_ENUM},
    {_TOKEN_KEY_UNION,                  _TOKEN_TEXT_UNION},
    {_TOKEN_KEY_VECTOR,                 _TOKEN_TEXT_VECTOR},
    {_TOKEN_KEY_LIST,                   _TOKEN_TEXT_LIST},
    {_TOKEN_KEY_SLIST,                  _TOKEN_TEXT_SLIST},
    {_TOKEN_KEY_DEQUE,                  _TOKEN_TEXT_DEQUE},
    {_TOKEN_KEY_STACK,                  _TOKEN_TEXT_STACK},
    {_TOKEN_KEY_QUEUE,                  _TOKEN_TEXT_QUEUE},
    {_TOKEN_KEY_PRIORITY_QUEUE,         _TOKEN_TEXT_PRIORITY_QUEUE},
    {_TOKEN_KEY_SET,                    _TOKEN_TEXT_SET},
    {_TOKEN_KEY_MAP,                    _TOKEN_TEXT_MAP},
    {_TOKEN_KEY_MULTISET,               _TOKEN_TEXT_MULTISET},
    {_TOKEN_KEY_MULTIMAP,               _TOKEN_TEXT_MULTIMAP},
    {_TOKEN_KEY_HASH_SET,               _TOKEN_TEXT_HASH_SET},
    {_TOKEN_KEY_HASH_MAP,               _TOKEN_TEXT_HASH_MAP},
    {_TOKEN_KEY_HASH_MULTISET,          _TOKEN_TEXT_HASH_MULTISET},
    {_TOKEN_KEY_HASH_MULTIMAP,          _TOKEN_TEXT_HASH_MULTIMAP},
    {_TOKEN_KEY_PAIR,                   _TOKEN_TEXT_PAIR},
    {_TOKEN_KEY_STRING,                 _TOKEN_TEXT_STRING},
    {_TOKEN_KEY_RANGE,                  _TOKEN_TEXT_RANGE},
    {_TOKEN_KEY_BASIC_STRING,           _TOKEN_TEXT_BASIC_STRING},
    {_TOKEN_KEY_ITERATOR,               _TOKEN_TEXT_ITERATOR},
    {_TOKEN_KEY_VECTOR_ITERATOR,        _TOKEN_TEXT_VECTOR_ITERATOR},
    {_TOKEN_KEY_LIST_ITERATOR,          _TOKEN_TEXT_LIST_ITERATOR},
    {_TOKEN_KEY_SLIST_ITERATOR,         _TOKEN_TEXT_SLIST_ITERATOR},
    {_TOKEN_KEY_DEQUE_ITERATOR,         _TOKEN_TEXT_DEQUE_ITERATOR},
    {_TOKEN_KEY_SET_ITERATOR,           _TOKEN_TEXT_SET_ITERATOR},
    {_TOKEN_KEY_MAP_ITERATOR,           _TOKEN_TEXT_MAP_ITERATOR},
    {_TOKEN_KEY_MULTISET_ITERATOR,      _TOKEN_TEXT_MULTISET_ITERATOR},
    {_TOKEN_KEY_MULTIMAP_ITERATOR,      _TOKEN_TEXT_MULTIMAP_ITERATOR},
    {_TOKEN_KEY_HASH_SET_ITERATOR,      _TOKEN_TEXT_HASH_SET_ITERATOR},
    {_TOKEN_KEY_HASH_MAP_ITERATOR,      _TOKEN_TEXT_HASH_MAP_ITERATOR},
    {_TOKEN_KEY_HASH_MULTISET_ITERATOR, _TOKEN_TEXT_HASH_MULTISET_ITERATOR},
    {_TOKEN_KEY_HASH_MULTIMAP_ITERATOR, _TOKEN_TEXT_HASH_MULTIMAP_ITERATOR},
    {_TOKEN_KEY_STRING_ITERATOR,        _TOKEN_TEXT_STRING_ITERATOR},
    {_TOKEN_KEY_INPUT_ITERATOR,         _TOKEN_TEXT_INPUT_ITERATOR},
    {_TOKEN_KEY_OUTPUT_ITERATOR,        _TOKEN_TEXT_OUTPUT_ITERATOR},
    {_TOKEN_KEY_FORWARD_ITERATOR,       _TOKEN_TEXT_FORWARD_ITERATOR},
    {_TOKEN_KEY_BIDIRECTIONAL_ITERATOR, _TOKEN_TEXT_BIDIRECTIONAL_ITERATOR},
    {_TOKEN_KEY_RANDOM_ACCESS_ITERATOR, _TOKEN_TEXT_RANDOM_ACCESS_ITERATOR},
    {_TOKEN_KEY_BASIC_STRING_ITERATOR,  _TOKEN_TEXT_BASIC_STRING_ITERATOR},
    {_TOKEN_IDENTIFIER,                 NULL}
};

/** exported function implementation section **/
/**
 * Normalize the typename, test the typename is valid or not and get the type style 
 */
_typestyle_t _type_get_style(const char* s_typename, char* s_formalname)
{
    /*
     * this parser algorithm is associated with BNF in file doc/project/libcstl.bnf.
     */
    char            s_userdefine[_TYPE_NAME_SIZE + 1];
    _typestyle_t    t_style = _TYPE_INVALID;

    assert(s_typename != NULL);
    assert(s_formalname != NULL);
    assert(strlen(s_typename) <= _TYPE_NAME_SIZE);

    /* initialize an array efficently */
    s_formalname[0] = s_formalname[_TYPE_NAME_SIZE] = '\0';

    /* find type style cache */
    if ((t_style = _type_cache_find(s_typename, s_formalname)) != _TYPE_INVALID) {
        return t_style;
    }

    /* initialize the type analysis */
    s_userdefine[0] = s_userdefine[_TYPE_NAME_SIZE] = '\0';
    memset(_gt_typeanalysis._s_typename, '\0', _TYPE_NAME_SIZE+1);
    memset(_gt_typeanalysis._s_tokentext, '\0', _TYPE_NAME_SIZE+1);
    _gt_typeanalysis._t_index = 0;
    _gt_typeanalysis._t_token = _TOKEN_INVALID;
    strncpy(_gt_typeanalysis._s_typename, s_typename, _TYPE_NAME_SIZE);

    /* TYPE_DESCRIPT -> C_BUILTIN | USER_DEFINE | CSTL_BUILTIN */
    _type_get_token();
    switch (_gt_typeanalysis._t_token) {
        /* TYPE_DESCRIPT -> C_BUILTIN */
        case _TOKEN_KEY_CHAR:
        case _TOKEN_KEY_SHORT:
        case _TOKEN_KEY_INT:
        case _TOKEN_KEY_LONG:
        case _TOKEN_KEY_FLOAT:
        case _TOKEN_KEY_DOUBLE:
        case _TOKEN_KEY_SIGNED:
        case _TOKEN_KEY_UNSIGNED:
        case _TOKEN_KEY_VOID:
        case _TOKEN_KEY_CSTL_BOOL:
        case _TOKEN_KEY_BOOL:
            t_style = _type_parse_c_builtin(s_formalname) ? _TYPE_C_BUILTIN : _TYPE_INVALID;
            break;
        /* TYPE_DESCRIPT -> USER_DEFINE */
        case _TOKEN_KEY_STRUCT:
        case _TOKEN_KEY_ENUM:
        case _TOKEN_KEY_UNION:
        case _TOKEN_IDENTIFIER:
            if (_type_parse_user_define(s_userdefine)) {
                t_style = _TYPE_USER_DEFINE;
                strncat(s_formalname, s_userdefine, _TYPE_NAME_SIZE);
            } else {
                t_style = _TYPE_INVALID;
            }
            break;
        /* TYPE_DESCRIPT -> CSTL_BUILTIN */
        case _TOKEN_KEY_VECTOR:
        case _TOKEN_KEY_LIST:
        case _TOKEN_KEY_SLIST:
        case _TOKEN_KEY_DEQUE:
        case _TOKEN_KEY_STACK:
        case _TOKEN_KEY_QUEUE:
        case _TOKEN_KEY_PRIORITY_QUEUE:
        case _TOKEN_KEY_SET:
        case _TOKEN_KEY_MAP:
        case _TOKEN_KEY_MULTISET:
        case _TOKEN_KEY_MULTIMAP:
        case _TOKEN_KEY_HASH_SET:
        case _TOKEN_KEY_HASH_MAP:
        case _TOKEN_KEY_HASH_MULTISET:
        case _TOKEN_KEY_HASH_MULTIMAP:
        case _TOKEN_KEY_PAIR:
        case _TOKEN_KEY_STRING:
        case _TOKEN_KEY_RANGE:
        case _TOKEN_KEY_BASIC_STRING:
        case _TOKEN_KEY_ITERATOR:
        case _TOKEN_KEY_VECTOR_ITERATOR:
        case _TOKEN_KEY_LIST_ITERATOR:
        case _TOKEN_KEY_SLIST_ITERATOR:
        case _TOKEN_KEY_DEQUE_ITERATOR:
        case _TOKEN_KEY_SET_ITERATOR:
        case _TOKEN_KEY_MAP_ITERATOR:
        case _TOKEN_KEY_MULTISET_ITERATOR:
        case _TOKEN_KEY_MULTIMAP_ITERATOR:
        case _TOKEN_KEY_HASH_SET_ITERATOR:
        case _TOKEN_KEY_HASH_MAP_ITERATOR:
        case _TOKEN_KEY_HASH_MULTISET_ITERATOR:
        case _TOKEN_KEY_HASH_MULTIMAP_ITERATOR:
        case _TOKEN_KEY_STRING_ITERATOR:
        case _TOKEN_KEY_INPUT_ITERATOR:
        case _TOKEN_KEY_OUTPUT_ITERATOR:
        case _TOKEN_KEY_FORWARD_ITERATOR:
        case _TOKEN_KEY_BIDIRECTIONAL_ITERATOR:
        case _TOKEN_KEY_RANDOM_ACCESS_ITERATOR:
        case _TOKEN_KEY_BASIC_STRING_ITERATOR:
            t_style = _type_parse_cstl_builtin(s_formalname) ? _TYPE_CSTL_BUILTIN : _TYPE_INVALID;
            break;
        default:
            t_style = _TYPE_INVALID;
            break;
    }

    _type_get_token();
    t_style = _gt_typeanalysis._t_token == _TOKEN_END_OF_INPUT ? t_style : _TYPE_INVALID;

    /* update type style cache */
    if (t_style != _TYPE_INVALID) {
        _type_cache_update(s_typename, s_formalname, t_style);
    }

    return t_style;
}

/**
 * Get the next toke from input string.
 */
void _type_get_token(void)
{
    /*
     * this lexical analysis algorithm is associated with 
     * lexical state machine in file doc/project/libcstl.bnf.
     */
    size_t       t_tokentextindex = 0;
    size_t       t_keyindex = 0;
    _typelex_t   t_lexstate = _LEX_START;

    memset(_gt_typeanalysis._s_tokentext, '\0', _TYPE_NAME_SIZE + 1);

    while (t_lexstate != _LEX_ACCEPT) {
        switch (t_lexstate) {
            case _LEX_START:
                if (isalpha(_gt_typeanalysis._s_typename[_gt_typeanalysis._t_index]) ||
                    _gt_typeanalysis._s_typename[_gt_typeanalysis._t_index] == _TOKEN_CHARACTER_UNDERLINE) {
                    _gt_typeanalysis._s_tokentext[t_tokentextindex++] = _gt_typeanalysis._s_typename[_gt_typeanalysis._t_index++];
                    t_lexstate = _LEX_IN_IDENTIFIER;
                } else if (_gt_typeanalysis._s_typename[_gt_typeanalysis._t_index] == _TOKEN_CHARACTER_LEFT_BRACKET) {
                    _gt_typeanalysis._s_tokentext[t_tokentextindex++] = _gt_typeanalysis._s_typename[_gt_typeanalysis._t_index++];
                    _gt_typeanalysis._t_token = _TOKEN_SIGN_LEFT_BRACKET;
                    t_lexstate = _LEX_ACCEPT;
                } else if (_gt_typeanalysis._s_typename[_gt_typeanalysis._t_index] == _TOKEN_CHARACTER_RIGHT_BRACKET) {
                    _gt_typeanalysis._s_tokentext[t_tokentextindex++] = _gt_typeanalysis._s_typename[_gt_typeanalysis._t_index++];
                    _gt_typeanalysis._t_token = _TOKEN_SIGN_RIGHT_BRACKET;
                    t_lexstate = _LEX_ACCEPT;
                } else if (_gt_typeanalysis._s_typename[_gt_typeanalysis._t_index] == _TOKEN_CHARACTER_COMMA) {
                    _gt_typeanalysis._s_tokentext[t_tokentextindex++] = _gt_typeanalysis._s_typename[_gt_typeanalysis._t_index++];
                    _gt_typeanalysis._t_token = _TOKEN_SIGN_COMMA;
                    t_lexstate = _LEX_ACCEPT;
                } else if (_gt_typeanalysis._s_typename[_gt_typeanalysis._t_index] == _TOKEN_CHARACTER_POINTER) {
                    _gt_typeanalysis._s_tokentext[t_tokentextindex++] = _gt_typeanalysis._s_typename[_gt_typeanalysis._t_index++];
                    _gt_typeanalysis._t_token = _TOKEN_SIGN_POINTER;
                    t_lexstate = _LEX_ACCEPT;
                } else if (isspace(_gt_typeanalysis._s_typename[_gt_typeanalysis._t_index])) {
                    _gt_typeanalysis._t_index++;
                    t_lexstate = _LEX_START;
                } else if (_gt_typeanalysis._s_typename[_gt_typeanalysis._t_index] == _TOKEN_CHARACTER_END_OF_INPUT) {
                    _gt_typeanalysis._t_token =  _TOKEN_END_OF_INPUT;
                    t_lexstate = _LEX_ACCEPT;
                } else {
                    _gt_typeanalysis._t_token =  _TOKEN_INVALID;
                    t_lexstate = _LEX_ACCEPT;
                }
                break;
            case _LEX_IN_IDENTIFIER:
                if (isalpha(_gt_typeanalysis._s_typename[_gt_typeanalysis._t_index]) ||
                    isdigit(_gt_typeanalysis._s_typename[_gt_typeanalysis._t_index]) ||
                    _gt_typeanalysis._s_typename[_gt_typeanalysis._t_index] == _TOKEN_CHARACTER_UNDERLINE) {
                    _gt_typeanalysis._s_tokentext[t_tokentextindex++] = _gt_typeanalysis._s_typename[_gt_typeanalysis._t_index++];
                    t_lexstate = _LEX_IN_IDENTIFIER;
                } else {
                    _gt_typeanalysis._t_token = _TOKEN_IDENTIFIER;
                    t_lexstate = _LEX_ACCEPT;
                }
                break;
            default:
                _gt_typeanalysis._t_token = _TOKEN_INVALID;
                t_lexstate = _LEX_ACCEPT;
                assert(false);
                break;
        }
    }

    /* if token is identifier then check is keyword */
    if (_gt_typeanalysis._t_token == _TOKEN_IDENTIFIER) {
        while (_sgt_table[t_keyindex]._s_tokentext != NULL) {
            if (strncmp(_gt_typeanalysis._s_tokentext, _sgt_table[t_keyindex]._s_tokentext, _TYPE_NAME_SIZE) == 0) {
                _gt_typeanalysis._t_token = _sgt_table[t_keyindex]._t_token;
                return;
            }

            t_keyindex++;
        }
    }
}

/**
 * Rollback current token to input string.
 */
void _type_token_rollback(void)
{
    assert(_gt_typeanalysis._t_token == _TOKEN_END_OF_INPUT ||
           _gt_typeanalysis._t_token == _TOKEN_SIGN_COMMA ||
           _gt_typeanalysis._t_token == _TOKEN_SIGN_RIGHT_BRACKET);
    assert(_gt_typeanalysis._s_typename[_gt_typeanalysis._t_index] == _TOKEN_CHARACTER_END_OF_INPUT ||
           _gt_typeanalysis._s_typename[_gt_typeanalysis._t_index-1] == _TOKEN_CHARACTER_COMMA ||
           _gt_typeanalysis._s_typename[_gt_typeanalysis._t_index-1] == _TOKEN_CHARACTER_RIGHT_BRACKET);
    assert(strncmp(_gt_typeanalysis._s_tokentext, _TOKEN_TEXT_EMPTY, _TYPE_NAME_SIZE) == 0 ||
           strncmp(_gt_typeanalysis._s_tokentext, _TOKEN_TEXT_COMMA, _TYPE_NAME_SIZE) == 0 ||
           strncmp(_gt_typeanalysis._s_tokentext, _TOKEN_TEXT_RIGHT_BRACKET, _TYPE_NAME_SIZE) == 0);

    if (_gt_typeanalysis._s_typename[_gt_typeanalysis._t_index] != _TOKEN_CHARACTER_END_OF_INPUT) {
        _gt_typeanalysis._t_index--;
    } else if (_gt_typeanalysis._t_token == _TOKEN_SIGN_COMMA ||
               _gt_typeanalysis._t_token == _TOKEN_SIGN_RIGHT_BRACKET) {
        _gt_typeanalysis._t_index--;
    }
    _gt_typeanalysis._t_token = _TOKEN_ROLLBACK;
}

/**
 * Parse specific token, and get formal name.
 */
bool_t _type_parse_c_builtin(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* C_BUILTIN -> SIMPLE_BUILTIN | SIGNED_BUILTIN | UNSIGNED_BUILTIN | POINTER_BUILTIN */
    switch (_gt_typeanalysis._t_token) {
        /* C_BUILTIN -> SIMPLE_BUILTIN */
        case _TOKEN_KEY_CHAR:
        case _TOKEN_KEY_SHORT:
        case _TOKEN_KEY_INT:
        case _TOKEN_KEY_LONG:
        case _TOKEN_KEY_FLOAT:
        case _TOKEN_KEY_DOUBLE:
        case _TOKEN_KEY_CSTL_BOOL:
        case _TOKEN_KEY_BOOL:
            return _type_parse_simple_builtin(s_formalname);
            break;
        /* C_BUILTIN -> SIGNED_BUILTIN */
        case _TOKEN_KEY_SIGNED:
            return _type_parse_signed_builtin(s_formalname);
            break;
        /* C_BUILTIN -> UNSIGNED_BUILTIN */
        case _TOKEN_KEY_UNSIGNED:
            return _type_parse_unsigned_builtin(s_formalname);
            break;
        /* C_BUILTIN -> POINTER_BUILTIN */
        case _TOKEN_KEY_VOID:
            return _type_parse_pointer_builtin(s_formalname);
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_pointer_builtin(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* POINTER_BUILTIN -> void * */
    switch (_gt_typeanalysis._t_token) {
        case _TOKEN_KEY_VOID:
            _TOKEN_MATCH(_TOKEN_TEXT_VOID, s_formalname);
            _type_get_token();
            _TOKEN_MATCH(_TOKEN_TEXT_POINTER, s_formalname);
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_pointer_suffix(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* POINTER_SUFFIX -> * | $ */
    switch (_gt_typeanalysis._t_token) {
        /* POINTER_SUFFIX -> * */
        case _TOKEN_SIGN_POINTER:
            _TOKEN_MATCH(_TOKEN_TEXT_POINTER, s_formalname);
            return true;
            break;
        /* POINTER_SUFFIX -> $ */
        case _TOKEN_END_OF_INPUT:
        case _TOKEN_SIGN_RIGHT_BRACKET:
        case _TOKEN_SIGN_COMMA:
            _type_token_rollback();
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_common_suffix(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* COMMON_SUFFIX -> {+' '}int | $ */
    switch (_gt_typeanalysis._t_token) {
        /* COMMON_SUFFIX -> {+' '}int */
        case _TOKEN_KEY_INT:
            _TOKEN_MATCH_SPACE(s_formalname);
            _TOKEN_MATCH(_TOKEN_TEXT_INT, s_formalname);
            return true;
            break;
        /* COMMON_SUFFIX -> $ */
        case _TOKEN_END_OF_INPUT:
        case _TOKEN_SIGN_RIGHT_BRACKET:
        case _TOKEN_SIGN_COMMA:
            _type_token_rollback();
            return true;
            break;
        default:
            return false;
            break;
    }
}


bool_t _type_parse_complex_long_suffix(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* COMPLEX_LONG_SUFFIX -> {+' '}long COMMON_SUFFIX | COMMON_SUFFIX */
    switch (_gt_typeanalysis._t_token) {
        /* COMPLEX_LONG_SUFFIX -> {+' '}long COMMON_SUFFIX */
        case _TOKEN_KEY_LONG:
            _TOKEN_MATCH_SPACE(s_formalname);
            _TOKEN_MATCH(_TOKEN_TEXT_LONG, s_formalname);
            _type_get_token();
            return _type_parse_common_suffix(s_formalname);
            break;
        /* COMPLEX_LONG_SUFFIX -> COMMON_SUFFIX */
        case _TOKEN_KEY_INT:
        case _TOKEN_END_OF_INPUT:
        case _TOKEN_SIGN_RIGHT_BRACKET:
        case _TOKEN_SIGN_COMMA:
            return _type_parse_common_suffix(s_formalname);
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_simple_long_suffix(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* SIMPLE_LONG_SUFFIX -> {+' '}double | COMPLEX_LONG_SUFFIX */
    switch (_gt_typeanalysis._t_token) {
        /* SIMPLE_LONG_SUFFIX -> {+' '}double */
        case _TOKEN_KEY_DOUBLE:
            _TOKEN_MATCH_SPACE(s_formalname);
            _TOKEN_MATCH(_TOKEN_TEXT_DOUBLE, s_formalname);
            return true;
            break;
        /* SIMPLE_LONG_SUFFIX -> COMPLEX_LONG_SUFFIX */
        case _TOKEN_KEY_LONG:
        case _TOKEN_KEY_INT:
        case _TOKEN_END_OF_INPUT:
        case _TOKEN_SIGN_RIGHT_BRACKET:
        case _TOKEN_SIGN_COMMA:
            return _type_parse_complex_long_suffix(s_formalname);
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_simple_builtin(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* 
     * SIMPLE_BUILTIN -> char POINTER_SUFFIX | short COMMON_SUFFIX | int |
     *                   long SIMPLE_LONG_SUFFIX | float | double | bool_t | _Bool
     */
    switch (_gt_typeanalysis._t_token) {
        /* SIMPLE_BUILTIN -> char POINTER_SUFFIX */
        case _TOKEN_KEY_CHAR:
            _TOKEN_MATCH(_TOKEN_TEXT_CHAR, s_formalname);
            _type_get_token();
            return _type_parse_pointer_suffix(s_formalname);
            break;
        /* SIMPLE_BUILTIN -> short COMMON_SUFFIX */
        case _TOKEN_KEY_SHORT:
            _TOKEN_MATCH(_TOKEN_TEXT_SHORT, s_formalname);
            _type_get_token();
            return _type_parse_common_suffix(s_formalname);
            break;
        /* SIMPLE_BUILTIN -> int */
        case _TOKEN_KEY_INT:
            _TOKEN_MATCH(_TOKEN_TEXT_INT, s_formalname);
            return true;
            break;
        /* SIMPLE_BUILTIN -> long SIMPLE_LONG_SUFFIX */
        case _TOKEN_KEY_LONG:
            _TOKEN_MATCH(_TOKEN_TEXT_LONG, s_formalname);
            _type_get_token();
            return _type_parse_simple_long_suffix(s_formalname);
            break;
        /* SIMPLE_BUILTIN -> float */
        case _TOKEN_KEY_FLOAT:
            _TOKEN_MATCH(_TOKEN_TEXT_FLOAT, s_formalname);
            return true;
            break;
        /* SIMPLE_BUILTIN -> double */
        case _TOKEN_KEY_DOUBLE:
            _TOKEN_MATCH(_TOKEN_TEXT_DOUBLE, s_formalname);
            return true;
            break;
        /* SIMPLE_BUILTIN -> bool_t */
        case _TOKEN_KEY_CSTL_BOOL:
            _TOKEN_MATCH(_TOKEN_TEXT_CSTL_BOOL, s_formalname);
            return true;
            break;
        /* SIMPLE_BUILTIN -> _Bool */
        case _TOKEN_KEY_BOOL:
            _TOKEN_MATCH(_TOKEN_TEXT_BOOL, s_formalname);
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_unsigned_builtin(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* UNSIGNED_BUILTIN -> unsigned COMPLEX_SUFFIX */
    switch (_gt_typeanalysis._t_token) {
        case _TOKEN_KEY_UNSIGNED:
            _TOKEN_MATCH(_TOKEN_TEXT_UNSIGNED, s_formalname);
            _type_get_token();
            return _type_parse_complex_suffix(s_formalname);
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_complex_suffix(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* 
     * COMPLEX_SUFFIX -> {+' '}char | {+' '}short COMMON_SUFFIX |
     *                   {+' '}int | {+' '}long COMPLEX_LONG_SUFFIX | $
     */
    switch (_gt_typeanalysis._t_token) {
        /* COMPLEX_SUFFIX -> {+' '}char */
        case _TOKEN_KEY_CHAR:
            _TOKEN_MATCH_SPACE(s_formalname);
            _TOKEN_MATCH(_TOKEN_TEXT_CHAR, s_formalname);
            return true;
            break;
        /* COMPLEX_SUFFIX -> {+' '}short COMMON_SUFFIX */
        case _TOKEN_KEY_SHORT:
            _TOKEN_MATCH_SPACE(s_formalname);
            _TOKEN_MATCH(_TOKEN_TEXT_SHORT, s_formalname);
            _type_get_token();
            return _type_parse_common_suffix(s_formalname);
            break;
        /* COMPLEX_SUFFIX -> {+' '}int */
        case _TOKEN_KEY_INT:
            _TOKEN_MATCH_SPACE(s_formalname);
            _TOKEN_MATCH(_TOKEN_TEXT_INT, s_formalname);
            return true;
            break;
        /* COMPLEX_SUFFIX -> {+' '}long COMPLEX_LONG_SUFFIX */
        case _TOKEN_KEY_LONG:
            _TOKEN_MATCH_SPACE(s_formalname);
            _TOKEN_MATCH(_TOKEN_TEXT_LONG, s_formalname);
            _type_get_token();
            return _type_parse_complex_long_suffix(s_formalname);
            break;
        /* COMPLEX_SUFFIX -> $ */
        case _TOKEN_END_OF_INPUT:
        case _TOKEN_SIGN_RIGHT_BRACKET:
        case _TOKEN_SIGN_COMMA:
            _type_token_rollback();
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_signed_builtin(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* SIGNED_BUILTIN -> signed COMPLEX_SUFFIX */
    switch (_gt_typeanalysis._t_token) {
        case _TOKEN_KEY_SIGNED:
            _TOKEN_MATCH(_TOKEN_TEXT_SIGNED, s_formalname);
            _type_get_token();
            return _type_parse_complex_suffix(s_formalname);
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_user_define_type(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* USER_DEFINE_TYPE -> struct | enum | union */
    switch (_gt_typeanalysis._t_token) {
        case _TOKEN_KEY_STRUCT:
            _TOKEN_MATCH(_TOKEN_TEXT_STRUCT, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_ENUM:
            _TOKEN_MATCH(_TOKEN_TEXT_ENUM, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_UNION:
            _TOKEN_MATCH(_TOKEN_TEXT_UNION, s_formalname);
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_user_define(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* USER_DEFINE -> USER_DEFINE_TYPE {+' '}identifier | identifier */
    switch (_gt_typeanalysis._t_token) {
        /* USER_DEFINE -> USER_DEFINE_TYPE {+' '}identifier */
        case _TOKEN_KEY_STRUCT:
        case _TOKEN_KEY_ENUM:
        case _TOKEN_KEY_UNION:
            if (_type_parse_user_define_type(s_formalname)) {
                _TOKEN_MATCH_SPACE(s_formalname);
                _type_get_token();
                if (_gt_typeanalysis._t_token != _TOKEN_IDENTIFIER) {
                    return false;
                } else {
                    _TOKEN_MATCH_IDENTIFIER(s_formalname);
                    return true;
                }
            } else {
                return false;
            }
            break;
        /* USER_DEFINE -> identifier */
        case _TOKEN_IDENTIFIER:
            _TOKEN_MATCH_IDENTIFIER(s_formalname);
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_sequence_name(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* 
     * SEQUENCE_NAME -> vector_t | list_t | slist_t | deque_t | stack_t | 
     *                  queue_t | priority_queue_t | set_t | multiset_t |
     *                  hash_set_t | hash_multiset_t | basic_string_t
     */
    switch (_gt_typeanalysis._t_token) {
        case _TOKEN_KEY_VECTOR:
            _TOKEN_MATCH(_TOKEN_TEXT_VECTOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_LIST:
            _TOKEN_MATCH(_TOKEN_TEXT_LIST, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_SLIST:
            _TOKEN_MATCH(_TOKEN_TEXT_SLIST, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_DEQUE:
            _TOKEN_MATCH(_TOKEN_TEXT_DEQUE, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_STACK:
            _TOKEN_MATCH(_TOKEN_TEXT_STACK, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_QUEUE:
            _TOKEN_MATCH(_TOKEN_TEXT_QUEUE, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_PRIORITY_QUEUE:
            _TOKEN_MATCH(_TOKEN_TEXT_PRIORITY_QUEUE, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_SET:
            _TOKEN_MATCH(_TOKEN_TEXT_SET, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_MULTISET:
            _TOKEN_MATCH(_TOKEN_TEXT_MULTISET, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_HASH_SET:
            _TOKEN_MATCH(_TOKEN_TEXT_HASH_SET, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_HASH_MULTISET:
            _TOKEN_MATCH(_TOKEN_TEXT_HASH_MULTISET, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_BASIC_STRING:
            _TOKEN_MATCH(_TOKEN_TEXT_BASIC_STRING, s_formalname);
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_sequence(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* SEQUENCE -> SEQUENCE_NAME < TYPE_DESCRIPT > */
    if (_type_parse_sequence_name(s_formalname)) {
        /* < */
        _type_get_token();
        if (_gt_typeanalysis._t_token != _TOKEN_SIGN_LEFT_BRACKET) {
            return false;
        }
        _TOKEN_MATCH(_TOKEN_TEXT_LEFT_BRACKET, s_formalname);
        /* TYPE_DESCRIPT */
        _type_get_token();
        if (!_type_parse_type_descript(s_formalname)) {
            return false;
        }
        /* > */
        _type_get_token();
        if (_gt_typeanalysis._t_token != _TOKEN_SIGN_RIGHT_BRACKET) {
            return false;
        }
        _TOKEN_MATCH(_TOKEN_TEXT_RIGHT_BRACKET, s_formalname);
        return true;
    } else {
        return false;
    }
}

bool_t _type_parse_relation_name(char* s_formalname)
{
    assert(s_formalname != NULL);
    /*
     * RELATION_NAME -> map_t | multimap_t | hash_map_t | hash_multimap_t | pair_t
     */
    switch (_gt_typeanalysis._t_token) {
        case _TOKEN_KEY_MAP:
            _TOKEN_MATCH(_TOKEN_TEXT_MAP, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_MULTIMAP:
            _TOKEN_MATCH(_TOKEN_TEXT_MULTIMAP, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_HASH_MAP:
            _TOKEN_MATCH(_TOKEN_TEXT_HASH_MAP, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_HASH_MULTIMAP:
            _TOKEN_MATCH(_TOKEN_TEXT_HASH_MULTIMAP, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_PAIR:
            _TOKEN_MATCH(_TOKEN_TEXT_PAIR, s_formalname);
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_iterator(char* s_formalname)
{
    assert(s_formalname != NULL);
    /*
     * ITERATOR -> iterator_t | vector_iterator_t | list_iterator_t | slist_iterator_t |
     *             deque_iterator_t | set_iterator_t | map_iterator_t | multiset_iterator_t |
     *             multimap_iterator_t | hash_set_iterator_t | hash_map_iterator_t |
     *             hash_multiset_iterator_t | hash_multimap_iterator_t |
     *             string_iterator_t | input_iterator_t | output_iterator_t | forward_iterator_t |
     *             bidirectional_iterator_t | random_access_iterator_t | basic_string_iterator_t
     */
    switch (_gt_typeanalysis._t_token) {
        case _TOKEN_KEY_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_VECTOR_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_VECTOR_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_LIST_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_LIST_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_SLIST_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_SLIST_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_DEQUE_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_DEQUE_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_SET_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_SET_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_MAP_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_MAP_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_MULTISET_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_MULTISET_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_MULTIMAP_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_MULTIMAP_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_HASH_SET_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_HASH_SET_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_HASH_MAP_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_HASH_MAP_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_HASH_MULTISET_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_HASH_MULTISET_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_HASH_MULTIMAP_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_HASH_MULTIMAP_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_STRING_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_STRING_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_INPUT_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_INPUT_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_OUTPUT_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_OUTPUT_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_FORWARD_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_FORWARD_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_BIDIRECTIONAL_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_BIDIRECTIONAL_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_RANDOM_ACCESS_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_RANDOM_ACCESS_ITERATOR, s_formalname);
            return true;
            break;
        case _TOKEN_KEY_BASIC_STRING_ITERATOR:
            _TOKEN_MATCH(_TOKEN_TEXT_BASIC_STRING_ITERATOR, s_formalname);
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_relation(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* RELATION -> RELATION_NAME < TYPE_DESCRIPT, TYPE_DESCRIPT > */
    if (_type_parse_relation_name(s_formalname)) {
        /* < */
        _type_get_token();
        if (_gt_typeanalysis._t_token != _TOKEN_SIGN_LEFT_BRACKET) {
            return false;
        }
        _TOKEN_MATCH(_TOKEN_TEXT_LEFT_BRACKET, s_formalname);
        /* TYPE_DESCRIPT */
        _type_get_token();
        if (!_type_parse_type_descript(s_formalname)) {
            return false;
        }
        /* , */
        _type_get_token();
        if (_gt_typeanalysis._t_token != _TOKEN_SIGN_COMMA) {
            return false;
        }
        _TOKEN_MATCH(_TOKEN_TEXT_COMMA, s_formalname);
        /* TYPE_DESCRIPT */
        _type_get_token();
        if (!_type_parse_type_descript(s_formalname)) {
            return false;
        }
        /* > */
        _type_get_token();
        if (_gt_typeanalysis._t_token != _TOKEN_SIGN_RIGHT_BRACKET) {
            return false;
        }
        _TOKEN_MATCH(_TOKEN_TEXT_RIGHT_BRACKET, s_formalname);
        return true;
    } else {
        return false;
    }
}

bool_t _type_parse_cstl_builtin(char* s_formalname)
{
    assert(s_formalname != NULL);
    /* CSTL_BUILTIN -> SEQUENCE | RELATION | string_t | range_t | ITERATOR */
    switch (_gt_typeanalysis._t_token) {
        /* CSTL_BUILTIN -> SEQUENCE */
        case _TOKEN_KEY_VECTOR:
        case _TOKEN_KEY_LIST:
        case _TOKEN_KEY_SLIST:
        case _TOKEN_KEY_DEQUE:
        case _TOKEN_KEY_STACK:
        case _TOKEN_KEY_QUEUE:
        case _TOKEN_KEY_PRIORITY_QUEUE:
        case _TOKEN_KEY_SET:
        case _TOKEN_KEY_MULTISET:
        case _TOKEN_KEY_HASH_SET:
        case _TOKEN_KEY_HASH_MULTISET:
        case _TOKEN_KEY_BASIC_STRING:
            return _type_parse_sequence(s_formalname);
            break;
        /* CSTL_BUILTIN -> RELATION */
        case _TOKEN_KEY_MAP:
        case _TOKEN_KEY_MULTIMAP:
        case _TOKEN_KEY_HASH_MAP:
        case _TOKEN_KEY_HASH_MULTIMAP:
        case _TOKEN_KEY_PAIR:
            return _type_parse_relation(s_formalname);
            break;
        /* CSTL_BUILTIN -> string_t */
        case _TOKEN_KEY_STRING:
            _TOKEN_MATCH(_TOKEN_TEXT_STRING, s_formalname);
            return true;
            break;
        /* CSTL_BUILTIN -> range_t */
        case _TOKEN_KEY_RANGE:
            _TOKEN_MATCH(_TOKEN_TEXT_RANGE, s_formalname);
            return true;
            break;
        /* CSTL_BUILTIN -> ITERATOR */
        case _TOKEN_KEY_ITERATOR:
        case _TOKEN_KEY_VECTOR_ITERATOR:
        case _TOKEN_KEY_LIST_ITERATOR:
        case _TOKEN_KEY_SLIST_ITERATOR:
        case _TOKEN_KEY_DEQUE_ITERATOR:
        case _TOKEN_KEY_SET_ITERATOR:
        case _TOKEN_KEY_MAP_ITERATOR:
        case _TOKEN_KEY_MULTISET_ITERATOR:
        case _TOKEN_KEY_MULTIMAP_ITERATOR:
        case _TOKEN_KEY_HASH_SET_ITERATOR:
        case _TOKEN_KEY_HASH_MAP_ITERATOR:
        case _TOKEN_KEY_HASH_MULTISET_ITERATOR:
        case _TOKEN_KEY_HASH_MULTIMAP_ITERATOR:
        case _TOKEN_KEY_STRING_ITERATOR:
        case _TOKEN_KEY_INPUT_ITERATOR:
        case _TOKEN_KEY_OUTPUT_ITERATOR:
        case _TOKEN_KEY_FORWARD_ITERATOR:
        case _TOKEN_KEY_BIDIRECTIONAL_ITERATOR:
        case _TOKEN_KEY_RANDOM_ACCESS_ITERATOR:
        case _TOKEN_KEY_BASIC_STRING_ITERATOR:
            return _type_parse_iterator(s_formalname);
            break;
        default:
            return false;
            break;
    }
}

bool_t _type_parse_type_descript(char* s_formalname)
{
    char   s_userdefine[_TYPE_NAME_SIZE + 1];

    memset(s_userdefine, '\0', _TYPE_NAME_SIZE+1);

    assert(s_formalname != NULL);
    /* TYPE_DESCRIPT -> C_BUILTIN | USER_DEFINE | CSTL_BUILTIN */
    switch (_gt_typeanalysis._t_token) {
        /* TYPE_DESCRIPT -> C_BUILTIN */
        case _TOKEN_KEY_CHAR:
        case _TOKEN_KEY_SHORT:
        case _TOKEN_KEY_INT:
        case _TOKEN_KEY_LONG:
        case _TOKEN_KEY_FLOAT:
        case _TOKEN_KEY_DOUBLE:
        case _TOKEN_KEY_SIGNED:
        case _TOKEN_KEY_UNSIGNED:
        case _TOKEN_KEY_VOID:
        case _TOKEN_KEY_CSTL_BOOL:
        case _TOKEN_KEY_BOOL:
            return _type_parse_c_builtin(s_formalname);
            break;
        /* TYPE_DESCRIPT -> USER_DEFINE */
        case _TOKEN_KEY_STRUCT:
        case _TOKEN_KEY_ENUM:
        case _TOKEN_KEY_UNION:
        case _TOKEN_IDENTIFIER:
            if (_type_parse_user_define(s_userdefine)) {
                strncat(s_formalname, s_userdefine, _TYPE_NAME_SIZE);
                return _type_is_registered(s_userdefine) != NULL ? true : false;
            } else {
                return false;
            }
            break;
        /* TYPE_DESCRIPT -> CSTL_BUILTIN */
        case _TOKEN_KEY_VECTOR:
        case _TOKEN_KEY_LIST:
        case _TOKEN_KEY_SLIST:
        case _TOKEN_KEY_DEQUE:
        case _TOKEN_KEY_STACK:
        case _TOKEN_KEY_QUEUE:
        case _TOKEN_KEY_PRIORITY_QUEUE:
        case _TOKEN_KEY_SET:
        case _TOKEN_KEY_MAP:
        case _TOKEN_KEY_MULTISET:
        case _TOKEN_KEY_MULTIMAP:
        case _TOKEN_KEY_HASH_SET:
        case _TOKEN_KEY_HASH_MAP:
        case _TOKEN_KEY_HASH_MULTISET:
        case _TOKEN_KEY_HASH_MULTIMAP:
        case _TOKEN_KEY_PAIR:
        case _TOKEN_KEY_STRING:
        case _TOKEN_KEY_RANGE:
        case _TOKEN_KEY_BASIC_STRING:
        case _TOKEN_KEY_ITERATOR:
        case _TOKEN_KEY_VECTOR_ITERATOR:
        case _TOKEN_KEY_LIST_ITERATOR:
        case _TOKEN_KEY_SLIST_ITERATOR:
        case _TOKEN_KEY_DEQUE_ITERATOR:
        case _TOKEN_KEY_SET_ITERATOR:
        case _TOKEN_KEY_MAP_ITERATOR:
        case _TOKEN_KEY_MULTISET_ITERATOR:
        case _TOKEN_KEY_MULTIMAP_ITERATOR:
        case _TOKEN_KEY_HASH_SET_ITERATOR:
        case _TOKEN_KEY_HASH_MAP_ITERATOR:
        case _TOKEN_KEY_HASH_MULTISET_ITERATOR:
        case _TOKEN_KEY_HASH_MULTIMAP_ITERATOR:
        case _TOKEN_KEY_STRING_ITERATOR:
        case _TOKEN_KEY_INPUT_ITERATOR:
        case _TOKEN_KEY_OUTPUT_ITERATOR:
        case _TOKEN_KEY_FORWARD_ITERATOR:
        case _TOKEN_KEY_BIDIRECTIONAL_ITERATOR:
        case _TOKEN_KEY_RANDOM_ACCESS_ITERATOR:
        case _TOKEN_KEY_BASIC_STRING_ITERATOR:
            return _type_parse_cstl_builtin(s_formalname);
            break;
        default:
            return false;
            break;
    }
}

/** eof **/

