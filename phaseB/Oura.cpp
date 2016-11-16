#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <string.h>
using namespace std;

//////////////////////////////////////////////////////////////////
////                Kombos me periexomena twn afi3ewn         ////
//////////////////////////////////////////////////////////////////
class QueueNode
{
public:
       float Arrival;
       float StartServing;
       float FinishServing;
       
       QueueNode(float A,float S,float F)
       {
          Arrival =  A;
          StartServing = S;
          FinishServing = F;
       }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////      Ylopoihsh Ouras, opou oi komboi QueueNode kataxwrountai sumfwna me thn domh ths ouras      ////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class Oura
{
public:
	QueueNode *komvosOura;
	Oura  *front,*rear,*next;
	
	Oura()
	{
		next=NULL;
		front=NULL;
		rear=NULL;
	}
	void push(float A,float S,float F)  //pros8esh tou kombou QueueNode sto telos ths ouras
	{
        QueueNode *komvos = new QueueNode(A,S,F);
        
		Oura *temp = new Oura(); //temp deikths pou deixnei ton trexon kombo pros eisagwgh
		temp->komvosOura=komvos;
		temp->next=NULL;

		if(front==NULL) front=temp;
		else rear->next=temp;

		rear=temp;
	}
	
	void pop() //diagrafh tou kombou QueueNode sthn arxh ths ouras
	{
         if(!isEmpty())
         {
            Oura *temp= new Oura();
            
            temp=front;
            front=front->next;
            
            delete temp;
         } 
    }
    
    bool isEmpty()
    {
         if(front == NULL) return true;
         else return false;
    }
};

int main()
{
    Oura oura;
    cout<<oura.isEmpty()<<endl;
    oura.push(9.653,9,12);
    oura.push(12,14,22);
    oura.push(14,20,25);
    
    Oura *tempfirst2=oura.front;
	while(tempfirst2 != NULL)
	{
		//for(int i=0;i<tempfirst2->nodekomvos->sizeElem;i++)
		cout<<tempfirst2->komvosOura->Arrival;
		cout<<tempfirst2->komvosOura->StartServing;
		cout<<tempfirst2->komvosOura->FinishServing;
		cout<<endl;
		tempfirst2=tempfirst2->next;
	}

    cout<<oura.isEmpty()<<endl;
    
    oura.pop();
    //oura.pop();
    oura.pop();
    
    tempfirst2=oura.front;
    while(tempfirst2 != NULL)
	{
		//for(int i=0;i<tempfirst2->nodekomvos->sizeElem;i++)
		cout<<tempfirst2->komvosOura->Arrival;
		cout<<tempfirst2->komvosOura->StartServing;
		cout<<tempfirst2->komvosOura->FinishServing;
		cout<<endl;
		tempfirst2=tempfirst2->next;
	}
system("pause");
return 0;
}
