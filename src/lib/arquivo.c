#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "structure.h"
#include "arquivo.h"
#include "processos.h"
#include "percorre.h"


#define DIR "dados/"
#define BUFFER 100


/**
 */
void gravaContato(ArvoreMista *arv, void *param) {
    FILE *arquivo = (FILE *) param;
    fprintf( arquivo, "%s#%s\n", arv->contato->nome, arv->contato->telefone );
}

/**
	salva arquivo temporario para usar nas operacoes de salvar nova agenda
	nao pondo em risco os arquivos verdadeiros
*/
void tempFile( ArvoreMista *arv ) {

	FILE *arquivo;
	if ( arv != NULL && ( arquivo = fopen("temp.dat~", "a" ) ) != NULL )
	{
    	 percorrePrefixado(arv, gravaContato, (FILE *) arquivo);
	     fclose(arquivo);
	}
}


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
			if ( !feof(arq1) ) {
        		putc( caracter, arq2 );
			}
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

    if (access(DIR, F_OK) != 0) {
#ifdef LINUX
        mkdir(DIR, 0777);
#else
        mkdir(DIR);
#endif
    }

	if ( copiaArquivo("temp.dat~", nomeBackup) && copiaArquivo("temp.dat~", nomeAgenda) ) {
		remove("temp.dat~");
		return 1;
	}
	return 0;
}


AgendaInfo *import( char *nomeAgenda, char ehAVL ) {
	FILE *arquivo;
	ArvoreMista *arvore = NULL;
	ArvoreMista *noh = NULL;
	AgendaInfo *info = NULL;
	Contato *contato = NULL;

	char linha[BUFFER];
	char nome[50] = "";
	char telefone[50] = "";

	char agenda[50];
	char backup[50];

	int index = 0;
	int index2 = 0;


	strcpy( agenda, nomeAgenda );
	strcpy( backup, nomeAgenda );

	strcat( agenda, ".dat" );
	strcat( backup, ".bkp" );

	//tenta abrir agenda se nao conseguir tenta abrir backup
	if ( ( arquivo = fopen( agenda, "r")) == NULL ) {
		if ( ( arquivo = fopen( backup, "r" )) == NULL ) {
			return NULL;
		}
	}


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

		contato = malloc( sizeof( Contato ) );
		strcpy( contato->nome, nome  );
		strcpy( contato->telefone, telefone  );


		noh = malloc(sizeof(ArvoreMista));
		noh->contato = contato;
		noh->esq = noh->dir = NULL;
		noh->fb = BAL;
		noh->ehAVL = ehAVL;
		arvore = insereNoh( arvore, noh );

	}

	info = inicAgendaInfo();
	info->ehAVL = ehAVL;
	info->arv = arvore;

	return info;
}

