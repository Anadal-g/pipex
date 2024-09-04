/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:40:15 by anadal-g          #+#    #+#             */
/*   Updated: 2024/09/04 17:43:26 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_file(char *argv, int x)
{
	int	file;

	file = 0;
	// Esto indica que el archivo se abre solo para lectura
	if (x == 1)
		file = open(argv, O_RDONLY);
	if (x == 2)
		file = open(argv, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file == -1)
		perror_error("Error al abrir el archivo");
	return (file);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int wait_childs_bonus(pid_t pid)
{
    pid_t	waited;
	int		aux;
	int		status;
	

    // waited = waitpid(pid, status, 0);
    // if (waited == -1)
    //     return -1; // Error al esperar al proceso hijo


	while (1)
	{
		waited = waitpid(-1, &aux, 0);
		if (waited < 0)
			break ;
		if (waited == pid)
			status = WEXITSTATUS(aux);
	}
    return (status);
}

int main(int ac, char *av[], char *env[])
{
    int fd[2];
    int pid;
    int final_status;

    final_status = 0;
    if (ac >= 5)
    {
        if (ft_strcmp(av[1], "here_doc") == 0)
            here_doc(av);

        if (pipe(fd) == -1)
            perror_error("Error al crear pipe");

        pid = fork();
        if (pid == -1)
            perror_error("Error al crear proceso hijo");

        if (pid == 0)
            first_child(av, env, fd);
        else
            next_cmds(av, env, &pid, fd);
		close(fd[0]);
        close(fd[1]);
        final_status = wait_childs_bonus(pid);
        unlink("TMP_FILE");  // Elimina el archivo temporal si se usó here_doc
    }
    else
    {
        perror_error("Número insuficiente de argumentos");
    }
    return final_status;
}

// int	main (int argc, char **argv, char **envp)
// {
// 	int	fd[2];
// 	int	pid[2];
// 	int	status;

// 	if (argc >= 5)
// 	{
// 		if (ft_strcmp(argv[1], "here_doc") == 0)
// 		{
// 			open_file(argv[argc - 1], 1);
// 			here_doc(argv);
// 		}
// 		if (pipe(fd) == -1)
// 			perror_error("pipe error");
// 		pid[0] = fork();
// 		if (pid[0] == -1)
// 			perror_error("fork error");
// 		if (pid[0] == 0)
// 			first_child(argv, envp, fd);
// 		else
// 			other_childs(argv, envp, pid, fd);
// 		wait_childs(&status, pid[0]);
// 		return (WEXITSTATUS(status));
// 	}
// }
