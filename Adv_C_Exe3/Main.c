#include <stdio.h>
#include "Stack.h"
#include "Queue.h"
#include <string.h>

void main()
{
	Stack stack;
	Stack* stackPtr = &stack;
	initStack(stackPtr);

	Queue queue;
	Queue* queuePtr = &queue;
	initQueue(queuePtr);

	//STACKS EXE
	//Exe I
	char sentence1[] = "Remem#reb# thi#crap s#tice"; // Temp 1
	flipBetweenHashes(sentence1);
	printf("\n");
	char sentence2[] = "#meR#embe#siht r# practice"; // Temp 2
	flipBetweenHashes(sentence2);
	printf("\n");
	destroyStack(stackPtr);

	//Exe II
	char sentence3[] = "NOON";
	for (int i = 0; i < strlen(sentence3); i++)
		push(stackPtr, sentence3[i]);
	if (isPalindrome(stackPtr))
		printf("Palindrome\n");
	else
		printf("Not Palindrome\n");

	char sentence4[] = "MADAM";
	for (int i = 0; i < strlen(sentence4); i++)
		push(stackPtr, sentence4[i]);
	if (isPalindrome(stackPtr))
		printf("Palindrome\n");
	else
		printf("Not Palindrome\n");

	//Exe III
	char sentence5[] = "ABCDEF";
	for (int i = 0; i < strlen(sentence5); i++)
		push(stackPtr, sentence5[i]);
	rotateStack(stackPtr, 3);
	while (!isEmptyStack(stackPtr))
		printf("%c", pop(stackPtr));
	printf("\n"); printf("\n");
	

	//Queue EXE
	//Exe I
	int arr1[] = { 1,2,3,4,5,6,7 };
	for (int i = 0; i < sizeof(arr1)/4; i++)
		enqueue(queuePtr, arr1[i]);
	rotateQueue(queuePtr);
	while (!isEmptyQueue(queuePtr))
		printf("%d", dequeue(queuePtr));
	printf("\n");

	//Exe II
	int arr2[] = { 6,1,5,2,3,1,9 };
	for (int i = 0; i < sizeof(arr2) / 4; i++)
		enqueue(queuePtr, arr2[i]);
	cutAndReplace(queuePtr);
	while (!isEmptyQueue(queuePtr))
		printf("%d", dequeue(queuePtr));
	printf("\n");

	int arr3[] = { 6,5,2,3,1,9 };
	for (int i = 0; i < sizeof(arr3) / 4; i++)
		enqueue(queuePtr, arr3[i]);
	cutAndReplace(queuePtr);
	while (!isEmptyQueue(queuePtr))
		printf("%d", dequeue(queuePtr));
	printf("\n");

	//Exe III
	int arr4[] = { 5,0,3,4,2,1,7,9,5,4,2,3 };
	for (int i = 0; i < sizeof(arr4) / 4; i++)
		enqueue(queuePtr, arr4[i]);
	sortKidsFirst(queuePtr);
	while (!isEmptyQueue(queuePtr))
		printf("%d", dequeue(queuePtr));
	printf("\n");


}