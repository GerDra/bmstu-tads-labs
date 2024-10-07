#include <iostream>
#include <fstream>
#include <string> 
#include <math.h>
#include <malloc.h>
#include "list.h"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//class Matrx
struct Matrix{
	int* ia, //координаты индекса строки
		*ja, //координаты индекса строки
		*nr, //индекс следующего не нулевого элмента в строке
		*nc, //индекс следующего не нулевого элмента в колонке
		*jr, //точка входа в строку индекса массива не нулевого элемента(в  массиве ненулевых элементов индекс, с которого начинаются ненулевые элементы строки, котор
		*jc, 
		rows, 
		columns, 
		cntrForMass;
	double *an;
};

double** NewMatrix(int rows, int columns, Matrix &SM)
{
	int* ia,*ja,*nr, *nc,*jr,*jc, cntrForMass;
	double *an;
	int i;
	
	double**  matrix = (double**)malloc(sizeof(double*)*rows);
	
	for (i = 0; i < rows; i++) {
		matrix[i] = (double*)malloc(sizeof(double)*columns);
	}
	
	SM.ia=(int*)malloc(sizeof(int)*(rows*columns));
	SM.ja=(int*)malloc(sizeof(int)*(rows*columns));
//	SM.nr=(int*)malloc(sizeof(int)*numsNonNull);
//	SM.nc=(int*)malloc(sizeof(int)*numsNonNull);
	SM.jr=(int*)malloc(sizeof(int)*(rows+1));
//	SM.jc=(int*)malloc(sizeof(int)*columns);
	SM.an=(double*)malloc(sizeof(double)*(rows*columns));
//	SM3.cntrForMass=SM1.numsNonNull+SM2.numsNonNull;
	SM.cntrForMass=0;
	SM.rows=rows;
	SM.columns=columns;

	for(i=0;i<rows;i++)
		SM.jr[i]=-1;
	//SM.jr[rows]=numsNonNull;
	
	return matrix;
}



double** readMatrix(char *name, Matrix &SM){	
	int i,j,n,m,k;
	double numb;
	int sizOfMatr;
    double** matrix;
    int rows, columns;
	
	setlocale(0,"");
	List *matrixList;
	Elem *ofMatr1;
	
	matrixList=new List();
	
	FILE*fp=fopen(name,"r+");
	if (fp==NULL)
    {
    printf("file not open");
    return NULL;
    }
	fseek (fp,0,SEEK_SET);
	sizOfMatr=0;
	while(fscanf(fp, "%lf", &numb)!=EOF)
	{
		matrixList->add(numb);
		sizOfMatr++;
	}
	fclose(fp);
	rows=0;
	std::string line;
	std::ifstream in(name); 
    if (in.is_open())
    {
	while (std::getline(in, line))
        {
            rows++;
        }
	}
	in.close();
	
	SM.rows=rows;
	columns=SM.columns=sizOfMatr/rows;
	
	matrix = (double**)malloc(sizeof(double*)*rows);
	
	for (i = 0; i < rows; i++) {
		matrix[i] = (double*)malloc(sizeof(double)*columns);
	}
	
	matrixList->set_first_El();
	for(i=0; i<rows; i++){
		for(j=0; j<columns; j++){  
			double t = matrixList->next_El();
			matrix[i][j] = t; 
		}
	}
/*		printf("\nMatrix\n");
	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++)
		printf("%3.0lf\t", matrix[i][j]);
		printf("\n");
	}
	printf("\n");
*/	return matrix;
}

void convertMatrix(double** matrix, Matrix &SM){
		int i,j,n,m,k;
		int sizOfMatr;
		double nums;
		int rows=SM.rows;
		int columns=SM.columns;
	int numsNonNull=0;
	
	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++){  
			nums=matrix[i][j];
			if(nums!=0){
				numsNonNull++;
			}
		}
	}

	SM.ia=(int*)malloc(sizeof(int)*numsNonNull);
	SM.ja=(int*)malloc(sizeof(int)*numsNonNull);
	SM.nr=(int*)malloc(sizeof(int)*numsNonNull);
	SM.nc=(int*)malloc(sizeof(int)*numsNonNull);
	SM.jr=(int*)malloc(sizeof(int)*(rows+1));
	SM.jc=(int*)malloc(sizeof(int)*columns);
	SM.an=(double*)malloc(sizeof(double)*numsNonNull);
	
	SM.jc[i]=-1;
	for(i=0;i<rows;i++)
		SM.jr[i]=-1;
	SM.jr[rows]=numsNonNull;
	SM.cntrForMass=0;
	
	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++){  
			nums=matrix[i][j];
			if(nums!=0){
				SM.an[SM.cntrForMass]=nums;
				SM.ia[SM.cntrForMass]=i;
				SM.ja[SM.cntrForMass]=j;
				if(SM.jr[i]==-1){
					SM.jr[i]=SM.cntrForMass;
				}
				SM.cntrForMass++;
			}
		}
	}
	
	for(i=0;i<rows;i++){
		for(j=i;j<columns+1;j++){  
			if(SM.jr[i]==-1 && SM.jr[j]!=-1){
				SM.jr[i]=SM.jr[j];
			}
		}
	}
				
	k=0;
	for(i=0; i<SM.cntrForMass; i++){

		{
			if(SM.ia[i] != SM.ia[i+1])
			{
				k++;
				SM.nr[i]=-1;
			}
			else {
			SM.nr[i]=i+1;
			}
		}
	}

	for(i=0; i<columns; i++){
		k=0;
		SM.jc[i]=-1;
		while(i!=SM.ja[k] && k<SM.cntrForMass){
			k++;
		}
		
		if(k<SM.cntrForMass)
			SM.jc[i]=k;
	}

	int MaxCol = columns;
	int curj = 0;
	int temp=-1;
		
	for(curj=0; curj<MaxCol; curj++){
	  int t=-1;
	  for(i=0; i<SM.cntrForMass; i++){
		if(SM.ja[i]==curj){
		  	if(t==-1){
				SM.nc[i]=-1;
				t=i;
				}
			else{
				SM.nc[t]=i;
				temp=t;
				t=i;
				}
			}
		}
		
		if (temp!=-1){
			SM.nc[t]=-1;
		}
	}
}

void printMatrix(double** matrix, Matrix SM){
	int i,j;
	printf("\nMatrix\n");
	for(i=0; i<SM.rows; i++){
		for(j=0; j<SM.columns; j++)
			printf("%3.0lf\t", matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

void printRazvernMatrix(Matrix SM,double** &matrix)	{
	int i,j,k,l;
	int rows=SM.rows;
	int columns=SM.columns;
	k=i=0;
	printf("\nMatrix unpacked\n");
	
		
	while(i<rows){
		j=l=0;
		
		while(j<columns){
			if(SM.jr[i]!=SM.jr[i+1] && SM.ja[k]==j && k<SM.jr[i+1]){
				printf("%3.0lf\t", SM.an[k]);
				matrix[i][j]=SM.an[k];
				k++;
			}
			else{
				printf("%3.0lf\t", 0);
				matrix[i][j]=0.0;
			}
			
			j++;
		}

	printf("\n");
	i++;
	}
}		



void printRazMatrix(Matrix SM)	{
	int rows=SM.rows;
	int columns=SM.columns;
	int k;
	
	printf("an\n");
		for(k=0;k<SM.cntrForMass;k++){
	printf("%3.0lf\t",SM.an[k]);	
	}
//	printf("\n");
/*	printf("\nia\n");
	for(k=0;k<SM.cntrForMass;k++){
	printf("%i\t",SM.ia[k]);	
	}
*/	printf("\nja\n");
	for(k=0;k<SM.cntrForMass;k++){
	printf("%i\t",SM.ja[k]);
	}
/*	printf("\nnr\n");
		for(k=0;k<SM.cntrForMass;k++){
	printf("%i\t",SM.nr[k]);
	}
	printf("\nnc\n");
	
		for(k=0;k<SM.cntrForMass;k++){
	printf("%i\t",SM.nc[k]);
	}
*/	printf("\njr\n");
		for(k=0;k<=rows;k++){
	printf("%i\t",SM.jr[k]);
	}
/*	printf("\njc\n");
		for(k=0;k<columns;k++){
	printf("%i\t",SM.jc[k]);
	}
*/	printf("\n");
}

int addMatrix(Matrix SM1,Matrix SM2,Matrix &SM3){
	SM3.cntrForMass=SM1.cntrForMass+SM2.cntrForMass;

	
	if(SM1.rows != SM2.rows || SM1.columns != SM2.columns){
		printf("Invalid size of matrix\n");
		return -1;
	}
	int i,j,k,m,ka,kb;
	int rows=SM1.rows;
	int columns=SM1.columns;
	double temp;
	m=0;
	
	for(i=0; i<rows+1; i++){	
		ka = SM1.jr[i];
	    kb = SM2.jr[i];
	    
	    SM3.jr[i]=m;
	    
	   	while (ka < SM1.jr[i+1] && kb < SM2.jr[i+1]){
	      if(SM1.ja[ka] < SM2.ja[kb]){
	          SM3.an[m] = SM1.an[ka];
	          SM3.ja[m] = SM1.ja[ka];
			  ka++;
			  m++;
		  	}
	      else if (SM1.ja[ka] > SM2.ja[kb]){
	          SM3.an[m] = SM2.an[kb];
	          SM3.ja[m] = SM2.ja[kb];  
			  kb++;
			  m++;
		  	}
	      else
				{
		        temp=SM2.an[kb]+SM1.an[ka];
		    	if(temp!=0){
	          		SM3.an[m]=temp;
		        	SM3.ja[m]=SM1.ja[ka];
		        	m++;
				}
				
		        ka++;
		        kb++;
	      	}
	    }
	          
	     while(ka < SM1.jr[i+1]){
	     		SM3.an[m] = SM1.an[ka];
	        	SM3.ja[m] = SM1.ja[ka];
				ka++;
				m++;
		 }
	     while(kb < SM2.jr[i+1]){
	     		SM3.an[m] = SM2.an[kb];
	          	SM3.ja[m] = SM2.ja[kb];  
			  	kb++;
			  	m++;
		 }
	}
	
	SM3.cntrForMass = m;	 
	SM3.an=(double*)realloc(SM3.an,sizeof(double)*m);
	//SM3.ia=(int*)realloc(SM3.ia,sizeof(int)*m); //!
	SM3.ja=(int*)realloc(SM3.ja,sizeof(int)*m);
	if (SM3.an==NULL || SM3.ja==NULL)
		return -1;
	
	return 0;
}


int multiplayMatrix(Matrix SM1,Matrix SM2,Matrix &SM3){
	if(SM1.rows != SM2.columns || SM1.columns != SM2.rows){
		return -1;
	}
	int i,j,k,m,n,ka,kb;
	int rows=SM1.rows;
	int columns=SM2.columns;
	double temp;
	n=m=0;
	double* Cap;
	
	Cap = (double*)malloc(sizeof(double)*columns);
	
	for(i=0; i<columns; i++)
		Cap[i]=0.0;
	
	for(i = 0; i<SM1.rows; i++){
		
		for(j=0; j<columns; j++)
			Cap[j]=0;
				
		if(SM1.jr[i] < SM1.jr[i+1])// tochka vhoda ne sushestvuet
			    {
			    
		for(j = SM1.jr[i]; j < SM1.jr[i+1]; j++){

				int st = SM1.ja[j];
				
				for(k = SM2.jr[st]; k < SM2.jr[st+1]; k++){  //k - nomer elementa v AN v stroke st
					Cap[SM2.ja[k]] += SM1.an[j]*SM2.an[k];

				}
			}
			
			printf("\n");
			for(j=0; j<columns; j++)
				if(Cap[j]!=0){
					SM3.an[n]=Cap[j];
					SM3.ja[n]=j;
					SM3.ia[n]=i;
					
					if(SM3.jr[i]==-1){
						SM3.jr[i]=n;
						
						if(SM3.jr[i-1]==-1)
							SM3.jr[i-1]=SM3.jr[i];
					}
					n++;
				}
			}
		}
	SM3.cntrForMass=n;
	SM3.jr[rows]=n+1;
}
	
bool SravMatr(double** matrix1,double** matrix2, int rows, int colums){
	for(int i=0;i<rows; i++){
		for(int j=0;j<colums; j++){
			if(matrix1[i][j]!=matrix2[i][j])	
				return false;
			}
		}
	return true;
}



int main(int argc, char** argv) {
	int i, j, n, m, k;
	double numb;
	int rows, columns, sizOfMatr;
	
	Matrix SM1, SM2, SM3, SM4;

	char *name1={"matr1.txt"};
	char *name2={"matr2.txt"};
	double **matrix1, **matrix2, **matrix3, **matrix4, **matrix5, **matrix6;
	
	matrix1 = readMatrix(name1, SM1);
	printMatrix(matrix1, SM1);
	convertMatrix(matrix1, SM1);
	printRazMatrix(SM1);
	printRazvernMatrix(SM1,matrix1);
	
	matrix2 = readMatrix(name2, SM2);
	printMatrix(matrix2, SM2);
	convertMatrix(matrix2, SM2);
	printRazMatrix(SM2);
	printRazvernMatrix(SM2,matrix2);

	printf("\n Matrica C = A + B\n");
	matrix3 = NewMatrix(SM1.rows, SM1.columns, SM3);
	matrix5 = NewMatrix(SM1.rows, SM1.columns, SM3);

	if (addMatrix(SM1,SM2,SM3)==0){
		printRazMatrix(SM3);
		printRazvernMatrix(SM3,matrix3);
	}
	printf("\n Test\n");
	
	for (i = 0; i < SM1.rows; i++){
        for (j = 0; j < SM1.columns; j++)
        	printf("%3.0lf\t",matrix5[i][j]=matrix1[i][j]+matrix2[i][j]);
        printf("\n");
	}
	
	if(SravMatr(matrix3, matrix5, SM3.rows, SM3.columns))
		printf("Match\n");
	else 
		printf("Not match\n");
	
	
	printf("\n Matrica C = A x B");
	matrix4 = NewMatrix(SM1.rows, SM2.columns, SM4);
	matrix6 = NewMatrix(SM1.rows, SM2.columns, SM4);

/*
	for (i = 0; i < SM1.rows; i++)
        for (j = 0; j < SM1.columns; j++)
        {
            matrix4[i][j] = 0.0;
            for (k = 0; k < SM1.columns; k++)
                matrix4[i][j] += matrix1[i][k] * matrix2[k][j];
        }
	printMatrix(matrix4,SM4); 			
*/
	
	multiplayMatrix(SM1, SM2, SM4);
	//printMatrix(matrix4,SM4);
	printRazMatrix(SM4);
	printRazvernMatrix(SM4, matrix4);
	printf("\n Test");
	for(i = 0; i<SM1.rows; i++){
		
		for(j = 0; j < SM1.columns; j++)
			matrix6[i][j]=0;
		
		for(j = 0; j < SM1.columns; j++){
				for(k = 0; k < SM2.columns; k++){
						matrix6[i][k] += matrix1[i][j] * matrix2[j][k];
					}
			}
	}
	printMatrix(matrix4, SM4); 
	
		if(SravMatr(matrix4, matrix6, SM4.rows, SM4.columns))
			printf("Match\n");
		else 
			printf("Not match\n");
	
	return 0;
}
