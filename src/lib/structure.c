/**
	Modulo com funcoes para lidar com as estruturas
 */

#include <stdio.h>
#include <stdlib.h>

#include "structure.h"

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
