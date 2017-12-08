#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <time.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct _SYSTIME
{
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} systime;

typedef struct node* lista;

typedef struct node
{
    char primeiro_nome[35];
    char ultimo_nome[35];
    int cor; /* 0-em triagem, 1-vermelho, 2-laranja, 3-verde*/
    int num_bi;
    int hora, minuto, dia, mes, ano;
    systime data;
    lista prev;
    lista next;
} node_lista;

void menu();
lista cria_lista(void);
void guarda_ficheiro_porcima(lista l1);
void guarda_ficheiro_append(int dia, int mes, int ano, int hora, int minuto, int cor, char primeiro_nome[], char ultimo_nome[], int num_bi);
void guarda_ficheiro_append2(lista l1);
void entrada();
void atribuir();
void carrega_espera(lista l1);
void carrega_verde(lista l1);
void carrega_amarelo(lista l1);
void carrega_vermelho(lista l1);
void insere_lista(lista aux, int dia,int mes,int ano,int hora,int minuto,int cor,char primeiro_nome[],char ultimo_nome[],int num_bi);
void cancelar_bi();
int procura_bi_elimina(lista l1, int bi);
void imprime_lista_prioridades2();
void imprime_lista_prioridades();
void imprime_lista(lista l1);
void imprime_lista_contrario(lista l1);
void limpar (void);
void atendimento();

#endif // HEADER_H_INCLUDED
