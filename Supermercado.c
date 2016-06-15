#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "Supermercado.h"

int carrId = 0;
int clientId = 0;
int clientWaiting = 0;
int noCaja = 0;
int noClients = 0;
int countStep = 0;
int graphFile = 0;
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
void printOnCircQueue(FILE * f){
    struct Node* temp = headCirc;
    if(temp != NULL)
    {
	while(temp->next != headCirc) {
	    printf("********\n");
	    printf("id %d \n",temp->id);
	    printf("edad %d \n", temp->age);
	    printf("prioridad %d \n", temp->priority);
	    printf("Carreta %d \n", temp->carretaId);
	    printf("Turno %d \n", temp->turnoCompra);
	    fprintf(f," Cliente%d, carreta%d turno%d, prioridad%d \n",
		    temp->id, temp->carretaId, temp->turnoCompra, temp->priority);
		    
	    temp = temp->next;
	    
	}
	if(temp != NULL){
	    printf("********\n");
	    printf("id %d \n",temp->id);
	    printf("prioridad %d \n", temp->priority);
	    printf("edad %d \n", temp->age);
	    printf("Carreta %d \n", temp->carretaId);
	    printf("Turno %d \n", temp->turnoCompra);
	    printf("\n");
	    fprintf(f," Cliente%d, carreta%d turno%d, prioridad%d \n",
		    temp->id, temp->carretaId, temp->turnoCompra, temp->priority);

	}
    }
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

void insertToPay(Node *nodo, FILE *f){
  if(nodo->priority == 1){
      fprintf(f,"Cliente%d pasando a cola de Normal \n",nodo->id);
    enqueueForPay(nodo->gender, nodo->age, nodo->pregnant, nodo-> id,
		      nodo->priority, nodo->carretaId,getRandom(3));
  }else{
            fprintf(f,"Cliente%d pasando a cola de pago Oro \n",nodo->id);
    enqueueForPayCiti(nodo->gender, nodo->age, nodo->pregnant, nodo-> id,
		      nodo->priority, nodo->carretaId,getRandom(3));
  }
  
}


struct Node* removeOnCircular(int turn, FILE *f){
    fprintf(f, "************ Clientes pasando a Cola de pago ************\n");
    printf("---------------------ENTER  ------------ \n");
    struct Node* current = headCirc;
    Node * prev;
    
   if(headCirc==NULL) {
      return;
   } 
   if(headCirc->turnoCompra == turn) {
      if(headCirc->next != headCirc) {
         current = headCirc;
         while(current->next!=headCirc) {
            current = current->next;
         }
	 insertToPay(headCirc,f);
         current->next = headCirc->next;
         headCirc = headCirc->next;
	 removeOnCircular(0,f);
         return;
      }else {
	  insertToPay(headCirc,f);
	  headCirc = NULL;
	 return;
      }
   }else if(headCirc->turnoCompra != turn && headCirc->next == NULL) {
      return;
   }
        
   current = headCirc;
   
   while(current->next != headCirc && current->turnoCompra != turn) {
      prev = current;
      current = current->next;
   }        

   if(current->turnoCompra == turn) {
      prev->next = prev->next->next;
      insertToPay(current, f);
      free(current);
      removeOnCircular(0,f);
   }


}

void print(FILE *f) {
  struct Node* temp = head;
  printf("Listado de clientes: ");
  fprintf(f, " ************ Listado de clientes en espera:************\n");
  while(temp != NULL) {
    printf("********\n");
    printf("id %d \n",temp->id);
    printf("edad%d \n", temp->age);
    printf("prioridad %d \n", temp->priority);
    printf("embarazado %d \n", temp->pregnant);
    printf("genero %d \n", temp->gender);
    fprintf(f,"Cliente%d prioridad%d\n",temp->id, temp->priority);
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

void printG(Node* goldenH,FILE *f) {
  struct Node* temp = goldenH;
  printf("Forward: ");
  while(temp != NULL) {
    printf("********\n");
    printf("id %d \n",temp->id);
    printf("edad%d \n", temp->age);
    printf("prioridad %d \n", temp->priority);
    printf("embarazado %d \n", temp->pregnant);
    printf("genero %d \n", temp->gender);
    fprintf(f,"Cliente%d, prioridad%d\n",temp->id, temp->priority);
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


void printStack(Carreta* stack,FILE *f) {
  struct Carreta* temp = stack;
  while(temp != NULL) {
    printf("\n********Carreta**********\n");
    printf("Carreta %d \n",temp->noCarreta);
    fprintf(f,"Carreta %d \n",temp->noCarreta);
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

void createClient(int flag, FILE *f){
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
      if(priority == 1)
      {insertAtTail(gender, age, pregnant, clientId++, priority);
		  }
	  else{insertMiddle(gender, age, pregnant, clientId++, priority);
	  }
  }
  if(flag == 1){
    int queueTurn = getRandom(5);
    addOnCircular(gender, age, pregnant, clientId++, priority,carrId++,queueTurn);
  }
  if(flag == 2){
    age = getRandom(59);
    if(pregnant == 1){pregnant = 0;}
    enqueueForPay(gender, age, pregnant, clientId++, 1,carrId++, -1);
  }
}

void setClientsOnIQueue(FILE *f){
  int i = 0;
  int perCompras = getPerCompras();
  for(i ; i < perCompras ; i++){
      createClient(1,f);
  }
}


void setClientsOnList(FILE *f){
  int i = 0;
  int clientNumber = getClientNumber();
  for(i ; i < clientNumber ; i++){
      createClient(0,f);
    clientWaiting++;
    printf("--------Esperando-------- %d \n",clientWaiting);
  }
}

void createCitizensForPay(FILE *f){
  int i;
  int city = getCitizen();
  for(i = 0 ; i < city ; i++){
      createClient(2,f);
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

  
void insertOnCircular(Node* person, FILE *f){
    int turn = getRandom(5);
  addOnCircular(person->gender, person->age, person->pregnant, person->id, person->priority,
		person->carretaId, turn);
  fprintf(f,"Cliente%d toma Carreta%d, pasa a comprar con turno %d \n",head->id, person->carretaId, turn); 
  
}

int getCarrNumber(){
    int ret = -1;
    if(headStack0 != NULL){
	if(headStack0->next==NULL){
	    ret = headStack0->noCarreta;
	    free(headStack0);
	    headStack0 = NULL;
	    return ret;
	}else{
	    struct Carreta * temp = headStack0->next;
	    ret = headStack0->noCarreta;
	    headStack0 = temp;
	    return ret;
	}
    }else{ret = -1;}
    //1
    if(headStack1 != NULL){
	if(headStack1->next==NULL){
	    ret = headStack1->noCarreta;
	    free(headStack1);
	    headStack1 = NULL;
	    return ret;
	}else{
	    struct Carreta * temp = headStack1->next;
	    ret = headStack1->noCarreta;
	    headStack1 = temp;
	    return ret;
	}
    }else{ret = -1;}
//2
    if(headStack2 != NULL){
	if(headStack2->next==NULL){
	    ret = headStack2->noCarreta;
	    free(headStack2);
	    headStack2 = NULL;
	    return ret;
	}else{
	    struct Carreta * temp = headStack2->next;
	    ret = headStack2->noCarreta;
	    headStack2 = temp;
	    return ret;
	}
    }else{ret = -1;}
//3
    if(headStack3 != NULL){
	if(headStack3->next==NULL){
	    ret = headStack3->noCarreta;
	    free(headStack3);
	    headStack3 = NULL;
	    return ret;
	}else{
	    struct Carreta * temp = headStack3->next;
	    ret = headStack3->noCarreta;
	    headStack3 = temp;
	    return ret;
	}
    }else{ret = -1;}

    return ret;
}

void asignCarreta(FILE * file){
    FILE * f = file;
    struct Carreta *stack;
    struct Node *temp;
    if(head != NULL){
	int carreta = getCarrNumber();
	if(carreta == -1){
	    printf("No hay carretas disponibles, cliente en espera \n");
	    return;
	}
	if(head->next != NULL){ temp = head->next;}
	else {temp = NULL;}
	head->carretaId = carreta;
	insertOnCircular(head, f);
	free(head);
	head = NULL;
	head = temp;
	clientWaiting--;
	printf("--------Esperando-------- %d \n",clientWaiting);
	printf("********terminando assign ******** %d \n",carreta);
    }else{
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

void iterateAsignCarreta(FILE *f){
    fprintf(f,"************ Asignacion Carreta ************ \n");
    int i = 0;
    while( i < carrId){
	asignCarreta(f);
	i++;
    }
}

void passingToCaja(FILE *f){
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
	fprintf(f,"Cliente%d pasa a caja No.%d con turno%d\n", client->id, temp->noCaja,
	    temp->turno);
	passingToCaja(f);
    }
}

void releaseCarreta(Caja * toRelease, FILE *f){
    printf("entrando en release \n");
    struct Caja *temp = toRelease;
    switch(getRandom(4)){
    case 0:
	if(temp->noCarreta != -1)
	insertAtStack(temp->noCarreta, 0 , headStack0);
	fprintf(f,"Cliente%d paga, se libera carreta No.%d en pila %d \n",
		temp->noCliente,temp->noCarreta, 0);
	printf("Cliente%d paga, se libera carreta No.%d en pila %d \n",
		temp->noCliente,temp->noCarreta, 0);
	
	temp->noCliente = -1;
	temp->clients = 0;
	temp->turno = -1;
	temp->available = 0;
	temp->noCarreta = -1;
	break;
    case 1:
	if(temp->noCarreta != -1)
	insertAtStack(temp->noCarreta, 1 , headStack1);
	fprintf(f,"Cliente%d paga, se libera carreta No.%d en pila %d\n",
		temp->noCliente,temp->noCarreta, 1);
	printf("Cliente%d paga, se libera carreta No.%d en pila %d \n",
		temp->noCliente,temp->noCarreta, 0);
	temp->noCliente = -1;
	temp->clients = 0;
	temp->turno = -1;
	temp->available = 0;
	temp->noCarreta = -1;
	break;
    case 2:
	if(temp->noCarreta != -1)
	insertAtStack(temp->noCarreta, 2 , headStack2);
	fprintf(f,"Cliente%d paga, se libera carreta No.%d en pila %d \n",
		temp->noCliente,temp->noCarreta, 2);
		printf("Cliente%d paga, se libera carreta No.%d en pila %d \n",
		temp->noCliente,temp->noCarreta, 0);
	temp->noCliente = -1;
	temp->clients = 0;
	temp->turno = -1;
	temp->available = 0;
	temp->noCarreta = -1;
	break;
    case 3:
	if(temp->noCarreta != -1)
	insertAtStack(temp->noCarreta, 3 , headStack3);
	fprintf(f,"Cliente%d paga, se libera carreta No.%d en pila%d\n",
		temp->noCliente,temp->noCarreta,3);
		printf("Cliente%d paga, se libera carreta No.%d en pila %d \n",
		temp->noCliente,temp->noCarreta, 0);
	temp->noCliente = -1;
	temp->clients = 0;
	temp->turno = -1;
	temp->available = 0;
	temp->noCarreta = -1;
	break;
    }
    printf("saliendo release \n");
}

void moveTurnoCompra(){
    struct Node* temp = headCirc;
    while(temp!= NULL && temp->next != headCirc) {
	if( temp->turnoCompra > 0)
	{
	    int tempTurn = temp->turnoCompra -1;
	    temp->turnoCompra = tempTurn;
	}
	temp = temp->next;
    }
    if(temp!=NULL && temp->turnoCompra > 0){
	int tempTurn = temp->turnoCompra -1;
	temp->turnoCompra = tempTurn;
	printf("\n");
    }
} 

void moveTurnoCaja(FILE *f){
    fprintf(f,"************ Clientes pagando ************ \n");
    struct Caja* temp = cajaHead;
    struct Caja* aux;
    while(temp!= NULL && temp->next != NULL) {
	printf("ciclo \n");
	if(temp->turno == 0){
	    printf("validated \n");
	    releaseCarreta(temp,f);
	}else{
	    if(temp->turno > 0){
		int prevTurno = temp->turno;
		temp->turno = prevTurno - 1;
	    }
	    temp = temp->next;
	}
   }
}

void graphStacks(Carreta* stack,FILE * file, int i){
    FILE *f = file;
    struct Carreta* temp = stack;
    printf("pilas\n");
    fprintf(f, "subgraph cluster%d {\n",i);
    if(temp != NULL && temp->next == NULL){
	printf("1\n");
	fprintf(f, " %d ;\n", temp->noCarreta);
    }
    while(temp!=NULL && temp->next != NULL) {
	printf("varios\n");
	fprintf(f, " %d ", temp->noCarreta);
	temp = temp->next;
	fprintf(f, "-> %d ;\n",temp->noCarreta);
    }
    printf("fin pilas\n");
    fprintf(f,"label = \" Pila no %d \" ; \n",i);
    fprintf(f, "}\n");
}

void graphColaCliente(FILE * file){
    printf("grapCola cliente\n");
    FILE *f = file;
    struct Node* temp = head;
    fprintf(f, "subgraph cluster4 {\n");
    if(temp != NULL && temp->next ==  NULL){
	fprintf(f, "Cliente%d ; \n",temp->id);
    }
    while(temp != NULL && temp->next != NULL) {
	fprintf(f, "Cliente%d",temp->id);	
	fprintf(f,"->");
	temp = temp->next;
	fprintf(f,"Cliente%d\n", temp->id);	
    }
    fprintf(f, "label = \" Cola Clientes \"\n");
    fprintf(f,"}\n");
}

void graphPersonasCompras(FILE *file){
    FILE *f = file;
    struct Node* temp = headCirc;
    printf("Personas compras\n");
    fprintf(f, "subgraph cluster5 {\n");
    if(temp != NULL)
    {
	while(temp->next != headCirc) {
	    int previous = temp->id;
	    fprintf(f,"node%d[label = \"Cliente%d \\n Carreta %d \\n turno %d \"];\n",
		    temp->id, temp->id, temp->carretaId, temp->turnoCompra); 
	    temp = temp->next;
	    fprintf(f,"node%d[label =\" Cliente%d \\n Carreta %d \\n turnoCompra %d\"];\n",
		    temp->id, temp->id, temp->carretaId, temp->turnoCompra); 
	    fprintf(f,"node%d",previous);
	    fprintf(f,"->");
	    fprintf(f,"node%d; \n",temp->id);
	}
	if(temp != NULL){
	    int previous = temp->id;
	    fprintf(f,"node%d[label = \"Cliente%d \\n Carreta %d \\n turno %d\"];\n",
		    temp->id, temp->id, temp->carretaId, temp->turnoCompra); 
	    temp = temp->next;
	    fprintf(f,"node%d[label =\" Cliente%d \\n Carreta %d \\n turno %d\"];\n",
		    temp->id, temp->id, temp->carretaId,temp->turnoCompra); 
	    fprintf(f,"node%d",previous);
	    fprintf(f,"->");
	    fprintf(f,"node%d; \n",temp->id);
	}
    }
    fprintf(f, "label = \" Lista personas comprando \"\n");
    fprintf(f,"}\n");
    
}

void graphColasToPay(FILE *file, Node *queue,int flag){
    printf("colas para pagar\n");
    FILE *f = file;
    struct Node* temp = queue;
    int i = 6 + flag;
    fprintf(f, "subgraph cluster%d {\n",i);
    if(temp != NULL && temp->next ==  NULL)
	fprintf(f, "Cliente%d ; \n",temp->id);
    while(temp != NULL && temp->next != NULL) {
	fprintf(f, "Cliente%d",temp->id);
	fprintf(f,"->");
	temp = temp->next;
	fprintf(f,"Cliente%d\n", temp->id);	
    }
    if(flag == 0)
	fprintf(f, "label = \" Cola Clientes oro para pagar\"\n");
    else
	fprintf(f, "label = \" Cola Clientes para pagar \"\n");
    fprintf(f,"}\n");
}

void graphCajas(FILE *file){
    FILE *f = file;
    struct Caja* temp = cajaHead;
    const char *libre = "libre";
    const char *ocup = "ocupada";
    fprintf(f, "subgraph cluster8{\n");
    if(temp != NULL && temp->next == NULL){
	if(temp->available == 0){
	    fprintf(f,"Node%d[label = \"Caja%d \\n  %s %d\"];\n",
		    temp->noCaja, temp->noCaja, libre);
	}
	else{
	    fprintf(f,"Node%d[label = \"-Caja%d \\n - %s \\n Turno %d \"];\n",
		    temp->noCaja, temp->noCaja, ocup, temp->turno);
	}
    }
    while(temp != NULL && temp->next != NULL) {
	int previous = temp->noCaja;
	if(temp->available == 0)
	    fprintf(f,"Node%d[label = \"-Caja%d \\n  %s\"];\n",
		    temp->noCaja, temp->noCaja, libre);
	else
	    fprintf(f,"Node%d[label = \"-Caja%d \\n - %s \\n Turno %d \"];\n",
		    temp->noCaja, temp->noCaja, ocup, temp->turno);    
	temp = temp->next;
	int actual  = temp->noCaja;
	if(temp->available == 0)
	    fprintf(f,"Node%d[label = \"-Caja%d \\n - %s \"];\n",
		    temp->noCaja, temp->noCaja, libre);
	else
	     fprintf(f,"Node%d[label = \"-Caja%d \\n - %s \\n Turno %d \"];\n",
		    temp->noCaja, temp->noCaja, ocup, temp->turno);
	fprintf(f,"Node%d",previous);
	fprintf(f,"->");
	fprintf(f,"Node%d ; \n",actual);
	fprintf(f,"Node%d",actual);
	fprintf(f,"->");
	fprintf(f,"Node%d ; \n",previous);
    }
    fprintf(f, "label = \" Cajas \"\n");
    fprintf(f,"}\n");
}

void writeLogCajas(FILE *file){
    struct Caja* temp = cajaHead;
    const char *libre = "libre";
    const char *ocup = "ocupada";
    if(temp != NULL && temp->next == NULL){
	if(temp->available == 0){
	    fprintf(file,"Caja%d  %s\n", temp->noCaja, libre);
	}
	else{
	    fprintf(file,"Caja%d   %s  Turno %d Cliente%d\n", temp->noCaja, ocup, temp->turno, temp->noCliente);
	}
    }
    while(temp != NULL && temp->next != NULL) {
	if(temp->available == 0){
	    fprintf(file,"Caja%d   %s\n", temp->noCaja, libre);
	}
	else{
	    fprintf(file,"Caja%d  %s \\n Turno %d Cliente%d\n", temp->noCaja, ocup, temp->turno, temp->noCliente);
	}
	temp = temp->next;
        
    }
}

void graph(){
    FILE *file = fopen("file.dot", "w");
    if (file == NULL)
    {
	printf("Error opening file!\n");
	exit(1);
    }
    fprintf(file, "digraph G { \n");
    graphStacks(headStack0, file, 0);
    graphStacks(headStack1, file, 1);
    graphStacks(headStack2, file, 2);
    graphStacks(headStack3, file, 3);
    graphColaCliente(file);
    graphPersonasCompras(file);
    graphColasToPay(file, goldenHead, 0);
    graphColasToPay(file, cityHead, 1);
    graphCajas(file);
    fprintf(file, "} \n");    
    fclose(file);
}

void printLog(){
}

void compileDot(){
    system("dot -Tjpg file.dot -o file.jpg");
    system("xdg-open file.jpg");
}

void createInitials(FILE *f){
    fprintf(f, "\n************************************\n");
    fprintf(f, "*        Parametros iniciales      *\n");
    fprintf(f, "************************************\n");
    createCarretas();
    printf("************ pila 1 ************");
    fprintf(f,"************ pila 0 ************\n");
    printStack(headStack0,f);
    fprintf(f,"************ pila 1 ************\n");
    printf("************ pila 2 ************");
    printStack(headStack1,f);
    fprintf(f,"************ pila 2 ************\n");
    printf("************ pila 3 ************");
    printStack(headStack2,f);
    fprintf(f,"************ pila 3 ************\n");
    printf("************ pila 4 ************"); 
    printStack(headStack3,f);
    setClientsOnList(f);
    print(f);
    setClientsOnIQueue(f);
    fprintf(f,"************ Clientes de Compras ************\n");
    printOnCircQueue(f);
    fprintf(f,"************ Clientes en cola de Oro ************\n");
    createGoldenCitizens(f);
    printG(goldenHead,f);
    fprintf(f,"************ Clientes en Cola normal ************\n");
    createCitizensForPay(f);
    printG(cityHead,f);
    fprintf(f,"************ Cajas ************\n");
    iterateCreateCaja();
    writeLogCajas(f);
    printC(cajaHead);
    graph();
    compileDot();
}

void step(FILE *f){
    iterateAsignCarreta(f);
    fprintf(f,"************ Clientes de compras ************\n");
    printOnCircQueue(f);
    removeOnCircular(0,f);
    moveTurnoCompra();
    fprintf(f,"************ Cola de clientes de oro ************\n");
    printG(goldenHead,f);
    fprintf(f,"************ Cola de clients normal ************\n");
    printG(cityHead,f);
    fprintf(f, "************ Clientes pasando a Caja ************\n");
    passingToCaja(f);
    fprintf(f, "************ Cajas ************\n");
    writeLogCajas(f);
    moveTurnoCaja(f);
    printC(cajaHead);
    graph();
    compileDot();
}
void doStep(int number, FILE * file){
    if(number == 1){
	if( countStep == 0 ){
	    fprintf(file, "\n***********************************\n");
	    fprintf(file, "*            Paso %d               *\n",countStep);
	    fprintf(file, "************************************\n");
	    step(file);
	    countStep++;
	    return;
	}
	fprintf(file, "\n************************************\n");
	fprintf(file, "*            Paso %d                *\n",countStep);
	fprintf(file, "************************************\n");
	setClientsOnList(file);
	print(file);
	step(file);
	countStep++;
    }
}

void getStep(FILE *file){
    int number = 0;
    printf("Ingresa uno y enter para dar paso, cualquier otro para salir");
    scanf("%d",&number);
    if(number == 1){
	doStep(1,file);
	getStep(file);
    }else{
	exit(0);
    }
}

int main() {
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
	printf("Error opening file!\n");
	exit(1);
    }
    createInitials(file);
    getStep(file);
    	fclose(file);
  return 0;
}
