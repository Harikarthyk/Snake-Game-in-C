
/*  ********************** SNAKE GAME using C Program ******************* */

		    /********** CREDITS - Hari *********** */

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define RC 191
#define VL 179
#define RB 217
#define LC 218
#define LB 192
#define F 196
#define S 124
#define SQ 219
#define R 19712
#define L 19200
#define U 18432
#define D 20480
struct node
{
	struct node *pre;
	struct node *next;
	int r ;
	int c;
};
int r,c,fr,fc;
struct node *start;
struct node *end;
struct node* Create_Node(int col , int row)
{
	struct node * newNode;
	newNode=(struct node*)malloc(sizeof(struct node));
	newNode->pre=NULL;
	newNode->next=NULL;
	newNode->r=row;
	newNode->c=col;
	return newNode;
}
void DLL(int col , int row)
{
	struct node  *newNode ;
	newNode=Create_Node(col , row);
	if(start==NULL)
	{

		start=newNode;
		end=newNode;
	}
	else
	{
		end->next=newNode;
		newNode->pre=end;
		end = newNode;
	}
	r=end->r;
	c=end->c;
}
void Draw_Box()
{
	int ctr, x=1 ,y=2;
	textcolor(WHITE);
	cprintf("%c",LC);
	for(ctr=0;ctr<79;ctr++)
		cprintf("%c",F);
	for(ctr=0;ctr<23;ctr++,y++)
	{
		cprintf("%c",VL);
		gotoxy(x,y) ;
	}
	printf("%c",LB);
	for(ctr=0;ctr<78;ctr++,x++)
		cprintf("%c",F);
	cprintf("%c",RB);
	gotoxy(80,23);
	y = 23;
	x = 80;
	for(ctr=0;ctr<23;ctr++,y--)
	{
		cprintf("%c",VL);
		gotoxy(x,y);
	}
	cprintf("%c",RC);
	for(ctr=2;ctr<80;ctr++)
	{
	gotoxy(ctr,3);
	cprintf("%c",F);
	}

}
void Delete_DLL()
{
	struct node *safe;
	gotoxy(start->c,start->r);
	printf(" ");
	safe=start;
	start=start->next;
	free(safe);
}
int count=0;
void display()
{
	struct node *tptr;
	textcolor(WHITE);
	for(tptr=start;tptr!=NULL;tptr=tptr->next)
	{
		gotoxy(tptr->c,tptr->r);
		cprintf("%c",219);
	}
	gotoxy(42,2);
	textcolor(YELLOW);
	cprintf("SNAKE GAME");
	textcolor(BLUE);
	gotoxy(69,2);
	cprintf("SCORE: %d",count);

}
int RF , LF , UF , DF;
void Food_Creation()
{
	struct node*tptr;
	randomize();
	fc = rand()%68+6;
	fr = rand()%18+5;
	gotoxy(fc,fr);
	textcolor(YELLOW);
	cprintf("%c",2);
	count++;
}
void move()
{
	int key;
	struct node*tptr;
	struct node*shadow;
	shadow=NULL;
	do
	{
	while(bioskey(1) == 0);
	key = (bioskey(0));
	switch(key)
	{
		case R :
		  if(RF == 0)
		{
		  DLL(++c,r);
		  Delete_DLL();
		  if(fc==c && fr==r)
			{
				DLL(++c,r);
				Food_Creation();
			}
			LF=1;
			UF=DF=0;
		}
		break;
		case L:
		  if(LF==0)
		  {
			DLL(--c,r);
			Delete_DLL();
			if(fc==c && fr==r)
			{
				DLL(--c,r);
				Food_Creation();
			}
			RF=1;
			DF=UF=0;
		   }
		   break;
		case U :
		   if(UF==0)
		   {
			DLL(c,--r);
			Delete_DLL();
			if(fc==c && fr==r)
			{
				DLL(c,--r);
				Food_Creation();
			}
			RF=LF=0;
			DF=1;
		   }
		   break;
		case D:
		   if(DF==0 )
		   {
			DLL(c,++r);
			Delete_DLL();
			if(fc==c && fr==r )
			{
				Food_Creation();
				DLL(c,++r);
			}
			UF=1;
			RF=LF=0;
		   }
		   break;
	}
	if(end->r==3 || end->c==2 || end->r==23  || end->c==79)
	{
		key=283;
		break;
	}
	for(tptr=start; (end->r != tptr->r && end->c!=tptr->c) ;tptr=tptr->next)
	{
		if(end->r==tptr->r && end->c==end->r)
	key=283;
	}
	display();
	}while(key != 283);
}
int main()
{
	clrscr();
	Draw_Box();
	DLL(3,9);
	DLL(4,9);
	DLL(5,9);
	display();
	Food_Creation();
	move();
	clrscr();
	textcolor(WHITE);
	textbackground(RED);
	gotoxy(33,10);
	cprintf("*****OUT*****");
	gotoxy(33,12);
	cprintf("SCORE : ' %d '",count);
	gotoxy(27,14);
	cprintf("*** PRESS ANY TO EXIT ***");
	gotoxy(77,20);
	cprintf("############## - BY HARI ");
	getch();
	return 0;
}