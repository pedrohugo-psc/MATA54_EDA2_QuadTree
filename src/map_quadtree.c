#include "include/map_quadtree.h"
#include "include/quadtree.h" 

void draw_axes(FILE* file, int scale) {
    // Desenha eixos x e y
    fprintf(file, "<line x1='0' y1='%d' x2='%d' y2='%d' stroke='black'/>\n", 
            scale*8, scale*8, scale*8); // Eixo x
    fprintf(file, "<line x1='0' y1='0' x2='0' y2='%d' stroke='black'/>\n", 
            scale*8); // Eixo y

    // Desenha ticks e labels
    for (int i = 0; i <= 8; i++) {
        // Eixo x (horizontal)
        fprintf(file, "<line x1='%d' y1='%d' x2='%d' y2='%d' stroke='black'/>\n", 
                i*scale, scale*8 - 5, i*scale, scale*8); // Tick
        fprintf(file, "<text x='%d' y='%d' text-anchor='middle' font-size='20'>%d</text>\n", 
                i*scale, scale*8 + 30, i); // Label

        // Eixo y (vertical)
        fprintf(file, "<line x1='0' y1='%d' x2='5' y2='%d' stroke='black'/>\n", 
                i*scale, i*scale); // Tick
        fprintf(file, "<text x='-30' y='%d' text-anchor='middle' font-size='20' transform='rotate(-90)'>%d</text>\n", 
                i*scale + 5, i); // Label
    }
}

void draw_scaled_quad(FILE* file, Quad* q, int scale) {
    if (!q) return;

    // Desenha o quadrante atual
    fprintf(file, "<rect x='%d' y='%d' width='%d' height='%d' fill='none' stroke='blue' stroke-width='2'/>\n",
            q->topLeft.x * scale,
            q->topLeft.y * scale,
            (q->botRight.x - q->topLeft.x + 1) * scale,
            (q->botRight.y - q->topLeft.y + 1) * scale);

    // Desenha o nó (se existir) com rótulo
    if (q->n) {
        fprintf(file, "<circle cx='%d' cy='%d' r='10' fill='red'/>\n",
                q->n->pos.x * scale + scale/2,
                q->n->pos.y * scale + scale/2);
                
        fprintf(file, "<text x='%d' y='%d' font-size='20' fill='white'>%d</text>\n",
                q->n->pos.x * scale + scale/2 - 7,
                q->n->pos.y * scale + scale/2 + 5,
                q->n->data);

    }

    // Renderiza recursivamente os sub-quadrantes
    draw_scaled_quad(file, q->topLeftTree, scale);
    draw_scaled_quad(file, q->topRightTree, scale);
    draw_scaled_quad(file, q->botLeftTree, scale);
    draw_scaled_quad(file, q->botRightTree, scale);
}

void generate_scaled_svg(Quad* root, const char* filename, int scale) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    int width = 8 * scale + 100;
    int height = 8 * scale + 100;

    fprintf(file, "<svg viewBox='0 0 %d %d' xmlns='http://www.w3.org/2000/svg'>\n", width, height);
    fprintf(file, "<g transform='translate(50, %d) scale(1, -1)'>\n", height - 50); // Inverte o eixo Y

    draw_axes(file, scale);
    draw_scaled_quad(file, root, scale);

    fprintf(file, "</g>\n</svg>");
    fclose(file);
}