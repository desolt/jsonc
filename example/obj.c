#include <stdlib.h>
#include <stdio.h>
#include <jsonc/json_object.h>
#include <jsonc/json_value.h>

int main(void)
{
    json_object_t *obj = init_json_object();
    json_value_t *test = json_value_str("this is a test");
    json_value_t *testnum = json_value_int(3);
    json_value_t *testfloat = json_value_float(3.145);

    json_object_put(obj, "test", test);
    json_object_put(obj, "testnum", testnum);
    json_object_put(obj, "testfloat", testfloat);

    /**
    struct json_val_node *node = obj->node;
    while (node != NULL) {
        printf("Key: %s, Value type: %d\n", node->key, node->val->val_type);
        node = node->next;
    }
    */

    char buffer[2048];
    json_object_to_str(obj, buffer);
    printf("%s\n", buffer);

    free_json_object(obj);
    return EXIT_SUCCESS;
}
