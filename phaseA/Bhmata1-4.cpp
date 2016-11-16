//v1 = rand() % 100;         // v1 in the range 0 to 99
//v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
//v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014

#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <string.h>
using namespace std;
double *OmoiomorfhKatanomh(int n);
//A = pinakas arxikopoihshs, n = megethos pinaka A, d = upodiasthmata tou diasthmatos [0,1]
int *Istogramma(double *A, int n, int d , double lowerbound,double upperbound);
void WriteToFile(int *B, int d, char string[20]);
double *EkthetikhKatanomh(int n, double &maxEuros);
int main()
{
    /* Intializes random number generator */
    srand ((unsigned) time(NULL));
    
    //-------------------------------------------------------------------------
    // --------        GIA OMOIOMORFH KATANOMH                     ------------
    //-------------------------------------------------------------------------
    /*
    int n = 1000;
    double *A = OmoiomorfhKatanomh(n); //epistrefei ton arxikopoihmeno pinaka A apo thn rand()
    
    int d = 20;
    int *B = Istogramma(A, n, d , 0 , 1 );//epistrefei ton pinaka B opou perilambanei ths suxnothtes emfanishs tou ka8e ypodiasthmatos apo [0,1]
    
    char filename[20]="Istogramma10000.txt";
    WriteToFile(B, d, filename);
    */
    
    
    //-------------------------------------------------------------------------
    // --------        GIA EKTHETIKH KATANOMH                     ------------
    //-------------------------------------------------------------------------
    
    /*
    int n = 1000;
    
    double maxEurous=0;
    double minEurous=0; //den uparxei mikroteri timi
    double *F = EkthetikhKatanomh(n, maxEurous);//epistrefei ton arxikopoihmeno pinaka F ths ekthetikhs katanomhs kai to megisto arithmo tou eurous tou pinaka F
    
    //printf("==>%f\n", maxEurous);
    
    int d = 20;
    int *B = Istogramma(F, n, d, 0 , maxEurous);//epistrefei ton pinaka B opou perilambanei ths suxnothtes emfanishs tou ka8e ypodiasthmatos apo [0,1/4] 
       
    char filename[20]="Ekthetikh10000.txt";
    WriteToFile(B, d, filename);
    */
system("pause");
return 0;
}

double *EkthetikhKatanomh(int n, double &maxEurous)
{
    double *F;              //pinakas ek8etikhs katanomhs F 
    F = (double*)malloc(sizeof(double)*n);
    
    double Sum = 0; //athroisma gia thn euresh ths meshs timhs E(x) 
    double Sum2 = 0; //athroisma gia thn euresh ths meshs timhs E(x^2) 
    
    double l = 0.25; // l = 1/4
    
    int i;
    for(i=0; i<n; i++)
    {
             //rand() % 32767 + 1 pernoume times mono apo [1,32767],dhl. apotrepoume to mhden 
            //x = ln(1-R)/-l
            F[i] = double( log( float(1) - float( rand() % 32767 + 1 ) / float(32767 + 1 )) )/  double( -l ); 
            if(F[i]> maxEurous) maxEurous = F[i];
            //printf("%.4f\t",F[i]);
            Sum = Sum + F[i];
            Sum2 = Sum2 + pow(F[i],2);
    }
    
    cout<<"\nGia thn Ekthetikh Katanomh exoume:\n";
    double MT = (float(Sum) / float(n)); //Mesh Timh E(x)
    
    double MT2 = (float(Sum2) / float(n)); //Mesh Timh E(x^2)
    
    double Var = MT2 - pow(MT,2); //Diaspora
    
    double s = sqrt(Var); //Tupikh Apoliksh
    
    printf("\nMT = %f\nMT2 = %f\nVar = %f\ns = %f\n\n",MT, MT2, Var, s);
    
    return F;
}

double *OmoiomorfhKatanomh(int n)
{
    double *A; //pinakas omoiomorfhs katanomhs A
    A = (double*)malloc(sizeof(double)*n);
    
    double Sum = 0; //athroisma gia thn euresh ths meshs timhs E(x) 
    double Sum2 = 0; //athroisma gia thn euresh ths meshs timhs E(x^2) 
    int i;
    for(i=0; i<n; i++)
    {
            A[i] = float( rand() % 32767 ) / float(32767) ;
            //printf("%.4f\t",A[i]);
            Sum = Sum + A[i];
            Sum2 = Sum2 + pow(A[i],2);
    }
    
    cout<<"\nGia thn Omoiomorfh Katanomh exoume:\n";
    double MT = (float(Sum) / float(n)); //Mesh Timh E(x)
    
    double MT2 = (float(Sum2) / float(n)); //Mesh Timh E(x^2)
    
    double Var = MT2 - pow(MT,2); //Diaspora
    
    double s = sqrt(Var); //Tupikh Apoliksh
    
    printf("\nMT = %f\nMT2 = %f\nVar = %f\ns = %f\n\n",MT, MT2, Var, s);
    
    return A;
}

int *Istogramma(double *A, int n, int d, double lowerbound, double upperbound)
{
    int *B; //pinakas opou perilambanei ths suxnothtes emfanishs tou ka8e ypodiasthmatos apo [0,1]
    B = (int*)malloc(sizeof(int)*d);
    
    double Euros = upperbound - lowerbound;
    double Bhma = double(Euros)/double(d);
    
    
    //arxikopoihsh tou pinaka B
    int k;
    for(k=0; k<d;k++) B[k]=0;
    
    int i,j;   
    for( i = 0; i < d; i++)
    {
         for( j = 0; j < n; j++ )
              if( double(Bhma*i) < A[j] && A[j] <= double(Bhma*(i+1)) )
                      B[i]++;
         
         //cout<<B[i]<<endl;
    }
    
    return B;
}

void WriteToFile(int *B, int d, char string[20])
{
    //Dhmiourgia arxeiou opou perilambanei tis times pou epistrefei o pinakas B
    FILE *arxeio; 
    char filename[20];
    strcpy(filename,string);
   	arxeio=fopen(filename,"w");
    if(arxeio==NULL)
    {
    	printf("Provlima kata to anoigma tou arxeiou.\n");       
    	system("pause");
    	exit(-1);
    }
    
    int i;
    for(i=0; i<d; i++)
    {
             fprintf(arxeio,"%d\n",B[i]);
    }
    
    fclose(arxeio);     
}
