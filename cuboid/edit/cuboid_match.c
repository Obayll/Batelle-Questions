// Program: Take in 3 inputs.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void generate_cuboid(char cuboid[], int x_len, int y_len, int z_len);

void main(int argc, char** argv)
{
	// Check to make sure user passes three arguments:
	if (argc != 4)
	{
		printf("Please pass the following three arguments: x, y, z\n");
		exit(1);
	}

	// Store out cuboid dimensions
	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	int z = atoi(argv[3]);

	if (((x <= 0 || x > 10) || (y <= 0 || y > 10) || (z <= 0 || z > 10)))
	{
		exit(1);
	}

	// Print out cuboid dimensions
	printf("Cuboid length: %i\n", x);
	printf("Cuboid width: %i\n", y);
	printf("Cuboid height: %i\n", z);

	// Allocate memory to store cuboid shape characters.
	char* cuboid = malloc(x * y * z * sizeof(int));

	// Generate the cuboid output we can pass to printf to print cuboid.
	generate_cuboid(cuboid, x, y, z);

	printf("%s\n", cuboid);

	free(cuboid);

	exit(0);
}

void generate_cuboid(char cuboid[], int x_len, int y_len, int z_len)
{
	int lines = y_len + z_len + 1;
	int index = 0;
	int i, j, k, m, side_chars;

	for (i = 0; i < lines; i++)
	{
		k = index;

		// Calculate number of spaces for this line
		for (j = abs(y_len - i); j > 0; j--)
		{
			cuboid[k++] = ' ';
		}

		// Insert first edge on each line
		if (i <= y_len && i)
		{
			cuboid[k++] = ' ';
			cuboid[k++] = '/';
		}
		else
		{
			if (i <= y_len)
			{
				cuboid[k++] = ' ';
			}
			else
			{
				cuboid[k++] = '\\';
			}
				
			cuboid[k++] = ' ';
		}

		// Calculate underscores
		for (m = 0; m < x_len; m++)
		{
			cuboid[k++] = '_';

			if (i <= y_len && i)
			{
				cuboid[k++] = ' ';
				cuboid[k++] = '/';
			}
			else if (i <= y_len)
			{
				cuboid[k++] = ' ';
				cuboid[k++] = ' ';
			}
			else
			{
				cuboid[k++] = '\\';

				if ( m != x_len - 1 )
				{
					cuboid[k++] = ' ';
				}
			}
		}

		// Calculate remaining edges
		if (i > z_len)
		{
			side_chars = lines - i;
		}
		else
		{
			side_chars = i;
		}

		for (m = 0; m < side_chars; m++)
		{
			if (i <= y_len && i)
			{
				if (m < y_len && m < z_len)
				{
					cuboid[k++] = '\\';

					if (m < side_chars - 1)
					{
						cuboid[k++] = '/';
					}
				}
			}
			else if (i <= y_len)
			{
				cuboid[k++] = ' ';
				cuboid[k++] = ' ';
			}
			else if (m < y_len && m < z_len)
			{
				cuboid[k++] = '/';

				if (m < side_chars - 1)
				{
					cuboid[k++] = '\\';
				}
			}
		}

		cuboid[k++] = '\n';

		index = k;	
	}
}