/**
 */

#ifndef _PROCESSOS_H

#define _PROCESSOS_H

#include "structure.h"

AgendaInfo *processoCriaAgenda();
AgendaInfo *processoAbrirAgenda();

void processoCriaContato(AgendaInfo *);
void processoAlteraContato(AgendaInfo *);
void processoSalvarAgenda(AgendaInfo *);
void processoFinalizaAgenda(AgendaInfo *);
void processoAbreAgenda(AgendaInfo *);
void processoBalanceEstatico(AgendaInfo *);
void processoExcluiContato(AgendaInfo *);
void processoSalvarAgenda(AgendaInfo *);
void processoProcuraContato(AgendaInfo *);
void processoMostraContatos(AgendaInfo *);
void processoMostraArvore(AgendaInfo *);
void processoBalanceEstatico(AgendaInfo *);

#endif /* !_PROCESSOS_H */
