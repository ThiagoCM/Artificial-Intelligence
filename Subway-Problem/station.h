#ifndef ESTACAO_H
#define ESTACAO_H


class Estacao
{
    Estacao *pai;
public:
    Estacao();
    int distancia(Estacao atual);
    void init_metro();
    int baldeacao();
    int tempo_total(int distancia, int baldeacao);
    Estacao gerar_filhos(Estacao atual);
    int heuristica(int d_reta);
};

#endif // ESTACAO_H
