#include <stdio.h>

#include "processos.h"
#include "io.h"
#include "structure.h"
#include "interface.h"


/**
	Deve perguntar ao usuario se a agenda eh balanceada,
	e alguma outra informacao necessaria para a criacao
	da agenda (nao deve se pedir informacoes como o nome do arquivo a
	ser criado, etc., isto deve ser feito depois quando
	se salva a agenda pela primeira vez), e entao
	retorna as informacoes desta agenda.
 */
AgendaInfo *processoCriaAgenda() {
	AgendaInfo *agendaInfo = inicAgendaInfo();

	if (!agendaInfo) {
		printf("***Erro alocando memoria para agenda***\n");
	}
	else {
		int opcao, snOpcoes[] = { 1, 2 };

		opcao = leOpcaoValida("---Arvore balanceada? (1. Sim, 2. Nao) ", &snOpcoes[0], "***Opcao invalida***\n");
		agendaInfo->ehAVL = (opcao == 1 ? 1 : 0);
	}

	return agendaInfo;
}


/**
	Deve ser usado quando quer se abrir uma agenda,
	deve perguntar aonde esta o arquivo da agenda,
	e pode chamar outra funcao que se encarrega
	de preencher alguma informacao na estrutura AgendaInfo.
 */
AgendaInfo *processoAbrirAgenda() {
	/* TODO */
	return NULL;
}


/**
 */
void processoSalvarAgenda(AgendaInfo *agenda) {
	/* TODO */

	/* Ao final do processo, se tudo certo.. */
	agenda->foiAlterada = 0;
}


/**
 */
void processoFinalizaAgenda(AgendaInfo *agenda) {
	if (agenda->foiAlterada) {
		char *msg = "---A agenda foi alterada desde a sua abertura, deseja salvar as alteracoes? (1. Sim, 2. Nao) ";
		int opcao, snOpcoes[] = { 1, 2 };

		opcao = leOpcaoValida(msg, &snOpcoes[0], "***Opcao invalida***\n");

		if (opcao == 1) {
			processoSalvarAgenda(agenda);
		}
	}

	finalizaAgendaInfo(agenda);
}


/**
	Mostra as opcoes do que se pode fazer com a agenda,
	pode chamar outra funcao para montar o menu, etc.
		Incluir
		Alterar
		Excluir
		Salvar
		Procurar
		Mostrar todos os contatos (em ordem alfabetica)
		Mostrar arvore
		Balancear estaticamente (mostrar apenas qdo eh uma nao-AVL)
		Sair
 */
void processoAbreAgenda(AgendaInfo *agenda) {
	char pedirPause = 0;
	int opcao, opcoesValidas[] = { 0, 1, 2, 3, 4, 5, 6, 7, -1, -1 };
	void (*processos[])(AgendaInfo *) = { processoCriaContato, processoAlteraContato, processoExcluiContato,
																				processoSalvarAgenda, processoProcuraContato, processoMostraContatos,
																				processoMostraArvore, processoBalanceEstatico };

	/* Habilita a opcao balancear estatico se for nao-AVL */
	opcoesValidas[8] = (!agenda->ehAVL ? 8 : -1);

	do {
		if (pedirPause) {
			printf("\n---Pressione ENTER para continuar---\n");
			getchar();

			pedirPause = 0;
		}

		limpaTela();
		infoPrograma();

		mostraMenuAgenda(agenda->ehAVL);
		opcao = leOpcaoValida("Opcao: ", &opcoesValidas[0], "***Opcao invalida***\n");

		if (opcao > 0) {
			/* Chama o processo de acordo com a opcao.. */
			(*processos[opcao-1])(agenda);
		}

		/* Os processos que mostram dados devem pedir pausa */
		pedirPause = (opcao >= 5 && opcao <= 7);

	} while(opcao != 0);
}


/**
 */
void processoBalanceEstatico(AgendaInfo *agenda) {
	/* TODO */
	printf("processoBalanceEstatico: nao implementado ainda\n");

	/* Apos o balanceamento a arvore deve ser considerada como modificada */
	agenda->foiAlterada = 1;
}


/**
 */
void processoCriaContato(AgendaInfo *agenda) {
	/* TODO */
	printf("processoCriaContato: nao implementado ainda\n");
}


/**
 */
void processoAlteraContato(AgendaInfo *agenda) {
	/* TODO */
	printf("processoAlteraContato: nao implementado ainda\n");
}


/**
 */
void processoExcluiContato(AgendaInfo *agenda) {
	/* TODO */
	printf("processoExcluiContato: nao implementado ainda\n");
}


/**
 */
void processoProcuraContato(AgendaInfo *agenda) {
	/* TODO */
	printf("processoProcuraContato: nao implementado ainda\n");
}


/**
 */
void processoMostraContatos(AgendaInfo *agenda) {
	/* TODO */
	printf("processoMostraContatos: nao implementado ainda\n");
}


/**
 */
void processoMostraArvore(AgendaInfo *agenda) {
	/* TODO */
	printf("processoMostraArvore: nao implementado ainda\n");
}
