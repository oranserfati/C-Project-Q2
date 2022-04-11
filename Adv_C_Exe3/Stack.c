#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

/***************** Stack ADT Implementation *****************/

void initStack(Stack* s)
{
	s->head = NULL;
}

void destroyStack(Stack* s)
{
	charNode* tmp = s->head;
	while (s->head != NULL)
	{
		s->head = s->head->next;
		free(tmp);
		tmp = s->head;
	}
}

void push(Stack* s, char data)
{
	charNode* newCharNode = (charNode*)malloc(sizeof(charNode));
	if (newCharNode == NULL) 
	{
		printf("Push: Memory allocation problem\n");
		return;
	}

	newCharNode->data = data; //Push data
	newCharNode->next = s->head; //Connect newNode to last node
	s->head = newCharNode; //Initiate head
}


char pop(Stack* s)
{
	char data;
	if (isEmptyStack(s)) 
	{
		printf("\nSTACK IS EMPTY");
		return 0;
	}
	data = s->head->data;//Pop it from the stack

	charNode* tmp = s->head; //Now remove used node
	s->head = s->head->next;
	free(tmp);

	return(data);
}

int isEmptyStack(const Stack* s)
{
	return (s->head == NULL);
}

/*************** Functions using stacks - Implementation/definition **************************/

void flipBetweenHashes(const char* sentence)
{
	Stack newStack, tmpStack;
	initStack(&newStack);
	initStack(&tmpStack);
	int i = 0;
	int hash = 0;
	while (*(sentence + i) != 0) 
	{
		if (*(sentence + i) == '#') //1st Hash push to temp stack
		{
			hash++;
			if (hash == 2) //2nd Hash push all temp stack to new stack
			{
				while (!isEmptyStack(&tmpStack))
					push(&newStack, pop(&tmpStack));
				hash = 0;
			}
		}
		else if (hash)
			push(&tmpStack, *(sentence + i));
		else
			push(&newStack, *(sentence + i));
		i++;
	}

	while (!isEmptyStack(&newStack))
		push(&tmpStack, pop(&newStack)); //Revert sentence

	while (!isEmptyStack(&tmpStack)) //Print sentence
		printf("%c", pop(&tmpStack));
	
}

int isPalindrome(Stack* s)
{

	int stackLen = 0;
	charNode* node = s->head;
	Stack tmpStack;
	initStack(&tmpStack);
	while (node != NULL) //Get stack lengh
	{
		stackLen++;
		node = node->next;
	}
	if (!stackLen)
		return 1;

	for (int i = 0; i < (stackLen/2); i++) //Split stack into to even stacks
	{
		push(&tmpStack, pop(s));
	}
	if (stackLen % 2) //If odd-lengh stack, throw away middle char
		pop(s);

	while (!isEmptyStack(s)) //Compare stacks
		if (pop(s) != pop(&tmpStack))
			return 0;

	return 1;
}

void rotateStack(Stack* s, int n)
{
	if (isEmptyStack(s))
		return 0;
	else if (n < 1)
		return 0;

	charNode* node = s->head;
	int stackLen = 0;
	while (node != NULL) //Get stack lengh
	{
		stackLen++;
		node = node->next;
	}
	if (n > stackLen)
		return 0;

	//Create two temp stacks for rotation
	Stack tmpStack1;
	Stack tmpStack2;
	initStack(&tmpStack1);
	initStack(&tmpStack2);

	for (int i = 0; i < (stackLen - n); i++) //Move all node we dont want to rotate
		push(&tmpStack1, pop(s));

	while (!isEmptyStack(s)) //Move rotate nodes to diff stack
		push(&tmpStack2, pop(s));

	while (!isEmptyStack(&tmpStack1)) //Move back the node we dont want to rotate
		push(s, pop(&tmpStack1));

	while (!isEmptyStack(&tmpStack2)) //rotate choosen nodes
		push(s, pop(&tmpStack2));
}