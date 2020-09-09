/* Copyright (C) 2019 - 2020 Fernando José Carames Vecino
 * (fernando.carames@gmail.com).
 ************************************************************************
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>
 ************************************************************************
 *
 * Este programa é um software livre; você pode redistribuí-lo e/ou
 * modificá-lo sob os termos da Licença Pública Geral GNU como publicada
 * pela Free Software Foundation; na versão 3 da Licença, ou
 * (a seu critério) qualquer versão posterior.
 *
 * Este programa é distribuído na esperança de que possa ser útil,
 * mas SEM NENHUMA GARANTIA; sem uma garantia implícita de ADEQUAÇÃO
 * a qualquer MERCADO ou APLICAÇÃO EM PARTICULAR. Veja a
 * Licença Pública Geral GNU para mais detalhes.
 *
 * Você deve ter recebido uma cópia da Licença Pública Geral GNU junto
 * com este programa. Se não, veja <http://www.gnu.org/licenses/>
 ************************************************************************
 */

#include"latex.h"

#include<stdio.h>
#include<stdarg.h>
#include<stdint.h>
#include<ctype.h>
#include<string.h>

#define erro(x)	fputs(x, stderr)

static const char *str_ruim = "ERRO: String mal-formatada\n";

void imprimeTipo(char* str, va_list varg, FILE* fp, unsigned linha);

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
#else /* TITULO_NO_INICIO */
	fputs(capt, inicia.arq_tabela);
#endif /* TITULO_NO_FINAL */

	fputs(inicio_tabular, inicia.arq_tabela);
#ifdef LINHAS_VERTICAIS
	fputc('c', inicia.arq_tabela);

	for(uint8_t i = 1U; i < inicia.num_col; i++)
		fputs("|c", inicia.arq_tabela);
#else /* SEM_LINHAS_VERTICAIS */
	for(uint8_t i = 0U; i < inicia.num_col; i++)
		fputc('c', inicia.arq_tabela);
#endif /* LINHAS_VERTICAIS */

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
			tabela.arq_tabela);		//Última linha?
	}

	va_end(args);	// Termina va_list
	fputs(pos_inicio, tabela.arq_tabela);
}



void printoneline(tabela_tex *tabela, char *format, ...){
	va_list args;
	va_start(args, format);

	char str_format[strlen(format)];
	strcpy(str_format, format);

	fprintf( (*tabela).arq_tabela, "\t\t%%Linha %hhu\n\t\t",
		 ++(*tabela).linhas_printadas);

	uint8_t i, cont_col, ini;
	for(i = 0U, cont_col = 0U, ini = 0U;
	*(str_format + i) && cont_col < (*tabela).num_col;){
		/* Acha o índice do final da célula */
		while(!isspace(*(str_format+i)) || *(str_format+i)!='\0')
			i++;

		/* Isola a célula para o vfprintf */
		*(str_format + i) = '\0';

		vfprintf((*tabela).arq_tabela, str_format+ini, args);

		if(++cont_col < (*tabela).num_col)
			fputs("&\n\t\t", (*tabela).arq_tabela);
		else
			fputs("\\\\\n\n", (*tabela).arq_tabela);

		ini = ++i;
	}

	va_end(args);
}

void printoneline_v2(tabela_tex *tabela, ...){
	va_list args;
	va_start(args, tabela);

	fprintf((*tabela).arq_tabela, "\t\t%%Linha %hhu\n\t\t",
		++(*tabela).linhas_printadas);

	for(uint8_t cont_col = 0U; cont_col < (*tabela).num_col;){
		vfprintf((*tabela).arq_tabela, va_arg(args, char*), args);
		fputs(++cont_col < (*tabela).num_col ? "&\n\t\t" : "\\\\\n\n",
			(*tabela).arq_tabela);
	}

	va_end(args);
}

void printmultiline(tabela_tex *tabela, const uint8_t qte_linhas,
				char *format, ...){
	va_list args;
	va_start(args, format);

	uint8_t i;
	char str_format[strlen(format)];
	for(i = 0U; i < qte_linhas; i++){
		va_list copy;
		va_copy(copy, args);

		strcpy(str_format, format);

		fprintf( (*tabela).arq_tabela, "\t\t%%Linha %hhu\n\t\t",
			++(*tabela).linhas_printadas);

		uint8_t j, cont_col, ini;
		for(j = 0U, cont_col = 0U, ini = 0U;
		*(str_format + j) && cont_col < (*tabela).num_col;){
			/* Acha o índice do final da célula */
			while(!isspace(*(str_format+j)) ||
				*(str_format+j)!='\0') j++;

			/* Isola a célula para o vfprintf */
			*(str_format + j) = '\0';

			/* Imprime a próxima coluna */
			imprimeTipo(str_format, copy,
					(*tabela).arq_tabela, i);

			if(++cont_col < (*tabela).num_col)
				fputs("&\n\t\t", (*tabela).arq_tabela);
			else
				fputs("\\\\\n\n", (*tabela).arq_tabela);

			ini = ++j;
		}

		va_end(copy);
	}

	va_end(args);
}

void printmultiline_v2(tabela_tex *tabela, const uint8_t qte_linhas, ...){
	va_list args;
	va_start(args, qte_linhas);

	for(uint8_t i = 0U; i < qte_linhas; i++){
		va_list copy;
		va_copy(copy, args);

		fprintf((*tabela).arq_tabela, "\t\t%%Linha %hhu\n\t\t",
			++(*tabela).linhas_printadas);

		for(uint8_t cont_col = 0U; cont_col < (*tabela).num_col;){
			/* Carrega o format da próxima célula */
			char *str = va_arg(copy, char*);
			/* Imprime a próxima coluna */
			imprimeTipo(str, copy, (*tabela).arq_tabela, i);

			if(++cont_col < (*tabela).num_col)
				fputs("&\n\t\t", (*tabela).arq_tabela);
			else
				fputs("\\\\\n\n", (*tabela).arq_tabela);
		}

		va_end(copy);
	}

	va_end(args);
}

void fechatabela(tabela_tex tabela, const char *rodape, const char *label){
	fputs(comeco_final, tabela.arq_tabela);

#ifdef TITULO_NO_FINAL
	fputs(caption, tabela.arq_tabela);
#endif /* TITULO_NO_FINAL */

	if(*rodape){
		fputs(small, tabela.arq_tabela);
		fputs(rodape, tabela.arq_tabela);
		fputs("}\n", tabela.arq_tabela);
	}


	if(*label){
		fputs(label_str, tabela.arq_tabela);
		fputs(label, tabela.arq_tabela);
		fputs("}\n", tabela.arq_tabela);
	}

	fputs(fim_final, tabela.arq_tabela);
	fclose(tabela.arq_tabela);
}

/* Imprime o próximo argumento do vetor */
void imprimeTipo(char* str, va_list varg, FILE* fp, unsigned linha){
#define imprime(tipo) fprintf(fp, str, va_arg(varg, tipo*)[linha])

	for(unsigned i = 0U; str[i]; i++)
		if(str[i] == '%')
ret_num:		switch(str[++i]){
				case '0':
					/* Precisão */
					goto ret_num;
				break;

				case '1':
					/* Precisão */
					goto ret_num;
				break;

				case '2':
					/* Precisão */
					goto ret_num;
				break;

				case '3':
					/* Precisão */
					goto ret_num;
				break;

				case '4':
					/* Precisão */
					goto ret_num;
				break;

				case '5':
					/* Precisão */
					goto ret_num;
				break;

				case '6':
					/* Precisão */
					goto ret_num;
				break;

				case '7':
					/* Precisão */
					goto ret_num;
				break;

				case '8':
					/* Precisão */
					goto ret_num;
				break;

				case '9':
					/* Precisão */
					goto ret_num;
				break;

				case '.':
					/* Precisão */
					goto ret_num;
				break;

				case 'l':
					switch(*(str + (++i))){
						case 'A':
							/* Double */
							imprime(double);
						break;

						case 'a':
							/* Double */
							imprime(double);
						break;

						case 'E':
							/* Double */
							imprime(double);
						break;

						case 'e':
							/* Double */
							imprime(double);
						break;

						case 'F':
							/* Double */
							imprime(double);
						break;

						case 'f':
							/* Double */
							imprime(double);
						break;

						case 'G':
							/* Double */
							imprime(double);
						break;

						case 'g':
							/* Double */
							imprime(double);
						break;

						case 'i':
							/* Long int */
							imprime(long);
						break;

						case 'u':
							/* Unsigned long */
							imprime(unsigned long);
						break;

						case 'l':
						switch(*(str + (++i))){
							case 'i':
								/* Long long */
								imprime(long
									long);
							break;

							case 'u':
								/* Unsigned
								 * long long */
								imprime(unsigned
									long
									long);
							break;

							default:
								/* Mal
								 * formatado */
								erro(str_ruim);
							break;
						}
						break;

						default:
							/* Mal formatado */
							erro(str_ruim);
						break;
					}
				break;

				case 'L':
					/* Long double */
					imprime(long double);
				break;

				case 'h':
					switch(*(str + (++i))){
						case 'i':
							/* Short int */
							imprime(short);
						break;

						case 'u':
							/* Unsigned short */
							imprime(unsigned short);
						break;

						case 'h':
						switch(*(str + (++i))){
							/* Signed char */
							case 'i':
							imprime(signed char);
							break;

							case 'u':
							/* Unsigned char */
							imprime(unsigned char);
							break;

							default:
								/* Mal
								 * formatado */
								erro(str_ruim);
							break;
						}
						break;

						default:
							/* Mal formatado */
							erro(str_ruim);
						break;
					}
				break;

				case 'd':
					/* Int */
					imprime(int);
				break;

				case 'i':
					/* Int */
					imprime(int);
				break;

				case 'u':
					/* Unsigned */
					imprime(unsigned);
				break;

				case 'c':
					/* Char */
					imprime(char);
				break;

				case 's':
					/* String */
					imprime(char*);
				break;

				case 'x':
					/* Unsigned */
					imprime(unsigned);
				break;

				case 'X':
					/* Unsigned */
					imprime(unsigned);
				break;

				case 'o':
					/* Unsigned */
					imprime(unsigned);
				break;

				case 'A':
					/* Float */
					imprime(float);
				break;

				case 'a':
					/* Float */
					imprime(float);
				break;

				case 'E':
					/* Float */
					imprime(float);
				break;

				case 'e':
					/* Float */
					imprime(float);
				break;

				case 'F':
					/* Float */
					imprime(float);
				break;

				case 'f':
					/* Float */
					imprime(float);
				break;

				case 'G':
					/* Float */
					imprime(float);
				break;

				case 'g':
					/* Float */
					imprime(float);
				break;

				case '[':
					/* Char */
					imprime(char);
				break;

				case 'p':
					/* Ponteiro */
					imprime(void*);
				break;

				case '%':
					/* Imprimir % */
				break;

				default:
					/* Mal formatado */
					erro(str_ruim);
				break;
			}
#undef imprime
}
