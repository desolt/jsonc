#include <stdlib.h>
#include <stdio.h>
#include <jsonc/json.h>

int main(void)
{
    json_object_t *jake = init_json_object();

    json_value_t *jake_name = json_value_str("Jake");
    json_array_t *arr_schools = init_json_array();
    json_array_add(arr_schools, json_value_str("Foo Elementary"));
    json_array_add(arr_schools, json_value_str("Bar High School"));

    json_object_put(jake, "name", jake_name);
    json_object_put(jake, "schools", json_value_arr(arr_schools));

    json_object_t *friend = init_json_object();
    json_object_put(friend, "name", json_value_str("Sam"));

    json_array_t *friends = init_json_array();
    json_array_add(friends, json_value_obj(friend));
    json_object_put(jake, "friends", json_value_arr(friends));

    char buffer[1024];
    json_object_to_str(jake, buffer);
    printf("%s\n", buffer);

    free_json_object(jake);
    return EXIT_SUCCESS;
}
