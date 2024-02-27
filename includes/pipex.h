/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:09:16 by anadal-g          #+#    #+#             */
/*   Updated: 2024/02/26 15:18:29 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


# define ERROR_ARGS "El numero de argumentos es incorrecto\"\n\t"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
# include "../libft/libft.h"
// typedef struct s_pipex
// {
// 	int		fd[2];
// 	pid_t	pid[2];
// 	char	infile;
// 	char	outfile;
// 	char	*path;
	
// }				t_pipex;

//Errores
int	error(char *msg);
void perror_error(char *msg);

//Child and Parent
void	child(char *argv[], char **envp, int *fd);
void	parent(char *argv[], char **envp, int *fd);
int	open_file(char *argv, int x);

//path
void	ft_execve(char *argv, char **envp);

//Utils
//size_t	ft_strlen(const char *str);


#endif
