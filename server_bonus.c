#include "minitalk_bonus.h"

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
		ft_handle_error(1);
	write(1, "PID: ", 5);
	ft_putnbr(pid);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
