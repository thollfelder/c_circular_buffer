#include <malloc.h>
#include <string.h>
#include "queue.h"

Queue *create_queue(size_t size, size_t capacity)
{
    if (capacity < 1) {
        fprintf(stderr, "%s", "Error in create_queue(...): Capacity of queue cannot be zero or negative\n");
        return NULL;
    }

    Queue *queue = (Queue *)malloc(sizeof(Queue));
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

    return queue;
}

bool write_queue(Queue *queue, void *data)
{
    if (((queue->write_ptr == queue->buffer_end) && (queue->read_ptr == queue->buffer)) || ((queue->write_ptr + queue->size) == queue->read_ptr))
    {
        // Buffer is full
        //fprintf(stderr, "%s", "Error in write_queue(...): Buffer is full\n");
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

bool read_queue(Queue *queue, void *data)
{
    if (queue->write_ptr == queue->read_ptr)
    {
        //fprintf(stderr, "%s", "Error in read_queue(...): Buffer is empty\n");
        return false;
    }

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

bool peek_queue(Queue *queue)
{
    if (queue->write_ptr == queue->read_ptr)
    {
        //fprintf(stderr, "%s", "Error in read_queue(...): Buffer is empty\n");
        return false;
    }
    else {
        return true;
    }    
}

bool free_queue(Queue *queue)
{
    queue->buffer_end = queue->write_ptr = queue->read_ptr = NULL;
    free(queue->buffer);
    free(queue);    
    return true;
}
