# Makefile é um script que transforma vários arquivos em binários 
# Um binário são "arquivos de programa" (arquivos .deb, .exe, .out...)
# Requer o "Make", que vem nativo no Linux mas tem como baixar no Windows
# O processo todo é mais fácil no Linux então eu recomendo você fazer dual boot
# Sério, só faz dual boot porque muita coisa nessa faculdade é consideravelmente mais fácil no Linux
# Mas não precisa se não quiser
# Tutorial do makefile: https://embarcados.com.br/introducao-ao-makefile/

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g

all: RegisterMaker # all gera todos os binários e objetos. Colocar tanto os sideapps quanto a árvore-B aqui nas dependências.

RegisterMaker: 
	$(CC) $(CFLAGS) ./sideapps/RegisterMaker.c -o RegisterMaker.out


.PHONY : clean
clean: # Limpa todos os binários e objetos dessa pasta.
	rm -rf *.o *.exe *.out

veryclean: clean # Limpa todos os binários, objetos e resultados
	find . -name "*.txt" -delete
	find . -name "*.o" -delete
