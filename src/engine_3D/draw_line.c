#include "cub.h"

/**
 * @brief 
 * 
 */
typedef	 struct s_bresenham
{
	int	differential[DIM];
	int	decision_parameter;
	int	current[DIM];
	int	end[DIM];
} t_bresenham;

/**
 * @brief does the bresenham's optimised algorithm to traverse each step of the digitalised line: drawing each pixel.
 * 
 * Plot the starting point
 * 
 * 
 * @param b 
 * @param start_point 
 * @param end_point 
 */
bresenham_steps(t_bresenham *b, int start_point[], int end_point[])
{
	
	printf("(%d, %d)\n", b->current[X], b->current[Y]);
	put_the_pixel();

	while (b->current[X] < b->end[X])
	{						// Loop until we reach the end point
		if (b->decision_parameter >= 0)
		{					// Decision parameter
			if ((b->current[Y] < b->end[Y]))	// Increment or decrement b->current[Y]
				(b->current[Y] += 1);
			else 
				(b->current[Y] -= 1);
			b->decision_parameter = b->decision_parameter + 2 * (b->differential[Y] - b->differential[X]);	// Update decision parameter
		} else {
			b->decision_parameter = b->decision_parameter + 2 * b->differential[Y];			// Update decision parameter
		}
		
		b->current[X]++;						// Increment b->current[X]-coordinate
		printf("(%d, %d)\n", b->current[X], b->current[Y]); // Plot the next point
	}
}

/**
 * @brief Construct a new bresenham ini object
 * 
 * Calculate difference in x
 * Calculate difference in y
 * 
 * Calculate Initial decision parameter
 * 
 * depending of if line goes from right to left or left to right:
 * ( If the line goes from right to left: swap starting points)
 * 
 * Starting current x-coordinate
 * Starting current y-coordinate
 * 
 * end x-coordinate
 * end y-coordinate
 * 
 * @param b 
 * @param start_point 
 * @param end_point 
 */
bresenham_ini(t_bresenham *b, int start_point[], int end_point[])
{
	b->differential[X] = abs(end_point[X] - start_point[X]);
	b->differential[Y] = abs(end_point[Y] - start_point[Y]);

	b->decision_parameter = 2 * b->differential[Y] - b->differential[X];
	b->current[X] = start_point[X];
	b->current[Y] = start_point[Y];
	
	if (start_point[X] > end_point[X])
	{
		b->current[X] = end_point[X];
		b->current[Y] = end_point[Y];
		b->end[X] = start_point[X];
		b->end[Y] = start_point[Y];
	} 
	else
	{
		b->end[X] = end_point[X];
		b->end[Y] = end_point[Y];
	}
	return ;
}

//using bresenham's optimised algorithm
/**
 * @brief 
 * 
 *	Calculate difference in x
 *	Calculate difference in y
 * @param start_point 
 * @param end_point 
 */
void draw_line(int start_point[], int end_point[])
{
	t_bresenham b;

	bresenham_ini(&b, start_point, end_point);
	bresenham_steps(&b, start_point, end_point);

}

#include <stdio.h>
#include <stdlib.h>

void drawLine(int x1, int y1, int x2, int y2) {
	int dx, dy, p, x, y, endX, endY;
	
	dx = abs(x2 - x1);     // Calculate difference in x
	dy = abs(y2 - y1);     // Calculate difference in y
	
	p = 2 * dy - dx;       // Initial decision parameter
	x = x1;                 // Starting x-coordinate
	y = y1;                 // Starting y-coordinate
	
	if (x1 > x2) {         // If the line goes from right to left
		x = x2;             // Swap the starting points
		y = y2;
		endX = x1;
		endY = y1;
	} else {
		endX = x2;
		endY = y2;
	}
}

int main() {
    int x1, y1, x2, y2;
    
    // Input starting and ending points
    printf("Enter x1, y1, x2, y2: ");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    
    // Call the drawLine function
    drawLine(x1, y1, x2, y2);
    
    return 0;
}
