#include "project.h"
#include <math.h>

#define PI 3.14159265
#define N 64               
#define DELAY_US 100       
uint8 senoTabla[N];        

void generarTablaSeno(void){
    for(int i = 0; i < N; i++){
        float angulo = (2.0 * PI * i) / N;
        senoTabla[i] = (uint8)(127.5 * sin(angulo) + 127.5);}
}

int main(void)
{
    CyGlobalIntEnable;
    generarTablaSeno();
    VDAC_Start();  
    for(;;){
        for(int i = 0; i < N; i++){
            VDAC_SetValue(senoTabla[i]); 
            CyDelayUs(DELAY_US);          
        }
    }}
