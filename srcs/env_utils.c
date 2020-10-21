/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:14:39 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/21 10:36:47 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	char	**g_env;
extern	char	**g_env_local;

static	int		ft_strncmp_gejeanet(const char *s1, const char *s2, size_t n)
{
	while (n != 0 && *s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			break ;
		else
		{
			n--;
			s1++;
			s2++;
		}
	}
	if (n == 0 || (*s1 == '\0' && *s2 == '\0'))
		return (0);
	else
		return ((int)(unsigned char)(*s1) - (int)(unsigned char)(*s2));
}

static	char	*find_var(char *var, char **env)
{
	size_t	len;

	if (env == NULL || var == NULL)
		return (NULL);
	len = ft_strlen(var);
	while (*env != NULL)
	{
		if (ft_strncmp_gejeanet(*env, var, len) == 0)
		{
			if ((*(*env + len)) == '=')
				return (*env + len + 1);
			if ((*(*env + len)) == '\0')
				return (NULL);
		}
		env++;
	}
	return (NULL);
}

/*
** return a pointer to variable value
** it MUST NOT be passed to free() !!!
** return NULL if variable does not exist OR does not have value
*/

char			*env_get_var(char *var)
{
	char	*result;

	if ((result = find_var(var, g_env)) != NULL)
		return (result);
	else if ((result = find_var(var, g_env_local)) != NULL)
		return (result);
	else
		return (NULL);
}

/*
** set variable to the value in the given environment (if exists)
** if it does not exist - add variable and set it to the given value
*/

void			env_set_var(char *var, char *value, char **env)
{
	size_t	len;
	size_t	new_len;

	len = ft_strlen(var);
	while (*env != NULL)
	{
		if ((ft_strncmp(*env, var, len) == 0) && \
			((*(*env + len) == '=') || (*(*env + len) == '\0')))
		{
			free(*env);
			(value == NULL) ? (new_len = len + 1) :
							(new_len = len + ft_strlen(value) + 2);
			*env = malloc(new_len);
			ft_memmove(*env, var, len);
			if (value != NULL)
			{
				*(*env + len) = '=';
				ft_memmove(*env + len + 1, value, ft_strlen(value));
				*(*env + len + 1 + ft_strlen(value)) = '\0';
			}
			else
				*(*env + len) = '\0';
		}
		env++;
	}
}

/*
** delete variable from given environment
** if variable does not exist - do nothing
*/

void			env_del_var(char *var, char **env)
{
	size_t	len;

	len = ft_strlen(var);
	while (*env != NULL)
	{
		if ((ft_strncmp(*env, var, len) == 0) && \
			((*(*env + len) == '=') || (*(*env + len) == '\0')))
		{
			free(*env);
			while (*env != NULL)
			{
				*env = *(env + 1);
				env++;
			}
			return ;
		}
		env++;
	}
}
