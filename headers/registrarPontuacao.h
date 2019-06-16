#ifndef REGISTRARPONTUACAO_H
#define REGISTRARPONTUACAO_H

int registrarPontuacao(ALLEGRO_BITMAP **sprites, int erros, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_FONT *font);
int inserirNome(ALLEGRO_BITMAP **sprites, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_FONT *font, int *i, char *nome, char *idade, int pontuacao);
int inserirIdade(ALLEGRO_BITMAP **sprites, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_FONT *font, int *j, char *nome, char *idade, int pontuacao);

#endif