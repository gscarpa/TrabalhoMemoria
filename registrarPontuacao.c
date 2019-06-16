#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string.h>
#include "headers/registrarPontuacao.h"
#include "headers/jogador.h"

int registrarPontuacao(int erros, ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_FONT *font){
	char nome[30], idade[4];
	nome[0]='\0', idade[0]='\0';
	int i=0, j=0, opcao=1;
	while(opcao>0){
		if(opcao==1)
			opcao=inserirNome(eventQueue, event, font, &i, nome, idade);
		else if(opcao==2)
			opcao=inserirIdade(eventQueue, event, font, &j, nome, idade);
	}
	
	jogador gravarJogador;

	gravarJogador.pontuacao=((18.0 / erros)*1000);
	if(nome[0]=='\0')
		strcat(nome, "Jogador");
	gravarJogador.tamanhoNome=strlen(nome)+1;
	gravarJogador.nome=malloc(gravarJogador.tamanhoNome*sizeof(char));
	if(gravarJogador.nome==NULL){
		printf("Ocorreu um erro ao gravar os dados do jogador.\n");
		return -1;
	}
	strcpy(gravarJogador.nome, nome);
	//printf("%d %d %d\n", ((int)idade[0]),((int)idade[1]),((int)idade[2]));
	if(idade[0]>=48){
		gravarJogador.idade=idade[0]-48;
		if(idade[1]>=48){
			gravarJogador.idade=(idade[0]-48)*10+idade[1]-48;
			if(idade[2]>=48)
				gravarJogador.idade=(idade[0]-48)*100+(idade[1]-48)*10+idade[2]-48;
		}
	}else
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


    rewind(fp);
    /*cont=0;
    while(cont<10){
    	short b, c;
    	int a=-1;
    	fread(&a,sizeof(int),1,fp);
		if(a==-1)
			break;
		char nomin[a];
		fread(nomin,sizeof(char),a,fp);
	    fread(&b,sizeof(int),1,fp);
	    fread(&c,sizeof(int),1,fp);
   		printf("%s de %hd anos fez %hd pontuacao\n", nomin, b, c);
   		cont++;
    }*/


    if(fclose(fp))
   		printf("Ocorreu um erro ao fechar o arquivo.\n");

	return 0;
}

int inserirNome(ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_FONT *font, int *i, char *nome, char *idade){
	char inputChar;
	while(1){
		al_clear_to_color(al_map_rgb(255,255,255));
		al_draw_textf(font, al_map_rgb(0,0,0), 50, 50, ALLEGRO_ALIGN_LEFT, "Nome: %s", nome);
		al_draw_textf(font, al_map_rgb(0,0,0), 50, 100, ALLEGRO_ALIGN_LEFT, "Idade: %s", idade);
		al_draw_textf(font, al_map_rgb(0,0,0), 20, 50, ALLEGRO_ALIGN_LEFT, "->");
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
		}
	}
	return 2;
}
int inserirIdade(ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_EVENT *event, ALLEGRO_FONT *font, int *j, char *nome, char *idade){
	char inputChar;
	while(1){
		al_clear_to_color(al_map_rgb(255,255,255));
		al_draw_textf(font, al_map_rgb(0,0,0), 50, 50, ALLEGRO_ALIGN_LEFT, "Nome: %s", nome);
		al_draw_textf(font, al_map_rgb(0,0,0), 50, 100, ALLEGRO_ALIGN_LEFT, "Idade: %s", idade);
		al_draw_textf(font, al_map_rgb(0,0,0), 20, 100, ALLEGRO_ALIGN_LEFT, "->");
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
				*j-=1;
				idade[*j]='\0';
			}else if(event->keyboard.keycode==ALLEGRO_KEY_ENTER)
				break;
		}
		if(*j>2)
			*j=2;
		
	}
	return 0;

}