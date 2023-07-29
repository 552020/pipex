#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	s;

	s = 0;
	while (str[s] != '\0')
		s++;
	return (s);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen((char *)src));
}

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	int		j;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	j = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dest);
	j = dst_len;
	if (dstsize == 0 || dstsize <= dst_len)
		return (src_len + dstsize);
	while (src[i] != '\0' && i < dstsize - dst_len - 1)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dst_len + src_len);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	strlen_s1;
	size_t	strlen_s2;
	char	*res;

	strlen_s1 = ft_strlen(s1);
	strlen_s2 = ft_strlen(s2);
	res = malloc (sizeof (char) * (strlen_s1 + strlen_s2 + 1));
	if (!res)
		return (NULL);
	ft_strlcpy (res, s1, (strlen_s1 + 1));
	ft_strlcat (res, s2, (strlen_s1 + strlen_s2 + 1));
	return (res);
}



char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	substr_len;
	int		s_len;

	s_len = ft_strlen((char *)s);
	if (start >= ft_strlen((char *)s))
	{
		substr = malloc (sizeof(char));
		if (!substr)
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	if (len <= s_len - start)
		substr_len = len;
	else
		substr_len = s_len - start;
	substr = malloc (sizeof(char) * substr_len + 1);
	if (substr == NULL)
		return (0);
	ft_strlcpy(substr, &s[start], substr_len + 1);
	return (&substr[0]);
}

int	ft_free_ret(char **ret, size_t i);

static size_t	ft_count_word(const char *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	if (!s[0])
		return (0);
	while (s[i] && s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			words++;
			while (s[i] && s[i] == c)
				i++;
		}
		else
			i++;
	}
	if (s[i - 1] != c)
		words++;
	return (words);
}

int	ft_free_ret(char **ret, size_t i)
{
	while (i--)
		free(ret[i]);
	free(ret);
	return (1);
}


char	**ft_split(const char *s, char c)
{
	char	**ret;
	size_t	len;
	size_t	i;

	i = 0;
	ret = (malloc(sizeof(char *) * (ft_count_word(s, c) + 1)));
	if (!ret)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			ret[i] = ft_substr(s - len, 0, len);
			if (!ret[i] && ft_free_ret(ret, i))
				return (0);
			i++;
		}
		else
			s++;
	}
	ret[i] = 0;
	return (ret);
}

void remove_element_at_index(char ***arr, int index)
{
    int i = 0;
    char **new_arr;

    while ((*arr)[i])
        i++;
    new_arr = (char **)malloc(sizeof(char *) * i);
    if (!new_arr)
        return;
    for (i = 0; i < index; i++)
        new_arr[i] = (*arr)[i];
    for (; (*arr)[i]; i++)
        new_arr[i] = (*arr)[i + 1];
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
            temp = ft_substr((*arr)[i], 1, ft_strlen((*arr)[i]) - 2);
            free((*arr)[i]);
            (*arr)[i] = temp;
        }
        i++;
    }
}

void    handle_quotes_with_space_between(char ***arr)
{
    int i = 0;
    int j;
    char *temp;
    char *space = " ";

    while ((*arr)[i])
    {
        if ((*arr)[i][0] == '\'')
        {
            j = i;
            while ((*arr)[j] && (*arr)[j][ft_strlen((*arr)[j]) - 1] != '\'')
                j++;
            while (i < j)
            {
                char *temp_with_space = ft_strjoin((*arr)[i], space);
                temp = ft_strjoin(temp_with_space, (*arr)[i + 1]);
                free(temp_with_space);
                free((*arr)[i]);
                (*arr)[i] = temp;
                remove_element_at_index(arr, i + 1);  // You need to implement this function
                j--;
            }
            temp = ft_substr((*arr)[i], 1, ft_strlen((*arr)[i]) - 2);
            free((*arr)[i]);
            (*arr)[i] = temp;
        }
        i++;
    }
}



// int main(int argc, char **argv)
// {
// 	char **ret;
// 	int i;

// 	i = 0;
// 	ret = ft_split(argv[1], argv[2][0]);
// 	while (ret[i])
// 	{
// 		printf("%s\n", ret[i]);
// 		i++;
// 	}
// 	return (0);
// }

