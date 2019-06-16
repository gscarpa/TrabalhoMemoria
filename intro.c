#include "headers/intro.h"
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

int intro(){
    ALLEGRO_BITMAP **logo = malloc(sizeof(ALLEGRO_BITMAP*));
    if(logo==NULL)
        return -1;
    *logo = al_load_bitmap("images/logo.png");
    al_rest(3.0);
    for(float i=0; i<256; i+=0.7){
        al_flip_display();
        al_clear_to_color(al_map_rgb(i,i,i));
        al_draw_bitmap(*logo, 300, 225, 0);
    }
    al_rest(0.5);
    for(float i=255; i>=0; i-=1){
        al_flip_display();
        al_clear_to_color(al_map_rgb(i,i,i));
        al_draw_bitmap(*logo, 300, 225, 0);
    }
    al_destroy_bitmap(*logo);
    free(logo);
    return 1;
}

/*
    y
    0
x0      n
    
    n

y=j
x=i

    */