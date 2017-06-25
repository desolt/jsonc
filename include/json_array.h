#ifndef JSONC_JSON_ARRAY_H_
#define JSONC_JSON_ARRAY_H_

#include "json_value.h"
#include <stddef.h>

typedef struct json_array {
    json_value_t **values;

    size_t capacity, size;
} json_array_t;

json_array_t *init_json_array();
void free_json_array(json_array_t *arr);

int json_array_add(json_array_t *arr, json_value_t *val);
json_value_t *json_array_get(json_array_t *arr, size_t index);

#endif // JSONC_JSON_ARRAY_H_
