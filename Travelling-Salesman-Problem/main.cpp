#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define TAM 10
#define TAM_CAMINHO 11

int distancia[TAM][TAM] = { { 0, 30, 84, 56, -1, -1, -1, 75, -1, 80 },
                            { 30, 0, 65, -1, -1, -1, 70, -1, -1, 40 },
                            { 84, 65, 0, 74, 52, 55, -1, 60, 143, 48 },
                            { 56, -1, 74, 0, 135, -1, -1, 20, -1, -1 },
                            { -1, -1, 52, 135, 0, 70, -1, 122, 98, 80 },
                            { 70, -1, 55, -1, 70, 0, 63, -1, 82, 35 },
                            { -1, 70, -1, -1, -1, 63, 0, -1, 120, 57 },
                            { 75, -1, 135, 20, 122, -1, -1, 0, -1, -1 },
                            { -1, -1, 143, -1, 98, 82, 120, -1, 0, -1 },
                            { 80, 40, 48, -1, 80, 35, 57, -1, -1, 0 } } ;
//Função que calcula o custo entre duas cidades, de acordo com a matriz. Retorna esse valor.
int custo(int caminhoTeste[]){
    int custo_total=0;
    int cidade1, cidade2;

    for(int i=0;i<TAM_CAMINHO-1;i++){
        cidade1 = caminhoTeste[i];
        cidade2 = caminhoTeste[i+1];
        custo_total += distancia[cidade1 - 1][ cidade2 - 1];
    }
    return custo_total;
}
//Função que diz se o array passado é uma solução para o problema ou não. Checa se a primeira cidade é a última, e se
//Não há nenhum valor "-1" na matriz distância, pois se houver não há ligação entre as cidades e não é solução. Retorna
//0, se não for solução, e 1 se for solução.
bool ehSolucao(int caminhoTeste[]){
    int cidade1, cidade2, custo;
    if(caminhoTeste[0]!=caminhoTeste[TAM_CAMINHO-1])
        return false;

    for(int i=0;i<TAM_CAMINHO-1;i++){
        cidade1 = caminhoTeste[i];
        cidade2 = caminhoTeste[i+1];
        custo = distancia[cidade1 - 1][ cidade2 - 1];
        if(custo==-1){
            return false;
        }
    }
    return true;
}
//Função que checava se um número pertence a um vetor. Foi retirada.
/*bool cidadeEstaNoVetor(int numero_cidade, int caminho[]){
    for(int i = 0; i < TAM_CAMINHO-1; i++){
        if(numero_cidade==caminho[i])
            return true;
    }
    return false;
}*/
//Função que imprime um array.
void printfSolucao(int caminho[]){
    printf("\n[");
    for (int i = 0; i < TAM_CAMINHO-1; i++) {
        printf("%d, ", caminho[i]);
    }
    printf("]\n");
}

//Função que executa a permutação num array, exceto em seu primeiro e último número.
int permutacao(int caminho[]){
    int b = 0;
    int aux;
    for(int i=0;i<TAM_CAMINHO;++i){
        for(int j=1;j<TAM_CAMINHO-2;++j){
            if(ehSolucao(caminho)){
                printf("\nRota:");
                printfSolucao(caminho);
                printf("\n%d", custo(caminho));
            }
            aux = caminho[j];
            caminho[j] = caminho[j+1];
            caminho[j+1] = aux;
        }
    }

    return 0;

}

int main(){
    int caminho_teste[TAM_CAMINHO];
    printf("Digite a rota desejada:");
    for(int i = 0; i<TAM_CAMINHO;i++){
        scanf("%d", &caminho_teste[i]);
    }
    printf("%d", ehSolucao(caminho_teste));
    printfSolucao(caminho_teste);
    permutacao(caminho_teste);


                /* Tentativa de fazer um array aleatório de números que não se repetem
    do{
        aux = (rand()%10 + 1);
        for(int i=1;i< TAM_CAMINHO; i++){
            for(int j=0;j<TAM_CAMINHO;j++){
                for(int k =0;k<TAM_CAMINHO;k++){
                if(aux != caminho_teste[i] && aux != caminho_teste[j])
                    caminho_teste[i] = aux;
            }
            }
        }
        aux2 = ehSolucao(caminho_teste);
        printfSolucao(caminho_teste);

    }while(aux2 == 0);
*/


    return 0;
}
