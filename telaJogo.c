#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "headers/telaJogo.h"
#include "headers/telaInicial.h"
#include "headers/inicializarFinalizar.h"

int telaJogo(ALLEGRO_BITMAP **sprites, ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_SAMPLE **score, ALLEGRO_EVENT_QUEUE **timerQueue, int *erros, ALLEGRO_SAMPLE **error){
    srand(time(NULL));
    int **matriz=alocarMatriz(); //Matriz que contém o número de cada carta
    preencheMatriz(matriz);
    int **frames=alocarMatriz(); //Matriz que contém o frame atual de cada sprite
    if(matriz==NULL){
        fprintf(stderr, "Erro ao alocar matriz.\n");
        return -1;
    }


    //ALLEGRO_BITMAP **vetorDeSprite;



    int acertos=0;
    *erros=0;
    int alturaSprite=91, larguraSprite=80;
    int cardsPosIJ[4]={-1,-1,-1,-1};

    updateGameScreen(sprites, frames, matriz, &larguraSprite, &alturaSprite, erros, &acertos, font);

    while(acertos<18){
        al_flush_event_queue(*eventQueue);
        al_wait_for_event(*eventQueue, event);
        if(event->type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            int coluna=event->mouse.x, linha=event->mouse.y; //[y][x]
//            printf("linha %d coluna%d", linha, coluna);
            if(linha>27 && linha<566 && coluna>27 && coluna<500){
                coluna-=27;
                coluna/=80;
                linha-=27;
                linha/=91;
                if(frames[linha][coluna]<9){
                    if(cardsPosIJ[0]<0){
                        cardsPosIJ[0]=linha;
                        cardsPosIJ[1]=coluna;
                        flipCard(sprites, frames, matriz, linha, coluna, timerQueue, event, &larguraSprite, &alturaSprite, erros, &acertos, font);
                    }else{
                        cardsPosIJ[2]=linha;
                        cardsPosIJ[3]=coluna;
                        flipCard(sprites, frames, matriz, linha, coluna, timerQueue, event, &larguraSprite, &alturaSprite, erros, &acertos, font);
                        if(matriz[(cardsPosIJ[0])][(cardsPosIJ[1])]==matriz[(cardsPosIJ[2])][(cardsPosIJ[3])]){
                            acertos++;
                            al_play_sample(*score, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                            updateGameScreen(sprites, frames, matriz, &larguraSprite, &alturaSprite, erros, &acertos, font);
                        }else{
                            *erros+=1;
                            al_play_sample(*error, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                            al_rest(1.0);
                            flipBack(sprites, frames, matriz, cardsPosIJ[0], cardsPosIJ[1], cardsPosIJ[2], cardsPosIJ[3], timerQueue, event, &larguraSprite, &alturaSprite, erros, &acertos, font);
                        }
                        cardsPosIJ[0]=-1;
                    }
                }
            }else if(coluna>560 && coluna<612 && linha>539 && linha<564){
                desaloca(matriz, 5);
                desaloca(frames, 5);
                return 0;
            }else if(coluna>560 && coluna<768 && linha>500 && linha<534){
                desaloca(matriz, 5);
                desaloca(frames, 5);
                return 1;
            }
        }else if(event->type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            desaloca(matriz, 5);
            desaloca(frames, 5);
            return 0;
        }
    }
    if(acertos==18){
        al_draw_textf(font, al_map_rgb(255,0,255), 400, 250, ALLEGRO_ALIGN_CENTER, "PARABENS VOCÊ COMPLETOU O JOGO");
        al_flip_display();
        al_rest(3.0);
    }


    desaloca(matriz, 5);
    desaloca(frames, 5);

    return 4;
}

void updateGameScreen(ALLEGRO_BITMAP **sprites, int **frames, int **matriz, int *larguraSprite, int *alturaSprite, int *erros, int *acertos, ALLEGRO_FONT *font){
    al_draw_bitmap(sprites[18], 0, 0, 1);
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            al_draw_bitmap_region(sprites[(matriz[i][j]-1)],*larguraSprite*frames[i][j],0,*larguraSprite,*alturaSprite,27+j*(*larguraSprite), 27+i*(*alturaSprite),0);
        }
    }
    al_draw_textf(font, al_map_rgb(255,255,255), 560, 40, ALLEGRO_ALIGN_LEFT, "Tentativas: %d", *erros+*acertos);
    al_draw_textf(font, al_map_rgb(255,255,255), 560, 90, ALLEGRO_ALIGN_LEFT, "Erros: %d", *erros);
    al_draw_textf(font, al_map_rgb(255,255,255), 560, 140, ALLEGRO_ALIGN_LEFT, "Acertos: %d", *acertos);
    al_draw_textf(font, al_map_rgb(255,255,255), 560, 540, ALLEGRO_ALIGN_LEFT, "Sair");
    al_draw_textf(font, al_map_rgb(255,255,255), 560, 500, ALLEGRO_ALIGN_LEFT, "Voltar ao Menu");
    al_flip_display();
}

void flipCard(ALLEGRO_BITMAP **sprites, int **frames, int **matriz, int linha, int coluna, ALLEGRO_EVENT_QUEUE **timerQueue, ALLEGRO_EVENT *event, int *larguraSprite, int *alturaSprite, int *erros, int *acertos, ALLEGRO_FONT *font){
    al_flush_event_queue(*timerQueue);
    while(frames[linha][coluna]<9){
        frames[linha][coluna]++;
        al_wait_for_event(*timerQueue, event);
        if(event->type==ALLEGRO_EVENT_TIMER){
            al_draw_bitmap(sprites[18], 0, 0, 1);
            for(int i=0; i<6; i++){ //i=linha
                for(int j=0; j<6; j++){ //j=coluna
                    al_draw_bitmap_region(sprites[(matriz[i][j]-1)],*larguraSprite*frames[i][j],0,*larguraSprite,*alturaSprite,27+j*(*larguraSprite), 27+i*(*alturaSprite),0);
                }
            }
            al_draw_textf(font, al_map_rgb(255,255,255), 560, 40, ALLEGRO_ALIGN_LEFT, "Tentativas: %d", *erros+*acertos);
            al_draw_textf(font, al_map_rgb(255,255,255), 560, 90, ALLEGRO_ALIGN_LEFT, "Erros: %d", *erros);
            al_draw_textf(font, al_map_rgb(255,255,255), 560, 140, ALLEGRO_ALIGN_LEFT, "Acertos: %d", *acertos);
            al_draw_textf(font, al_map_rgb(255,255,255), 560, 540, ALLEGRO_ALIGN_LEFT, "Sair");
            al_draw_textf(font, al_map_rgb(255,255,255), 560, 500, ALLEGRO_ALIGN_LEFT, "Voltar ao Menu");
            al_flip_display();
        }
    }
}

void flipBack(ALLEGRO_BITMAP **sprites, int **frames, int **matriz, int linha1, int coluna1, int linha2, int coluna2, ALLEGRO_EVENT_QUEUE **timerQueue, ALLEGRO_EVENT *event, int *larguraSprite, int *alturaSprite, int *erros, int *acertos, ALLEGRO_FONT *font){
    al_flush_event_queue(*timerQueue);
    while(frames[linha1][coluna1]>0){
        frames[linha1][coluna1]--;
        frames[linha2][coluna2]--;
        al_wait_for_event(*timerQueue, event);
        if(event->type==ALLEGRO_EVENT_TIMER){
            al_draw_bitmap(sprites[18], 0, 0, 1);
            for(int i=0; i<6; i++){ //i=linha
                for(int j=0; j<6; j++){ //j=coluna
                    al_draw_bitmap_region(sprites[(matriz[i][j]-1)],*larguraSprite*frames[i][j],0,*larguraSprite,*alturaSprite,27+j*(*larguraSprite), 27+i*(*alturaSprite),0);
                }
            }
            al_draw_textf(font, al_map_rgb(255,255,255), 560, 40, ALLEGRO_ALIGN_LEFT, "Tentativas: %d", *erros+*acertos);
            al_draw_textf(font, al_map_rgb(255,255,255), 560, 90, ALLEGRO_ALIGN_LEFT, "Erros: %d", *erros);
            al_draw_textf(font, al_map_rgb(255,255,255), 560, 140, ALLEGRO_ALIGN_LEFT, "Acertos: %d", *acertos);
            al_draw_textf(font, al_map_rgb(255,255,255), 560, 540, ALLEGRO_ALIGN_LEFT, "Sair");
            al_draw_textf(font, al_map_rgb(255,255,255), 560, 500, ALLEGRO_ALIGN_LEFT, "Voltar ao Menu");
            al_flip_display();
        }
    }

}

int** alocarMatriz(){
    int **matriz=malloc(6*sizeof(int*));
    if(matriz==NULL){
        fprintf(stderr, "Erro ao alocar grade de cartas.\n");
        return NULL;
    }
    for(int i=0; i<6; i++){
        matriz[i]=calloc(6,sizeof(int));
        if(matriz[i]==NULL){
            fprintf(stderr, "Erro ao alocar grade de cartas.\n");
            desaloca(matriz, i);
            return NULL;
        }
    }
    return matriz;
}

void preencheMatriz(int **matriz){
    int card=1;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            if(card==19)
                card=1;
            matriz[i][j]=card;
            card++;
        }
    }
    int temp;
    for(int i=0; i<36; i++){
        int c1x=rand()%6, c1y=rand()%6, c2x=rand()%6, c2y=rand()%6;
        temp=matriz[c1x][c1y];
        matriz[c1x][c1y]=matriz[c2x][c2y];
        matriz[c2x][c2y]=temp;
    }
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            printf("[%d]", matriz[i][j]);
        }
        printf("\n");
    }
}

void desaloca(int **matriz, int i){
    while(i>0){
        free(matriz[i]);
        i--;
    }
    free(matriz);
}