#include <iostream>
#include <stdlib.h>
#include <malloc.h>

//#define QMAX 100


class stack {
	public: 
  	int *qu;
  	int last, first;
  	int QMAX;
  	int count;
  	
  	stack(); //конструктор класса
  	stack(int QM); //конструктор класса
  	void init(int N);
	bool empty();
	bool full();
	bool insert(int x);
	void print();
	bool remove();
	void printFirst();
	
};

stack::stack()
{
	qu = NULL;
}

stack::stack(int QM)
{
	qu = NULL;
	init(QM);
}


void stack::init(int N) {
	QMAX = N;
	qu = (int*)malloc(sizeof(int)*QMAX);
	last = -1;
	count=0;
  return;
}

bool stack::empty() {
  	if(count==0)    return true;
  	else  return false;
}

bool stack::full(){
	if(count==QMAX)return true;
	else return false;
}

bool stack::insert(int x){
	if(!full()) {
	if(last==QMAX-1)
		last=0;
	else
		last++;
    qu[last]=x;
    count++;
    return true;
  	}
  else
  	{
  return false;
	}
}

void stack::print() {
  int i;
  if(empty()==true) {
    printf("Stack is empty!\n");
  }
  else{
  	int k;
  	if(first<=last)
    for(i = first, k=1; i<=last; i++,k++)
   		printf("N %i- element %d\n",k,qu[i]);
  	else{
		for(i = first, k=1; i<QMAX; i++,k++)
	   		printf("N %i- element %d\n",k,qu[i]);
	  	for(i = 0; i<=last; i++,k++)
	   		printf("N %i- element %d\n",k,qu[i]);
		}
  	
  }
  return;
}

bool stack::remove() {
	if(empty()==true) {
    	printf("Stack is empty!\n");
    	return false;
	}	
	else{
		last--;
    	count--;
	return true;
	}
}

void  stack::printFirst() {
  int i;
  if(empty()==true) {
    printf("Stack is empty!\n");
  }
  else{
    printf("Top element in stack:%d \n",qu[last]);
  }
return;}

bool menu(class stack *q, int N){
	int x;
	switch(N){
		case 1:
			if(q->qu!=NULL){
			   free(q->qu);
		       }
	
			printf("Input size of stack\n");
  			scanf("%d",&N);
			q->init(N);
			break;
		case 2: 
			printf("Input element: \n");
			scanf("%d",&x);
			if(q->insert(x)==false)
				printf("Stack is full!\n"); 
			
			break;
		case 3: 
			q->remove();
			break;
		case 4: 
			q->print();
			break;
		case 5:	
			q->printFirst();
			break;
		case 0:
			return false;
			//break;
		default:
			printf("input correct number\n");
		}
return true;
}

int main() {
  	int count,N,m;
  	//class stack q=stack(5);
  	class stack *q;
  	
  	q = new stack;
  	
  	int a=-2;
    
	printf("Input number for action:\n");
	printf("1 - restart stack\n");
	printf("2 - add element in stack\n");
	printf("3 - remove 1st element from stack\n");
	printf("4 - show stack\n");
	printf("5 - show 1st element of stack\n");
	printf("0 - finish\n");

  do {
  	scanf("%d", &a);
  }while(menu(q, a)==true);

  delete q;
  
  return 0;
}
