/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:14:41 by anadal-g          #+#    #+#             */
/*   Updated: 2024/02/26 15:11:18 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
 
 //Esta funcion abre el arhivo y devuelve el fd
int	open_file(char *argv, int x)
{
	int	file;

	file = 0;
	if (x == 1)//Esto indica que el archivo se abre solo para lectura
		file = open(argv, O_RDONLY);
	if (x == 2)//El archivo se abre solo para escritura, se crea si no existe y se borra el contenido existente si ya existe
		file = open(argv, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file == -1)
		perror_error("Error al abrir el archivo");
	return (file);
}

void	child(char *argv[], char **envp, int *fd)
{
	int	infile = 0;
	(void)envp;
	(void)argv;
	
	infile = open_file(argv[1], 1);//TODO
	dup2(fd[0], STDIN_FILENO);
	dup2(infile, STDOUT_FILENO);
	close(fd[1]);
	//ft_execve(argv[2], envp);//TODO
}

void	parent(char *argv[], char **envp, int *fd)
{
	int		outfile = 0;
	(void)envp;
	(void)argv;
	
	outfile = open_file(argv[4], 2);//TODO
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	//ft_execve(argv[3], envp);
}
