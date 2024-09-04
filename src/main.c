/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:39:00 by anadal-g          #+#    #+#             */
/*   Updated: 2024/09/04 13:56:26 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid[2];
	int		status;

	if (argc != 5)
		perror_error("Number of incorrect arguments");
	if (pipe(fd) == -1)
		perror_error("pipe error");
	pid[0] = fork();
	if (pid[0] == -1)
		perror_error("fork error");
	else if (pid[0] == 0)
		child(argv, envp, fd);
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
