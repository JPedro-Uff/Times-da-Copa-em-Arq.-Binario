#ifndef TIMES_H
#define TIMES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct timeCopa {
    int ID;
    char nome[50];
    char status[50];
    int nTitulos;
    int titulos[6];
    int ved[3];
    int golsFavor;
    int golsContra;
} Time;

Time *buscaTime(FILE *times, int id);

void insereTime(FILE *times);

Time *leTime(FILE *times);

void mostraTimes();

void insereTimes();

#endif