/** 
	TRABALHO ED1 - ARVORE BINARIA DE BUSCA
	10-set-2006	 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _Arv
{
	struct _Arv *esq;
	struct _Arv *dir;
	int info;
} Arv;



/** FUNCAO INTERNA PRA DEBUGAR  */
void trace( char *texto )
{
	printf("\n\ntrace msg >>>>  ");
	puts( texto );	
}

/** 
	FUNCAO SOMENTE PARA VERIFICAR A 
	INTEGRIDADE DA ARVORE: EM ORDEM	
		
*/
void tMostrarCentral( Arv **arvore )
{
	// se arvore existe
	if ( *arvore != NULL )	
	{
		
		tMostrarCentral( &(*arvore)->esq );		
		printf("Informacao: %d\n", (*arvore)->info );	
		tMostrarCentral( &(*arvore)->dir );		
	}			
}

/**
	FUNCAO QUE INSERE NOVO ELEMENTO NA ARVORE
	SE NAO HOUVER AROVORE ELA CRIA A RAIZ
*/
int tInsere( Arv **arvore, int info )
{
	// cria raiz se a arvore não existe
	if ( *arvore == NULL )
	{
		*arvore = malloc( sizeof( Arv ) );
		(*arvore)->info = info;		
		(*arvore)->esq = NULL;		
		(*arvore)->dir = NULL;		
		return 1;	
	}
	// se já ha raiz ela insere
	else
	{
		// insere a esquerda da rais
		if ( (*arvore)->info > info )
		{
			tInsere( &(*arvore)->esq,  info );			
		}
		
		// insere a direita da arvore
		if ( (*arvore)->info < info )
		{
			tInsere( &(*arvore)->dir,  info );			
		}
		
		// se ja tem valor na arvore trata
		if ( (*arvore)->info == info )
		{
			//tratar
		}		
	}
	return 0;
}



/**
	FUNCAO PARA REMOVER DADO DA ARVORE
*/

int tRemove( Arv **arvore, int info )
{	
	Arv *remover; // item a remover
	Arv *pai;     // item pai do que será removido		
	Arv *novo;    // item que irá subsssxxtiruir o nó removido 
	
	// set inicial
	pai = NULL;
	remover = *arvore;
	
	
	
	// procura na arvore até encontrar ou chegar ao fim
	while ( remover != NULL && remover->info != info )
	{
		pai = remover;
		(remover->info > info) ? (remover = remover->esq) : (remover = remover->dir);
	}
	
	// se não existe item retorna FALSE
	if ( remover == NULL ) return 0;
	
	// se existir trata os casos
	
	// verifica se tem somente um filho a direita
	if ( remover->esq == NULL ) 
	{
		novo = remover->dir;
		(pai->esq == remover) ? (pai->esq = novo) : (pai->dir = novo);
		free( remover );
	}
	
	// verifica se tem somente um filho a esquerda
	else if ( remover->dir == NULL )
	{
		novo = remover->esq;
		(pai->esq == remover) ? (pai->esq = novo) : (pai->dir = novo);
		free( remover );
	}
	
	// sacanagem, ele tem os dois filhos
	else
	{
		// implementar
	}	
}

int main()
{
	Arv *arvore = NULL;	
	tInsere( &arvore, 5);
	tInsere( &arvore, 6);
	tInsere( &arvore, 7);
	tInsere( &arvore, 2);
	tInsere( &arvore, 3);
	tInsere( &arvore, 1);
	tRemove( &arvore, 5);	
	
	
	
	
	
	//system("clear");
	tMostrarCentral( &arvore );
	return 0;
}
			