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

#ifndef LATEX_H
#define LATEX_H

#include<stdio.h>
#include<stdarg.h>
#include<stdint.h>

#ifdef FORCE_POSITION

static const char *inicio="\\begin{table}[!htp]\n\t\\centering\n";

#else

static const char *inicio="\\begin{table}[htp]\n\t\\centering\n";

#endif

static const char *caption="\t\\caption{";

static const char *inicio_tabular="\t\\begin{tabular}{";

#ifdef LINHAS_ESTILIZADAS

static const char *end_inicio = "}\n\t\t\\toprule\n";

static const char *pos_inicio="\t\t\\midrule\n\n";

static const char *comeco_final="\t\t\\bottomrule\n\t\\end{tabular}\n\n";

#else

static const char *end_inicio = "}\n\t\t\\hline\n";

static const char *pos_inicio="\t\t\\hline\n";

static const char *comeco_final="\t\t\\hline\n\t\\end{tabular}\n\n";

#endif

#ifdef TITULO_NO_FINAL

static const char *small="\\small\n\t\t";

#else

static const char *small="\t{\\small\n\t\t";

#endif

static const char *label_str="\t\\label{";

static const char *fim_final="\\end{table}\n";

typedef struct tabela_tex{
FILE *arq_tabela;		//ponteiro para o arquivo
uint8_t num_col;		//número de colunas da tabela
uint8_t linhas_printadas;	//número atual de linhas impressas

//bool caption_pos;		//Posição do caption: 0 começo, 1 final

//bool est_lin_horizon;		//estilo das linhas horizontais: 0 simples, 1 estilzadas
}tabela_tex;

tabela_tex inicializa(const char *nome_arq, uint8_t num_colunas,
			const char *nome_tabela);

void nome_colunas(tabela_tex tabela, ...);

void printoneline(tabela_tex *tabela, char *format, ...);
void printoneline_v2(tabela_tex *tabela, ...);

void printmultiline
	(tabela_tex *tabela, const uint8_t qte_linhas, char *format, ...);
void printmultiline_v2(tabela_tex *tabela, const uint8_t qte_linhas, ...);

void fechatabela(tabela_tex tabela, const char *rodape, const char *label);

#endif /*LATEX_H*/
