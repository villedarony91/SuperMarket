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

int getGoldenCitizen(){
  int number;
  printf ("Ingresa el numero de Ciudadanos de oro en cola para pagar");
  scanf ("%d", &number);
  return number;
}

int getCitizen(){
  int number;
  printf ("Ingresa el numero de Ciudadanos en cola para pagar");
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
int carrId;

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
    carrId++;
  }
}

struct Node* head;// global variable - pointer to head node.
struct Node* headQ;
struct Node* headCirc;
struct Node* goldenHead;
struct Node* cityHead;
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

struct Node* getNewNodeCirc(int gen, int ag, int preg, int id, int prior,int carreta, int turnQ){
  struct Node* newNode
    = (struct Node*)malloc(sizeof(struct Node));
  newNode->gender = gen;
  newNode->age = ag;
  newNode->pregnant = preg;
  newNode->id = clientId;
  newNode->priority = prior;
  newNode->turnoCompra = turnQ;
  newNode->carretaId = carreta;
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

void enqueueForPayCiti(int gen, int ag, int preg, int id, int prior,
		   int carreta, int turnQ){
  struct Node* temp = goldenHead;
  struct Node* newNode = getNewNodeCirc(gen, ag , preg, id, prior, carreta, turnQ);
  if(goldenHead == NULL) {
    goldenHead = newNode;
    return;
  }
  while(temp->next != NULL) temp = temp->next; // Go To last Node
  temp->next = newNode;
  newNode->prev = temp;
  head = head;
}

void enqueueForPay(int gen, int ag, int preg, int id, int prior,
		   int carreta, int turnQ){
  struct Node* temp = cityHead;
  struct Node* newNode = getNewNodeCirc(gen, ag , preg, id, prior, carreta, turnQ);
  if(cityHead == NULL) {
    cityHead = newNode;
    return;
  }
  while(temp->next != NULL) temp = temp->next; // Go To last Node
  temp->next = newNode;
  newNode->prev = temp;
}

void printG(Node* goldenH) {
  struct Node* temp = goldenH;
  printf("Forward: ");
  while(temp != NULL) {
    printf("********\n");
    printf("id %d \n",temp->id);
    printf("edad%d \n", temp->age);
    printf("prioridad %d \n", temp->priority);
    printf("embarazado %d \n", temp->pregnant);
    printf("genero %d \n", temp->gender);
    temp = temp->next;
  }
  printf("\n");
} 


void addOnCircular(int gen, int ag, int preg, int id, int prior, int turnCir){
  struct Node* temp = headCirc;
  struct Node* newNode = getNewNodeCirc(gen, ag , preg, id, prior, carrId++,turnCir);
  if(headCirc == NULL) {
    headCirc = newNode;
    headCirc->next = newNode;
    return;
  }
  if(temp->next == headCirc){
    temp->next = newNode;
    newNode->next = headCirc;
    printf("actual %d)",temp->id);
    printf("siguiente %d",temp->next->id);
  return;
  }
  while(temp->next != headCirc){
    temp = temp->next;
  }
    temp->next = newNode;
    newNode->next = headCirc;
    printf("actual %d)",temp->id);
    printf("siguiente %d",temp->next->id);
}

void createClient(int flag){
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
  if(flag == 0){
  if(priority == 1){insertAtTail(gender, age, pregnant, clientId++, priority);}
  else{insertMiddle(gender, age, pregnant, clientId++, priority);}
  }
  if(flag == 1){
    int queueTurn = getRandom(5);
    addOnCircular(gender, age, pregnant, clientId++, priority,queueTurn);
    printf("added");
  }
  if(flag == 2){
    age = getRandom(59);
    if(pregnant == 1){pregnant = 0;}
    enqueueForPay(gender, age, pregnant, clientId++, 1,carrId++, -1);
  }
}

int getRandom(int max){
  return rand() % max;
}

void setClientsOnIQueue(){
  int i = 0;
  int perCompras = getPerCompras();
  for(i ; i < perCompras ; i++){
    createClient(1);
  }
}

void printOnCircQueue(){
  struct Node* temp = headCirc;
  while(temp->next != headCirc) {
    printf("********\n");
    printf("id %d \n",temp->id);
    printf("prioridad %d \n", temp->priority);
    printf("Carreta %d \n", temp->carretaId);
    printf("Turno %d \n", temp->turnoCompra);
    temp = temp->next;
  }
    printf("********\n");
    printf("id %d \n",temp->id);
    printf("prioridad %d \n", temp->priority);
    printf("Carreta %d \n", temp->carretaId);
    printf("Turno %d \n", temp->turnoCompra);
    printf("\n");
}

int getClientNumber(){
  int number;
  printf ("Ingresa el numero de Clientes");
  scanf ("%d", &number);
  return number;
}

void setClientsOnList(){
  int i = 0;
  int clientNumber = getClientNumber();
  for(i ; i < clientNumber ; i++){
    createClient(0);
  }
}

void createCitizensForPay(){
  int i;
  int city = getCitizen();
  for(i = 0 ; i < city ; i++){
    createClient(2);
  }
}

void createGoldenCitizens(){
  int i;
  int golden = getGoldenCitizen();
  for(i = 0 ; i < golden ; i++){
    enqueueForPayCiti(1, 65 ,3 , clientId++, 0, carrId++, -1);
  }
}

int main() {
  createStacksForCarretas();
  setClientsOnList();
  print();
  setClientsOnIQueue();
  printOnCircQueue();
  createGoldenCitizens();
  printG(goldenHead);
  createCitizensForPay();
  printG(cityHead);
  return 0;
}

