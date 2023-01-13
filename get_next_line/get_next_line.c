/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 08:25:21 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/12 11:35:20 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 42

char *get_next_line(int fd)
{
	int i = 0;
	int rd = 0;
	char character;
	char *buffer;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while ((rd = read(fd, &character, 1)) > 0)
	{
		buffer[i++] = character;
		if (character == '\n')
			break;
	}
	if ((rd <= 0) && (i == 0))
	{
		free(buffer);
		return (NULL);
	}
	buffer[i] = '\0';
	return (buffer);
}