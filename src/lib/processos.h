/**
 */

#ifndef _PROCESSOS_H

#define _PROCESSOS_H

#include "structure.h"

AgendaInfo *processoCriaAgenda();
AgendaInfo *processoAbrirAgenda();

int processoCriaContato(AgendaInfo *);
int processoAlteraContato(AgendaInfo *);
int processoSalvarAgenda(AgendaInfo *);
void processoFinalizaAgenda(AgendaInfo *);
void processoAbreAgenda(AgendaInfo *);
int processoBalanceEstatico(AgendaInfo *);
int processoExcluiContato(AgendaInfo *);
int processoSalvarAgenda(AgendaInfo *);
int processoProcuraContato(AgendaInfo *);
int processoMostraContatos(AgendaInfo *);
int processoMostraArvore(AgendaInfo *);
int processoBalanceEstatico(AgendaInfo *);

#endif /* !_PROCESSOS_H */
