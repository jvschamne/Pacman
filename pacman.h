#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 20

typedef struct {
  int x;
  int y;
} Point;

typedef struct pac {
  Point p;
  struct pac *next;
} Pac;

/*Cria um struct pac vazio.*/
Pac* createPac ();

/*Adiciona um item na cabeça da lista.*/
Pac* insertFront (Pac *pac, Point p, char field[][SIZE], char carac);

/*Remove um item da cauda da lista.*/
Pac* deleteRear (Pac *pac, char field[][SIZE]);

/*Retorna sem remover o item na cabeça da lista.*/
Point getFront (Pac *pac);

Pac* insertFrontGhost (Pac *ghost, Point p, char field[][SIZE], int *flag);

Pac* ghostMove (Pac *g, char field[][SIZE], int *flag);

int kbhit(void);

int initialize_field (char field[][SIZE]);

void print_field (char field[][SIZE]);

int ganhou(int pontosTotais, int pontos);

int morreu (Pac *pac, Pac *ghost1, Pac *ghost2, char field[SIZE][SIZE], int *flag1, int *flag2);
