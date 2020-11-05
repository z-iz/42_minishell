/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:31:05 by larosale          #+#    #+#             */
/*   Updated: 2020/11/05 22:32:23 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_argv(int argc, char **argv)
{
	if (!argc)
		return (0);
	while (argc--)
		free(argv[argc]);
	return (0);
}

int		exec_cmd(char **argv)
{
	char	*path;

	if (ft_strchr(argv[0], '/'))
	{
		if (execve(argv[0], argv, g_env) < 0)
			return (errman(ERR_SYS));
	}
	else
	{
		if (!(path = search_path(argv[0])))
			return (errman(ERR_NOCMD));
		if (execve(path, argv, g_env) < 0)
			return (errman(ERR_SYS));
		free(path);
	}
	return (0);
}

int		get_argv(t_node *arg, int *argc, char **argv)
{
	int	arg_count;

	*argc = 0;
	arg_count = *argc;
	while (arg)
	{
		if (!(argv[arg_count] = ft_strdup(arg->data)))
			return (errman(ERR_SYS));
		if (++arg_count >= MAX_ARGS)
			break ;
		arg = arg->next_sibling;
	}
	argv[arg_count] = NULL;
	return (0);
}
