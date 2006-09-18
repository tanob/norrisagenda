#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"
#include "arquivo.h"

#define DIR "dados/"
#define BUFFER 100


/** 
	salva arquivo temporário para usar nas operações de salvar nova agenda
	nao pondo em risco os arquivos verdadeiros
*/
void tempFile( ArvoreMista *arv ) {	
	
	FILE *arquivo;
	if ( ( arquivo = fopen("temp.dat~", "a" ) ) != NULL && arv != NULL )
	{
		fprintf( arquivo, "%s#%s\n", arv->contato->nome, arv->contato->telefone );
		fclose( arquivo );
		tempFile( arv->esq );
		tempFile( arv->dir );		
	}		
}


/*
// inclui o indice avisando se é AVL ou não
void indice( AgendaInfo *agenda ) {
	
	FILE *arquivo;
	
	if ( arquivo = fopen("temp.dat~", "a") ) {
		if ( agenda->ehAVL == 1 ) {
			fprintf( arquivo, "##1\n" );
		} else {
			fprintf( arquivo, "##0\n" );
		}
		fclose( arquivo );	
	}
}
*/


/** 
	copia o conteudo de um arquivo para o outro
	caso o outro não exista sera criado se existir
	se atualizado(sobrescrito)
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
		return 0;
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
		return 1;
	}
	return 0;	
}

/** 
	salva a agenda em um arquivo nominado como o usuario deseja
	e salva um arquivo de backup com o mesmo nome do arquivo pricipal
	mas como a extensao .bkp
*/
int _salvaArquivo( AgendaInfo *agenda, char *nome ) {
	char nomeAgenda[ 50 ];
	char nomeBackup[ 50 ];
	
	strcpy(nomeAgenda, DIR);
	strcpy(nomeBackup, DIR);
	strcat(nomeAgenda, nome);
	strcat(nomeBackup, nome);
	strcat(nomeAgenda, ".dat");
	strcat(nomeBackup, ".bkp");
		
	remove("temp.dat~");	
	
	tempFile( agenda->arv );	
	
	if ( copiaArquivo("temp.dat~", nomeBackup) && copiaArquivo("temp.dat~", nomeAgenda) ) {
		remove("temp.dat~");
		return 1;
	}	
	return 0; 	
}


AgendaInfo *import( char *nomeAgenda ) {
	FILE *arquivo;
	char linha[BUFFER];
	char nome[50] = "";
	char telefone[50] = "";
	int index = 0;
	int index2 = 0;
		
	//abre arquivo
	arquivo = fopen(nomeAgenda, "r");
	if ( !arquivo ) 
		return NULL;
	
	while ( !feof( arquivo ) ) {
		fgets( linha, BUFFER, arquivo );
			
		// limpa valores
		strcpy( nome, "" );
		strcpy( telefone, "" );
				
		// pega nome
		for ( index = 0; linha[index] != '#'; index++ ) {
			nome[index] = linha[index];
		}
		nome[index] = '\0';
		
		// pega telefone
		for ( index = index + 1, index2 = 0; linha[index] != '\n'; index++, index2++ ) {
			telefone[index2] = linha[index];
		}		
		telefone[index2] = '\0';
		
		// insere no na arvore
		printf("Nome:%s\n", nome);
		printf("Telefone:%s\n\n", telefone);
				
	}		
	getchar();	
	return NULL;
}

