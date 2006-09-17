/**
	Arquivo de cabecalho do modulo structure
*/

#ifndef _STRUCTURE_H

#include <stdio.h>

#define _STRUCTURE_H

/**
	Estrutura para os dados do contato
 */

typedef struct _Contato Contato;

struct _Contato {
	char nome[50];
	char telefone[30];
};

/**
	Define constantes para trabalhar com os fatores de balanceamento
 */
#define BAL 0 /* Esta balanceada */
#define BD 1 /* Balanceada para direita */
#define BE -1 /* Balanceada para esquerda */

/**
	Estrutura para comportar tanto uma arvore balanceada, quanto
	uma nao-balanceada
 */
typedef struct _ArvoreMista ArvoreMista;

struct _ArvoreMista {
	Contato *contato;
	ArvoreMista *esq;
	ArvoreMista *dir;
	short int fb; /* Usado apenas quando for balanceada */
	char ehAVL; /* Indica se a arvore eh AVL */
};

/**
	Estrutura util para se reunir os dados usados para uma agenda
 */
typedef struct _AgendaInfo {
	FILE *arquivo; /* Manipulador do arquivo */

	char ehAVL; /* Indica se eh balanceada ou nao */
	char foiAlterada; /* Se a agenda foi aberta e alterada e suas alteracoes ainda nao foram salvas */

	ArvoreMista *arv;

} AgendaInfo;


AgendaInfo *inicAgendaInfo();
void finalizaAgendaInfo(AgendaInfo *);
void finalizaArvoreMista(ArvoreMista *);
ArvoreMista *insereNoh(ArvoreMista *, ArvoreMista *);
int removeNoh(const char *, ArvoreMista **);
int alturaArvore(ArvoreMista *arv);
void imprimeArvore(ArvoreMista *arv);
void balanceEstatico(ArvoreMista **arv);

#endif /* !_STRUCTURE_H */
