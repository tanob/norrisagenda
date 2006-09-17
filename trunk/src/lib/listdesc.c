/**
	Modulo que trabalha com listas encadeadas com descritor
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listdesc.h"


/**
 */
descValor *criaDescValor(void *dado, const int tamanho) {
	descValor *p = malloc(sizeof(descValor));

	p->tamanho = tamanho;
	p->dado = dado; /* malloc(sizeof(tamanho));
	memcpy(p->dado, dado, tamanho); */

	return p;
}

/**
 */
descritorLista *criaDescritorLista() {
               descritorLista *nova = malloc(sizeof(descritorLista));
               nova->inicio = NULL;
               nova->final = NULL;
               nova->tamanho = 0;
               return nova;
}

/**
 */
int tamanhoLista(descritorLista *p) {
  return p->tamanho;
}

/**
 */
void insereNoEsquerdaLista(descritorLista *dlista, const descValor *valor) {
     nodoLista *novoNodo = malloc(sizeof(nodoLista));

	novoNodo->valor = criaDescValor(valor->dado, valor->tamanho);
     novoNodo->prox = dlista->inicio;

     if (dlista->tamanho <= 0) {
        dlista->inicio = novoNodo;
        dlista->final = novoNodo;
        dlista->tamanho = 1;
     }
     else {
          dlista->inicio = novoNodo;
          dlista->tamanho++;
     }
}

/**
 */
void insereNoDireitaLista(descritorLista *dlista, const descValor *valor) {
     nodoLista *novoNodo = malloc(sizeof(nodoLista));

	novoNodo->valor = criaDescValor(valor->dado, valor->tamanho);
     novoNodo->prox = NULL;

     if (dlista->tamanho <= 0) {
        dlista->inicio = novoNodo;
        dlista->final = novoNodo;
        dlista->tamanho = 1;
     }
     else {
          dlista->final->prox = novoNodo;
          dlista->final = novoNodo;
          dlista->tamanho++;
     }
}

/**
 */
descValor *removeNoEsquerdaLista(descritorLista *dlista) {
	descValor *valor = NULL;

     if (dlista->tamanho > 0) {
        nodoLista *nodo = dlista->inicio;

        if (dlista->tamanho == 1) {
           dlista->inicio = NULL;
           dlista->final = NULL;
        }
        else {
             dlista->inicio = dlista->inicio->prox;
        }

		valor = nodo->valor;

        liberaNodo(nodo);
        dlista->tamanho--;
     }

	 return valor;
}

descValor *removeNoDireitaLista(descritorLista *dlista) {
	descValor *valor = NULL;

     if (dlista->tamanho > 0) {
     		nodoLista *nodo;

        if (dlista->tamanho == 1) {
        	 nodo = dlista->inicio;
           dlista->inicio = NULL;
           dlista->final = NULL;
        }
        else {
             nodoLista *nodoAnterior;

             for (nodo=dlista->inicio; nodo->prox != NULL; nodoAnterior=nodo, nodo=nodo->prox) ;

             nodoAnterior->prox = NULL;
        }

		valor = nodo->valor;

        liberaNodo(nodo);
        dlista->tamanho--;
     }

	 return valor;
}

/**
 */
descValor *buscaNoPosicao(descritorLista *dl, int k) {
  nodoLista *nodo;
  descValor *dv = NULL;
  
  if (k < dl->tamanho) {
    for (nodo=dl->inicio; nodo && k > 0; nodo=nodo->prox, k--) ;
    
    if (!k) {
      dv = nodo->valor;
    }
  }
  
  return dv;
}

/**
 */
void liberaNodo(nodoLista *p) {
	free(p);
}

/**
 */
void liberaDescValor(descValor *p) {
	/* free(p->dado); */
	free(p);
}

/**
 */
void liberaDescritorLista(descritorLista *dl) {
	nodoLista *p = dl->inicio, *aux;

	while (p) {
		aux = p->prox;
		liberaDescValor(p->valor);
		liberaNodo(p);
		p = aux;
	}

	free(dl);
}


/**
   Main.
 */
/*
int main(int argc, char **argv) {
	descritorLista *dlista = criaDescritorLista();
	nodoLista *nl, *aux;
	descValor *dv;
	int tmp, a=1, b=2, c=3, d=4, e=0;

	dv = criaDescValor(&a, sizeof(int));
	insereNoDireitaLista(dlista, dv);
	liberaDescValor(dv);

	dv = criaDescValor(&b, sizeof(int));
	insereNoDireitaLista(dlista, dv);
	liberaDescValor(dv);

	dv = criaDescValor(&c, sizeof(int));
	insereNoDireitaLista(dlista, dv);
	liberaDescValor(dv);

	dv = criaDescValor(&d, sizeof(int));
	insereNoDireitaLista(dlista, dv);
	liberaDescValor(dv);

	dv = criaDescValor(&e, sizeof(int));
	insereNoEsquerdaLista(dlista, dv);
	liberaDescValor(dv);

	for (aux=nl=dlista->inicio; aux != NULL; nl=aux) {
		tmp = *((int *) nl->valor->dado);
		printf("%d\n", tmp);

		aux = nl->prox;
	}
	
	dv = buscaNoPosicao(dlista, 2);
	if (dv) {
	  tmp = *((int *) dv->dado);
	  printf("retornado: %d\n", tmp);
	}
	else {
	 printf("not found\n");
	}

	liberaDescritorLista(dlista);

	return 0;
}
*/
