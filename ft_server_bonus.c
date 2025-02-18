/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:44:23 by aaycan            #+#    #+#             */
/*   Updated: 2025/02/18 16:37:13 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

int g_join = 0;

static void	ft_putstr(char *str);
static void	ft_putnbr(int nb);
static void	ft_putchar(char c);
static void	ft_create_char_by_bits(int sigval, siginfo_t *info, void *context);

int	main(void)
{
	pid_t	pid;
	struct	sigaction sa;

	pid = getpid();
	ft_putstr("Server PID: ");
	ft_putnbr(pid);
	ft_putstr("\nMessage: ");
	sa.sa_sigaction = ft_create_char_by_bits;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

static void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

static void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar('-');
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_create_char_by_bits(int sigval, siginfo_t *info, void *context)
{
	pid_t	client_pid;
	
	client_pid = info->si_pid;
	(void)context;
	if (sigval == SIGUSR1)
		g_join |= 1 << (7 - (g_join >> 8));
	g_join += 1 << 8;
	if ((g_join >> 8) == 8)
	{
		if ((g_join & 0xFF) == '\0')
		{
			ft_putstr("\nMessage: ");
			kill(client_pid, SIGUSR2);
		}
		else
			ft_putchar(g_join & 0xFF);
		g_join = 0;
	}
}
