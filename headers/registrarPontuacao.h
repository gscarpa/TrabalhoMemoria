#ifndef REGISTRARPONTUACAO_H
#define REGISTRARPONTUACAO_H

int registrarPontuacao(int erros, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_FONT *font);
int inserirNome(ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_FONT *font, int *i, char *nome, char *idade);
int inserirIdade(ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_FONT *font, int *j, char *nome, char *idade);

#endif