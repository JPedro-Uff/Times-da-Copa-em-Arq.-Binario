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

void insereTime(FILE *times){
    Time *novo = (Time *) malloc(sizeof(Time));

    int nTitulos, i = 0;
    strcpy(novo ->status, "Fase de grupos");
    

    novo ->ved[0] = 0;
    novo ->ved[1] = 0;
    novo ->ved[2] = 0;
    novo ->golsContra = 0;
    novo ->golsFavor = 0;

    scanf("%s %d %d", novo ->nome, &novo ->ID, &nTitulos);

    novo ->nTitulos = nTitulos;
    if(nTitulos == 0){
        novo ->titulos[0] = 0;
    }
    while(nTitulos > 0){
        scanf("%d", &novo ->titulos[i]);
        i++;
        nTitulos--; 
    }

    fwrite(&novo ->ID, sizeof(int), 1, times);
    fwrite(novo ->nome, sizeof(char), sizeof(novo ->nome), times);
    fwrite(novo ->ved, sizeof(int), 1, times);
    fwrite(&novo ->golsFavor, sizeof(int), 1, times);
    fwrite(&novo ->golsContra, sizeof(int), 1, times);
    fwrite(novo -> status, sizeof(char), sizeof(novo ->status), times);
    fwrite(&novo ->nTitulos, sizeof(int), 1, times);
    fwrite(novo ->titulos, sizeof(int), sizeof(novo ->titulos), times);
    free(novo);
}

Time *leTime(FILE *times){
    Time *lido = (Time *) malloc(sizeof(Time));

    fread(&lido ->ID, sizeof(int), 1, times);
    fread(&lido ->nome, sizeof(char), sizeof(lido ->nome), times);
    fread(&lido ->ved, sizeof(int), 1, times);
    fread(&lido ->golsFavor, sizeof(int), 1, times);
    fread(&lido ->golsContra, sizeof(int), 1, times);
    fread(&lido -> status, sizeof(char), sizeof(lido ->status), times);
    fread(&lido ->nTitulos, sizeof(int), 1, times);
    fread(&lido ->titulos, sizeof(int), sizeof(lido ->titulos), times);
    return lido;
}

void mostraTimes(FILE *times){
    int n = 32;
    Time *atual;
    while(n > 0){
        int i = 0;
        atual = leTime(times);
        printf("ID: %d\nSeleção: %s\nVitorias: %d \tEmpates: %d\tDerrotas: %d"
        "\nGols Feitos: %d\tGols Tomados: %d\n"
        "Fase Atual/Fase Eliminado: %s", atual ->ID, atual->nome,
        atual ->ved[0], atual ->ved[1], atual ->ved[2],
        atual ->golsContra, atual ->golsFavor, atual ->status);
        printf("\nNumero de Titulos: %d", atual ->nTitulos);
        while(i < atual ->nTitulos){
            printf("\n%d", atual->titulos[i]);
            i++;
        }
        printf("\n\n");
        n--;
    }

    free(atual);
}

int main(void){
    int i = 0;
    FILE *times;
    Time *time;
    times = fopen("times.txt", "ab+");
    while (i < 32){
        insereTime(times);
        i++;
    }
    fseek(times, 0, SEEK_SET);
    mostraTimes(times);
    fclose(times);
}