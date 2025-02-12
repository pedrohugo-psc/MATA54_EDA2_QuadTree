#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/quadtree.h"
#include "include/map_quadtree.h"

void insert_point(int x, int y, int data, Quad **map){
    Node* point = (Node*)malloc(sizeof(Node));
    point->pos = (Point){x, y};
    point->data = data;
    Quad_insert((*map), point);
}

int main() {
    int option = 0;
    int x = 0;
    int y = 0;
    int data = 0;

    Quad* map = Quad_create((Point){0, 0}, (Point){8, 8});
    

    printf("Trabalho sobre Quadtree:\n");
    printf("\n");

    while (1)
    {
        printf("Selecione as opções a seguir:\n3 - Adicionar um ponto\n2 - Remover um ponto\n1 - Buscar um ponto\n0 - Sair do programa para gerar o mapa\n");
        scanf("%d", &option);

        switch (option)
        {
        case 3:
            printf("Digite um valor para x: ");
            scanf("%d", &x);
            printf("Digite um valor para y: ");
            scanf("%d", &y);
            printf("Digite um valor para o registro: ");
            scanf("%d", &data);

            insert_point(x,y,data,&map);

            break;
        
        case 2:
            printf("Digite um valor para x: ");
            scanf("%d", &x);
            printf("Digite um valor para y: ");
            scanf("%d", &y);
            Quad_remove(map, (Point){x, y});
            break;

        case 1:{
            printf("Digite um valor para x: ");
            scanf("%d", &x);
            printf("Digite um valor para y: ");
            scanf("%d", &y);

            int data_point = safe_search(map, (Point){x, y});

            if (data_point != -1)
            {
                printf("Valor do no: %d\n", data_point);
            }else
            {
                printf("No nao encontrado\n");
            }    
            break;
        }
        case 0:
            printf("Saindo do programa e gerando o mapa\n");
            break;
        
        default:
            printf("Escolheu o digito errado. Deve-se digitar 3, 2, 1 ou 0\n");
            break;
        }
        printf("\n");

        if (option == 0)
        {
            break;
        }

    }

    // Gera a imagem SVG
    generate_scaled_svg(map, "quadtree.svg", 100);
    printf("Imagem gerada: quadtree.svg\n");

    Quad_destroy(map);
    return 0;
}