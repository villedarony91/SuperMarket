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
        /* Create a Stack */
        Carreta *S;
        S = (Carreta *)malloc(sizeof(Carreta));
        /* Initialise its properties */
        S->noCarreta = (int *)malloc(sizeof(int)*maxElements);
        S->size = 0;
        S->capacity = maxElements;
        /* Return the pointer */
        return S;
}

void pop(Carreta *S)
{
        /* If stack size is zero then it is empty. So we cannot pop */
        if(S->size==0)
        {
                printf("Stack is Empty\n");
                return;
        }
        /* Removing an element is equivalent to reducing its size by one */
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
        /* Return the topmost element */
        return S->noCarreta[S->size-1];
}
void push(Carreta *S,int noCarreta)
{
        /* If the stack is full, we cannot push an element into it as there is no space for it.*/
        if(S->size == S->capacity)
        {
                printf("Stack is Full\n");
        }
        else
        {
                /* Push an element on the top of it and increase its size by one*/ 
                S->noCarreta[S->size++] = noCarreta;
        }
        return;
}

int main() {
    Carreta *S = createStackCarr(getNumCarretas());
        push(S,7);
        push(S,5);
        push(S,21);
        push(S,-1);
        printf("Top element is %d\n",top(S));
        pop(S);
        printf("Top element is %d\n",top(S));
        pop(S);
        printf("Top element is %d\n",top(S));
        pop(S);
        printf("Top element is %d\n",top(S));
  return 0;

}









