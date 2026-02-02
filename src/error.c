/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:46:59 by jescuder          #+#    #+#             */
/*   Updated: 2026/02/02 23:27:00 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_err_line(int line, char *message)
{
	write(STDERR_FILENO, "error: line ", 12);
	ft_putnbr_fd(line, STDERR_FILENO);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

void	ft_err_field(int line, char *field, char *message)
{
	write(STDERR_FILENO, "error: line ", 12);
	ft_putnbr_fd(line, STDERR_FILENO);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, field, ft_strlen(field));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

void	ft_err_free(char *message, int line, char **array)
{
	ft_err_line(line, message);
	ft_free_str_array(array);
}

int		ft_check_rt_extension(char *filename)
{
	size_t	len;

	len	= ft_strlen(filename);
	if (len < 3 || ft_strcmp(filename + len - 3, ".rt"))
	{
		ft_err("The file must have the .rt extension");
		return (1);
	}
	return (0);
}
