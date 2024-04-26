/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:56:34 by anadal-g          #+#    #+#             */
/*   Updated: 2024/04/25 12:56:44 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	here_doc_2(char **argv, int *fd)
{
	char	*ret;
	char	*delimitier;

	delimitier = ft_strjoin(argv[2], "\n");
	close(fd[0]);
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, delimitier, ft_strlen(ret)) == 0) {
			free(delimitier);
			exit(0);
		}
		ft_putstr_fd(ret, fd[1]);
		free(ret);
	}
}

void	here_doc(char **argv)
{
	int		fd[2];
	pid_t	pid;
	
	if (pipe(fd) == -1)
		perror_error("pipe error");
	pid = fork();
	if (pid == -1)
		perror_error("fork error");
	if (!pid)
		here_doc_2(argv, fd);
	else
	{
		//Cierra escritura, porque solo leera el pipe
		close(fd[1]);
		//Cambia la entrada del pipe sea la entrada estandar del proceso padre 
		dup2(fd[0], 0);
		//El proceso padre espera hasta que termina el proceso hijo
		wait(NULL);
	}
}
