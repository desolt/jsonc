#ifndef JSONC_JSON_ARRAY_H_
#define JSONC_JSON_ARRAY_H_

#include "json.h"
#include <stddef.h>

struct json_array {
    json_value_t **values;

    size_t capacity, size;
};

json_array_t *init_json_array();
void free_json_array(json_array_t *arr);

int json_array_add(json_array_t *arr, json_value_t *val);
json_value_t *json_array_get(json_array_t *arr, size_t index);
int json_array_set(json_array_t *arr, size_t index, json_value_t *val);
int json_array_remove(json_array_t *arr, size_t index);

int json_array_to_str(json_array_t *arr, char *buffer);

#endif // JSONC_JSON_ARRAY_H_
