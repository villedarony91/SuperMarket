#include <stdio.h>
#include <stdlib.h>
#include "Supermercado.h"

int getNumCarretas(){
  int number;
  printf ("Ingresa el numero de carretillas ");
  scanf ("%d", &number);
  return number;
}


int getPerCompras(){
  int number;
  printf ("Ingresa el numero de Personas de Compras ");
  scanf ("%d", &number);
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
}

struct Node* head;// global variable - pointer to head node.
struct Node* headQ;
int clientId = 0;

//Creates a new Node and returns pointer to it. 
struct Node* getNewNode(int gen, int ag, int preg, int id, int prior){
  struct Node* newNode
    = (struct Node*)malloc(sizeof(struct Node));
  newNode->gender = gen;
  newNode->age = ag;
  newNode->pregnant = preg;
  newNode->id = clientId;
  newNode->priority = prior;
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}

void print() {
  struct Node* temp = head;
  printf("Forward: ");
  while(temp != NULL) {
    printf("********\n");
    printf("id %d \n",temp->id);
    printf("edad%d \n", temp->age);
    printf("prioridad %d \n", temp->priority);
    printf("embarazado %d \n", temp->pregnant);
    printf("genero %d \n", temp->gender);
    temp = temp->next;
    head = head;
  }
  printf("\n");
} 


//Inserts a Node at head of doubly linked list
void insertAtHead(int gen, int ag, int preg, int id, int prior) {
  struct Node* newNode = getNewNode(gen, ag , preg, id, prior);
  if(head == NULL) {
    head = newNode;
    return;
  }
  head->prev = newNode;
  newNode->next = head; 
  head = newNode;
}


//Inserts a Node at tail of Doubly linked list
void insertAtTail(int gen, int ag, int preg, int id, int prior) {
  struct Node* temp = head;
  struct Node* newNode = getNewNode(gen, ag , preg, id, prior);
  if(head == NULL) {
    head = newNode;
    return;
  }
  while(temp->next != NULL) temp = temp->next; // Go To last Node
  temp->next = newNode;
  newNode->prev = temp;
  head = head;
}

void insertMiddle(int gen, int ag, int preg, int id, int prior){
  struct Node* temp = head;
  struct Node* newNode = getNewNode(gen, ag , preg, id, prior);
  struct Node* aux;
  if(head == NULL || head->priority == 1 ){
    insertAtHead(gen, ag, preg, id, prior);
  }
  else{
    while(temp->priority == 0 && temp->next != NULL) {
      temp = temp->next;
    }
    if(temp->next == NULL || temp->priority != 1){
      insertAtTail(gen, ag, preg, id, prior);
    }else{
      temp->prev->next = newNode;
      newNode->prev = temp->prev;
      temp->prev = newNode;
      newNode->next = temp;
    }
  }
}



void createClient(int buying){
  int gender = getRandom(2);
  int pregnant = getRandom(2);
  int age = getRandom(100);
  int priority = 1;
  if(gender == 0){
    pregnant = 3;
  }
  if( pregnant == 1 || age > 59){
    priority = 0;
  }
  if(buying == 0){
  if(priority == 1){insertAtTail(gender, age, pregnant, clientId++, priority);}
  else{insertMiddle(gender, age, pregnant, clientId++, priority);}
  }
  if(buying == 1){
    queueTurn = getRandom(5);
    
  }
}

int getRandom(int max){
  return rand() % max;
}

int getClientNumber(){
  int number;
  printf ("Ingresa el numero de Clientes");
  scanf ("%d", &number);
  return number;
}

int setClientsOnList(){
  int i = 0;
  int clientNumber = getClientNumber();
  for(i ; i < clientNumber ; i++){
    createClient(0);
  }
}


int main() {
  createStacksForCarretas();
  setClientsOnList();
  print();
  printf("--------------------------/n");
  //  print();
  return 0;
}

