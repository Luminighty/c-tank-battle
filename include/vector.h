#ifndef VECTOR_H
#define VECTOR_H


#include <stdio.h>
#include <stdlib.h>


#define VECTOR(TypeName, ItemType, prefix) \
typedef struct { \
    unsigned long length; \
    unsigned long capacity; \
    ItemType * data; \
} TypeName; \
TypeName prefix ## _create();\
void prefix ## _destroy(TypeName * vector);\
void prefix ## _add(TypeName * vector, ItemType item);\
void prefix ## _remove(TypeName * vector, unsigned long index);\
ItemType * prefix ## _get(TypeName * vector, unsigned long index);\
inline unsigned long prefix ## _length(TypeName * vector);


#define VECTOR_IMPL(TypeName, ItemType, prefix, base_capacity) \
TypeName prefix ## _create() { \
    TypeName vector; \
    vector.length = 0; \
    vector.capacity = base_capacity; \
    vector.data = malloc(sizeof( ItemType ) * base_capacity); \
    if (!vector.data)\
        fprintf(stderr, "Failed to allocate %s\n", #prefix); \
    return vector; \
} \
void prefix ## _destroy(TypeName * vector) { \
    free( vector->data ); \
    vector->length = 0; \
    vector->capacity = 0; \
}\
void prefix ## _add(TypeName * vector, ItemType item) {\
    if ( vector->length >= vector->capacity ) { \
        unsigned long new_capacity = vector->capacity * 2; \
        ItemType * new = realloc( vector->data, sizeof( ItemType ) * new_capacity); \
        if (!new) { \
            fprintf(stderr, "Failed to reallocate %s\n", #prefix ); \
            return; \
        } \
        vector->capacity = new_capacity; \
        vector->data = new; \
    } \
    vector->data[ vector->length++ ] = item; \
}\
void prefix ## _remove(TypeName * vector, unsigned long index) {\
    if (index < 0 || index >= vector->length)\
        return;\
    vector->data[index] = vector->data[ vector->length - 1 ];\
    vector->length--;\
}\
ItemType * prefix ## _get(TypeName * vector, unsigned long index) {\
    if (index < 0 || index >= vector->length)\
        return NULL;\
    return &vector->data[index];\
}\
inline unsigned long prefix ## _length(TypeName * vector) {\
    return vector->length;\
}\


#endif // VECTOR_H
