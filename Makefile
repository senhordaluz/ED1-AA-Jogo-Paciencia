# Makefile do jogo ##
# Bibliotecas: SDL 2.0, SDL_image 2.0, SDL_mixer 2.0 ##

## O comando make cria o executavel ##
## O comando make clean limpa os arquivos .o ##
## O comando make mrproper apaga o executavel ##

############################### Makefile ###############################

all: paciencia
paciencia: main.c paciencia.h pilha.h interface.h pilha_descarte.h pilha_estoque.h pilha_fileira.h pilha_naipe.h carta.h
		# Compilando o jogo
		gcc main.c -o paciencia 2>paciencia.gccmessages
#------> Execucao dos arquivos
#
clean:
		rm -rf *.o
#
mrproper: clean
		rm -rf paciencia