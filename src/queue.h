#ifndef MPI_QUEUE_H
#define MPI_QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct MPI_Queue {
    // Pointer for read and write positions
    void* read_ptr;
    void* write_ptr;
    void* buffer_end;

    // Pointer to buffer
    void* buffer;

    // Capacity
    size_t capacity;

    // Element size in byte
    size_t size;

} MPI_Queue;

MPI_Queue* create_queue(size_t size, size_t capacity);

bool write_queue(MPI_Queue* queue, void* data);

bool read_queue(MPI_Queue* queue, void* data);

bool peek_queue(MPI_Queue* queue);

bool free_queue(MPI_Queue* queue);

#endif