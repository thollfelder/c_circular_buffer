#include <stdio.h>
#include "queue.h"

#define LEN 10

int main() {

    Queue* qa = create_queue(sizeof(int), 0);
    Queue* qu = create_queue(sizeof(int), LEN);

    for (int i = 0; i < LEN; ++i) {
        write_queue(qu, &i);
        printf("Wrote to Queue:\t\t%i\n", i);
    }

    for (int i = 0; i < LEN; ++i) {
        int temp;
        read_queue(qu, &temp);
        printf("Read from Queue:\t%i\n", temp);
    }

    return 0;
}