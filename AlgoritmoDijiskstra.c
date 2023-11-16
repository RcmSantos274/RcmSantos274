#include <stdlib.h>
#include <stdio.h>

int main() {
    int v;

    printf("\nDigite a quantidade de vertices: ");
    scanf("%d", &v);

    if (v > 0) {
        int m[v][v];
        char name[v][30];

        for (int f = 0; f < v; f++) {
            printf("\nNome do vertice %d: ", f);
            scanf("%s", name[f]);
        }

        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                 
                printf("\nDigite a kilometragem da cidade %s para a cidade %s: ", name[i], name[j]);
                scanf("%d", &m[i][j]);
                
            }
        }

        for (int s = 0; s < v; s++) {
            for (int l = 0; l < v; l++) {
                if (s != l && m[s][l]!= 999) {
                    printf("\nA kilometragem da cidade %s para a cidade %s e: %d", name[s], name[l], m[s][l]);
                }
            }
        }
        
        int mfinal[v][3];

        for(int x=0; x<v; x++){
           for(int w=0; w<v; w++){
              if( m[x][w]!= 999 && m[x][w] != 0 && mfinal[w][0] != 1){
                if(mfinal[x][2]+m[x][w] < mfinal[w][2]){ 
                   mfinal[w][0] = 0;
                   mfinal[w][1] = name[x];
                   mfinal[w][2] = m[x][w]+mfinal[x][2];
                }
                else{
                    mfinal[w][0] = 0;
                    mfinal[w][1] = name[x];
                    mfinal[w][2] = m[x][w];
                }
              }
              else if(m[x][w] = 0){
                mfinal[w][0] = 1;
                mfinal[w][1] = name[x];
                mfinal[w][2] = m[x][w];
              }
            }
            //mfinal[x][0] = 1;
        }

        for (int d = 0; d < v; d++) {
            printf("Matriz final de %s \nFechada: %d\nAntdescente: %d\n Peso: %d",name[d], mfinal[d][0], mfinal[d][1], mfinal[d][2]);
            
        }




    }else {
        printf("\nAs vertices tem que ser positivas");
    }

    return 0;
}
