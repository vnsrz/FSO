# Alocações

## Contígua

![contigua.png](/anotacoes/img/contigua.png)

- **Rapidez**: Como os blocos de cada arquivo se encontram em sequência no disco, o acesso
    sequencial aos dados do arquivo é rápido, por exigir pouca movimentação da cabeça de
    leitura do disco. O acesso aleatório também é rápido, pois a posição de cada byte do
    arquivo pode ser facilmente calculada a partir da posição do bloco inicial.
- **Robustez**: Caso um bloco apresente defeito, apenas o conteúdo daquele bloco é perdido.
- **Flexibilidade**: O tamanho máximo do arquivo deve ser conhecido no momento de sua criação

### Problemas

- **Fragmentação externa**: À medida que o sistema evolui, arquivos são criados e removidos, e mais espaços vazios aparecem, consequentemente, os espaços vazios ficam menores, impossibilitando a criação de arquivos maiores do que os espaços.

## Encadeada simples

![encadeada.png](/anotacoes/img/encadeada.png)

Cada bloco do arquivo no disco contém dados do arquivo e um ponteiro para o próximo bloco. Desta forma é construída uma lista encadeada, não sendo necessário manter os arquivos lado a lado.

- **Rapidez**: O acesso sequencial é simples e rápido, pois cada bloco contém um ponteiro para o próximo, mas caso os blocos estejam muito espalhados no disco, a cabeça de leitura terá de fazer muitos
    deslocamentos, diminuindo o desempenho de acesso ao disco. Já o acesso aleatório fica muito prejudicado, pois para se acessar determinado bloco do arquivo, todos os anteriores devem ser acessados.
- **Robustez**: Caso um bloco seja corrompido, todos os posteriores ficarão inacessíveis.
- **Flexibilidade**: Não há necessidade de se definir o tamanho máximo do arquivo durante sua criação, e qualquer bloco livre pode ser usado, eliminando a fragmentação externa.

### Problemas

- **Desempenho e robustez**: Para se acessar o bloco n, todos os n-1 blocos anteriores devem ser lidos, e o corrompimento de um bloco acarreta na perda de todos os posteriores.

## FAT

![fat.png](/anotacoes/img/fat.png)

Os ponteiros da alocação encadeada podem ser retirados dos blocos de dados e armazenados em uma tabela separada: a Tabela de Alocação de Arquivos (*FAT - File Allocation Table*).
A FAT fica armazenada em blocos reservados no início da partição. Cada entrada dessa tabela corresponde a um bloco lógico do disco e contém um ponteiro indicando o próximo bloco do mesmo arquivo.
Uma cópia dessa tabela é mantida em cache na memória durante o uso do sistema, para melhorar o desempenho na localização dos blocos dos arquivos.

- **Rapidez**: Resolve o problema de desempenho da alocação sequencial simples
- **Robustez**: Caso a tabela FAT seja corrompida o acesso aos arquivos será comprometido, mas cópias da FAT são mantidas
- **Flexibilidade**: Mantém a flexibilidade da alocação encadeada

### Problemas

- **Espaço**: A tabela FAT pode ocupar muito espaço em disco.

## Indexada simples (i-node)

![indexS.png](/anotacoes/img/indexS.png)

Utiliza um vetor contendo o *índice de blocos* do arquivo. Cada entrada desse índice corresponde a um bloco do arquivo e aponta para a posição dele no disco.
O índice de blocos de cada arquivo é mantido em uma estrutura chamada *nó de índice* (*index node*) ou *i-node*. O *i-node* de cada arquivo contém:

- seu indice de blocos
- seus principais atributos (tamanho, permissões, datas de acesso, etc)

Os *i-nodes* de todos os arquivos são agrupados em uma tabela de *i-nodes*, mantida em uma área reservada do disco, separada dos blocos de dados dos arquivos.
Como os *i-nodes* também tem tamanho fixo, o número de entradas no índice de blocos de um arquivo é limitado. Por isso existe um tamanho máximo para os arquivos. Ex: para um sistema com blocos de 4 KBytes e índice de blocos com 64 ponteiros, o tamanho máximo é de 256 KBytes.
Além disso só podem haver uma certa quantidade de arquivos ou diretórios, ditada pela quantidade de *i-nodes* da tabela.

## Indexada multinível (i-node)
![indexM.png](/anotacoes/img/indexM.png)

Para aumentar o tamanho máximo de arquivos armazenados, algumas entradas do índice de blocos podem ser transformadas em ponteiros indiretos. Essas entradas apontam para blocos do disco que contêm outros ponteiros, criando assim uma estrutura em árvore. Também podem ser usados ponteiros dupla e triplamente indiretos. A localização e acesso de um bloco do arquivo permanece simples.

Em relação ao desempenho, pode-se afirmar que esta estratégia é bastante rápida, tanto para acessos sequenciais quanto para acessos aleatórios a blocos, devido aos índices de ponteiros dos blocos presentes nos i-nodes. Contudo, no caso de blocos situados no final de arquivos muito grandes, podem ser necessários três ou quatro acessos a disco adicionais para localizar o bloco desejado, devido à necessidade de ler os blocos com ponteiros indiretos.

- **Rapidez**: Pode-se afirmar que esta estratégia é bastante rápida.
- **Robustez**: Defeitos em blocos de dados não afetam os demais. Defeito nos metadados podem danificar grandes extensões do arquivo.
- **Flexibilidade**: Mantém a flexibilidade da alocação encadeada

## Comparação
![compare.png](/anotacoes/img/compare.png)

