#include "headers/telaInicial.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>

int telaInicial(/*ALLEGRO_KEYBOARD_STATE *keyState, */ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event){
    //ALLEGRO_BITMAP *backgroundInicial = NULL;
    ALLEGRO_BITMAP **bitmapArray = malloc(sizeof(ALLEGRO_BITMAP*));
    bitmapArray[0] = NULL;
    //ALLEGRO_BITMAP *optionButton = NULL;
    bitmapArray[0] = al_load_bitmap("images/button.png");
    /*if(!optionButton){
        fprintf(stderr, "Falha ao carregar imagem.\n");
        return 0;
    }*/
    
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap(bitmapArray[0], 50, 50, 0);
    al_draw_textf(font, al_map_rgb(0,0,0), 80, 59, ALLEGRO_ALIGN_LEFT, "Iniciar");
    al_draw_textf(font, al_map_rgb(0,0,0), 80, 109, ALLEGRO_ALIGN_LEFT, "Histórico");
    al_draw_textf(font, al_map_rgb(0,0,0), 80, 159, ALLEGRO_ALIGN_LEFT, "Sair");

    int option=1;      //1=iniciar 2=scores 3=sair

    while(option!=0){
        
        //al_get_keyboard_state(keyState);
        al_clear_to_color(al_map_rgb(255,255,255));
        al_draw_bitmap(bitmapArray[0], 50, 50*option, 0);

        al_draw_textf(font, al_map_rgb(0,0,0), 80, 59, ALLEGRO_ALIGN_LEFT, "Iniciar");
        al_draw_textf(font, al_map_rgb(0,0,0), 80, 109, ALLEGRO_ALIGN_LEFT, "Histórico");
        al_draw_textf(font, al_map_rgb(0,0,0), 80, 159, ALLEGRO_ALIGN_LEFT, "Sair");
        al_flip_display();
        al_flush_event_queue(*eventQueue);
        al_wait_for_event(*eventQueue, event);
        
        if(event->type == ALLEGRO_EVENT_MOUSE_AXES){
            if(event->mouse.x>81 && event->mouse.x<165 && event->mouse.y>60 && event->mouse.y<85)
                option = 1;
            else if(event->mouse.x>81 && event->mouse.x<199 && event->mouse.y>109 && event->mouse.y<133)
                option = 2;
            else if(event->mouse.x>81 && event->mouse.x<132 && event->mouse.y>158 && event->mouse.y<183)
                option = 3;
        }else if(event->type == ALLEGRO_EVENT_KEY_DOWN){
            if(event->keyboard.keycode == ALLEGRO_KEY_DOWN && option<3)
                option++;
            else if(event->keyboard.keycode == ALLEGRO_KEY_UP && option>1)
                option--;
            else if(event->keyboard.keycode == ALLEGRO_KEY_ENTER){
                if(option==1)
                    return 2;
                if(option==2)
                    return 3;
                return 0;    
            }
        }else if(event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(event->mouse.x>81 && event->mouse.x<165 && event->mouse.y>60 && event->mouse.y<85)
                return 2;
            if(event->mouse.x>81 && event->mouse.x<199 && event->mouse.y>109 && event->mouse.y<133)
                return 3;
            if(event->mouse.x>81 && event->mouse.x<132 && event->mouse.y>158 && event->mouse.y<183)
                return 0;
        }else if(event->type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            option=0;
    }
    free(bitmapArray);
    return option;
}
