#ifndef LATEX_H
#define LATEX_H

#include<stdio.h>
#include<stdarg.h>
#include<stdbool.h>
#include<stdint.h>

#define COM_LINHAS_VERT	0x08
#define SEM_LINHAS_VERT	0x00
#define CAP_FIM		0x04
#define CAP_COMECO	0x00
#define LINHA_EST	0x02
#define LINHA_N_EST	0x00
#define FORCE_POS	0x01
#define N_FORCE_POS	0x00

#define inicializaFis(x,y) inicializa(x,y,0x07U,NULL)
#define inicializaMec(x,y,z) inicializa(x,y,0x09U,z)

static const char *inicio="\\begin{table}[";

static const char *inicio_meio="htp]\n\t\\centering\n";

static const char *caption="\t\\caption{";

static const char *inicio_all="\t\\begin{tabular}{";

static const char *end_inicio_est="}\n\t\t\\toprule\n";

static const char *end_inicio="}\n\t\t\\hline\n";

static const char *pos_inicio_est="\t\t\\midrule\n\n";

static const char *pos_inicio="\t\t\\hline\n";

static const char *comeco_final="\t\t\\hline\n\t\\end{tabular}\n\n";

static const char *comeco_final_est="\t\t\\bottomrule\n\t\\end{tabular}\n\n";

static const char *small="\\small\n\t\t";

static const char *small_sem_capt="\t\\small{\n\t\t";

static const char *label_str="}\n\t\\label{";

static const char *fim_final="}\n\\end{table}\n";

typedef struct tabela_tex{
FILE *arq_tabela;		//ponteiro para o arquivo
uint8_t num_col;		//número de colunas da tabela
uint8_t linhas_printadas;	//número atual de linhas impressas

bool caption_pos;		//Posição do caption: 0 começo, 1 final

bool est_lin_horizon;		//estilo das linhas horizontais: 0 simples, 1 estilzadas
}tabela_tex;

tabela_tex inicializa(const char *nome_arq, uint8_t num_colunas, uint8_t opcoes, const char *capt);

void nome_colunas(tabela_tex tabela, ...);

//void printline(tabela_tex tabela, char* tipos, ...);
//void printline(tabela_tex tabela, char* tipos[], ...);
void printoneline(tabela_tex *tabela, char *format, ...);
void printoneline_v2(tabela_tex *tabela, ...);

inline void fechatabela(tabela_tex tabela, const char *rodape,
			const char *label) __attribute__((always_inline));

#endif /*LATEX_H*/
