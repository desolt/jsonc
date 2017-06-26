#include <stdlib.h>
#include <stdio.h>
#include <jsonc/json.h>
#include <jsonc/parser.h>

int main(void)
{
    char *strbuf1 = parse_str("\"he\\\"llo\" there", NULL);
    printf("%s\n", strbuf1);
    free(strbuf1);

    float fnum; int inum;
    value_type vt = parse_num("5325, \"name\": \"test\"}", &inum, &fnum, NULL);

    if (vt == json_int) {
        printf("%d\n", inum);
    } else if (vt == json_float) {
        printf("%f\n", fnum);
    }

    json_value_t *val = json_gets("{\"test\": \"Hello, world!\", \"test_num\": 53, \"test_obj\": {\"word\": \"testing!\"}, \"friends\": [\"Bob\", \"Jim\", \"Foo\"]}");
    json_value_t *val_arr =  json_gets("[\"test1\", \"test2\", \"test3\"]");
    if (val_arr != NULL) {
        printf("%d\n", val_arr->val_type);
        for (size_t i = 0; i < val_arr->arr_val->size; i++) {
            printf("%s\n", json_array_get(val_arr->arr_val, i)->str_val);
        }
    }

    if (val != NULL) {
        json_value_t *test = json_object_get(val->obj_val, "test");
        printf("%s\n", test->str_val);
        json_value_t *test_num = json_object_get(val->obj_val, "test_num");
        printf("%d\n", test_num->int_val);
        json_value_t *word = json_object_get(json_object_get(val->obj_val, "test_obj")->obj_val, "word");
        printf("%s\n", word->str_val);

        
        json_value_t *friends = json_object_get(val->obj_val, "friends");
        if (friends != NULL) {
            printf("%d\n", friends->val_type);
            for (size_t i = 0; i < friends->arr_val->size; i++) {
                printf("%s\n", json_array_get(friends->arr_val, i)->str_val);
            }
        } else {
            printf("null!\n");
        }
    }

    free_json_value(val_arr);
    free_json_value(val);

    return EXIT_SUCCESS;
}
