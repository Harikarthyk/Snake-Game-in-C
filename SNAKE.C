//Snake Game -using DLL.
#include<stdio.h>
#include<conio.h>
#define Right 19712
#define Left 19200
#define Up 18432
#define Down 20480
#define Food 1
#define SBody 219
int fc , fr , count=-1 , k ;
struct Snake
{
   //Sc-SnakeColumn and Sr-SnakeRow.
   int Sr , Sc ;
   struct Snake *next , *pre;
};
struct Snake *Head=NULL , *Tail=NULL;
void createSnake(int row , int col)
{
   struct Snake *newNode=(struct Snake*)malloc(sizeof(struct Snake));
   newNode->Sc=col;
   newNode->Sr=row;
   newNode->next=NULL;
   if(Head==NULL)
   {
      Tail=newNode;
      Head=newNode;
   }
   else
   {
      //Insertion at End.
      newNode->next=Head;
      Head->pre=newNode;
      Head=newNode;
   }
}
void DeleteBut()
{
   //Deleting at End.
   Tail=Tail->pre;
   Tail->next=NULL;
}
void PrintSnake()
{
   struct Snake *tptr;
   clrscr();
   //Displaying Snake.
   for(tptr=Head;tptr!=NULL;tptr=tptr->next)
   {
       gotoxy(tptr->Sc,tptr->Sr);
       printf("%c",SBody);
   }
   gotoxy(fc,fr);
   printf("%c",Food);
}
void FoodCreation()
{
    struct Snake *tptr;
    //To Generate Food in random positions.
    fc=rand() % 78 ;
    fr=rand() % 23 ;
    for(tptr=Head;tptr!=NULL;tptr=tptr->next)
    {
       //to avoid Food to be Generated in Snake's Position.
       if(tptr->Sr==fr && tptr->Sc==fc)
	  FoodCreation();
    }
    count++;
}
void CheckRestriction()
{
   //Checking out-of-bound and conditions.
   struct Snake *tptr , *tptr1;
   for(tptr=Head;tptr!=NULL;tptr=tptr->next)
   {
       for(tptr1=tptr->next;tptr1!=NULL;tptr1=tptr1->next)
       {
	   if((tptr->Sc==tptr1->Sc && tptr->Sr==tptr1->Sr) ||((Head->Sc==80 || Head->Sr==24 || Head->Sc==0 || Head->Sr==0)))
	   {
	       k=283;
	       clrscr();
	       gotoxy(37,12);
	       printf("Out");
	       delay(350);
	       break;
	   }
       }
   }
}
void main()
{
   clrscr();

   createSnake(11,33);
   createSnake(11,34);
   createSnake(11,35);
   createSnake(Head->Sr , (Head->Sc + 1));
   FoodCreation();
   PrintSnake();
   do
   {
	//bioskey is to know the key pressed.
	k=(bioskey(0));
	switch(k)
	{
	   case Right:
	   {
	      createSnake(Head->Sr , (Head->Sc + 1));
	      DeleteBut();
	      if(Head->Sr==fr && Head->Sc==fc)
	      {
		  FoodCreation();
		  createSnake(Head->Sr , (Head->Sc + 1));
	      }
	      break;
	   }
	   case Left:
	   {
	      createSnake(Head->Sr , (Head->Sc - 1));
	      DeleteBut();
	      if(Head->Sr==fr && Head->Sc==fc)
	      {
		  FoodCreation();
		  createSnake(Head->Sr , (Head->Sc - 1));
	      }
	      break;
	   }
	   case Up:
	   {
	      createSnake((Head->Sr - 1) , Head->Sc);
	      DeleteBut();
	      if(Head->Sr==fr && Head->Sc==fc)
	      {
		  FoodCreation();
		  createSnake((Head->Sr - 1) , Head->Sc);
	      }
	      break;
	   }
	   case Down:
	   {
	      createSnake((Head->Sr + 1), Head->Sc);
	      DeleteBut();
	      if(Head->Sr==fr && Head->Sc==fc)
	      {
		  FoodCreation();
		  createSnake((Head->Sr + 1) , Head->Sc);
	      }
	   }
	}
	CheckRestriction();
	PrintSnake();
   //if k=283 Game Quits -(If we press Esc or when we go wrong).
   }while(k!=283);
   clrscr();
   //Display the Final Result.
   gotoxy(32,12);
   printf("Your Score = %d",count);
   getch();
}
