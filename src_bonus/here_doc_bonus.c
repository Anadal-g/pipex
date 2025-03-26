/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:56:34 by anadal-g          #+#    #+#             */
/*   Updated: 2024/09/09 16:12:59 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	here_doc_2(char **argv, int *fd)
{
	char	*ret;
	char	*delimitier;

	delimitier = ft_strjoin(argv[2], "\n");
	if (!delimitier)
	{
		perror("Memory allocation failed for delimiter");
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	while (1)
	{
		ret = get_next_line(0);
		if (!ret)
		{
			perror("Error reading input");
			free(delimitier);
			close(fd[1]);
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(ret, delimitier, ft_strlen(ret)) == 0)
		{
			free(ret);
			free(delimitier);
			close(fd[1]); // Cierra el lado de escritura antes de sali
			exit(0);
		}
		ft_putstr_fd(ret, fd[1]);
		free(ret);
	}
	free(delimitier);
}
/*
 * here_doc2 
 */
// int	read_and_compare(char *delimiter, int fd_write)
// {
// 	char	*ret;

// 	while (1)
// 	{
// 		ret = get_next_line(0);
// 		if (!ret)
// 		{
// 			perror("Error reading input");
// 			return (-1);
// 		}
// 		if (ft_strncmp(ret, delimiter, ft_strlen(ret)) == 0)
// 		{
// 			free(ret);
// 			return (0); // Devuelve 0 si encuentra el delimitador
// 		}
// 		// Escribir la línea en el pipe
// 		ft_putstr_fd(ret, fd_write);
// 		free(ret);
// 	}
// 	return (0);
// }


// void	here_doc_2(char **argv, int *fd)
// {
// 	char	*delimiter;

// 	delimiter = ft_strjoin(argv[2], "\n");
// 	if (!delimiter)
// 	{
// 		perror("Memory allocation failed for delimiter");
// 		exit(EXIT_FAILURE);
// 	}
// 	close(fd[0]);
// 	if (read_and_compare(delimiter, fd[1]) == -1)
// 	{
// 		free(delimiter);
// 		exit(EXIT_FAILURE);
// 	}
// 	close(fd[1]);
// 	free(delimiter);
// 	exit(0);
// }

void	here_doc(char **argv)
{
	int		fd[2];
	pid_t	pid;
	int		infile;
	
	infile = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile == -1)
    	perror_error("Error al crear TMP_FILE");
	if (pipe(fd) == -1)
		perror_error("pipe error");
	pid = fork();
	if (pid == -1)
		perror_error("fork error");
	if (pid == 0)
		here_doc_2(argv, fd);
	else
	{
		// Cierra escritura, porque solo leera el pipe
		close(fd[1]);
		// Cambia la entrada del pipe sea la entrada estandar del proceso padre
		dup2(fd[0], 0);
		// El proceso padre espera hasta que termina el proceso hijo
		close(fd[0]);
		wait(NULL);
	}
	close(infile);
}



