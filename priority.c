//https://www.geeksforgeeks.org/priority-queue-using-linked-list/
// C code to implement Priority Queue
// using Linked List
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

// Node
typedef struct node {
    pid_t data;
 
    // Lower values indicate higher priority
    int priority;
 
    struct node* next;
 
} Node;
 
// Function to Create A New Node
Node* newNode(pid_t d, int p)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;
 
    return temp;
}
 
// Return the value at head
int peek(Node** head)
{
    return (*head)->data;
}
 
// Removes the element with the
// highest priority form the list
void pop(Node** head)
{
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}
 
// Function to push according to priority
void push(Node** head, pid_t d, int p)
{
    Node* start = (*head);
 
    // Create new Node
    Node* temp = newNode(d, p);
 
    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->priority > p) {
 
        // Insert New Node before head
        temp->next = *head;
        (*head) = temp;
    }
    else {
 
        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL &&
            start->next->priority < p) {
            start = start->next;
        }
 
        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}
 
// Function to check is list is empty
int isEmpty(Node** head)
{
    return (*head) == NULL;
}
 
// Driver code
int main()
{
    // Create a Priority Queue
    // 7->4->5->6

    //int i;

    //for(i = 0; i < 20; i++){
    	int i, n;
   time_t t;
   
   n = 5;

   srand((unsigned) time(&t));

	pid_t pid = fork();
	
	for( i = 0 ; i < n ; i++ )
            i = (rand() % 3);

    	Node* pq = newNode(pid, 1);
    	push(&pq, pid, i);
    	push(&pq, pid, i);
    	push(&pq, pid, i);
    

    while (!isEmpty(&pq)) {
        printf("%d\n ", peek(&pq));
        pop(&pq);
    }
	
    return 0;
}
