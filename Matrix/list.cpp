#include <iostream>
#include <math.h>
#include "list.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



void List::add_head(double j){
	cur =new Elem();
	cur->n=j;
	if(first==0){
		cur->next=0;
		first=cur;
		last=cur;
	}
	else{
		cur->next=first; first=cur;
	}
}

void List::add(double j){
	cur=new Elem();
	cur->n=j;
	cur->next=0;
	if(first){
		last->next=cur;
		last=cur;
	}
	else{
		first=cur;
		last=cur;
	}
}

void List::del_head(){
	if(first->next){
		cur=first;
		first=first->next;
		delete cur;
	}
	else if(first){
		cur=first;
		delete cur;
		first=0;
		last=0;
	}
	else cout<<"first=0"<<endl;
}

void List::del_xwost(){
	if(last==first){
		delete last;
		first=0;
		last=0;
	}
	else{
		cur=prev_last();
		delete last;
		last=cur;
		last->next=0;
	}
}

void List::dell_xwost(){
	cur=first;
	if(last==first){
		delete last;
		first=0;
		last=0;
	}
	else{
		while(cur->next->next!=0)
			cur=cur->next;
		cur=prev_last();
		delete last;
		last=cur;
		last->next=0;
	}
}

void List::print_List(){
	cur=first;
	while(cur){
		cout<<cur->n<<" ";
		cur=cur->next;
	}
	cout<<endl;
}

void List::set_first_El(){
	cur=first;
	//double x=cur->n;
	//return x;
}

double List::next_El(){
	//while(cur){
		double x=cur->n;
		if (cur != last)
			cur=cur->next;
		return x;
//}
}

Elem*List::prev_last(){
	cur=first;
	while(cur->next->next){
		cur=cur->next;
	}
	return cur;
}

void List::del_List(){
	while(first&&last)
		del_head();
}
