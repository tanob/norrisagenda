/**
	Arquivo de cabecalho do modulo io
*/

#ifndef _IO_H

#define _IO_H

int leOpcao(int *opcoesValidas, char *valido);
int leOpcaoValida(char *prompt, int *opcoesValidas, char *msgErro);
char arquivoExiste(char *caminho);

#endif /* !_IO_H */
