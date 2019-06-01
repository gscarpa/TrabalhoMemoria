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

int main(int argc, char *argv[]){
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_AUDIO_STREAM *musicaMenu = NULL;
    ALLEGRO_SAMPLE *score = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_BITMAP **vetorDeSprites;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT_QUEUE *timerQueue;


    if(!inicializar(&janela, &timer, &font, &eventQueue, &musicaMenu, &score, &timerQueue)){
        fprintf(stderr, "Falha ao inicializar a Allegro 5\n");
        return -1;
    }
    vetorDeSprites = alocarSprites();
    carregarSprites(vetorDeSprites);
    

    /*if(!intro()){
        fprintf(stderr, "Falha na inicialização da logo.\n");
        finalizar(&janela,&font,&eventQueue, &musicaMenu);
        return -1;
    }*/

    int option=1; 
    al_attach_audio_stream_to_mixer(musicaMenu, al_get_default_mixer());
    al_set_audio_stream_playmode(musicaMenu, ALLEGRO_PLAYMODE_LOOP);

    while(option!=0){
        if(option==1){
            option=telaInicial(font, &eventQueue, &event);
            if(option==-1){
                fprintf(stderr, "Falha ao criar o menu inicial.\n");
                //finalizar(&janela,&font,&eventQueue,&musicaMenu);
                return -1;
            }
        }else if(option==2){
            option=telaJogo(vetorDeSprites, font, &eventQueue, &event, &score, &timerQueue);
            if(option==-1){
                fprintf(stderr, "Falha ao criar tela de jogo.\n");
                //finalizar(&janela,&font,&eventQueue, &musicaMenu);
                return -1;
            }
        }   
    }
    
    //finalizar(&janela,&font,&eventQueue, &musicaMenu);

    return 0;
}
