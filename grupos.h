#ifndef GRUPOS_H
#define GRUPOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "times.h"

typedef struct grupoCopa{
    char ID;
    int times[4];
    int pontos[4];
    int saldoGols[4];
    int ved[4][3];
}Grupo;

Grupo *criaGrupo();

Grupo *leGrupo(FILE *grupos);

Grupo *buscaGrupo(FILE *grupos, char id);

void printaGrupos();

void printaGrupo(char idGrupo);

void insereGrupos();

void organizaGrupos();

Grupo *zeraGrupo(Grupo *grupo);

void recomeca();



#endif