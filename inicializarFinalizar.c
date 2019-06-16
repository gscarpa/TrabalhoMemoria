#include "headers/inicializarFinalizar.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

int inicializar(ALLEGRO_DISPLAY **janela, ALLEGRO_TIMER **timer, ALLEGRO_FONT **font, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_AUDIO_STREAM **musicaMenu, ALLEGRO_SAMPLE **score, ALLEGRO_EVENT_QUEUE **timerQueue, ALLEGRO_BITMAP ***vetorDeSprites, ALLEGRO_SAMPLE **error){
    //inicia o allegro e verifica o sucesso
    if(!al_init()){
        printf("Falha ao iniciar allegro.\n");
        return 0;
    }
    //instala o teclado e verifica o sucesso
    if(!al_install_keyboard()){
        printf("Falha ao iniciar teclado.\n");
        return 0;
    }
    //instala o mouse e verifica o sucesso
    if(!al_install_mouse()){
        printf("Falha ao iniciar mouse.\n");
        al_uninstall_keyboard();
        return 0;
    }
    //inicia biblioteca de imagens e verifica o sucesso
    if(!al_init_image_addon()){
        printf("Falha ao iniciar biblioteca de imagens.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        return 0;
    }
    //inicia biblioteca de fontes e verifica o sucesso
    if(!al_init_font_addon()){        
        printf("Falha ao iniciar biblioteca de fontes.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        return 0;
    }
    //inicia biblioteca de ttf e verifica o sucesso
    if(!al_init_ttf_addon()){
        printf("Falha ao iniciar biblioteca ttf.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        return 0;
    }
    //instala audio do sistema e verifica o sucesso 
    if(!al_install_audio()){
        printf("Falha ao installar audio.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        return 0;
    }
    //inicia biblioteca de audio e verifica o sucesso
    if(!al_init_acodec_addon()){
        printf("Falha ao iniciar biblioteca de codecs de som.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        return 0;
    }
    //carrega fonte arial da pasta fonts
    *font = al_load_font("fonts/BlueHighwayPixie.ttf", 30, 0);
    //verifica se a fonte foi caregada com sucesso
    if(!*font){
        printf("Falha ao carregar fonte.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        return -1;
    }
    //cria fila de eventos recebida pela função via endereço
    *eventQueue = al_create_event_queue();
    //verifica se a filha de eventos foi criada com sucesso
    if(!*eventQueue){
        printf("Falha ao criar fila de eventos.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        return -1;
    }
    *timerQueue = al_create_event_queue();
    if(!*timerQueue){
        printf("Falha ao criar fila de eventos para animação das cartas.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        al_destroy_event_queue(*eventQueue);
        return -1;
    }
    //cria janela de tamanho 800x600
    *janela = al_create_display(800,600);
    //verifica se a janela foi criada com sucesso
    if(!janela){
        printf("Falha ao criar a janela.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        al_destroy_event_queue(*eventQueue);
        al_destroy_event_queue(*timerQueue);
        return -1;
    }
    //reserva amostra de sons e verifica sucesso
    if(!al_reserve_samples(5)){
        printf("Falha ao reservar amostras de som.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        al_destroy_event_queue(*eventQueue);
        al_destroy_event_queue(*timerQueue);
        al_destroy_display(*janela);
        return -1;
    }
    //adiciona música de menu aos fluxo de áudio(não sei bem como traduzir isso)
    *musicaMenu=al_load_audio_stream("audios/menu.ogg", 4, 1024);
    //verifica se a música foi adicionada com sucesso
    if(!*musicaMenu){
        printf("Falha ao carregar música do menu.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        al_destroy_event_queue(*eventQueue);
        al_destroy_event_queue(*timerQueue);
        al_destroy_display(*janela);
        al_destroy_mixer(al_get_default_mixer());
        al_destroy_audio_stream(*musicaMenu);
        return -1;
    }
    *score=al_load_sample("audios/score.ogg");
    if(!*score){
        printf("Falha ao carregar som de pontuação.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        al_destroy_event_queue(*eventQueue);
        al_destroy_event_queue(*timerQueue);
        al_destroy_display(*janela);
        al_destroy_mixer(al_get_default_mixer());
        al_destroy_audio_stream(*musicaMenu);
        al_destroy_sample(*score);
        return -1;
    }
    *error=al_load_sample("audios/error.ogg");
    if(!*score){
        printf("Falha ao carregar som de pontuação.\n");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        al_destroy_event_queue(*eventQueue);
        al_destroy_event_queue(*timerQueue);
        al_destroy_display(*janela);
        al_destroy_mixer(al_get_default_mixer());
        al_destroy_audio_stream(*musicaMenu);
        al_destroy_sample(*score);
        al_destroy_sample(*error);
        return -1;
    }
    *timer = al_create_timer(1/30.0);
    if(!timer){
        printf("Falha ao criar temporizador");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        al_destroy_event_queue(*eventQueue);
        al_destroy_event_queue(*timerQueue);
        al_destroy_display(*janela);
        al_destroy_mixer(al_get_default_mixer());
        al_destroy_audio_stream(*musicaMenu);
        al_destroy_sample(*score);
        al_destroy_sample(*error);
        return -1;
    }
    //adiciona a música de menu ao mixer padrão
    //al_attach_audio_stream_to_mixer(*musicaMenu, al_get_default_mixer());
    //al_set_audio_stream_playmode(*musicaMenu, ALLEGRO_PLAYMODE_LOOP);
    //registra eventos de janela,teclado, mouse e timer na fila de eventos
    al_register_event_source(*eventQueue, al_get_display_event_source(*janela));
    al_register_event_source(*eventQueue, al_get_keyboard_event_source());
    al_register_event_source(*eventQueue, al_get_mouse_event_source());
    al_register_event_source(*timerQueue, al_get_timer_event_source(*timer));

    //inicia o timer
    al_start_timer(*timer);
    //aloca vetor para sprites e backgrounds e cofere sucesso 
    *vetorDeSprites=alocarSprites();
    if(vetorDeSprites==NULL){
        printf("Erro ao alocar vetor de sprites");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        al_destroy_event_queue(*eventQueue);
        al_destroy_event_queue(*timerQueue);
        al_destroy_display(*janela);
        al_destroy_mixer(al_get_default_mixer());
        al_destroy_audio_stream(*musicaMenu);
        al_destroy_sample(*score);
        al_destroy_sample(*error);
        al_destroy_timer(*timer);
        return -1;
    }
    //carrega sprites e background no vetor de sprites e confere sucesso
    if(!carregarSprites(*vetorDeSprites)){
        printf("Erro ao alocar vetor de sprites");
        al_uninstall_keyboard();
        al_uninstall_mouse();
        al_uninstall_audio();
        al_destroy_font(*font);
        al_destroy_event_queue(*eventQueue);
        al_destroy_event_queue(*timerQueue);
        al_destroy_display(*janela);
        al_destroy_mixer(al_get_default_mixer());
        al_destroy_audio_stream(*musicaMenu);
        al_destroy_sample(*score);
        al_destroy_sample(*error);
        al_destroy_timer(*timer);
        //free(*vetorDeSprites);
    }
    return 1;
}   
//aloca o vetor de sprites
ALLEGRO_BITMAP** alocarSprites(){
    ALLEGRO_BITMAP **sprites = malloc(19*sizeof(ALLEGRO_BITMAP*));
    if(sprites==NULL){
        printf("Erro ao alocar sprites\n");
        exit(-1);
    }
    for(int i=0; i<19; i++){
        sprites[i]=NULL;
    }
    return sprites;
}
//carrega as imagens no vetor
int carregarSprites(ALLEGRO_BITMAP **sprites){
    char carta[18];
    for(int i=0; i<18; i++){
        sprintf(carta, "images/card%d.png", i+1);
        sprites[i]=al_load_bitmap(carta);
    }
    sprites[18]=al_load_bitmap("images/gameBackground.png");
    for(int i=0; i<19; i++){
        if(sprites[i]==NULL){
            for(int j=0; j<19; j++){
                if(sprites[j]!=NULL)
                    al_destroy_bitmap(sprites[j]);
            }
            return -1;
        }
    }
    return 1;
}

void finalizar(ALLEGRO_DISPLAY **janela, ALLEGRO_FONT **font, ALLEGRO_EVENT_QUEUE **eventQueue,
        ALLEGRO_AUDIO_STREAM **musicaMenu, ALLEGRO_EVENT_QUEUE **timerQueue, ALLEGRO_BITMAP **vetorDeSprites){
    //desinstala e desaloca os itens inicializados pelo programada
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_uninstall_audio();
    al_destroy_font(*font);
    al_destroy_event_queue(*eventQueue);
    al_destroy_event_queue(*timerQueue);
    al_destroy_display(*janela);
    al_destroy_mixer(al_get_default_mixer());
    al_destroy_audio_stream(*musicaMenu);
    for(int i=0; i<19; i++){
        al_destroy_bitmap(vetorDeSprites[i]);
    }
    free(vetorDeSprites);
}
