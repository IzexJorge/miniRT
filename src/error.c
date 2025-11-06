/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:46:59 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/06 19:11:05 by jescuder         ###   ########.fr       */
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
