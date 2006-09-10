/** 
	TRABALHO ED1 - ARVORE BINARIA DE BUSCA
	10-set-2006	 
*/

#include <stdio.h>
#include <stdlib.h>


typedef struct _Arv
{
	struct _Arv *esq;
	struct _Arv *dir;
	int info;
} Arv;



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

int main()
{
	Arv *arvore;
	tInsere( &arvore , 5);
	tInsere( &arvore , 6);
	tInsere( &arvore , 2);
	tInsere( &arvore , 1);	
	//system("clear");
	tMostrarCentral( &arvore );
	return 0;
}
