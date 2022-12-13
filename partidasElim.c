#include "partidasElim.h"
#include "grupos.h"

void setOitavas(){
    FILE *grupostxt = fopen("grupos.txt", "rb+");
    FILE *partidasElimtxt = fopen("partidasElim.txt", "wb+");
    PartidaElim *oitavas[8];
    Grupo *grupos[2];
    int i = 0;
    char id = 'A';
    
    while(i <= 4)//terminar o loop para fazer automaticamente
    oitavas[0] = (PartidaElim *) malloc(sizeof(PartidaElim));
    oitavas[0]->id = 1;
    grupos[0] = buscaGrupo(grupostxt, 'A');
    grupos[1] = buscaGrupo(grupostxt, 'B');
    oitavas[0]->times[0] = grupos[0]->times[0];
    oitavas[0]->times[1] = grupos[1]->times[1];

    oitavas[1] = (PartidaElim *) malloc(sizeof(PartidaElim));
    oitavas[1]->id = 2;
    grupos[0] = buscaGrupo(grupostxt, 'C');
    grupos[1] = buscaGrupo(grupostxt, 'D');
    oitavas[1]->times[0] = grupos[0].times[0];
    oitavas[1]->times[1] = grupos[1].times[1];

}