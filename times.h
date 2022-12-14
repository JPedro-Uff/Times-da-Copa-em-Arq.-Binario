#ifndef TIMES_H
#define TIMES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct timeCopa {
    int ID;
    char nome[50];
    int nTitulos;
    int titulos[6];
} Time;

Time *buscaTime(FILE *times, int id);

void insereTime(FILE *times);

Time *leTime(FILE *times);

void mostraTime(int id);

void mostraTimes();

void insereTimes();

#endif