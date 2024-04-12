/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:35:49 by anadal-g          #+#    #+#             */
/*   Updated: 2024/04/12 17:13:29 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// Esta funcion abre el arhivo y devuelve el fd
int	open_file(char *argv, int x)
{
	int	file;

	file = 0;
	// Esto indica que el archivo se abre solo para lectura
	if (x == 1)
		file = open(argv, O_RDONLY);
	// El archivo se abre solo para escritura,
	// se crea si no existe y se borra el contenido existente si ya existe
	if (x == 2)
		file = open(argv, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file == -1)
		perror_error("Error al abrir el archivo");
	return (file);
}

/*
	- Input: archivo --> infile
	- Output: pipe	 --> fd[1]

	fd[0] = lectura
	fd[1] = esritura
*/
void	child(char *argv[], char **envp, int *fd)
{
	int	infile;

	infile = 0;
	infile = open_file(argv[1], 1);
	if (!infile)
		perror_error("Outfile error");
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(infile);
	close(fd[1]);
	ft_execve(argv[2], envp);
}

void	parent(char *argv[], char **envp, int *fd)
{
	int	outfile;

	outfile = 0;
	(void)envp;
	(void)argv;
	outfile = open_file(argv[4], 2);
	if (outfile < 0)
		perror_error("Outfile error");
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	ft_execve(argv[3], envp);
}
