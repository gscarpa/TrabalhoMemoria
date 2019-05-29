#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include "headers/telaJogo.h"
#include <allegro5/allegro_primitives.h>

int telaJogo(/*ALLEGRO_BITMAP **bitmapArray,*/ ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_SAMPLE **score){
    srand(time(NULL));
    int **matriz=alocarMatriz();
    if(matriz==NULL){
        fprintf(stderr, "Erro ao alocar matriz.\n");
        return -1;
    }
    al_init_primitives_addon(); //Isso está aqui apenas para desenhar os quadrados. Remover ao substitui-los por sprites.

    int sair=1;
    int carta1=0, carta2=0, erros=0, acertos=0;

    al_clear_to_color(al_map_rgb(255,255,255));
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            al_draw_rectangle(100+i*80, 100+j*80, 120+i*80+75, 120+j*80+75, al_map_rgb(0,0,0), 2);
            al_draw_textf(font, al_map_rgb(0,0,0), 100+i*80, 100+j*80, ALLEGRO_ALIGN_CENTER, "%d",matriz[i][j]);
        }
    }
    al_draw_textf(font, al_map_rgb(0,0,0), 600, 100, ALLEGRO_ALIGN_LEFT, "Erros: %d",erros);
    al_draw_textf(font, al_map_rgb(0,0,0), 600, 150, ALLEGRO_ALIGN_LEFT, "Acertos: %d",acertos);
        
    int x1=-1, y1=-1, x2=-1, y2=-1;

    while(sair>0){
        
        al_flip_display();
        al_clear_to_color(al_map_rgb(255,255,255));
        for(int i=0; i<6; i++){
            for(int j=0; j<6; j++){
                al_draw_rectangle(100+i*80, 100+j*80, 100+i*80+75, 100+j*80+75, al_map_rgb(0,0,0),2);
                al_draw_textf(font, al_map_rgb(0,0,0), 120+i*80, 120+j*80, ALLEGRO_ALIGN_CENTER, "%d",matriz[i][j]);
            }
        }
        al_draw_textf(font, al_map_rgb(0,0,0), 600, 100, ALLEGRO_ALIGN_LEFT, "Erros: %d",erros);
        al_draw_textf(font, al_map_rgb(0,0,0), 600, 150, ALLEGRO_ALIGN_LEFT, "Acertos: %d",acertos);
        al_draw_textf(font, al_map_rgb(0,0,0), 600, 200, ALLEGRO_ALIGN_LEFT, "Reiniciar");
        al_draw_textf(font, al_map_rgb(0,0,0), 600, 250, ALLEGRO_ALIGN_LEFT, "Sair");

        al_wait_for_event(*eventQueue, event);

        if(event->type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            int x=event->mouse.x, y=event->mouse.y;
            printf("%d, %d\n", x, y);
            if(x>100 && x<580 && y>100 && y<580){
                x-=100;
                y-=100;
                if(x1<0 && y1<0){
                    x1=x/80;
                    y1=y/80;
                }else{
                    x2=x/80;
                    y2=y/80;
                //}
                    if(x1==x2 && y1==y2){
                        x2=-1;
                        y2=-1;
                    }else{printf("x1:%d, y1:%d, x2:%d, y2:%d\n",x1, y1, x2, y2 );
                        carta1=matriz[x1][y1];
                        carta2=matriz[x2][y2];
                        if(carta1==carta2){
                            acertos++;
                            al_play_sample(*score, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                        }else{
                            erros++;
                        }
                        carta1=0;
                        carta2=0;
                        x1=-1;
                        y1=-1;
                        x2=-1;
                        y2=-2;
                    }
                }
            }
        }
        if(event->type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            desaloca(matriz, 5);
            return 0;
        }
        if(event->keyboard.keycode == ALLEGRO_KEY_ESCAPE){
            desaloca(matriz, 5);
            return 0;
        }
        
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
    return matriz;
}

void desaloca(int **matriz, int i){
    while(i>0){
        free(matriz[i]);
        i--;
    }
    free(matriz);
}
