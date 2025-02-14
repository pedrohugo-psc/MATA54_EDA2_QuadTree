#include <stdio.h>
#include <stdlib.h>
#include "include/quadtree.h"

/**
 * @brief Cria um novo nó da Quadtree com os limites especificados.
 *
 * @param topL Ponto superior esquerdo da região.
 * @param botR Ponto inferior direito da região.
 * @return Quad* Ponteiro para o nó da Quadtree criado.
 */
Quad *Quad_create(Point topL, Point botR)
{
    Quad *q = (Quad *)malloc(sizeof(Quad));
    q->topLeft = topL;
    q->botRight = botR;
    q->n = NULL;
    q->topLeftTree = NULL;
    q->topRightTree = NULL;
    q->botLeftTree = NULL;
    q->botRightTree = NULL;
    q->depth = 0;
    return q;
}

/**
 * @brief Destrói recursivamente a Quadtree e libera a memória alocada.
 *
 * @param q Ponteiro para o nó da Quadtree a ser destruído.
 */
void Quad_destroy(Quad *q)
{
    if (!q)
        return;
    Quad_destroy(q->topLeftTree);
    Quad_destroy(q->topRightTree);
    Quad_destroy(q->botLeftTree);
    Quad_destroy(q->botRightTree);
    if (q->n)
    {
        free(q->n);
    }
    free(q);
}

/**
 * @brief Verifica se um ponto está dentro dos limites especificados.
 *
 * @param p Ponto a ser verificado.
 * @param topLeft Canto superior esquerdo do limite.
 * @param botRight Canto inferior direito do limite.
 * @return true Se o ponto está dentro do limite.
 * @return false Caso contrário.
 */
bool inBoundary(Point p, Point topLeft, Point botRight)
{
    return (p.x >= topLeft.x && p.x <= botRight.x &&
            p.y >= topLeft.y && p.y <= botRight.y);
}

/**
 * @brief Determina se o nó da Quadtree é uma folha.
 *
 * @param q Ponteiro para o nó da Quadtree.
 * @return true Se for nó folha.
 * @return false Caso contrário.
 */
bool isLeafNode(Quad *q)
{
    return (q->botRight.x - q->topLeft.x <= 1) ||
           (q->botRight.y - q->topLeft.y <= 1) ||
           (q->depth >= 3);
}

/**
 * @brief Insere um nó na Quadtree.
 *
 * @param q Ponteiro para o nó da Quadtree.
 * @param node Nó a ser inserido.
 */
void Quad_insert(Quad *q, Node *node)
{
    if (!node || !inBoundary(node->pos, q->topLeft, q->botRight))
        return;

    if (isLeafNode(q))
    {
        if (!q->n)
        {
            q->n = node;
        }
        else
        {
            if (q->n->pos.x == node->pos.x && q->n->pos.y == node->pos.y)
            {
                q->n->data = node->data;
                free(node);
                return;
            }
            Node *existing = q->n;
            q->n = NULL;
            int midX = (q->topLeft.x + q->botRight.x) / 2;
            int midY = (q->topLeft.y + q->botRight.y) / 2;
            q->topLeftTree = Quad_create(q->topLeft, (Point){midX, midY});
            q->topRightTree = Quad_create((Point){midX, q->topLeft.y}, (Point){q->botRight.x, midY});
            q->botLeftTree = Quad_create((Point){q->topLeft.x, midY}, (Point){midX, q->botRight.y});
            q->botRightTree = Quad_create((Point){midX, midY}, q->botRight);
            Quad_insert(q, existing);
            Quad_insert(q, node);
        }
    }
    else
    {
        int midX = (q->topLeft.x + q->botRight.x) / 2;
        int midY = (q->topLeft.y + q->botRight.y) / 2;
        Quad **target = NULL;
        if (node->pos.x <= midX)
        {
            target = (node->pos.y <= midY) ? &q->topLeftTree : &q->botLeftTree;
        }
        else
        {
            target = (node->pos.y <= midY) ? &q->topRightTree : &q->botRightTree;
        }
        if (!*target)
        {
            Point tl, br;
            if (target == &q->topLeftTree)
            {
                tl = q->topLeft;
                br = (Point){midX, midY};
            }
            else if (target == &q->botLeftTree)
            {
                tl = (Point){q->topLeft.x, midY};
                br = (Point){midX, q->botRight.y};
            }
            else if (target == &q->topRightTree)
            {
                tl = (Point){midX, q->topLeft.y};
                br = (Point){q->botRight.x, midY};
            }
            else
            {
                tl = (Point){midX, midY};
                br = q->botRight;
            }
            *target = Quad_create(tl, br);
            (*target)->depth = q->depth + 1;
        }
        Quad_insert(*target, node);
    }
}

/**
 * @brief Busca um nó na Quadtree com base em um ponto.
 *
 * @param q Ponteiro para o nó da Quadtree.
 * @param p Ponto a ser buscado.
 * @return Node* Ponteiro para o nó encontrado ou NULL se não encontrado.
 */
Node *Quad_search(Quad *q, Point p)
{
    if (!inBoundary(p, q->topLeft, q->botRight))
        return NULL;
    if (isLeafNode(q))
    {
        return q->n;
    }
    const int midX = (q->topLeft.x + q->botRight.x) / 2;
    const int midY = (q->topLeft.y + q->botRight.y) / 2;
    if (p.x <= midX)
    {
        return (p.y <= midY) ? (q->topLeftTree ? Quad_search(q->topLeftTree, p) : NULL) : (q->botLeftTree ? Quad_search(q->botLeftTree, p) : NULL);
    }
    return (p.y <= midY) ? (q->topRightTree ? Quad_search(q->topRightTree, p) : NULL) : (q->botRightTree ? Quad_search(q->botRightTree, p) : NULL);
}

/**
 * @brief Realiza uma busca segura na Quadtree e retorna o dado do nó.
 *
 * @param q Ponteiro para o nó da Quadtree.
 * @param p Ponto a ser buscado.
 * @return int Dado do nó se encontrado ou -1 se não encontrado.
 */
int safe_search(Quad *q, Point p)
{
    Node *result = Quad_search(q, p);
    return result ? result->data : -1;
}

/**
 * @brief Remove um nó da Quadtree com base em um ponto.
 *
 * @param q Ponteiro para o nó da Quadtree.
 * @param p Ponto do nó a ser removido.
 */
void Quad_remove(Quad *q, Point p)
{
    if (!q || !inBoundary(p, q->topLeft, q->botRight))
        return;
    if (isLeafNode(q))
    {
        if (q->n != NULL && q->n->pos.x == p.x && q->n->pos.y == p.y)
        {
            free(q->n);
            q->n = NULL;
        }
        return;
    }
    const int midX = (q->topLeft.x + q->botRight.x) / 2;
    const int midY = (q->topLeft.y + q->botRight.y) / 2;
    if (p.x <= midX)
    {
        if (p.y <= midY)
        {
            if (q->topLeftTree)
                Quad_remove(q->topLeftTree, p);
        }
        else
        {
            if (q->botLeftTree)
                Quad_remove(q->botLeftTree, p);
        }
    }
    else
    {
        if (p.y <= midY)
        {
            if (q->topRightTree)
                Quad_remove(q->topRightTree, p);
        }
        else
        {
            if (q->botRightTree)
                Quad_remove(q->botRightTree, p);
        }
    }
    if (q->topLeftTree && q->topRightTree && q->botLeftTree && q->botRightTree)
    {
        if (!q->topLeftTree->n && !q->topRightTree->n &&
            !q->botLeftTree->n && !q->botRightTree->n)
        {
            Quad_destroy(q->topLeftTree);
            Quad_destroy(q->topRightTree);
            Quad_destroy(q->botLeftTree);
            Quad_destroy(q->botRightTree);
            q->topLeftTree = q->topRightTree = q->botLeftTree = q->botRightTree = NULL;
        }
    }
}
