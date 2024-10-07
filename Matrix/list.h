#include <iostream>
#include <math.h>
using namespace std;

class El_mas{
	public:
		int j;
		double num;
		void pr(){
			cout<<" num= "<<num<<" ";
		}
		El_mas(){}
		El_mas(double x, int ip){
			num=x; j=ip;
		}
};

class Elem{
	public:
		El_mas dat;
		double n;
		Elem *next;
		Elem(){n=0;next=0;
		}
};

class List{
	public:
		Elem* first, * last, *cur;
		List(){ first=NULL; last=NULL; cur=NULL;
		}
		void add(double j);
		void add_head(double j);
		void del_head();
		void del_xwost();
		void dell_xwost();
		void print_List();
		void del_List();
		void set_first_El();
		Elem* prev_last();
		double next_El();
		
};
