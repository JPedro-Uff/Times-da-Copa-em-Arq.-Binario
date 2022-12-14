#include "partidasFG.h"
#include "grupos.h"

void inserePartidasFG(){
    FILE *partidas = fopen("partidasFG.txt", "ab+");
    PartidaFG *partida = (PartidaFG *) malloc (sizeof(PartidaFG));
    
    int j = 0;
    while(j <= 7){
        scanf(" %c", &partida ->idGrupo);
        int i = 0;
        while(i <= 5){
            scanf("%d %d %d", &partida ->times[0], &partida ->times[1], &partida ->rodada);
            partida ->placar[0] = 0;
            partida ->placar[1] = 0;
            i++;
            fwrite(&partida ->idGrupo, sizeof(char), 1, partidas);
            fwrite(partida ->times, sizeof(int), 2, partidas);
            fwrite(&partida ->rodada, sizeof(int), 1, partidas);
            fwrite(partida ->placar, sizeof(int), 2, partidas);
        }
        j++;
    }
    fclose(partidas);
    free(partida);
}

PartidaFG *lePartida(FILE *partidas){
    PartidaFG *partidaAtual = (PartidaFG*) malloc(sizeof(PartidaFG));

    fread(&partidaAtual ->idGrupo, sizeof(char), 1, partidas);
    fread(&partidaAtual ->times, sizeof(int), 2, partidas);
    fread(&partidaAtual ->rodada, sizeof(int), 1, partidas);
    fread(&partidaAtual ->placar, sizeof(int), 2, partidas);

    return partidaAtual;
}

void escrevePartidaFG(){
    char grupo;
    int rodada;
    int placar[2][2];
    FILE *partidasFG = fopen("partidasFG.txt", "rb+");
    FILE *timestxt = fopen("times.txt", "ab+");
    PartidaFG *partidas[2];
    Time *times[2];
    while (1){
        printf("\nDigite o grupo a ser simulado:\n");
        scanf("\n%c", &grupo);
        printf("\nDigite a rodada:\n");
        scanf("%d", &rodada);
        if ((1 <= rodada && rodada <= 3) && (65 <= grupo && grupo <= 72)) break;
    }
    seekPartidasFG(grupo, rodada, partidasFG);

    int i = 0;
    while(i <= 1){
        partidas[i] = lePartida(partidasFG);
        times[0] = buscaTime(timestxt, partidas[i] ->times[0]);
        times[1] = buscaTime(timestxt, partidas[i] ->times[1]);
        printf("\nGrupo %c\nRodada %d\n%s x %s\n", partidas[i] ->idGrupo, partidas[i] ->rodada,
        times[0] ->nome, times [1] ->nome);
        printf("\nDigite o placar no formato: 0 0\n");
        scanf("%d %d", &placar[i][0], &placar[i][1]);
        partidas[i] ->placar[0] = placar[i][0];
        partidas[i] ->placar[1] = placar[i][1];
        i++;
    }

    seekPartidasFG(grupo, rodada, partidasFG);
    i = 0;
    while(i <= 1){
        fwrite(&partidas[i] ->idGrupo, sizeof(char), 1, partidasFG);
        fwrite(partidas[i] ->times, sizeof(int), 2, partidasFG);
        fwrite(&partidas[i] ->rodada, sizeof(int), 1, partidasFG);
        fwrite(partidas[i] ->placar, sizeof(int), 2, partidasFG);
        i++;
    }
    fclose(partidasFG);
    fclose(timestxt);
    organizaGrupos();
}
    


void seekPartidasFG(char idG, int rodada, FILE *partidas){
    int posicaoGrupo = (idG - 65) * 21 * 6;
    int posicaoRodada = (rodada - 1) * 21 * 2;
    fseek(partidas, posicaoGrupo, SEEK_SET);
    fseek(partidas, posicaoRodada, SEEK_CUR);   
}

void printaPartidaFG(char id){
    FILE *partidas = fopen("partidasFG.txt", "ab+");
    FILE *times = fopen("times.txt", "ab+");
    PartidaFG *partidaAtual = (PartidaFG*) malloc (sizeof(PartidaFG));
    Time *time1 = (Time *) malloc(sizeof(Time));
    Time *time2 = (Time *) malloc(sizeof(Time));
    seekPartidasFG(id, 1, partidas);

    int i = 0;
    while(i <= 5){
        fread(&partidaAtual ->idGrupo, sizeof(char), 1, partidas);
        fread(&partidaAtual ->times, sizeof(int), 2, partidas);
        fread(&partidaAtual ->rodada, sizeof(int), 1, partidas);
        fread(&partidaAtual ->placar, sizeof(int), 2, partidas);
        time1 = buscaTime(times, partidaAtual->times[0]);
        time2 = buscaTime(times, partidaAtual->times[1]);
        printf("Grupo %c Rodada %d\t%s %d x %d %s\n", partidaAtual ->idGrupo, partidaAtual ->rodada, 
        time1 ->nome, partidaAtual->placar[0], partidaAtual ->placar[1], time2 ->nome);
        i++;
    }

    free(time1);
    free(time2);
    fclose(partidas);
    fclose(times);

}

void printaPartidasFG(){
    FILE *partidas = fopen("partidasFG.txt", "ab+");
    FILE *times = fopen("times.txt", "ab+");
    PartidaFG *partidaAtual = (PartidaFG*) malloc (sizeof(PartidaFG));
    Time *time1 = (Time *) malloc(sizeof(Time));
    Time *time2 = (Time *) malloc(sizeof(Time));

    int i = 0, rdAnterior = 1;
    char gpAnterior = 'A';
    
    while(i <= 47){
        
        fread(&partidaAtual ->idGrupo, sizeof(char), 1, partidas);
        fread(&partidaAtual ->times, sizeof(int), 2, partidas);
        fread(&partidaAtual ->rodada, sizeof(int), 1, partidas);
        fread(&partidaAtual ->placar, sizeof(int), 2, partidas);

        time1 = buscaTime(times, partidaAtual->times[0]);
        time2 = buscaTime(times, partidaAtual->times[1]);

        if (gpAnterior != partidaAtual->idGrupo) printf("\n\n");
        else if(rdAnterior != partidaAtual->rodada) printf("\n");

        rdAnterior = partidaAtual->rodada;
        gpAnterior = partidaAtual->idGrupo;

        printf("Grupo %c Rodada %d\t%s %d x %d %s\n", partidaAtual ->idGrupo, partidaAtual ->rodada, 
        time1 ->nome, partidaAtual->placar[0], partidaAtual ->placar[1], time2 ->nome);
        i++;
    }

    free(time1);
    free(time2);
    fclose(partidas);
    fclose(times);
}

void zeraPartidas(){
    PartidaFG *atual;
    FILE *partidasFG = fopen("partidasFG.txt", "rb+");
    int i = 0;
    while(i <= 47){
        atual = lePartida(partidasFG);
        atual ->placar[0] = 0;
        atual ->placar[1] = 0;
        fseek(partidasFG, -21, SEEK_CUR);
        fwrite(&atual ->idGrupo, sizeof(char), 1, partidasFG);
        fwrite(atual ->times, sizeof(int), 2, partidasFG);
        fwrite(&atual ->rodada, sizeof(int), 1, partidasFG);
        fwrite(atual ->placar, sizeof(int), 2, partidasFG);
        i++;
    }
    fclose(partidasFG);
    free(atual);
}