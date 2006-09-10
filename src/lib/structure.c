/**
	Modulo com funcoes para lidar com as estruturas
 */

#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "io.h"
#include "interface.h"


/**
 */
AgendaInfo *inicAgendaInfo() {
	AgendaInfo *nova = malloc(sizeof(AgendaInfo));

	if (nova) {
		nova->arquivo = NULL;
		nova->ehAVL = 0;
		nova->foiAlterada = 0;
	}

	return nova;
}

/**
 */
void finalizaAgendaInfo(AgendaInfo *agenda) {
	free(agenda);
}
