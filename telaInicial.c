#include "headers/telaInicial.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>

int telaInicial(ALLEGRO_BITMAP **sprites, ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event){
    
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap(sprites[19], 0, 0, 0);
    al_draw_bitmap(sprites[20], 320, 395, 0);
    al_draw_textf(font, al_map_rgb(255,255,255), 400, 409, ALLEGRO_ALIGN_CENTRE, "Iniciar");
    al_draw_textf(font, al_map_rgb(255,255,255), 400, 459, ALLEGRO_ALIGN_CENTRE, "Histórico");
    al_draw_textf(font, al_map_rgb(255,255,255), 400, 509, ALLEGRO_ALIGN_CENTRE, "Sair");
    
    int option=1;      //1=iniciar 2=scores 3=sair

    while(option!=0){
        
        al_clear_to_color(al_map_rgb(255,255,255));
        al_draw_bitmap(sprites[19], 0, 0, 0);

        if(option==1){
            al_draw_bitmap(sprites[19], 0, 0, 0);
            al_draw_bitmap(sprites[20], 320, 395, 0);
        }
        if(option==2){
            al_draw_bitmap(sprites[19], 0, 0, 0);
            al_draw_bitmap(sprites[20], 300, 395+((option-1)*50), 0);
        }   
        if(option==3){
            al_draw_bitmap(sprites[19], 0, 0, 0);
            al_draw_bitmap(sprites[20], 335, 395+((option-1)*50), 0);
        }

        al_draw_textf(font, al_map_rgb(255,255,255), 400, 409, ALLEGRO_ALIGN_CENTRE, "Iniciar");
        al_draw_textf(font, al_map_rgb(255,255,255), 400, 459, ALLEGRO_ALIGN_CENTRE, "Histórico");
        al_draw_textf(font, al_map_rgb(255,255,255), 400, 509, ALLEGRO_ALIGN_CENTRE, "Sair");

        al_flip_display();
        al_flush_event_queue(*eventQueue);
        al_wait_for_event(*eventQueue, event);
        
        if(event->type == ALLEGRO_EVENT_MOUSE_AXES){
            if(event->mouse.x>355 && event->mouse.x<449 && event->mouse.y>405 && event->mouse.y<440)
                option = 1;
            else if(event->mouse.x>335 && event->mouse.x<463 && event->mouse.y>455 && event->mouse.y<490)
                option = 2;
            else if(event->mouse.x>367 && event->mouse.x<429 && event->mouse.y>505 && event->mouse.y<540)
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
            if(event->mouse.x>355 && event->mouse.x<449 && event->mouse.y>405 && event->mouse.y<440)
                return 2;
            if(event->mouse.x>335 && event->mouse.x<463 && event->mouse.y>455 && event->mouse.y<490)
                return 3;
            if(event->mouse.x>367 && event->mouse.x<429 && event->mouse.y>505 && event->mouse.y<540)
                return 0;
        }else if(event->type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            option=0;
    }

    return option;
}
