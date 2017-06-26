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

    json_value_t *val = json_gets("{\"test\": \"Hello, world!\", \"test_num\": 53, \"test_obj\": {\"word\": \"testing!\"}}");
    if (val != NULL) {
        json_value_t *test = json_object_get(val->obj_val, "test");
        printf("%s\n", test->str_val);
    }

    return EXIT_SUCCESS;
}
