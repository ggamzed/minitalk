#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_handle_error(int error_num);
void	ft_putchar(char c);
void	ft_putnbr(int n);
int		ft_new_atoi(char *str);
void	send_signal(int pid, int sig_val);

#endif