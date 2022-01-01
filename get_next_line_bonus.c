/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaciri <anaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 13:33:13 by anaciri           #+#    #+#             */
/*   Updated: 2022/01/01 14:44:42 by anaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_buff_size(int fd, char **lines)
{
	char	*bufer;
	int		i;

	i = 1;
	bufer = malloc(BUFFER_SIZE + 1);
	if (!bufer)
		return (NULL);
	while (i && !(ft_strchr(*lines, '\n')))
	{
		i = read(fd, bufer, BUFFER_SIZE);
		if (i == -1)
		{	
			free(bufer);
			return (NULL);
		}
		bufer[i] = '\0';
		*lines = ft_strjoin(*lines, bufer);
	}
	free (bufer);
	return (*lines);
}

char	*one_line(char *lines)
{
	int	i;

	i = 0;
	if (lines[i] == '\0')
		return (NULL);
	while (lines[i] != '\n' && lines[i])
		i++;
	return (ft_substr(lines, 0, ++i));
}

char	*lines_rest(char *file_line)
{
	int		j;
	char	*dup;

	j = 0;
	while (file_line[j] != '\n' && file_line[j])
		j++;
	if (file_line[j] == '\0')
	{
		free(file_line);
		return (NULL);
	}
	dup = ft_substr(file_line, ++j, ft_strlen(file_line));
	free(file_line);
	return (dup);
}

char	*get_next_line(int fd)
{
	static char	*file_line[4096];
	char		*o_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	file_line[fd] = read_buff_size(fd, (file_line + fd));
	if (file_line[fd] == '\0')
		return (NULL);
	o_line = one_line(file_line[fd]);
	file_line[fd] = lines_rest(file_line[fd]);
	return (o_line);
}

//#include<stdio.h>
//int main()
//{
//	int fd1;
//    int fd2;
//    int fd3;
//	fd1 = open( "test.c", O_RDONLY);
//	fd2 = open( "test1.c", O_RDONLY);
//	fd3 = open( "test2.c", O_RDONLY);
//
//    
//	printf ("%s", get_next_line(fd1));
//	printf ("%s", get_next_line(fd2));
//	printf ("%s", get_next_line(fd1));
//	printf ("%s", get_next_line(fd3));
//	printf ("%s", get_next_line(fd1));
//}
