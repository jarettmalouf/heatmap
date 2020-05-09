#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>

#include "track.h"
#include "trackpoint.h"
#include "location.h"

int main(int argc, char **argv)
{
	double width = (double) atof(argv[1]);
	double height = (double) atof(argv[2]);

	// printf("width: %lf, height: %lf\n", width, height);

	// construct trk from file

	track *trk = track_create();
	char line[1000];
	char c1;

	while (fgets(line, sizeof(line), stdin) != NULL)
	{
		double lat, lon;
		long time;
		if (sscanf(line, "%lf %lf %ld", &lat, &lon, &time) == 3)
		{
			trackpoint* pt_eph = trackpoint_create(lat, lon, time);
			track_add_point(trk, pt_eph);
			trackpoint_destroy(pt_eph);

		}
		else if ((sscanf(line, "%c", &c1) == 1) && c1 == '\n')
		{
			track_start_segment(trk);
		}
	}

	// print_track(trk);

	// adjusting the map to the new symbols

	int m = strlen(argv[3]);
	int n = (int) atof(argv[4]);

	// printf("m = %d, n = %d\n", m, n);

	int **map;
	int rows, cols;
	track_heatmap(trk, width, height, &map, &rows, &cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int cell = map[i][j];
			char cell_char;
			
			for (int k = 0; k < m - 1; k++)
			{
				if ((cell >= k*n) && (cell <= (k+1) * n - 1))
				{
					cell_char = argv[3][k];
				}
			}
			if (cell >= (m - 1) * n)
			{
				cell_char = argv[3][m - 1];
			}
			printf("%c", cell_char);
		}
		printf("\n");
	}
	// destroy map
	// free each row then free map
	for (int i = 0; i < rows; i++) 
	{
		free(map[i]);
	}
	free(map);

	track_destroy(trk);
}
