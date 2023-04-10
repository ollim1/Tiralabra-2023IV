#ifndef RINGBUFFER_H
#define RINGBUFFER_H
#include <stdlib.h>

typedef struct ringbuffer_t {
    void *buf;
    size_t len; // length in elements
    size_t start; // index of first element
    size_t end; // 
    size_t nbytes; // size of element in bytes
} RingBuffer;


#endif
