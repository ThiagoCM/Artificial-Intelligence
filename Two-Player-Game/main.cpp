#include <stdio.h>

char anotar(int i) {
    switch(i) {
        case -1:
            return 'O';
        case 0:
            return ' ';
        case 1:
            return 'X';
    }
}

void desenhar(int tabuleiro[9]) {
    //"anota" as informações no jogo da velha a depender de quem jogou
    printf(" %c | %c | %c\n",anotar(tabuleiro[0]),anotar(tabuleiro[1]),anotar(tabuleiro[2]));
    printf("-----------\n");
    printf(" %c | %c | %c\n",anotar(tabuleiro[3]),anotar(tabuleiro[4]),anotar(tabuleiro[5]));
    printf("-----------\n");
    printf(" %c | %c | %c\n",anotar(tabuleiro[6]),anotar(tabuleiro[7]),anotar(tabuleiro[8]));
}
    //determina se um jogador ganhou, ou retorna 0 se não ocorrer.
int ganha(int tabuleiro[9]) {

    int tabela[8][3] = {{0,1,2},
                        {3,4,5},
                        {6,7,8},
                        {0,3,6},
                        {1,4,7},
                        {2,5,8},
                        {0,4,8},
                        {2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(tabuleiro[tabela[i][0]] != 0 &&
           tabuleiro[tabela[i][0]] == tabuleiro[tabela[i][1]] &&
           tabuleiro[tabela[i][0]] == tabuleiro[tabela[i][2]]){
            return tabuleiro[tabela[i][2]];
        }
    }
    return 0;
}
    //Qual a provável posição do jogador na sua vez?
int minimax(int tabuleiro[9], int jogador) {
    int vencedor = ganha(tabuleiro);
    if(vencedor != 0) return vencedor*jogador;
    int movimento = -1;
    int pontuar = -20;//No lugar de fazer um movimento "ruim", é melhor não fazer nenhum
    int i;
    for(i = 0; i < 9; ++i) {//Para todas as jogadas
        if(tabuleiro[i] == 0) {//Se o espaço estiver vazio
            tabuleiro[i] = jogador;//Tenta o movimento
            int jogada = -minimax(tabuleiro, jogador*-1);
            if(jogada > pontuar) {
                pontuar = jogada;
                movimento = i;
            }//Escolhe o pior movimento para o oponente.
            tabuleiro[i] = 0;
        }
    }
    if(movimento == -1) {
        return 0; //Se for o player que vai jogar, não fazer nada
    }
      return pontuar;
}

void computador(int tabuleiro[9]) {
    int movimento = -1;
    int pontuar = -20   ;
    int i;
    for(i = 0; i < 9; ++i) {
        if(tabuleiro[i] == 0) {
            tabuleiro[i] = 1;
            int temporario = -minimax(tabuleiro, -1);
            tabuleiro[i] = 0;
            if(temporario > pontuar) {
                pontuar = temporario;
                movimento = i;
            }
        }
    }
    //retorna uma pontuação a depender da árvore minimax no nó dado.
    tabuleiro[movimento] = 1;
}

void jogador(int tabuleiro[9]) {
    int movimento = 0;
    do {
        printf("Lembre-se que: 0 1 2 /n 3 4 5/n 6 7 8\n");
        printf("\nDigite seu movimento ([0..8]): ");
        scanf("%d", &movimento);
        printf("\n");
    } while (movimento >= 9 || movimento < 0 && tabuleiro[movimento] == 0);
    tabuleiro[movimento] = -1;
}

int main() {
    int tabuleiro[9] = {0,0,0,0,0,0,0,0,0};
    //o computador joga em 1, enquanto o jogador joga em -1.
    printf("Computador: O, Jogador: X\nVoce quer ser o primeiro(1) ou o segundo(2)? ");
    int c=0;
    scanf("%d",&c);
    printf("\n");
    for(int vez = 0; vez < 9 && ganha(tabuleiro) == 0; ++vez) {
        if((vez+c) % 2 == 0)
            computador(tabuleiro);
        else {
            desenhar(tabuleiro);
            jogador(tabuleiro);
        }
    }
    switch(ganha(tabuleiro)) {
        case 0:
            printf("Empatou.\n");
            break;
        case 1:
            desenhar(tabuleiro);
            printf("Perdeu.\n");
            break;
        case -1:
            printf("Ganhou!\n");
            break;
    }
}
