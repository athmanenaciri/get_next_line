/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaciri <anaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 13:29:52 by anaciri           #+#    #+#             */
/*   Updated: 2022/01/01 10:37:06 by anaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *read_buff_size(int fd, char *lines)
{
    char    *bufer;
    int        i;

    i = 1;
    bufer = malloc(BUFFER_SIZE + 1);
    if (!bufer)
        return (NULL);
    while (i && !(ft_strchr(lines, '\n')))
    {
        i = read(fd, bufer, BUFFER_SIZE);
        if (i == -1)
        {
            free(bufer);
            return (NULL);
        }
        bufer[i] = '\0';
        lines = ft_strjoin(lines, bufer);
    }
    free (bufer);
    return (lines);
}

char    *one_line(char *lines)
{
    int        i;

    i = 0;
    if (!lines[i])
        return (NULL);
    while (lines[i] != '\n' && lines[i])
        i++;
    return (ft_substr(lines, 0, ++i));
}

char    *lines_rest(char *file_line)
{
    int        j;
    char    *dup;

    j = 0;
    while (file_line[j] != '\n' && file_line[j])
        j++;
    if (!file_line[j])
    {
        free(file_line);
        return (NULL);
    }
    dup = ft_substr(file_line, ++j, ft_strlen(file_line));
    free(file_line);
    return (dup);
}

char    *get_next_line(int fd)
{
    static char    *file_line;
    char        *o_line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    file_line = read_buff_size(fd, file_line);
    if (!file_line)
        return (NULL);
    o_line = one_line(file_line);
    file_line = lines_rest(file_line);
    return (o_line);
}

#include<stdio.h>
int main()
{
	int fd;
	fd = open( "test.c", O_RDONLY);
    char *str;
    while((str = get_next_line(fd)))
    {
	    printf ("%s", str);
        free(str);
    }
    while(1);
	//printf ("%s", get_next_line(fd));
	//printf ("%s", get_next_line(fd));
	//printf ("%s", get_next_line(fd));
	//printf ("%s", get_next_line(fd));
	//printf ("%s", get_next_line(fd));
}