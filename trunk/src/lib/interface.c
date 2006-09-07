#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#define LINUX

/**
	Imprime informacoes do programa
 */
void infoPrograma() {
	printf("Programa ED1-Agenda (C) 2006 Computa boys\n\n");
}

/**
	Limpa a tela do console
 */
void limpaTela() {
#ifdef LINUX
	system("clear");
#elif
	system("cls");
#endif
}


/**
	Limpa a tela, imprime algum cabecalho com o nome do programa e
	mostra ao usuario as 3 opcoes iniciais:
		- (C)riar agenda
		- (A)brir agenda
		- (S)air

	Entre parentesis eh o que o usuario deve
	digitar e pressionar enter para acessar.
 */
void menuInicial() {
	char opcao;
	AgendaInfo *agenda = NULL;

	limpaTela();
	infoPrograma();

	printf("(C)riar agenda\n(A)brir agenda\n(S)air\n\n");

	do {
		printf("Opcao: ");

		opcao = leOpcao("CcAaSs");
		if (!opcao) {
			printf("***Opcao invalida***\n");
		}

	} while(!opcao);

	if (opcao == 'C' || opcao == 'c') {
		agenda = processoCriaAgenda();

		// Se sucesso criando agenda
		if (agenda) {
			processoAbreAgenda(agenda);
		}
	}
	else if (opcao == 'A' || opcao == 'a') {
		agenda = processoAbrirAgenda();

		// Se sucesso abrindo a agenda
		if (agenda) {
			processoAbreAgenda(agenda);
		}
	}
	else if (opcao == 'S' || opcao == 's') {
	}
	else {
		// De acordo com a logica, nunca poderia se chegar aqui...
		printf("menuInicial: BUG!");
	}

	// Limpa a tela ao finalizar a utilizacao do programa
	limpaTela();
}

		

