# jsonc

jsonc is a small library that parses and works with json. There are many libraries available, many that likely implement json better than this one, however this project is good practice.

## Using jsonc

### Parsing

```c
// parsing_example.c
#include <stdlib.h>
#include <stdio.h>
#include <jsonc/json.h>
#include <jsonc/parser.h>

int main(void)
{
    json_value_t *val = json_gets("{\"word\": \"example\"}");
    if (val == NULL) {
        return EXIT_FAILURE;
    }

    if (val->val_type == json_obj) {
        json_value_t *word = json_object_get(val->obj_val, "word");
        if (word != NULL && word->val_type == json_str) {
            printf("the word is %s\n", word->str_val);
        }
    }

    free_json_value(val);
    return EXIT_SUCCESS;
}
```

    $ gcc parsing_example.c -ljsonc
    $ ./a.out
    the word is example

### Serializing

```c
// json_serialize.c
#include <stdlib.h>
#include <stdio.h>
#include <jsonc/json.h>

struct person {
    const char *name, *country;
    int age;
};

json_object_t *serialize_person(struct person *val)
{
    json_object_t *obj = init_json_object();
    if (obj == NULL) return NULL;

    json_object_put(obj, "name", json_value_str(val->name));
    json_object_put(obj, "country", json_value_str(val->country));
    json_object_put(obj, "age", json_value_int(val->age));

    return obj;
}

int main(void)
{
    struct person bob = { "Bob", "United States", 22 };
    struct person will = { "William", "United Kingdom", 26 };

    json_object_t *bob_obj = serialize_person(&bob);
    json_object_t *will_obj = serialize_person(&will);

    char bob_str[128], will_str[128];
    json_object_to_str(bob_obj, bob_str);
    json_object_to_str(will_obj, will_str);

    printf("%s\n%s\n", bob_str, will_str);

    free_json_object(will_obj);
    free_json_object(bob_obj);
    return EXIT_SUCCESS;
}
```

    $ gcc json_serialize.c -ljsonc
    $ ./a.out
    {"name": "Bob","country": "United States","age": 22}
    {"name": "William","country": "United Kingdom","age": 26}

## Building

jsonc only requires the standard c library, and uses CMake, so it should work on just about any system.

### \*nix

    $ git clone "https://github.com/desolt/jsonc" && cd jsonc
    $ mkdir build && cd build
    $ cmake -DCMAKE_BUILD_TYPE=Release
    # make install

### Arch Linux

You can easily install jsonc on Arch Linux [from the AUR.](https://aur.archlinux.org/packages/jsonc/)

#### With makepkg

    $ mkdir -p ~/.aur && cd ~/.aur
    $ curl "https://aur.archlinux.org/cgit/aur.git/snapshot/jsonc.tar.gz" -o jsonc.tar.gz
    $ tar -xvf jsonc.tar.gz && cd jsonc
    $ makepkg -si

#### With yaourt

    $ yaourt -S jsonc
