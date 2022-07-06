//falta colocar caso n de p por na matriz p digitar outra vez ou mudar a matriz
//LISTA DE BUGS: nao sei onde tem bug
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define  TAM 20

int k,x,y, jogadas;
struct{
    char p[TAM];
    char r[TAM];
    char resp[TAM];
    int nline;
    int ncolun;
    int horiz;
    int verti;
}perguntas[TAM];

void fpergunta(){ //é o bagulete que lê as perguntas, mas falta fazer ele entender espaço e etc, mas ao menos as palavras de vários caracteres ele já consegue entender de buenas
    int tam,e,i;
    int line, colun, maior;
    char *pt;
    printf("Quantas linhas tem o palavra-cruzada?\n");
    scanf("%d", &x);

    printf("Quantas colunas tem o jogo?\n");
    scanf("%d", &y);

    maior =0;
    if(y>maior)
        maior=y;
    if(x>maior)
        maior=x;

    char res[x][y];
    for(int w=0; w<x; w++){
        for(int p=0; p<y; p++){
            char t= ' ';
            res[w][p]=t;
        }
    }

    printf("Quantas perguntas você quer adicionar?\n");
    scanf("%d", &k);
    for(i=0; i<k; i++){
        printf("Digite a pergunta:\n");
        scanf("%s",perguntas[i].p);
        printf("Digite a resposta:\n");
        scanf("%s",perguntas[i].r);
        tam=strlen(perguntas[i].r);
        pt=&perguntas[i].r;

        if (tam>maior){
            do{
                printf("\nA palavra eh maior que o espaco de jogo estabelecido. Escolha outra palavra\n");
                scanf ("%s", perguntas[i].r);
                tam=strlen(perguntas[i].r);
            }while(tam>maior);
        }

        printf("A palavra deve ser colocada na horizontal ou na vertical?\n");
        printf("1:vertical\n2:horizontal\n");
        scanf("%d",&e);

        if(e!=2 && e!=1){
            do{
                printf("Não é uma escolha. Digite novamente\n");
                scanf("%d",&e);
            }while(e!=2 && e!=1);
        }

        if(e==1){
            if(tam>x && tam<=y){
                printf("A palavra não pode ser colocada na vertical. A palavra será colocada na horizontal\n");
                printf("Digite em qual linha deve ser colocada a palavra\n");
                scanf("%d",&line);

                for(int roda=0; roda<line; roda++){
                    if(perguntas[roda].nline==line-1 && perguntas[roda].horiz==1){
                        do{
                            printf("Essa linha já foi escolhida. Digite outra\n");
                            scanf("%d", &line);
                        }while(perguntas[roda].nline==(line-1));
                    }
                }
                perguntas[i].nline=(line-1);
                perguntas[i].horiz=1;

                for(int h=0; h<tam; h++){
                    res[line-1][h]=pt[h];
                }
            }

            if (tam<=x){
                printf("Em qual coluna a palavra deve ser inserida?\n");
                scanf("%d",&colun);
                for(int roda=0; roda<colun; roda++){
                    if(perguntas[roda].ncolun==colun-1 && perguntas[roda].verti==1){
                        do{
                            printf("Essa coluna já foi escolhida. Digite outra\n");
                            scanf("%d", &colun);
                        }while(perguntas[roda].ncolun==(colun-1));
                    }
                }
                perguntas[i].ncolun=(colun-1);
                perguntas[i].verti=1;

                for(int p=0; p<tam; p++){
                    res[p][colun-1]=pt[p];
                }
            }
        }

        if(e==2){
            if(tam>y && tam<=x){
                printf("A palavra não pode ser colocada na horizontal. A palavra será colocada na vertical.\n");
                printf("Digite em qual coluna deve ser colocada a palavra\n");
                scanf("%d",&colun);
                for(int roda=0; roda<line; roda++){
                    if(perguntas[roda].nline==line-1 && perguntas[roda].horiz==1){
                        do{
                            printf("Essa linha já foi escolhida. Digite outra\n");
                            scanf("%d", &line);
                        }while(perguntas[roda].nline==(line-1));
                    }
                }

                perguntas[i].ncolun=(colun-1);
                perguntas[i].verti=1;

                for(int h=0; h<tam; h++){
                    res[h][colun-1]=pt[h];
                }
            }

            if(tam<=y){
                printf("Em qual linha a palavra deve ser inserida?\n");
                scanf("%d",&line);
                for(int roda=0; roda<line; roda++){
                    if(perguntas[roda].nline==line-1 && perguntas[roda].horiz==1){
                        do{
                            printf("Essa linha já foi escolhida. Digite outra\n");
                            scanf("%d", &line);
                        }while(perguntas[roda].nline==(line-1));
                    }
                }
                perguntas[i].nline=(line-1);
                perguntas[i].horiz=1;

                for(int u=0; u<tam; u++){
                    res[line-1][u]=pt[u];
                }
            }
        }
    }
    printf("A resposta na matriz está na seguinte forma:\n");

    for(int v=0; v<x; v++){
        for(int j=0; j<y; j++){
            printf("%c\t", res[v][j]);
        }printf("\n");
    }
}

void fprintar(){// é a função pra printar as perguntas que já foram digitadas e as respostas tmb.
    printf("As perguntas são:\n");
    for(int i=0; i<k; i++){
        printf("%s\n", perguntas[i].p);
    }

    printf("As respostas foram:\n");
    for (int i=0; i<k; i++){
        printf("%s\n", perguntas[i].r);
    }
}

void jogar(){//aqui é onde acontece o jogo, essa função depende tanto do comparar, que eu já expliquei logo abaixo o que é, quanto do sub, que eu tmb já expliquei o que faz mais pra baixo.
    jogadas=0;
    char m[x][y];
    char t='_';
    int e, tamR;
    jogadas=0;

    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            m[i][j]=t;
            printf("%c\t", m[i][j]);
        }printf("\n");
    }

    do{
        printf("As perguntas são:\n");
        for(int w=0; w<k; w++){
            printf("%d.%s\n", w, perguntas[w].p);
        }

        printf("Qual pergunta você deseja responder?\n");
        scanf("%d", &e);
        comparar(e,m);

        for(int i=0; i<x; i++){
            for(int j=0; j<y; j++){
                printf("%c\t", m[i][j]);
            }printf("\n");
        }
    }while(jogadas<k);

    printf("Parabéns, você ganhou!\n");
}

void comparar(int e, char m[x][y]){//aqui é a função que ele compara a resposta inserida pelo jogador com a resposta real, se bater, ele printa na matriz M, se não, aí deu merda
    int t, e1;
    printf("%s\n", perguntas[e].p);
    printf("Digite a resposta da pergunta\n");
    scanf("%s",perguntas[e].resp);
    t=strcmp(perguntas[e].resp, perguntas[e].r);

    if(t==0){
        printf("Deu bom\n");
        sub(e,m);
        jogadas++;
    }
    if(t!=0){
        printf("Resposta errada. Escolha:\n1.Tentar novamente\n2.Trocar de pergunta\n");
        scanf("%d",&e1);
        if(e1==1){
            int e2;
            do{
                printf("Digite a resposta novamente\n");
                scanf("%s", perguntas[e].resp);
                t=strcmp(perguntas[e].resp, perguntas[e].r);

                if(t!=0){
                    printf("Resposta errada\n");
                    printf("Você deseja tentar novamente?\n1:Sim\n2:Não\n");
                    scanf("%d", &e2);
                }

                if(t==0){
                    sub(e,m);
                    jogadas++;
                    break;
                }
            }while(t==1 || e2==1);
        }

        if(e1==2){
            printf("Obrigado pela escolha\n");
        }
    }
}

void sub(int e, char m[x][y]){//aqui é a parte do código que faz ele printar a resposta inserida na matriz de jogadas
    char *psub;
    int tam, n;

    tam=strlen(perguntas[e].resp);
    psub=&perguntas[e].resp;
    if(perguntas[e].verti==1){
        for(int h=0; h<tam; h++){
            m[h][perguntas[e].ncolun]=psub[h];
        }
    }

    if(perguntas[e].horiz==1){
        for(int c=0; c<tam; c++){
            m[perguntas[e].nline][c]=psub[c];
        }
    }
}

int main() {
    int n;

    printf("Qual opção você quer?\n");
    printf("1:criar perguntas\n2:printar perguntas\n3:jogar\n");
    scanf("%d",&n);
    switch(n){
        case 1:
            fpergunta();
            main();// eu botei um "main()" em vez de um "break;" porque aí assim que acaba de fazer a função do negócio, ele volta pro começo do main, aí a gente evita ter que fazer coisa de loop e pipipipopopo
        case 2:
            fprintar();
            main();
        case 3:
            jogar();
            main();
    }
}
