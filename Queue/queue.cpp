#include <iostream>
#include <stdlib.h>
#include <malloc.h>

//#define QMAX 100


class queue {
	public: 
  	int *qu;
  	int last, first;
  	int QMAX;
  	int count;
  	
  	queue(); //конструктор класса
  	void init(int N);
	bool empty();
	bool full();
	bool insert(int x);
	void print();
	bool removeN(int remelem);
	bool remove();
	void printFirst();
	
};

queue::queue()
{
	qu = NULL;
}

void queue::init(int N) {
	QMAX = N;
	qu = (int*)malloc(sizeof(int)*QMAX);
	first = 0;
	last = -1;
	count=0;
  return;
}

bool queue::empty() {
  	if(count==0)    return true;
  	else  return false;
}

bool queue::full(){
	if(count==QMAX)return true;
	else return false;
}
// last - индекс последнего заполненного элемента массива
bool queue::insert(int x){
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
  //printf("Queue is full!\n");
  	return false;
	}
}

void queue::print() {
  int i;
  if(empty()==true) {
    printf("Queue is empty!\n");
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

bool queue::removeN(int remelem) {
  int x, i;
  if(empty()==true) {
    printf("Queue is empty!\n");
    return false;
  }
  for(i = remelem; i < last; i++) {
    qu[i] = qu[i+1];
  }
  last--;
  return true;
}


bool queue::remove() {
	if(empty()==true) {
    	printf("Queue is empty!\n");
    	return false;
	}	
	if (first == QMAX-1)
		{
		first = 0;
		count--;
		}
	else
		{
		first++;
		count--;
		}
		
	return true;
}


void  queue::printFirst() {
  int i;
  if(empty()==true) {
    printf("Queue is empty!\n");
  }
  else{
    printf("First element in queue:%d \n",qu[first]);
  }
return;}

bool menu(class queue *q, int N){
	int x;
	switch(N){
		case 1:
			if(q->qu!=NULL){
			   free(q->qu);
		       }
	
			printf("Input size of queue\n");
  			scanf("%d",&N);
			q->init(N);
			break;
		case 2: 
			printf("Input element: \n");
			scanf("%d",&x);
			if(q->insert(x)==false)
				printf("Queue is full!\n"); 
			
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
  	class queue q;
  	class queue *q1;	
  	
  	int a=-2;
    q1 = new (class queue);
	q1->qu = NULL;
	
	printf("Input number for action:\n");
	printf("1 - restart queue\n");
	printf("2 - add element in queue\n");
	printf("3 - remove 1st element from queue\n");
	printf("4 - show queue\n");
	printf("5 - show 1st element of queue\n");
	printf("0 - finish\n");

  do {
  	scanf("%d", &a);
  }while(menu(&q, a)==true);


  return 0;
}
