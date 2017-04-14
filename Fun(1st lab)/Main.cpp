#include <math.h>
#include <iostream>
#include <locale.h>
#include <time.h>

using namespace std;

int main()
{
	double a=0.0,b=1200111.3,d=0.1,res,fl=0;
	setlocale(LC_ALL,"Russian");
	while(1)
	{
		while(1)
		{
			cout<<"Введите a:";
			cin>>a;
			if(cin.fail())
			{
				
				cin.clear();
				cin.sync();
				cout<<"Ошибка! Повторите ввод!"<<endl;
				system("pause");
				system("cls");
				continue;
			}
			else break;
		}
		system("cls");
		cin.clear();
		cin.sync();
		while(1)
		{
			
			cout<<"Введите b:";
			cin>>b;
			if(cin.fail())
			{
				cin.clear();
				cin.sync();
				cout<<"Ошибка! Повторите ввод!"<<endl;
				system("pause");
				system("cls");
				continue;
			}
			else 
				break;
		}
		if(a>=b)
		{
			cout<<"Ошибка!Граница а больше границы b!"<<endl;
			continue;
		}
		else 
			break;
	}
	system("cls");
	cin.clear();
	cin.sync();
	while(1)
		{
			
			cout<<"Введите d:";
			cin>>d;
			if(cin.fail()||d<=0)
			{
				cin.clear();
				cin.sync();
				cout<<"Ошибка! Повторите ввод!"<<endl;
				system("pause");
				system("cls");
				continue;
			}
			else 
				break;
		}
		
	system("cls");
	cout<<"a:"<<a<<endl;
	cout<<"b:"<<b<<endl;
	cout<<"d:"<<d<<endl;
	cout<<"Работа функции сопроцессора:"<<endl;
	unsigned int pre_time = clock();
	
	_asm finit
	for(double x=a;x<b;x=x+d)
	{
		_asm{
			FLD x
			FSIN

			FLD x
			FSQRT

			FSUB
			FABS
			FSTP res
		}
		
	}
	_asm fwait

	unsigned int post_time = clock();
	cout<<"Затраченное время,c:";
	cout<<(double)(post_time-pre_time)/CLOCKS_PER_SEC<<endl;
	cout<<"Результат последнего вычисления:";
	cout<<res<<endl;


	cout<<"\nРабота обычной функции:"<<endl;
	pre_time = clock();
	for(double x=a;x<b;x+=d)
	{
		res=abs(sin(x)-sqrt(x));
	}
	post_time = clock();
	cout<<"Затраченное время,c:";
	cout<<(double)(post_time-pre_time)/CLOCKS_PER_SEC<<endl;
	cout<<"Результат последнего вычисления:";
	cout<<res<<endl;

	return 0;
}