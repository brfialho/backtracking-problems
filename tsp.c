/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:53:36 by brfialho          #+#    #+#             */
/*   Updated: 2026/04/03 21:27:22 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct s_city
{
	float x;
	float y;
}	t_city;

float	distance(t_city a, t_city b)
{
	float x = b.x - a.x;
	float y = b.y - a.y;

	return (sqrtf((x * x) + (y * y)));
}

float	total_distance(t_city *cities, int *path, int n)
{
	float	full_distance;

	full_distance = 0;
	int	i = -1;
	while (++i < n - 1)
		full_distance += distance(cities[path[i]], cities[path[i + 1]]);
	full_distance += distance(cities[path[i]], cities[0]);
	return (full_distance);
}

void	swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void	solve(t_city *cities, int *path, int n, int pos, float *min)
{
	if (pos == n)
		return;
	int	i = 0;
	while (++i < n)
	{
		if (i == pos)
			continue;
		swap(&path[pos], &path[i]);
		float new_min = total_distance(cities, path, n);
		if (*min > new_min)
			*min = new_min;
		solve(cities, path, n, pos + 1, min);
		swap(&path[pos], &path[i]);
	}
}

int	main(void)
{
	t_city	cities[11];
	int		n = 0;

	while (n < 11 && fscanf(stdin, "%f, %f", &cities[n].x, &cities[n].y) == 2)
		n++;

	if (n < 2)
		return (printf("0.00\n"), 0);

	int path[11];
	for (int i = 0; i < n; i++)
		path[i] = i;

	if (n == 2)
		return (printf("%.2f\n", total_distance(cities, path, n)), 0);

	float min = FLT_MAX;
	solve(cities, path, n, 1, &min);
	printf("%.2f\n", min);
	return (0);
}
