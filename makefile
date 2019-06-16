all:	main.c 
	gcc -Wall intro.c telaInicial.c inicializarFinalizar.c registrarPontuacao.c telaJogo.c main.c -o memoria `pkg-config --cflags --libs allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_dialog-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5`

clean:
	rm -rf *.o *~ memoria
