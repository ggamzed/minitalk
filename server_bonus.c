/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemirci <gdemirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:34:18 by gdemirci          #+#    #+#             */
/*   Updated: 2025/08/05 16:40:50 by gdemirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_putnbr(int n)
{
	unsigned int	nb;
	unsigned char	chr;

	nb = n;
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	if (nb < 10)
	{
		chr = nb + 48;
		write(1, &chr, 1);
	}
}

void	send_signal(int pid, int sig_val)
{
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

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static unsigned char	chr = 0;
	static int				i = 0;
	static int				client_pid = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	if (sig == SIGUSR2)
		chr |= (1 << i);
	i++;
	if (i == 8)
	{
		i = 0;
		if (chr == 0)
		{
			send_signal(client_pid, 1);
			client_pid = 0;
			return ;
		}
		if (chr != 0)
			write(1, &chr, 1);
		chr = 0;
	}
	send_signal(client_pid, 0);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	signal_action;

	signal_action.sa_flags = SA_SIGINFO;
	signal_action.sa_sigaction = signal_handler;
	sigemptyset(&signal_action.sa_mask);
	pid = getpid();
	if ((sigaction(SIGUSR1, &signal_action, NULL) == -1)
		|| (sigaction(SIGUSR2, &signal_action, NULL) == -1))
	{
		write (1, "SIGACTION interrupted!\n", 23);
		exit(EXIT_FAILURE);
	}
	write(1, "PID: ", 5);
	ft_putnbr(pid);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
