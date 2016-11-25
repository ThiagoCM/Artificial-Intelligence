/* Professor, não conseguimos separar o código em vários arquivos. Talvez esteja um pouco bagunçado
 * por estar num arquivo só. Também não utilizamos o cálculo de baldeação.*/

#include <stdio.h>
#include <math.h>
#define TAM 14
#define QNT_VIZINHOS 4
#define MAX_VALOR 500


int matriz_distancias[TAM][TAM] = { { 0, 11, 20, 27, 40, 43, 39, 28, 18, 10, 18, 30, 30, 32 }, //E1
                         {11, 0, 9, 16, 29, 32, 28, 19, 11, 4, 17, 23, 21, 24 }, //E2
                         {20, 9, 0, 7, 20, 22, 19, 15, 10, 11, 21, 21, 13, 18 }, //E3
                         {27, 16, 7, 0, 13, 16, 12, 13, 13, 18, 26, 21, 11, 17 }, //E4
                         {40, 29, 20, 13, 0, 3, 2, 21, 25, 31, 38, 27, 16, 20 }, //E5
                         {43, 32, 22, 16, 3, 0, 4, 23, 28, 33, 41, 30, 17, 20 }, //E6
                         {39, 28, 19, 12, 2, 4, 0, 22, 25, 29, 38, 28, 13, 17 }, //E7
                         { 28, 19, 15, 13, 21, 23, 22, 0, 9, 22, 18, 7, 25, 30 }, //E8
                         { 18, 11, 10, 13, 25, 28, 25, 9, 0, 13, 12, 12, 23, 28 }, //E9
                         { 10, 4, 11, 18, 31, 33, 29, 22, 13, 0, 20, 27, 20, 23 }, //E10
                         { 18, 17, 21, 26, 38, 41, 38, 18, 12, 20, 0, 15, 35, 39 }, //E11
                         { 30, 23, 21, 21, 27, 30, 28, 7, 12, 27, 15, 0, 31, 37 }, //E12
                         { 30, 21, 13, 11, 16, 17, 13, 25, 23, 20, 35, 31, 0, 5 }, //E13
                         { 32, 24, 18, 17, 20, 20, 17, 30, 28, 23, 39, 37, 5, 0 } }; //E14
//Matriz que representa os vizinhos de cada estação
int vizinhos[TAM][QNT_VIZINHOS] = { {2,0,0,0},  //Vizinhos da Estação E1
                                  {1,3,9,10},   //Vizinhos da Estação E2
                                  {2,4,9,13},   //Vizinhos da Estação E3
                                  {3,5,8,13},   //Vizinhos da Estação E4
                                  {4,6,7,8},    //Vizinhos da Estação E5
                                  {5,0,0,0},    //Vizinhos da Estação E6
                                  {5,0,0,0},    //Vizinhos da Estação E7
                                  {4,5,9,12},   //Vizinhos da Estação E8
                                  {2,3,8,11},   //Vizinhos da Estação E9
                                  {2,0,0,0},    //Vizinhos da Estação E10
                                  {9,0,0,0},    //Vizinhos da Estação E11
                                  {8,0,0,0},    //Vizinhos da Estação E12
                                  {3,4,14,0},   //Vizinhos da Estação E13
                                  {13,0,0,0} };     //Vizinhos da Estação E14

int caminho[TAM] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //Array que contém o caminho feito pelo usuário
int posicao = 0; //Interior que auxilia na locomoção pelo array de caminho e pelo array de custo
int custos[TAM] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //Array que guarda o custo de uma estação para outra,
                                                //quando o mesmo precisa voltar da estação X para a
                                                //estação X-1(pai de X) por ter encontrado um caminho melhor

//Função heurística, que é a distância em linha reta de uma estação a outra.Retorna a distância em linha reta de uma estação a outra.
int f_heuristica(int estacao_atual, int estacao_final){
    int dist_linha_reta = matriz_distancias[estacao_atual-1][estacao_final-1];
    return dist_linha_reta;
}
//Função que é somada com a função heurística. Ela também utiliza a distância em linha reta de uma estação a outra, o que
//pode ser um problema. Retorna a distância em linha reta de uma estação a outra.
int f_custo(int estacao_atual, int estacao_inicial){
    int custo_acumulado = matriz_distancias[estacao_atual-1][estacao_inicial-1];
    return custo_acumulado;
}
//Retorna a soma da função heurística e da função custo. Serve para determinar o caminho que o usuário deve percorrer
//pelo metrô para chegar da estação de escolha a qualquer estação final escolhida.
int f(int estacao_atual, int estacao_vizinha, int estacao_destino, int custo_acumulado){
    return custo_acumulado + f_custo(estacao_atual, estacao_vizinha) + f_heuristica(estacao_vizinha, estacao_destino);
}
//Função utilizada para saber se o caminho estava sendo calculado corretamente.
/*int buscaAnterior(int estacao){
    for (int var = 0; var < TAM; ++var) {
        if(caminho[var]==estacao){
            return caminho[--var];
        }
    }
    return 0;
}*/
//Função que representa a aplicação do A*. Ela é recursiva, e a condição de parada é: a estação que representa o menor
//custo na função f ser a estação destino escolhida pelo usuário. Também existem condições para a função seguir um deter
//minado padrão ou passar parâmetros diferentes dos esperados, que é como o A* se comporta ao expandir um caminho e
//em seguida perceber que há outro melhor(mais barato) do que o que está sendo expandido.
void a_estrela(int estacao_atual, int estacao_destino, int estacao_anterior, int custo_acumulado){

    int estacoes[QNT_VIZINHOS];
    int menor_custo = INFINITY;
    int estacao_custo_acumulado = 0;
    int estacao_menor_custo = 0;
    for(int i=0; i<QNT_VIZINHOS; i++){
        estacoes[i] = vizinhos[estacao_atual-1][i];
    }
    for (int var = 0; var < QNT_VIZINHOS; ++var) {
        if(estacoes[var]!=0 && estacoes[var]!=estacao_anterior){
            int valor_f = f(estacao_atual, estacoes[var], estacao_destino, custo_acumulado);
            if(menor_custo > valor_f){
                menor_custo = valor_f;
                estacao_menor_custo = estacoes[var];
                estacao_custo_acumulado = custo_acumulado + f_custo(estacao_atual, estacoes[var]);
            }
        }
    }

    if(estacao_menor_custo==estacao_destino){
        printf("\nestacao: %d | custo: %d", estacao_menor_custo, menor_custo);
    } else {
        printf("\n%d | estacao-atual: %d  | estacao: %d\n", estacao_custo_acumulado, estacao_atual, estacao_menor_custo);
        if(estacao_menor_custo==0){
            matriz_distancias[estacao_atual-1][estacao_anterior-1] = MAX_VALOR;
            matriz_distancias[estacao_anterior-1][estacao_atual-1] = MAX_VALOR;
            a_estrela(estacao_anterior, estacao_destino, buscaAnterior(estacao_anterior), custos[posicao-1]);//erro
        } else {
            caminho[posicao] = estacao_atual;
            custos[posicao] = custo_acumulado;
            posicao++;
            a_estrela(estacao_menor_custo, estacao_destino, estacao_atual, estacao_custo_acumulado);
        }
        //}
    }
}

int main()
{
    int estacao_atual, estacao_destino;
    printf("Digite a estacao atual:\n");
    scanf("%d", &estacao_atual);
    printf("Digite a estacao destino:\n");
    scanf("%d", &estacao_destino);
    a_estrela(estacao_atual, estacao_destino, 0, 0);
    return 0;
}
