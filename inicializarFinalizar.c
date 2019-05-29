#include "headers/inicializarFinalizar.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

int inicializar(ALLEGRO_DISPLAY **janela, ALLEGRO_FONT **font, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_AUDIO_STREAM **musicaMenu, ALLEGRO_SAMPLE **score){
    //inicia o allegro e verifica o sucesso
    if(!al_init()){
        fprintf(stderr, "Falha ao iniciar allegro.\n");
        return 0;
    }
    //instala o teclado e verifica o sucesso
    if(!al_install_keyboard()){
        fprintf(stderr, "Falha ao iniciar teclado.\n");
        return 0;
    }
    //instala o mouse e verifica o sucesso
    if(!al_install_mouse()){
        fprintf(stderr, "Falha ao iniciar mouse.\n");
        al_uninstall_keyboard();
        return 0;
    }
    //inicia biblioteca de imagens e verifica o sucesso
    if(!al_init_image_addon()){
        fprintf(stderr, "Falha ao iniciar biblioteca de imagens.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        return 0;
    }
    //inicia biblioteca de fontes e verifica o sucesso
    if(!al_init_font_addon()){        
        fprintf(stderr, "Falha ao iniciar biblioteca de fontes.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        return 0;
    }
    //inicia biblioteca de ttf e verifica o sucesso
    if(!al_init_ttf_addon()){
        fprintf(stderr, "Falha ao iniciar biblioteca ttf.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        return 0;
    }
    //instala audio do sistema e verifica o sucesso 
    if(!al_install_audio()){
        fprintf(stderr, "Falha ao installar audio.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        return 0;
    }
    //inicia biblioteca de audio e verifica o sucesso
    if(!al_init_acodec_addon()){
        fprintf(stderr, "Falha ao iniciar biblioteca de codecs de som.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        return 0;
    }
    //carrega fonte arial da pasta fonts
    *font = al_load_font("fonts/arial.ttf", 30, 0);
    //verifica se a fonte foi caregada com sucesso
    if(!*font){
        fprintf(stderr, "Falha ao carregar fonte.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        return -1;
    }
    //cria fila de eventos recebida pela função via endereço
    *eventQueue = al_create_event_queue();
    //verifica se a filha de eventos foi criada com sucesso
    if(!*eventQueue){
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        return -1;
    }
    //cria janela de tamanho 800x600
    *janela = al_create_display(800,600);
    //registra eventos de janela,teclado e mouse na fila de eventos
    al_register_event_source(*eventQueue, al_get_display_event_source(*janela));
    al_register_event_source(*eventQueue, al_get_keyboard_event_source());
    al_register_event_source(*eventQueue, al_get_mouse_event_source());
    //verifica se a janela foi criada com sucesso
    if(!janela){
        fprintf(stderr, "Falha ao criar a janela.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        al_destroy_event_queue(*eventQueue);
        return -1;
    }
    //reserva amostra de sons e verifica sucesso
    if(!al_reserve_samples(5)){
        fprintf(stderr, "Falha ao reservar amostras de som.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        al_destroy_event_queue(*eventQueue);
        al_destroy_display(*janela);
        return -1;
    }
    //adiciona música de menu aos fluxo de áudio(não sei bem como traduzir isso)
    *musicaMenu=al_load_audio_stream("audios/menu.ogg", 4, 1024);
    //verifica se a música foi adicionada com sucesso
    if(!*musicaMenu){
        fprintf(stderr, "Falha ao carregar música do menu.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        al_destroy_event_queue(*eventQueue);
        al_destroy_display(*janela);
        al_destroy_mixer(al_get_default_mixer());
        al_destroy_audio_stream(*musicaMenu);
        return -1;
    }
    *score=al_load_sample("audios/score.ogg");
    if(!*score){
        fprintf(stderr, "Falha ao carregar som de pontuação.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        al_destroy_event_queue(*eventQueue);
        al_destroy_display(*janela);
        al_destroy_mixer(al_get_default_mixer());
        al_destroy_audio_stream(*musicaMenu);
        al_destroy_sample(*score);
    }
    //adiciona a música de menu ao mixer padrão
    //al_attach_audio_stream_to_mixer(*musicaMenu, al_get_default_mixer());
    //al_set_audio_stream_playmode(*musicaMenu, ALLEGRO_PLAYMODE_LOOP);


    return 1;
}   

void finalizar(ALLEGRO_DISPLAY **janela, ALLEGRO_FONT **font, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_AUDIO_STREAM **musicaMenu){
    //desinstala e desaloca os itens inicializados pelo programada
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_uninstall_audio();
    al_destroy_font(*font);
    al_destroy_event_queue(*eventQueue);
    al_destroy_display(*janela);
    al_destroy_mixer(al_get_default_mixer());
    al_destroy_audio_stream(*musicaMenu);
}