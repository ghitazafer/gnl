/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzafer <gzafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:18:25 by gzafer            #+#    #+#             */
/*   Updated: 2024/12/02 14:54:11 by gzafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		i++;
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
	while (stockbuff[i] && stockbuff[i] != '\n')
		i++;
	if (!stockbuff[i])
		return (free(stockbuff), NULL);
	new_stockbuff = malloc(ft_strlen(stockbuff) - i + 1);
	if (!new_stockbuff)
		return (free(stockbuff), NULL);
	i++;
	while (stockbuff[i])
		new_stockbuff[j++] = stockbuff[i++];
	new_stockbuff[j] = '\0';
	free(stockbuff);
	return (new_stockbuff);
}

static char	*read_buff(int fd, char *stockbuff)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stockbuff), NULL);
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), NULL);
		buffer[bytes_read] = '\0';
		temp = stockbuff;
		stockbuff = ft_strjoin(stockbuff, buffer);
		if (!stockbuff)
			return (free(temp), free(buffer), NULL);
		free (temp);
		if (ft_strchr(stockbuff, '\n'))
			break ;
	}
	free(buffer);
	return (stockbuff);
}

char	*get_next_line(int fd)
{
	static char	*stockbuff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX
		|| read(fd, NULL, 0) == -1 || BUFFER_SIZE > INT_MAX)
		return (free(stockbuff), stockbuff = NULL, NULL);
	stockbuff = read_buff(fd, stockbuff);
	if (!stockbuff)
		return (free(stockbuff), stockbuff = NULL, NULL);
	line = returnline(stockbuff);
	if (!line || *line == 0)
		return (NULL);
	stockbuff = updatedstock(stockbuff);
	return (line);
}
