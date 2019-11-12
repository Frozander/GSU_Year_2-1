#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main(int argc, char const *argv[])
{
    AdjMatrixNode **main_matrix = create_matrix_from_data("sensor_locations.csv");
    int n_count = line_counter("sensor_locations.csv") - 1;
    for (int i = 0; i < n_count; ++i)
    {
        for (int j = 0; j < n_count; ++j)
        {
            printf("%.2f - ", main_matrix[i][j].distance);
        }
        printf("\n\n");
    }
    
    return 0;
}
