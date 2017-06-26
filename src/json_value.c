#include "json.h"
#include <stdlib.h>
#include <stdio.h>

// Defaults to null.
json_value_t *create_json_value()
{
    json_value_t *val = malloc(sizeof(json_value_t));
    if (val == NULL) {
        return NULL;
    }
    val->val_type = json_null;

    return val;
}

void free_json_value(json_value_t *val)
{
    switch (val->val_type) {
        case json_str:
            free(val->str_val);
            break;
        case json_obj:
            free_json_object(val->obj_val);
        case json_arr:
            free_json_array(val->arr_val);
        default:
            break;
    }

    free(val);
}

json_value_t *json_value_str(const char *str)
{
    json_value_t *val = malloc(sizeof(json_value_t));
    if (val == NULL) return NULL;

    val->val_type = json_str;
    val->str_val = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(val->str_val, str);

    return val;
}

json_value_t *json_value_int(int num) {
    json_value_t *val = malloc(sizeof(json_value_t));
    if (val == NULL) return NULL;

    val->val_type = json_int;
    val->int_val = num;

    return val;
}

json_value_t *json_value_float(float num) {
    json_value_t *val = malloc(sizeof(json_value_t));
    if (val == NULL) return NULL;

    val->val_type = json_float;
    val->float_val = num;

    return val;
}

json_value_t *json_value_obj(json_object_t *obj)
{
    json_value_t *val = malloc(sizeof(json_value_t));
    if (val == NULL) return NULL;

    val->val_type = json_obj;
    val->obj_val = obj;

    return val;
}

json_value_t *json_value_arr(json_array_t *arr)
{
    json_value_t *val = malloc(sizeof(json_value_t));
    if (val == NULL) return NULL;

    val->val_type = json_arr;
    val->arr_val = arr;

    return val;
}

int json_value_to_str(json_value_t *val, char *buffer)
{
    switch (val->val_type) {
    case json_int:
        sprintf(buffer, "%d", val->int_val);
        break;
    case json_float:
        sprintf(buffer, "%g", val->float_val);
        break;
    case json_str:
        sprintf(buffer, "\"%s\"", val->str_val);
        break;
    case json_bool:
        strcpy(buffer, val->bool_val ? "true" : "false");
        break;
    case json_arr:
        json_array_to_str(val->arr_val, buffer);
        break;
    case json_obj:
        json_object_to_str(val->obj_val, buffer);
        break;
    case json_null:
    default:
        strcpy(buffer, "null");
    }

    return !0;
}
