#include"latex.h"
#include<stdio.h>
#include<stdarg.h>
#include<stdbool.h>
#include<stdint.h>
#include<string.h>

tabela_tex inicializa(const char *nome_arq, uint8_t num_colunas,
			const char *capt){
	tabela_tex inicia={	NULL,
				num_colunas,
			       	0U};

	do{
		inicia.arq_tabela = fopen(nome_arq,"w");
	}while(inicia.arq_tabela == NULL);

	fputs(inicio, inicia.arq_tabela);	//begin{table}[(!)htp]

#ifndef TITULO_NO_FINAL
	fputs(caption, inicia.arq_tabela);
	fputs(capt, inicia.arq_tabela);
	fputs("}\n", inicia.arq_tabela);
#else
	fputs(capt, inicia.arq_tabela);
#endif

	fputs(inicio_tabular, inicia.arq_tabela);
#ifdef LINHAS_VERTICAIS
	fputc('c', inicia.arq_tabela);

	for(uint8_t i = 1U; i<inicia.num_col; i++)
		fputs("|c", inicia.arq_tabela);
#else
	for(uint8_t i = 0U; i<inicia.num_col; i++)
		fputc('c', inicia.arq_tabela);
#endif

	fputs(end_inicio, inicia.arq_tabela);
	return inicia;
}



void nome_colunas(tabela_tex tabela, ...){
	va_list args;
	va_start(args, tabela);	// Inicia va_list

	for(uint8_t i = 0; i < tabela.num_col;){
		fputs("\t\t", tabela.arq_tabela);
		fputs(va_arg(args, char*), tabela.arq_tabela);
		fputs(++i < tabela.num_col ? "\t&\n" : "\t\\\\\n",
			tabela.arq_tabela);             //Última linha?
	}

	va_end(args);	// Termina va_list
	fputs(pos_inicio, tabela.arq_tabela);
}



void printoneline(tabela_tex *tabela, char *format, ...){
	va_list args;
	va_start(args, format);

	char copia_format[strlen(format)];
	strcpy(copia_format, format);

	fprintf( (*tabela).arq_tabela, "\t\t%%Linha %hhu\n\t\t",
		 ++(*tabela).linhas_printadas);

	for(uint8_t i = 0U, cont_col = 0U, ini = 0U;
	*copia_format && cont_col < (*tabela).num_col;){
		while(	*(copia_format+i)!=' ' &&
			*(copia_format+i)!='\t' &&
			*(copia_format+i)) i++;
		*(copia_format+i) = '\0';

		vfprintf((*tabela).arq_tabela, copia_format+ini, args);
		fputs(++cont_col < (*tabela).num_col ? "&\n\t\t" : "\\\\\n\n",
			(*tabela).arq_tabela);
		ini = ++i;
	}

	va_end(args);
}



void printoneline_v2(tabela_tex *tabela, ...){
	va_list args;
	va_start(args, tabela);

	fprintf((*tabela).arq_tabela, "\t\t%%Linha %hhu\n\t\t",
		++(*tabela).linhas_printadas);

	for(uint8_t cont_col = 0U; cont_col<(*tabela).num_col;){
		vfprintf((*tabela).arq_tabela, va_arg(args, char*), args);
		fputs(++cont_col<(*tabela).num_col ? "&\n\t\t" : "\\\\\n\n",
			(*tabela).arq_tabela);
	}

	va_end(args);
}



/*
void printlines(tabela_tex *tabela, uint8_t num_linhas, ...){
	va_list args;
	va_start(args, num_linhas);

	void (*argumentos)[(*tabela).num_col<<1U];

	for(uint8_t i = 0; i < (*tabela).num_col << 1U; i++){
		argumentos[i] = va_arg(args, void*);
	}

	for(uint8_t i=0;)
	for(uint8_t j=0;)

	va_end(args);
}
*/


void fechatabela(tabela_tex tabela, const char *rodape, const char *label){
	fputs(comeco_final, tabela.arq_tabela);

#ifdef TITULO_NO_FINAL
	fputs(caption, tabela.arq_tabela);
#endif

	fputs(small, tabela.arq_tabela);
	fputs(rodape, tabela.arq_tabela);


	if(*label){
		fputs(label_str, tabela.arq_tabela);
		fputs(label, tabela.arq_tabela);
	}

	fputs(fim_final, tabela.arq_tabela);
	fclose(tabela.arq_tabela);
}
