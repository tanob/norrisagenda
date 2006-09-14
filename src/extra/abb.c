/** 
	TRABALHO ED1 - ARVORE BINARIA DE BUSCA
	10-set-2006	 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tamanho da string lida do arquivo
#define BUFFER 150


typedef struct _Arv
{
	struct _Arv *esq;
	struct _Arv *dir;
	int info;
} Arv;



/** FUNCAO INTERNA PRA DEBUGAR  */
void trace()
{
	printf("\n\n*********************\n\n");
	
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
	FUNCAO QUE CLASSIFICA UM NO
	PARAMETRO TIPO:	
	0 = folha
	1 = esquerda
	2 = direita
	3 = direta e esquerda
	-1 = NULL	
*/
int getType( Arv **arvore )		
{
	Arv *raiz;
	raiz = *arvore;					
	if ( raiz == NULL ) return -1;	
	if ( raiz->esq == NULL && raiz->dir == NULL ) return 0;
	if ( raiz->esq != NULL && raiz->dir == NULL ) return 1;
	if ( raiz->esq == NULL && raiz->dir != NULL ) return 2;
	if ( raiz->esq != NULL && raiz->dir != NULL ) return 3;	
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
	FUNCAO PARA PROCURA DADO DA ARVORE
	RETORNA O PONTEIRO PAR AO NOH ENCONTRADO	
*/
Arv *busca( Arv **arvore, Arv **pai, int info )
{
	Arv *buscando;
	Arv *fpai = NULL;
	int flag = 0; // TRUE = chegou ao fim e nao achou
	
	buscando = *arvore;
	
	while ( buscando != NULL && buscando->info != info )	
	{
		fpai = buscando;
		if ( buscando->info > info ) 
		{
			if ( buscando->esq != NULL ) 
			{ 
				buscando = buscando->esq; 
			}
			else
			{
				flag = 1;
				break; 
			}
		}
		else if ( buscando->info < info ) 
		{
			if ( buscando->dir != NULL ) 
			{
				buscando = buscando->dir;
			}
			else
			{
				flag = 1;
				break;
			}
		}
	}
			
	*pai = fpai;
	if ( !flag )
	{
		return buscando;
	}
	else
	{
		*pai = NULL;
		return NULL;
	}
}



/** 
	RETORNA O ITEM MAIS A ESQUERDA DE UMA ARVORE PASSADA
	POR PARAMETRO E SETA O PARAMETRO PAI COM O ENDERECO
	DO "PAI" DA FOLHA
*/
Arv *getFolha( Arv **arvore, Arv **pai )
{
	Arv *fpai = NULL;
	Arv *raiz;
	int tipo; // tipo do noh
	
	raiz = *arvore;
	
	if ( raiz != NULL )
	{
		// verifica o tipo do noh
		tipo = getType( &raiz );
		
		// se for folha retorna ele mesmo, senão busca item mais a esquerda
		if ( tipo == 0 )
		{
			return raiz;
		}
		else
		{
			while ( raiz->esq != NULL )		
			{
				fpai = raiz;
				raiz = raiz->esq;
			}
			*pai = fpai;
			return raiz;
		}
	}
	else
	{
		*pai = NULL;
		return NULL;	
	}
	
}





/** 
	FUNCAO PARA SALVAR A ARVORE EM UM ARQUIVO TEMPORARIO
*/
int tempFile( Arv **arvore )
{
	Arv *raiz;
	Arv *info;		
	FILE *arq;
	
	raiz = *arvore;
		
	// se nao conseguir arquivo cria um
	if ( (arq = fopen("temp.dat~", "a")) == NULL )
	{
		return 0;
	}
	
	// se nao conseguiu abrir o arquivo ou nao tem informacao
	if ( arq == NULL || raiz == NULL )
	{
		return 0;
	}
	else
	{
		// salva informacoes no arquivo
		fprintf( arq, "%d\n", raiz->info  );
		fclose( arq );
		tempFile( &(raiz->esq) );
		tempFile( &(raiz->dir) );		
	}
}


/** 
	FUNCAO PARA COPIAR UM ARQUIVO PARA O OUTRO
*/
int copiaArquivo( char *nomeArq1, char *nomeArq2 )
{
	FILE *arq1;
	FILE *arq2;
	char caracter;
	
	arq1 = fopen( nomeArq1, "r" );
	arq2 = fopen( nomeArq2, "w" );
		
	// se nao obteve sucesso na abertura de alguma arquivo sai
	if ( arq1 == NULL || arq2 == NULL )
	{
		printf("\n\nERROO\n\n");
	}
	else
	{
		while ( !feof( arq1 ) )
      	{
        	caracter = getc( arq1 );
        	putc( caracter, arq2 );
      	}
    	fclose( arq1 );
		fclose( arq2 );		
	}
	
}

/** 
	FUNCAO PARA ATUALIZAR A MUDANCA E CRIAR ARQUIVO REAL
*/
int createFile( Arv **arvore )
{
	Arv *raiz;
	FILE *arquivo;
	FILE *temp;
	FILE *bkp;	
	raiz = *arvore;
	
	// limpa o arquivo temporario
	temp = fopen("temp.dat~", "w");
	if ( temp == NULL ) 
	{
		return 0;
	}
	else
	{
		fclose( temp );
	}
		
	// cria arquivo temporario se nao conseguir sai
	if ( tempFile( &raiz ) == 0 )
	{
		return 0;
	}
	else
	{
		// cria arquivo backup
		if ( copiaArquivo("temp.dat~", "agenda.dat.bkp") )
		{
			return 0;
		}
		
		// subsitui arquivo atual da agenda pelo novo
		if ( copiaArquivo("temp.dat~", "agenda.dat") )
		{
			return 0;
		}
		
		// remove arquivo temporario
		remove("temp.dat~");
		
		return 1;
	}
}


/**
	FUNCAO PARA CRIAR ARVORE APARTIR DE ARQUIVO CRIADO
*/
Arv *importAgenda( char *arquivo )
{
	FILE *arq;
	char linha[ BUFFER ];
	int info;
	Arv *arvore = NULL;
	
	arq = fopen( arquivo, "r" );
	
	if ( arq == NULL )
	{
		return NULL;
	}
	
	while ( !feof( arq ) )
	{
		fgets( linha, BUFFER, arq );		
		info = atoi( linha );
		tInsere( &arvore, info );
	}	
	fclose( arq );
	return arvore;
}




/**
	FUNCAO PARA REMOVER DADO DA ARVORE
*/

int tRemove( Arv **arvore, int info )
{	
	Arv *remover;  //sera removido	
	Arv *raiz;     //toda a arvore
	Arv *novo;     //novo item
	Arv *pai;      //pai do que sera removido
	Arv *paifolha; // pai da folha
	int tipo;      //tipo do no que sera removido   
	
	raiz = *arvore;
	remover = busca( &raiz, &pai, info );
	
	if ( remover != NULL )
	{
		tipo = getType( &remover );
	}
	
	// removendo folga
	if ( tipo == 0 )
	{
		if ( pai->esq == remover ) { pai->esq = NULL; }
		if ( pai->dir == remover ) { pai->dir = NULL; }
		free( remover );
		return 1;		
	}
	
	// removendo com item a esquerda
	if ( tipo == 1 )
	{
		novo = remover->esq;
		if ( pai->esq == remover ) { pai->esq = novo; }
		if ( pai->dir == remover ) { pai->dir = novo; }
		free( remover );		
	}
	
		// removendo com item a direta
	if ( tipo == 2 )
	{
		novo = remover->dir;
		if ( pai->esq == remover ) { pai->esq = novo; }
		if ( pai->dir == remover ) { pai->dir = novo; }
		free( remover );	
	}
	
	// removendo com item a esquerda e a direita
	if ( tipo == 3 )
	{
		
		novo = getFolha( &(remover->dir), &paifolha );
				
		if ( paifolha == NULL )
		{
			remover->info = novo->info;			
			if ( remover->dir == novo )
			{
				remover->dir = NULL;
			}		
			
			if ( remover->esq == novo )
			{
				remover->esq = NULL;
			}			
			return 1;
		}
		else
		{
			remover->info = novo->info;			
			paifolha->esq = NULL;
			return 1;
		}
		
		return 0;
				
	}	
}


int main()
{
	Arv *arvore = NULL;		
	Arv *fileArvore = NULL;	
	Arv *raiz = NULL;		
	
	tInsere( &arvore, 10 );
	tInsere( &arvore, 5 );
	tInsere( &arvore, 6 );
	tInsere( &arvore, 2 );	
	tInsere( &arvore, 15 );
	tInsere( &arvore, 13 );	
	tInsere( &arvore, 69 );		
	tInsere( &arvore, 80 );
	tInsere( &arvore, 50 );
	tInsere( &arvore, 1 );
	tInsere( &arvore, 40 );
		
	raiz = arvore;	
	createFile( &raiz );
	fileArvore = importAgenda( "agenda.dat" );
	createFile( &fileArvore );
	return 0;
}
			