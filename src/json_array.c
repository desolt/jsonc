#include "json.h"
#include <stdlib.h>
#include <string.h>

json_array_t *init_json_array()
{
    json_array_t *arr = malloc(sizeof(json_array_t));
    if (arr == NULL) free(arr);

    arr->capacity = 10;
    arr->size = 0;
    arr->values = calloc(arr->capacity, sizeof(json_value_t *));
    if (arr->values == NULL) {
        free(arr);
        return NULL;
    }

    return arr;
}

void free_json_array(json_array_t *arr)
{
    if (arr == NULL) return;

    for (size_t i = 0; i < arr->size; i++) {
        if (arr->values[i] != NULL) free_json_value(arr->values[i]);
    }

    free(arr->values);
    free(arr);
}

int json_array_resize(json_array_t *arr, size_t capacity)
{
    size_t old_capacity = arr->capacity;
    json_value_t **tmp_ptr = realloc(arr->values, capacity * sizeof(json_value_t *));
    if (tmp_ptr == NULL) return 0;
    arr->values = tmp_ptr;
    arr->capacity = capacity;

    if (capacity > old_capacity) {
        tmp_ptr = memset(tmp_ptr + (old_capacity * sizeof(json_value_t *)), 0, (capacity - old_capacity) * sizeof(json_value_t *));
        if (tmp_ptr == NULL) {
            return 0;
        }
    }

    return !0;
}

int json_array_add(json_array_t *arr, json_value_t *val)
{
    if (arr->size <= arr->capacity) {
        int success = json_array_resize(arr, arr->capacity + 3);
        if (!success) {
            return success;
        }

        arr->capacity += 3;
    }

    arr->values[arr->size++] = val;
    return !0;
}

json_value_t *json_array_get(json_array_t *arr, size_t index)
{
    if (index >= arr->size) {
        return NULL;
    }

    return arr->values[index];
}

int json_array_set(json_array_t *arr, size_t index, json_value_t *val)
{
    if (index >= arr->size) {
        return 0;
    }

    free_json_value(arr->values[index]);
    arr->values[index] = val;
    return !0;
}

int json_array_remove(json_array_t *arr, size_t index)
{
    if (index >= arr->size) {
        return 0;
    }

    free_json_value(arr->values[index]);
    memmove(&(arr->values[index]), &(arr->values[index + 1]), sizeof(json_array_t *) * (arr->size - index));
    arr->size--;

    return !0;
}

int json_array_add_at(json_array_t *arr, size_t index, json_value_t *val)
{
    if (arr->size <= arr->capacity) {
        int success = json_array_resize(arr, arr->capacity + 3);
        if (!success) {
            return success;
        }

        arr->capacity += 3;
    }

    memmove(&(arr->values[index + 1]), &(arr->values[index]), (arr->size - index) * sizeof(val));
    arr->values[index] = val;
    arr->size++;
    return !0;
}

int json_array_to_str(json_array_t *arr, char *buffer)
{
    *buffer++ = '[';
    for (size_t i = 0; i < arr->size; i++) {
        json_value_t *val = arr->values[i];
        int success = json_value_to_str(val, buffer);
        if (!success) return success;
        buffer += strlen(buffer);
        if (i + 1 < arr->size) {
            *buffer++ = ',';
        }
    }

    *buffer++ = ']';
    *buffer = '\0';

    return !0;
}
