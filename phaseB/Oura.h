#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
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
