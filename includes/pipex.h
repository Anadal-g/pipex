/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:09:16 by anadal-g          #+#    #+#             */
/*   Updated: 2024/03/12 11:03:01 by anadal-g         ###   ########.fr       */
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

//Errores
int	error(char *msg);
void perror_error(char *msg);

//Child and Parent
void	child(char *argv[], char **envp, int *fd);
void	parent(char *argv[], char **envp, int *fd);
int		open_file(char *argv, int x);

//path
void	ft_execve(char *argv, char **envp);
char	*find_path(char *command, char **envp);
int		check_envp(char **envp);

#endif
