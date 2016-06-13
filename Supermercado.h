#include <stdio.h>
#include <stdlib.h>

typedef struct Carreta
{
  int noCarreta;
  struct Carreta* next;
  struct Carreta* prev;    
}Carreta;


typedef struct Node  {
  int gender;
  int age;
  int pregnant;
  int id;
  int priority;
  int carretaId;
  int turnoCompra;
  int turnoCaja;
  struct Node* next;
  struct Node* prev;
}Node;

typedef struct Caja{
  int noCaja;
  int clients;
  int available;
  int noCliente;
  int turno;
  int noCarreta;
  struct Caja* next;
  struct Caja* prev;
}Caja;

int getClientNumber(){
int number;
  printf ("Ingresa el numero de clientes");
  scanf ("%d", &number);
  return number;
}  

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

int getNoCajas(){
  int number;
  printf ("Ingresa el numero de Cajas");
  scanf ("%d", &number);
  return number;
}


int getRandom(int max){
  return rand() % max;
}


