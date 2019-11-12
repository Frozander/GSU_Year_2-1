#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main(int argc, char const *argv[])
{
    AdjMatrixNode **main_matrix = create_matrix_from_data("sensor_locations.csv");
    int n_count = line_counter("sensor_locations.csv") - 1;
    Graph *main_graph = matrix_to_graph(main_matrix, n_count);

    for (size_t i = 0; i < n_count; ++i)
        for (size_t j = i; j < n_count; ++j)
        {
            printf("SensorID: (%d, %d),  Distance to main node: %f, Neighbour Number: %d, Neighbours: ", i, j, main_matrix[i][j].distance, main_graph->vertex_array[i].adj_count);
            for (size_t k = i; k < n_count; ++k)
                if (main_matrix[i][k].distance > 0)
                    printf("%d ", k);
            
            printf("\n");
        }
    
    return 0;
}
