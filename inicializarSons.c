#include "headers/inicializarSons.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

int inicializarSons(ALLEGRO_AUDIO_STREAM **musicaMenu/*Outros sons a serem adicionados depois*/){
    if(al_reserve_samples(5)){
        fprintf(stderr, "Falha a reservar amostras de áudio");
        return 0;
    }
    *musicaMenu = alLoad_audio_stream("audios/menu.ogg", 4, 2014);
    if(!*musicaMenu){
        fprintf(stderr, "Falha ao carregar musica de menu");
        al_destroy_audio_stream(*musicaMenu);
        return 1;    
    }
    al_attach_audio_stream_to_mixer(*musicaMenu, al_get_default_mixer());
    al_set_audio_stream_playmode(*musicaMenu, ALLEGRO_PLAYMODE_LOOP);

    return 1;
}
