#include "minitalk_bonus.h"

void	ft_handle_error(int error_num)
{
	if (error_num == 0)
	{
		write (1, "KILL interrupted!\n", 18);
		exit(EXIT_FAILURE);
	}
	if (error_num == 1)
	{
		write (1, "SIGACTION interrupted!\n", 23);
		exit(EXIT_FAILURE);
	}
	if (error_num == 2)
	{
		write(1, "PID is not valid!\n", 18);
		exit(EXIT_FAILURE);
	}
	if (error_num == 3)
	{
		write(1, "Incorrect form! Format: ./client <PID> <String>\n", 48);
		exit(EXIT_FAILURE);
	}
}

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
			ft_handle_error(2);
	}
	if (nb < 2)
		ft_handle_error(2);
	return (nb);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	unsigned int	nb;

	nb = n;
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	if (nb < 10)
		ft_putchar(nb + 48);
}

void	send_signal(int pid, int sig_val)
{
	static int	i = 0;

	if (sig_val == -1)
	{
		i++;
		if (i <= 8)
			if (kill(pid, SIGUSR1) == -1)
				ft_handle_error(0);
	}
	else if (sig_val == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
			ft_handle_error(0);
	}
	else if (sig_val == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
			ft_handle_error(0);
	}
}
