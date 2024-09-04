/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:14:41 by anadal-g          #+#    #+#             */
/*   Updated: 2024/09/04 13:53:44 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// Esta funcion abre el arhivo y devuelve el fd

int	open_file(char *argv, int x)
{
	int	file;

	file = 0;
	if (x == 1)
		file = open(argv, O_RDONLY);
	if (x == 2)
		file = open(argv, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	return (file);
}

void	child(char *argv[], char **envp, int *fd)
{
	int	infile;

	close(fd[0]);
	infile = 0;
	infile = open_file(argv[1], 1);
	if (infile < 0)
	{
		close(fd[1]);
		perror_error("Outfile error");
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	ft_execve(argv[2], envp);
}

void	parent(char *argv[], char **envp, int *fd)
{
	int	outfile;

	close(fd[1]);
	outfile = 0;
	outfile = open_file(argv[4], 2);
	if (outfile < 0)
	{
		close(fd[0]);
		perror_error("Outfile error");
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	close(outfile);
	ft_execve(argv[3], envp);
}
