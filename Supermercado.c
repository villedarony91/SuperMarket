#include <stdio.h>
#include <stdlib.h>
#include "Supermercado.h"

int getNumCarretas(){
  int number;
  printf ("Ingresa el numero de carretillas ");
  scanf ("%d", &number);
  printf ("You entered: %d \n", number);
  return number;
}

Carreta * createStackCarr(int maxElements)
{
  Carreta *S;
  S = (Carreta *)malloc(sizeof(Carreta));
  S->noCarreta = (int *)malloc(sizeof(int)*maxElements);
  S->size = 0;
  S->capacity = maxElements;
  return S;
}

void pop(Carreta *S)
{
  if(S->size==0)
    {
      printf("Pila esta vacia\n");
      return;
    }
  else
    {
      S->size--;
    }
  return;
}

int top(Carreta *S)
{
  if(S->size==0)
    {
      printf("Stack is Empty\n");
      exit(0);
    }
  //Devolver el último elemento de la pila
  return S->noCarreta[S->size-1];
}
void push(Carreta *S,int noCarreta)
{
  //Verificar si la pila esta llena
  if(S->size == S->capacity)
    {
      printf("Pila esta llena\n");
    }
  else
    {
      //Al ingresar un elemento a la pila se debe de aumentar el tamaño
      S->noCarreta[S->size++] = noCarreta;
    }
  return;
}

void createStacksForCarretas(){
  int i = 0;
  int r;
  int carrNum = getNumCarretas();
  printf("carrnum %d",carrNum);
  Carreta *stack0 = createStackCarr(carrNum);
  Carreta *stack1 = createStackCarr(carrNum);
  Carreta *stack2 = createStackCarr(carrNum);
  Carreta *stack3 = createStackCarr(carrNum);
  for(i ; i < carrNum; i++){
    switch(r = rand() % 4){
    case 0:
      push(stack0,i);
      printf("the top is stack0 %d\n",top(stack0));
      break;
    case 1:
      push(stack1, i);
      printf("the top is stack1 %d\n",top(stack1));
      break;
    case 2:
      push (stack2, i);
      printf("the top is stack2 %d\n",top(stack2));
      break;
    case 3:
      push (stack3, i);
      printf("the top is stack3 %d\n",top(stack3));
      break;
    }  
  }
  for(i; i < stack0->size; i++){
    printf("the top is %d\n",top(stack0));
    pop(stack0);
  }
}

struct Node* head; // global variable - pointer to head node.
int clientId = 0;

//Creates a new Node and returns pointer to it. 
struct Node* getNewNode(int gen, int ag, int preg, int id){
	struct Node* newNode
		= (struct Node*)malloc(sizeof(struct Node));
	newNode->gender = gen;
	newNode->age = ag;
	newNode->pregnant = preg;
	newNode->id = clientId;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

//Inserts a Node at head of doubly linked list
void insertAtHead(int gen, int ag, int preg, int id) {
  struct Node* newNode = getNewNode(gen, ag , preg, id);
	if(head == NULL) {
		head = newNode;
		return;
	}
	head->prev = newNode;
	newNode->next = head; 
	head = newNode;
}
/*
//Inserts a Node at tail of Doubly linked list
void InsertAtTail(int x) {
	struct Node* temp = head;
	struct Node* newNode = GetNewNode(x);
	if(head == NULL) {
		head = newNode;
		return;
	}
	while(temp->next != NULL) temp = temp->next; // Go To last Node
	temp->next = newNode;
	newNode->prev = temp;
}
*/
//Prints all the elements in linked list in forward traversal order
void print() {
	struct Node* temp = head;
	printf("Forward: ");
	while(temp != NULL) {
	  printf("********");
		printf("id %d \n",temp->id);
		printf("edad%d \n", temp->age);
		temp = temp->next;
	}
	printf("\n");
}
/*
//Prints all elements in linked list in reverse traversal order. 
void ReversePrint() {
	struct Node* temp = head;
	if(temp == NULL) return; // empty list, exit
	// Going to last Node
	while(temp->next != NULL) {
		temp = temp->next;
	}
	// Traversing backward using prev pointer
	printf("Reverse: ");
	while(temp != NULL) {
		printf("%d ",temp->data);
		temp = temp->prev;
	}
	printf("\n");
}
*/
void createClient(){
  int gender = getGender();
  int pregnant = setPregnant();
  if(gender = 0){
    pregnant = 3;
  }
  insertAtHead(gender, getAge(), pregnant, clientId++);
}

int getGender(){
  return rand() % 1;
}

int getAge(){
  return rand() % 100;
}

int setPregnant(){
  return rand() % 1;
}

int getClientNumber(){
  int number;
  printf ("Ingresa el numero de Clientes");
  scanf ("%d", &number);
  printf ("You entered: %d \n", number);
  return number;
}

int setClientsOnList(){
  int i = 0;
  int clientNumber = getClientNumber();
  for(i ; i < clientNumber ; i++){
    createClient();
  }
}


int main() {
  createStacksForCarretas();
  setClientsOnList();
  print();
  return 0;
}
