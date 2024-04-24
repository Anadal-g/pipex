/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:42:17 by anadal-g          #+#    #+#             */
/*   Updated: 2024/04/15 12:46:53 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// Esta funcion comprueba si se ha quitado el envp de la ruta
int	check_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	perror_error("Error en el envp");
	exit(EXIT_FAILURE);
}

// Esta funcion comprueba si el comando existe en la ruta
char	*find_path(char *command, char **envp)
{
	int		i;
	int		env;
	char	**paths;
	char	*path;
	char	*part_path;

	/* NOTE
		- Si el comando tiene una barra --> es una ruta absoluta o relativa
		- SI no hay barra --> buscamos en PATH
	*/
	if (ft_strchr(command, '/'))
		return (command);
	env = check_envp(envp);
	paths = ft_split(envp[env] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, command);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

// Se encarga de ejecutar un comando especifico que le pasamos en el argv
// Separamos la cadena de caracteres con el split
// Ejecuta el execve comprobando que la ruta del comando este bien
void	ft_execve(char *argv, char **envp)
{
	char	**command;

	command = ft_split(argv, ' ');
	if (command == NULL) // Error si hay fallo en la asgnacion de memoria
	{
		perror_error("Error al dividir la cadena");
		return ;
	}
	if (execve(find_path(command[0], envp), command, envp) == -1)
		perror_error("La ruta esta incorrecta");
}
