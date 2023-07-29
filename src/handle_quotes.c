void remove_element_at_index(char ***arr, int index)
{
    int i = 0;
    char **new_arr;

    /* Count the size of the array */
    while ((*arr)[i])
        i++;

    /* Allocate memory for the new array. The size is one less than the original array */
    new_arr = (char **)malloc(sizeof(char *) * i);
    if (!new_arr)
        return;

    /* Copy elements before the index */
    for (i = 0; i < index; i++)
        new_arr[i] = (*arr)[i];

    /* Skip the element at the index and copy the rest */
    for (; (*arr)[i]; i++)
        new_arr[i] = (*arr)[i + 1];

    /* Free the original array and replace it with the new one */
    free(*arr);
    *arr = new_arr;
}



void    handle_quotes(char ***arr)
{
    int i = 0;
    int j;
    char *temp;

    while ((*arr)[i])
    {
        /* Check if the string starts with a quote */
        if ((*arr)[i][0] == '\'')
        {
            /* Find the string that ends with a quote */
            j = i;
            while ((*arr)[j] && (*arr)[j][ft_strlen((*arr)[j]) - 1] != '\'')
                j++;

            /* If there is no ending quote, we might want to handle this as an error */

            /* Merge all strings from i to j */
            while (i < j)
            {
                temp = ft_strjoin((*arr)[i], (*arr)[i + 1]);
                free((*arr)[i]);
                (*arr)[i] = temp;
                remove_element_at_index(arr, i + 1);  // You need to implement this function
                j--;
            }

            /* Remove the quotes */
            temp = ft_strsub((*arr)[i], 1, ft_strlen((*arr)[i]) - 2);
            free((*arr)[i]);
            (*arr)[i] = temp;
        }
        i++;
    }
}
