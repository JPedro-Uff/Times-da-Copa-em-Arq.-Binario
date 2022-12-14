#include "times.h"
#include "grupos.h"
#include "partidasFG.h"

void linha(){
    printf("\n---------------------------------------------------------------\n");
}

int opcaoEntrada(){

    int escolha = 0;
    do{
        linha();
        printf("\n\t\tMenu de opcoes\n");
        linha();

        printf("\n\t[1] - Menu Usuario\n");
        printf("\n\t[2] - Menu Administrador\n");
        printf("\n\t[0] - Sair do programa\n");
        linha();

        printf("\n\t\tDigite aqui: ");
        scanf("%d", &escolha);
        linha();

        if (escolha <0 || escolha >2){
            printf("\n\n\nPor favor digite uma opcao valida\n\n\n");
        }

    }while (escolha <0 || escolha >2);

    return escolha;
}
int menuAdm(){
    int escolha = 0;
    do{
        linha();
        printf("\n\t\tMenu administrador\n");
        linha();
        printf("\n\t[1] - Inserir grupos\n");
        printf("\n\t[2] - Inserir partidas da fase de grupos\n");
        printf("\n\t[3] - Inserir times da fase de grupos\n");
        printf("\n\t[0] - Voltar\n");

        printf("\n\t\tDigite aqui: ");
        scanf("%d", &escolha);
        linha();

        if (escolha < 0 || escolha > 3){
            printf("\nPor favor digite uma opcao valida\n");
        }
    }while (escolha < 0 || escolha > 3);
    return escolha;
}

int menuUsuario(){

    int escolha = 0;
    do{
        linha();
        printf("\n\t\tMenu Usuario\n");
        linha();
        printf("\n\t[1] - Mostrar partidas da fase de grupos\n");
        printf("\n\t[2] - Mostrar um grupo especifico\n");
        printf("\n\t[3] - Mostrar todos os grupos\n");
        printf("\n\t[4] - Mostrar um time especifico\n");
        printf("\n\t[5] - Mostrar times da fase de grupos\n");
        printf("\n\t[6] - Simular partida da fase de grupos\n");
        printf("\n\t[7] - Zerar o simulador\n");
        printf("\n\t[0] - Voltar\n");

        printf("\n\t\tDigite aqui: ");
        scanf("%d", &escolha);
        linha();

        if (escolha < 0 || escolha > 7){
            printf("\nPor favor digite uma opcao valida\n");
        }
    }while (escolha < 0 || escolha > 7);

    return escolha;
}

int main(void)
{
    system("clear");
    linha();
    printf("\n\tBem vindo ao simulador da copa\n");

    int condicaoParada = 0, escolhaMenu = 0, escolhaMenus = 0, sairMenus = 0, idTime, senha;
    char idGrupo;
    
    do{
        escolhaMenu = opcaoEntrada();
        system("clear");
        do{
            sairMenus = 0;
            switch(escolhaMenu){
            
                //Menu do Usuário
                case 1:
                    escolhaMenus = menuUsuario();
                    system("clear");
                    switch(escolhaMenus){
                        case 1:
                            printaPartidasFG();
                            break;
                        
                        case 2:
                            printf("\nDigite a letra grupo:\n");
                            scanf(" %c", &idGrupo);
                            printaGrupo(idGrupo);
                            break;
                        case 3:
                            printaGrupos();
                            break;
                        case 4:
                            printf("\nDigite o id do time:\n");
                            scanf("%d", &idTime);
                            mostraTime(idTime);
                            break;
                        case 5:
                            mostraTimes();
                            break;
                        case 6:
                            escrevePartidaFG();
                            break;
                        case 7:
                            recomeca();
                            zeraPartidas();
                            break;
                        case 0:
                            sairMenus = 1;
                            break;                                
                        }
                    break;

                case 2:
                    printf("\nDigite a senha:\n");
                    scanf("%d", &senha);
                    if(senha != 12345) {
                        printf("\nSenha incorreta!\n");
                        sairMenus = 1;
                        break;
                    }
                    escolhaMenus = menuAdm();
                    system("clear");
                    switch(escolhaMenus){
                        case 1:
                            insereGrupos();
                            break;
                        case 2:
                            inserePartidasFG();
                            break;
                        case 3:
                            insereTimes();
                            break;
                        case 0:
                            sairMenus = 1;
                            break;
                    }
                    break;
                case 0:
                    sairMenus = 1;
                    condicaoParada = 1;
                    break;
            }

        }while(sairMenus == 0);
         
    }while(condicaoParada == 0);
}