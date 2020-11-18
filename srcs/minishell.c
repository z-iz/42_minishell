/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 01:44:32 by larosale          #+#    #+#             */
/*   Updated: 2020/11/18 19:36:23 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Global variables' definition.
*/

char	**g_env = NULL;
char	**g_env_local = NULL;
t_token	*g_null_token = NULL;
char	*g_gnl_str = NULL;
int		g_status = 0;

/*
** Reads input string using GNL and creates the structure of type "t_input"
** to hold the string, its length, current reading position and other params.
** Returns the structure on success, or NULL on error.
*/

t_input	*read_input(void)
{
	char	*input;
	char	*temp;
	char	*temp2;
	t_input	*in;

	if (gnl_wrapper(0, &input) < 0 && errman(ERR_SYSCMD, NULL, NULL))
		return (NULL);
	while (ft_strlen(input) > 0 && (input[ft_strlen(input) - 1] == '\\' ||
		check_quotes(input)))
	{
		print_prompt2();
		if (input[ft_strlen(input) - 1] == '\\')
			input[ft_strlen(input) - 1] = '\0';
		if ((gnl_wrapper(0, &temp) < 0 || !(temp2 = ft_strjoin(input, temp))) &&
			errman(ERR_SYSCMD, NULL, NULL))
			return (free_read_input(&input, &temp));
		free_read_input(&input, &temp);
		input = temp2;
	}
	if (!(in = create_input(input)))
		return (free_read_input(&input, &temp));
	free(input);
	return (in);
}

/*
** Starts main minishell loop of reading input, parsing and executing it.
*/

int		shell_loop(void)
{
	t_input	*in;
	t_node	*ast;

	while (1)
	{
		print_prompt();
		if (!(in = read_input()))
			continue ;
		// Added for lexer testing. Remove before submitting
		if (!ft_strncmp(in->buffer, "lexer", 5))
		{
			test_tokenize(in);
			continue ;
		}
		// Added for parser testing. Remove before submitting
		if (!ft_strncmp(in->buffer, "parser", 6))
		{
			test_parser(in);
			continue ;
		}
		if (!(ast = parse_input(in)))
		{
			delete_input(in);
			continue ;
		}
		run_ast(ast);
		delete_tree(ast);
	}
	return (0);
}

/*
** Main minishell function.
*/

int		main(int argc, char **argv, char **env)
{
	g_env = env_init(env);
	g_status = 0;
	if (!(g_null_token = null_token()))
		errman(ERR_SYS, NULL, NULL);
	set_signals(SIGNAL_SET);
	if (argc == 1 && *argv)
		shell_loop();
	env_free(g_env);
	env_free(g_env_local);
	free(g_null_token);
	return (0);
}
