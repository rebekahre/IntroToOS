//CITE: https://www.geeksforgeeks.org/scanf-and-fscanf-in-c/
//CITE: https://www.geeksforgeeks.org/delete-a-node-in-a-doubly-linked-list/
//CITE: https://www.programiz.com/c-programming/c-file-input-output
//CITE: https://www.geeksforgeeks.org/doubly-linked-list/
//CITE: https://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm
//CITE: https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
//CITE: https://www.geeksforgeeks.org/c-program-for-deleting-a-node-in-a-doubly-linked-list/
//CITE: https://www.geeksforgeeks.org/delete-occurrences-given-key-doubly-linked-list/
//CITE: https://stackoverflow.com/questions/44181689/what-does-allocating-memory-of-size-char-do

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
	char* data;
	struct Node* next;
	struct Node* prev;
};


int isEmpty(struct Node* head) { //base case
	if (head == NULL) {
		return 0;
	}
}

 
struct Node* getNewNode(char* x) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); //create node in heap
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}


void insertHead(char* x, struct Node** head) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->prev = NULL;
	newNode->next = (*head);
	newNode->data = x;

	if((*head) != NULL) {
		(*head)->prev = newNode;
	}
	(*head) = newNode;
	return;
}


void insertTail(char* new_data, struct Node** head) { 
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	struct Node* last = *head;

	newNode->data = new_data;
	newNode->next = NULL;	
	if(*head == NULL) { //if list is empty, make new node as head
		newNode->prev = NULL;
		*head = newNode;
		return;
	}
 	//else traverse till the last node
	while(last->next != NULL) {
		last = last->next;
	}
	//then last next is new node
	last->next = newNode; 
        newNode->prev = last;
	return;
}


void deleteNode(struct Node** head, struct Node* nodeDel) {
	if (*head == NULL || nodeDel == NULL) { //base case
                return;
        }
	if(*head == nodeDel) {
		*head = nodeDel->next;
	}
	if(nodeDel->next != NULL) {
		nodeDel->next->prev = nodeDel->prev;	
	}
	if(nodeDel->prev != NULL) {
		nodeDel->prev->next = nodeDel->next;
	}
	free(nodeDel);
	return;
}


void deleteAll(struct Node** head, char* del) {
	if(*head == NULL) {	//base case
 		return;
	}
	struct Node* current = *head;
	struct Node* next;
	
	while(current != NULL) {
	int isEqual = strcmp(current->data, del); //compare strings	
	if (isEqual == 0) { //if equal, 0
		next = current->next; 
		deleteNode(head, current);	//delete
		current = next; 		//current is now next 
	}
	else { //if it doesnt contain value,
		current = current->next;		//traverse
	}
}
	return;
}


void formatPrint(struct Node* node, FILE *fpointer) {
	struct Node* tail;
	if(node == NULL) {
	fprintf(fpointer, "%s\n", "EMPTY");
	}

	while(node != NULL) { //traverse	
	if(node->next == 0 && node->prev == 0) {
	fprintf(fpointer, "(%s,HEAD,TAIL)\n", node->data);
	}
	else if(node->prev == 0 && node->next != 0) {
	fprintf(fpointer, "(%s,HEAD,%s), ", node->data, node->next->data);
	}
	else if(node->next == 0 && node->prev != 0) {
	fprintf(fpointer, "(%s,%s,TAIL)\n", node->data, node->prev->data);  
	}
	else {
	fprintf(fpointer, "(%s,%s,%s), ", node->data, node->prev->data, node->next->data);
	}
	tail = node;	//tail is head at first
	node = node->next;	//node is now equal to node next
}
}


char* addhead(char* fname, int n) {
	FILE* fptr = fopen(fname, "r");
	char ctemp[30];
	char* temp;
	for(int i = 0; i < n; ++i) {
		fscanf(fptr, "addhead \"%s\"\n", temp);
	}
}


int main(int argc, char *argv[]) {
	struct Node* head = NULL;
	struct Node* tail = NULL;
	int lines;
	int ctr = 0;
	char cvar[30];
	char *var = cvar;
	char* bufferPrint;
	char* bufferHead;
	char* bufferTail;
	char* bufferDel;
	char ctemp[30];
	char* temp = ctemp;
	FILE *fptr;
	FILE *foutput;
	

	fptr = fopen(argv[1], "r");
	foutput = fopen(argv[2], "w");

	while(fscanf(fptr, "%[^\n] ", var) != EOF)
	{
	printf(" %s\n ", var); 	

	bufferPrint = strstr(var, "print");   
	if(bufferPrint != NULL) {	
		formatPrint(head, foutput);
	}

	bufferHead = strstr(var, "addhead");
	if(bufferHead != NULL) {
		++ctr;
	temp = strtok(var, "\"");
	temp = strtok(NULL, "\"");
	char* store = (char*)malloc(sizeof(char)*30);
	strcpy(store, temp); //stores into temp	
		insertHead(store, &head);
	}

	bufferTail = strstr(var, "addtail");
	if(bufferTail != NULL) {
	temp = strtok(var, "\"");
        temp = strtok(NULL, "\"");
        char* store = (char*)malloc(sizeof(char)*30);
        strcpy(store, temp); //stores into temp 
                insertTail(store, &head);
	}

	bufferDel = strstr(var, "del");
	if(bufferDel != NULL) {
	temp = strtok(var, "\"");
        temp = strtok(NULL, "\"");
	char* store = (char*)malloc(sizeof(char)*30);
        strcpy(store, temp); //stores into temp 
                deleteAll(&head, store);
	}
}
	fclose(fptr);
    return 0;
}
