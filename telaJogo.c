#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include "headers/telaJogo.h"
#include <allegro5/allegro_primitives.h>

int telaJogo(ALLEGRO_BITMAP **sprites, ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_SAMPLE **score){
    srand(time(NULL));
    int **matriz=alocarMatriz(); //Matriz que contém o número de cada carta
    preencheMatriz(matriz);
    int **frames=alocarMatriz(); //Matriz que contém o frame atual de cada sprite
    if(matriz==NULL){
        fprintf(stderr, "Erro ao alocar matriz.\n");
        return -1;
    }
    //al_init_primitives_addon(); //Isso está aqui apenas para desenhar os quadrados. Remover ao substitui-los por sprites.

    int sair=1;
    int carta1=0, carta2=0, erros=0, acertos=0;
    int alturaSprite=91, larguraSprite=80;
    int card1x=-1, card1y=-1, card2x=-1, card2y=-1, errou=0, confere=0;
    al_clear_to_color(al_map_rgb(255,255,255));
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            al_draw_bitmap_region(sprites[(matriz[i][j]-1)],larguraSprite*frames[i][j],0,larguraSprite,alturaSprite,20+i*larguraSprite, 20+j*alturaSprite,0);
            //al_draw_rectangle(20+i*80, 20+j*91, 20+i*80+80, 20+j*91+91, al_map_rgb(0,0,0), 2);
            //al_draw_textf(font, al_map_rgb(0,0,0), 100+i*80, 100+j*80, ALLEGRO_ALIGN_CENTER, "%d",matriz[i][j]);
        }
    }
    al_draw_textf(font, al_map_rgb(0,0,0), 600, 100, ALLEGRO_ALIGN_LEFT, "Erros: %d",erros);
    al_draw_textf(font, al_map_rgb(0,0,0), 600, 150, ALLEGRO_ALIGN_LEFT, "Acertos: %d",acertos);

    while(sair>0){
        al_flip_display();
        al_clear_to_color(al_map_rgb(255,255,255));
        for(int i=0; i<6; i++){
            for(int j=0; j<6; j++){
                al_draw_bitmap_region(sprites[(matriz[i][j]-1)],larguraSprite*frames[i][j],0,larguraSprite,alturaSprite,20+i*larguraSprite, 20+j*alturaSprite,0);
            }
        }
        al_draw_textf(font, al_map_rgb(0,0,0), 600, 100, ALLEGRO_ALIGN_LEFT, "Erros: %d",erros);
        al_draw_textf(font, al_map_rgb(0,0,0), 600, 150, ALLEGRO_ALIGN_LEFT, "Acertos: %d",acertos);
        al_draw_textf(font, al_map_rgb(0,0,0), 600, 200, ALLEGRO_ALIGN_LEFT, "Reiniciar");
        al_draw_textf(font, al_map_rgb(0,0,0), 600, 250, ALLEGRO_ALIGN_LEFT, "Sair");

        if(confere==1){
            printf("card1= %d card2= %d\n", carta1, carta2);
            if(carta1==carta2){
                acertos++;
                card1x=-1;
                card2x=-1;
                al_play_sample(*score, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            }else if(errou==0){
                errou=1;
                erros++;
                al_rest(0.5);
            }
            confere=0;
        }
        al_wait_for_event(*eventQueue, event);
        if(event->type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            int j=event->mouse.x, i=event->mouse.y;
            //printf("%d, %d\n", x, y);
            if(i>20 && i<566 && j>20 && j<500){
                j-=20;
                j/=80;
                i-=20;
                i/=91;
                if(card1x<0){
                    card1x=i;
                    card1y=j; printf("card1 matriz[%d][%d]\n", card1x, card1y);
                }else{
                    card2x=i;
                    card2y=j;
                    carta1=matriz[card1x][card1y];
                    if(card1x==card2x && card1y==card2y){
                        card2x=-1;
                    }else{//printf("x1:%d, y1:%d, x2:%d, y2:%d\n",x1, y1, x2, y2 );
                        printf("card2 matriz[%d][%d]\n", card2x, card2y);
                        carta2=matriz[card2x][card2y];
                        /*
                        carta1=0;
                        carta2=0;
                        card1x=-1;
                        card2x=-1;*/
                    }
                }
            }
        }else if(event->type==ALLEGRO_EVENT_TIMER){
            if(errou==1){
                frames[card1y][card1x]--;
                frames[card2y][card2x]--;
                if(frames[card2y][card2x]==0){
                    card1x=-1;
                    card2x=-1;
                    errou=0;
                }
            }else if(confere==0){
                if(card1x>=0){
                    if(frames[card1y][card1x]<9){
                        frames[card1y][card1x]++;
                    }else if(card2x>=0){
                        if(frames[card2y][card2x]<9){
                            frames[card2y][card2x]++;
                        }else{
                            confere=1;
                        }
                    }
                }
            }
        }

        /*if(event->type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            desaloca(matriz, 5);
            return 0;
        }
        if(event->keyboard.keycode == ALLEGRO_KEY_ESCAPE){
            desaloca(matriz, 5);
            return 0;

        if(event->type==ALLEGRO_EVENT_TIMER && card1x>0 && frames[card1x][card1y]<9){
            frames[card1x][card1y]++;
        }else if(event->type==ALLEGRO_EVENT_TIMER && card2x>0 && frames[card2x][card2y]<9){
            frames[card2x][card2y]++;
        }
        }*/
        
    }

    desaloca(matriz, 5);

    return 1;
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
    for(int i=1; i<19; i++){
        int j=0;
        while(j<2){
            int linha, coluna;
            linha=rand()%6;
            coluna=rand()%6;
            if(matriz[linha][coluna]==0){
                matriz[linha][coluna]=i;
                j++;
            }
        }
    }
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            fprintf(stderr, "[%d]", matriz[i][j]);
        }
        fprintf(stderr, "\n");
    }
}

void desaloca(int **matriz, int i){
    while(i>0){
        free(matriz[i]);
        i--;
    }
    free(matriz);
}
