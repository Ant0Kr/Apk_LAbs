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
			cout<<"������� a:";
			cin>>a;
			if(cin.fail())
			{
				
				cin.clear();
				cin.sync();
				cout<<"������! ��������� ����!"<<endl;
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
			
			cout<<"������� b:";
			cin>>b;
			if(cin.fail())
			{
				cin.clear();
				cin.sync();
				cout<<"������! ��������� ����!"<<endl;
				system("pause");
				system("cls");
				continue;
			}
			else 
				break;
		}
		if(a>=b)
		{
			cout<<"������!������� � ������ ������� b!"<<endl;
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
			
			cout<<"������� d:";
			cin>>d;
			if(cin.fail()||d<=0)
			{
				cin.clear();
				cin.sync();
				cout<<"������! ��������� ����!"<<endl;
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
	cout<<"������ ������� ������������:"<<endl;
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
	cout<<"����������� �����,c:";
	cout<<(double)(post_time-pre_time)/CLOCKS_PER_SEC<<endl;
	cout<<"��������� ���������� ����������:";
	cout<<res<<endl;


	cout<<"\n������ ������� �������:"<<endl;
	pre_time = clock();
	for(double x=a;x<b;x+=d)
	{
		res=abs(sin(x)-sqrt(x));
	}
	post_time = clock();
	cout<<"����������� �����,c:";
	cout<<(double)(post_time-pre_time)/CLOCKS_PER_SEC<<endl;
	cout<<"��������� ���������� ����������:";
	cout<<res<<endl;

	return 0;
}