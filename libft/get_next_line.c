/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:26:19 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/29 15:33:26 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_line_right(int fd, char *buff)
{
	int		rd_bytes;
	char	*str;

	rd_bytes = 1;
	if (buff)
		str = malloc(ft_strlen(buff) * sizeof(char) + 1);
	else
		str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	ft_strlcat(str, buff, ft_strlen(buff) + 1);
	if (!str)
		return (NULL);
	while (!ft_strchr(str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (buff[0] = '\0', free(str), NULL);
		buff[rd_bytes] = '\0';
		str = strjoin_gnl(str, buff);
		if (!str || ft_strlen(str) == 0)
			return (free(str), NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*str;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = ft_line_right(fd, buff);
	if (!tmp)
		return (NULL);
	str = ft_get_line(tmp);
	if (!str)
	{
		free(tmp);
		return (NULL);
	}
	tmp = ft_get_new_line(tmp);
	if (!tmp)
	{
		free(str);
		return (NULL);
	}
	buff[0] = '\0';
	ft_strlcat(buff, tmp, ft_strlen(tmp) + 1);
	free(tmp);
	return (str);
}

char	*ft_get_line(char *str)
{
	char	*str_return;
	int		i;

	i = 0;
	if (!str)
		return (str);
	while (str[i] && str[i] != '\n')
		i++;
	str_return = malloc((sizeof(char) * i) + 1);
	if (!str_return)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		str_return[i] = str[i];
		i++;
	}
	str_return[i] = '\0';
	return (str_return);
}

char	*ft_get_new_line(char	*str)
{
	char	*str_return;
	int		i;
	int		j;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	str_return = malloc(((ft_strlen(str) - i) + 1) * sizeof(char));
	if (!str_return)
		return (NULL);
	j = 0;
	while (str[i])
		str_return[j++] = str[i++];
	str_return[j] = '\0';
	free(str);
	return (str_return);
}

void	trash_gnl(char *str)
{
	int		fd;
	char	*line;

	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
