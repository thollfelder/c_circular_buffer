#ifndef Queue_H
#define Queue_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue {
    // Pointer for read, write and buffer_end positions
    void* read_ptr;
    void* write_ptr;
    void* buffer_end;

    // Pointer to buffer
    void* buffer;

    // Capacity
    size_t capacity;

    // Element size in byte
    size_t size;

} Queue;

Queue* create_queue(size_t size, size_t capacity);

bool write_queue(Queue* queue, void* data);

bool read_queue(Queue* queue, void* data);

bool peek_queue(Queue* queue);

bool free_queue(Queue* queue);

#endif