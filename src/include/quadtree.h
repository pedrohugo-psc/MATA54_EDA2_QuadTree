#include <stdbool.h>

#ifndef QUADTREE_H
#define QUADTREE_H

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

Quad* Quad_create(Point topL, Point botR);
void Quad_destroy(Quad* q);
void Quad_insert(Quad* q, Node* node);
Node* Quad_search(Quad* q, Point p);
bool inBoundary(Point p, Point topLeft, Point botRight);
bool isLeafNode(Point topLeft, Point botRight);
void Quad_remove(Quad* q, Point p);
int safe_search(Quad* q, Point p);

#endif // QUADTREE_H