/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzafer <gzafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:59:47 by gzafer            #+#    #+#             */
/*   Updated: 2024/12/01 15:15:16 by gzafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*returnline(char *stockbuff)
{
	int		i;
	char	*line;

	i = 0;
	if (!stockbuff || !stockbuff[0])
		return (NULL);
	while (stockbuff[i] && stockbuff[i] != '\n')
		i++;
	if (stockbuff[i] == '\n')
		line = malloc((i + 2));
	else
		line = malloc((i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stockbuff[i] && stockbuff[i] != '\n')
	{
		line[i] = stockbuff[i];
		i++;
	}
	if (stockbuff[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*updatedstock(char *stockbuff)
{
	int		i;
	char	*new_stockbuff;
	int		j;

	i = 0;
	j = 0;
	if (!stockbuff)
		return (NULL);
	while (stockbuff[i] && stockbuff[i] != '\n')
		i++;
	if (stockbuff[i] == '\0')
		return (free(stockbuff), NULL);
	new_stockbuff = malloc(ft_strlen(stockbuff) - i);
	if (!new_stockbuff)
		return (free(stockbuff), NULL);
	i++;
	while (stockbuff[i])
		new_stockbuff[j++] = stockbuff[i++];
	new_stockbuff[j] = '\0';
	free(stockbuff);
	return (new_stockbuff);
}

static char	*read_buff(int fd, char **stockbuff)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(*stockbuff), NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*stockbuff, buffer);
		if (!temp)
			return (free(*stockbuff), free(buffer), NULL);
		*stockbuff = temp;
		if (ft_strchr(*stockbuff, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read < 0)
		return (free(*stockbuff), NULL);
	return (*stockbuff);
}

char	*get_next_line(int fd)
{
	static char	*stockbuff[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX
		|| BUFFER_SIZE > INT_MAX)
		return (NULL);
	stockbuff[fd] = read_buff(fd, &stockbuff[fd]);
	if (!stockbuff[fd])
		return (free(stockbuff[fd]), stockbuff[fd] = NULL, NULL);
	line = returnline(stockbuff[fd]);
	if (!line || *line == 0)
		return (free(stockbuff[fd]), stockbuff[fd] = NULL);
	stockbuff[fd] = updatedstock(stockbuff[fd]);
	return (line);
}
