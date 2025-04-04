/**
 * @file  graph.h
 * @author Teachers at EPS
 * @brief Graph library
 */


#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include "stack.h"
#include "queue.h"

typedef struct _Graph Graph;

/**
 * @brief Creates a new empty graph.
 * 
 * @author Izan Robles
 *
 * Allocates memory for a new graph and initializes it to be empty 
 * (no vertices and no edges).
 *
 * @return A pointer to the graph if it was correctly allocated, 
 * NULL otherwise.
 **/
Graph * graph_init();

/**
 * @brief Frees a graph.
 * 
 * @author Izan Robles
 *
 * Frees all the memory allocated for the graph.
 *
 * @param g Pointer to graph to be freed.
 **/
void graph_free(Graph *g);

/**
 * @brief Inserts a new vertex in a graph.
 *
 * @author Izan Robles
 * 
 * Creates a vertex by calling vertex_initFromString and adds it to
 * a graph. If a vertex with the same id already exists in the graph, 
 * it is not added. 
 *
 * @param g Pointer to the graph.
 * @param desc Description of the vertex.
 *
 * @return Returns OK if the vertex could be created (or if it exists 
 * already), ERROR otherwise.
 **/
Status graph_newVertex(Graph *g, char *desc);

/**
 * @brief Creates an edge between to vertices of a graph.
 *
 * @author Izan Robles
 * 
 * If any of the two vertices does not exist in the graph the edge is
 * not created.
 *
 * @param g Pointer to the graph.
 * @param orig ID of the origin vertex.
 * @param dest ID of the destination vertex.
 *
 * @return OK if the edge could be added to the graph, ERROR otherwise.
 **/
Status graph_newEdge(Graph *g, long orig, long dest);

/**
 * @brief Checks if a graph contains a vertex.
 * 
 * @author Izan Robles
 * 
 * @param g Pointer to the graph.
 * @param id ID of the vertex.
 *
 * @return Returns TRUE if there is a vertex in the graph g with the
 * ID id, FALSE otherwise.
 **/
Bool graph_contains(const Graph *g, long id);

/**
 * @brief Returns the total number of vertices in a graph.
 * 
 * @author Izan Robles
 *
 * @param g Pointer to the graph.
 *
 * @return Returns The number of vertices in the graph, or -1 if 
 * there is any error.
 **/
int graph_getNumberOfVertices(const Graph *g);

/**
 * @brief Returns the total number of edges  * in the graph.
 *
 * @author Izan Robles
 * 
 * @param g Pointer to the graph.
 *
 * @return Returns The number of vertices in the graph, or -1 if 
 * there is any error.
 **/
int graph_getNumberOfEdges(const Graph *g);

/**
 * @brief Determines if there is a connection between a pair of vertices.
 *
 * @author Izan Robles
 * 
 * @param g Pointer to the graph.
 * @param orig ID of the origin vertex.
 * @param dest ID of the destination vertex.
 *
 * @return Returns TRUE if there is a connection in g from orig
 *  to dest, FALSE otherwise.
 **/
Bool graph_connectionExists(const Graph *g, long orig, long dest);

/**
 * @brief Gets the number of connections starting at a given vertex.
 *
 * @author Izan Robles
 * 
 * @param g Pointer to the graph.
 * @param id ID of the origin vertex.
 *
 * @return Returns the total number of connections starting at 
 * vertex with ID id, or -1 if there is any error.
 **/
int graph_getNumberOfConnectionsFromId(const Graph *g, long id);

/**
 * @brief Returns an array with the ids of all the vertices which a 
 * given vertex connects to.
 * 
 * @author Izan Robles
 *
 * This function allocates memory for the array.
 *
 * @param g Pointer to the graph.
 * @param id ID of the origin vertex.
 *
 * @return Returns an array with the ids of all the vertices to which 
 * the vertex with ID id is connected, or NULL if there is any error.
 */
long *graph_getConnectionsFromId(const Graph *g, long id);

/**
 * @brief Gets the number of connections starting at a given vertex.
 *
 * @author Izan Robles
 * 
 * @param g Pointer to the graph.
 * @param tag Tag of the origin vertex.
 *
 * @return Returns the total number of connections starting at 
 * vertex with Tag tag, or -1 if there is any error.
 **/
int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag);

/**
 * @brief Returns an array with the ids of all the vertices which a 
 * given vertex connects to.
 *
 * @author Izan Robles
 * @author Arturo Pérez
 * 
 * This function allocates memory for the array.
 *
 * @param g Pointer to the graph.
 * @param tag Tag of the origin vertex.
 *
 * @return Returns an array with the ids of all the vertices to which 
 * the vertex with Tag tag is connected, or NULL if there is any error.
 */
long *graph_getConnectionsFromTag(const Graph *g, char *tag);

/**
 * @brief Prints a graph.
 *
 * @author Izan Robles
 * @author Arturo Pérez
 * 
 * Prints the graph g to the file pf.
 * The format to be followed is: print a line by vertex with the 
 * information associated with the vertex and the id of their connections:
 *
 * For example:
 * [1, Madrid, 0]: [2, Toledo, 0] [3, Avila, 0] 
 * [2, Toledo, 0]: [4, Segovia, 0] 
 * [3, Avila, 0]: 
 * [4, Segovia, 0]: [3, Avila, 0]
 *
 * @param pf File descriptor.
 * @param g Pointer to the graph.
 *
 * @return The number of characters printed, or -1 if there is any error.
 */
int graph_print (FILE *pf, const Graph *g);


/**
 * @brief Reads a graph definition from a text file.
 *
 * @author Izan Robles
 * 
 * Reads a graph description from the text file pointed to by fin,
 * and fills the graph g.
 *
 * The first line in the file contains the number of vertices.
 * Then one line per vertex with the vertex description.  
 * Finally one line per connection, with the ids of the origin and 
 * the destination. 
 *
 * For example:
 *
 * 4
 * id:1 tag:Madrid
 * id:2 tag:Toledo
 * id:3 tag:Avila
 * id:4 tag:Segovia
 * 1 2
 * 1 3
 * 2 4
 * 4 3
 *
 * @param fin Pointer to the input stream.
 * @param g Pointer to the graph.
 *
 * @return OK or ERROR
 */
Status graph_readFromFile (FILE *fin, Graph *g);

/**
 * @brief Verifies if all the fields of a graph are valid.
 * 
 * @author Izan Robles
 *
 * @param g Graph pointer
 *
 * @return  Returns TRUE if the vertex is invalid, FALSE otherwise
 */
Bool is_invalid_graph (const Graph *g);

/**
 * @brief Changes the label of all the vertex of the graph
 * 
 * @author Izan Robles
 *
 * @param g Graph pointer
 * @param l Label to be set in all vertex
 *
 * @return  Returns OK if task was completed, ERROR otherwise. 
 */
Status graph_set_all_vertex_label(Graph *g, Label l);

/**
 * @brief Gets the vertex array from a graph
 * 
 * @author Izan Robles
 *
 * @param g Graph pointer
 *
 * @return  Returns a pointer to the graph vertex
 */
Vertex **graph_get_vertex_array(Graph *g);

/**
 * @brief Executes depth search algorithm
 * 
 * @author Izan Robles
 *
 * @param g Graph pointer
 * @param from_id Index of vertex to start from
 * @param to_id Index of vertex to end path
 *
 * @return  Returns OK or ERROR if something went wrong
 */
Status graph_depthSearch(Graph *g, long from_id, long to_id);

/**
 * @brief Executes breath search algorithm
 * 
 * @author Izan Robles
 *
 * @param g Graph pointer
 * @param from_id Index of vertex to start from
 * @param to_id Index of vertex to end path
 *
 * @return  Returns OK or ERROR if something went wrong
 */
Status graph_breathSearch (Graph *g, long from_id, long to_id);

#endif

