#include <stdio.h>
#include <stdlib.h>


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

