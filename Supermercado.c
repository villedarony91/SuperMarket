#include <stdlib.h>
#include "Supermercado.h"

int carrId = 0;
int clientId = 0;
int clientWaiting = 0;
int noCaja = 0;
int noClients = 0;
struct Carreta* headStack0;
struct Carreta* headStack1;
struct Carreta* headStack2;
struct Carreta* headStack3;
struct Node* head;
struct Node* headQ;
struct Node* headCirc;
struct Node* goldenHead;
struct Node* cityHead;
struct Caja* cajaHead;


struct Carreta* getNewCarr(int carreta){
  struct Carreta* newNode = (struct Carreta*)malloc(sizeof(struct Carreta));
  newNode->noCarreta = carreta;
  newNode->next = NULL;
  newNode->prev = NULL;			    
}

void insertAtStack(int carreta, int stackNo, Carreta *stack) {
  struct Carreta* newNode = getNewCarr(carreta);
  if(stack == NULL) {
    stack = newNode;
  }else{
  stack->prev = newNode;
  newNode->next = stack;
  }
  switch(stackNo){
  case 0:
    headStack0 = newNode;
    break;
  case 1:
    headStack1 = newNode;
    break;
  case 2:
    headStack2 = newNode;
    break;
  case 3:
    headStack3 = newNode;
    break;
  }
}

void createCarretas(){
  int i;
  int carrNum = getNumCarretas();
  for( i = 0; i < carrNum ; i++){
    switch(getRandom(4)){
    case 0:
      insertAtStack(carrId++, 0, headStack0);
      break;
    case 1:
      insertAtStack(carrId++, 1, headStack1);
      break;
    case 2:
      insertAtStack(carrId++, 2, headStack2);
      break;
    case 3:
      insertAtStack(carrId++, 3, headStack3);
      break;
    }
  }
}
void printOnCircQueue(){
  struct Node* temp = headCirc;
  while(temp->next != headCirc) {
    printf("********\n");
    printf("id %d \n",temp->id);
    printf("edad %d \n", temp->age);
    printf("prioridad %d \n", temp->priority);
    printf("Carreta %d \n", temp->carretaId);
    printf("Turno %d \n", temp->turnoCompra);
    temp = temp->next;
  }
    printf("********\n");
    printf("id %d \n",temp->id);
    printf("prioridad %d \n", temp->priority);
    printf("edad %d \n", temp->age);
    printf("Carreta %d \n", temp->carretaId);
    printf("Turno %d \n", temp->turnoCompra);
    printf("\n");
}
struct Node* getNewNodeCirc(int gen, int ag, int preg, int id, int prior,int carreta, int turnQ){
  struct Node* newNode
    = (struct Node*)malloc(sizeof(struct Node));
  newNode->gender = gen;
  newNode->age = ag;
  newNode->pregnant = preg;
  newNode->id = id;
  newNode->priority = prior;
  newNode->turnoCompra = turnQ;
  newNode->carretaId = carreta;
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}

struct Node* getNewNode(int gen, int ag, int preg, int id, int prior){
  struct Node* newNode
    = (struct Node*)malloc(sizeof(struct Node));
  newNode->gender = gen;
  newNode->age = ag;
  newNode->pregnant = preg;
  newNode->id = id;
  newNode->priority = prior;
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}
void enqueueForPayCiti(int gen, int ag, int preg, int id, int prior,
		   int carreta, int turnQ){
  struct Node* temp = goldenHead;
  struct Node* newNode = getNewNodeCirc(gen, ag , preg, id, prior, carreta, turnQ);
  if(goldenHead == NULL) {
    goldenHead = newNode;
    return;
  }
  while(temp->next != NULL) temp = temp->next;
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
  while(temp->next != NULL) temp = temp->next;
  temp->next = newNode;
  newNode->prev = temp;
}

void insertToPay(Node *nodo){
  if(nodo->priority == 1){
    enqueueForPay(nodo->gender, nodo->age, nodo->pregnant, nodo-> id,
		      nodo->priority, nodo->carretaId,getRandom(3));
  }else{
    enqueueForPayCiti(nodo->gender, nodo->age, nodo->pregnant, nodo-> id,
		      nodo->priority, nodo->carretaId,getRandom(3));
  }
  
}


struct Node* removeOnCircular(int turn){
  printf("---------------------ENTER  ------------ \n");
  struct Node* temp = headCirc;
  struct Node* previous=headCirc;
  struct Node* retorno;

  while(temp->next != headCirc){
    if(temp == headCirc) temp = temp->next;
    if(temp->turnoCompra == turn){
      previous->next=temp->next;
      retorno = temp;
      free(temp);
      temp = NULL;
      printf("---------------------FOUND  ------------ %d \n", retorno->turnoCompra);
      insertToPay(retorno);
      temp=previous;
    }
    previous = temp;
    temp = temp->next;
  }
  // printOnCircQueue();
  if( temp->next == headCirc && temp->turnoCompra == turn){
      printf("----------HEADING--------- %d \n",headCirc->age);
      printf("----------FINAL--------- %d \n", temp->age);
      printf("----------FINAL--------- %d \n", previous->age);
      previous->next = NULL;
      previous->prev = NULL;
      retorno = temp;
      insertToPay(retorno);
      free(temp);
      temp = NULL;
      previous->next = headCirc;
      
    }
	/*printOnCircQueue();
      if(headCirc->turnoCompra == turn){
	printf("----------HEAD--------- %d \n", headCirc->age);
      temp = headCirc;
      temp = temp->next;
      headCirc = temp;
      free(temp);
      temp = NULL;
      printf("----------HEADING---------* %d \n",headCirc->age);
      //printf("----------FINAL---------* %d \n", temp->age);
      //      printf("----------FINAL---------* %d \n", previous->age);
      }*/
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

void insertAtTail(int gen, int ag, int preg, int id, int prior) {
  struct Node* temp = head;
  struct Node* newNode = getNewNode(gen, ag , preg, id, prior);
  if(head == NULL) {
    head = newNode;
    return;
  }

  while(temp->next != NULL) temp = temp->next;
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

void printC(Caja* goldenH) {
  struct Caja* temp = goldenH;
  printf("Forward: ");
  while(temp != NULL) {
    printf("********\n");
    printf("caja Id %d \n",temp->noCaja);
    printf("cliente %d \n", temp->clients);
    printf("disponible %d \n", temp->available);
    printf("no cliente %d \n", temp->noCliente);
    printf("turno %d \n", temp->turno);
    printf("carreta %d \n", temp->noCarreta);
    temp = temp->next;
  }
  printf("\n");
} 


void printStack(Carreta* stack) {
  struct Carreta* temp = stack;
  while(temp != NULL) {
    printf("\n********Carreta**********\n");
    printf("Carreta %d \n",temp->noCarreta);
    temp = temp->next;
  }
  printf("\n");
} 


void addOnCircular(int gen, int ag, int preg, int id, int prior, int numCarreta, int turnCir){
  struct Node* temp = headCirc;
  struct Node* newNode = getNewNodeCirc(gen, ag , preg, id, prior, numCarreta,turnCir);
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
    addOnCircular(gender, age, pregnant, clientId++, priority,carrId++,queueTurn);
    printf("added");
  }
  if(flag == 2){
    age = getRandom(59);
    if(pregnant == 1){pregnant = 0;}
    enqueueForPay(gender, age, pregnant, clientId++, 1,carrId++, -1);
  }
}

void setClientsOnIQueue(){
  int i = 0;
  int perCompras = getPerCompras();
  for(i ; i < perCompras ; i++){
    createClient(1);
  }
}


void setClientsOnList(){
  int i = 0;
  int clientNumber = getClientNumber();
  for(i ; i < clientNumber ; i++){
    createClient(0);
    clientWaiting++;
    printf("--------Esperando-------- %d \n",clientWaiting);
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


struct Node* getClient(){
  if(head == NULL){printf("No hay clientes en espera");}
  else{
    return head;
  }
}

void pop(Carreta *stack, int stackNo){
  printf("POOOOP \n");
  struct Carreta *temp;
  if(stack->next != NULL){
    temp = stack->next;}
  temp = NULL;
  switch(stackNo){
  case 0:
    free(headStack0);
    headStack0 = NULL;
    headStack0 = temp;
    break;
  case 1:
    free(headStack1);
    headStack1 = NULL;
    headStack1 = temp;
    break;
  case 2:
    free(headStack2);
    headStack2 = NULL;
    headStack2 = temp;
    break;
  case 3:
    free(headStack3);
    headStack3 = NULL;
    headStack3 = temp;
    break;
  }
    printf("POOOOP TERMINADO\n");
}

int getCarrId(Carreta *stack){
  struct Carreta* temp = stack;
  return stack->noCarreta;
}

int getStackNo(){
    printf("getting stack NO \n");
  if(headStack0 != NULL) return 0;
  if(headStack1 != NULL) return 1;
  if(headStack2 != NULL) return 2;
  if(headStack3 != NULL) return 3;
  return -1;
}

struct Carreta* getStack(int stackNo){
  printf("getting stack \n");
  switch(stackNo){
  case 0:
    return headStack0;
    break;
  case 1:
    return headStack1;
    break;
  case 2:
    return headStack2;
    break;
  case 3:
    return headStack3;
    break;
  }
  return NULL;
}
  
void insertOnCircular(Node* person){
  addOnCircular(person->gender, person->age, person->pregnant, person->id, person->priority,
		person->carretaId, getRandom(5));
  
}
void asignCarreta(){
  int stackId = getStackNo();
  struct Carreta *stack;
  struct Node *temp;
  if(stackId != -1 && head != NULL){
    stack = getStack(stackId);
    int carreta = getCarrId(stack);
    printf("********imprimiendo numero ******** %d",carreta);
    pop(stack, stackId);
    printf("********imprimiendo numero ******** %d",carreta);
    if(head->next != NULL){ temp = head->next;}
    else {temp = NULL;}
    head->carretaId = carreta;
    insertOnCircular(head);
    free(head);
    head = NULL;
    head = temp;
    clientWaiting--;
        printf("--------Esperando-------- %d \n",clientWaiting);
        printf("********terminando assign ******** %d \n",carreta);
  }else{
      if(head != NULL)
      {printf("No hay carretas disponibles, cliente en espera \n");}
      if(stackId != -1)
      {printf("Clientes agotados, carreta en espera \n");}
  }
}

struct Node *getQueueToPay(){
    if(goldenHead != NULL) return goldenHead;
    if(cityHead != NULL) return cityHead;
    return NULL;
}

struct Node* getClientToPay(){
    struct Node* temp = getQueueToPay();
    struct Node* aux = temp;
    struct Node* previous = temp;
    struct Node* retorno;
    if(getQueueToPay() == NULL) return NULL;
    //if(temp->next != NULL)
    temp = temp->next;
    if(aux == goldenHead){
	retorno = goldenHead;
	goldenHead = temp;
	free(previous);
	previous = NULL;
    } else{
	retorno = cityHead;
	cityHead = temp;
	free(previous);
	previous = NULL;
    }
    return retorno;
}


struct Caja *getNewCaja(int noCaja, int clients, int available, int noCliente, int turno, int noCarreta){
    struct Caja* newNode = (struct Caja*)malloc(sizeof(struct Caja));
    newNode->noCaja = noCaja;
    newNode->clients= clients;
    newNode->available = available;
    newNode->noCliente = noCliente;
    newNode->turno = turno;
    newNode->noCarreta = noCarreta;
    printf("finish creating \n");
    return newNode;
}

struct Caja* createDoubleCaja(){
    struct Caja* node = getNewCaja(noCaja++, noClients, 0, -1, -1, -1);
    printf("finish double Caja \n");
    return node;
}

void createListCaja(){
    printf("HEAD");
    struct Caja* newNode = createDoubleCaja();
    struct Caja* temp = cajaHead;
    if(cajaHead == NULL){
	cajaHead = newNode;
    }else{
	while(temp->next != NULL)temp = temp->next;
	temp->next = newNode;
	newNode->prev = temp;
	cajaHead = cajaHead;
    }
    
}

void iterateCreateCaja(){
    int i = 0;
    int cajas = getNoCajas();
    for( i; i < cajas ; i++){
	createListCaja();
    }
    printf("finish Creation \n");
}

void iterateAsignCarreta(){
    int i = 0;
    while( i < carrId){
	asignCarreta();
	i++;
    }
}

void passingToCaja(){
    struct Caja* temp = cajaHead;
    struct Node* client = getClientToPay();
    if(client == NULL){
	printf("No Hay clientes en espera\n");
	return;
    }
    while(temp->available != 0 && temp->next != NULL) {
	temp = temp->next;
    }
    if(temp->next == NULL && temp->available != 0){
	printf("No hay cajas disponibles cliente en espera \n");
	    return;
    }else{
	printf("empiezan a pasar \n");
    temp->clients = 0;
    temp->noCliente = client->id;
    temp->noCarreta = client->carretaId;
    temp->turno = getRandom(3);
    temp->available = 1;
    passingToCaja();
    }
}

void createInitials(){
  createCarretas();
  printf("************ pila 1 ************");
  printStack(headStack0);
  printf("************ pila 2 ************");
  printStack(headStack1);
  printf("************ pila 3 ************");
  printStack(headStack2);
  printf("************ pila 4 ************"); 
  printStack(headStack3);
  setClientsOnList();
  print();
  setClientsOnIQueue();
  printOnCircQueue();
  createGoldenCitizens();
  printG(goldenHead);
  createCitizensForPay();
  printG(cityHead);
  printG(cityHead);
  iterateCreateCaja();
  printC(cajaHead);
}
void releaseCarreta(Caja * toRelease){
    printf("entrando en release \n");
    struct Caja *temp = toRelease;
    switch(getRandom(4)){
    case 0:
	insertAtStack(temp->noCarreta, 0 , headStack0);
	temp->noCliente = -1;
	temp->clients = 0;
	temp->turno = -1;
	temp->available = 0;
	temp->noCarreta = -1;
    case 1:
	insertAtStack(temp->noCarreta, 1 , headStack1);
	temp->noCliente = -1;
	temp->clients = 0;
	temp->turno = -1;
	temp->available = 0;
	temp->noCarreta = -1;
    case 2:
	insertAtStack(temp->noCarreta, 2 , headStack2);
	temp->noCliente = -1;
	temp->clients = 0;
	temp->turno = -1;
	temp->available = 0;
	temp->noCarreta = -1;
    case 3:
	insertAtStack(temp->noCarreta, 3 , headStack3);
	temp->noCliente = -1;
	temp->clients = 0;
	temp->turno = -1;
	temp->available = 0;
	temp->noCarreta = -1;
    }
    printf("saliendo release \n");
}

void moveTurnoCompra(){
    struct Node* temp = headCirc;
    while(temp->next != headCirc) {
	if( temp->turnoCompra > 0)
	{
	    int tempTurn = temp->turnoCompra -1;
	    temp->turnoCompra = tempTurn;
	}
	temp = temp->next;
    }
    if(temp->turnoCompra > 0){
	int tempTurn = temp->turnoCompra -1;
	temp->turnoCompra = tempTurn;
	printf("\n");
    }
} 

void moveTurnoCaja(){
    struct Caja* temp = cajaHead;
    struct Caja* aux;
    while(temp->next != NULL) {
	printf("ciclo \n");
	if(temp->turno == 0){
	    printf("validated \n");
	    releaseCarreta(temp);
	}else{
	    if(temp->turno > 0){
		int prevTurno = temp->turno;
		temp->turno = prevTurno - 1;
	    }
	    temp = temp->next;
	}
   }
}


int main() {
  createInitials();
  print();
  printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
  setClientsOnList();
  print();
  /*iterateAsignCarreta();
  printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
  print();
  printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx \n");
  printOnCircQueue();
  removeOnCircular(0);
  printOnCircQueue();
  printf("************************************* \n");
  moveTurnoCompra();
  printOnCircQueue();
   printG(goldenHead);
   passingToCaja();
   printC(cajaHead);*/
  // printG(goldenHead);
  // printG(cityHead);
//   moveTurnoCaja();
//   printC(cajaHead);
  return 0;
}

