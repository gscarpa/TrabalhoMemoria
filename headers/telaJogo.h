#ifndef TELAJOGO_H
#define TELAJOGO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>

int telaJogo(ALLEGRO_BITMAP **sprites, ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_SAMPLE **score, ALLEGRO_EVENT_QUEUE **timerQueue, int *erros, ALLEGRO_SAMPLE **error);
void updateGameScreen(ALLEGRO_BITMAP **sprites, int **frames, int **matriz, int *larguraSprite, int *alturaSprite, int *erros, int *acertos, ALLEGRO_FONT *font);
void flipCard(ALLEGRO_BITMAP **sprites, int **frames, int **matriz, int posI, int posJ, ALLEGRO_EVENT_QUEUE **timerQueue, ALLEGRO_EVENT *event, int *larguraSprite, int *alturaSprite, int *erros, int *acertos, ALLEGRO_FONT *font);
void flipBack(ALLEGRO_BITMAP **sprites, int **frames, int **matriz, int linha1, int coluna1, int linha2, int coluna2, ALLEGRO_EVENT_QUEUE **timerQueue, ALLEGRO_EVENT *event, int *larguraSprite, int *alturaSprite, int *erros, int *acertos, ALLEGRO_FONT *font);
int** alocarMatriz();
void preencheMatriz();
void desaloca(int **matriz, int i);

#endif
