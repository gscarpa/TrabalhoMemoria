#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string.h>
#include "headers/registrarPontuacao.h"
#include "headers/jogador.h"

int registrarPontuacao(ALLEGRO_BITMAP **sprites, int erros, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_FONT *font){
	char nome[30], idade[4];
	nome[0]='\0', idade[0]='\0';
	int i=0, j=0, opcao=1;
	int pontuacao;
	if(erros==0)
		pontuacao=20000;
	else
		pontuacao=18000/erros;

	while(opcao!=0){
		switch(opcao){
			case(1):
				opcao=inserirNome(sprites, eventQueue, event, font, &i, nome, idade, pontuacao);
				break;
			case(2):
				opcao=inserirIdade(sprites, eventQueue, event, font, &j, nome, idade, pontuacao);
				break;
			case(0):
				opcao=0;
				break;
			default:
				break;
		}
	}
	printf("oi");
	jogador gravarJogador;

	gravarJogador.pontuacao=pontuacao;
	if(nome[0]=='\0')
		strcat(nome, "Jogador");
	gravarJogador.tamanhoNome=strlen(nome)+1;
	gravarJogador.nome=malloc(gravarJogador.tamanhoNome*sizeof(char));
	if(gravarJogador.nome==NULL){
		printf("Ocorreu um erro ao gravar os dados do jogador.\n");
		return -1;
	}
	strcpy(gravarJogador.nome, nome);
	if(idade[0]>=48){
		gravarJogador.idade=idade[0]-48;
		if(idade[1]>=48){
			gravarJogador.idade=(idade[0]-48)*10+idade[1]-48;
			if(idade[2]>=48)
				gravarJogador.idade=(idade[0]-48)*100+(idade[1]-48)*10+idade[2]-48;
		}
	}else if(idade[0]=='\0')
		gravarJogador.idade=0;

	FILE * fp;
	fp = fopen("históricoJogadores","r+b");

	if(fp==NULL){
    	printf("Falha ao carregar o arquivo.\nCriando novo arquivo...\n");
	    fp=fopen("históricoJogadores", "w+b");
	    if(fp==NULL){
	    	printf("Ocorreu um erro ao criar o arquivo de histórico.\n");
	    	return -1;
    	}
  	}

  	jogador jogadores[10];

  	short cont=0;
  	while(cont<9){
	    jogadores[cont].tamanhoNome=-1;
	    fread(&jogadores[cont].tamanhoNome,sizeof(int),1,fp);
	    if(jogadores[cont].tamanhoNome==-1)
	    	break;
	    jogadores[cont].nome=malloc(jogadores[cont].tamanhoNome*sizeof(char));
	    if(jogadores[cont].nome==NULL){
			printf("Ocorreu um erro ao gravar os dados do jogador.\n");
			return -1;
		}
	    fread(jogadores[cont].nome,sizeof(char),jogadores[cont].tamanhoNome,fp);
	    fread(&jogadores[cont].idade,sizeof(int),1,fp);
	    fread(&jogadores[cont].pontuacao,sizeof(int),1,fp);
	    cont++;
	}
	jogadores[cont]=gravarJogador;

	for(int i=0; i<cont; i++){
		jogador temp=jogadores[i];
		for(int j=i+1; j<=cont; j++){
			if(jogadores[j].pontuacao > temp.pontuacao){
				temp=jogadores[j];
				jogadores[j]=jogadores[i];
				jogadores[i]=temp;
			}
		}
	}
	rewind(fp);
	//int tamanhoNome=strlen(nome);
	for(int i=0; i<=cont; i++){
		fwrite(&jogadores[i].tamanhoNome,sizeof(int),1,fp);
		fwrite(jogadores[i].nome,sizeof(char),jogadores[i].tamanhoNome,fp);
	    fwrite(&jogadores[i].idade,sizeof(int),1,fp);
	    fwrite(&jogadores[i].pontuacao,sizeof(int),1,fp);
	}
    if(fclose(fp))
   		printf("Ocorreu um erro ao fechar o arquivo.\n");
	return 3;
}

int inserirNome(ALLEGRO_BITMAP **sprites, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_FONT *font, int *i, char *nome, char *idade, int pontuacao){
	char inputChar;
	while(1){
		al_draw_bitmap(sprites[18], 0, 0, 1);
		al_draw_textf(font, al_map_rgb(0,0,0), 50, 200, ALLEGRO_ALIGN_LEFT, "Insira seus dados");
		al_draw_textf(font, al_map_rgb(0,0,0), 50, 250, ALLEGRO_ALIGN_LEFT, "Nome: %s", nome);
		al_draw_textf(font, al_map_rgb(0,0,0), 50, 300, ALLEGRO_ALIGN_LEFT, "Idade: %s", idade);
		al_draw_textf(font, al_map_rgb(0,0,0), 50, 350, ALLEGRO_ALIGN_LEFT, "Pontuação: %d", pontuacao);
		al_draw_textf(font, al_map_rgb(0,0,0), 20, 250, ALLEGRO_ALIGN_LEFT, "->");
		al_draw_textf(font, al_map_rgb(255,255,255), 400, 550, ALLEGRO_ALIGN_CENTER, "Salvar");
		al_flip_display();
		al_wait_for_event(*eventQueue, event);
		if(event->type==ALLEGRO_EVENT_KEY_CHAR){
			inputChar=event->keyboard.unichar;
			if(inputChar>=32 && inputChar<=126){
				nome[*i]=inputChar;
				*i+=1;
				nome[*i]='\0';
			}
		}else if(event->type==ALLEGRO_EVENT_KEY_UP){
			if(event->keyboard.keycode==ALLEGRO_KEY_BACKSPACE){
				*i-=1;
				nome[*i]='\0';
			}else if(event->keyboard.keycode==ALLEGRO_KEY_ENTER)
				break;
		}else if(event->type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			if(event->mouse.x>=365 && event->mouse.x<=435 && event->mouse.y>=535 && event->mouse.y<=565)
				return 0;
			if(event->mouse.x>=50 && event->mouse.x<=700 && event->mouse.y>=300 && event->mouse.y<=330)
				return 2;
		}
	}
	return 2;
}
int inserirIdade(ALLEGRO_BITMAP **sprites, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_FONT *font, int *j, char *nome, char *idade, int pontuacao){
	char inputChar;
	while(1){
		al_draw_bitmap(sprites[18], 0, 0, 1);
		al_draw_textf(font, al_map_rgb(0,0,0), 50, 200, ALLEGRO_ALIGN_LEFT, "Insira seus dados");
		al_draw_textf(font, al_map_rgb(0,0,0), 50, 250, ALLEGRO_ALIGN_LEFT, "Nome: %s", nome);
		al_draw_textf(font, al_map_rgb(0,0,0), 50, 300, ALLEGRO_ALIGN_LEFT, "Idade: %s", idade);
		al_draw_textf(font, al_map_rgb(0,0,0), 50, 350, ALLEGRO_ALIGN_LEFT, "Pontuação: %d", pontuacao);
		al_draw_textf(font, al_map_rgb(0,0,0), 20, 300, ALLEGRO_ALIGN_LEFT, "->");
		al_draw_textf(font, al_map_rgb(255,255,255), 400, 550, ALLEGRO_ALIGN_CENTER, "Salvar");
		al_flip_display();
		al_wait_for_event(*eventQueue, event);
		if(event->type==ALLEGRO_EVENT_KEY_CHAR){
			inputChar=event->keyboard.unichar;
			if(inputChar>=48 && inputChar<=57){
				idade[*j]=inputChar;
				*j+=1;
				idade[*j]='\0';
			}
		}else if(event->type==ALLEGRO_EVENT_KEY_UP){
			if(event->keyboard.keycode==ALLEGRO_KEY_BACKSPACE){
				if(*j==2)
					idade[*j]='\0';
				else{
					*j-=1;
					idade[*j]='\0';
				}
			}else if(event->keyboard.keycode==ALLEGRO_KEY_ENTER)
				break;
		}else if(event->type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			if(event->mouse.x>=365 && event->mouse.x<=435 && event->mouse.y>=535 && event->mouse.y<=565)
				break;
			if(event->mouse.x>=50 && event->mouse.x<=700 && event->mouse.y>=250 && event->mouse.y<=280)
				return 1;
		}
		if(*j>2)
			*j=2;
	}
	return 0;
}