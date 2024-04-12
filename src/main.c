/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:39:00 by anadal-g          #+#    #+#             */
/*   Updated: 2024/04/12 11:37:43 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid[2];
	int		status;

	if (argc != 5)
		perror_error("Numero de argumentos incorrectos");
	if (pipe(fd) == -1)
		perror_error("pipe error");
	pid[0] = fork();
	if (pid[0] == -1) // Error no se esta ejecutando nada
		perror_error("fork error");
	else if (pid[0] == 0) // se esta ejecutando el hijo
		child(argv, envp, fd);
	/* Ejecutamos el padre */
	pid[1] = fork();
	if (pid[1] < 0)
		perror_error("fork error");
	else if (pid[1] == 0)
		parent(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	return (WEXITSTATUS(status));
}
