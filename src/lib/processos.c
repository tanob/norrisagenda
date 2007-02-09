#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "processos.h"
#include "io.h"
#include "structure.h"
#include "interface.h"
#include "percorre.h"
#include "arquivo.h"

#define DIR "dados/"


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
	char nome[50];
	char caminho[50], ehAVL;
	int opcao, snOpcoes[] = { 1, 2 };

	printf("\n\n---Abrir Agenda---\nNome da agenda que deseja abrir: ");
	fgets(nome, sizeof(nome), stdin);
	nome[strlen(nome) - 1] = '\0';
	strcpy(caminho, DIR);
	strcat(caminho, nome);

	opcao = leOpcaoValida("---Arvore balanceada? (1. Sim, 2. Nao) ", &snOpcoes[0], "***Opcao invalida***\n");
	ehAVL = (opcao == 1 ? 1 : 0);

	return import( caminho, ehAVL );
}


/**
 */
int processoSalvarAgenda(AgendaInfo *agenda) {
	char nome[50];

	do {
		printf("\n\n---Salvar Agenda---\nNome da agenda a salvar: ");
		fgets(nome, sizeof(nome), stdin);

		nome[ strlen( nome ) - 1 ] = '\0';

		if ( strlen( nome ) ==  0 ) {
        	printf("\n\n***Nome de arquivo invalido***");
		}

	} while(!strlen(nome));

	if ( _salvaArquivo( agenda, nome ) ) {
		/* Ao final do processo, se tudo certo.. */
		agenda->foiAlterada = 0;
	}
	else {
		printf("\n***Erro salvando agenda***\n");
		return 1; /* Pede pause */
	}

	return 0;
}


/**
 */
void processoFinalizaAgenda(AgendaInfo *agenda) {
	if (agenda->foiAlterada) {
		char *msg = "---A agenda foi alterada desde a sua abertura, deseja salvar as alteracoes? (1. Sim, 2. Nao) ";
		int opcao, snOpcoes[] = { 1, 2 };

		opcao = leOpcaoValida(msg, &snOpcoes[0], "***Opcao invalida***\n");

		if (opcao == 1) {
			while (processoSalvarAgenda(agenda)) ;
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
	int pedirPause = 0;
	int opcao, opcoesValidas[] = { 0, 1, 2, 3, 4, 5, 6, 7, -1, -1 };
	int (*processos[])(AgendaInfo *) = { processoCriaContato, processoAlteraContato, processoExcluiContato,
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
			/* Dah um espaco */
			printf("\n\n");

			/* Chama o processo de acordo com a opcao.. */
			pedirPause = (*processos[opcao-1])(agenda);
		}

	} while(opcao != 0);
}


/**
 */
ArvoreMista *criaNoh(Contato *contato, char ehAVL) {
	ArvoreMista *p = malloc(sizeof(ArvoreMista));
	p->contato = contato;
	p->esq = p->dir = NULL;
	p->fb = BAL;
	p->ehAVL = ehAVL;
	return p;
}


/**
 */
void mostraContato(const Contato *contato) {
	printf("Nome: %s\nTelefone: %s\n\n", contato->nome, contato->telefone);
}


/**
 */
Contato *procuraContato(const ArvoreMista *arv, const char *nome) {
	Contato *ret = NULL;
	int cmp;

	if (arv) {
		cmp = strcasecmp(nome, arv->contato->nome);

		if (!cmp) {
			ret = arv->contato;
		}
		else if (cmp < 0) {
			ret = procuraContato(arv->esq, nome);
		}
		else {
			ret = procuraContato(arv->dir, nome);
		}
	}

	return ret;
}


/**
 */
Contato *requisitaNomeEProcuraContato(const ArvoreMista *arv) {
	Contato *contato = NULL;
	char nome[50];

	printf("Nome do contato: ");
	fgets(nome, sizeof(nome), stdin);
	nome[strlen(nome)-1] = '\0';

	if (nome[0] == '\0') {
		printf("\n***Nome invalido***\n");
	}
	else {
		contato = procuraContato(arv, nome);

		if (!contato) {
			printf("\n***Contato nao existente***\n");
		}
	}

	return contato;
}


/**
 */
int processoBalanceEstatico(AgendaInfo *agenda) {
	balanceEstatico(&agenda->arv);

	/* Apos o balanceamento a arvore deve ser considerada como modificada */
	agenda->foiAlterada = 1;

	return 0;
}


/**
 */
int processoCriaContato(AgendaInfo *agenda) {
	ArvoreMista *arv;
	Contato *contato = malloc(sizeof(Contato));

	printf("---Novo Contato---\nNome: ");
	fgets(contato->nome, sizeof(contato->nome), stdin);
	contato->nome[strlen(contato->nome)-1] = '\0';

	if (contato->nome[0] == '\0') {
		printf("\n***Nome invalido***\n\n");
		free(contato);
		return 1; /* Pede pause */
	}

	printf("Telefone: ");
	fgets(contato->telefone, sizeof(contato->telefone), stdin);
	contato->telefone[strlen(contato->telefone)-1] = '\0';

	arv = criaNoh(contato, agenda->ehAVL);
	agenda->arv = insereNoh(agenda->arv, arv);
	agenda->foiAlterada = 1;

	return 0;
}


/**
 */
int processoAlteraContato(AgendaInfo *agenda) {
	Contato *contato;
	char novoTelefone[30], dadosAlterados = 0;

	printf("---Alterar Contato---\n");

	contato = requisitaNomeEProcuraContato(agenda->arv);
	if (contato) {
		printf("\n---Atualizar dados---\n");
		printf("Telefone: %s\nNovo telefone (ENTER para manter o antigo): ", contato->telefone);

		fgets(novoTelefone, sizeof(novoTelefone), stdin);
		novoTelefone[strlen(novoTelefone)-1] = '\0';

		if (novoTelefone[0] != '\0') {
			strncpy(contato->telefone, novoTelefone, sizeof(contato->telefone));
			dadosAlterados = 1;
		}

		if (dadosAlterados) {
			printf("\n---Dados atualizados---\n");
			mostraContato(contato);

			agenda->foiAlterada = 1;
		}
		else {
			printf("\n***Nenhum dado atualizado***\n");
		}
	}

	return 1;
}


/**
 */
int processoExcluiContato(AgendaInfo *agenda) {
	char nome[50];
	int result;

	printf("---Excluir Contato---\nNome do contato a ser excluido: ");
	fgets(nome, sizeof(nome), stdin);
	nome[strlen(nome)-1] = '\0';

	result = removeNoh(nome, &agenda->arv);
	if (result > 0) {
		printf("\n***Contato removido***\n");
		agenda->foiAlterada = 1;
	}
	else {
		printf("\n***Contato nao existente***\n");
	}

	return 1;
}


/**
 */
int processoProcuraContato(AgendaInfo *agenda) {
	Contato *contato;

	printf("---Procurar Contato---\n");

	contato = requisitaNomeEProcuraContato(agenda->arv);
	if (contato) {
		printf("\n---Contato encontrado---\n");
		mostraContato(contato);
	}

	return 1;
}


/**
 */
void _mostraContato(ArvoreMista *p, void *param) {
	Contato *contato = p->contato;
	mostraContato(contato);
}


/**
 */
int processoMostraContatos(AgendaInfo *agenda) {
	printf("---Contatos cadastrados---\n\n");
	percorreInfixado(agenda->arv, _mostraContato, NULL);
	return 1;
}


/**
 */
int processoMostraArvore(AgendaInfo *agenda) {
	printf("---Arvore de contatos---\n\n");
	imprimeArvore(agenda->arv);
	return 1;
}
