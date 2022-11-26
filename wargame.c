#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#define ESPACO '-'
#define ALTURA_DEFAULT 9//valor por omissao da altura do tabuleiro
#define LARGURA_DEFAULT 9 //valor por omissao da largura do tabuleiro
#define MODOJOGO_DEFAULT 0//valor por omissao do modo de jogo
#define MODOPOSICIONAMENTO_DEFAULT 1//valor por omissao do modo de posicionamento
#define MODODISPARO_DEFAULT 1//valor por omissao do modo de disparo

//Cabeçalho
void inic(int M,int N,char s[M][N]);
void linha(int M,int N,char s[M][N]);
int colunas(int N);
void posicionamento_1(int M,int N,char tabuleiro[M][N],char instpeca[43][3][3],int nr_pecas[9]);
void num_pecas(int nr_pecas[9],int var);
void print_num_pecas(int M,int N,int nr_pecas[9]);//da print numa linha com as dimensoes do tabuleiro e o numero de cada tipo de peça
int escolhe_var_p1(int *try);
int restricao_1(int M,int N,char tabuleiro[M][N]);

//posicionamento 2
void inic_0(int M,int N,char s[M][N],int m, int n);
void reset(int M,int N,int s[M*N/9]);
void tipo_aleatorio(int M,int N,int tipo_peca[9],int distribuicao[M*N/9],int random_tipo[M*N/9]);
int escolhe_var_try(int M,int N,int random_tipo[M*N/9],int k,int *var,int vezes);
int escolhe_var_p2(int M,int N,int random_tipo[M*N/9],int k);
int restricao_3(int M,int N,int tipo_peca[9]);
int soma(int a,int b, int c, int d, int e, int f, int g, int h);
void swap(int *x, int *y);
int posicionamento_2(int M,int N,char tabuleiro[M][N],char instpeca[43][3][3],int random_tipo[M*N/9]);

//disparo 1
void disparo_1(int M,int N,char tabuleiro[M][N],char tabuleiro_disparo[M][N],char tab_verifica_disparo[M][N],int *jogadas);
void disparo_aleatorio(int M,int N,char tabuleiro[M][N],char tabuleiro_disparo[M][N],char tab_verifica_disparo[M][N],int *jogadas);
int fim_d(int M,int N,char tabuleiro[M][N]);//fim do disparo 1
int contagem_(int *jogadas);
void print_posicao_disp1(int M,int N,int i,int j,char tabuleiro_disparo[M][N]);

//disparo 2
void disparo_2(int M,int N,char tabuleiro[M][N],char tabuleiro_disparo[M][N],char tab_verifica_disparo[M][N],int *jogadas);
void coordenadas_disparo(int M,int N,char tabuleiro_disparo[M][N],char tabuleiro[M][N],int *m, int *n,int *num_disparo,int *jogadas);
int verif_disp2(int M,int N,char tabuleiro[M][N], int *m, int *n);
int fim_d2(int M,int N,char tabuleiro_disparo[M][N], char tab_verifica_disparo[M][N]);
void print_posicao_disp2(int M,int N,int m, int n,int i,int j, char tabuleiro_disparo[M][N]);

//disparo 3
void disparo_3(int M,int N,char tabuleiro[M][N],char tabuleiro_disparo[M][N],char tab_verifica_disparo[M][N],int *jogadas);
void restricao_disparo(int M,int N,char tabuleiro_disparo[M][N],char posic_adjacente[M][N]);
void coordenadas_disparo_3(int M,int N,char posic_adjacente[M][N],char tabuleiro_disparo[M][N],char tabuleiro[M][N],int *m, int *n,int *num_disparo,int *jogadas);


//MODO JOGO 1
void input_coord(int M,int N,char tab_verifica_disparo[M][N],char tabuleiro_disparo[M][N],char tabuleiro[M][N],int *jogadas);//input das coordenadas do utilizador respondendo com a peça do tabuleiro
void print_header1(void);//print no header
void modo_jogo_1(int M,int N,char tabuleiro[M][N],char tabuleiro_disparo[M][N],char tab_verifica_disparo[M][N], int nr_pecas[9],int *jogadas);
int fim_j1(int M,int N,char tabuleiro[M][N], char tabuleiro_disparo[M][N]);

//MODO JOGO 2
void print_header2(void);
void modo_jogo_2(int M,int N,int modo_disparo,char tabuleiro[M][N],char tabuleiro_disparo[M][N],char tab_verifica_disparo[M][N], int nr_pecas[9],int *jogadas);

//LINHA DE COMANDOS
void ajuda(void);//imprime o interface de ajuda

int main(int argc, char *argv[])
{
                                                /*D E C L A R A C O E S  D A  L I N H A  D E  C O M A N D O S */
    extern char *optarg;
    int modo_jogo=MODOJOGO_DEFAULT;
    int modo_posicionamento=MODOPOSICIONAMENTO_DEFAULT;
    int modo_disparo=MODODISPARO_DEFAULT;
    int M=ALTURA_DEFAULT;
    int N=LARGURA_DEFAULT;
    /* para getopt() não gerar erros por opçoes invalidas*/
    int nr_pecas[9] = {0,0,0,0,0,0,0,0,0};//contagem das peças no modo posicionamento 1
    int tipo_peca[9]= {0,0,0,0,0,0,0,0,0};//input do numero de pecas do utilizador, vetor detentor do numero de pecas de cada tipo 0-8
    int opt= 'h';
        //processa linha de comando
  opterr=0;
    if((opt= getopt(argc, argv,"ht:j:p:d:1:2:3:4:5:6:7:8:")) != -1)
        {
        while(opt!=-1)
        {
        switch(opt)  {
            case 't':
                sscanf(optarg,"%dx%d",&M,&N);
                    if(M%3!=0 || M<9 || M>15 || N%3!=0 || N<9 || N>24 ){
                        printf("Entrada das dimensoes do tabuleiro invalida.");
                        return -1;
                    }
                break;

            case 'j':
                modo_jogo = atoi(optarg);
                    if(modo_jogo <0 || modo_jogo >2){
                        printf("Entrada de modo jogo inválida.");
                        return -1;
                        }
                break;

            case 'p':
                modo_posicionamento= atoi(optarg);
                    if(modo_posicionamento!=1 && modo_posicionamento!=2){
                        printf("Entrada do modo de posicionamento inválida.");
                        return -1;
                    }
                break;

            case 'd':
                modo_disparo = atoi(optarg);
                if(modo_disparo<1 || modo_disparo>3){
                        printf("Entrada do modo de disparo inválida.");
                        return -1;
                }
                break;

            case '1':
                tipo_peca[1]= atoi(optarg);
                break;

            case '2':
                tipo_peca[2]= atoi(optarg);
                break;

            case '3':
                tipo_peca[3]= atoi(optarg);
                break;

            case '4':
                tipo_peca[4]= atoi(optarg);
                break;

            case '5':
                tipo_peca[5]= atoi(optarg);
                break;

            case '6':
                tipo_peca[6]= atoi(optarg);
                break;

            case '7':
                tipo_peca[7]= atoi(optarg);
                break;

            case '8':
                tipo_peca[8]= atoi(optarg);
                break;

            case 'h':
            default:
                ajuda();
                return -1;
                break;

        }
        opt= getopt(argc, argv,"ht:j:p:d:1:2:3:4:5:6:7:8:");
      }
    }
    else
    {
        ajuda();
        return -1;
    }

    //ALGUMAS CONDICOES DE VALIDACAO
    if(modo_jogo ==1 && (modo_disparo != 1)){
      printf("Parâmetros Inválidos.");
      return -1;
    }
    if(modo_posicionamento == 2)
    {
        int y=restricao_3(M,N,tipo_peca);
        if(y)
        {
        printf("Entrada de numero de peças inválida.\n");
        return -1;
        }
    }


                                /* I N I C I O  D O  P R O G R A M A */
    clock_t begin = clock();//comeca a contagem do runtime do programa

    int x;//Excede as 8 tentativas de gerar um tabuleiro em p2 dando reset no tabuleiro
    int jogadas=0;
    char tab_verifica_disparo[M][N];
    char tabuleiro[M][N];//tabuleiro do posicionamento das pecas
    char tabuleiro_disparo[M][N];//tabuleiro de disparo

    //Posicionamento 2
    int random_tipo[M*N/9],distribuicao[M*N/9];
    int tentativas=0;//numero de tabuleiros recriados

    char instpeca[43][3][3]={                      /*Descriçao das peças */
        {{'-','-','-'},{'-','-','-'},{'-','-','-'}},//Matriz nula:peça0
                                                   /*Peças tipo 1:*/
        {{'1','-','-'},{'-','-','-'},{'-','-','-'}},//peça1
        {{'-','1','-'},{'-','-','-'},{'-','-','-'}},//peça2
        {{'-','-','1'},{'-','-','-'},{'-','-','-'}},//peça3
        {{'-','-','-'},{'1','-','-'},{'-','-','-'}},//peça4
        {{'-','-','-'},{'-','1','-'},{'-','-','-'}},//peça5
        {{'-','-','-'},{'-','-','1'},{'-','-','-'}},//peça6
        {{'-','-','-'},{'-','-','-'},{'1','-','-'}},//peça7
        {{'-','-','-'},{'-','-','-'},{'-','1','-'}},//peça8
        {{'-','-','-'},{'-','-','-'},{'-','-','1'}},//peça9
                                                   /*Peças tipo 2:*/
        {{'2','2','-'},{'-','-','-'},{'-','-','-'}},//peça10
        {{'-','2','2'},{'-','-','-'},{'-','-','-'}},//peça11
        {{'-','-','-'},{'2','2','-'},{'-','-','-'}},//peça12
        {{'-','-','-'},{'-','2','2'},{'-','-','-'}},//peça13
        {{'-','-','-'},{'-','-','-'},{'2','2','-'}},//peça14
        {{'-','-','-'},{'-','-','-'},{'-','2','2'}},//peça15
        {{'2','-','-'},{'2','-','-'},{'-','-','-'}},//peça16
        {{'-','-','-'},{'2','-','-'},{'2','-','-'}},//peça17
        {{'-','2','-'},{'-','2','-'},{'-','-','-'}},//peça18
        {{'-','-','-'},{'-','2','-'},{'-','2','-'}},//peça19
        {{'-','-','2'},{'-','-','2'},{'-','-','-'}},//peça20
        {{'-','-','-'},{'-','-','2'},{'-','-','2'}},//peça21
                                                    /*Peças tipo 3:*/
        {{'3','3','3'},{'-','-','-'},{'-','-','-'}},//peça22
        {{'-','-','-'},{'3','3','3'},{'-','-','-'}},//peça23
        {{'-','-','-'},{'-','-','-'},{'3','3','3'}},//peça24
        {{'3','-','-'},{'3','-','-'},{'3','-','-'}},//peça25
        {{'-','3','-'},{'-','3','-'},{'-','3','-'}},//peça26
        {{'-','-','3'},{'-','-','3'},{'-','-','3'}},//peça27
                                                    /*Peças tipo 4:*/
        {{'4','4','-'},{'4','4','-'},{'-','-','-'}},//peça28
        {{'-','4','4'},{'-','4','4'},{'-','-','-'}},//peça29
        {{'-','-','-'},{'4','4','-'},{'4','4','-'}},//peça30
        {{'-','-','-'},{'-','4','4'},{'-','4','4'}},//peça31
                                                    /*Peças tipo 5:*/
        {{'5','5','5'},{'-','5','-'},{'-','5','-'}},//peça32
        {{'5','-','-'},{'5','5','5'},{'5','-','-'}},//peça33
        {{'-','5','-'},{'-','5','-'},{'5','5','5'}},//peça34
        {{'-','-','5'},{'5','5','5'},{'-','-','5'}},//peça35
                                                    /*Peças tipo 6:*/
        {{'6','6','6'},{'6','-','6'},{'-','6','-'}},//peça36
        {{'6','6','-'},{'6','-','6'},{'6','6','-'}},//peça37
        {{'-','6','-'},{'6','-','6'},{'6','6','6'}},//peça38
        {{'-','6','6'},{'6','-','6'},{'-','6','6'}},//peça39
                                                    /*Peça tipo 7:*/
        {{'7','7','7'},{'-','7','-'},{'7','7','7'}},//peça40
        {{'7','-','7'},{'7','7','7'},{'7','-','7'}},//peça41
                                                    /*Peça tipo 8: */
        {{'8','8','8'},{'8','-','8'},{'8','8','8'}},//peça42
       };

    time_t t;//timers e randomizers
    srand((unsigned)time(&t));
    //inicialização dos varios tabuleiros
    inic(M,N,tabuleiro);
    inic(M,N,tabuleiro_disparo);
    inic(M,N,tab_verifica_disparo);

     if(modo_jogo==0)//MODO JOGO 0, da print num tabuleiro P1 ou P2
     {
         if(modo_posicionamento==1){//POSICIONAMENTO 1
            posicionamento_1(M,N,tabuleiro,instpeca,nr_pecas);
        }
          if(modo_posicionamento==2){//posicionamento 2
            do{
                inic(M,N,tabuleiro);
                reset(M,N,random_tipo);
                reset(M,N,distribuicao);
                tipo_aleatorio(M,N,tipo_peca,distribuicao,random_tipo);
                x=posicionamento_2(M,N,tabuleiro,instpeca,random_tipo);
                    if(tentativas==1000){//Caso chegue a 1000 tentativas de gerar um tabuleiro da retorno de -1
                        printf("\nNao conseguiu gerar o tabuleiro.\n");
                        return -1;
                    }
                tentativas++;
            }
            while(x);//excedeu 8 tentativas de gerar um tabuleiro, volta a fazer outro tabuleiro
            print_num_pecas(M,N,tipo_peca);//print na linha com as dimensoes e nr de pecas de cada tipo
            }
    linha(M,N,tabuleiro);
    colunas(N);
    putchar('\n');

    return EXIT_SUCCESS;
    }

     if(modo_jogo==1)//MODO JOGO 1, o utilizador da input das coordenadas do disparo
    {
            print_header1();
            if(modo_posicionamento==1){//POSICIONAMENTO 1
                posicionamento_1(M,N,tabuleiro,instpeca,nr_pecas);
            }
            if(modo_posicionamento==2){//posicionamento 2
                    do{
                        inic(M,N,tabuleiro);
                        reset(M,N,random_tipo);
                        reset(M,N,distribuicao);
                        tipo_aleatorio(M,N,tipo_peca,distribuicao,random_tipo);
                        x=posicionamento_2(M,N,tabuleiro,instpeca,random_tipo);
                            if(tentativas==1000){//Caso chegue a 1000 tentativas de gerar um tabuleiro da retorno de -1
                                printf("\nNao conseguiu gerar o tabuleiro.\n");
                                return -1;
                            }
                        tentativas++;
                    }
                    while(x);//excedeu 8 tentativas de gerar um tabuleiro, volta a fazer outro tabuleiro
                    print_num_pecas(M,N,tipo_peca);
            }
    modo_jogo_1(M,N,tabuleiro,tabuleiro_disparo,tab_verifica_disparo,nr_pecas,&jogadas);
    }

    if(modo_jogo==2){//MODO JOGO 2, escolhem-se os modos de disparo e modos de posicionamento
            print_header2();
            if(modo_posicionamento==1){
                posicionamento_1(M,N,tabuleiro,instpeca,nr_pecas);
            }
            if(modo_posicionamento==2){//posicionamento 2
                    do{
                        inic(M,N,tabuleiro);
                        reset(M,N,random_tipo);
                        reset(M,N,distribuicao);
                        tipo_aleatorio(M,N,tipo_peca,distribuicao,random_tipo);
                        x=posicionamento_2(M,N,tabuleiro,instpeca,random_tipo);
                            if(tentativas==1000){//Caso chegue a 1000 tentativas de gerar um tabuleiro da retorno de -1
                                printf("\nNao conseguiu gerar o tabuleiro.\n");
                                return -1;
                            }
                        tentativas++;
                    }
                    while(x);//excedeu 8 tentativas de gerar um tabuleiro, volta a fazer outro tabuleiro
                    print_num_pecas(M,N,tipo_peca);
            }
    modo_jogo_2(M,N,modo_disparo,tabuleiro,tabuleiro_disparo,tab_verifica_disparo,nr_pecas,&jogadas);
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Fim de Jogo: %d jogadas em %.0f segundos.\n",jogadas, time_spent);

    linha(M,N,tabuleiro_disparo);
    colunas(N);
    putchar('\n');

return EXIT_SUCCESS;
}
//LINHA DE COMANDOS
void ajuda(void)
{
    printf("Programa que reproduz o jogo da batalha naval.\n\n");
    printf("opções válidas:\n");
    printf("[-h]\t\t                invoca o interface de ajuda\n");
    printf("[-t linhasxcolunas]\t   define as dimensoes do tabuleiro no formato Linhas x Colunas(por omissão %dx%d).\n", ALTURA_DEFAULT,LARGURA_DEFAULT);
    printf("[-j num]\t              define o modo de jogo (por omissão %d), tendo como valores válidos 0, 1 e 2.\n",MODOJOGO_DEFAULT);
    printf("[-p num]\t              define o modo de posicionamento (por omissão %d), tendo como valores válidos 1 e 2.\n", MODOPOSICIONAMENTO_DEFAULT);
    printf("[-d num]\t\t            define o modo de disparo (por omissão %d), tendo como valores válidos 1, 2 e 3.\n", MODODISPARO_DEFAULT);
    printf("[-1 num]\t\t            define o numero de peças tipo 1 a serem colocadas no tabuleiro.\n");
    printf("[-2 num]\t\t            define o numero de peças tipo 2 a serem colocadas no tabuleiro.\n");
    printf("[-3 num]\t\t            define o numero de peças tipo 3 a serem colocadas no tabuleiro.\n");
    printf("[-4 num]\t\t            define o numero de peças tipo 4 a serem colocadas no tabuleiro.\n");
    printf("[-5 num]\t\t            define o numero de peças tipo 5 a serem colocadas no tabuleiro.\n");
    printf("[-6 num]\t\t            define o numero de peças tipo 6 a serem colocadas no tabuleiro.\n");
    printf("[-7 num]\t\t            define o numero de peças tipo 7 a serem colocadas no tabuleiro.\n");
    printf("[-8 num]\t\t            define o numero de peças tipo 8 a serem colocadas no tabuleiro.\n");
    printf("\nAlgumas restrições:\n");
    printf("As dimensoes validas do tabuleiro são multiplos de 3,estando o numero de Linhas inserido no intervalo [9-15] e o numero de Colunas inserido no intervalo [9-24].\n");
    printf("As entradas referentes à definiçao do numero de peças a serem colocadas not tabuleiro apenas deverão ser consideradas caso o modo de posicionamento 2 esteja definido.\n");
    printf("O numero de peças a serem colocadas no tabuleiro deverá ser menor ou igual à capacidade total do tabuleiro escolhido.\n");
    printf("O numero de peças de tipos superiores deverá ser sempre menor ou igual ao numero de peças do tipo inferior.\n");
    printf("Na invocação do modo de jogo 1 o utilizador não deve introduzir o modo de disparo.\n");

    printf("\nexemplos válidos da invocação do modo de jogo 0, 1 e 2 respetivamente:\n");
    printf("./wargame -t 12x12 -j 0 -p 1\n");
    printf("./wargame -t 12x15 -j 1 -p 2 -1 3 -2 3 -3 1 -4 1 -5 1\n");
    printf("./wargame -t 15x24 -j 2 -p 2 -d 3 -1 3 -2 3 -3 3 -4 3 -5 2 -6 2 -7 1\n");

}

//POSICIONAMENTO 1
void posicionamento_1(int M,int N,char tabuleiro[M][N],char instpeca[43][3][3],int nr_pecas[9])
{
int try,m,n,i,j;
int var=0;
int r1;//restricao 1

for(m=0;m<M/3;m++){//Matriz 9x9
    for(n=0;n<N/3;n++){
        if(n>0) num_pecas(nr_pecas,var);
        try=0;
        do{
            var=escolhe_var_p1(&try);

            for(i=0;i<3;i++){//Matriz 3x3
                for(j=0;j<3;j++){
                  tabuleiro[m*3+i][n*3+j]=instpeca[var][i][j];
                }
            }
        r1=restricao_1(M,N,tabuleiro);
        }
     while(r1);
    }
     num_pecas(nr_pecas,var);
  }
  print_num_pecas(M,N,nr_pecas);
}

int escolhe_var_p1(int *try)
{
int var;
var=rand()%43;
    if(*try++>4){
     var=5;
    }

return var;
}

int restricao_1(int M,int N,char tabuleiro[M][N])
{
int i,j,k,x,y,m,n;
int pos[8][2]={{-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1}};//posicoes adjacentes ao centro da matriz
char not_this_matrix[M][N];


    for(k=0;k<9;k++){
        for(m=0;m<M/3;m++){
            for(n=0;n<N/3;n++){
                inic(M,N,not_this_matrix);
                inic_0(M,N,not_this_matrix,m,n);
                for(i=0;i<3;i++){
                    for(j=0;j<3;j++){
                        x=n*3+j+pos[k][0];
                        y=m*3+i+pos[k][1];
                            if((y>-1 && y<M) && (x>-1 && x<N)){
                                if(tabuleiro[m*3+i][n*3+j]!=ESPACO && (tabuleiro[y][x]!=ESPACO && not_this_matrix[y][x]!='0'))
                                    return 1;
                            }
                    }
                }

            }
        }

    }

return 0;
}

void num_pecas(int nr_pecas[9],int var)
{
              if(var>0 && var<10)
                nr_pecas[1]++;
              if(var>=10 && var<22)
                nr_pecas[2]++;
              if(var>=22 && var<28)
                nr_pecas[3]++;
              if(var>=28 && var<32)
                nr_pecas[4]++;
              if(var>=32 && var<36)
                nr_pecas[5]++;
              if(var>=36 && var<40)
                nr_pecas[6]++;
              if(var>=40 && var<42)
                nr_pecas[7]++;
              if(var>41)
                nr_pecas[8]++;
              if(var==0)
                nr_pecas[0]++;

}

void print_num_pecas(int M,int N,int nr_pecas[9])
{
    int i;
    putchar('\n');
    printf("%dx%d ",M,N);
    for( i = 1; i < 9; i++)
    {
        printf("%d ",nr_pecas[i]);
    }
    putchar('\n');
}

void inic(int M,int N,char s[M][N])//inicia o tabuleiro com matrizes nulas
{
int i,j;
    for(i=0;i<M;i++)
      for(j=0;j<N;j++)
          s[i][j]=ESPACO;
}

void linha(int M,int N,char s[M][N])//identifica as linhas
{
    int i,j,lin;
    for(i=0,lin=M;i<M && lin>=1;i++,lin--)
    {
      if(lin<=9){
        putchar(' ');
        printf("%d",lin);
        putchar(' ');
        }
      else{
        printf("%d",lin);
        putchar(' ');
        }
      for(j=0;j<N;j++)
        printf("%c ", s[i][j]);
      putchar('\n');
    }
}

int colunas(int N)//identifica as colunas
{
int i;
putchar(' ');
putchar(' ');
putchar(' ');
for(i=65;i<65+N;i++)
    printf("%c ",(char)i);

return 0;
}

//POSICIONAMENTO 2
void inic_0(int M,int N,char s[M][N],int m,int n)//faz o programa ignorar a restricao 1 para as peças na mesma matriz 3x3
{
int i,j;
    for(i=0;i<3;i++)
      for(j=0;j<3;j++)
          s[m*3+i][n*3+j]='0';
return;
}

void reset(int M,int N,int s[M*N/9])//da reset no vetor tipo aleatorio
{
int i;
    for(i=0;i<M*N/9;i++)
          s[i]=0;
return;
}

void tipo_aleatorio(int M,int N,int tipo_peca[9],int distribuicao[M*N/9],int random_tipo[M*N/9])
{
int i,j,pos,pos_max;
int copia_tipo_peca[9];

    for(i=0;i<9;i++)//Faz uma copia do tabuleiro inicial
    {
       copia_tipo_peca[i]=tipo_peca[i];
    }
    for(i = 0, j=0; i <9; i++){
        while(copia_tipo_peca[i]--> 0){
        distribuicao[j] = i;
        j++;
        }
    }
pos_max=M*N/9;
    while(pos_max!=0){//percorre todo o vetor incluindo a posiçao 0
        for(i=0;i<M*N/9;i++){//escolhe aleatoriamente uma posiçao do vetor distribuiçao e atribui esse valor ao vetor tipo, onde é indicada a ordem de implementaçao do tipo de peça no tabuleiro p.e. tipo[0]=1ºpeca do tab
        pos=rand()%pos_max;
        random_tipo[i]= distribuicao[pos];

            if(pos!=pos_max){
                swap(&distribuicao[pos],&distribuicao[pos_max-1]);
            }
        pos_max--;    //decrementa o numero de posiçoes disponiveis
        }
    }
return;
}

int escolhe_var_try(int M,int N,int random_tipo[M*N/9],int k,int *var,int vezes) //posicionamento 2_P4
{
int a=*var;
    switch(random_tipo[k]){//P3
          case 0:{
              return 0;
          break;
          }
          case 1:{
            if(vezes==0)  return 1;
            while(a<9){
                a++;
                return a;
            }
          break;
          }
          case 2:{
            if(vezes==0)  return 10;
            while(a<21){
                a++;
                return a;
            }
          break;
          }
          case 3:{
            if(vezes==0)  return 22;
            while(a<27){
                a++;
                return a;
            }
          break;
          }
          case 4:{
            if(vezes==0)  return 28;
            while(a<31){
                a++;
                return a;
            }
          break;
          }
          case 5:{
            if(vezes==0)  return 32;
            while(a<35){
                a++;
                return a;
            }
          break;
          }
          case 6:{

              if(a<39)  a++;
               if(vezes==0) a=36;
          break;
          }
          case 7:{

            if(vezes==0){
             return 40;
             }
            else{
             return 41;
            }
          break;
          }
          case 8:{
             return 42;
          break;
          }
        }
return a;
}

int escolhe_var_p2(int M,int N,int random_tipo[M*N/9],int k)//escolhe a variante aleatoriamente
{
int var;
    switch(random_tipo[k]){//P3
          case 0:{
          var=0;
          break;
          }
          case 1:{
           var=rand()%9+1;
          break;
          }
          case 2:{
          var= rand()%12+10;
          break;
          }
          case 3:{
          var= rand()%6+22;
          break;
          }
          case 4:{
          var= rand()%4+28;
          break;
          }
          case 5:{
          var=rand()%4+32;
          break;
          }
          case 6:{
          var=rand()%4+36;
          break;
          }
          case 7:{
          var= rand()%2+40;
          break;
          }
          default:
          case 8:{
          var=42;
          break;
          }
        }
return var;
}

int restricao_3(int M,int N,int tipo_peca[9])
{
int i,j,nr_pecas;
int nr_pecas_total=M*N/9;

nr_pecas=soma(tipo_peca[1],tipo_peca[2],tipo_peca[3],tipo_peca[4],tipo_peca[5],tipo_peca[6],tipo_peca[7],tipo_peca[8]);//pecas tipo 1-8
tipo_peca[0]=nr_pecas_total-nr_pecas;
    //RESTRICAO 4
    if(tipo_peca[0]<nr_pecas)
    {
     return 1;
    }
    //RESTRICAO 3
    for(i=1;i<8;i++){
        for(j=1;j<9-i;j++){
            if(tipo_peca[i]<tipo_peca[i+j])
            {
            return 1;
            }
        }
    }
return 0;
}

int soma(int a,int b, int c, int d, int e, int f, int g, int h)
{
    return a+b+c+d+e+f+g+h;
}

void swap(int *x, int *y)
{
int temp;
    temp= *x;
    *x = *y;
    *y = temp;
return;
}

int posicionamento_2(int M,int N,char tabuleiro[M][N],char instpeca[43][3][3],int random_tipo[M*N/9])
{
int m,n,i,j,r1,try;
int nr_pecas_total=M*N/9;//num matrizes
int k=0;
int var=0;
int vezes=0;//posiçao inicial na sequencia de peças do mesmo tipo

    for(m=0;m<M/3;m++){
        for(n=0;n<N/3;n++,k++){
          try=0;
            do{
                    if(try++>9){
                        return 1;
                    }
                    if(k==nr_pecas_total){
                    return 0;
                    }

                    if(try>1){
                    var=escolhe_var_try(M,N,random_tipo,k,&var,vezes);//percorre todas as instancias possiveis
                    vezes++;
                    }
                    else
                    {
                    var= escolhe_var_p2(M,N,random_tipo,k);//escolha aleatoria
                    }
                    for(i=0;i<3;i++){
                        for(j=0;j<3;j++){
                            tabuleiro[m*3+i][n*3+j]=instpeca[var][i][j];
                        }
                    }
                r1=restricao_1(M,N,tabuleiro);
            }
            while(r1);
        }
    }
return 0;
}


//DISPARO 1
void disparo_1(int M,int N,char tabuleiro[M][N],char tabuleiro_disparo[M][N],char tab_verifica_disparo[M][N],int *jogadas)
{
int x;
    do{
    disparo_aleatorio(M,N,tabuleiro,tabuleiro_disparo,tab_verifica_disparo,&*jogadas);
    x=fim_d(M,N,tabuleiro);
    }while(!x);

return;
}

void disparo_aleatorio(int M,int N,char tabuleiro[M][N],char tabuleiro_disparo[M][N],char tab_verifica_disparo[M][N],int *jogadas)//Faz disparo aleatórios sem repetições
{
//gera posiçoes aleatorias na matriz, atibuindo o valor do disparo no interface, quer seja navio ou agua
int i,j;
    do{
    i=rand()%M;
    j=rand()%N;
    }
    while(tab_verifica_disparo[i][j]=='0');

    if(tabuleiro[i][j]!=ESPACO) tabuleiro_disparo[i][j]=tabuleiro[i][j];
    tab_verifica_disparo[i][j]='0';
    tabuleiro[i][j]=ESPACO;

    print_posicao_disp1(M,N,i,j,tabuleiro_disparo);
    *jogadas = contagem_(&*jogadas);

return;
}

int fim_d(int M,int N,char tabuleiro[M][N])
{
int i,j;
    for(i=0;i<M;i++){
        for(j=0;j<N;j++){
            if(tabuleiro[i][j]!=ESPACO) return 0;
        }
    }
return 1;
}

int contagem_(int *jogadas)
{
    return *jogadas+1;
}

void print_posicao_disp1(int M,int N,int i,int j,char tabuleiro_disparo[M][N])
{
int num=M-i;
int letra=65+j;
    printf("%c%d\n'%c'\n",(char)letra,num,tabuleiro_disparo[i][j]);
return;
}

//DISPARO 2
void disparo_2(int M,int N,char tabuleiro[M][N],char tabuleiro_disparo[M][N],char tab_verifica_disparo[M][N],int *jogadas)
{
tab_verifica_disparo[M][N]=tabuleiro[M][N];
int num_disparo=0;//numero do disparo dentro de uma matriz 3x3
int m=0;
int n=0;
int x,y;//variaveis de restricoes
y=1;

    do{
    coordenadas_disparo(M,N,tabuleiro_disparo,tabuleiro,&m,&n,&num_disparo,&*jogadas);
    putchar('\n');
    x=verif_disp2(M,N,tabuleiro,&m,&n);//verifica se a matriz 3x3 ainda apresenta peças
      if(x){
        num_disparo=0;//reset do numero
        n++;
        if(n==N/3){
            n=0;
            m++;
            if(m==M/3)
                return;
        }
      }
    if(tab_verifica_disparo[M][N]!=tabuleiro[M][N])
        y=fim_d2(M,N,tabuleiro_disparo,tab_verifica_disparo);
    }
    while(y);//enquanto o tabuleiro de disparo nao for igual ao tabuleiro inicial

    linha(M,N,tabuleiro_disparo);// da print da matriz
    colunas(N);
return;
}

void coordenadas_disparo(int M,int N,char tabuleiro_disparo[M][N],char tabuleiro[M][N],int *m, int *n,int *num_disparo,int *jogadas)
{
int i,j;
    switch(*num_disparo){
        case 0:{
            i=1;
            j=1;
            break;
        }
        case 1:{
            i=0;
            j=1;
            break;
        }
        case 2:{
            i=2;
            j=1;
            break;
        }
        case 3:{
            i=1;
            j=0;
            break;
        }
        case 4:{
            i=1;
            j=2;
            break;
        }
        case 5:{
            i=0;
            j=0;
            break;
        }
        case 6:{
            i=2;
            j=2;
            break;
        }
        case 7:{
            i=0;
            j=2;
            break;
        }
        default:
        case 8:{
            i=2;
            j=0;
            break;
        }
    }

        if(tabuleiro[*m*3+i][*n*3+j]!=ESPACO)    tabuleiro_disparo[*m*3+i][*n*3+j]=tabuleiro[*m*3+i][*n*3+j];

    tabuleiro[*m*3+i][*n*3+j]=ESPACO;

    *num_disparo = contagem_(&*num_disparo);
    *jogadas = contagem_(&*jogadas);
    print_posicao_disp2(M,N,*m,*n,i,j,tabuleiro_disparo);
return;
}

int verif_disp2(int M,int N,char tabuleiro[M][N], int *m, int *n)
{

          if((tabuleiro[*m*3][*n*3]==tabuleiro[*m*3+1][*n*3]) && (tabuleiro[*m*3][*n*3]==tabuleiro[*m*3+2][*n*3]) && (tabuleiro[*m*3][*n*3] == tabuleiro[*m*3+1][*n*3+1])
            && (tabuleiro[*m*3][*n*3]==tabuleiro[*m*3+2][*n*3+1]) && (tabuleiro[*m*3][*n*3]==tabuleiro[*m*3+1][*n*3+2]) && (tabuleiro[*m*3][*n*3]==tabuleiro[*m*3+2][*n*3+2])
            && (tabuleiro[*m*3][*n*3]==tabuleiro[*m*3][*n*3+1]) && (tabuleiro[*m*3][*n*3]==tabuleiro[*m*3][*n*3+2]))
                return 1;
return 0;
}

int fim_d2(int M,int N,char tabuleiro_disparo[M][N], char tab_verifica_disparo[M][N])
{
    if(tabuleiro_disparo==tab_verifica_disparo) return 1;
return 0;

}

void print_posicao_disp2(int M,int N,int m, int n,int i,int j,char tabuleiro_disparo[M][N])
{
int num=M-m*3-i;
int letra=65+n*3+j;
    printf("%c%d\n'%c'",(char)letra,num,tabuleiro_disparo[m*3+i][n*3+j]);
return;
}

//DISPARO 3
void disparo_3(int M,int N,char tabuleiro[M][N],char tabuleiro_disparo[M][N],char tab_verifica_disparo[M][N],int *jogadas)
{
tab_verifica_disparo[M][N]=tabuleiro[M][N];
char posic_adjacente[M][N];//matriz com a marcacao das
inic(M,N,posic_adjacente);
int num_disparo=0;//numero do disparo dentro de uma matriz 3x3
int m=0;
int n=0;
int x,y;//variaveis de restricoes
y=1;

    do{
    coordenadas_disparo_3(M,N,posic_adjacente,tabuleiro_disparo,tabuleiro,&m,&n,&num_disparo,&*jogadas);
    putchar('\n');
    x=verif_disp2(M,N,tabuleiro,&m,&n);//verifica se a matriz 3x3 já nao tem mais peças
      if(x){
        restricao_disparo(M,N,tabuleiro_disparo,posic_adjacente);//elimina posiçoes de disparo adjacentes a peças anteriormente acertadas
        num_disparo=0;//reset do numero
        n++;
        if(n==N/3){
            n=0;
            m++;
            if(m==M/3)
                return;
        }
      }
    if(tab_verifica_disparo[M][N]!=tabuleiro[M][N])
        y=fim_d2(M,N,tabuleiro_disparo,tab_verifica_disparo);
    }
    while(y);//enquanto o tabuleiro de disparo nao for igual ao tabuleiro inicial

    linha(M,N,tabuleiro_disparo);// da print da matriz
    colunas(N);
return;
}

void restricao_disparo(int M,int N,char tabuleiro_disparo[M][N],char posic_adjacente[M][N])
{
int i,j,k,x,y,m,n;
int pos[8][2]={{-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1}};//posicoes adjacentes ao centro da matriz

    for(k=0;k<9;k++){
        for(m=0;m<M/3;m++){
            for(n=0;n<N/3;n++){
                for(i=0;i<3;i++){
                    for(j=0;j<3;j++){
                        x=n*3+j+pos[k][0];
                        y=m*3+i+pos[k][1];
                            if((y>-1 && y<M) && (x>-1 && x<N))
                                if(tabuleiro_disparo[m*3+i][n*3+j]!=ESPACO)   posic_adjacente[y][x]='X';
                    }
                }

            }
        }

    }

return;
}

void coordenadas_disparo_3(int M,int N,char posic_adjacente[M][N],char tabuleiro_disparo[M][N],char tabuleiro[M][N],int *m, int *n,int *num_disparo,int *jogadas)
{
   int i,j;
    do{
    switch(*num_disparo){
        case 0:{
            i=1;
            j=1;
            break;
        }
        case 1:{
            i=0;
            j=1;
            break;
        }
        case 2:{
            i=2;
            j=1;
            break;
        }
        case 3:{
            i=1;
            j=0;
            break;
        }
        case 4:{
            i=1;
            j=2;
            break;
        }
        case 5:{
            i=0;
            j=0;
            break;
        }
        case 6:{
            i=2;
            j=2;
            break;
        }
        case 7:{
            i=0;
            j=2;
            break;
        }
        case 8:{
            i=2;
            j=0;
            break;
        }
        default:
            i=0;
            j=0;
            break;
      }
    *num_disparo = contagem_(&*num_disparo);
    }
    while(posic_adjacente[*m*3+i][*n*3+j]=='X');

        if(tabuleiro[*m*3+i][*n*3+j]!=ESPACO)    tabuleiro_disparo[*m*3+i][*n*3+j]=tabuleiro[*m*3+i][*n*3+j];

    tabuleiro[*m*3+i][*n*3+j]=ESPACO;
    *jogadas = contagem_(&*jogadas);
    print_posicao_disp2(M,N,*m,*n,i,j,tabuleiro_disparo);
return;
}


//MODO JOGO 1
void input_coord(int M,int N,char tab_verifica_disparo[M][N],char tabuleiro_disparo[M][N],char tabuleiro[M][N],int *jogadas)
{
    int linha;
    char coluna;
    int i,j;

    scanf(" %c %d",&coluna,&linha);

    //Conversao das coordenadas para posicoes do tabuleiro
    i=M-linha;
    j=(int)coluna-65;

    if(tabuleiro[i][j]!=ESPACO)
        {
        tabuleiro_disparo[i][j]=tabuleiro[i][j];
        }

    printf("%c\n",tabuleiro[i][j]);
    tabuleiro[i][j]=ESPACO;

    *jogadas = contagem_(&*jogadas);

return;
}

void print_header1(void)
{
    printf("* ================================\n");
    printf("* Modo de Jogo 1\n");
    printf("* Insira as Coordenadas de Disparo\n");
    printf("* ================================");

return;
}

void modo_jogo_1(int M,int N,char tabuleiro[M][N],char tabuleiro_disparo[M][N],char tab_verifica_disparo[M][N], int nr_pecas[9],int *jogadas)
{
int x;
    tab_verifica_disparo[M][N]=tabuleiro[M][N];
    do
    {
    input_coord(M,N,tab_verifica_disparo,tabuleiro_disparo,tabuleiro,&*jogadas);
        x=fim_j1(M,N,tabuleiro,tabuleiro_disparo);
    }
    while(x);
return;
}

int fim_j1(int M,int N,char tabuleiro[M][N], char tabuleiro_disparo[M][N])
{
int i,j;
    for(i=0;i<M;i++){
        for(j=0;j<N;j++){
            if(tabuleiro[i][j]!=ESPACO)    return 1;
        }
    }
return 0;
}

//MODO JOGO 2
void print_header2(void)
{
    printf("* ================================\n");
    printf("* Modo de Jogo 2\n");
    printf("* Crie um tabuleiro com as caracteristicas indicadas\n");
    printf("* Responda aos disparos do programa\n");
    printf("* ================================");

return;
}

void modo_jogo_2(int M,int N,int modo_disparo,char tabuleiro[M][N],char tabuleiro_disparo[M][N],char tab_verifica_disparo[M][N], int nr_pecas[9],int *jogadas)
{
        if(modo_disparo==1){//disparo 1
        disparo_1(M,N,tabuleiro,tabuleiro_disparo,tab_verifica_disparo,&*jogadas);
        }
        if(modo_disparo==2){//disparo 2
        disparo_2(M,N,tabuleiro,tabuleiro_disparo,tab_verifica_disparo,&*jogadas);
        }
        if(modo_disparo==3)//disparo 3
        {
        disparo_3(M,N,tabuleiro,tabuleiro_disparo,tab_verifica_disparo,&*jogadas);
        }
}
