/**
	Arquivo de cabecalho do modulo structure
*/

#ifndef _STRUCTURE_H

#define _STRUCTURE_H

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

AgendaInfo *processoCriaAgenda();

AgendaInfo *processoAbrirAgenda();

void processoAbreAgenda(AgendaInfo *agenda);

#endif /* !_STRUCTURE_H */
