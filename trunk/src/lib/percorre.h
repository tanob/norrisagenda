/**
	Arquivo de cabecalho do modulo que define os caminhamentos
*/

#ifndef _PERCORRE_H

#define _PERCORRE_H

void percorrePrefixado(ArvoreMista *arv, void (*visita)(ArvoreMista *, void *), void *param);
void percorreInfixado(ArvoreMista *arv, void (*visita)(ArvoreMista *, void *), void *param);
void percorrePosfixado(ArvoreMista *arv, void (*visita)(ArvoreMista *, void *), void *param);
void percorrePorNivel(ArvoreMista *arv, void (*visita)(ArvoreMista *, void *), void *param);

#endif /* !_PERCORRE_H */
