#include <stdlib.h>
#include <stdio.h>
#include <jsonc/json_value.h>

int main(void)
{
    json_value_t *val = json_value_str("Hello, world!");

    char buffer[64];
    json_value_to_str(val, buffer);
    // Assumes value is a string.
    printf("Value info - type: %d, content: %s\n", val->val_type, buffer);

    free_json_value(val);
    return EXIT_SUCCESS;
}
