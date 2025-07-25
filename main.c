#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int* data;
    int size;
    int capacity;
} Vector;


Vector vector_init(int starting_size) {
    int capacity = 16;
    while (capacity < starting_size) {
        capacity *=2;
    }

    int* data = malloc(capacity * sizeof(int));
    if (data ==NULL) {
        fprintf(stderr, "out of memory\n");
        exit(EXIT_FAILURE);
    }
    Vector v;
    v.data = data;
    v.size = 0;
    v.capacity = capacity;
    return v;
}
int vector_size(Vector* v) {
    return v->size;
}

int vector_capacity(Vector* v) {
    return v->capacity;
}

int vector_empty(Vector* v) {
    return v->size == 0;
}

int vector_at(Vector* v, int index) {
    if (index < 0 || index >= v->size) {
        fprintf(stderr, "Index %d out of bounds (size: %d)\n", index, v->size);
        exit(EXIT_FAILURE);
    }
    return *(v ->data + index);
}
void vector_resize(Vector* v, int new_capacity) {
    int* new_data = malloc(new_capacity * sizeof(int));
    if (new_data == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(EXIT_FAILURE);
    }

    //copy old data
    for (int i = 0; i < v -> size; i++) {
        *(new_data + i) = *(v -> data + i);
    }

    //free old memory
    free(v -> data);

    //update vector
    v -> data = new_data;
    v -> capacity = new_capacity;
    printf("Resized vector to new capacity: %d\n", new_capacity);
}
void vector_push(Vector* v, int value) {
    if (v -> size == v-> capacity) {
        vector_resize(v, v-> capacity);
    }
    *(v -> data+ v -> size) = value;
    v->size++;
}


int main(void) {
    //checking for vector initialization and resizing
    Vector v = vector_init(20); // Try initializing with a number > 16

    printf("Vector initialized with capacity: %d, size: %d\n", v.capacity, v.size);

    //checking for vector size, capacity and empty status
    Vector v1 = vector_init(10);

    printf("Size: %d\n", vector_size(&v1));
    printf("Capacity: %d\n", vector_capacity(&v1));
    printf("Is Empty: %d\n", vector_empty(&v1));


    // checking for vector push and at(index)
    Vector v2 = vector_init(5);
    v2.data[0] = 42;
    v2.size = 1;

    printf("Value at index 0: %d\n", vector_at(&v, 0));  // Should print 42
    printf("Value at index 1: %d\n", vector_at(&v, 1));  // Should crash: out of bounds

    //implementing the push function of an array
    Vector v3 = vector_init(1);
    for (int i = 0; i < 20; i++) {
        vector_push(&v3, i * 10);
    }
    for (int i = 0; i < vector_size(&v); i++) {
        printf("v[%d] = %d\n", i, vector_at(&v3, i));
    }



    free(v.data); // Don't forget to free the allocated memory later
    free(v1.data);
    free(v2.data);
    free(v3.data);

    return 0;
}