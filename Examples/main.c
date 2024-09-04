// Created by angel on 19/08/24.

#include <stdio.h>
#include "dsa.h"

typedef struct box {
	float x;
	float y;
	unsigned int height;
	unsigned int width;
} box;

NEW_ST_DSA(box);

void PrintQueueint(Nodeint* head) {
	while (head) {
		printf("{%d} \n", head->data);
		head = head->next;
	}
	printf("\n");
}

int main ( void ) {

	Queueint* q = InitQueueint(4);
	QueuePush(q, int, 5);
	QueuePush(q, int, 6);

	PrintQueueint(q->tmp);

	QueuePop(q);
	QueuePop(q);
	QueuePop(q);

	PrintQueueint(q->tmp);

	QueuePush(q, int, 4);

	PrintQueueint(q->tmp);

	QueuePush(q, int, 7);

	PrintQueueint(q->tmp);

    return 0;

}