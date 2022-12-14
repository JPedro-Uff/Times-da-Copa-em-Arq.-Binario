#include "times.h"

void insereTime(FILE *times){
    Time *novo = (Time *) malloc(sizeof(Time));

    int nTitulos, i = 0;

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
    fwrite(&novo ->nTitulos, sizeof(int), 1, times);
    fwrite(novo ->titulos, sizeof(int), 6, times);
    free(novo);
}



Time *leTime(FILE *times){
    Time *lido = (Time *) malloc(sizeof(Time));

    fread(&lido ->ID, sizeof(int), 1, times);
    fread(&lido ->nome, sizeof(char), sizeof(lido ->nome), times);
    fread(&lido ->nTitulos, sizeof(int), 1, times);
    fread(&lido ->titulos, sizeof(int), 6, times);
    return lido;
}

Time *buscaTime(FILE *times, int id){
    Time *achado = (Time *) malloc(sizeof(Time));
    int posicao = 82*(id-1);
    
    fseek(times, posicao, SEEK_SET);
    
    achado = leTime(times);
    return achado;
}

void mostraTime(int id){
    FILE *times = fopen("times.txt", "ab+");
    Time *atual = buscaTime(times, id);

    printf("\nID: %d\nSeleção: %s", atual ->ID, atual->nome);
    printf("\nNumero de Titulos: %d\n", atual ->nTitulos);
    int i = 0;
    while(i < atual ->nTitulos){
        printf("\n%d", atual->titulos[i]);
        i++;
    }
    printf("\n\n\n");

    fclose(times);
    free(atual);

}

void mostraTimes(){

    FILE *times;
    times = fopen("times.txt", "ab+");
    int n = 32;
    Time *atual;
    while(n > 0){
        int i = 0;
        atual = leTime(times);
        printf("ID: %d\nSeleção: %s",atual ->ID, atual->nome);
        printf("\nNumero de Titulos: %d\n", atual ->nTitulos);
        while(i < atual ->nTitulos){
            printf("\n%d", atual->titulos[i]);
            i++;
        }
        printf("\n\n\n");
        n--;
    }

    free(atual);
    fclose(times);
}

void insereTimes(){
    int i = 0;
    FILE *times = fopen("times.txt", "wb+");
    while(i <= 31){
        insereTime(times);
        i++;
    }
    fclose(times);
}



