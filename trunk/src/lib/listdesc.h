/**
	Arquivo de cabecalho do modulo que trabalha com listas encadeadas com descritor
*/

#ifndef _LISTDESC_H

#define _LISTDESC_H

/**
	Estruturas
 */

typedef struct _descValor descValor;
struct _descValor {
	void *dado;
	int tamanho;
};

typedef struct _nodoLista nodoLista;
struct _nodoLista {
	descValor *valor;
       nodoLista *prox;
};

typedef struct _descritorLista descritorLista;
struct _descritorLista {
       nodoLista *inicio;
       nodoLista *final;
       int tamanho;
};

/**
	Operacoes
 */

descValor *criaDescValor(void *dado, const int tamanho);
descritorLista *criaDescritorLista();

int tamanhoLista(descritorLista *p);
descValor *buscaNoPosicao(descritorLista *dl, int k);

void insereNoEsquerdaLista(descritorLista *dlista, const descValor *valor);
void insereNoDireitaLista(descritorLista *dlista, const descValor *valor);

descValor *removeNoEsquerdaLista(descritorLista *dlista);
descValor *removeNoDireitaLista(descritorLista *dlista);

void liberaNodo(nodoLista *p);
void liberaDescValor(descValor *p);
void liberaDescritorLista(descritorLista *dl);


#endif /* !_LISTDESC_H */
