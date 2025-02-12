#include "quadtree.h"
#include <stdio.h>

#ifndef MAP_QUADTREE_H
#define MAP_QUADTREE_H

void generate_scaled_svg(Quad* root, const char* filename, int scale);
void draw_scaled_quad(FILE* file, Quad* q, int scale);
void draw_axes(FILE* file, int scale);

#endif // MAP_QUADTREE_H