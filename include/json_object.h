#ifndef JSONC_JSON_OBJECT_H_
#define JSONC_JSON_OBJECT_H_

typedef struct json_value json_value_t;

struct json_val_node {
    char *key;
    json_value_t *val;

    struct json_val_node *next, *prev;
};

typedef struct json_object {
    struct json_val_node *node;
} json_object_t;

json_object_t *init_json_object();
void free_json_object(json_object_t *obj);

void json_object_put(json_object_t *obj, const char *key, json_value_t *val);
json_value_t *json_object_get(json_object_t *obj, const char *key);

#endif // JSONC_JSON_OBJECT_H_
