    #include <stdio.h>
    #include <stdlib.h>
    #include "include/quadtree.h"

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

    void Quad_destroy(Quad* q) {
        if (!q) return;
        Quad_destroy(q->topLeftTree);
        Quad_destroy(q->topRightTree);
        Quad_destroy(q->botLeftTree);
        Quad_destroy(q->botRightTree);
        if (q->n) {
            free(q->n);
        }
        free(q);
    }

    bool inBoundary(Point p, Point topLeft, Point botRight) {
        return (p.x >= topLeft.x && p.x <= botRight.x &&
                p.y >= topLeft.y && p.y <= botRight.y);
    }

    bool isLeafNode(Point topLeft, Point botRight) {
        return (botRight.x - topLeft.x == 0) && 
            (botRight.y - topLeft.y == 0);
    }

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

    int safe_search(Quad* q, Point p) {
        Node* result = Quad_search(q, p);
        return result ? result->data : -1;
    }

    void Quad_remove(Quad* q, Point p) {
        if (!q || !inBoundary(p, q->topLeft, q->botRight)) return;

        // Se for um nó folha, verifica e remove o nó
        if (isLeafNode(q->topLeft, q->botRight)) {
            if (q->n != NULL && q->n->pos.x == p.x && q->n->pos.y == p.y) {
                free(q->n); // Libera o Node
                q->n = NULL;
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

