#include "include/map_quadtree.h"
#include "include/quadtree.h"

/**
 * @brief Desenha os eixos X e Y no arquivo SVG.
 *
 * @param file Ponteiro para o arquivo SVG.
 * @param scale Fator de escala para o desenho.
 */
void draw_axes(FILE *file, int scale)
{
    int canvasHeight = scale * 10;
    fprintf(file, "<line x1='0' y1='%d' x2='%d' y2='%d' stroke='black' stroke-width='2'/>\n", canvasHeight, 0, canvasHeight);
    fprintf(file, "<line x1='0' y1='%d' x2='0' y2='%d' stroke='black' stroke-width='2'/>\n", canvasHeight, 0);
    fprintf(file, "<text x='-40' y='%d' font-size='30'>y</text>\n", canvasHeight - 1000);
    fprintf(file, "<text x='%d' y='%d' font-size='30'>x</text>\n", canvasHeight - 1035, canvasHeight);
    for (int i = 0; i <= 10; i++)
    {
        fprintf(file, "<line x1='%d' y1='%d' x2='%d' y2='%d' stroke='black'/>\n", i * scale, canvasHeight, i * scale, canvasHeight - 5);
        fprintf(file, "<text x='%d' y='%d' text-anchor='middle' font-size='20'>%d</text>\n", i * scale, canvasHeight + 20, i);
        int y = canvasHeight - i * scale;
        fprintf(file, "<line x1='0' y1='%d' x2='5' y2='%d' stroke='black'/>\n", y, y);
        fprintf(file, "<text x='-10' y='%d' text-anchor='middle' font-size='20'>%d</text>\n", y, i);
    }
}

/**
 * @brief Desenha recursivamente as subdivisões e nós da Quadtree no arquivo SVG.
 *
 * @param file Ponteiro para o arquivo SVG.
 * @param q Ponteiro para o nó da Quadtree.
 * @param scale Fator de escala para o desenho.
 */
void draw_scaled_quad(FILE *file, Quad *q, int scale)
{
    if (!q)
        return;
    int canvasHeight = scale * 10;
    if (!isLeafNode(q))
    {
        int yTop = canvasHeight - (q->botRight.y * scale);
        int yBot = canvasHeight - (q->topLeft.y * scale);
        fprintf(file, "<rect x='%d' y='%d' width='%d' height='%d' fill='none' stroke='blue' stroke-width='1'/>\n",
                q->topLeft.x * scale,
                yTop,
                (q->botRight.x - q->topLeft.x) * scale,
                yBot - yTop);
    }
    if (q->n)
    {
        int x = q->n->pos.x * scale;
        int y = canvasHeight - (q->n->pos.y * scale);
        fprintf(file, "<circle cx='%d' cy='%d' r='10' fill='green'/>\n", x, y);
        fprintf(file, "<text x='%d' y='%d' font-size='20' fill='white' text-anchor='middle'>%d</text>\n",
                x, y + 5, q->n->data);
    }
    draw_scaled_quad(file, q->topLeftTree, scale);
    draw_scaled_quad(file, q->topRightTree, scale);
    draw_scaled_quad(file, q->botLeftTree, scale);
    draw_scaled_quad(file, q->botRightTree, scale);
}

/**
 * @brief Gera um arquivo SVG que representa a Quadtree.
 *
 * @param root Ponteiro para a raiz da Quadtree.
 * @param filename Nome do arquivo SVG a ser gerado.
 * @param scale Fator de escala para as dimensões do SVG.
 */
void generate_scaled_svg(Quad *root, const char *filename, int scale)
{
    FILE *file = fopen(filename, "w");
    if (!file)
        return;
    int width = 10 * scale;
    int height = 10 * scale;
    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(file, "<svg viewBox='-50 -50 %d %d' width='%dpx' height='%dpx' version='1.1' xmlns='http://www.w3.org/2000/svg'>\n",
            width + 100, height + 100, width + 100, height + 100);
    draw_axes(file, scale);
    draw_scaled_quad(file, root, scale);
    fprintf(file, "</svg>\n");
    fclose(file);
}
