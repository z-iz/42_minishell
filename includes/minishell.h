// ADD HEADER


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <stdio.h>
# include <signal.h>
# include "libft.h"
# include "errors.h"
# include "lexer.h"
//# include "parser.h"

/*
** External variables' declarations
*/

/*
** extern char	**environ;
*/

extern int	errno;

/*
** Builtin functions
*/

int			ft_cd(char **command);
int			ft_pwd(void);
void		ft_exit(void);
int			ft_env(void);
int			ft_echo(char **args);
int			ft_export(char **var);
int			ft_unset(char **var);
int			ft_env(void);

/*
** Input handling
*/

char		**read_input(int *gnl_result);

/*
** Signal handlers
*/

void   		signal_handler(int signo);

/*
** Environment handling
*/

char		**env_init(char **env);
void		env_free(char **env);
void		env_del_var(char *var, char **env);
void		env_set_var(char *var, char *value, char **env);
char		*env_get_var(char *var);

/*
** Utils
*/

void		print_prompt(void);
void		print_prompt2(void);

#endif
