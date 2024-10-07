#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <math.h>
#include <malloc.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//#include "ustack.h"
#include <queue>
const int MAX_LEN = 32;//иаксимальная длинна переменной или числа
class stack {
	private: 
  	char *qu;
  	int last, first;
  	int QMAX;
  	int count;
  	
  	public:
  	stack(); //конструктор класса
  	stack(int QM); //конструктор класса
  	void init(int N);
	bool empty();
	bool full();
	bool insert(char x);
	void print();
	bool remove();
	void printFirst();
	char pop();
	char top();
	
};


class ustack {
	public: 
  	float *qu;
  	int last, first;
  	int QMAX;
  	int count;
  	
  	ustack(); //??????????? ??????
  	ustack(int QM); //??????????? ??????
  	void init(int N);
	bool empty();
	bool full();
	bool insert(float x);
	void print();
	bool remove();
	void printFirst();
	float top();
	float pop();
	
};


//#define QMAX 100
ustack::ustack()
{
	qu = NULL;
}

ustack::ustack(int QM)
{
	qu = NULL;
	init(QM);
}


void ustack::init(int N) {
	QMAX = N;
	qu = (float*)malloc(sizeof(float)*QMAX);
	last = -1;
	count=0;
  return;
}

bool ustack::empty() {
  	if(count==0)    return true;
  	else  return false;
}

bool ustack::full(){
	if(count==QMAX)return true;
	else return false;
}

bool ustack::insert(float x){
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

void ustack::print() {
  int i;
  if(empty()==true) {
    printf("Stack is empty!\n");
  }
  else{
  	int k;
  	if(first<=last)
    for(i = first, k=1; i<=last; i++,k++)
   		printf("N %i- element %f\n",k,qu[i]);
  	else{
		for(i = first, k=1; i<QMAX; i++,k++)
	   		printf("N %i- element %f\n",k,qu[i]);
	  	for(i = 0; i<=last; i++,k++)
	   		printf("N %i- element %f\n",k,qu[i]);
		}
  	
  }
  return;
}

bool ustack::remove() {
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

void  ustack::printFirst() {
  int i;
  if(empty()==true) {
    printf("Stack is empty!\n");
  }
  else{
    printf("Top element in ustack:%d \n",qu[last]);
  }
return;}

float ustack::top() {
	if(empty()==true) {
    	return '\0';
	}	
	else{
		float c = qu[last];
		return c;
	}
}

float ustack::pop() {
	if(empty()==true) {
    	return '\0';
	}	
	else{
		float c = qu[last];
		last--;
    	count--;
	return c;
	}
}

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
	qu = (char*)malloc(sizeof(char)*QMAX);
	last = -1;
	first = 0;
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

bool stack::insert(char x){
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
   		printf("N %i- element %c\n",k,qu[i]);
  	else{
		for(i = first, k=1; i<QMAX; i++,k++)
	   		printf("N %i- element %c\n",k,qu[i]);
	  	for(i = 0; i<=last; i++,k++)
	   		printf("N %i- element %c\n",k,qu[i]);
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

char stack::top() {
	if(empty()==true) {
    	return '\0';
	}	
	else{
		char c = qu[last];
		return c;
	}
}

char stack::pop() {
	if(empty()==true) {
    	return '\0';
	}	
	else{
		char c = qu[last];
		last--;
    	count--;
	return c;
	}
}


void  stack::printFirst() {
  int i;
  if(empty()==true) {
    printf("Stack is empty!\n");
  }
  else{
    printf("Top element in stack:%c \n",qu[last]);
  }
return;}

//Operation prioritet
int priorOp( char c){
		
	switch(c){
	case '+':
	case '-':
		return 1;
		break;
	case '*':
	case '/':
		return 2;
		break;
	case '^':
		return 3;
	/*case "sin":
	case "cos":
	case "tg":
		return 4;*/
	case '(':
		return 5;
		break;
	case ')':
		return 6;
		break;
	default:
		printf(" WRONG operator %с", c);
		return -1;
		break;
}

};

int calculate( char k, float x1, float x2){
		float rez;
	switch(k){
	case '+':
		rez=x1+x2;
		break;
	case '-':
		rez=x1-x2;
		break;
	case '*':
		rez=x1*x2;
		break;
	case '/':
		rez=x1/x2;
		break;
	case '^':
		rez=pow(x2,x1);
		break;
	/*case "sin":
	case "cos":
	case "tg":*/
		
	default:
		printf(" WRONG operator");
		//return -1;
		break;
}
		return rez;

};

using namespace std;


/*
class scaning{
		public:
			char*instr; // входная строка
			queue out_queue; 
			stack opstack;
			int sizein;
			
			scaning(char*is);
			void devide();
			 
}; 

scaning::scaning(char*is){
	
	sizein=length.instr;
	instr=new malloc(sizeof(char)*sizein)
	instr=is;
	for(i=0;)
}

void devide(){
	
}
*/

int main(int argc, char** argv) {
	int i,j,m,z,ii,jj,numi, plzcn;char k,l;
	char text[]=("10-25*33-(42/(23-56)-10*6)*2");
	int len_input_str = 100;
	int n=32; // максимальное суммарное количество операторов и операндов
	char operat[]={"+-*/()"};
	float numbers[n];
	char nums[MAX_LEN];
	char operands[n][MAX_LEN];
	char inputOper[n][MAX_LEN];
	//string* inputOper[]= new string* [n,MAX_LEN];
	char opers[n];
	char temp[n][MAX_LEN];
	
	
	for(i=0,m=0,ii=0,jj=0;i<len_input_str;i++)
	{
		k=text[i]; //текущий символ
			
		if(k>='0'&& k<='9'|| k=='.'){
			j=0;
			do{
				nums[j] = k; 
				j++;
				
				i++;
				k = text[i];	    
			}while(k>='0'&& k<='9'|| k=='.' );
			//while(k!='+'&&k!='-'&&k!='*'&&k!='/'&&k!='('&&k!=')'&&k!='\0');
			nums[j] = '\0';
			
			strcpy(operands[ii], nums);
			strcpy((char*)(inputOper[jj]), (char*)(operands[ii]));
			ii++;
			jj++;
			i--;
			}
		else if(k>='a'&&k<='z'){
			j=0;
			do{
				nums[j] = k;
				j++;
				
				i++;
				k = text[i];	    
			}while(k>='a'&&k<='z' );
			//while(k!='+'&&k!='-'&&k!='*'&&k!='/'&&k!='('&&k!=')'&&k!='\0');
			nums[j] = '\0';
			
			strcpy(operands[ii], nums);
			strcpy(inputOper[jj], operands[ii]);
			ii++;jj++;
			i--;
			}
		
		else if(k=='+'||k=='-'||k=='*'||k=='/'||k=='('||k==')'){
			opers[m]=k;
			
			nums[0] = opers[m];
			nums[1] = '\0';
			//sprintf(nums,"%с",opers[m]);
			strcpy((char*)(inputOper[jj]), nums);
			jj++;
			m++;
			}
		else if(k==' ')i++;
		else if(k=='\0') break;
		else{
				printf("wrong operator");
				return -1;
			}
		}	
	
	for(i=0;i<m;i++)
		printf("%c ",opers[i]);
	printf("\n"); 
	
//	for(i=0;i<j;i++)
//		printf("%i\t",numbers[i]);
//	printf("\n"); 
	//ПОЛИЗ: 10.5.3.*.+.2.-
	
	for(i=0; i < ii; i++)
		printf("operands[%i] %s \n",i,operands[i]);
	printf("\n"); 
	
	for(i=0; i < (ii-1);i++)
		{
		for(j=0;j<MAX_LEN && operands[i][j]!='\0';j++)
			printf("%c",operands[i][j]);
		printf(" ");
		}
	printf("\n"); 
	
	
	for(i=0; i < jj; i++)
		printf("inputOper[%i] %s \n",i,inputOper[i]);
	printf("\n"); 

	
	//БЛОК ПРЕОБРАЗОВАНИЯ входного массива inputOper, полученного на выходе в предыдщем блоке в ПОЛИЗ
	
	stack *Op = new stack(m); //stack operatcii
	Op->init(m);
	
	char poliz[n][MAX_LEN];// obratnaya polskaya zapis
	//int tc;
	//цикл преобразования в ПОЛИЗ
	for(i=0,j=0,numi=0;i<jj;i++){
		
		k=inputOper[i][0]; //текущий символ
			
		if(k>='0'&& k<='9'|| k=='.'){
			//numbers[numi]=atoi(inputOper[i]);
			strcpy(poliz[j],inputOper[i]);
			//numi++;
			j++;
		}
		else if(k>='a'&&k<='z'){
			//numbers[numi]=atoi(inputOper[i]);
			strcpy(poliz[j],inputOper[i]);
			//numi++;
			j++;
		}
		else if(k=='+'||k=='-'||k=='*'||k=='/'||k=='('||k==')'){
			if(priorOp(k)==5){		// Символ "("
				Op->insert(k);
			}
			else if(priorOp(k)==6){			//Символ ")"
				l=Op->pop();		// выталкиваем верхнее значение, пока не "("
				while(priorOp(l)!=5){
					if(Op->empty()){
						printf("Error,not enough brackets");	
						return -1;
					}
						
					poliz[j][0]=l;
					poliz[j][1]='\0';
					j++;
					l=Op->pop();
				};
				//l=Op->pop();
			}
			else if(priorOp(k)!=-1){		//Разрешенные знаки операций
				if(Op->empty()==true){		// Стек пуст, выталкиваем
					Op->insert(k);
				}
				else {		//Стек не пуст,
					if(priorOp(Op->top())==5){		//В стеке "("
					Op->insert(k);
					}
					else if(priorOp(Op->top())<priorOp(k)){		 //сравнение приоритетов
							Op->insert(k);
							}
						else{
							while(priorOp(Op->top())>=priorOp(k)&& priorOp(k)!=5){
							poliz[j][0]=Op->pop();
							poliz[j][1]='\0';
							j++;	
							
							}
							Op->insert(k);
						}
					}
				}
			else{
				printf("wrong operator: -1");
				return -1;
			}
			
		} else {
				printf("wrong Operand: -2");
				return -2;
			}
		}
				
			//Op->insert(k);
			
		/*while(c!=5){
			stack.pop()
		}*/
		
		/*Op->print();
		printf("%f ", numbers[numi-1]);
		printf("%s",poliz[j-1]);
		printf("\n");*/

			 if(Op->empty()==false){		//Операции закончились, стек не пуст
				while(Op->empty()==false){
					if(priorOp(Op->top())==5){	// в стеке осталась"("
						
						printf("Error,not enough brackets");	
						return -1;
					}
					else{
					poliz[j][0]=Op->pop();
					poliz[j][1]='\0';
					j++;
					}
			}
	}
		plzcn=j;
	 	Op->print();
	 	for(i=0;i<plzcn;i++){
	 	//printf("%f ", numbers[i]);
	 	printf("%s ",poliz[i]);}
		//printf("\n");
		
		float x1,x2;
		
		ustack *Calc = new ustack(plzcn); //stack operatcii
		Calc->init(plzcn);
		Op->init(m);
		printf("\ntext=%s\n", text);
		
		for(i=0;i<plzcn;i++){
			k=poliz[i][0]; //текущий символ
			
			if(k>='0'&& k<='9'|| k=='.'){
				//numbers[numi]=atof(inputOper[i]);
				Calc->insert(atof(poliz[i]));
				//numi++;
		}
			else if(k>='a'&&k<='z'){
				Calc->insert(k);
		}
		else if(k=='+'||k=='-'||k=='*'||k=='/'){
				x2=Calc->pop();	
				x1=Calc->pop();
				float f = calculate(k,x1,x2);
				Calc->insert(f);
				printf("%f %c %f = %f\n", x1, k, x2, f);
				}
			else{
				printf("wrong operator");
				return -1;
			}
			
		}
		
		Calc->print();
	return 0;
}
