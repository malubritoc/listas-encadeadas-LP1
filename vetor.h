#ifndef VETOR_H
#define VETOR_H

#include <iostream>

template <typename T>
class Vetor
{
private:
    struct No
    {
        T info;
        No *prox;
    };
    No *cabeca;
    int cont;

public:
    // construtor
    Vetor()
    {
        cabeca = NULL;
        cont = 0;
    };

    // destrutor
    ~Vetor()
    {
        No *p = cabeca;
        while (p != NULL)
        {
            No *t = p->prox;
            delete p;
            p = t;
        }
        cont = 0;
    };

    // quantidade de elementos
    int size()
    {
        return cont;
    };

    // adiciona elemento
    bool add(T i_)
    {
        try
        {
            No *novo = new No;
            novo->info = i_;
            novo->prox = NULL;

            if (cabeca == NULL)
            {
                cabeca = novo;
            }
            else
            {
                No *p = cabeca;
                while (p->prox != NULL)
                {
                    p = p->prox;
                }
                p->prox = novo;
            }
            cont++;
            return true;
        }
        catch (std::exception &e)
        {
            return false;
        }
    };

    // remove elemento
    bool remove(int i)
    {
        if (i < 0 || i >= cont)
        {
            return false;
        }

        try
        {
            No *p = cabeca;
            No *ant = NULL;
            for (int j = 0; j < i; j++)
            {
                ant = p;
                p = p->prox;
            }

            if (ant == NULL)
            {
                cabeca = p->prox;
            }
            else
            {
                ant->prox = p->prox;
            }

            delete p;
            cont--;
            return true;
        }
        catch (std::exception &e)
        {
            return false;
        }
    };

    // printa o vetor
    void show()
    {
        No *p = cabeca;
        while (p != NULL)
        {
            std::cout << p->info << " ";
            p = p->prox;
        }
        std::cout << std::endl;
    };

    // encontra a posiçao do vetor
    T at(int i)
    {
        if (i < 0 || i >= cont)
        {
            throw std::out_of_range("Índice inválido");
        }

        No *p = cabeca;
        for (int j = 0; j < i; j++)
        {
            p = p->prox;
        }

        return p->info;
    };

    // ordena o vetor
    bool sort(bool (*func_compara)(T, T))
    {
        if (cont <= 1)
        {
            return false;
        }

        for (int i = 0; i < cont - 1; i++)
        {
            No *p = cabeca;
            No *ant = NULL;
            for (int j = 0; j < i; j++)
            {
                ant = p;
                p = p->prox;
            }

            No *menor = p;
            No *ant_menor = ant;
            No *q = p->prox;
            No *ant_q = p;
            while (q != NULL)
            {
                if (func_compara(q->info, menor->info))
                {
                    menor = q;
                    ant_menor = ant_q;
                }
                ant_q = q;
                q = q->prox;
            }

            if (menor != p)
            {
                if (ant == NULL)
                {
                    cabeca = menor;
                }
                else
                {
                    ant->prox = menor;
                }

                ant_menor->prox = menor->prox;
                menor->prox = p;

                if (ant_menor == p)
                {
                    ant_menor = menor;
                }

                if (ant != NULL)
                {
                    ant = ant_menor;
                }
            }
        }

        return true;
    };
};

#endif
