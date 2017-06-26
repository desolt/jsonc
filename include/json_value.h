#ifndef JSONC_JSON_VALUE_H_
#define JSONC_JSON_VALUE_H_

#include "json.h"

#include <stdint.h>
#include <string.h>

typedef enum {
    json_int = 0,
    json_float = 1,
    json_str = 2,
    json_bool = 3,
    json_arr = 4,
    json_obj = 5,
    json_null = 6
} value_type;

struct json_value {
    value_type val_type;

    int int_val;
    float float_val;
    char *str_val;
    uint8_t bool_val;
    json_object_t *obj_val;
    json_array_t *arr_val;
};

json_value_t *create_json_value();
// JSON values automatically free their values. They will try to act self-containing.
void free_json_value(json_value_t *val);

json_value_t *json_value_str(const char *str);
json_value_t *json_value_int(int num);
json_value_t *json_value_float(float num);
json_value_t *json_value_obj(json_object_t *obj);
json_value_t *json_value_arr(json_array_t *arr);

/* len is set to the number of characters in the string buffer */
int json_value_to_str(json_value_t *val, char *buffer);

#endif // JSONC_JSON_VALUE_H_
