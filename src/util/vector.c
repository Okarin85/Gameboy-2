/* vector.c --- 
 * 
 * Filename: vector.c
 * Author: Jules <archjules>
 * Created: Wed Jun 14 23:30:16 2017 (+0200)
 * Last-Updated: Thu Jun 15 01:47:31 2017 (+0200)
 *           By: Jules <archjules>
 */
#include <stdlib.h>
#include "logger.h"
#include "util/vector.h"

bool vector_expand(struct Vector * vector, int data) {
    int * new_ptr = NULL;
    
    vector->capacity++;
    new_ptr = realloc(vector->data, vector->capacity * sizeof(int));
    
    if (new_ptr == NULL) {
	log_err("Could not allocate more memory!");
	return false;
    } else {
	vector->data = new_ptr;
	vector->data[vector->capacity - 1] = data;

	vector_present(*vector, data);
	return true;
    }
}

bool vector_remove(struct Vector * vector, int data) {
    int id = -1;
    for (int i = 0; i < vector->capacity; i++) {
	if (vector->data[i] == data) id = i;
    }

    if (id == -1) return false;
    
    for (int i = id; i < (vector->capacity - 1); i++) {
	vector->data[i] = vector->data[i + 1];
    }

    vector->capacity--;
    vector->data = realloc(vector->data, vector->capacity * sizeof(int));
    
    return true;
}

bool vector_present(struct Vector vector, int data) {
    bool is_present = false;

    for (int i = 0; i < vector.capacity; i++) {
	if (vector.data[i] == data) {
	    is_present = true;
	    break;
	}
    }

    return is_present;
}

void vector_free(struct Vector * vector) {
    free(vector->data);

    vector->data = NULL;
    vector->capacity = 0;
}
