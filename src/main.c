/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:39:00 by anadal-g          #+#    #+#             */
/*   Updated: 2024/02/19 12:15:30 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		perror_error("Numero de argumentos incorrectos");
	pid = fork();
	if (pid == -1) // Error no se esta ejecutando nada
	{
		perror_error("fork error");
	}
	else if (pid == 0) // se esta ejecutando el hijo
	{
		child(argv, envp, fd);
	}
	else if (pid > 0) // se esta ejecutando el padre
	{
		parent(argv, envp, fd);
	}
	return (0);
}
