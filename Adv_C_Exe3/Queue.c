#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

/***************** Queue ADT Implementation *****************/

void initQueue(Queue* q)
{
	q->head = NULL;
	q->tail = NULL;
}

void destroyQueue(Queue* q)
{
	// add your code here
}

void enqueue(Queue* q, unsigned int data)
{
	intNode* newIntNode = (intNode*)malloc(sizeof(intNode));
	if (newIntNode == NULL)
	{
		printf("Push: Memory allocation problem\n");
		return;
	}

	newIntNode->data = data; //Set element data
	newIntNode->next = NULL;

	if (!isEmptyQueue(q)) 
		q->tail->next = newIntNode; 

	else 
		q->head = newIntNode;

	q->tail = newIntNode; //Update queue tail
}

unsigned int dequeue(Queue* q)
{
	// this function return and delete the head
	if (isEmptyQueue(q))
	{
		printf("Cannot dequeue an empty queue!");
		return 0;
	}
	
	int temp = q->head->data;
	intNode* tmpIntNode = q->head;

	q->head = q->head->next;

	if (q->head == NULL) //If queue gets empty
		q->tail = NULL;//Both front and rear NULL

	free(tmpIntNode);
	return temp;
}

int isEmptyQueue(const Queue* q)
{
	if ((q->head == NULL && q->tail == NULL))
		return 1;
	return 0;
}

/***************** Functions using Queues - Implementation/definition **************************/

void rotateQueue(Queue* q)
{
	if (q == NULL)//Check if valid queue pointer
		return -1;
	else if (isEmptyQueue(q))
		return -1;

	intNode* tmpIntNode = q->head;
	int queueLen = 0;

	while (tmpIntNode != NULL) //Get queue lengh
	{
		tmpIntNode = tmpIntNode->next;
		queueLen++;
	}
	tmpIntNode = q->head;
	for (int i = 0; i < queueLen-2; i++) //Set temp to one node before tail
		tmpIntNode = tmpIntNode->next;

	tmpIntNode->next = NULL;
	q->tail->next = q->head; //Set tail-node-pointer to head-node
	q->head = q->tail; //Set head pointer to tail-node
	q->tail = tmpIntNode; //Set tail to the one node before the previous tail

}

void cutAndReplace(Queue* q)
{
	if (q == NULL)//Check if valid queue pointer
		return -1;
	else if (isEmptyQueue(q))
		return -1;

	intNode* tmpIntNode = q->head;
	int queueLen = 0;

	while (tmpIntNode != NULL) //Get queue lengh
	{
		tmpIntNode = tmpIntNode->next;
		queueLen++;
	}
	tmpIntNode = q->head;

	if (queueLen % 2) //If queue lengh is odd
	{
		intNode newNode;
		int sum = 0;
		for (int i = 0; i < queueLen; i++)
		{
			sum += tmpIntNode->data;
			tmpIntNode = tmpIntNode->next;
		}
		sum = sum / queueLen;
		enqueue(q, sum);
		queueLen++;
	}

	Queue tmpQueue;
	initQueue(&tmpQueue);
	for (int  i = 0; i < queueLen/2; i++)
	{
		rotateQueue(q);
		enqueue(&tmpQueue, dequeue(q));
	}
	for (int i = 0; i < queueLen / 2; i++)
	{
		enqueue(&tmpQueue, dequeue(q));
	}
	q->head = tmpQueue.head;
	q->tail = tmpQueue.tail;
}

void sortKidsFirst(Queue* q)
{
	if (q == NULL)//Check if valid queue pointer
		return -1;
	else if (isEmptyQueue(q))
		return -1;
	intNode* tmpNode1 = q->head;
	intNode* tmpNode2 = q->head;
	Queue tmpQueue;
	initQueue(&tmpQueue);

	int queueLen = 0;
	int maxNum = 0;
	while (tmpNode1 != NULL) //Get queue lengh and max num
	{
		if (tmpNode1->data > maxNum)
			maxNum = tmpNode1->data;
		tmpNode1 = tmpNode1->next;
		queueLen++;
	}
	tmpNode1 = q->head;

	for (int x = 0; x < queueLen; x++)//Go through the que len's time of the que
	{
		int minNum = maxNum;
		while (tmpNode1 != NULL) 
		{
			if (tmpNode1->data <= minNum)//Get the current min num and save his positon
			{
				minNum = tmpNode1->data;
				tmpNode2 = tmpNode1;
			}
				tmpNode1 = tmpNode1->next;
		}
		tmpNode1 = q->head;
		tmpNode2->data = maxNum;//Set tge min-num-node-date to maxnum so won't get him again
		enqueue(&tmpQueue, minNum);//enqueue the current min num
	}
	destroyQueue(q);
	q->head = tmpQueue.head;
	q->tail = tmpQueue.tail;//Set tmp queue as the current queue
}