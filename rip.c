/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:04:17 by brfialho          #+#    #+#             */
/*   Updated: 2026/04/01 18:00:04 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	count_pairs(char *s)
{
	int	pairs = 0;
	int open = 0;

	while (*s)
	{
		if (*s == '(')
			open++;
		else if (*s == ')' && open)
		{
			open--;
			pairs++;
		}
		s++;
	}
	return (pairs);
}

char	is_balanced(char *s)
{
	int		open;
	int		close;

	open = 0;
	close = 0;
	while (*s)
	{
		if (*s == '(')
			open++;
		else if (*s == ')')
			close++;
		if (open - close < 0)
			return (0);
		s++;
	}
	return ((open - close) == 0);
}

void	solver(char *s, int pairs, int index)
{
	if (!s[index])
		return ;
	if (is_balanced(s))
	{
		puts(s);
		return ;
	}

	int		i;
	char	c;

	i = index - 1;
	while (s[++i])
	{
		c = s[i];
		s[i] = ' ';
		if (count_pairs(s) >= pairs)
			solver(s, pairs, index + 1);
		s[i] = c;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2 || !argv[1][0])
		return (1);

	if (is_balanced(argv[1]))
		return (puts(argv[1]));

	char	s[10000] = {0};
	int i = -1;
	while (argv[1][++i])
		s[i] = argv[1][i];

	// printf("PAIRS: %d\n", count_pairs(s));
	solver(s, count_pairs(s), 0);
}
