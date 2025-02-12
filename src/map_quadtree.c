#include "include/map_quadtree.h"
#include "include/quadtree.h"

void draw_axes(FILE* file, int scale) {
    int canvasHeight = scale * 10;

    // Desenha eixo x
    fprintf(file, "<line x1='0' y1='%d' x2='%d' y2='%d' stroke='black' stroke-width='2'/>\n", 
            canvasHeight, 0, canvasHeight);
    // Desenha eixo y (-note que y1 agora é canvasHeight)
    fprintf(file, "<line x1='0' y1='%d' x2='0' y2='%d' stroke='black' stroke-width='2'/>\n", 
            canvasHeight, 0);
    
    // Desenha labels dos eixos
    fprintf(file, "<text x='-30' y='%d' font-size='20'>y</text>\n", canvasHeight + 25);
    fprintf(file, "<text x='%d' y='%d' font-size='20'>x</text>\n", canvasHeight - 130, canvasHeight);

    // Desenha ticks e labels
    for (int i = 0; i <= 10; i++) {
        // Eixo x
        fprintf(file, "<line x1='%d' y1='%d' x2='%d' y2='%d' stroke='black'/>\n", 
                i * scale, canvasHeight, i * scale, canvasHeight - 5);
        fprintf(file, "<text x='%d' y='%d' text-anchor='middle' font-size='15'>%d</text>\n", 
                i * scale, canvasHeight + 20, i);
        
        // Eixo y
        int y = canvasHeight - i * scale;
        fprintf(file, "<line x1='0' y1='%d' x2='5' y2='%d' stroke='black'/>\n", 
                y, y);
        fprintf(file, "<text x='-25' y='%d' text-anchor='middle' font-size='15'>%d</text>\n", 
                y, i);
    }
}

void draw_scaled_quad(FILE* file, Quad* q, int scale) {
    if (!q) return;

    int canvasHeight = scale * 10;

    if (!isLeafNode(q->topLeft, q->botRight)) {
        int yTop = canvasHeight - (q->botRight.y * scale);
        int yBot = canvasHeight - (q->topLeft.y * scale);
        
        fprintf(file, "<rect x='%d' y='%d' width='%d' height='%d' fill='none' stroke='blue' stroke-width='1'/>\n",
                q->topLeft.x * scale,
                yTop,
                (q->botRight.x - q->topLeft.x) * scale,
                yBot - yTop);
    }

    // Desenha o nó com destaque
    if (q->n) {
        int centerX = (q->topLeft.x + q->botRight.x) * scale / 2;
        int centerY = canvasHeight - ((q->topLeft.y + q->botRight.y) * scale / 2);
        
        // Desenha um círculo cheio de verde para destacar o nó
        fprintf(file, "<circle cx='%d' cy='%d' r='10' fill='green'/>\n", centerX, centerY);
        // Desenha o valor do nó em branco no centro do círculo
        fprintf(file, "<text x='%d' y='%d' font-size='20' fill='white' text-anchor='middle'>%d</text>\n",
               centerX, centerY, q->n->data);
    }

    // Processa os filhos
    draw_scaled_quad(file, q->topLeftTree, scale);
    draw_scaled_quad(file, q->topRightTree, scale);
    draw_scaled_quad(file, q->botLeftTree, scale);
    draw_scaled_quad(file, q->botRightTree, scale);
}

void generate_scaled_svg(Quad* root, const char* filename, int scale) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    // Define o tamanho do canvas
    int width = 10 * scale;
    int height = 10 * scale;

    // Cria o arquivo SVG
    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(file, "<svg viewBox='-50 -50 %d %d' width='%dpx' height='%dpx' version='1.1' xmlns='http://www.w3.org/2000/svg'>\n",
            width + 100, height + 100, width + 100, height + 100);

    // Desenha os eixos e o quadtree
    draw_axes(file, scale);
    draw_scaled_quad(file, root, scale);

    fprintf(file, "</svg>\n");
    fclose(file);
}
