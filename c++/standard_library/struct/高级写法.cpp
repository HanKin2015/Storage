#include <iostream>
#include <string.h>
#include <cstdio>

#define UP      0
#define DOWN    1
#define REPEAT  2
#define MUTE    3
#define LABEL(constant) { #constant, constant }
#define LABEL_END { NULL, -1 }

struct label {
    const char *name;
    int value;
};

static struct label key_value_labels[] = {
    LABEL(UP),
    LABEL(DOWN),
    LABEL(REPEAT),
    LABEL(MUTE),
    LABEL_END,
};

#define KEY_VOLUMEUP      110
#define KEY_VOLUMEDOWN    111
#define KEY_MUTE          112
static struct label key_labels[] = {
    LABEL(KEY_VOLUMEUP),
    LABEL(KEY_VOLUMEDOWN),
    LABEL(KEY_MUTE),
    LABEL_END,
};

static char *get_label(const struct label *labels, int value) {
    while (labels->name && value != labels->value) {
        printf("%s = %d\n", labels->name, labels->value);
        labels++;
    }

    return (char *)labels->name;
}

int main()
{
    if (get_label(key_value_labels, 2)) {
        printf("found\n");
    } else {
        printf("not found\n");
    }
    if (get_label(key_labels, 12)) {
        printf("found\n");
    } else {
        printf("not found\n");
    }
    return 0;
}
/*
hejian@android-PowerEdge-R920:~/hj$ ./a.out
UP = 0
DOWN = 1
found
KEY_VOLUMEUP = 110
KEY_VOLUMEDOWN = 111
KEY_MUTE = 112
not found
*/