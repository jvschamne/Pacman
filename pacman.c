#include "pacman.h"

Pac* createPac () {
          return NULL;
}

/*Função que retorna a coordenada armazenada na cabeça da lista encadeada!*/
Point getFront (Pac *pac) {
        return pac->p;
}

/*Função para inserir na cabeça da lista encadeada!*/
Pac* insertFront (Pac *pac, Point p, char field[][SIZE], char carac) {

        Pac *novo = (Pac*) malloc(sizeof(Pac));
        novo->p = p;
        novo->next = pac;

         field[novo->p.x][novo->p.y] = carac; /*Ponto inserido faz parte do corpo do Pacman!*/
         return novo;
}

Pac* insertFrontGhost (Pac *pac, Point p, char field[][SIZE], int *flag) {
        Pac *novo = (Pac*) malloc(sizeof(Pac));
        novo->p = p;
        novo->next = pac;

        if(field[novo->p.x][novo->p.y] == ' '){
          *flag = 0;
        }
        else if(field[novo->p.x][novo->p.y] == '.'){
          *flag = 1;
        }
        else if(field[novo->p.x][novo->p.y] == '<' || field[novo->p.x][novo->p.y] == '>'|| field[novo->p.x][novo->p.y] == 'A' || field[novo->p.x][novo->p.y] == 'V'){
          *flag = 2;
        }

         field[novo->p.x][novo->p.y] = 'X'; /*Ponto inserido faz parte do corpo do Pacman!*/
         return novo;
}

Pac* ghostMove (Pac *g, char field[][SIZE], int *flag) {

          Pac *ultimo = g->next;

          if(*flag == 0)
            field[ultimo->p.x][ultimo->p.y] = ' ';
          else if(*flag == 1)
            field[ultimo->p.x][ultimo->p.y] = '.';

          free(ultimo);

          return g;
}

/*Função para remover a cauda da lista encadeada!*/
Pac* deleteRear (Pac *pac, char field[][SIZE]) {

          Pac *ultimo = pac->next;

          field[ultimo->p.x][ultimo->p.y] = ' ';

          free(ultimo);

           return pac;
}

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

int initialize_field (char field[SIZE][SIZE]) {
    int i, j, cont=-1;

    for(i = 0; i < SIZE; i++){
      for(j = 0; j < SIZE; j++){
        /*inicializa as bordas com 'O' e as posições vagas com '.'*/
        if(i == 0 || i == (SIZE-1) || (j == 0 || j==(SIZE-1)))
          field[i][j] = 'O';
        else
          field[i][j] = '.';
      }
    }

    field[2][2] = '#';
    field[2][3] = '#';
    field[2][4] = '#';
    field[3][2] = '#';
    field[3][3] = '#';
    field[3][4] = '#';
    field[4][2] = '#';
    field[4][3] = '#';
    field[4][4] = '#';
    field[5][2] = '#';
    field[5][3] = '#';
    field[5][4] = '#';

    field[2][6] = '#';
    field[3][6] = '#';
    field[4][6] = '#';
    field[5][6] = '#';
    field[2][7] = '#';
    field[3][7] = '#';
    field[4][7] = '#';
    field[5][7] = '#';

    field[2][12] = '#';
    field[3][12] = '#';
    field[4][12] = '#';
    field[5][12] = '#';
    field[2][13] = '#';
    field[3][13] = '#';
    field[4][13] = '#';
    field[5][13] = '#';

    field[2][15] = '#';
    field[2][16] = '#';
    field[2][17] = '#';
    field[3][15] = '#';
    field[3][16] = '#';
    field[3][17] = '#';
    field[4][15] = '#';
    field[4][16] = '#';
    field[4][17] = '#';
    field[5][15] = '#';
    field[5][16] = '#';
    field[5][17] = '#';

    field[1][9] = '#';
    field[2][9] = '#';
    field[3][9] = '#';
    field[4][9] = '#';
    field[5][9] = '#';
    field[1][10] = '#';
    field[2][10] = '#';
    field[3][10] = '#';
    field[4][10] = '#';
    field[5][10] = '#';

    field[7][1] = '#';
    field[7][2] = '#';
    field[7][3] = '#';
    field[8][1] = '#';
    field[9][3] = '#';
    field[10][2] = '#';
    field[10][3] = '#';
    field[11][3] = '#';
    field[12][1] = '#';
    field[13][1] = '#';
    field[13][2] = '#';
    field[13][3] = '#';

    field[12][7] = '#';
    field[12][12] = '#';

    field[7][16] = '#';
    field[7][17] = '#';
    field[7][18] = '#';
    field[8][18] = '#';
    field[9][16] = '#';
    field[10][16] = '#';
    field[10][17] = '#';
    field[11][16] = '#';
    field[12][18] = '#';
    field[13][18] = '#';
    field[13][17] = '#';
    field[13][16] = '#';

    field[7][5] = '#';
    field[8][5] = '#';
    field[9][5] = '#';
    field[10][5] = '#';
    field[11][5] = '#';
    field[12][5] = '#';
    field[9][6] = '#';
    field[9][7] = '#';
    field[10][6] = '#';
    field[10][7] = '#';

    field[7][14] = '#';
    field[8][14] = '#';
    field[9][14] = '#';
    field[10][14] = '#';
    field[11][14] = '#';
    field[12][14] = '#';
    field[9][13] = '#';
    field[9][12] = '#';
    field[10][13] = '#';
    field[10][12] = '#';

    field[7][7] = '#';
    field[7][8] = '#';
    field[7][9] = '#';
    field[7][10] = '#';
    field[7][11] = '#';
    field[7][12] = '#';
    field[8][9] = '#';
    field[8][10] = '#';
    field[9][9] = '#';
    field[9][10] = '#';


    field[14][7] = '#';
    field[14][8] = '#';
    field[14][9] = '#';
    field[14][10] = '#';
    field[14][11] = '#';
    field[14][12] = '#';
    field[13][9] = '#';
    field[13][10] = '#';
    field[12][9] = '#';
    field[12][10] = '#';

    field[15][2] = '#';
    field[15][3] = '#';
    field[15][4] = '#';
    field[16][2] = '#';
    field[16][3] = '#';
    field[16][4] = '#';
    field[17][2] = '#';
    field[17][3] = '#';
    field[17][4] = '#';
    field[14][5] = '#';
    field[15][5] = '#';
    field[16][5] = '#';
    field[17][5] = '#';

    field[15][15] = '#';
    field[15][16] = '#';
    field[15][17] = '#';
    field[16][15] = '#';
    field[16][16] = '#';
    field[16][17] = '#';
    field[17][15] = '#';
    field[17][16] = '#';
    field[17][17] = '#';
    field[14][14] = '#';
    field[15][14] = '#';
    field[16][14] = '#';
    field[17][14] = '#';

    field[16][7] = '#';
    field[17][7] = '#';

    field[16][12] = '#';
    field[17][12] = '#';

    field[16][9] = '#';
    field[17][9] = '#';
    field[18][9] = '#';
    field[16][10] = '#';
    field[17][10] = '#';
    field[18][10] = '#';

    field[10][0]= '.';
    field[10][19]= '.';

    for(i = 0; i < SIZE; i++){
      for(j = 0; j < SIZE; j++){
        if(field[i][j]=='.'){
          cont++;
        }
      }
    }
    return cont-2;
}

void print_field (char field[SIZE][SIZE]) {
  int i, j;

  for (i = 0; i < SIZE; i++){
    for (j = 0; j < SIZE; j++){
      if(field[i][j] == 'V' || field[i][j] == 'A' || field[i][j] == '>' || field[i][j] == '<'){
        printf("\033[33m%c ", field[i][j]);
      }
      else if(field[i][j] == 'X'){
        printf("\033[31m%c ", field[i][j]);
      }
      else if(field[i][j] == '.'){
        printf("\033[37m%c ", field[i][j]);
      }
      else if(field[i][j] == 'O'){
        printf("\033[34m%c ", field[i][j]);
      }
      else{
        printf("\033[36m%c ", field[i][j]);
      }
    }
    printf("\n");
  }
}

int ganhou(int pontosTotais, int pontos){
  if(pontos == pontosTotais)
    return 1;
  else
    return 0;
}

int morreu (Pac *pac, Pac *ghost1, Pac *ghost2, char field[SIZE][SIZE], int *flag, int *flag2) {

   Point p = getFront (pac);
   Point g1 = getFront (ghost1);
   Point g2 = getFront (ghost2);

  /*se bater nas paredes externas*/
   if (p.x < 1 || p.x > SIZE-2 || (p.y < 1 && p.x!=10)|| (p.y > SIZE-2 && p.x!=10)){
      return 1;
   }

  else if((g1.x == p.x) && (g1.y == p.y))/*se as coordenadas dos fantasmas foram iguais às do pacman*/
      return 1;
  else if((g2.x == p.x) && (g2.y == p.y))/*se as coordenadas dos fantasmas foram iguais às do pacman*/
      return 1;
  else if(*flag == 2 || *flag2 == 2)/*se o pacman atravessar o fantasma*/
      return 1;
   else
      return 0;
}

