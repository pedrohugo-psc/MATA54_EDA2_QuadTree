# Quadtree: Estrutura de Dados Espacial
Este código foi desenvolvido para a matéria MATA54: Estrutura de Dados II

Autor: Pedro Hugo Passos da Silva Carlos

## Contexto Histórico e Relevância
Introduzida na década de 1970, a quadtree tornou-se fundamental em geometria computacional, gráficos e bancos de dados espaciais. Sua estrutura recursiva permite acesso rápido a dados, sendo crucial para aplicações como detecção de colisões em tempo real, análise geográfica e processamento de imagens multirresolução. Avanços recentes melhoraram sua eficiência, especialmente com grandes conjuntos de dados dinâmicos.

## Conceito

Uma **Quadtree** é uma estrutura de dados em árvore utilizada para organizar e gerenciar informações espaciais em um espaço bidimensional (2D). Cada nó dessa árvore pode ter até quatro filhos, correspondentes aos quatro quadrantes (noroeste, nordeste, sudoeste, sudeste) de uma região 2D. O nó raiz representa toda a área espacial, e níveis subsequentes subdividem recursivamente esse espaço em quadrantes menores até que condições específicas sejam atendidas, como um tamanho mínimo de célula ou uma densidade máxima de dados. Essa decomposição hierárquica permite indexação espacial eficiente, buscas rápidas e gestão otimizada de dados.

### Estrutura e Funcionalidade
A quadtree divide o espaço 2D em quatro quadrantes de tamanho igual. Cada nó representa uma região e, se um quadrante contém dados (como pontos, linhas ou objetos), ele é subdividido novamente. Esse processo continua até que uma condição de parada seja alcançada, como a presença de um único ponto por quadrante ou uma resolução mínima definida. A estrutura se adapta à densidade dos dados, criando subdivisões mais refinadas em áreas complexas e mantendo regiões mais amplas onde os dados são esparsos.

### Operações Essenciais
1. **Inserção**: Um ponto é adicionado percorrendo a árvore até o quadrante adequado. Se o quadrante exceder sua capacidade, ele se divide em quatro subquadrantes. Essa operação tem complexidade *O(log N)*, onde *N* é o tamanho do espaço ou dos dados.
2. **Busca**: Para localizar um ponto ou região, a árvore é percorrida comparando coordenadas com os limites dos quadrantes. A busca reduz rapidamente a área de interesse, também com complexidade *O(log N)*.

### Aplicações
As quadtrees são ideais para cenários que demandam eficiência espacial:
- **Compressão de Imagens**: Nós armazenam valores médios de cor de seus quadrantes, com níveis mais profundos capturando detalhes finos (ex: formato JPEG).
- **Detecção de Colisões**: Identifica sobreposições entre objetos verificando interseções entre quadrantes.
- **Sistemas de Informação Geográfica (SIG)**: Gerencia consultas espaciais, como busca por proximidade ou intervalos.
- **Computação Gráfica**: Otimiza renderização e cálculos espaciais.

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

### Considerações de Implementação
O desempenho depende de:
- **Distribuição Espacial**: Dados muito agrupados aumentam a profundidade da árvore.
- **Critérios de Parada**: Como tamanho mínimo da célula ou limite de pontos por quadrante.
- **Balanceamento**: Técnicas para otimizar a profundidade, como pré-ordenação de dados.

## Conclusão
A quadtree é uma ferramenta versátil e eficaz para gerenciar dados espaciais 2D. Ao combinar subdivisão hierárquica e adaptabilidade, equilibra granularidade e desempenho, sendo indispensável em áreas como visão computacional, mapeamento geográfico e simulações. Embora desafios como consumo de memória persistam, sua velocidade e flexibilidade garantem relevância contínua no processamento espacial moderno.

