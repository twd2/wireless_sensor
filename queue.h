/*
 * queue.h
 *
 *  Created on: 2014-1-4
 *      Author: twd2
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>

typedef struct queue_queue queue_queue;
typedef struct queue_item queue_item;

queue_queue* queue_create();
void queue_set_maxsize(queue_queue*, unsigned int);
void queue_free(queue_queue*);
unsigned int queue_size(queue_queue*);
int queue_head(queue_queue*);
int queue_tail(queue_queue*);
unsigned int queue_enqueue(queue_queue*, unsigned char);
unsigned int queue_dequeue(queue_queue*);

#endif /* QUEUE_H_ */
