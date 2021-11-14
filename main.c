#include "pacman.h"

int main () {
   char field[SIZE][SIZE];/*mapa do jogo*/
   int pontosTotais = initialize_field (field), pontos=0;
   int center = SIZE/2;
   int dirGhost1 = 1;/*direcao do ghost1: 1 para direita e 0 para esquerda*/
   int dirGhost2 = 0;/*direcao do ghost2: 1 para cima e 0 baixo*/
   int flagG1 = 1; /*se ghost1 passou por cima de um espaco(0) vazio ou de 1 ponto(1) ou do pacman (2)*/
   int flagG2 = 1;/*determina se o ghost2 passou por cima de um espaco(0) vazio, de 1 ponto(1) ou do pacman (2)*/

   Pac *pac = createPac();/*criando pacman*/
   Pac *ghost1 = createPac(); /*criando ghost1*/
   Pac *ghost2 = createPac(); /*criando ghost2*/

   /*Inserindo o PACMAN no campo: */
   pac = insertFront (pac, (Point){center, center}, field, '<');

   /*Inserindo os Ghosts no campo: */
   ghost1 = insertFrontGhost(ghost1, (Point){6, 1}, field, &flagG1);
   ghost2 = insertFrontGhost(ghost2, (Point){11, 6}, field, &flagG2);

   char pressionou_prv = ' ';
   char pressionou_act = ' ';
   int reverse = 0; /*variável para inverter o pacman (e vice-versa)*/

   int flag = 0;/*determina se o jogador venceu(1) ou perdeu o jogo(0)*/

    while (!morreu(pac, ghost1, ghost2, field, &flagG1, &flagG2)) {

      if(ganhou(pontosTotais, pontos)){
            flag = 1;
            break;
      }
      while((!kbhit()) && (!morreu(pac, ghost1, ghost2, field, &flagG1, &flagG2))) {
            /*Movimentação dos Ghosts*/
            Point g1 = getFront(ghost1);
            if(dirGhost1 == 1){
              if(field[g1.x][g1.y+1] == 'O'){
                dirGhost1 = 0;
              }
              else{
                ghost1 = insertFrontGhost (ghost1, (Point){g1.x, g1.y+1}, field, &flagG1);
                ghostMove(ghost1, field, &flagG1);
              }
            }
            else{/*se a direção for igual a 0*/
              if(field[g1.x][g1.y-1] == 'O'){
                dirGhost1 = 1;
              }
              else{
                ghost1 = insertFrontGhost (ghost1, (Point){g1.x, g1.y-1}, field, &flagG1);
                ghostMove(ghost1, field, &flagG1);
              }
            }

            Point g2 = getFront(ghost2);
            if(dirGhost2 == 1){
              if(field[g2.x-1][g2.y] == 'O' || field[g2.x-1][g2.y] == '#'){
                dirGhost2 = 0;
              }
              else{
                ghost2 = insertFrontGhost (ghost2, (Point){g2.x-1, g2.y}, field, &flagG2);
                ghostMove(ghost2, field, &flagG2);
              }
            }
            else{/*se a direção for igual a 0*/
              if(field[g2.x+1][g2.y] == 'O' || field[g2.x+1][g2.y] == '#'){
                dirGhost2 = 1;
              }
              else{
                ghost2 = insertFrontGhost (ghost2, (Point){g2.x+1, g2.y}, field, &flagG2);
                ghostMove(ghost2, field, &flagG2);
              }
            }

            /*MOVIMENTAÇÃO DO PACMAN + IMPEDIR QUE ATRAVESSE A PAREDE*/
            Point p = getFront (pac);
            if (pressionou_act ==  'w' && field[p.x-1][p.y] != '#') {
               if(field[p.x-1][p.y]=='.') pontos++;
              pac = insertFront (pac, (Point){p.x-1, p.y}, field, 'V');
              pac = deleteRear (pac, field);
            }
            else if (pressionou_act == 's' && field[p.x+1][p.y]!='#') {
              if(field[p.x+1][p.y]=='.') pontos++;
              pac = insertFront (pac, (Point){p.x+1, p.y}, field, 'A');
              pac = deleteRear (pac, field);
            }
            else if (pressionou_act ==  'a' && field[p.x][p.y-1]!='#') {
              if(field[p.x][p.y-1]=='.') pontos++;
              if(p.x==10 && p.y==0){
                if(field[10][19]=='.') pontos++;
                pac = insertFront (pac, (Point){10, 19}, field, '>');
              }
               else pac = insertFront (pac, (Point){p.x, p.y-1}, field, '>');
               pac = deleteRear (pac, field);

            }
            else if(pressionou_act ==  'd' && field[p.x][p.y+1]!='#') {
              if(field[p.x][p.y+1]=='.') pontos++;
              if(p.x==10 && p.y==19){
                if (field[10][0]=='.') pontos++;
                pac = insertFront (pac, (Point){10, 0}, field, '<');
              }
              else pac = insertFront (pac, (Point){p.x, p.y+1}, field, '<');
              pac = deleteRear (pac, field);


            }


          print_field (field);/*Printando o mapa*/
          printf("\033[37m\npontos a serem pegos:%d\n",pontosTotais);
          printf("\033[37mpontos:%d\n",pontos);
          usleep(250000);
          system("clear");
      }
      if (!morreu(pac, ghost1, ghost2, field, &flagG1, &flagG2)) {
          /*Cada vez que uma tecla é pressionada o controle executa esse trecho:*/
          pressionou_prv = pressionou_act;
          pressionou_act = getchar();
          if ((pressionou_act ==  'a') && (pressionou_prv ==  'w')) { reverse = !reverse; }
          else if ((pressionou_act ==  'w') && (pressionou_prv ==  's')) { reverse = !reverse; }
          else if ((pressionou_act ==  'a') && (pressionou_prv ==  'd')) { reverse = !reverse; }
          else if ((pressionou_act ==  'd') && (pressionou_prv ==  'a')) { reverse = !reverse; }
      }
   }

   if(flag==1){
     printf("GANHOU!!!\n");
     return 0;
   }
   else{
     printf ("MORREU :(  \n");
     return 0;
   }
}

