#ifndef JSONC_PARSER_H_
#define JSONC_PARSER_H_

#include "json.h"

char *parse_str(const char *src, size_t *len);
value_type parse_num(const char *src, int *out_int, float *out_float, size_t *len);

json_object_t *parse_json_obj(const char *src, const char **ptr);
json_array_t *parse_json_arr(const char *src, const char **ptr);
json_value_t *json_gets(const char *src);

#endif // JSONC_PARSER_H_
