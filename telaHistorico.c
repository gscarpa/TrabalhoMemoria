#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>

#include "headers/telaHistorico.h"
#include "headers/jogador.h"

int telaHistorico(ALLEGRO_BITMAP **sprites, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_FONT *font){
	int i=0;
	FILE *fp;
	fp=fopen("históricoJogadores", "rb");
	if(fp==NULL){
		printf("Falha ao carregar o arquivo,\n");
	}else{
		jogador *top;
		top=malloc(3*sizeof(jogador));
		if(top==NULL){
			printf("Ocorreu um erro ao exibir o top 3\n");
			if(fclose(fp))
			printf("Ocorreu um erro ao fechar o arquivo.\n");
		}else{
			while(i<3){
				top[i].tamanhoNome=-1;
				fread(&top[i].tamanhoNome, sizeof(int),1,fp);
				if(top[i].tamanhoNome==-1)
					break;
				top[i].nome=malloc(top[i].tamanhoNome*sizeof(char));
				if(top[i].nome==NULL){
					printf("Ocorreu um erro ao exibir o top 3\n");
					for(int j=0; j<i; j++){
						if(top[j].nome!=NULL)
							free(top[j].nome);
					}
					break;
				}
				fread(top[i].nome, sizeof(char), top[i].tamanhoNome, fp);
				fread(&top[i].idade, sizeof(int), 1, fp);
				fread(&top[i].pontuacao, sizeof(int),1,fp);
				i++;
			}
			while(1){
			al_draw_bitmap(sprites[19],0,0,1);
			al_draw_textf(font, al_map_rgb(255,255,255), 400, 250, ALLEGRO_ALIGN_CENTER, "Top 3");
			for(int j=0; j<i; j++){
				al_draw_textf(font, al_map_rgb(255,255,255), 50, 300, ALLEGRO_ALIGN_LEFT, "Jogador");
				al_draw_textf(font, al_map_rgb(255,255,255), 500, 300, ALLEGRO_ALIGN_LEFT, "Idade");
				al_draw_textf(font, al_map_rgb(255,255,255), 580, 300, ALLEGRO_ALIGN_LEFT, "Pontuação");
				al_draw_textf(font, al_map_rgb(255,255,255), 50, 350+50*j, ALLEGRO_ALIGN_LEFT, "%s", top[j].nome);
				al_draw_textf(font, al_map_rgb(255,255,255), 500, 350+50*j, ALLEGRO_ALIGN_LEFT, "%d", top[j].idade);
				al_draw_textf(font, al_map_rgb(255,255,255), 580, 350+50*j, ALLEGRO_ALIGN_LEFT, "%d", top[j].pontuacao);
			}
			al_draw_textf(font, al_map_rgb(255,255,255), 400, 550, ALLEGRO_ALIGN_CENTER, "Voltar");
			al_flip_display();
			al_wait_for_event(*eventQueue, event);
			if(event->type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				if(event->mouse.x>=365 && event->mouse.x<=435 && event->mouse.y>=535 && event->mouse.y<=565)
					break;
			}
		}
		for(int j=0; j<i; j++){
			free(top[j].nome);
		}
		free(top);
		if(fclose(fp))
			printf("Ocorreu um erro ao fechar o arquivo.\n");
		}
		return 1;
	}
	while(1){
		al_draw_bitmap(sprites[19],0,0,1);
		al_draw_textf(font, al_map_rgb(255,255,255), 400, 250, ALLEGRO_ALIGN_CENTER, "Top 3");
		al_draw_textf(font, al_map_rgb(255,255,255), 50, 300, ALLEGRO_ALIGN_LEFT, "Jogador");
		al_draw_textf(font, al_map_rgb(255,255,255), 500, 300, ALLEGRO_ALIGN_LEFT, "Idade");
		al_draw_textf(font, al_map_rgb(255,255,255), 580, 300, ALLEGRO_ALIGN_LEFT, "Pontuação");	
		al_draw_textf(font, al_map_rgb(255,255,255), 400, 550, ALLEGRO_ALIGN_CENTER, "Voltar");
		al_flip_display();
		al_wait_for_event(*eventQueue, event);
		if(event->type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			if(event->mouse.x>=365 && event->mouse.x<=435 && event->mouse.y>=535 && event->mouse.y<=565)
				break;
		}
	}

	return 1;
}
