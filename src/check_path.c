/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:15:36 by anadal-g          #+#    #+#             */
/*   Updated: 2024/02/26 15:25:18 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

//Se encarga de ejecutar un comando especifico que le pasamos en el argv
//Separamos la cadena de caracteres con el split
//Ejecuta el execve comprobando que la ruta del comando este bien
void	ft_execve(char *argv, char **envp)
{
	char **command;
    
	command = ft_split(argv, ' ');
    if (execve(check_path(command[0], envp), command, envp) == -1)
        ft_error(127);
}
