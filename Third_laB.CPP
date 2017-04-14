#include <dos.h>

struct VIDEO //structure for videoBuf
{
	unsigned char symbol;
	unsigned char attribut;
};
char color = 0x01;
char strColor = 0x04;

void changeColor()
{
	if(color<0x07)
		color++;
	else
		color = 0x01;
}

void changeStrColor()
{
	if(color<0x08)
		strColor++;
	else
		strColor = 0x01;
}

void printRegister(int reg,int posX,int posY)
{
	VIDEO far* screen = (VIDEO far*)MK_FP(0xB800,0);
	screen+=(80*posY+posX);
	int i;
	for(i = 0;i<=7;i++)
	{
		screen->symbol = reg%2 + '0';
		reg/=2;
		screen->attribut = color;
		screen++;
	}
}

void printString(char *st,int length,int posX,int posY)
{      //function that print string on screen
	VIDEO far * screen = (VIDEO far*)MK_FP(0xB800,0);
	screen+=(80*posY+posX);//offset cursor for output
	int i;
	for(i = 0;i<length;i++)
	{
		screen->symbol = *(st+i);
		screen->attribut = strColor;
		changeStrColor();
		screen++;
	}
}



void print()
{
	printString("MASTER!",7,0,0);
	printString("Register of masks:",18,0,1);
	printRegister(inp(0x21),19,1);

	printString("Register of requests:",21,0,2);
	outp(0x20,0x0A);
	printRegister(inp(0x20),22,2);

	printString("Register of services:",21,0,3);
	outp(0x20,0x0B);
	printRegister(inp(0x20),22,3);

	printString("Slave!",6,0,5);
	printString("Register of masks:",18,0,6);
	printRegister(inp(0xA1),19,6);

	printString("Register of requests:",21,0,7);
	outp(0xA0,0x0A);
	printRegister(inp(0xA0),22,7);

	printString("Register of services:",21,0,8);
	outp(0xA0,0x0B);
	printRegister(inp(0xA0),22,8);

}

void interrupt (*int08) (...);
void interrupt (*int09) (...);
void interrupt (*int0A) (...);
void interrupt (*int0B) (...);
void interrupt (*int0C) (...);
void interrupt (*int0D) (...);
void interrupt (*int0E) (...);
void interrupt (*int0F) (...);

void interrupt (*int70) (...);
void interrupt (*int71) (...);
void interrupt (*int72) (...);
void interrupt (*int73) (...);
void interrupt (*int74) (...);
void interrupt (*int75) (...);
void interrupt (*int76) (...);
void interrupt (*int77) (...);

void interrupt new08(...){print();int08();}
void interrupt new09(...){changeColor();print();int09();}//keyboard
void interrupt new0A(...){print();int0A();}
void interrupt new0B(...){print();int0B();}
void interrupt new0C(...){print();int0C();}
void interrupt new0D(...){print();int0D();}
void interrupt new0E(...){print();int0E();}
void interrupt new0F(...){print();int0F();}

void interrupt new70(...){print();int70();}
void interrupt new71(...){print();int71();}
void interrupt new72(...){print();int72();}
void interrupt new73(...){print();int73();}
void interrupt new74(...){print();int74();}
void interrupt new75(...){print();int75();}
void interrupt new76(...){print();int76();}
void interrupt new77(...){print();int77();}

void init()
{
	int08 = getvect(0x08);
	int09 = getvect(0x09);
	int0A = getvect(0x0A);
	int0B = getvect(0x0B);
	int0C = getvect(0x0C);
	int0D = getvect(0x0D);
	int0E = getvect(0x0E);
	int0F = getvect(0x0F);

	int70 = getvect(0x70);
	int71 = getvect(0x71);
	int72 = getvect(0x72);
	int73 = getvect(0x73);
	int74 = getvect(0x74);
	int75 = getvect(0x75);
	int76 = getvect(0x76);
	int77 = getvect(0x77);

	setvect(0x90,new08);
	setvect(0x91,new09);
	setvect(0x92,new0A);
	setvect(0x93,new0B);
	setvect(0x94,new0C);
	setvect(0x95,new0D);
	setvect(0x96,new0E);
	setvect(0x97,new0F);

	setvect(0x08,new70);
	setvect(0x09,new71);
	setvect(0x0A,new72);
	setvect(0x0B,new73);
	setvect(0x0C,new74);
	setvect(0x0D,new75);
	setvect(0x0E,new76);
	setvect(0x0F,new77);


	_disable();

	outp(0x20,0x11);
	outp(0x21,0x90);
	outp(0x21,0x04);
	outp(0x21,0x01);

	outp(0xA0,0x11);
	outp(0xA1,0x08);
	outp(0xA1,0x02);
	outp(0xA1,0x01);

	_enable();
}

int main()
{
	unsigned far *fp;
	init();
	FP_SEG (fp) = _psp;
	FP_OFF (fp) = 0x2c;

	_dos_freemem(*fp);
	_dos_keep(0,(_DS - _CS)+(_SP/16)+1);

	return 0;
}