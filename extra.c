#include "raytrace.h"

void	print_matrix(const t_matrix *m)
{
	int	i;
	int	j;

	i = -1;
	printf("matrix is:\n");
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			printf("%.5f  ", m->matrix[i][j]);
		printf("\n");
	}
}
