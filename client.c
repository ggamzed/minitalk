/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemirci <gdemirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:33:36 by gdemirci          #+#    #+#             */
/*   Updated: 2025/08/05 16:40:16 by gdemirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_new_atoi(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
		{
			nb = (nb * 10) + (str[i] - '0');
			i++;
		}
		else
		{
			write(1, "PID is not valid!\n", 18);
			exit(EXIT_FAILURE);
		}
	}
	if (nb < 2)
	{
		write(1, "PID is not valid!\n", 18);
		exit(EXIT_FAILURE);
	}
	return (nb);
}

void	send_signal(int pid, int sig_val)
{
	static int	i = 0;

	if (sig_val == -1 && ++i <= 8)
		sig_val = 0;
	if (sig_val == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			write (1, "KILL interrupted!\n", 18);
			exit(EXIT_FAILURE);
		}
	}
	if (sig_val == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			write (1, "KILL interrupted!\n", 18);
			exit(EXIT_FAILURE);
		}
	}
}

void	string_handler(int pid, char *str)
{
	static int				i = 0;
	static unsigned char	*s_str = 0;

	if (str)
		s_str = (unsigned char *)str;
	if (*s_str)
	{
		if ((*s_str >> i) & 1)
			send_signal(pid, 1);
		else
			send_signal(pid, 0);
		i++;
		if (i == 8)
		{
			s_str++;
			i = 0;
		}
	}
	else
		send_signal(pid, -1);
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int	server_pid = 0;

	(void)context;
	if (!server_pid)
		server_pid = info->si_pid;
	if (sig == SIGUSR1)
		string_handler(server_pid, NULL);
	if (sig == SIGUSR2)
	{
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	signal_action;

	signal_action.sa_flags = SA_SIGINFO;
	signal_action.sa_sigaction = handle_signal;
	sigemptyset(&signal_action.sa_mask);
	if ((sigaction(SIGUSR1, &signal_action, NULL) == -1)
		|| (sigaction(SIGUSR2, &signal_action, NULL) == -1))
	{
		write (1, "SIGACTION interrupted!\n", 23);
		exit(EXIT_FAILURE);
	}
	if (argc != 3)
	{
		write(1, "Incorrect form! Format: ./client <PID> <String>\n", 48);
		exit(EXIT_FAILURE);
	}
	string_handler(ft_new_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
