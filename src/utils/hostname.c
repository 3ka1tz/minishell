/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hostname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:13:11 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/16 12:16:20 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	build_hostname(char *name, char *user, char *cwd, char *home)
{
	size_t	home_len;

	ft_strcpy(name, "\033[34m");
	ft_strcat(name, user);
	ft_strcat(name, "@minishell:");
	if (home)
	{
		home_len = ft_strlen(home);
		if (ft_strncmp(cwd, home, home_len) == 0)
		{
			ft_strcat(name, "~");
			ft_strcat(name, cwd + home_len);
		}
		else
			ft_strcat(name, cwd);
	}
	else
		ft_strcat(name, cwd);
	ft_strcat(name, "$ ");
	ft_strcat(name, "\033[0m");
}

char	*hostname(char **env)
{
	static char	*name;
	char		*user;
	char		*home;
	char		cwd[1024];
	size_t		size;

	user = get_value("USER", env);
	if (!user)
		user = "guest";
	home = getenv("HOME");
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("Error: Couldn't get current working directory"), NULL);
	size = ft_strlen(user) + ft_strlen("minishell") + ft_strlen(cwd) + 4;
	name = malloc(size);
	if (!name)
		return (perror("Error: Memory allocation failed for hostname"), NULL);
	build_hostname(name, user, cwd, home);
	return (name);
}
