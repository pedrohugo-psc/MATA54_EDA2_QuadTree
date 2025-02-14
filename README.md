# Quadtree: Estrutura de Dados Espacial
Este código foi desenvolvido para a matéria MATA54: Estrutura de Dados II

Autor: Pedro Hugo Passos da Silva Carlos

Matrícula: 219115222

## Conceito

Uma **Quadtree** é uma estrutura de dados em árvore utilizada para organizar e gerenciar informações espaciais em um espaço bidimensional (2D). Cada nó dessa árvore pode ter até quatro filhos, correspondentes aos quatro quadrantes (noroeste, nordeste, sudoeste, sudeste) de uma região 2D. O nó raiz representa toda a área espacial, e níveis subsequentes subdividem recursivamente esse espaço em quadrantes menores até que condições específicas sejam atendidas, como um tamanho mínimo de célula ou uma densidade máxima de dados. Essa decomposição hierárquica permite indexação espacial eficiente, buscas rápidas e gestão otimizada de dados.

### Estrutura e Funcionalidade
A quadtree divide o espaço 2D em quatro quadrantes de tamanho igual. Cada nó representa uma região e, se um quadrante contém dados (como pontos, linhas ou objetos), ele é subdividido novamente. Esse processo continua até que uma condição de parada seja alcançada, como a presença de um único ponto por quadrante ou uma resolução mínima definida. A estrutura se adapta à densidade dos dados, criando subdivisões mais refinadas em áreas complexas e mantendo regiões mais amplas onde os dados são esparsos.

### Operações Essenciais
1. **Inserção**: Um ponto é adicionado percorrendo a árvore até o quadrante adequado. Se o quadrante exceder sua capacidade, ele se divide em quatro subquadrantes. Essa operação tem complexidade *O(log N)*, onde *N* é o tamanho do espaço ou dos dados.
2. **Busca**: Para localizar um ponto ou região, a árvore é percorrida comparando coordenadas com os limites dos quadrantes. A busca reduz rapidamente a área de interesse, também com complexidade *O(log N)*.

### Vantagens e Desvantagens
- **Vantagens**:
  - Adapta-se a distribuições não uniformes de dados.
  - Reduz a complexidade de consultas espaciais.
  - Dinamismo na gestão de dados densos ou esparsos.
- **Desvantagens**:
  - Sobrecarga de memória em dados muito irregulares (excesso de subdivisões).
  - Complexidade na implementação para dados dinâmicos (atualizações frequentes).
  - Risco de artefatos em imagens comprimidas se a divisão for muito simplificada.

### Variantes e Extensões
- **Region Quadtree**: Foca na subdivisão do espaço, comum em processamento de imagens.
- **Point Quadtree**: Armazena pontos, subdividindo com base em suas localizações (similar a k-d trees).
- **Octree**: Versão 3D que divide o espaço em oito octantes, usada para dados volumétricos.
- **Hyperoctree**: Generaliza a quadtree para *n* dimensões.

### Aplicações
As quadtrees são ideais para cenários que demandam eficiência espacial:
- **Compressão de Imagens**: Nós armazenam valores médios de cor de seus quadrantes, com níveis mais profundos capturando detalhes finos (ex: formato JPEG).
- **Detecção de Colisões**: Identifica sobreposições entre objetos verificando interseções entre quadrantes.
- **Sistemas de Informação Geográfica (SIG)**: Gerencia consultas espaciais, como busca por proximidade ou intervalos.
- **Computação Gráfica**: Otimiza renderização e cálculos espaciais.

## Conclusão
A quadtree é uma ferramenta versátil e eficaz para gerenciar dados espaciais 2D. Ao combinar subdivisão hierárquica e adaptabilidade, equilibra granularidade e desempenho, sendo indispensável em áreas como visão computacional, mapeamento geográfico e simulações. Embora desafios como consumo de memória persistam, sua velocidade e flexibilidade garantem relevância contínua no processamento espacial moderno.

## Implmentação do código

Este trabalho tem como objetivo implementar uma estrutura de dados **quadtree** para armazenar pontos em um espaço bidimensional e gerar uma visualização gráfica da estrutura em formato SVG. A quadtree facilita operações de inserção, remoção e busca de pontos, além de organizar os dados de forma espacialmente eficiente.

### Arquivos do Projeto

- **main.c**  
  Contém a função principal que apresenta um menu interativo para:
  - Inserir pontos (com coordenadas e valor associado).
  - Remover pontos existentes.
  - Buscar pontos na estrutura.
  
  Ao encerrar o programa, gera um arquivo SVG que representa a quadtree.

- **quadtree.c**  
  Define a estrutura e as funções básicas da quadtree, incluindo:
  - Criação da árvore.
  - Inserção de pontos (com subdivisão do espaço quando necessário).
  - Busca e remoção de pontos.
  - Verificação de limites e profundidade para manter a estrutura eficiente.

- **map_quadtree.c**  
  Responsável pela geração do arquivo SVG:
  - Desenha os eixos e as subdivisões da quadtree.
  - Plota os pontos armazenados, representados por círculos com seus valores.

## Como Rodar o Código

Para compilar e executar o programa, siga os passos abaixo:

1. **Acesse o diretório dos fontes:**  
   No terminal, navegue até a pasta `src` que contém os arquivos fonte:
   ```bash
   cd ./src/
2. **Compile o código:**  
   Utilize o compilador GCC para gerar o executável main:
   ```bash
   gcc -o main main.c quadtree.c map_quadtree.c
1. **Execute o programa:**  
   Após a compilação, rode o executável:
   ```bash
   ./main

## Referências Bibliográficas

