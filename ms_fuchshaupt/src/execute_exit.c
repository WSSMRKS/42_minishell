/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:22:53 by sgramsch          #+#    #+#             */
/*   Updated: 2024/12/05 12:22:53 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_atoi(t_data *data, char *nptr, unsigned char *nbr)
{
	long	i;
	int		sign;

	i = 0;
	sign = 1;
	if (!nptr || ft_strncmp(nptr, "--", ft_strlen(nptr)) == 0)
		return ;
	while (nptr[i] && (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
			|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			exit_on_error(data, "Numeric argument required", 1, 2);
		*nbr = *nbr * 10 + (nptr[i] - '0');
		i++;
	}
	*nbr = *nbr * sign;
}

int	only_digits(char *str)
{
	int	pos;

	pos = 0;
	if (!str || !(*str))
		return (0);
	while (str[pos])
	{
		if (!ft_isdigit(str[pos]))
			return (0);
		pos ++;
	}
	return (1);
}

int	numeric(t_cmd_list *cmd)
{
	t_token	*arg;

	arg = cmd->first_token;
	if (arg->str == NULL || arg->str[0] == '\0')
		return (2);
	if (arg->str[0] == '-' && arg->str[1] == '-' && !arg->str[2])
		return (0);
	if ((arg->str[0] == '+' || arg->str[0] == '-') && only_digits(arg->str + 1))
		return (0);
	if (!ft_isdigit(arg->str[0]))
		return (2);
	return (0);
}

int	handle_exit(t_data *data, t_cmd_list *cmd)
{
	unsigned char	nbr;
	int				tmp;

	nbr = data->status;
	if (data->parent == 1)
		write(1, "exit\n", 5);
	if (cmd->first_token != NULL)
	{
		tmp = numeric(cmd);
		if (tmp == 2)
			exit_on_error(data, "Numeric argument required", 1, 2);
		if (cmd->first_token->next != NULL)
			exit_on_error(data, TMA, 1, 1);
		if (tmp == 0)
			exit_atoi(data, cmd->first_token->str, &nbr);
	}
	printf("exiting %u\n", nbr);
	cleanup(data);
	exit(nbr);
	return (0);
}
