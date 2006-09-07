/**
	Modulo com funcoes de entrada/saida
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

/**
	Le um caractere do teclado, e verifica se
	este se encontra em um vetor de caracteres validos.
	Caso seja valido, eh retornado o caractere lido,
	caso contrario, eh retornado 0 (NULL).
 */
char leOpcao(char *chValidos) {
	char buf[512], opcao, valido=0, *p;

	fgets(buf, sizeof(buf), stdin);
	opcao = buf[0];

	// Verifica se opcao esta entre as validas
	p = chValidos;
	while (*p) {
		if (opcao == *p)
			valido = 1;
		p++;
	}

	return valido ? opcao : 0;
}
