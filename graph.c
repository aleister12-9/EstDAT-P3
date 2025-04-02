/**
 * @file  graph.c
 * @author Izan Robles
 * @brief Graph library
 */


#include "graph.h"

#define MAX_VTX 4096

struct _Graph
{
    Vertex *vertices[MAX_VTX];
    Bool connections[MAX_VTX][MAX_VTX];
    int num_vertices;
    int num_edges;
};  

/*----------------------------------------------------------------------------------------*/
Graph * graph_init()
{
    Graph *g = NULL;
    int x, y, i;

    if (!(g = (Graph *)malloc(sizeof(Graph))))
    {
        return NULL;
    }

    g->num_edges = 0;
    g->num_vertices = 0;

    for (x = 0; x < MAX_VTX; x++)
    {
        for (y = 0; y < MAX_VTX; y++)
        {
            g->connections[x][y] = FALSE;
        }  
    }

    for (i = 0; i < MAX_VTX; i++)
    {
        g->vertices[i] = NULL;
    }
    
    
    return g;
}

/*----------------------------------------------------------------------------------------*/
void graph_free(Graph *g)
{
    int i;

    if (g != NULL)
    {
        for (i = 0; i < g->num_vertices; i++) 
        {
            vertex_free(g->vertices[i]);
        }
        free(g);
    }
}

/*----------------------------------------------------------------------------------------*/
Status graph_newVertex(Graph *g, char *desc)
{
    Vertex *v;

    if (is_invalid_graph(g) || desc == NULL || g->num_vertices == MAX_VTX)
    {
        return ERROR;
    }

    v = vertex_initFromString(desc);

    if (v == NULL)
    {
        return ERROR;
    }

    else if (is_invalid_vertex(v))
    {
        vertex_free(v);
        return ERROR;
    }
    
    if (graph_contains(g, vertex_getId(v)))
    {
        vertex_free(v);
        return OK;
    }
    
    g->vertices[g->num_vertices] = v;
    vertex_set_index(v, g->num_vertices);
    g->num_vertices++;

    return OK;
}

/*----------------------------------------------------------------------------------------*/
Status graph_newEdge(Graph *g, long orig, long dest)
{
    int orig_index = -1;
    int dest_index = -1;
    int i;
    
    if (is_invalid_graph(g) || orig < 0 || dest < 0)
    {
        return ERROR;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->vertices[i]->id == orig)
        {
            orig_index = i;
        }
        if (g->vertices[i]->id == dest)
        {
            dest_index = i;
        }
    }

    if (orig_index == -1 || dest_index == -1)
    {
        return ERROR;
    }

    if (graph_connectionExists(g, orig_index, dest_index))
    {
        return OK;
    }
    
    g->connections[orig_index][dest_index] = TRUE;
    g->num_edges++;

    return OK;
}

/*----------------------------------------------------------------------------------------*/
Bool graph_contains(const Graph *g, long id)
{
    int i;
    
    if (is_invalid_graph(g) || id < 0)
    {
        return FALSE;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->vertices[i]->id == id)
        {
            return TRUE;
        }        
    }

    return FALSE;
}

/*----------------------------------------------------------------------------------------*/
int graph_getNumberOfVertices(const Graph *g)
{
    if (is_invalid_graph(g))
    {
        return -1;
    }

    return g->num_vertices;
}

/*----------------------------------------------------------------------------------------*/
int graph_getNumberOfEdges(const Graph *g)
{
    if (is_invalid_graph(g))
    {
        return -1;
    }

    return g->num_edges;
}

/*----------------------------------------------------------------------------------------*/
Bool graph_connectionExists(const Graph *g, long orig, long dest)
{
    int orig_index = -1;
    int dest_index = -1;
    int i;
    
    if (is_invalid_graph(g) || orig < 0 || dest < 0)
    {
        return FALSE;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->vertices[i]->id == orig)
        {
            orig_index = i;
        }
        if (g->vertices[i]->id == dest)
        {
            dest_index = i;
        }
    }

    if (orig_index == -1 || dest_index == -1)
    {
        return FALSE;
    }

    return g->connections[orig_index][dest_index];
}

/*----------------------------------------------------------------------------------------*/
int graph_getNumberOfConnectionsFromId(const Graph *g, long id)
{
    int counter = 0;
    int index = -1;
    int i;
    
    if (is_invalid_graph(g) || id < 0)
    {
        return -1;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->vertices[i]->id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        return -1;
    }

    for (i = 0; i < MAX_VTX; i++)
    {
        if (g->connections[index][i] == TRUE)
        {
            counter++;
        }
    }
    
    return counter;
}

/*----------------------------------------------------------------------------------------*/
long *graph_getConnectionsFromId(const Graph *g, long id)
{
    long *connections = NULL;
    int n_connections = 0;
    int counter = 0;
    int index = -1;
    int i;

    if (is_invalid_graph(g) || id < 0)
    {
        return NULL;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->vertices[i]->id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        return NULL;
    }

    n_connections = graph_getNumberOfConnectionsFromId(g, id);

    if (n_connections == -1)
    {
        return NULL;
    }

    if (!(connections = (long *)malloc(n_connections * sizeof(long))))
    {
        return NULL;
    }

    for (i = 0; i < MAX_VTX; i++)
    {
        if (g->connections[index][i] == TRUE)
        {
            connections[counter] = g->vertices[i]->id;
            counter++;
        }
    }

    return connections;
}

/*----------------------------------------------------------------------------------------*/
int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag)
{
    int i;
    
    if (is_invalid_graph(g) || tag == NULL)
    {
        return -1;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (strcmp(g->vertices[i]->tag, tag) == 0)
        {
            return graph_getNumberOfConnectionsFromId(g, g->vertices[i]->id);
        }
    }

    return -1;
} 

/*----------------------------------------------------------------------------------------*/
long *graph_getConnectionsFromTag(const Graph *g, char *tag)
{
    int i;
    
    if (is_invalid_graph(g) || tag == NULL)
    {
        return NULL;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (strcmp(g->vertices[i]->tag, tag) == 0)
        {
            return graph_getConnectionsFromId(g, g->vertices[i]->id);
        }
    }

    return NULL;
}

/*----------------------------------------------------------------------------------------*/
int graph_print (FILE *pf, const Graph *g)
{
    int character_counter = 0;
    int i, j;

    if (is_invalid_graph(g) || pf == NULL)
    {
        return -1;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        character_counter += vertex_print(pf, g->vertices[i]);
        character_counter += fprintf(pf, ": ");
        for (j = 0; j < MAX_VTX; j++)
        {
            if (g->connections[i][j] == TRUE)
            {
                character_counter += vertex_print(pf, g->vertices[j]);
            }
        }

        character_counter += fprintf(pf, "\n");
    }

    return character_counter;
} 

/*----------------------------------------------------------------------------------------*/
Status graph_readFromFile (FILE *fin, Graph *g)
{
    int num_vertices = 0;
    char temp[MAX_DATA];
    int temp_id_orig = 0;
    int temp_id_dest = 0;
    int i;

    if (is_invalid_graph(g) || fin == NULL)
    {
        return ERROR;
    }

    fscanf(fin, "%d\n", &num_vertices);
    if (num_vertices < 1)
    {
        return ERROR;
    }

    for (i = 0; i < num_vertices; i++)
    {
        if (fgets(temp, MAX_DATA, fin) == NULL)
        {
            return ERROR;
        }
        
        if (graph_newVertex(g, temp) == ERROR)
        {
            return ERROR;
        }

        if (vertex_set_index(g->vertices[i], i) == ERROR)
        {
            return ERROR;
        }
        
    }

    while (fscanf(fin, "%d %d\n", &temp_id_orig, &temp_id_dest) == 2)
    {
        if (graph_newEdge(g, temp_id_orig, temp_id_dest) == ERROR)
        {
            return ERROR;
        }
    }

    return OK;
}

/*----------------------------------------------------------------------------------------*/
Bool is_invalid_graph (const Graph *g)
{
    int i;
    
    if (g == NULL)
    {
        return TRUE;
    }

    if (g->num_vertices < 0 || g->num_vertices > MAX_VTX)
    {
        return TRUE;
    }

    if (g->num_edges < 0 || g->num_edges > MAX_VTX * MAX_VTX)
    {
        return TRUE;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->vertices[i] == NULL || vertex_get_index(g->vertices[i]) != i || is_invalid_vertex(g->vertices[i]))
        {
            return TRUE;
        }
    }
    
    return FALSE;
}

/*----------------------------------------------------------------------------------------*/
Status graph_set_all_vertex_label(Graph *g, Label l)
{
    int i;
    Label *backup = NULL;


    if (is_invalid_graph(g) || (l != WHITE && l != BLACK && l != ERROR_VERTEX))
    {
        return ERROR;
    }
    
    /*Create backup in case something fails*/
    backup = (Label *)malloc(g->num_vertices * sizeof(Label));
    if (!backup) 
    {
         return ERROR;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        backup[i] = vertex_getState(g->vertices[i]);
        if (backup[i] == ERROR_VERTEX)
        {
            free(backup);
            return ERROR;
        }
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (vertex_setState(g->vertices[i], l) == ERROR)
        {
            for (; i >= 0; i--)
            {
                vertex_setState(g->vertices[i], backup[i]);
            }
            free(backup);
            return ERROR;
        }
    }
    
    free(backup);
    return OK;
}

/*----------------------------------------------------------------------------------------*/
Vertex **graph_get_vertex_array(Graph *g)
{
    if (is_invalid_graph(g))
    {
        return NULL;
    }

    return g->vertices;
}

/*----------------------------------------------------------------------------------------*/
Status graph_depthSearch(Graph *g, long from_id, long to_id)
{
    int i, j, num_vertices;
    Stack *st = NULL;
    Vertex **vertex_array = NULL;
    Vertex *current = NULL;
    Vertex *neighbor = NULL;
    long *connections = NULL;
    int n_connections = 0;

    if (is_invalid_graph(g) || from_id < 0 || to_id < 0)
    {
        return ERROR;
    }

    /*Set all vertices to white*/
    if (graph_set_all_vertex_label(g, WHITE) == ERROR)
    {
        printf("Could not perform algorithm (Code 001)");
    }

    /*Execute algorithm*/
    if (!(st = stack_init()))
    {
        return ERROR;
    }

    if ((num_vertices = graph_getNumberOfVertices(g)) < 0)
    {
        stack_free(st);
        printf("Could not perform algorithm (Code 002)");
        return ERROR;
    }

    if (!(vertex_array = graph_get_vertex_array(g)))
    {
        stack_free(st);
        printf("Could not perform algorithm (Code 003)");
        return ERROR;
    }

    /*Find "from" vertex, paint black and add to stack*/
    for (i = 0; i < num_vertices; i++) {
        if (vertex_getId(vertex_array[i]) == from_id) {
            vertex_setState(vertex_array[i], BLACK);
            stack_push(st, vertex_array[i]);
            break;
        }
    }

    /*Main loop for algorithm*/
    printf("From vertex ID: %ld\n", from_id);
    printf("To vertex id: %ld\n", to_id);

    while (!stack_isEmpty(st))
    {
        current = stack_pop(st);
        vertex_print(stdout, current);
        printf("\n");

        /* Check if we found target */
        if (vertex_getId(current) == to_id)
        {
            stack_free(st);
            return OK;
        }

        /* Get connections for current vertex */
        n_connections = graph_getNumberOfConnectionsFromId(g, vertex_getId(current));
        if (n_connections < 0)
        {
            stack_free(st);
            return ERROR;
        }

        connections = graph_getConnectionsFromId(g, vertex_getId(current));
        if (!connections && n_connections > 0)
        {
            stack_free(st);
            return ERROR;
        }

        /* Add unvisited neighbors to stack */
        for (j = 0; j < n_connections; j++)
        {
            /* Find neighbor vertex object from its ID */
            for (i = 0; i < num_vertices; i++)
            {
                if (vertex_getId(vertex_array[i]) == connections[j])
                {
                    neighbor = vertex_array[i];
                    break;
                }
            }

            /* If neighbor is unvisited, mark it and add to stack */
            if (vertex_getState(neighbor) == WHITE)
            {
                vertex_setState(neighbor, BLACK);
                if (stack_push(st, neighbor) == ERROR)
                {
                    stack_free(st);
                    free(connections);
                    return ERROR;
                }
            }
        }

        if (connections)
        {
            free(connections);
        }
    }

    stack_free(st);

    return OK;
}

/*----------------------------------------------------------------------------------------*/
Status graph_breathSearch (Graph *g, long from_id, long to_id)
{
    int i, j, num_vertices;
    Queue *qu = NULL;
    Vertex **vertex_array = NULL;
    Vertex *current = NULL;
    Vertex *neighbor = NULL;
    long *connections = NULL;
    int n_connections = 0;

    if (is_invalid_graph(g) || from_id < 0 || to_id < 0)
    {
        return ERROR;
    }

    /*Set all vertices to white*/
    if (graph_set_all_vertex_label(g, WHITE) == ERROR)
    {
        printf("Could not perform algorithm (Code 001)");
    }

    /*Execute algorithm*/
    if (!(qu = queue_new()))
    {
        return ERROR;
    }

    if ((num_vertices = graph_getNumberOfVertices(g)) < 0)
    {
        queue_free(qu);
        printf("Could not perform algorithm (Code 002)");
        return ERROR;
    }

    if (!(vertex_array = graph_get_vertex_array(g)))
    {
        queue_free(qu);
        printf("Could not perform algorithm (Code 003)");
        return ERROR;
    }

    /*Find "from" vertex, paint black and add to stack*/
    for (i = 0; i < num_vertices; i++) {
        if (vertex_getId(vertex_array[i]) == from_id) {
            vertex_setState(vertex_array[i], BLACK);
            queue_push(qu, vertex_array[i]);
            break;
        }
    }

    /*Main loop for algorithm*/
    printf("From vertex ID: %ld\n", from_id);
    printf("To vertex id: %ld\n", to_id);

    while (!queue_isEmpty(qu))
    {
        current = queue_pop(qu);
        vertex_print(stdout, current);
        printf("\n");

        /* Check if we found target */
        if (vertex_getId(current) == to_id)
        {
            queue_free(qu);
            return OK;
        }

        /* Get connections for current vertex */
        n_connections = graph_getNumberOfConnectionsFromId(g, vertex_getId(current));
        if (n_connections < 0)
        {
            queue_free(qu);
            return ERROR;
        }

        connections = graph_getConnectionsFromId(g, vertex_getId(current));
        if (!connections && n_connections > 0)
        {
            queue_free(qu);
            return ERROR;
        }

        /* Add unvisited neighbors to stack */
        for (j = 0; j < n_connections; j++)
        {
            /* Find neighbor vertex object from its ID */
            for (i = 0; i < num_vertices; i++)
            {
                if (vertex_getId(vertex_array[i]) == connections[j])
                {
                    neighbor = vertex_array[i];
                    break;
                }
            }

            /* If neighbor is unvisited, mark it and add to stack */
            if (vertex_getState(neighbor) == WHITE)
            {
                vertex_setState(neighbor, BLACK);
                if (queue_push(qu, neighbor) == ERROR)
                {
                    queue_free(qu);
                    free(connections);
                    return ERROR;
                }
            }
        }

        if (connections)
        {
            free(connections);
        }
    }

    queue_free(qu);

    return OK;
}



