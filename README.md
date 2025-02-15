# Quadtree: Estrutura de Dados Espacial

Este projeto implementa uma estrutura de dados **quadtree** para armazenar pontos em um espaço bidimensional e gerar uma visualização gráfica em SVG. A solução foi desenvolvida para a disciplina MATA54: Estrutura de Dados II e se baseia em conceitos amplamente estudados na área de estruturas de dados espaciais.

Autor: Pedro Hugo Passos da Silva Carlos

Matrícula: 219115222

## Sumário

- [Quadtree: Estrutura de Dados Espacial](#quadtree-estrutura-de-dados-espacial)
  - [Sumário](#sumário)
  - [Introdução](#introdução)
  - [Conceito e Funcionamento](#conceito-e-funcionamento)
    - [Vantagens e Desvantagens](#vantagens-e-desvantagens)
  - [Detalhamento da Implementação](#detalhamento-da-implementação)
    - [Arquivos do Projeto](#arquivos-do-projeto)
    - [Funções Básicas](#funções-básicas)
  - [Exemplo de Uso: Detectando Colisões em Jogos](#exemplo-de-uso-detectando-colisões-em-jogos)
  - [Complexidade Temporal](#complexidade-temporal)
  - [Como Rodar o Código](#como-rodar-o-código)
    - [Pré-requisitos](#pré-requisitos)
    - [Instruções de Compilação e Execução](#instruções-de-compilação-e-execução)
  - [Conclusão](#conclusão)
  - [Referências Bibliográficas](#referências-bibliográficas)


## Introdução

Uma **quadtree** é uma estrutura em árvore que particiona recursivamente um espaço bidimensional em quatro sub-regiões (quadrantes). Essa técnica de divisão hierárquica permite organizar, indexar e acessar dados espaciais de forma eficiente – seja para armazenamento de pontos, linhas, polígonos ou mesmo para processamento de imagens, sistemas de informações geográficas e aplicações em jogos.

O projeto integra conceitos de estudos acadêmicos clássicos sobre estruturas de dados hierárquicas e busca aplicar esses conhecimentos na implementação de um sistema com operações de inserção, remoção e busca de pontos, acompanhado de uma visualização gráfica que ilustra a divisão espacial.


## Conceito e Funcionamento

A Quadtree trabalha com os seguintes conceitos:

- **Divisão Espacial:**  
  O nó raiz representa toda a área 2D e é subdividido em quatro quadrantes (noroeste, nordeste, sudoeste, sudeste). Cada nó que contém mais de um ponto (ou que excede uma capacidade definida) é dividido novamente, formando uma estrutura de árvore.

- **Adaptação à Distribuição:**  
  Em regiões com muitos dados, a subdivisão é mais fina, enquanto em áreas esparsas os blocos permanecem maiores, o que ajuda na eficiência das buscas e no processamento espacial.

- **Operações Básicas:**
  - **Inserção:** Percorre a árvore até encontrar o quadrante adequado para o ponto. Se o nó encontrado já estiver ocupado, ocorre a subdivisão do nó, que passa a ter quatro filhos, e o processo continua recursivamente.  
    *Complexidade: Aproximadamente O(log N).*
    
  - **Busca:** Compara as coordenadas do ponto com os limites de cada quadrante, avançando pela árvore recursivamente até localizar o dado associado.  
    *Complexidade: Aproximadamente O(log N).*
    
  - **Remoção:** Procura e remove o ponto especificado. Se, após a remoção, um nó e seus irmãos não possuírem dados, pode ocorrer a “colapso” desses nós, recuperando espaço.


### Vantagens e Desvantagens

**Vantagens:**
- Adaptação dinâmica à distribuição dos dados.
- Redução do espaço de busca em consultas espaciais.
- Possibilidade de compressão de imagens e representação de áreas homogêneas com menos informação.

**Desvantagens:**
- Em casos de dados muito irregulares ou ruidosos, podem ser gerados muitos nós pequenos, aumentando a sobrecarga de memória.
- Implementação e manutenção podem ser mais complexas em cenários de dados altamente dinâmicos.
- Divisões excessivamente simples podem ocasionar artefatos em aplicações de compressão.

## Detalhamento da Implementação

### Arquivos do Projeto

- **main.c**  
  Conta com a função principal e um menu interativo que possibilita:
  - Inserir pontos (digitando coordenadas e um valor).
  - Remover pontos existentes.
  - Buscar pontos na estrutura.  
  Ao encerrar, o programa gera um arquivo SVG que representa graficamente a quadtree construída.

- **quadtree.c**  
  Implementa a Quadtree e inclui funções para:
  - Criação da árvore com limites definidos.
  - Inserção de pontos (incluindo a lógica de subdivisão).
  - Busca e remoção de pontos.
  - Verificações de limites e verificação se o nó é folha (para manter a eficiência).

- **map_quadtree.c**  
  Responsável pela geração do arquivo SVG:
  - Desenha os eixos e as subdivisões da quadtree.
  - Plota os pontos (utilizando círculos e textos) de forma escalonada.
  - Cria o arquivo com dimensões escaladas conforme especificado.

### Funções Básicas

- **Inserção:**  
  A função de inserção verifica se o ponto está dentro dos limites do nó atual. Se o nó for folha e já contiver um ponto, uma subdivisão é realizada, e ambos os pontos (o existente e o novo) são reinseridos nos quadrantes apropriados.

- **Busca:**  
  A busca percorre a árvore com base nas coordenadas, retornando o nó correspondente se encontrado; caso contrário, retorna que o ponto não foi localizado.

- **Remoção:**  
  Remove o ponto com base em sua posição e, se possível, realiza a consolidação de nós, eliminando subdivisões desnecessárias.

## Exemplo de Uso: Detectando Colisões em Jogos

Para aplicações como jogos, o mundo do jogo é particionado hierarquicamente com uma quadtree. Nesse cenário:

1. **Organização do Espaço:**  
   O nó raiz representa o mundo inteiro e, conforme as entidades (como jogadores e obstáculos) são inseridas, ocorre a subdivisão do espaço.
   
2. **Inserção Dinâmica:**  
   Ao adicionar uma entidade, se ela estiver próxima de outras, o nó associada pode ser subdividido para garantir que cada subárea contenha poucos elementos.
   
3. **Verificação de Colisões:**  
   Com a quadtree, apenas entidades da mesma subdivisão (ou de regiões vizinhas, quando a entidade toca uma fronteira) são verificadas, melhorando o desempenho da detecção de colisões.
   
## Complexidade Temporal

O uso de quadtrees permite:

- Inserção de cada entidade em aproximadamente *O(log N)*, onde *N* representa a resolução ou tamanho da área espacial.
- Construção completa da árvore com *N* inserções resulta em uma complexidade de *O(N log N)*.
- A verificação de colisões dentro dos nós é feita, na prática, em tempo aproximadamente linear *O(N)*, resultando em um tempo total realista em *O(N log N)* na maioria dos cenários.

Essa abordagem é muito mais eficiente que a verificação completa de colisões, que é tipicamente O(N²).

## Como Rodar o Código

### Pré-requisitos

- Ambiente Linux ou similar com compilador GCC instalado.
- Acesso ao terminal para compilação e execução.

### Instruções de Compilação e Execução

1. **Acesse o diretório dos fontes:**  
   No terminal, navegue até a pasta `src` que contém os arquivos fonte:
   ```bash
   cd ./src/
2. **Compile o código:**  
   Utilize o compilador GCC para gerar o executável main:
   ```bash
   gcc -o main main.c quadtree.c map_quadtree.c
3. **Execute o programa:**  
   Após a compilação, rode o executável:
   ```bash
   ./main
4. **Visualize o arquivo SVG:**   
  Ao finalizar, o programa gera um SVG (por exemplo, quadtree.svg) que pode ser aberto em qualquer navegador ou editor de imagens compatível para visualizar a estrutura da quadtree.

## Conclusão 

A quadtree é uma estrutura de dados poderosa para o armazenamento e a consulta de informações espaciais. Sua capacidade de adaptação à densidade dos dados e o desempenho em buscas e operações espaciais fazem dela uma ferramenta imprescindível em diversas aplicações, desde compressão de imagens até detecção de colisões em jogos. Este projeto demonstra, por meio de uma implementação em C, como criar, manipular e visualizar uma quadtree de forma eficiente.

## Referências Bibliográficas


  - Samet, H. (1984). The Quadtree and Related Hierarchical Data Structures. Computing Surveys, 16(2).
  - Finkel, R. A., & Bentley, J. L. (1974). Quad trees: A data structure for retrieval on composite keys. Acta Informatica, 4(1), 1–9.
  - Bentley, J. L. (1975). Multidimensional binary search trees used for associative searching. Communications of the ACM, 18(9), 509–517.


