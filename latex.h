#ifndef LATEX_H
#define LATEX_H

#include<stdio.h>
#include<stdarg.h>
#include<stdbool.h>
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

static const char *label_str="}\n\t\\label{";

static const char *fim_final="}\n\\end{table}\n";

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

//void printline(tabela_tex tabela, char* tipos, ...);
//void printline(tabela_tex tabela, char* tipos[], ...);
void printoneline(tabela_tex *tabela, char *format, ...);
void printoneline_v2(tabela_tex *tabela, ...);

inline void fechatabela(tabela_tex tabela, const char *rodape,
			const char *label) __attribute__((always_inline));

#endif /*LATEX_H*/
