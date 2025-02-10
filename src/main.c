#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Node {
    Point pos;
    int data;
} Node;

typedef struct Quad {
    Point topLeft;
    Point botRight;
    
    Node* n;
    
    struct Quad* topLeftTree;
    struct Quad* topRightTree;
    struct Quad* botLeftTree;
    struct Quad* botRightTree;
} Quad;

// Protótipos de funções
Quad* Quad_create(Point topL, Point botR);
void Quad_destroy(Quad* q);
void Quad_insert(Quad* q, Node* node);
Node* Quad_search(Quad* q, Point p);
bool inBoundary(Point p, Point topLeft, Point botRight);
bool isLeafNode(Point topLeft, Point botRight);
void Quad_remove(Quad* q, Point p);

// Função de criação do Quad
Quad* Quad_create(Point topL, Point botR) {
    Quad* q = (Quad*)malloc(sizeof(Quad));
    q->topLeft = topL;
    q->botRight = botR;
    q->n = NULL;
    q->topLeftTree = NULL;
    q->topRightTree = NULL;
    q->botLeftTree = NULL;
    q->botRightTree = NULL;
    return q;
}

// Função de destruição recursiva
void Quad_destroy(Quad* q) {
    if (!q) return;
    Quad_destroy(q->topLeftTree);
    Quad_destroy(q->topRightTree);
    Quad_destroy(q->botLeftTree);
    Quad_destroy(q->botRightTree);
    free(q);
}

// Verifica se um ponto está dentro dos limites
bool inBoundary(Point p, Point topLeft, Point botRight) {
    return (p.x >= topLeft.x && p.x <= botRight.x &&
            p.y >= topLeft.y && p.y <= botRight.y);
}

// Verifica se é um nó folha
bool isLeafNode(Point topLeft, Point botRight) {
    return (botRight.x - topLeft.x == 0) && 
           (botRight.y - topLeft.y == 0);
}

// Função de inserção
void Quad_insert(Quad* q, Node* node) {
    if (!node || !inBoundary(node->pos, q->topLeft, q->botRight)) return;

    if (isLeafNode(q->topLeft, q->botRight)) {
        q->n = node;
        return;
    }

    const int midX = (q->topLeft.x + q->botRight.x) / 2;
    const int midY = (q->topLeft.y + q->botRight.y) / 2;

    if (node->pos.x <= midX) {
        if (node->pos.y <= midY) {
            if (!q->topLeftTree) {
                q->topLeftTree = Quad_create(q->topLeft, 
                    (Point){midX, midY});
            }
            Quad_insert(q->topLeftTree, node);
        } else {
            if (!q->botLeftTree) {
                q->botLeftTree = Quad_create(
                    (Point){q->topLeft.x, midY + 1},
                    (Point){midX, q->botRight.y});
            }
            Quad_insert(q->botLeftTree, node);
        }
    } else {
        if (node->pos.y <= midY) {
            if (!q->topRightTree) {
                q->topRightTree = Quad_create(
                    (Point){midX + 1, q->topLeft.y},
                    (Point){q->botRight.x, midY});
            }
            Quad_insert(q->topRightTree, node);
        } else {
            if (!q->botRightTree) {
                q->botRightTree = Quad_create(
                    (Point){midX + 1, midY + 1},
                    q->botRight);
            }
            Quad_insert(q->botRightTree, node);
        }
    }
}

// Função de busca
Node* Quad_search(Quad* q, Point p) {
    if (!inBoundary(p, q->topLeft, q->botRight)) return NULL;
    
    if (isLeafNode(q->topLeft, q->botRight)) {
        return q->n;
    }

    const int midX = (q->topLeft.x + q->botRight.x) / 2;
    const int midY = (q->topLeft.y + q->botRight.y) / 2;

    if (p.x <= midX) {
        return (p.y <= midY) ? 
            (q->topLeftTree ? Quad_search(q->topLeftTree, p) : NULL) :
            (q->botLeftTree ? Quad_search(q->botLeftTree, p) : NULL);
    }
    return (p.y <= midY) ? 
        (q->topRightTree ? Quad_search(q->topRightTree, p) : NULL) :
        (q->botRightTree ? Quad_search(q->botRightTree, p) : NULL);
}

// Função auxiliar para busca segura
int safe_search(Quad* q, Point p) {
    Node* result = Quad_search(q, p);
    return result ? result->data : -1;
}

// Função para remover um nó em uma posição específica
void Quad_remove(Quad* q, Point p) {
    if (!q || !inBoundary(p, q->topLeft, q->botRight)) return;

    // Se for um nó folha, verifica e remove o nó
    if (isLeafNode(q->topLeft, q->botRight)) {
        if (q->n != NULL && q->n->pos.x == p.x && q->n->pos.y == p.y) {
            q->n = NULL;  // Remove o nó
        }
        return;
    }

    // Calcula os pontos médios
    const int midX = (q->topLeft.x + q->botRight.x) / 2;
    const int midY = (q->topLeft.y + q->botRight.y) / 2;

    // Navega recursivamente no quadrante apropriado
    if (p.x <= midX) {
        if (p.y <= midY) {
            if (q->topLeftTree) Quad_remove(q->topLeftTree, p);
        } else {
            if (q->botLeftTree) Quad_remove(q->botLeftTree, p);
        }
    } else {
        if (p.y <= midY) {
            if (q->topRightTree) Quad_remove(q->topRightTree, p);
        } else {
            if (q->botRightTree) Quad_remove(q->botRightTree, p);
        }
    }
}

// Função para desenhar os eixos e a escala
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

int main() {
    Quad* center = Quad_create((Point){0, 0}, (Point){8, 8});
    
    Node a = {(Point){1, 1}, 1};
    Node b = {(Point){2, 5}, 2};
    Node c = {(Point){7, 6}, 3};
    Node d = {(Point){4, 2}, 32};
    Node e = {(Point){6, 2}, 5};
    Node f = {(Point){4, 1}, 4};
    Node g = {(Point){2, 3}, 6};
    Node h = {(Point){5, 7}, 8};
    Node i = {(Point){4, 7}, 9};
    
    Quad_insert(center, &a);
    Quad_insert(center, &b);
    Quad_insert(center, &c);
    Quad_insert(center, &d);  // Teste de duplicação
    Quad_insert(center, &e);  // Teste de duplicação
    Quad_insert(center, &f);  // Teste de duplicação
    Quad_insert(center, &g);  // Teste de duplicação
    Quad_insert(center, &h);  // Teste de duplicação
    Quad_insert(center, &i);  // Teste de duplicação

    printf("Node a: %d\n", safe_search(center, (Point){4, 2}));
    printf("Node b: %d\n", safe_search(center, (Point){4, 1}));
    printf("Node c: %d\n", safe_search(center, (Point){4, 7}));
    printf("Non-existing node: %d\n", safe_search(center, (Point){5, 5}));

    Quad_remove(center, (Point){1, 1});
    Quad_remove(center, (Point){9, 9});  // Teste de ponto fora dos limites

    // printf("Node a: %d\n", safe_search(center, (Point){1, 1}));  // -1
    // printf("Node b: %d\n", safe_search(center, (Point){2, 5}));  // 2
    // printf("Node c: %d\n", safe_search(center, (Point){7, 6}));

    // Gera a imagem SVG
    generate_scaled_svg(center, "quadtree.svg", 100);
    printf("Imagem gerada: quadtree.svg\n");

    Quad_destroy(center);
    return 0;
}