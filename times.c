#include "times.h"

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
    fwrite(novo ->ved, sizeof(int), 3, times);
    fwrite(&novo ->golsFavor, sizeof(int), 1, times);
    fwrite(&novo ->golsContra, sizeof(int), 1, times);
    fwrite(novo -> status, sizeof(char), sizeof(novo ->status), times);
    fwrite(&novo ->nTitulos, sizeof(int), 1, times);
    fwrite(novo ->titulos, sizeof(int), 6, times);
    free(novo);
}



Time *leTime(FILE *times){
    Time *lido = (Time *) malloc(sizeof(Time));

    fread(&lido ->ID, sizeof(int), 1, times);
    fread(&lido ->nome, sizeof(char), sizeof(lido ->nome), times);
    fread(&lido ->ved, sizeof(int), 3, times);
    fread(&lido ->golsFavor, sizeof(int), 1, times);
    fread(&lido ->golsContra, sizeof(int), 1, times);
    fread(&lido -> status, sizeof(char), sizeof(lido ->status), times);
    fread(&lido ->nTitulos, sizeof(int), 1, times);
    fread(&lido ->titulos, sizeof(int), 6, times);
    return lido;
}

Time *buscaTime(FILE *times, int id){
    Time *achado = (Time *) malloc(sizeof(Time));
    int posicao = 152*(id-1);
    
    fseek(times, posicao, SEEK_SET);
    
    achado = leTime(times);
    return achado;
}

void mostraTimes(){

    FILE *times;
    times = fopen("times.txt", "ab+");
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
    fclose(times);
}

void insereTimes(){
    Time *atual;
    int i = 0;
    FILE *times = fopen("times.txt", "wb+");
    while(i <= 31){
        insereTime(times);
        i++;
    }
    free(atual);
    fclose(times);
}



