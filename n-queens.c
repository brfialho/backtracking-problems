/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n-queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:07:47 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/31 19:08:21 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

char	**get_matrix(int n)
{
	char **matrix;

	matrix = calloc(n + 1, sizeof(char *));
	if (!matrix)
		return (NULL);

	for (int i = 0; i < n; i++)
	{
		matrix[i] = calloc(n + 1, sizeof(char));
		if (!matrix[i])
			return (NULL);
		for (int j = 0; j < n; j++)
			matrix[i][j] = '.';
	}
	return (matrix);
}

void	print_matrix(char **matrix)
{
	int	row;

	row = -1;
	while (matrix[++row])
		printf("%s\n", matrix[row]);
	printf("\n");
}

char	in_check_line(char **matrix, int n, int row, int col)
{
	int	x;

	x = -1;
	while (++x < n)
		if (matrix[row][x] == 'Q' && x != col)
			return (1);
	return (0);
}

char	in_check_colum(char **matrix, int n, int row, int col)
{
	int	y;

	y = -1;
	while (++y < n)
		if (matrix[y][col] == 'Q' && y != row)
			return (1);
	return (0);
}

char	in_check_left_diag(char **matrix, int n, int row, int col)
{
	int	y;
	int x;

	y = row;
	x = col;
	while (x && y)
	{
		x--;
		y--;
	}
	while (x < n && y < n)
	{
		if (matrix[y][x] == 'Q' && y != row && x != col)
			return (1);
		x++;
		y++;
	}
	return (0);
}

char	in_check_right_diag(char **matrix, int n, int row, int col)
{
	int	y;
	int x;

	y = row;
	x = col;
	while (x < n - 1 && y)
	{
		x++;
		y--;
	}
	while (x && y < n)
	{
		if (matrix[y][x] == 'Q' && y != row && x != col)
			return (1);
		x--;
		y++;
	}
	return (0);
}

int	valid(char **matrix, int n, int row, int col)
{
	int	q_count;

	if (in_check_line(matrix, n, row, col)
		|| in_check_colum(matrix, n, row, col)
		|| in_check_left_diag(matrix, n, row, col)
		|| in_check_right_diag(matrix, n, row, col))
		return (0);
	q_count = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (matrix[i][j] == 'Q')
				q_count++;
	if (q_count == n)
		print_matrix(matrix);
	return (1);
}


void	solver(char **matrix, int n, int row, int col)
{
	if (row == n)
		return ;
	if (col == n)
	{
		solver(matrix, n, row + 1, 0);
		return ;
	}
	matrix[row][col] = 'Q';
	if (valid(matrix, n, row, col))
		solver(matrix, n, row, col + 1);
	matrix[row][col] = '.';
	solver(matrix, n, row, col + 1);
}

int main(int argc, char **argv)
{
	int		n;
	char	**matrix;

	if (argc != 2 || !argv[1][0])
		return (1);

	n = atoi(argv[1]);

	if (n == 0)
		printf("0\n");
	if (n < 4)
		return (2);

	matrix = get_matrix(n);
	if (!matrix)
		return (3);
	solver(matrix, n, 0, 0);

	for (int i = 0; i < n; i++)
		free(matrix[i]);
	free(matrix);
}
