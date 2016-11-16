#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <string.h>

#include "Oura.h"       //Ylopoihsh Ouras
#define n 10          //plithos pelatwn
using namespace std;

float Time; //Poloi prosomoiwshs

///////////////////////////////////////////////////////////////////////////////
//                          Metablhtes Katastashs  

bool ServerIsBusy; //Katastash tou Server True i False
int QueueSize;     //Plh8os ouras, xwris na prosmetra ton e3yphretoumeno pelath
float LastEvent;   //Xronikh Stigmh Teleutaiou Gegonotos

///////////////////////////////////////////////////////////////////////////////
//                          Statistikoi Apari8mhtes

float FreeTime;      //Synolikos Xronos mh aposxolhshs tou Server (tameia) 
int Lq;              //To a8roistiko plh8os twn pelatwn pou einai sthn oura otan exoume lh3h ejyphrethsh enos pelath
float Wq;            //Athroisma xronwn anamonhs pelatwn
float W;             //Athroisma xronwn anamonhs kai e3uphrethshs pelatwn
int servedCustomers; //E3yphretoumenoi Pelates sthn prosomoiwsh
int Counter4plus;    //Metriths plh8ous opou h oura einai panw apo 4 pelates
int Counter1wraplus; //Metriths plh8ous twn pelatwn opou 8a perasnoun panw apo mia wra sthn trapeza (anamonh + e3yphrethsh)


//                          Diaforetika gia thn ylopoihsh

float *Arrivals;         //pinakas twn afi3ewn pelatwn se lepta ek8etikhs katanomhs
float *Service;          //pinakas xronikhs diarkeias e3uphrethshs pelatwn gia ka8e afi3h (se lepta ekthetikhs katanomhs)
float *TotalWaitingTime; //pinakas synolikou xronou paramonhs se ka8e afi3h (anamonh + e3yphrethsh)
int next;                //metablhths opou deixnei thn epomenh 8esh gia tos pinakes Arrivals kai Service

Oura oura;               //Dhmiourgia antikeimenou Ouras opou 8a kratountai oi pelates pou anamenoun

//----------------------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
////                           Poutines                                     ////                           

void initialization();
void timing();
void arrival();
void departure();
void report();

void BubbleSort();

////////////////////////////////////////////////////////////////////////////////
//----------------------------main----------------------------------------------
int main()
{
    /* Intializes random number generator */
    srand ((unsigned) time(NULL));
    
    initialization();
    
    //Oura *tempfirst2;
    while( servedCustomers < n )
    {
    /*cout<<"servedCustomers "<<servedCustomers<<endl;
    cout<<"Time "<<Time<<endl;
    //typwsi trexon ouras
    tempfirst2=oura.front;
	while(tempfirst2 != NULL)
	{
		cout<<tempfirst2->komvosOura->Arrival<<"\t";
		cout<<tempfirst2->komvosOura->StartServing<<"\t";
		cout<<tempfirst2->komvosOura->FinishServing<<"\t";
		cout<<endl;
		tempfirst2=tempfirst2->next;
	}
	cout<<endl;*/

	timing();
	//system("pause");
    }
    
    BubbleSort();                                       
    
    report();
       
system("pause");
return 0;
}


void BubbleSort() //Ta3inomhsh Bubble sort
{
    float temp = 0;
    bool flag=false; //ean ginetai allagh 
    int i,sz;
    
    for(sz=n;sz>1;sz--)
    {
     flag = false;
       for(i=0;i<n-1;i++)
         if(TotalWaitingTime[i] > TotalWaitingTime[i+1]) 
         { 
            temp=TotalWaitingTime[i];
            TotalWaitingTime[i]=TotalWaitingTime[i+1];
            TotalWaitingTime[i+1]=temp;
            flag = true;
         }
     if(!flag) break;
    }
         
    //typwsi
    //for(i=0;i<n;i++)
    //cout<<TotalWaitingTime[i]<<endl;
}


////////////////////////////////////////////////////////////////////////////////
/*                      Ylopoihsh Poutinwn                                    */
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
void initialization()
{
     Time = 0; 
     
     ServerIsBusy = false;
     QueueSize = 0; 
     LastEvent = 0;
     
     FreeTime = 0;      
     Lq = 0;              
     Wq = 0;            
     W = 0;             
     servedCustomers = 0; 
     Counter4plus = 0;    
     Counter1wraplus = 0;
     
     Arrivals = (float*)malloc(sizeof(float)*(n+1));
     Service  = (float*)malloc(sizeof(float)*(n+1));
     TotalWaitingTime = (float*)malloc(sizeof(float)*(n+1));
     
     next = 1; //8a deixnei thn epomenh 8esh twn pinakwn Arrivals kai Service
     
     /*
     l = 1/6 einai o ru8mos afi3ewn pelatwn (pelates ana lepto)
     */
     float l = float(1) / float(6);
     
     /*
     m = 1/5 einai o ru8mos xronikhs diarkeias e3yphrethshs pelatwn (e3uphrethsh pelatwn ana lepto)
     */
     float m = float(1) / float(5);
     
     //Metablhths opou boh8aei na exoume ta a8roismata twn afi3ewn, wste o pinakas Arrivals na einai se au3ousa seira
     float tempA = 0;
     
     int i=0;
     TotalWaitingTime[i] = 0;
     Arrivals[i] = 0;
     Service[i] = 0;
     for( i=1; i < (n+1); i++ )
     {
          //rand() % 32767 + 1 pernoume times mono apo [1,32767],dhl. apotrepoume to mhden 
          //A = ln(1-R)/-l
          tempA += float( log( float(1) - float( rand() % 32767 + 1 ) / float(32767 + 1 )) )/  float( -l );
          Arrivals[i] = tempA;
          
          //S = ln(1-R)/-m
          Service[i] = float( log( float(1) - float( rand() % 32767 + 1 ) / float(32767 + 1 )) )/  float( -m );
     }
     
     
     /*int j=0;
     for(j=0;j<n+1;j++)
     cout<<Arrivals[j]<<"\t\t"<<Service[j]<<endl;
     system("pause");*/
     
}


//---------------------------------------------------------------------------------------------------------------
void timing()
{
     //cout<<"timing oura.isEmpty() = "<<oura.isEmpty()<<endl;
     
     while( (Time <= Arrivals[next] && Arrivals[next] < (Time + 1) ) || 
                ( ServerIsBusy == true && 
                  (Time <= oura.front->komvosOura->FinishServing && oura.front->komvosOura->FinishServing < (Time + 1)) 
                ) 
          )
     {
          if(Time <= Arrivals[next] && Arrivals[next] < (Time + 1))
            arrival();
          
          if( ServerIsBusy == true && 
               (Time <= oura.front->komvosOura->FinishServing && oura.front->komvosOura->FinishServing < (Time + 1)) 
            )
            departure();
          
     }//end while
     
     Time++;
}

//------------------------------------------------------------------------------
void arrival()
{
     float arrival,start,end;
     
     arrival = Arrivals[next];
     
     if(oura.isEmpty())
     {//cout<<"oura Adeia stin arrival\n";
           start = arrival;
           end = start + Service[next];
           
           //enhmerwsh metablhtwn
           FreeTime += arrival - LastEvent;
           ServerIsBusy = true;
     }
     else //oura den einai adeia
     {//cout<<"oura DEN Adeia stin arrival\n";
          
          if(oura.rear->komvosOura->FinishServing < arrival)
          {
               start = arrival;
               end = start +  Service[next];
               
               //enhmerwsh metablhtwn
               FreeTime +=  start - oura.rear->komvosOura->FinishServing;
          }
          else // h lh3h tou xronou e3yphrethshs tou teleutaiou pelath sthn anamonh einai >= arrival
          {
               start = oura.rear->komvosOura->FinishServing;
               end = start +  Service[next];
          }
     }
     
     oura.push(arrival,start,end);
     QueueSize++; 
     
     /*cout<<"Egine push to \n";
     cout<<oura.rear->komvosOura->Arrival<<"\t";
     cout<<oura.rear->komvosOura->StartServing<<"\t";
	 cout<<oura.rear->komvosOura->FinishServing<<"\t";
	 cout<<endl;
     system("pause");*/
     
     Wq += start - arrival;
     
     W += end - arrival; //anamonh + e3yphrethsh => (start - arrival) + (end - start)
     
     //anamonh + e3yphrethsh
     if( (end - arrival) > 60 )  Counter1wraplus++;
     
     TotalWaitingTime[next] = end - arrival;
     
     next++;
}

//------------------------------------------------------------------------------
void departure()
{
     //cout<<"Mphka departure\n";
     
     //enhmerwsh metablhtwn
     if(QueueSize > 4) Counter4plus++;
     LastEvent = oura.front->komvosOura->FinishServing;
     QueueSize--;
     
     //diagrafh apo thn oura o prwtos pou e3yphreth8hke
     oura.pop();
     
     if(oura.isEmpty()) ServerIsBusy = false;
     
     Lq += QueueSize;
     //cout<<QueueSize<<"\t";
     
     
     
     servedCustomers++;
}

//------------------------------------------------------------------------------
void report()
{
     //erwthma1
     printf("Mesos ari8mos pelatwn se anamonh einai: Lq = %f\n\n", float(Lq)/ float(n) );
     
     //erwthma2
     printf("Mesos ari8mos pelatwn synolika sthn trapeza einai: L = %f\n\n", float(Lq)/ float(n) + 1 ); //(Lq+n)/n
     
     //erwthma3
     printf("Meso xroniko diasthma anamonhs pelath sthn oura: Wq = %f lepta\n\n", float(Wq)/ float(n) );
     
     //erwthma4
     printf("Meso xroniko diasthma paramonhs pelath sthn trapeza: W = %f lepta\n\n", float(W)/ float(n) );
     
     //erwthma5
     printf("Pi8anothta na perimenoun perissoteroi apo 4 pelates sthn oura einai:  %f %%\n\n", float(Counter4plus)/ float(n) *100 );
     
     //erwthma6
     printf("Pososto tou xronou opou o tamias einai aposxolhmenos:  %f %%\n\n", float(LastEvent-FreeTime)/ float(LastEvent) *100 );
     
     //erwthma7
     printf("Pososto pelatwn pou 8a perasei perissoterh apo mia wra sthn trapeza: %f %%\n\n", float(Counter1wraplus)/ float(n) *100);
     
     //erwthma8
     //n = P/100 *N +1/2
     float p90 = float(90)/ float(100) * n + 0.5;
     float p95 = float(95)/ float(100) * n + 0.5;
     
     printf("To pw[90] pososthmoria tou xronou paramonhs einai: %f lepta \n\n", TotalWaitingTime[int(p90)] );
     printf("To pw[95] pososthmoria tou xronou paramonhs einai: %f lepta \n\n", TotalWaitingTime[int(p95)] );
}
