#include "list.h"
#include "file_utils.h"

int main(int argc, char *argv[])
{
    FILE *file = NULL;
    List *ls = NULL;
    List *ls2 = NULL;
    char *endptr;
    int num, num_elements = 0, i, half;
    float *temp_value = NULL;
    P_ele_free ffree = (P_ele_free)free;
    P_ele_cmp fcmp = float_cmp;
    P_ele_print fpr = _float_print;

    /*---------------------------------  Check arguments  ---------------------------------*/

    if (argc < 3)
    {
        printf("Use: %s <file.txt> <1 or -1>\n", argv[0]);
        return 1;
    }
    printf("--> number of arguments correct\n");

    num = strtol(argv[2], &endptr, 10);

    if (*endptr != '\0')
    {
        printf("ERROR: invalid numeric input.\n");
        return 1;
    }

    if (num != 1 && num != -1)
    {
        printf("ERROR: number must be 1 or -1\n");
        return 1;
    }
    printf("--> valid numeric input\n");

    /*---------------------------------  Read file  ---------------------------------*/

    if (!(file = fopen(argv[1], "r")))
    {
        printf("ERROR: %s not found\n", argv[1]);
        return 1;
    }
    printf("--> target file succesfully opened\n");

    if (!(ls = list_new()))
    {
        printf("ERROR: could not create list\n");
        fclose(file);
        return 1;
    }
    printf("--> new list succesfully initialized\n");

    if (fscanf(file, "%d\n", &num_elements) != 1)
    {
        printf("ERROR: could not read number of elements\n");
        list_free(ls);
        fclose(file);
        return 1;
    }
    printf("--> number of elements saved\n");

    for (i = 0; i < num_elements; i++)
    {
        temp_value = malloc(sizeof(float)); 

        if (!temp_value)
        {
            printf("ERROR: memory allocation failed\n");
            list_free_with_elements(ls, ffree);
            fclose(file);
            return 1;
        }

        if (fscanf(file, "%f\n", temp_value) != 1) 
        {
            printf("ERROR: could not read elements\n");
            free(temp_value);
            list_free_with_elements(ls, ffree);
            fclose(file);
            return 1;
        }

        if (i % 2 == 0)
        {
            list_pushFront(ls, temp_value);
        }
        else
        {
            list_pushBack(ls, temp_value);
        }
    }
    printf("--> data succesfully saved in list\n");

    fclose(file);
    printf("--> file closed\n");
    
    /*---------------------------------  Create new list and order elements  ---------------------------------*/

    if (!(ls2 = list_new()))
    {
        printf("ERROR: could not create second list\n");
        list_free_with_elements(ls, ffree);
        return 1;
    }
    printf("--> second list created\n");

    half = num_elements / 2; 

    for (i = 0; i < half; i++)
    {
        temp_value = list_popFront(ls);  
        if (list_pushInOrder(ls2, temp_value, fcmp, num) == ERROR) 
        {
            printf("ERROR: could not insert element in ordered list\n");
            free(temp_value);
            list_free_with_elements(ls, ffree);
            list_free_with_elements(ls2, ffree);
            return 1;
        }
    }

    for (i = 0; i < num_elements - half; i++)
    {
        temp_value = list_popBack(ls);  
        if (list_pushInOrder(ls2, temp_value, fcmp, num) == ERROR) 
        {
            printf("ERROR: could not insert element in ordered list\n");
            free(temp_value);
            list_free_with_elements(ls, ffree);
            list_free_with_elements(ls2, ffree);
            return 1;
        }
    }

    printf("--> elements ordered in the desired order\n");

    list_print(stdout, ls2, fpr);  

    list_free_with_elements(ls2, ffree);
    list_free_with_elements(ls, ffree);
    printf("--> all memory freed\n");
    printf("--> program end\n");

    return 0;
}