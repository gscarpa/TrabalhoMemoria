#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "headers/inicializarFinalizar.h"
#include "headers/intro.h"
#include "headers/telaInicial.h"
#include "headers/telaJogo.h"
#include "headers/registrarPontuacao.h"

int main(int argc, char *argv[]){
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_AUDIO_STREAM *musicaMenu = NULL;
    ALLEGRO_SAMPLE *score = NULL;
    ALLEGRO_SAMPLE *error = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_BITMAP **vetorDeSprites;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT_QUEUE *timerQueue;
    int erros=0;


    if(!inicializar(&janela, &timer, &font, &eventQueue, &musicaMenu, &score, &timerQueue, &vetorDeSprites, &error)){
        printf("Falha ao inicializar a Allegro 5\n");
        return -1;
    }

    /*if(!intro()){
        printf("Falha na inicialização da logo.\n");
        finalizar(&janela, &font, &eventQueue, &musicaMenu, &timerQueue, &vetorDeSprites);
        return -1;
    }*/

    int option=1; 
    al_attach_audio_stream_to_mixer(musicaMenu, al_get_default_mixer());
    al_set_audio_stream_playmode(musicaMenu, ALLEGRO_PLAYMODE_LOOP);

    while(option!=0){
        if(option==1){
            option=telaInicial(font, &eventQueue, &event);
            if(option==-1){
                printf("Falha ao criar o menu inicial.\n");
                finalizar(&janela, &font, &eventQueue, &musicaMenu, &timerQueue, vetorDeSprites);
                return -1;
            }
        }else if(option==2){
            option=telaJogo(vetorDeSprites, font, &eventQueue, &event, &score, &timerQueue, &erros, &error);
            if(option==-1){
                printf("Falha ao criar tela de jogo.\n");
                finalizar(&janela, &font, &eventQueue, &musicaMenu, &timerQueue, vetorDeSprites);
                return -1;
            }
        }/*else if(option==3){
            if(!telaHistorico()){
                printf("Falha ao abrir histórico de pontuações");
                finalizar(&janela, &font, &eventQueue, &musicaMenu, &timerQueue, &vetorDeSprites, &score, &error);
                return -1;
            }
            option=1;
        }*/else if(option==4){
            if(!registrarPontuacao(erros, &eventQueue, &event, font)){
                printf("Falha ao registrar a pontuação do jogador");
                finalizar(&janela, &font, &eventQueue, &musicaMenu, &timerQueue, vetorDeSprites);
                return -1;
            }
        }
    }
    
    finalizar(&janela, &font, &eventQueue, &musicaMenu, &timerQueue, vetorDeSprites);

    return 0;
}
