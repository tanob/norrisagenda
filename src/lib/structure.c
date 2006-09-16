/**
	Modulo com funcoes para lidar com as estruturas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"
#include "io.h"
#include "interface.h"

/**
	Prototipos
 */
ArvoreMista *balanceDireita(ArvoreMista *, char *);
ArvoreMista *balanceEsquerda(ArvoreMista *, char *);
ArvoreMista *rebalanceEsquerda(ArvoreMista *, char *);
ArvoreMista *rebalanceDireita(ArvoreMista *, char *);
ArvoreMista *_insereNoh(ArvoreMista *, ArvoreMista *, char *);
int _removeNoh(const char *, ArvoreMista **, char *);


/**
 */
AgendaInfo *inicAgendaInfo() {
	AgendaInfo *nova = malloc(sizeof(AgendaInfo));

	if (nova) {
		nova->arquivo = NULL;
		nova->ehAVL = 0;
		nova->foiAlterada = 0;

		nova->arv = NULL;
	}

	return nova;
}

/**
 */
void finalizaAgendaInfo(AgendaInfo *agenda) {
	if (agenda) {
		if (agenda->arv) {
			finalizaArvoreMista(agenda->arv);
		}

		free(agenda);
	}
}

/**
 */
void finalizaArvoreMista(ArvoreMista *am) {
	if (am) {
		/* TODO: fazer funcao para percorrer pos-fixado, liberando as memorias alocadas */
	}
}

/**
	Insere um noh na arvore mista, caso esta seja AVL, entao insere
	e faz o balanceamento
 */
ArvoreMista *insereNoh(ArvoreMista *raiz, ArvoreMista *noh) {
	char cresceu = 0;
	return _insereNoh(raiz, noh, &cresceu);
}

/**
 */
ArvoreMista *_insereNoh(ArvoreMista *raiz, ArvoreMista *noh, char *cresceu) {
	if (!raiz) {
		raiz = noh;
		raiz->esq = raiz->dir = NULL;
		raiz->fb = BAL;
		*cresceu = 1;
	}
	else {
		int cmp = strcasecmp(noh->contato->nome, raiz->contato->nome);

		if (cmp == 0) {
			/* Contato jah existente, nao se faz nada */
		}
		else if (cmp < 0) {
			raiz->esq = _insereNoh(raiz->esq, noh, cresceu);
		}
		else /* cmp > 0 */ {
			raiz->dir = _insereNoh(raiz->dir, noh, cresceu);
		}

		if (raiz->ehAVL && *cresceu && (cmp != 0)) {
			switch(raiz->fb) {
				case BAL:
					/* Se a arvore estava balanceada, e foi inserido um noh,
					   a arvore deve ficar balanceada para o lado que foi inserido o noh */
					raiz->fb = (cmp < 0) ? BE : BD;
					break;

				case BD:
					if (cmp < 0) {
						raiz->fb = BAL;
						*cresceu = 0;
					}
					else {
						raiz = balanceDireita(raiz, cresceu);
					}
					break;

				case BE:
					if (cmp < 0) {
						raiz = balanceEsquerda(raiz, cresceu);
					}
					else {
						raiz->fb = BAL;
						*cresceu = 0;
					}
					break;
			}
		}
	}

	return raiz;
}

/**
 */
int removeNoh(const char *elemento, ArvoreMista **raiz) {
	char diminuiu = 0;
	return _removeNoh(elemento, raiz, &diminuiu);
}

/**
 */
int _removeNoh(const char *elemento, ArvoreMista **raiz, char *diminuiu)
{
	int result = -1, cmp;
	char menorsubarv = 0;
	ArvoreMista *subarv;

	if (!raiz || !(*raiz) || !(*raiz)->contato) {
		/* fprintf(stderr, "removeNoh: !raiz || !(*raiz) || !(*raiz)->contato\n"); */
		return result;
	}

	cmp = strcasecmp(elemento, (*raiz)->contato->nome);

	if (!cmp) {
		if ((*raiz)->esq && (*raiz)->dir) {
			ArvoreMista *pred;
			void *tmp;

			for (pred = (*raiz)->esq; pred->dir; pred = pred->dir) ;

			tmp = (*raiz)->contato;
			(*raiz)->contato = pred->contato;
			pred->contato = tmp;

			subarv = (*raiz)->esq;
			result = _removeNoh(elemento, &subarv, &menorsubarv);
			(*raiz)->esq = subarv;

			if (menorsubarv) {
				switch((*raiz)->fb) {
					case BD:
						*raiz = rebalanceDireita(*raiz, diminuiu);
						break;

					case BAL:
						(*raiz)->fb = BD;
						*diminuiu = 0;
						break;

					case BE:
						(*raiz)->fb = BAL;
						*diminuiu = 1;
						break;
				}
			}
		}
		else {
			subarv = (!(*raiz)->esq) ? (*raiz)->dir : (*raiz)->esq;
			free((*raiz)->contato);
			free(*raiz);

			*raiz = subarv;
			*diminuiu = 1;
			result = 1;
		}
	}
	else if (cmp < 0) {
		subarv = (*raiz)->esq;
		result = _removeNoh(elemento, &subarv, &menorsubarv);
		(*raiz)->esq = subarv;

		if (menorsubarv) {
			switch((*raiz)->fb) {
				case BD:
					*raiz = rebalanceDireita(*raiz, diminuiu);
					break;

				case BAL:
					(*raiz)->fb = BD;
					*diminuiu = 0;
					break;

				case BE:
					(*raiz)->fb = BAL;
					*diminuiu = 1;
					break;
			}
		}
	}
	else {
		subarv = (*raiz)->dir;
		result = _removeNoh(elemento, &subarv, &menorsubarv);
		(*raiz)->dir = subarv;

		if (menorsubarv) {
			switch((*raiz)->fb) {
				case BE:
					*raiz = rebalanceEsquerda(*raiz, diminuiu);
					break;

				case BAL:
					(*raiz)->fb = BE;
					*diminuiu = 0;
					break;

				case BD:
					(*raiz)->fb = BAL;
					*diminuiu = 1;
					break;
			}
		}
	}

	return result;
}

/**
 */
ArvoreMista *rotacionaDireita(ArvoreMista *p) {
	ArvoreMista *esqp;

	if (!p || !p->esq) {
		fprintf(stderr, "rotacionaEsquerda: !p || !p->esq\n");
	}
	else {
		esqp = p->esq;
		p->esq = esqp->dir;
		esqp->dir = p;
	}

	return esqp;
}

/**
 */
ArvoreMista *rotacionaEsquerda(ArvoreMista *p) {
	ArvoreMista *dirp;

	if (!p || !p->dir) {
		/* Imprime mensagem de debug na saida de erro */
		fprintf(stderr, "rotacionaDireita: !p || !p->dir\n");
	}
	else {
		dirp = p->dir;
		p->dir = dirp->esq;
		dirp->esq = p;
	}

	return dirp;
}

/**
 */
ArvoreMista *balanceEsquerda(ArvoreMista *raiz, char *cresceu) {
	ArvoreMista *esqraiz = raiz->esq;
	ArvoreMista *diresq;

	switch(esqraiz->fb) {
		case BE:
			raiz->fb = esqraiz->fb = BAL;
			raiz = rotacionaDireita(raiz);
			*cresceu = 0;
			break;

		case BD:
			diresq = esqraiz->dir;

			switch(diresq->fb) {
				case BAL:
					raiz->fb = esqraiz->fb = BAL;
					break;

				case BE:
					raiz->fb = BE;
					esqraiz->fb = BAL;
					break;

				case BD:
					raiz->fb = BAL;
					esqraiz->fb = BD;
					break;
			}

			diresq->fb = BAL;
			raiz->esq = rotacionaEsquerda(esqraiz);
			raiz = rotacionaDireita(raiz);
			*cresceu = 0;
	}

	return raiz;
}

/**
 */
ArvoreMista *balanceDireita(ArvoreMista *raiz, char *cresceu) {
	ArvoreMista *dirraiz = raiz->dir;
	ArvoreMista *esqdir;

	switch(dirraiz->fb) {
		case BD:
			raiz->fb = dirraiz->fb = BAL;
			raiz = rotacionaEsquerda(raiz);
			*cresceu = 0;
			break;

		case BE:
			esqdir = dirraiz->esq;

			switch(esqdir->fb) {
				case BAL:
					raiz->fb = dirraiz->fb = BAL;
					break;

				case BD:
					raiz->fb = BE;
					dirraiz->fb = BAL;
					break;

				case BE:
					raiz->fb = BAL;
					dirraiz->fb = BD;
					break;
			}

			esqdir->fb = BAL;
			raiz->dir = rotacionaDireita(dirraiz);
			raiz = rotacionaEsquerda(raiz);
			*cresceu = 0;
	}

	return raiz;
}

/**
 */
ArvoreMista *rebalanceDireita(ArvoreMista *raiz, char *diminuiu)
{
	ArvoreMista *dirsub, *esqdirsub;

	if (!raiz || !raiz->dir) {
		fprintf(stderr, "rebalanceDireita: !raiz || !raiz->left\n");
		return;
	}

	dirsub = raiz->dir;

	switch(dirsub->fb) {
		case BAL:
			raiz->fb = BD;
			dirsub->fb = BE;
			raiz = rotacionaEsquerda(raiz);
			*diminuiu = 0;
			break;

		case BD:
			raiz->fb = dirsub->fb = BAL;
			raiz = rotacionaEsquerda(raiz);
			*diminuiu = 1;
			break;

		case BE:
			esqdirsub = dirsub->esq;

			switch(esqdirsub->fb) {
				case BAL:
					raiz->fb = dirsub->fb = BAL;
					break;

				case BE:
					raiz->fb = BAL;
					dirsub->fb = BD;
					break;

				case BD:
					raiz->fb = BE;
					dirsub->fb = BAL;
					break;
			}

			esqdirsub->fb = BAL;
			dirsub = rotacionaDireita(dirsub);
			raiz->dir = dirsub;
			raiz = rotacionaEsquerda(raiz);
			*diminuiu = 1;

			break;
	}
	
	return raiz;
}

/**
 */
ArvoreMista *rebalanceEsquerda(ArvoreMista *raiz, char *diminuiu)
{
	ArvoreMista *esqsub, *diresqsub;

	if (!raiz || !raiz->esq) {
		fprintf(stderr, "rebalanceEsquerda: !raiz || !raiz->left\n");
		return;
	}

	esqsub = raiz->esq;

	switch(esqsub->fb) {
		case BAL:
			raiz->fb = BE;
			esqsub->fb = BD;
			raiz = rotacionaDireita(raiz);
			*diminuiu = 0;
			break;

		case BE:
			raiz->fb = esqsub->fb = BAL;
			raiz = rotacionaDireita(raiz);
			*diminuiu = 1;
			break;

		case BD:
			diresqsub = esqsub->dir;

			switch(diresqsub->fb) {
				case BAL:
					raiz->fb = esqsub->fb = BAL;
					break;

				case BD:
					raiz->fb = BAL;
					esqsub->fb = BE;
					break;

				case BE:
					raiz->fb = BD;
					esqsub->fb = BAL;
					break;
			}

			diresqsub->fb = BAL;
			esqsub = rotacionaEsquerda(esqsub);
			raiz->esq = esqsub;
			raiz = rotacionaDireita(raiz);
			*diminuiu = 1;

			break;
	}
	
	return raiz;
}

