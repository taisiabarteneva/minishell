/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:11:31 by wurrigon          #+#    #+#             */
/*   Updated: 2021/10/26 14:19:39 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

#define BUFFER_SIZE 100

void	ft_fill_line(char **rmd, char **line, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		(*line)[i] = (*rmd)[i];
	if ((*rmd)[i] == '\n')
	{
		(*line)[i] = '\n';
		(*line)[i + 1] = '\0';
	}
	else
	{
		(*line)[i] = '\0';
		free(*rmd);
		*rmd = NULL;
	}
}

void	ft_handle_remainder(char **rmd, char **line)
{
	unsigned int	i;
	int				flag;
	char			*tmp;

	i = 0;
	flag = 0;
	while ((*rmd)[i] != '\n' && (*rmd)[i] != '\0')
		i++;
	if ((*rmd)[i] == '\n')
		flag++;
	*line = (char *)malloc(sizeof(char) * (i + flag + 1));
	if (!*line)
		return ;
	ft_fill_line(rmd, line, i);
	if (*rmd != NULL)
	{
		tmp = *rmd;
		*rmd = ft_substr(*rmd, i + 1, ft_strlen(*rmd) - i);
		free(tmp);
	}
}

int	ft_read(int fd, char **rmd, char **buf, char **line)
{
	char	*tmp;
	int		res;

	res = 1;
	while (!ft_strchr(*rmd, '\n') && res > 0)
	{
		res = read(fd, *buf, BUFFER_SIZE);
		if (res == -1)
			return (res);
		(*buf)[res] = '\0';
		tmp = *rmd;
		*rmd = ft_strjoin(*rmd, *buf);
		free(tmp);
		tmp = NULL;
	}
	free(*buf);
	*buf = NULL;
	ft_handle_remainder(rmd, line);
	if ((*line)[0] != '\0')
		return (res);
	free(*line);
	*line = NULL;
	return (res);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*rmd;
	int			res;

	line = NULL;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (line);
	if (rmd == NULL)
		rmd = ft_strdup("");
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return ((char *) NULL);
	res = ft_read(fd, &rmd, &buf, &line);
	if (res == -1 && line == NULL)
	{
		free(buf);
		free(rmd);
		buf = NULL;
		rmd = NULL;
		return (NULL);
	}
	return (line);
}
