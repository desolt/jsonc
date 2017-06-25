#include "json.h"
#include <stdlib.h>
#include <string.h>

json_object_t *init_json_object()
{
    json_object_t *obj = malloc(sizeof(json_object_t));
    if (obj == NULL) {
        return NULL;
    }

    return obj;
}

void free_json_node(struct json_val_node *node)
{
    free(node->key);
    free_json_value(node->val);
    free(node);
}

void free_json_object(json_object_t *obj)
{
    struct json_val_node *node = obj->node;
    if (node != NULL) {
        while (node->next != NULL) {
            node = node->next;
        }

        while (node->prev != NULL) {
            node = node->prev;
            free_json_node(node->next);
        }
    }

    if (node != NULL) {
        free_json_node(node);
    }

    free(obj);
}

void json_object_put(json_object_t *obj, const char *key, json_value_t *val)
{
    struct json_val_node **node = &(obj->node);
    while (*node != NULL) {
        if (!strcmp(key, (*node)->key)) {
            break;
        }

        node = &((*node)->next);
    }

    if (*node == NULL) {
        *node = malloc(sizeof(struct json_val_node));
        (*node)->key = malloc(strlen(key) + 1);
        strcpy((*node)->key, key);
    }

    (*node)->val = val;
}

json_value_t *json_object_get(json_object_t *obj, const char *key) {
    struct json_val_node *node = obj->node;

    while (node != NULL) {
        if (!strcmp(key, node->key)) {
            break;
        }

        node = node->next;
    }

    if (node == NULL) {
        return NULL;
    }

    return node->val;
}
