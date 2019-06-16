#ifndef INICIALIZARFINALIZAR_H
#define INICIALIZARFINALIZAR_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

int inicializar(ALLEGRO_DISPLAY **janela,ALLEGRO_TIMER **timer, ALLEGRO_FONT **font, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_AUDIO_STREAM **musicaMenu, ALLEGRO_SAMPLE **score, ALLEGRO_EVENT_QUEUE **timerQueue, ALLEGRO_BITMAP ***vetorDeSprites, ALLEGRO_SAMPLE **error);
ALLEGRO_BITMAP** alocarSprites();
int carregarSprites(ALLEGRO_BITMAP **sprites);
void finalizar(ALLEGRO_DISPLAY **janela, ALLEGRO_FONT **font, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_AUDIO_STREAM **musicaMenu, ALLEGRO_EVENT_QUEUE **timerQueue, ALLEGRO_BITMAP **vetorDeSprites);

#endif
