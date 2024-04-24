/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:40:15 by anadal-g          #+#    #+#             */
/*   Updated: 2024/04/24 11:56:58 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	do_pipe(char *command, char **envp)
{
	pid_t	pid;
	int		fd[2];
	
	if (pipe(fd) == -1)
		perror_error("pipe error");
	pid = fork();
	if (pid == -1)
		perror_error("pipe error");
	if(!pid)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		ft_execve(command, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int i;
	int fd_in;
	int fd_out;
	
	if (argc < 5)
		perror_error("Numero de argumentos incorrectos");
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
	if (argc < 6)
		perror_error("Numero de argumentos incorrectos");
	/*
 	* Inicializamos a 3 porque vamos a 
 	* necesitar los argumentos a partir de argv[3]
	*/
	i = 3;
	/*
	 * Indica el modo de apertura del archivo (escirtura)
	 * se usa el [ac -1] para acceder al 
	 * ultimo argumento de la linea de comandos
	*/
	fd_out = open_file(argv[argc - 1], 2);
	here_doc(argv);
	}
	else 
	{
	/*
 	* Inicializamos a 3 porque vamos a 
 	* necesitar los argumentos a partir de argv[3]
	*/
	i = 2;
	fd_in = open_file(argv[1], 0); //TODO
	fd_out = open_file(argv[argc - 1], 1);
	dup2(fd_in, 0);
	}
	while (i < argc - 2)
	{
		do_pipe(argv[i], envp);
		i++;
	}
	dup2(fd_out, 1);
	ft_execve(argv[argc - 2], envp);
}
