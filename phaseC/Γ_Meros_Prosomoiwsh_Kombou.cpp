#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <string.h>

#include "Oura.h"       //Ylopoihsh Ouras
#define n 1000          //plithos pelatwn
using namespace std;

float Time; //Poloi prosomoiwshs

///////////////////////////////////////////////////////////////////////////////
//                          Metablhtes Katastashs  

bool ServerIsBusy; //Katastash tou Server True i False
int QueueSize;     //Plh8os ouras, xwris na prosmetra ton e3yphretoumeno pelath
float LastEvent;   //Xronikh Stigmh Teleutaiou Gegonotos
int K=3;             //arithmos buffers

///////////////////////////////////////////////////////////////////////////////
//                          Statistikoi Apari8mhtes
//                          (Parametroi Epidoshs)

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
    
    
    while( next < (n+1) )
    {
           timing();
    }
    
    BubbleSort();                                       
    
    report();
       
system("pause");
return 0;
}



//------------------------------------------------------------------------------
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
     
}


//---------------------------------------------------------------------------------------------------------------
void timing()
{
         
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
     if(QueueSize < (K-1))  //ean to plh8os ouras einai mikrotero apo to buffer
     {
         float arrival,start,end;
         
         arrival = Arrivals[next];
         
         
         if(oura.isEmpty())
         {
               start = arrival;
               end = start + Service[next];
               
               //enhmerwsh metablhtwn
               FreeTime += arrival - LastEvent;
               ServerIsBusy = true;
         }
         else //oura den einai adeia
         {
              
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
         
         Wq += start - arrival;
         
         W += end - arrival; //anamonh + e3yphrethsh => (start - arrival) + (end - start)
         
         //anamonh + e3yphrethsh
         if( (end - arrival) > 60 )  Counter1wraplus++;
         
         TotalWaitingTime[next] = end - arrival;
     }
     next++;
}

//------------------------------------------------------------------------------
void departure()
{    
     //enhmerwsh metablhtwn
     if(QueueSize > 4) Counter4plus++;
     LastEvent = oura.front->komvosOura->FinishServing;
     
     
     //diagrafh apo thn oura, o prwtos pou e3yphreth8hke
     oura.pop();
     
     if(oura.isEmpty()) ServerIsBusy = false;
     
     Lq += QueueSize;
     
     QueueSize--;
     
     servedCustomers++;
}

//------------------------------------------------------------------------------
void report()
{
     //erwthma1
     printf("Pososto apwleiwn = %f\n\n", float(servedCustomers)/ float(n) );
     
     //erwthma2
     printf("Throughput = %f pelates ana wra\n\n", float(servedCustomers*60)/ float(Time)); //(Lq+n)/n
     
     //erwthma3
     printf("Mesos ari8mos pelatwn se anamonh einai: Lq = %f\n\n", float(Lq)/ float(servedCustomers) );
     
     //erwthma4
     printf("Mesos ari8mos pelatwn synolika sthn trapeza einai: L = %f\n\n", float(Lq)/ float(servedCustomers) + 1 ); //(Lq+n)/n
     
     //erwthma5
     printf("Meso xroniko diasthma anamonhs pelath sthn oura: Wq = %f lepta\n\n", float(Wq)/ float(servedCustomers) );
     
     //erwthma6
     printf("Meso xroniko diasthma paramonhs pelath sthn trapeza: W = %f lepta\n\n", float(W)/ float(servedCustomers) );
     
     //erwthma7
     printf("Pososto tou xronou opou o tamias einai aposxolhmenos:  %f %%\n\n", float(LastEvent-FreeTime)/ float(LastEvent) *100 );
     
}
