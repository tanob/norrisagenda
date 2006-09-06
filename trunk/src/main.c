/**
	Trabalho de Estrutura de Dados I - Agenda (2006/1)
		(AB) Adriano Bonat
		(DB) Djonatan Buss
		(EJ) Elvio Junior

		Historico:
		06/09, AB: montagem do esqueleto;
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINUX

typedef struct _AgendaInfo {
	FILE *arquivo; /* Manipulador do arquivo */

	char ehAVL; /* Indica se eh balanceada ou nao */
	char foiAlterada; /* Se a agenda foi aberta e alterada e suas alteracoes ainda nao foram salvas */

	/*
		A ideia eh guardar alguma outra estrutura de dados aqui,
		como uma estrutura que valha tanto para a AVL qto para a nao-AVL,
		talvez um "union" dessas estruturas...
	*/

} AgendaInfo;

/**
	Le um caractere do teclado, e verifica se
	este se encontra em um vetor de caracteres validos.
	Caso seja valido, eh retornado o caractere lido,
	caso contrario, eh retornado 0 (NULL).
 */
char leOpcao(char *chValidos) {
	char buf[512], opcao, valido=0, *p;

	fgets(buf, sizeof(buf), stdin);
	opcao = buf[0];

	// Verifica se opcao esta entre as validas
	p = chValidos;
	while (*p) {
		if (opcao == *p)
			valido = 1;
		p++;
	}

	return valido ? opcao : 0;
}

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
	Deve perguntar ao usuario se a agenda eh balanceada,
	e alguma outra informacao necessaria para a criacao
	da agenda (nao deve se pedir informacoes como o nome do arquivo a
	ser criado, etc., isto deve ser feito depois quando
	se salva a agenda pela primeira vez), e entao
	retorna as informacoes desta agenda.
 */
AgendaInfo *processoCriaAgenda() {
	return NULL;
}

/**
	Deve ser usado quando quer se abrir uma agenda,
	deve perguntar aonde esta o arquivo da agenda,
	e pode chamar outra funcao que se encarrega
	de preencher alguma informacao na estrutura AgendaInfo.
 */
AgendaInfo *processoAbrirAgenda() {
	return NULL;
}

/**
	Mostra as opcoes do que se pode fazer com a agenda,
	pode chamar outra funcao para montar o menu, etc.
 */
void processoAbreAgenda(AgendaInfo *agenda) {
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

/**
	Funcao inicial.
 */
int main(int argc, char *argv[]) {

	menuInicial();

	return 0;
}
