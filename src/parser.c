#include "parser.h"
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

char *parse_str(const char *src, size_t *len)
{
    while (*src == ' ') ++src;
    if (*src != '"') return NULL;

    char *str_end = strchr(++src, '"');
    while (str_end != NULL) {
        if (*(str_end - 1) != '\\') {
            break;
        }

        str_end = strchr(str_end + 1, '"');
    }

    if (str_end == NULL) return NULL;

    size_t length = str_end - src;
    if (len != NULL) *len = length + 1;

    char *buffer = malloc(sizeof(char) * (length + 1));
    for (size_t i = 0; i < length; i++) {
        buffer[i] = src[i];
    }
    buffer[length] = '\0';

    return buffer;
}

value_type parse_num(const char *src, int *out_int, float *out_float, size_t *length)
{
    while (*src == ' ') ++src;

    if (!isdigit(*src) && *src != '.') return json_null;

    char *end = strchr(src, ',');
    char *end_arr = strchr(src, ']');
    if (end_arr != NULL && (end == NULL || end_arr < end)) end = end_arr;
    char *end_obj = strchr(src, '}');
    if (end_obj != NULL && (end == NULL || end_obj < end)) end = end_obj;

    size_t len = 0;
    if (end == NULL) {
        len = strlen(src);
    } else {
        len = end - src;
    }

    if (length != NULL) *length = len;

    char buffer[len + 1];
    buffer[len] = '\0';

    for (size_t i = 0; i < len; i++) {
        buffer[i] = src[i];
    }

    if (strchr(buffer, '.') != NULL) {
        float num = strtof(src, NULL);
        if (errno) return json_null;

        if (out_float != NULL) *out_float = num;
        return json_float;
    } else {
        int num = strtold(src, NULL);
        if (errno) return json_null;

        if (out_int != NULL) *out_int = num;
        return json_int;
    }

    return json_null;
}

json_value_t *parse_val(const char *src, const char **ptr)
{
    json_value_t *val = malloc(sizeof(json_value_t));

    while (*src == ' ') ++src; // Ignore whitespace

    char c = *src;
    if (c == '{') {
        val->val_type = json_obj;
        val->obj_val = parse_json_obj(src, &src);

        if (val->obj_val == NULL) {
            free(val);
            return NULL;
        }

        if (src + 1 != NULL) ++src;
    } else if (c == '[') {
        val->val_type = json_arr;
        val->arr_val = parse_json_arr(src, &src);

        if (val->arr_val == NULL) {
            free(val);
            return NULL;
        }
    } else if (isdigit(c) || c == '.') {
        float fnum;
        int inum;

        size_t len;
        value_type vt = parse_num(src, &inum, &fnum, &len);
        if (vt == json_null) {
            free(val);
            return NULL;
        } else if (vt == json_float) {
            val->float_val = fnum;
        } else {
            val->int_val = inum;
        }

        val->val_type = vt;

        src += len;
    } else if (c == '"') {
        val->val_type = json_str;
        size_t len;
        val->str_val = parse_str(src, &len);
        if (val->str_val == NULL) {
            free(val);
            return NULL;
        }

        src += len + 1;
    } else if (isalpha(c)) {
        if (!strcmp(src, "null")) {
            val->val_type = json_null;
        } else {
            free(val);
            return NULL;
        }
    }

    if (ptr != NULL) *ptr = src;

    return val;

}

json_object_t *parse_json_obj(const char *src, const char **ptr)
{
    while (*src == ' ') ++src;
    if (*src != '{') return NULL;
    ++src;

    json_object_t *obj = init_json_object();

    while (src != NULL) {
        if (*src == '"') {
            size_t key_len;
            char *key = parse_str(src, &key_len);
            if (key == NULL) {
                free_json_object(obj);
                return NULL;
            }

            src += key_len + 1; // Includes end quotation mark

            while (*src == ' ') ++src;

            if (*src != ':') {
                free_json_object(obj);
                return NULL;
            }

            ++src;
            while (*src == ' ') ++src;

            json_value_t *val = parse_val(src, &src);
            if (val == NULL) {
                free_json_object(obj);
                return NULL;
            }

            json_object_put(obj, key, val);
            continue;
        } else if (*src == '}') {
            break;
        }

        ++src;
    }

    if (ptr != NULL) {
        *ptr = src;
    }

    return obj;
}

json_array_t *parse_json_arr(const char *src, const char **ptr)
{
    while (*src == ' ') ++src;
    if (*src != '[') return NULL;
    ++src;

    json_array_t *arr = init_json_array();
    while (src != NULL) {
        while (*src == ' ') ++src;

        if (*src == ']') {
            break;
        } else if (*src == '"' || *src == '.' || *src == '{' || *src == '[' || isdigit(*src)) {
            json_value_t *val = parse_val(src, &src);
            if (val == NULL) {
                free_json_array(arr);
                return NULL;
            }

            json_array_add(arr, val);
            continue;
        }

        ++src;
    }

    if (ptr != NULL) *ptr = src;
    return arr;
}

json_value_t *json_gets(const char *src)
{
    return parse_val(src, NULL);
}
