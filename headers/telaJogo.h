#ifndef TELAJOGO_H
#define TELAJOGO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>

int telaJogo(/*ALLEGRO_BITMAP **bitmapArray, */ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_SAMPLE **score);
int** alocarMatriz();
void desaloca(int **matriz, int i);

#endif
