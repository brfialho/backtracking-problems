/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:53:36 by brfialho          #+#    #+#             */
/*   Updated: 2026/04/03 20:43:36 by brfialho         ###   ########.fr       */
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

/*
** You must implement this function
** It should return the Euclidean distance between 2 cities
*/
float	distance(t_city a, t_city b)
{
	float x = b.x - a.x;
	float y = b.y - a.y;

	return (sqrtf((x * x) + (y * y)));
}

/*
** You must implement this function
** It should compute total distance of the path
** including the return to the starting city
*/
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

/*
** You must implement this function
** Use backtracking to try all permutations
*/

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

	// Read input from stdin
	while (n < 11 && fscanf(stdin, "%f, %f", &cities[n].x, &cities[n].y) == 2)
		n++;

	// If less than 2 cities → distance = 0
	if (n < 2)
	{
		printf("0.00\n");
		return (0);
	}


	// Initialize path: [0,1,2,...]
	int path[11];
	for (int i = 0; i < n; i++)
		path[i] = i;

	if (n == 2)
		return (printf("%.2f\n", total_distance(cities, path, n)), 0);

	float min = FLT_MAX;

	/*
	** Optimization:
	** Fix first city → start from pos = 1
	*/
	solve(cities, path, n, 1, &min);

	printf("%.2f\n", min);
	// printf("%.2f\n", distance(cities[0], cities[1]));
	// printf("%.2f\n", distance(cities[1], cities[2]));
	// printf("%.2f\n", distance(cities[0], cities[2]));
	// printf("TOTAL: %.2f\n", total_distance(cities, path, n));
	return (0);
}
