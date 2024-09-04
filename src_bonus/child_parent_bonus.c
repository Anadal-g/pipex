/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:35:49 by anadal-g          #+#    #+#             */
/*   Updated: 2024/09/04 17:26:25 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// void	commands(int *fd, int *fd2)
// {
// 		dup2(fd[0], STDIN_FILENO);
// 		dup2(fd2[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		close(fd2[0]);
// 		close(fd2[1]);		
// }

// // Esta funcion abre el arhivo y devuelve el fd
// int	open_file_bonus(char **argv, int x)
// {
// 	int	file;

// 	file = 0;
// 	// Esto indica que el archivo se abre solo para lectura
// 	if (x == 0)
// 		file = open(*argv, O_RDONLY, 0777);
// 	// El archivo se abre solo para escritura,
// 	// se crea si no existe y se borra el contenido existente si ya existe
// 	if (x == 1)
// 		file = open(*argv, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 	if (x == 2)
// 		file = open(*argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (file == -1)
// 		perror_error("Error al abrir el archivo");
// 	return (file);
// }

// /*
// 	- Input: archivo --> infile
// 	- Output: pipe		--> fd[1]

// 	fd[0] = lectura
// 	fd[1] = esritura
// */
// void	first_child(char *argv[], char **envp, int *fd)
// {
// 	int	infile;
// 	int	i;

// 	i = 1;
// 	if (ft_strcmp(argv[1], "here_doc") == 0)
// 	{
// 		infile = open_file_bonus(argv, 0);
// 		i += 2;
// 	}
// 	else 
// 		infile = open_file_bonus(&argv[i++], O_RDONLY);
// 	if (!infile)
// 		perror_error("Outfile error");
// 	dup2(infile, STDIN_FILENO);
// 	dup2(fd[1], STDOUT_FILENO);
// 	close(infile);
// 	close(fd[0]);
// 	close(fd[1]);
// 	ft_execve(argv[2], envp);
// }

// void	parent_bonus(char *argv[], char **envp, int *pid, int *fd)
// {
// 	int	outfile;
// 	int	argc;

// 	argc = 0;
// 	while (argv[argc])
// 		argc++;
// 	close(fd[1]);
// 	*pid = fork();
// 	if (*pid < 0)
// 		perror_error("Outfile error");
// 	if (*pid == 0)
// 	{
// 		if (ft_strcmp(argv[1], "here_doc") == 0)
// 			outfile = open_file_bonus(argv, 2);
// 		else 
// 			outfile = open_file_bonus(argv, 1);
// 		dup2(fd[0], STDIN_FILENO);
// 		dup2(outfile, STDOUT_FILENO);
// 		close(fd[0]);
// 		ft_execve(argv[argc - 2], envp);
// 	}
// }

// void	other_childs(char **argv, char **envp, int *pid, int *fd)
// {
// 	int	i;
// 	int	fd2[2];
// 	int argc;

// 	i = 0;
// 	argc = 0;
// 	while (argv[argc])
// 		argc++;
// 	if (ft_strcmp(argv[1], "here_doc") == 0)
// 		i++;
// 	while (++i < (argc - 2))
// 	{
// 		if (pipe(fd) == -1)
// 			perror_error("pipe error");
// 		*pid = fork();
// 		if (*pid == -1)
// 			perror_error("pipe error");
// 		if (*pid == 0)
// 		{
// 			commands(fd, fd2);
// 			ft_execve(argv[3], envp);
// 		}
// 		close(fd[0]);
// 		close(fd2[1]);
// 		fd[0] = fd2[0];
// 	}
// 	parent_bonus(argv, envp, pid, fd);
// }
void other_childs(int *fd, int *fd2)
{
    // Redirige stdin a fd[READ_FD] y stdout a fd2[WRITE_FD]
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]); // Cerramos después de duplicar
    close(fd[1]); // Cerramos el extremo opuesto que no se utiliza

    dup2(fd2[1], STDOUT_FILENO);
    close(fd2[1]); // Cerramos después de duplicar
    close(fd2[0]); // Cerramos el extremo opuesto que no se utiliza
}

void connect_next_cmd(int *fd, int *fd2)
{
    // Cierra la lectura del anterior y la escritura del nuevo pipe
    close(fd[0]);
    close(fd2[1]);
    // Reasigna la lectura del nuevo pipe al anterior
    fd[0] = fd2[0];
	fd[1] = fd2[1];
}

void first_child(char **arguments, char **enviroment, int *fd)
{
    int infile;
    int i;

    i = 1;
    if (ft_strcmp(arguments[1], "here_doc") == 0)
    {
        infile = open("TMP_FILE", O_RDONLY);  // Asume que TMP_FILE es el archivo temporal de here_doc
        i += 2;
    }
    else
    {
        infile = open(arguments[i++], O_RDONLY);
    }
    if (infile == -1)
        perror_error("Error al abrir el archivo de entrada");
    
    dup2(infile, STDIN_FILENO);
    close(infile);
	
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    close(fd[0]);
    ft_execve(arguments[i], enviroment);  // Ejecuta el primer comando
}
void next_cmds(char **arg, char **env, int *pid, int *fd)
{
    int fd2[2];
    int ac;
    int i;

    i = 2;
    ac = 0;
    while (arg[ac])
        ac++;
    if (ft_strcmp(arg[1], "here_doc") == 0)
        i++;
    while (++i < (ac - 2))
    {
        if (pipe(fd2) == -1)
            perror_error("Error al crear pipe");

        *pid = fork();
        if (*pid == -1)
            perror_error("Error al crear proceso hijo");

        if (*pid == 0)
        {
            other_childs(fd, fd2);
            ft_execve(arg[i], env);  // Ejecuta el comando intermedio
        }

        close(fd2[1]); // Cierra el extremo de escritura en el padre
        close(fd[0]);  // Cierra el extremo de lectura del antiguo fd en el padre
        fd[0] = fd2[0]; // Actualiza fd para la siguiente iteración
    }

    parent_bonus(arg, env, pid, fd);
}


void parent_bonus(char **arguments, char **enviroment, int *pid, int *fd)
{
    int outfile;
    int ac;

    ac = 0;
    while (arguments[ac])
        ac++;
    
    close(fd[1]);  // Cierra la escritura del último pipe

    *pid = fork();
    if (*pid == -1)
        perror_error("Error al crear proceso hijo");
    if (*pid == 0)
    {
        if (ft_strcmp(arguments[1], "here_doc") == 0)
            outfile = open(arguments[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            outfile = open(arguments[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (outfile == -1)
            perror_error("Error al abrir el archivo de salida");

        dup2(fd[0], STDIN_FILENO);
        close(fd[0]); // Cerramos después de duplicar

        dup2(outfile, STDOUT_FILENO);
        close(outfile); // Cerramos después de duplicar

        ft_execve(arguments[ac - 2], enviroment);  // Ejecuta el último comando
    }

    close(fd[0]);  // Cierra la lectura del último pipe en el padre

}

