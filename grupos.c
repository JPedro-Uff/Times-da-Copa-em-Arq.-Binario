#include "grupos.h"
#include "partidasFG.h"

Grupo *criaGrupo()
{
    int t, i = 0;
    char idGrupo;
    Grupo *novo = (Grupo *)malloc(sizeof(Grupo));
    scanf(" %c", &idGrupo);
    novo->ID = idGrupo;
    while (i <= 3)
    {
        scanf("%d", &t);
        novo->times[i] = t;
        novo->saldoGols[i] = 0;
        novo->ved[i][0] = 0;
        novo->ved[i][1] = 0;
        novo->ved[i][2] = 0;
        novo->pontos[i] = 0;
        i++;
    }
    return novo;
}

Grupo *leGrupo(FILE *grupos)
{
    Grupo *atual = (Grupo *) malloc(sizeof(Grupo));
    fread(&atual->ID, sizeof(char), 1, grupos);
    fread(&atual->times, sizeof(int), 4, grupos);
    fread(&atual->pontos, sizeof(int), 4, grupos);
    fread(&atual->ved, sizeof(int), 12, grupos);
    fread(&atual->saldoGols, sizeof(int), 4, grupos);
    return atual;
}

Grupo *buscaGrupo(FILE *grupos, char id)
{
    Grupo *achado = (Grupo*) malloc(sizeof(Grupo));
    int posicao = 97*(id-65);
    
    fseek(grupos, posicao, SEEK_SET);
    
    achado = leGrupo(grupos);
    return achado;
    
}

void printaGrupo(char idGrupo)
{
    FILE *grupos = fopen("grupos.txt", "ab+");
    FILE *times = fopen("times.txt", "ab+");
    Time *atuais[4];
    int j = 0;
    Grupo *atual = buscaGrupo(grupos, idGrupo);
    
    printf("GRUPO %c\n\n", atual ->ID);
    printf("\tP\t\tV\t\tE\t\tD\t\tSG\n\n");
    while(j <= 3){
        atuais[j] = buscaTime(times, atual ->times[j]);
        printf("%c%c%c\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", atuais[j] ->nome[0], 
        atuais[j] ->nome[1], atuais[j] ->nome[2], atual ->pontos[j], atual ->ved[j][0],
        atual ->ved[j][1],atual ->ved[j][2], atual ->saldoGols[j]);
        j++;
    }

    printf("\n\n");
    printaPartidaFG(idGrupo);
    printf("\n\n");
    free(*atuais);
}

void printaGrupos()
{
    int i = 0;
    while (i <= 7){
        printaGrupo(65+i);
        i++;
    }
}

void insereGrupos()
{
    Grupo *atual;
    int i = 0;
    FILE *grupos;
    grupos = fopen("grupos.txt", "wb");
    while (i <= 7)
    {
        atual = criaGrupo();
        fwrite(&atual->ID, sizeof(char), 1, grupos);
        fwrite(atual->times, sizeof(int), 4, grupos);
        fwrite(atual->pontos, sizeof(int), 4, grupos);
        fwrite(atual->ved, sizeof(int), 12, grupos);
        fwrite(atual->saldoGols, sizeof(int), 4, grupos);
        i++;
        free(atual);
    }
    fclose(grupos);
}

Grupo *zeraGrupo(Grupo *grupo){
    grupo->pontos[0] = 0;
    grupo->pontos[1] = 0;
    grupo->pontos[2] = 0;
    grupo->pontos[3] = 0;
    grupo->saldoGols[0] = 0;
    grupo->saldoGols[1] = 0;
    grupo->saldoGols[2] = 0;
    grupo->saldoGols[3] = 0;
    for(int i = 0; i <= 3; i++){
        grupo->ved[i][0] = 0;
        grupo->ved[i][1] = 0;
        grupo->ved[i][2] = 0;
    }
    return grupo;
}

void recomeca(){
    FILE *grupos = fopen("grupos.txt", "rb+");
    Grupo *atual;
    int i = 0;
    while(i <= 7){
        atual = leGrupo(grupos);
        atual = zeraGrupo(atual);
        fseek(grupos, -97, SEEK_CUR);
        fwrite(&atual->ID, sizeof(char), 1, grupos);
        fwrite(atual->times, sizeof(int), 4, grupos);
        fwrite(atual->pontos, sizeof(int), 4, grupos);
        fwrite(atual->ved, sizeof(int), 12, grupos);
        fwrite(atual->saldoGols, sizeof(int), 4, grupos);
        i++;
    }
    free(atual);
    fclose(grupos);   
}

void organizaGrupos()
{
    FILE *grupostxt = fopen("grupos.txt", "rb+");
    FILE *partidasFGtxt = fopen("partidasFG.txt", "rb+");
    FILE *timestxt = fopen("times.txt", "rb+");
    PartidaFG *partidaAtual;
    Grupo *grupoAtual;

    int i=0, j, k, l, m, n, aux, vedAUX[3];
    while(i!=8)
    {
        grupoAtual = leGrupo(grupostxt);
        grupoAtual = zeraGrupo(grupoAtual);
        j = 0;
        while(j<=5)
        {
            partidaAtual = lePartida(partidasFGtxt);
            k = 0;
            while(k<=1)
            {
                l = 0;
                while(l<=3)
                {
                    if(partidaAtual->times[k] == grupoAtual->times[l]) break;
                    l++;
                }
                int saldo, pontos;
                if(k == 0) saldo =  partidaAtual->placar[k] - partidaAtual->placar[k+1];
                else saldo = partidaAtual->placar[k] - partidaAtual->placar[k-1];

                if (saldo > 0){
                    pontos = 3;
                    grupoAtual->ved[l][0] = grupoAtual->ved[l][0] + 1;
                }
                else if(saldo < 0) {
                    pontos = 0;
                    grupoAtual->ved[l][2] = grupoAtual->ved[l][2] + 1;
                    }
                else {
                    pontos = 1;
                    grupoAtual->ved[l][1] = grupoAtual->ved[l][1] + 1;
                    }
                grupoAtual->saldoGols[l] = grupoAtual->saldoGols[l] + saldo;
                grupoAtual->pontos[l] = grupoAtual->pontos[l] + pontos;
                k++;
            }
            j++;
        }
        m = 0;
        while(m < 4){
            n = 0;
            while(n < 3){
                if ((grupoAtual->pontos[n] < grupoAtual->pontos[n+1]) ||
                 ((grupoAtual->pontos[n] == grupoAtual->pontos[n+1]) && 
                 (grupoAtual->saldoGols[n] < grupoAtual->saldoGols[n+1]))){

                    aux = grupoAtual->pontos[n];
                    grupoAtual->pontos[n] = grupoAtual->pontos[n+1];
                    grupoAtual->pontos[n+1] = aux;

                    aux = grupoAtual->times[n];
                    grupoAtual->times[n] = grupoAtual->times[n+1];
                    grupoAtual->times[n+1] = aux;

                    aux = grupoAtual->saldoGols[n];
                    grupoAtual->saldoGols[n] = grupoAtual->saldoGols[n+1];
                    grupoAtual->saldoGols[n+1] = aux;

                    vedAUX[0] = grupoAtual->ved[n][0];
                    vedAUX[1] = grupoAtual->ved[n][1];
                    vedAUX[2] = grupoAtual->ved[n][2];
                    grupoAtual->ved[n][0] = grupoAtual->ved[n+1][0];
                    grupoAtual->ved[n][1] = grupoAtual->ved[n+1][1];
                    grupoAtual->ved[n][2] = grupoAtual->ved[n+1][2];
                    grupoAtual->ved[n+1][0] = vedAUX[0];
                    grupoAtual->ved[n+1][1] = vedAUX[1];
                    grupoAtual->ved[n+1][2] = vedAUX[2];

                }

                n++;
            }
            m++;
        }
        fseek(grupostxt, -97, SEEK_CUR);
        fwrite(&grupoAtual->ID, sizeof(char), 1, grupostxt);
        fwrite(grupoAtual->times, sizeof(int), 4, grupostxt);
        fwrite(grupoAtual->pontos, sizeof(int), 4, grupostxt);
        fwrite(grupoAtual->ved, sizeof(int), 12, grupostxt);
        fwrite(grupoAtual->saldoGols, sizeof(int), 4, grupostxt);
        i++;
    }
    free(grupoAtual);
    free(partidaAtual);
    fclose(grupostxt);
    fclose(partidasFGtxt);
    fclose(timestxt);
}