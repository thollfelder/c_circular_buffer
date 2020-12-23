#include <malloc.h>
#include <string.h>
#include "queue.h"

MPI_Queue *create_queue(size_t size, size_t capacity)
{
    MPI_Queue *queue = (MPI_Queue *)malloc(sizeof(MPI_Queue));
    if (queue == NULL)
    {
        fprintf(stderr, "%s", "Error in create_queue(...): Allocating memory for queue failed\n");
        return NULL;
    }

    queue->buffer = malloc(size * capacity);
    if (queue->buffer == NULL)
    {
        fprintf(stderr, "%s", "Error in create_queue(...): Allocating memory for queue->buffer failed\n");
        return NULL;
    }

    queue->read_ptr = queue->write_ptr = queue->buffer;
    queue->size = size;
    queue->capacity = capacity;
    queue->buffer_end = queue->buffer + queue->capacity * queue->size;

    // DEBUG:
    printf("Adress of read_ptr: %p\n", queue->read_ptr);
    printf("Adress of write_ptr: %p\n", queue->write_ptr);
    printf("Adress of buffer_end: %p\n", queue->buffer_end);
    printf("Size of queue: %zu\n", queue->size);
    printf("Capacity of queue: %zu\n", queue->capacity);
    printf("Adress of read_ptr + 1: %p\n", queue->read_ptr + 1);
    printf("Adress of read_ptr + size: %p\n", queue->read_ptr + queue->size);
    /*
    int x = 5;
    void* data = (void*) &x;

    queue->write_ptr = queue->buffer_end - 4;
    queue->read_ptr = queue->buffer_end;

    write_queue(queue, data);
*/

    return queue;
    /*
    //printf("Adress \n", (queue->read_ptr + queue->size) % (queue->count * queue->size))

    void* max_address = queue->data + queue->capacity * queue->size;
    printf("Adress of max_address: %p\n", max_address);

        // calculate end of queue->data:
    void* end_address = queue->data + queue->capacity * queue->size;
    void* start_address = queue->data;
    // check if write pointer is a
    printf("Difference of read_ptr: %td\n", end_address - queue->read_ptr);
    queue->read_ptr += 4;
    printf("Difference of read_ptr: %td\n", end_address - queue->read_ptr);

    // calculate end of queue->data:

    // check if write pointer is a
    //printf("Difference of read_ptr: %p\n", end_address - queue->read_ptr);
    printf("Difference of read_ptr: %td\n", end_address - queue->read_ptr);
    queue->read_ptr += 1;
    printf("Difference of read_ptr: %td\n", end_address - queue->read_ptr);

*/
}

bool write_queue(MPI_Queue *queue, void *data)
{

    // check if write_ptr is behind read_ptr
    // DEBUG:
    // printf("Adress of read_ptr: %p\n", queue->read_ptr);
    // printf("Adress of write_ptr: %p\n", queue->write_ptr);
    // printf("Data: %i\n", *((int*) data));


    if (((queue->write_ptr == queue->buffer_end) && (queue->read_ptr == queue->buffer)) || ((queue->write_ptr + queue->size) == queue->read_ptr))
    {
        //buffer is full
        fprintf(stderr, "%s", "Error in write_queue(...): Buffer is full\n");
        return false;
    }
    else
    {

        memcpy(queue->write_ptr, data, queue->size);
        if (queue->write_ptr == queue->buffer_end)
        {
            queue->write_ptr = queue->buffer;
        }
        else
        {
            queue->write_ptr += queue->size;
        }
        return true;
    }
}

bool read_queue(MPI_Queue *queue, void *data)
{
    if (queue->write_ptr == queue->read_ptr)
    {
        fprintf(stderr, "%s", "Error in read_queue(...): Buffer is empty\n");
        return false;
    }

    // DEBUG:
    // printf("Adress of read_ptr: %p\n", queue->read_ptr);
    // printf("Adress of write_ptr: %p\n", queue->write_ptr);
    // printf("Content of read_ptr: %i\n", *(int*)queue->read_ptr);

    memcpy(data, queue->read_ptr, queue->size);
    if (queue->read_ptr == queue->buffer_end)
    {
        queue->read_ptr = queue->buffer;
    }
    else
    {
        queue->read_ptr += queue->size;
    }
    return true;
}

bool peek_queue(MPI_Queue *queue)
{
    if (queue->write_ptr == queue->read_ptr)
    {
        fprintf(stderr, "%s", "Error in read_queue(...): Buffer is empty\n");
        return false;
    }
    else {
        return true;
    }    
}

bool free_queue(MPI_Queue *queue)
{
    queue->buffer_end = queue->write_ptr = queue->read_ptr = NULL;
    free(queue->buffer);
    free(queue);    
}
