#include <stdlib.h>
#include <stdio.h>

int main (){

    int v;
    
    printf("\nDigite a quantidade de vertices: ");
    scanf("%d", &v);    
    
    if(v>0){
        int m[v][v];
        for(int i=0; i<v; i++){
           for(int j=0; j<v; j++){
               if(i!=j){ 
               printf("\nDigite a kilometragem da cidade %d para a cidade %d: ", i+1, j+1);
               scanf("%d", &m[i][j]);
               }
            }
        }

        for(int s=0; s<v; s++){
            for(int l=0; l<v; l++){
               if(s!=l){  
                  printf("\nA kilometragem da cidade %d para a cidade %d e: %d", s+1, l+1, m[s][l]);
               }
            }
        }
    }
    else{
        printf("\nAs vertices tem que ser positivas");
    }

    
}
