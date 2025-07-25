#include <stdio.h>
#include <stdlib.h>

// defining struct Vector
typedef struct{
    int* data;
    int size;
    int capacity;
} Vector;

//creating a constructor for vector
Vector vector_init(int starting_size) {
    int capacity = 16;
    while (capacity < starting_size) {
        capacity *=2;
    }

    int* data = malloc(capacity * sizeof(int)); // Allocate memory for the data array
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
// defining functions for vector operations
int vector_size(Vector* v) {
    return v->size;
}
// Function to get the capacity of the vector
int vector_capacity(Vector* v) {
    return v->capacity;
}
// Function to check if the vector is empty
int vector_empty(Vector* v) {
    return v->size == 0;
}

// Function to get the value at a specific index in the vector
int vector_at(Vector* v, int index) {
    if (index < 0 || index >= v->size) {
        fprintf(stderr, "Index %d out of bounds (size: %d)\n", index, v->size);
        exit(EXIT_FAILURE);
    }
    return *(v ->data + index); // Accessing the value at the specified index
}
// Function to resize the vector's data array
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
// Function to push a new value into the vector
void vector_push(Vector* v, int value) {
    if (v -> size == v-> capacity) {
        vector_resize(v, v-> capacity);
    }
    *(v -> data+ v -> size) = value;
    v->size++;
}

// Function to insert a value at a specific index in the vector
void vector_insert(Vector*v, int index, int item) {
    if (index < 0 || index > v -> size) {
        fprintf(stderr, "Index %d out of bounds (size: %d)\n", index, v->size);
        exit(EXIT_FAILURE);
    }

    if (v -> size == v -> capacity) {
        vector_resize(v, v -> capacity * 2);
    }

    for (int i = v -> size; i > index; i--) {
        *(v -> data + i) = *(v -> data + i);
    }
    *(v -> data + index) = item;
    v -> size++;
}

//Inserts an item at the front of the vector — index 0
void vector_prepend(Vector* v, int item) {
    vector_insert(v, 0, item);
}

//pop() function, which removes and returns the last item of the vector.
int vector_pop(Vector* v) {
    //To avoid wasting too much memory when many elements are removed.
    //We reduce capacity to half when the size falls below 25% of capacity (but never below your starting minimum capacity).
    if (v->size == 0) {
        fprintf(stderr, "Pop from empty vector\n");
        exit(EXIT_FAILURE);
    }

    int item = *(v->data + v->size - 1);
    v->size--;

    if (v->size > 0 && v->size <= v->capacity / 4) {
        int new_capacity = v->capacity / 2;
        if (new_capacity < 16) {
            new_capacity = 16;  // Keep minimum capacity
        }
        vector_resize(v, new_capacity);
    }

    return item;
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

// checking for vector insert function
    Vector v4 = vector_init(4);
    vector_push(&v4, 10);
    vector_push(&v4, 20);
    vector_push(&v4, 30);

    vector_insert(&v4, 1, 15);  // Insert 15 at index 1

    for (int i = 0; i < vector_size(&v4); i++) {
        printf("v[%d] = %d\n", i, vector_at(&v4, i));
    }

    Vector v5 = vector_init(4);

    vector_push(&v5, 10);
    vector_push(&v5, 20);

    vector_prepend(&v5, 5);

    for (int i = 0; i < vector_size(&v5); i++) {
        printf("v[%d] = %d\n", i, vector_at(&v5, i));
    }

    Vector v6 = vector_init(16);
    vector_push(&v6, 10);
    vector_push(&v6, 20);
    vector_push(&v6, 30);

    printf("Popped: %d\n", vector_pop(&v6)); // 30
    printf("Popped: %d\n", vector_pop(&v6)); // 20

    for (int i = 0; i < vector_size(&v6); i++) {
        printf("v[%d] = %d\n", i, vector_at(&v6, i)); // Should print only 10
    }

    free(v.data); // Don't forget to free the allocated memory later
    free(v1.data);
    free(v2.data);
    free(v3.data);
    free(v4.data);
    free(v5.data);
    free(v6.data);

    return 0;
}