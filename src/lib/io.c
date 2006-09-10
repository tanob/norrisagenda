/**
	Modulo com funcoes de entrada/saida
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

/**
	Le opcoes inteiras do teclado, e as valida contra um vetor
	de opcoes validas. Caso seja lido algo valido, o flag valido
	eh verdadeiro, e eh retornada a opcao lida.
	Caso contrario o flag valido eh falso e eh retornado -1.

	O vetor opcoesValidas deve ter como ultimo elemento -1.
 */
int leOpcao(int *opcoesValidas, char *valido) {
	char buf[512];
	int opcao, tmp;

	*valido = 0;
	fgets(buf, sizeof(buf), stdin);
	tmp = sscanf(buf, "%d", &opcao);

	if (tmp > 0) {
		while (*opcoesValidas != -1) {
			if (*opcoesValidas == opcao) {
				*valido = 1;
				break;
			}

			opcoesValidas++;
		}
	}
	else {
		while (getchar() != '\n') ;
	}

	return *valido ? opcao : -1;
}

/**
	Espera uma escolha do usuario, e verifica se esta escolha
	esta na lista de escolhas validas.
	A funcao recebe uma mensagem para pedir a opcao, e tambem
	uma mensagem de erro caso o usuario entre com dados invalidos.
 */
int leOpcaoValida(char *prompt, int *opcoesValidas, char *msgErro) {
	char valido;
	int opcao;

	do {
		printf("%s", prompt);

		valido = 0;
		opcao = leOpcao(opcoesValidas, &valido);

		if (!valido) {
			printf("%s", msgErro);
		}

	} while(!valido);

	return opcao;
}

/**
	Retorna verdadeiro se o arquivo existe, e falso caso contrario.
 */
char arquivoExiste(char *caminho) {
	FILE *fp = fopen(caminho, "r");
	char existe = (fp != NULL);

	if (existe)
		fclose(fp);

	return existe;
}

