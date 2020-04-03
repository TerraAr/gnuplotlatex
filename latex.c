#include"latex.h"
#include<stdio.h>
#include<stdarg.h>
#include<stdbool.h>
#include<stdint.h>
#include<string.h>

tabela_tex inicializa(const char *nome_arq, uint8_t num_colunas, uint8_t opcoes, const char *capt){
	tabela_tex inicia={	NULL,
				num_colunas,
			       	0U,
			       	opcoes & CAP_FIM,
			       	opcoes & LINHA_EST};

	do{
		inicia.arq_tabela=fopen(nome_arq,"w");
	}while(inicia.arq_tabela==NULL);

	fputs(inicio, inicia.arq_tabela);	//begin{table}
	if(opcoes & FORCE_POS)			//com [! ou só[
		fputc('!', inicia.arq_tabela);
	fputs(inicio_meio, inicia.arq_tabela);	//coloca htp] \centering

	if(!inicia.caption_pos){		//título na tabela
		fputs(caption, inicia.arq_tabela);
		fputs(capt, inicia.arq_tabela);
		fputs("}\n", inicia.arq_tabela);
	}else
		fputs(capt, inicia.arq_tabela);

	fputs(inicio_all, inicia.arq_tabela);
	if(opcoes & COM_LINHAS_VERT){	//coloca linhas verticais entre colunas?
		fputc('c', inicia.arq_tabela);

		for(uint8_t i=1; i<inicia.num_col; i++)
			fputs("|c", inicia.arq_tabela);
	}else
		for(uint8_t i=0; i<inicia.num_col; i++)
			fputc('c', inicia.arq_tabela);

	fputs(inicia.est_lin_horizon ? end_inicio_est : end_inicio,
		inicia.arq_tabela);
	return inicia;
}



void nome_colunas(tabela_tex tabela, ...){
	va_list args;
	va_start(args, tabela);

	for(uint8_t i=0; i<tabela.num_col;){
		fputs("\t\t", tabela.arq_tabela);
		fputs(va_arg(args, char*), tabela.arq_tabela);
		fputs(++i < tabela.num_col ? "\t&\n" : "\t\\\\\n",
			tabela.arq_tabela);             //Última linha?
	}

	fputs(tabela.est_lin_horizon ? pos_inicio_est : pos_inicio,
		tabela.arq_tabela);
	va_end(args);
}



void printoneline(tabela_tex *tabela, char *format, ...){
	va_list args;
	va_start(args, format);

	char copia_format[strlen(format)];
	strcpy(copia_format, format);

	fprintf( (*tabela).arq_tabela, "\t\t%%Linha %hhu\n\t\t",
		 ++(*tabela).linhas_printadas);

	for(uint8_t i=0U, cont_col=0U, ini=0U;
	*copia_format && cont_col<(*tabela).num_col;){
		while(	*(copia_format+i)!=' ' &&
			*(copia_format+i)!='\t' &&
			*(copia_format+i)) i++;
		*(copia_format+i)='\0';

		vfprintf((*tabela).arq_tabela, copia_format+ini, args);
		fputs(++cont_col < (*tabela).num_col ? "&\n\t\t" : "\\\\\n\n",
			(*tabela).arq_tabela);
		ini=++i;
	}

	va_end(args);
}



void printoneline_v2(tabela_tex *tabela, ...){
	va_list args;
	va_start(args, tabela);

	fprintf((*tabela).arq_tabela, "\t\t%%Linha %hhu\n\t\t",
		++(*tabela).linhas_printadas);

	for(uint8_t cont_col=0U; cont_col<(*tabela).num_col;){
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

	for(uint8_t i=0;i<(*tabela).num_col<<1;i++){
		argumentos[i] = va_arg(args, void*);
	}

	for(uint8_t i=0;)
	for(uint8_t j=0;)

	va_end(args);
}
*/


void fechatabela(tabela_tex tabela, const char *rodape, const char *label){
	fputs(tabela.est_lin_horizon ? comeco_final_est : comeco_final,
		tabela.arq_tabela);

	if(tabela.caption_pos)
		fputs(caption, tabela.arq_tabela);
	else
		fputs(small_sem_capt, tabela.arq_tabela);

	fputs(small, tabela.arq_tabela);
	fputs(rodape, tabela.arq_tabela);


	if(*label){
		fputs(label_str, tabela.arq_tabela);
		fputs(label, tabela.arq_tabela);
	}

	fputs(fim_final, tabela.arq_tabela);
	fclose(tabela.arq_tabela);
}
