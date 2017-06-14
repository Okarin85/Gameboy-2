/* vector.h --- 
 * 
 * Filename: vector.h
 * Author: Jules <archjules>
 * Created: Wed Jun 14 22:22:08 2017 (+0200)
 * Last-Updated: Thu Jun 15 01:27:08 2017 (+0200)
 *           By: Jules <archjules>
 */

#ifndef VECTOR_H
#define VECTOR_H
#include <stdbool.h>

struct Vector {
    int capacity;
    int * data;
};

bool vector_expand (struct Vector *, int);
bool vector_remove (struct Vector *, int);
bool vector_present(struct Vector, int);
void vector_free   (struct Vector *);

#endif /* VECTOR_H */
