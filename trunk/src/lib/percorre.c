/**
 */
#include "structure.h"
#include "listdesc.h"

#include "percorre.h"


/**
 */
void percorrePrefixado(ArvoreMista *arv, void (*visita)(ArvoreMista *, void *), void *param) {
	if (arv) {
		(*visita)(arv, param);
		percorrePrefixado(arv->esq, visita, param);
		percorrePrefixado(arv->dir, visita, param);
	}
}

/**
 */
void percorreInfixado(ArvoreMista *arv, void (*visita)(ArvoreMista *, void *), void *param) {
	if (arv) {
		percorrePrefixado(arv->esq, visita, param);
		(*visita)(arv, param);
		percorrePrefixado(arv->dir, visita, param);
	}
}

/**
 */
void percorrePosfixado(ArvoreMista *arv, void (*visita)(ArvoreMista *, void *), void *param) {
	if (arv) {
		percorrePrefixado(arv->esq, visita, param);
		percorrePrefixado(arv->dir, visita, param);
		(*visita)(arv, param);
	}
}

/**
 */
void _percorrePorNivel(descritorLista *dlista, void (*visita)(ArvoreMista *, void *), void *param) {
	ArvoreMista *arv;
	descValor *dv;

	dv = removeNoEsquerdaLista(dlista);

	if (dv) {
		arv = (ArvoreMista *) dv->dado;
		liberaDescValor(dv);

		(*visita)(arv, param);

		if (arv->esq) {
			/* Adiciona filho esquerdo na fila */
			dv = criaDescValor(arv->esq, sizeof(ArvoreMista *));
			insereNoDireitaLista(dlista, dv);
			liberaDescValor(dv);
		}

		if (arv->dir) {
			/* Adiciona filho direito na fila */
			dv = criaDescValor(arv->dir, sizeof(ArvoreMista *));
			insereNoDireitaLista(dlista, dv);
			liberaDescValor(dv);
		}

		/* Chama recursivamente esta funcao, pegando os elementos da fila... */
		_percorrePorNivel(dlista, visita, param);
	}
}

/**
 */
void percorrePorNivel(ArvoreMista *arv, void (*visita)(ArvoreMista *, void *), void *param) {
	descritorLista *dlista = criaDescritorLista();
	descValor *dv = criaDescValor(arv, sizeof(ArvoreMista *));

	/* Insere a raiz na fila */
	insereNoDireitaLista(dlista, dv);
	_percorrePorNivel(dlista, visita, param);

	liberaDescValor(dv);
	liberaDescritorLista(dlista);
}

