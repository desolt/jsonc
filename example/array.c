#include <stdlib.h>
#include <stdio.h>
#include <jsonc/json.h>

void print_arr(json_array_t *arr)
{
    char buffer[1024];
    json_array_to_str(arr, buffer);
    printf("%s\n", buffer);
}

int main(void)
{
    json_array_t *arr1 = init_json_array();

    json_array_add(arr1, json_value_str("hello"));
    json_array_add(arr1, json_value_str("world"));

    for (size_t i = 0; i < arr1->size; i++) {
        json_value_t *val = json_array_get(arr1, i);
        if (val->val_type == json_str) {
            printf("%s\n", val->str_val);
        }
    }

    print_arr(arr1);
    free_json_array(arr1);

    json_array_t *arr2 = init_json_array();

    for (size_t i = 0; i < 15; i++) {
        json_array_add(arr2, json_value_int(i));
    }

    print_arr(arr2);
    json_array_remove(arr2, 12);
    print_arr(arr2);
    json_array_set(arr2, 4, json_value_str("Test!"));
    print_arr(arr2);

    free_json_array(arr2);
    return EXIT_SUCCESS;
}
