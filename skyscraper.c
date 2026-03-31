/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skyscraper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:32:30 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/31 18:06:40 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

void	set_row(char (*matrix)[4],  char *def, char *rev, int row)
{
	int	i;

	i = -1;
	while (++i < 4)
		def[i] = matrix[row][i];
	i = -1;
	while (++i < 4)
		rev[i] = matrix[row][3 - i];
}

void	set_col(char (*matrix)[4], char *def, char *rev, int col)
{
	int	i;

	i = -1;
	while (++i < 4)
		def[i] = matrix[i][col];
	i = -1;
	while (++i < 4)
		rev[i] = matrix[3 - i][col];
}

char	check_for_repeats(char *s)
{
	char	found[5] = {0};
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] != '0' && found[s[i] - '0'])
			return (1);
		else	
			found[s[i] - '0'] = 1;
	return (0);
}

char	validate_line(char *s, int rule)
{
	int	visible;
	int	hightest_value;
	int	is_incomplete;

	if (check_for_repeats(s))
		return (0);
	visible = 0;
	hightest_value = 0;
	is_incomplete = 0;
	while (*s)
	{
		if (*s == '0')
			is_incomplete = 1;
		if (*s - '0' > hightest_value)
		{
			hightest_value = *s - '0';
			visible++;
		}
		s++;
	}
	if (is_incomplete)
		return (1);
	if (visible != rule - '0')
		return (0);
	return (1);
}

char validate_position(char *rules, char (*matrix)[4], int row, int col)
{
	char	lines[4][5] = {{0}};

	set_row(matrix, lines[0], lines[1], row);
	set_col(matrix, lines[2], lines[3], col);
	return (validate_line(lines[0], *(rules + row + (2 * 4)))
			&& validate_line(lines[1], *(rules + row + (3 * 4)))
			&& validate_line(lines[2], *(rules + col + (0 * 4)))
			&& validate_line(lines[3], *(rules + col + (1 * 4))));
}

void	print_matrix(char (*matrix)[4])
{
	int	row;
	int	col;

	row = -1;
	while (++row < 4)
	{
		col = -1;
		while (++col < 4)
			write(1, &matrix[row][col], 1);
		write(1, "\n", 1);
	}
}

char	solver(char (*matrix)[4], char *rules, int row, int col)
{
	char	value;

	value = '0';
	if (row > 3)
		return (1);
	if (col > 3)
		return (solver(matrix, rules, row + 1, 0));
	while (++value < '5')
	{
		matrix[row][col] = value;
		if (validate_position(rules, matrix, row, col)
		&& solver(matrix, rules, row, col + 1))
			return (1);
	}
	matrix[row][col] = '0';
	return (0);
}

int	set_rules(char *argv, char *rules)
{
	int	len;

	len = 0;
	while (argv[len])
	{
		if (len > 31)
			return (3);
		if (len % 2 == 0 && !(argv[len] >= '1' && argv[len] <= '4'))
			return (1);
		else if (len % 2 && argv[len] != ' ')
			return (2);
		if (len % 2 == 0)
			rules[len / 2] = argv[len];
		len++;
	}
	if (len != 31)
		return (4);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (write(1, "Usage: ./skycraper \"rules\"\n", 27));
	
	char rules[17] = {0};
	if (set_rules(argv[1], rules))
		return (write(1, "Invalid ruleset\n", 16));
	char matrix[4][4] = {
	    {'0','0','0','0'},
	    {'0','0','0','0'},
	    {'0','0','0','0'},
	    {'0','0','0','0'}};
	if (solver(matrix, rules, 0, 0))
		print_matrix(matrix);
	else
		write(1, "No Solution possible\n", 22);
}


	// char *rules = "4321"
	// 		   "1222"
	// 		   "4321"
	// 	       "1222";
	
	// unsolvable
	// char *rules = "4321"
	// 			"1222"
	// 			"4321"
	// 			"1224";
	// DEU PAU AQUI
	// solvable1
	// char *rules = "4321"
	// 		   "1222"
	// 		   "4321"
	// 	       "1222";
	// 1234
	// 2341
	// 3412
	// 4123	
	// solvable2
	// char *rules = "1223"
	// 		   "3221"
	// 		   "1233"
	// 	       "3321";
	// 4132
	// 3421
	// 1234
	// 2314
	//solvable3
	// char *rules = "3122"
	// 			"1232"
	// 			"2231"
	// 		 	"2213";
	// 1423
	// 3241
	// 2134
	// 4312
