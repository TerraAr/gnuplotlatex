# gnuplotlatex

 Esta é uma biblioteca em progresso com o
intuito de facilitar a comunicação com o
software gnuplot (pedir gráfico e ajuste
de curva e receber os parâmetros calculados)
e fazer a saída com formatação de tabela
(ou talvez imagem para os gráficos numa
versão futura) do LaTeX.

 As comunicações estão sendo feitas de modo
que seja possível fazer essas comunicações
simples, porém altamente configurável para os
programadores que necessitem seguir normas
específicas de formatação de tabelas e gráficos
que não sejam necessariamente "amigáveis" com
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
 de a primeira e última serem mais fortes que
 as demais)

 - Número de colunas

 - Número de linhas já escritas

 - Ponteiro para o arquivo onde está sendo
 escrita a tabela

 - Posicionamento da numeração da tabela (antes
 ou depois da mesma)

 - Ponteiro para o texto que deve ser adicionado
 junto com a numeração da tabela

### Funções da saída para o LaTeX

 - inicializa(const char\*, uint8\_t, uint8\_t, const char\*)
 > Inicializa a estrutura com as configurações especificadas
  além de abrir e inicializar o arquivo, abrindo a tabela,
  centralizando, além de colocar o título, caso seja
  especificado nas configurações.

 - nome\_colunas(tabela\_tex, ...)
 > Coloca as strings na sequência como nomes das colunas até
  que o número de colunas seja atingido e coloca uma linha
  horizontal em seguida.

 - printoneline(tabela\_tex, char\*, ...)
 > A função printa uma linha da tabela conforme especificado
  na string de formato, enquanto faz a separação entre as
  colunas pelos espaço ou tabulações presentes na string.

 - fechatabela(tabela\_tex, const char\*, const char\*)
 > Fecha a tabela colocando as notas de rodapé, o label
  da tabela e o end{table}, além de fechar o arquivo.
  Caso não se queira um label ou notas de rodapé deve-se
  apenas enviar strings vazias nos respectivos argumentos.
