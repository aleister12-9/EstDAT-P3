/**
 * @brief Example program to test functions using new queue library
 * @author Izan Robles
 */

#include "delivery.h"
#include "queue.h"


Delivery *build_delivery(FILE *pf)
{
    char delivery_name[MAX_DELIVERY_NAME];
    char product_name[MAX_PRODUCT_NAME];
    char vertex_desc[1024]; /* Max buffer length from vertex function */
    int vertex_number, i;
    Delivery *delivery = NULL;
    void *temp = NULL;
    p_element_free ffree = vertex_free;
    p_element_print fprint = vertex_print;

    if (!pf)
    {
        return NULL;
    }

    rewind(pf);

    /* Read names on first line */
    if (fscanf(pf, "%s %s", delivery_name, product_name) != 2)
    {
        return NULL;
    }

    delivery = delivery_init(delivery_name, product_name);
    if (!delivery)
    {
        return NULL;
    }

    /* Move to next line */
    fgetc(pf);

    /* Read number of vertices */
    if (fscanf(pf, "%d", &vertex_number) != 1)
    {
        delivery_free(delivery);
        return NULL;
    }

    /* Move to next line */
    fgetc(pf);

    /* For every vertex, init and add to queue */
    for (i = 0; i < vertex_number; i++)
    {
        if (!(fgets(vertex_desc, 1024, pf)))
        {
            delivery_free_products(delivery, ffree);
            delivery_free(delivery);
            return NULL;
        }

        temp = vertex_initFromString(vertex_desc);
        if (!temp)
        {
            delivery_free_products(delivery, ffree);
            delivery_free(delivery);
            return NULL;
        }

        printf("--> adding: ");
        vertex_print(stdout, temp);
        printf(" to delivery %s\n", delivery_name);

        if (delivery_add(NULL, delivery, temp, fprint) == ERROR) 
        {
            ffree(temp);
            delivery_free_products(delivery, ffree);
            delivery_free(delivery);
            return NULL;
        }
    }

    return delivery;
}


int main(int argc, char *argv[])
{
    FILE *file = NULL;
    Delivery *delivery = NULL;
    p_element_print f = vertex_print;
    p_element_free r = vertex_free;
    
    if (argc != 2)
    {
        printf("ERROR: usage: program_name <file.txt>\n");
        return 1;
    }
    printf("--> init arguments detected\n");

    if (!(file = fopen(argv[1], "r")))
    {
        printf("ERROR: file not found\n");
    }
    printf("--> target file found\n");

    if (!(delivery = build_delivery(file)))
    {
        printf("ERROR: could not create delivery\n");
        fclose(file);
    }
    printf("--> delivery created and filled\n");
    
    if (delivery_run_plan(stdout, delivery, f, r) == ERROR)
    {
        printf("ERROR: could not print delivery\n");
        fclose(file);
        delivery_free_products(delivery, r);
        delivery_free(delivery);
    }
    printf("--> delivery printed\n");


    printf("--> program terminated\n");
    fclose(file);
    delivery_free_products(delivery, r);
    delivery_free(delivery);
    return 0;
}