#include "delivery.h"
#include "queue.h"
#include "graph.h"

int main(int argc, char *argv[])
{
    /* -------------------------------------------- Error control and varaible creation -------------------------------------------- */

    Graph *g = NULL;
    FILE *file = NULL;
    long id_from, id_to;
    char *endptr;

    if (argc != 4)
    {
        printf("ERROR: Usage: program <graph_file> <id_from> <id_to>\"\n");
        return 1;
    }
    printf("--> init arguments detected\n");

    /* -------------------------------------------- Init and start graph -------------------------------------------- */

    g = graph_init();
    if (!g)
    {
        printf("ERROR: could not initialize graph\n");
        return 1;
    }
    printf("--> graph initialized\n");


    if (!(file = fopen(argv[1], "r")))
    {
        printf("ERROR: could not open file\n");
        graph_free(g);
        return 1;
    }
    printf("--> target file found\n");

    if (graph_readFromFile(file, g) == ERROR)
    {
        printf("ERROR: could not read graph\n");
        graph_free(g);
        fclose(file);
        return 1;
    }
    printf("--> graph data retrieved from file\n");

    fclose(file);

    /* -------------------------------------------- Check input ids -------------------------------------------- */


    id_from = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || id_from < 0 || !graph_contains(g, id_from))
    {
        printf("ERROR: Invalid vertex \"from\": %s\n", argv[2]);
        graph_free(g);
        return 1;
    }

    id_to = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || id_to < 0 || !graph_contains(g, id_to))
    {
        printf("ERROR: Invalid vertex \"to\": %s\n", argv[3]);
        graph_free(g);
        return 1;
    }
    printf("--> input data is valid\n");


    /* -------------------------------------------- Print graph and execute algorithm -------------------------------------------- */

    printf("Input graph: \n");
    if (graph_print(stdout, g) <= 0)
    {
        printf("ERROR: Could not print graph\n");
        graph_free(g);
        return 1;
    }
    printf("--> graph succesfully printed\n");


    printf("\n-----DFS-----\n\n");
    if (graph_depthSearch(g, id_from, id_to) == ERROR)
    {
        printf("ERROR: Could not execute dfs\n");
        graph_free(g);
        return 1;
    }
    printf("--> dfs completed\n");


    printf("\n-----BFS-----\n\n");
    if (graph_breathSearch(g, id_from, id_to) == ERROR)
    {
        printf("ERROR: Could not execute bfs\n");
        graph_free(g);
        return 1;
    }
    printf("--> bfs completed\n");

    printf("--> program end\n");
    graph_free(g);
    return 0;
}