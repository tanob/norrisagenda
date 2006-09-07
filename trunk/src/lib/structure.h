/** 
	Arquivo de cabeçalho do modulo structure
*/

typedef struct _AgendaInfo {
	FILE *arquivo; 
	char ehAVL;
	char foiAlterada;	
} AgendaInfo;


AgendaInfo *processoCriaAgenda();

AgendaInfo *processoAbrirAgenda();

void processoAbreAgenda(AgendaInfo *agenda);
