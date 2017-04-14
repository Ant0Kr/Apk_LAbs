#include <math.h>
#include <iostream>
#include <locale.h>
#include <time.h>
#include <random>
#include <iomanip>
using namespace std;

const int n = 8;
const int m = 8;
const unsigned int size = 4000000;

int main()
{
	setlocale(LC_ALL,"Russian");

	unsigned int pre_time,post_time;
    short int mt1[n][m],mt2[n][m],C[n][m],ASM[n][m],MMX[n][m];
	
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<m;j++)
		{
			mt1[i][j] = rand()/1000+1;
			mt2[i][j] = rand()/1000+1;
		}
	}
	
	pre_time = clock();
	for(int k = 0;k<size;k++)             //С реализация
	{
		for(int i = 0;i<n;i++)
		{
			for(int j = 0;j<m;j++)
			{
				C[i][j] = mt1[i][j]&mt2[i][j];	
			}
		}
	}
	post_time = clock();
	
	cout<<"C implementation."<<endl;
	cout<<"Elapsed time,mc:";
	cout<<post_time-pre_time<<endl;
	cout<<endl;

	short cnt,number=n*m;
	
	pre_time = clock();                                 //ассемблерная реализация
	for(int k = 0;k<size;k++)
	{
		_asm {
						
			pusha
			xor esi,esi
			mov ax,number
			mov cnt,ax
		loop1:
			mov ax,mt1[esi]
			mov bx,mt2[esi]
		
			and ax,bx

			mov ASM[esi],ax
				
			add esi,2
			dec cnt
		jnz loop1
			popa
		}
	}
	post_time = clock();
	
	cout<<"Assembler implementation."<<endl;
	cout<<"Elapsed time,ms:";
	cout<<post_time-pre_time<<endl;
	cout<<endl;
	number = n*m/4;
	pre_time = clock();
	for(int k = 0;k<size;k++)
	{
		_asm {
						
			pusha
			xor esi,esi
			movq MM0,number
			movq cnt,MM0
		loop2:
			movq MM0,mt1[esi]    //по 4 элемента за 1 раз
			movq MM1,mt2[esi]
		
			pand MM0,MM1
			
			movq MMX[esi],MM0

			add esi,8    // через 8 байт
			dec cnt
		jnz loop2
			
			popa
		}
	}
	_asm{
	emms
	}
	post_time = clock();
	
	cout<<"MMX implementation."<<endl;
	cout<<"Elapsed time,ms:";
	cout<<post_time-pre_time<<endl;
	cout<<endl;

	cout.precision(3);
	cout<<"MT-1:"<<endl;
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<m;j++)
		{
			cout<<setw(4)<<mt1[i][j];		
		}
		cout<<endl;
	}

	cout<<endl;
	cout<<"MT-2:"<<endl;
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<m;j++)
		{
			cout<<setw(4)<<mt2[i][j];
		}
		cout<<endl;
	}

	cout<<endl;
	cout<<"C solution:"<<endl;
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<m;j++)
		{
			cout<<setw(4)<<C[i][j];
		}
		cout<<endl;
	}

	cout<<endl;
	cout<<"ASM solution:"<<endl;
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<m;j++)
		{
			cout<<setw(4)<<ASM[i][j];
		}
		cout<<endl;
	}

	cout<<endl;
	cout<<"MMX solution:"<<endl;
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<m;j++)
		{
			cout<<setw(4)<<MMX[i][j];
		}
		cout<<endl;
	}

	return 0;
}