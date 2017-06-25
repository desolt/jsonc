#include "json_value.h"
#include <stdlib.h>
#include <string.h>

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
        // TODO: Free JSON object or array when implemented.
        case json_obj:
        case json_arr:
        default:
            break;
    }

    free(val);
}

json_value_t *json_value_str(const char *str)
{
    json_value_t *val = malloc(sizeof(json_value_t));
    if (val == NULL) {
        return NULL;
    }

    val->val_type = json_str;
    val->str_val = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(val->str_val, str);

    return val;
}

json_value_t *json_value_int(int num) {
    return json_value_float((float) num);
}

json_value_t *json_value_float(float num) {
    json_value_t *val = malloc(sizeof(json_value_t));
    if (val == NULL) {
        return NULL;
    }

    val->val_type = json_num;
    val->num_val = num;

    return val;
}
