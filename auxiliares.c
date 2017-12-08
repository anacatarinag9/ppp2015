#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <time.h>
#include <Windows.h>

void menu()
{
    limpar();
    int opcao, opcao2;
    printf("PROJECTO 2015 PPP\n\n0.Entrada de Utente;\n1.Atribuir Prioridade;\n2.Cancelar Marcacao;\n3.Listar Doentes;\n4.Atendimento;\n\n\nENTER PARA SAIR");
    opcao = getch();
    if(opcao=='0')
    {
        entrada();
    }
    if(opcao=='1')
    {
        atribuir();
    }
    if(opcao=='2')
    {
        cancelar_bi();
    }
    if(opcao=='3')
    {
        limpar();
        printf("PROJECTO 2015 PPP\n\n0.Mais recente para o mais antigo;\n1.Mais antigo para o mais recente;\n\n\n");
        opcao2= getch();
        if (opcao2 == '0')
            imprime_lista_prioridades2();
        if (opcao2 == '1')
            imprime_lista_prioridades();

    }
    if(opcao == '4')
    {
        atendimento();
    }


}

lista cria_lista(void)
{
    lista aux;
    aux = (lista)malloc(sizeof(node_lista));
    if (aux!=NULL)
    {
        aux->next = NULL;
        aux->prev = NULL;
    }
    return aux;

}

void guarda_ficheiro_porcima(lista l1)/*atualiza ficheiro*/
{

    if (l1->next != NULL)
    {
        FILE *fp;
        if (l1->next->cor == 0)
            fp = fopen("espera.txt", "w");
        else if (l1->next->cor == 1)
            fp = fopen("vermelho.txt", "w");
        else if (l1->next->cor == 2)
            fp = fopen("amarelo.txt", "w");
        else if (l1->next->cor == 3)
            fp = fopen("verde.txt", "w");
        l1 = l1->next;
        while (l1 != NULL)
        {
            fprintf(fp, "%d/%d/%d %d:%d %d %s %s %d\n", l1->data.wDay, l1->data.wMonth, l1->data.wYear, l1->data.wHour, l1->data.wMinute, l1->cor, l1->primeiro_nome, l1->ultimo_nome, l1->num_bi);
            l1 = l1->next;
        }
        fclose(fp);
    }
    else/*quando nao ha nada no ficheiro*/
    {
        FILE *fp;
        if (l1->cor == 0)
            fp = fopen("espera.txt", "w");
        else if (l1->cor == 1)
            fp = fopen("vermelho.txt", "w");
        else if (l1->cor == 2)
            fp = fopen("amarelo.txt", "w");
        else if (l1->cor == 3)
            fp = fopen("verde.txt", "w");
        fprintf(fp, "");
        fclose(fp);
    }

}

void guarda_ficheiro_append(int dia, int mes, int ano, int hora, int minuto, int cor, char primeiro_nome[], char ultimo_nome[], int num_bi)/*so de entrada*/
{
    FILE *fp;
    if (cor == 0)
        fp = fopen("espera.txt", "a");
    else if (cor == 1)
        fp = fopen("vermelho.txt", "a");
    else if (cor == 2)
        fp = fopen("amarelo.txt", "a");
    else if (cor == 3)
        fp = fopen("verde.txt", "a");
    fprintf(fp, "%d/%d/%d %d:%d %d %s %s %d\n", dia, mes, ano, hora, minuto, cor, primeiro_nome, ultimo_nome, num_bi);
    fclose(fp);
}

void guarda_ficheiro_append2(lista l1)/*da append no ficheiro dependendo do l1->cor*/
{
    FILE *fp;
    if (l1->cor == 0)
        fp = fopen("espera.txt", "a");
    else if (l1->cor == 1)
        fp = fopen("vermelho.txt", "a");
    else if (l1->cor == 2)
        fp = fopen("amarelo.txt", "a");
    else if (l1->cor == 3)
        fp = fopen("verde.txt", "a");
    fprintf(fp,"%d/%d/%d %d:%d %d %s %s %d\n", l1->data.wDay, l1->data.wMonth, l1->data.wYear, l1->data.wHour, l1->data.wMinute, l1->cor, l1->primeiro_nome, l1->ultimo_nome, l1->num_bi);
    fclose(fp);

}

void entrada()
{
    limpar();
    printf("PROJECTO 2015 PPP\n\n");
    int cor=0, num_bi, dia, mes, ano, hora, minuto;
    char primeiro_nome[35];
    char ultimo_nome[35];
    systime aux;

    printf("Primeiro nome:");
    scanf("%s", &primeiro_nome);
    printf("Ultimo nome:");
    scanf("%s", &ultimo_nome);
    printf("Numero bi:");
    scanf("%d", &num_bi);

    GetSystemTime(&aux);
    dia = aux.wDay;
    mes = aux.wMonth;
    ano = aux.wYear;
    hora = aux.wHour;
    minuto = aux.wMinute;

    guarda_ficheiro_append(dia,mes,ano,hora,minuto,cor,primeiro_nome,ultimo_nome,num_bi);
    printf("O utente deu entrada com sucesso!");
    getch();
    menu();
}

void atribuir()
{
    limpar();
    printf("PROJECTO 2015 PPP\n\n");

    int cor_atribuida;
    lista l1;
    lista anterior, seguinte;
    FILE *fp;


    l1 = cria_lista();
    carrega_espera(l1);
    if (l1->next != NULL)
    {
        l1 = l1->next;


        printf("%d/%d/%d %d:%d %d %s %s %d\n", l1->data.wDay, l1->data.wMonth, l1->data.wYear, l1->data.wHour, l1->data.wMinute, l1->cor, l1->primeiro_nome, l1->ultimo_nome, l1->num_bi);


        printf("\nprioridade:(1-vermelho, 2-amarelo, 3-verde)");
        scanf("%d", &cor_atribuida);

        l1->cor = cor_atribuida;
        guarda_ficheiro_append2(l1);
        if (l1->next == NULL)
        {
            anterior = l1->prev;
            anterior->next = NULL;
            free(l1);
            fp = fopen("espera.txt", "w");
            fprintf(fp,"");
            fclose(fp);

        }
        else
        {
            seguinte = l1->next;
            anterior = l1->prev;
            seguinte->prev = anterior;
            anterior->next = seguinte;
            free(l1);
            anterior = anterior->next;
            guarda_ficheiro_porcima(anterior);
        }
        printf("Foi atribuida a prioridade com sucesso");
        getch();
        menu();
    }
    else
    {
        printf("Nao existiam elementos em triagem");
        getch();
        menu();
    }


}

void carrega_espera(lista l1)/*carrega para uma lista o que esta no ficheiro em questao*/
{
    FILE *fp;
    char primeiro_nome[35];
    char ultimo_nome[35];
    int dia, mes, ano, hora, minuto, cor, num_bi;
    lista aux = l1;

    fp = fopen("espera.txt", "r");
    if (fp!=NULL)
    {
        while(fscanf(fp, "%d/%d/%d %d:%d %d %s %s %d\n", &dia, &mes, &ano, &hora, &minuto, &cor, &primeiro_nome, &ultimo_nome, &num_bi) != EOF)
        {
            insere_lista(aux, dia, mes, ano, hora, minuto, cor, primeiro_nome, ultimo_nome, num_bi);
            aux = aux->next;
        }
        fclose(fp);
    }
    else
    {
        printf("Nao existem utentes nesta lista");
    }
}

void carrega_verde(lista l1)
{
    FILE *fp;
    char primeiro_nome[35];
    char ultimo_nome[35];
    int dia, mes, ano, hora, minuto, cor, num_bi;
    lista aux = l1;

    fp = fopen("verde.txt", "r");
    if (fp!=NULL)
    {
        while(fscanf(fp, "%d/%d/%d %d:%d %d %s %s %d\n", &dia, &mes, &ano, &hora, &minuto, &cor, &primeiro_nome, &ultimo_nome, &num_bi) != EOF)
        {
            insere_lista(aux, dia, mes, ano, hora, minuto, cor, primeiro_nome, ultimo_nome, num_bi);
            aux = aux->next;
        }
        fclose(fp);
    }
    else
    {
        printf("Nao existem utentes nesta lista");
    }
}

void carrega_amarelo(lista l1)
{
    FILE *fp;
    char primeiro_nome[35];
    char ultimo_nome[35];
    int dia, mes, ano, hora, minuto, cor, num_bi;
    lista aux = l1;

    fp = fopen("amarelo.txt", "r");
    if (fp!=NULL)
    {
        while(fscanf(fp, "%d/%d/%d %d:%d %d %s %s %d\n", &dia, &mes, &ano, &hora, &minuto, &cor, &primeiro_nome, &ultimo_nome, &num_bi) != EOF)
        {
            insere_lista(aux, dia, mes, ano, hora, minuto, cor, primeiro_nome, ultimo_nome, num_bi);
            aux = aux->next;
        }
        fclose(fp);
    }
    else
    {
        printf("Nao existem utentes nesta lista");

    }
}

void carrega_vermelho(lista l1)
{
    FILE *fp;
    char primeiro_nome[35];
    char ultimo_nome[35];
    int dia, mes, ano, hora, minuto, cor, num_bi;
    lista aux = l1;

    fp = fopen("vermelho.txt", "r");
    if (fp!=NULL)
    {
        while(fscanf(fp, "%d/%d/%d %d:%d %d %s %s %d\n", &dia, &mes, &ano, &hora, &minuto, &cor, &primeiro_nome, &ultimo_nome, &num_bi) != EOF)
        {
            insere_lista(aux, dia, mes, ano, hora, minuto, cor, primeiro_nome, ultimo_nome, num_bi);
            aux = aux->next;
        }
        fclose(fp);
    }
    else
    {
        printf("Nao existem utentes nesta lista");

    }
}

void insere_lista(lista aux, int dia,int mes,int ano,int hora,int minuto,int cor,char primeiro_nome[],char ultimo_nome[],int num_bi)
{
    lista no;

    no= (lista) malloc (sizeof(node_lista));

    if(no != NULL)
    {
        no->data.wDay = dia;
        no->data.wMonth = mes;
        no->data.wYear = ano;
        no->data.wHour = hora;
        no->data.wMinute = minuto;
        no->cor = cor;
        no->num_bi = num_bi;
        strcpy(no->primeiro_nome, primeiro_nome);
        strcpy(no->ultimo_nome, ultimo_nome);


        aux->next = no;
        no->prev = aux;
        no->next = NULL;

    }
}

void cancelar_bi()
{
    limpar();
    printf("PROJECTO 2015 PPP\n\n");

    int num_bi;
    lista l1, l2, l3, l4;
    l1 = cria_lista();
    l2 = cria_lista();
    l3 = cria_lista();
    l4 = cria_lista();


    printf("Insira o numero do bi do utente:");
    scanf("%d", &num_bi);

    carrega_espera(l1);
    carrega_vermelho(l2);
    carrega_amarelo(l3);
    carrega_verde(l4);

    procura_bi_elimina(l1, num_bi);
    procura_bi_elimina(l2, num_bi);
    procura_bi_elimina(l3, num_bi);
    procura_bi_elimina(l4, num_bi);

    guarda_ficheiro_porcima(l1);
    guarda_ficheiro_porcima(l2);
    guarda_ficheiro_porcima(l3);
    guarda_ficheiro_porcima(l4);

    printf("\n\nSucesso!");

    getch();
    menu();



}

int procura_bi_elimina(lista l1, int bi)
{
    lista anterior, seguinte, inutil;
    l1=l1->next;
    while (l1 != NULL)
    {
        if (l1->num_bi == bi)
        {
            if (l1->next == NULL)/*caso so haja um elemento na lista*/
            {
                inutil = l1;
                anterior = l1->prev;
                l1 = anterior;
                l1->cor = inutil->cor;
                l1->next = NULL;
                free(inutil);
                break;
            }
            seguinte = l1->next;
            anterior = l1->prev;
            seguinte->prev = anterior;
            anterior->next = seguinte;
            free(l1);
            break;
        }
        else
        {
            l1 = l1->next;
        }


    }
}

void imprime_lista_prioridades2()
{
    limpar();
    printf("PROJECTO 2015 PPP\n\n");

    lista l1, aux;
    l1 = cria_lista();
    aux = l1;
    carrega_verde(l1);
    while(l1->next!=NULL)
        l1= l1->next;
    carrega_amarelo(l1);
    while(l1->next!=NULL)
        l1= l1->next;
    carrega_vermelho(l1);
    imprime_lista_contrario(aux);

    getch();
    menu();
}

void imprime_lista_prioridades()
{
    limpar();
    printf("PROJECTO 2015 PPP\n\n");

    lista l1, aux;
    l1 = cria_lista();
    aux = l1;
    carrega_vermelho(l1);
    while(l1->next!=NULL)
        l1= l1->next;
    carrega_amarelo(l1);
    while(l1->next!=NULL)
        l1= l1->next;
    carrega_verde(l1);
    imprime_lista(aux);

    getch();
    menu();
}

void imprime_lista(lista l1)
{
    while (l1->next != NULL)
    {
        l1 = l1->next;
        printf("%d/%d/%d %d:%d %d %s %s %d\n", l1->data.wDay, l1->data.wMonth, l1->data.wYear, l1->data.wHour, l1->data.wMinute, l1->cor, l1->primeiro_nome, l1->ultimo_nome, l1->num_bi);
    }
}

void imprime_lista_contrario(lista l1)
{
    while (l1->next!=NULL)
        l1=l1->next;
    while (l1->prev!=NULL)
    {
        printf("%d/%d/%d %d:%d %d %s %s %d\n", l1->data.wDay, l1->data.wMonth, l1->data.wYear, l1->data.wHour, l1->data.wMinute, l1->cor, l1->primeiro_nome, l1->ultimo_nome, l1->num_bi);
        l1=l1->prev;
    }
}

void limpar (void)
{
    system("cls");
}

void atendimento()
{
    limpar();
    printf("PROJECTO 2015 PPP\n\n");

    lista l1,l2,l3;
    l1= cria_lista();
    l2=cria_lista();
    l3= cria_lista();
    int contador_vermelhos = 0;
    int contador_amarelos = 0;
    int i = 0;

    carrega_vermelho(l1);
    l1= l1->next;
    carrega_amarelo(l2);
    l2 = l2->next;
    carrega_verde(l3);
    l3 = l3-> next;

    while ( i < 20 )
    {
        if (contador_vermelhos < 3 && l1 != NULL)
        {
            printf("%d/%d/%d %d:%d %d %s %s %d\n", l1->data.wDay, l1->data.wMonth, l1->data.wYear, l1->data.wHour, l1->data.wMinute, l1->cor, l1->primeiro_nome, l1->ultimo_nome, l1->num_bi);
            l1 = l1->next;
            contador_vermelhos++;
        }

        else if (contador_vermelhos <=3 && contador_amarelos <5 && l2!= NULL )
        {
            printf("%d/%d/%d %d:%d %d %s %s %d\n", l2->data.wDay, l2->data.wMonth, l2->data.wYear, l2->data.wHour, l2->data.wMinute, l2->cor, l2->primeiro_nome, l2->ultimo_nome, l2->num_bi);
            l2 = l2->next;
            contador_vermelhos= 0;
            contador_amarelos++;

        }
        else if (contador_vermelhos<=3 && contador_amarelos <= 5 && l3!= NULL )
        {
            printf("%d/%d/%d %d:%d %d %s %s %d\n", l3->data.wDay, l3->data.wMonth, l3->data.wYear, l3->data.wHour, l3->data.wMinute, l3->cor, l3->primeiro_nome, l3->ultimo_nome, l3->num_bi);
            l3 = l3->next;
            contador_vermelhos = 0;
            contador_amarelos = 0;
        }
        if (l1 == NULL && l2 == NULL && l3 == NULL)
        {
            break;
        }
        i++;
    }
    getch();
    menu();
}
