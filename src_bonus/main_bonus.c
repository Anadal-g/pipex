/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:40:15 by anadal-g          #+#    #+#             */
/*   Updated: 2024/04/26 11:10:39 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int wait_childs(int *status, pid_t pid)
{
    pid_t waited;

    waited = waitpid(pid, status, 0);
    if (waited == -1)
        return -1; // Error al esperar al proceso hijo
    return WEXITSTATUS(*status);
}


int	main (int argc, char **argv, char **envp)
{
	int	fd[2];
	int	fd_out;
	int	pid[2];
	int	status;
	int status_final;

	if (argc >= 5)
	{
		if (ft_strcmp(argv[1], "here_doc") == 0)
		{
			fd_out = open_file(argv[argc - 1], 1);
			here_doc(argv);
		}
		if (pipe(fd) == -1)
			perror_error("pipe error");
		pid[0] = fork();
		if (pid[0] == -1)
			perror_error("fork error");
		if (pid[0] == 0)
			first_child(argv, envp, fd);
		else
			other_childs(argv, envp, pid, fd);
		status_final = wait_childs(&status, pid[0]);
		return (WEXITSTATUS(status));
	}
}
