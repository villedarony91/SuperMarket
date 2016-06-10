#include <stdio.h>
#include <stdlib.h>

typedef struct Carreta
{
  int *noCarreta;
  int size;
  int capacity;
    
}Carreta;


typedef struct Node  {
  int gender;
  int age;
  int pregnant;
  int id;
  int priority;
  int turnoCompra;
  int turnoCaja;
  struct Node* next;
  struct Node* prev;
}Node;




