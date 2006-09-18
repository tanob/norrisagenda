/**
	Modulo com funcoes para interface console
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "io.h"
#include "structure.h"
#include "processos.h"


/**
	Imprime informacoes do programa
 */
void infoPrograma() {
	printf("Programa Norris-Agenda (C) 2006 Computa boys\n\n");
}


/**
	Limpa a tela do console
 */
void limpaTela() {
#ifdef LINUX
	system("clear");
#else
	system("cls");
#endif
}


/**
	Limpa a tela, imprime algum cabecalho com o nome do programa e
	mostra ao usuario as 3 opcoes iniciais:
		- 1. Criar agenda
		- 2. Abrir agenda
		- 0. Sair

	Entre parentesis eh o que o usuario deve
	digitar e pressionar enter para acessar.
 */
void menuInicial() {
	int opcao, opcoesValidas[] = { 0, 1, 2, -1 };
	AgendaInfo *agenda = NULL;

	limpaTela();
	infoPrograma();

	printf("1. Criar agenda\n2. Abrir agenda\n0. Sair\n\n");

	opcao = leOpcaoValida("Opcao: ", &opcoesValidas[0], "***Opcao invalida***\n");

	switch(opcao) {
		case 1:
			agenda = processoCriaAgenda();

			/* Se sucesso criando agenda */
			if (agenda) {
				processoAbreAgenda(agenda);
				processoFinalizaAgenda(agenda);
			}

			break;

		case 2:
			do {
				/* Enquanto nao conseguir abrir a agenda.. */
				agenda = processoAbrirAgenda();
				if (!agenda) {
					printf("\n***Erro abrindo agenda***\n");
				}

			} while(!agenda);

			/* Se sucesso abrindo a agenda */
			if (agenda) {
				processoAbreAgenda(agenda);
				processoFinalizaAgenda(agenda);
			}

			break;

		/*
		case '0':
			break;
		*/
	}

	/* Limpa a tela ao finalizar a utilizacao do programa */
	limpaTela();
}


/**
	Mostra as opcoes para lidar com a agenda aberta.
	Recebe como parametro uma flag se a arvore de dados da agenda eh balanceada,
	usando esta flag ele oferece ou nao a opcao de balanceamento estatico.
 */
void mostraMenuAgenda(char agendaBal) {
	printf("1. Incluir\n2. Alterar\n3. Excluir\n4. Salvar\n5. Procurar\n6. Mostrar todos contatos\n7. Mostrar arvore\n");

	if (!agendaBal) {
		printf("8. Balancear estaticamente\n");
	}

	printf("0. Sair\n");
}
