/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:56:34 by anadal-g          #+#    #+#             */
/*   Updated: 2024/02/19 12:05:22 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	error(char *msg)
{
	write(1, msg, ft_strlen(msg));
	return (1);
}

void	perror_error(char *msg)
{
	perror(msg);
	exit(1);
}
