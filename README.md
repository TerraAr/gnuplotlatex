# latex

 Esta é uma biblioteca em progresso com o
intuito de facilitar a exportação dos dados
com formatação de tabela (e imagem para
os gráficos numa versão futura) do LaTeX.  

 As comunicações estão sendo feitas de modo
que seja possível fazer essas comunicações
simples, porém altamente configurável para os
programadores que necessitem seguir normas
específicas de formatação de tabelas e gráficos
que não sejam necessariamente ''amigáveis'' com
as da ABNT ou similares.  

 Atualmente apenas a parte de saída formatada
como tabela do LaTeX está operante, enquanto
a comunicação com o gnuplot está sendo
esquematizada para futura implementação.  

## Tabelas LaTeX

 Esta parte da biblioteca tem sua implementação
centrada em uma estrutura que guarda as
informações que são necessárias durante ou após
a construção da tabela, são elas:  

 - Estilo das linhas horizontais (possibilidade
 de a primeira e última serem estilizadas)  

 - Número de colunas  

 - Número de linhas já escritas
 É usado para numerar as linhas da tabela na
 forma comentada, facilitando eventuais
 modificações desta ''à mão'', sem necessidade
 de criar um novo programa em C para modificá-lo

 - Ponteiro para o arquivo onde está sendo
 escrita a tabela  

 - Posicionamento do label da tabela (antes ou
 depois da mesma)  

 - Ponteiro para o texto que deve ser adicionado
 junto com a numeração da tabela  

### Funções da saída para o LaTeX

 ~~~c
 tabela_tex inicializa(const char *nome_arq, uint8_t num_colunas, uint8_t opcoes, const char *capt)
 ~~~

  Inicializa a estrutura com as configurações especificadas
  além de abrir e inicializar o arquivo, abrindo a tabela,
  centralizando, e colocando o título, caso este seja no
  cabeçalho.  

 ~~~c
 void nome_colunas(tabela_tex tabela, ...)
 ~~~

  Coloca as strings na sequência como nomes das colunas até
  que o número de colunas seja atingido e coloca uma linha
  horizontal em seguida.  

 ~~~c
 void printoneline(tabela_tex *tabela, char *format, ...)
 ~~~

 A função printa uma linha da tabela conforme especificado
 na string de formato, enquanto faz a separação entre as
 colunas pelos espaço ou tabulações presentes na string.  

 ~~~c
 void fechatabela(tabela_tex tabela, const char *rodape, const char *label)
 ~~~

 Fecha a tabela colocando as notas de rodapé, o label
 da tabela e o `end{table}`, além de fechar o arquivo.
 Caso não se queira um label ou notas de rodapé deve-se
 apenas enviar strings vazias nos respectivos argumentos.
