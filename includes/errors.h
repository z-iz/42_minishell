/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:27:02 by larosale          #+#    #+#             */
/*   Updated: 2020/11/18 03:56:30 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/*
** The "e_errors" enum and corresponding type determine the list of error
** codes used for error handling with the following meaning:
**   - WAR_*: some non-fatal error (warnings). We do not exit() at this.
**   - ERR_SYS: system call error (file opening, memory allocation, etc);
**   - ERR_UNKNOWN: used in main to handle an error, not catched earlier
**     in helper functions;
**   - ERR_TOKEN: error when parsing tokens;
*/

typedef enum	e_errors
{
	ERR_OK = 0,
	ERR_SYS = -1,
	ERR_SYSCMD = -2,
	ERR_TOKEN = -11,
	ERR_NOCMD = -12,
	ERR_NOHOME = -13,
	ERR_MNARGS = -14,
	ERR_NUMARG = -15,
	ERR_INVLID = -16
}				t_errors;

void			print_error(int e, char *var, char **args);
int				errman(int errnum, char *var, char **args);

#endif
