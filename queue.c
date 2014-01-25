/*
 * queue.c
 *
 *  Created on: 2014-1-4
 *      Author: twd2
 */

#include "queue.h"

struct queue_queue
{
	unsigned int size, maxsize;
	queue_item *head, *tail;
};

struct queue_item
{
	unsigned char data;
	queue_item *next;
};

queue_queue* queue_create()
{
	queue_queue *q;
	q=(queue_queue*)malloc(sizeof(queue_queue));
	if(!q) return NULL;
	q->size=0;
	q->maxsize=0;
	q->head=NULL;
	q->tail=NULL;
	return q;
}

void queue_set_maxsize(queue_queue *q, unsigned int m)
{
	if (!q) return;
	q->maxsize=m;
}

void queue_free(queue_queue *q)
{
	if (!q) return;
	while (queue_dequeue(q));
	free(q);
}

unsigned int queue_size(queue_queue *q)
{
	return q->size;
}

int queue_head(queue_queue *q)
{
	if (!q->head) return -1;
	return q->head->data;
}

int queue_tail(queue_queue *q)
{
	if (!q->tail) return -1;
	return q->tail->data;
}

unsigned int queue_enqueue(queue_queue *q, unsigned char data)
{
	queue_item *i;
	while (q->size>=q->maxsize && q->maxsize>0)
	{
		queue_dequeue(q);
	}
	i=(queue_item*)malloc(sizeof(queue_item));
	if (!i) return 0;
	i->data=data;
	i->next=NULL;
	if (!q->head) q->head=i;
	if (q->tail) q->tail->next=i;
	q->tail=i;
	q->size++;
	return 1;
}

unsigned int queue_dequeue(queue_queue *q)
{
	if (!q->head) return 0;
	queue_item *next;
	next=q->head->next;
	free(q->head);
	q->head=next;
	q->size--;
	return 1;
}
