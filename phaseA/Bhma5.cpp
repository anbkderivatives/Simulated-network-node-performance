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

int main()
{
    /* Intializes random number generator */
    srand ((unsigned) time(NULL));
    
    int n=100; //kataxwroume 100 8eseis mhmhs, opou einai yperarketes dioti den prokeitai na ta 3eperasei pote
    double t[n];
    
    //arxikopoihsh pinaka t
    int k;
    for(k=0; k<n;k++) t[k]=0;
    
    double x; //xroniko diasthmata afi3hs
    int afi3eis=0;
    double l = double(1)/double(6); // l = 1/6
    
    double sum=0;
    int i=0;
    while( sum <= 120 )
    {
        //rand() % 32767 + 1 pernoume times mono apo [1,32767],dhl. apotrepoume to mhden 
        //x = ln(1-R)/-l
        x = double( log( float(1) - float( rand() % 32767 + 1 ) / float(32767 + 1 )) )/  double( -l );  
        
        
        sum=sum+x;
        if(sum<=120) { t[i] = sum; afi3eis++; }
        i++;
    }
    
    cout<<"\nGia thn prosomoiwsh twn 120 leptwn eixame: "<<afi3eis<<" afi3eis\n";
    
    cout<<"\nO pinakas twn xronikwn stigmwn twn afi3ewn:\n";
    
    for( i=0; i<afi3eis; i++)
    {
         printf("H %di afi3h: %.4f (se lepta)\n",i+1,t[i]);
    }
    
    printf("\nO pragmatikos ari8mos afi3ewn ths prosomoiwshs einai %.2f pelath ana lepto\n", double(afi3eis)/double(120));
    
    
system("pause");
return 0;
}
