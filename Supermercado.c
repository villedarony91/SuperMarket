#include <stdio.h>
#include <stdlib.h>

int getNumCarretas(){
  int number;
  printf ("Ingresa el numero de carretillas ");
  scanf ("%d", &number);
  printf ("You entered: %d \n", number);
  return number;

}

typedef struct Carreta
{
  int *noCarreta;
  int size;
  int capacity;
    
}Carreta;

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

int main() {
  createStacksForCarretas();
  return 0;
}









