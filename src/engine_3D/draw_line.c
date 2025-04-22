#include "cub.h"

// /**
//  * @brief 
//  * 
//  */
// typedef	 struct s_bresenham
// {
// 	int	differential[NB_DIM];
// 	int	decision_parameter;
// 	int	current[NB_DIM];
// 	int	end[NB_DIM];
// } t_bresenham;

// /**
//  * @brief does the bresenham's optimised algorithm to traverse each step of the digitalised line: drawing each pixel.
//  * 
//  * Plot the starting point
//  * Loop until we reach the end point
//  * 
//  * depending on decision parameter:
//  * if decision_parameter >= 0
//  * either Y step up or Y step down depending on if I'm above end[Y] or not (step toward end[Y])
//  * 
//  * X step right
//  * 
//  * TODO replace printf of coord by MLX putpixel
//  * 
//  * @param b 
//  * @param start_point 
//  * @param end_point 
//  */
// void	bresenham_steps(t_bresenham *b, int start_point[], int end_point[])
// {
// 	printf("(%d, %d)\n", b->current[X], b->current[Y]); //plot first point
// 	//TODO put_the_pixel();
// 	while (b->current[X] < b->end[X])
// 	{
// 		if (b->decision_parameter >= 0)
// 		{					// Decision parameter
// 			if ((b->current[Y] < b->end[Y]))	// Increment or decrement b->current[Y]
// 				(b->current[Y] += 1);
// 			else 
// 				(b->current[Y] -= 1);
// 			b->decision_parameter = b->decision_parameter + 2 * (b->differential[Y] - b->differential[X]);	// Update decision parameter
// 		}
// 		else
// 		{
// 			b->decision_parameter = b->decision_parameter + 2 * b->differential[Y];			// Update decision parameter
// 		}
// 		b->current[X]++;						// Increment b->current[X]-coordinate
// 		printf("(%d, %d)\n", b->current[X], b->current[Y]); // Plot the next point
// 	}
// }

// /**
//  * @brief Construct a new bresenham ini object
//  * 
//  * Calculate difference in x
//  * Calculate difference in y
//  * 
//  * Calculate Initial decision parameter
//  * 
//  * depending of if line goes from right to left or left to right:
//  * ( If the line goes from right to left: swap starting points)
//  * 
//  * Starting current x-coordinate
//  * Starting current y-coordinate
//  * 
//  * end x-coordinate
//  * end y-coordinate
//  * 
//  * @param b 
//  * @param start_point 
//  * @param end_point 
//  */
// void	bresenham_ini(t_bresenham *b, int start_point[], int end_point[])
// {
// 	b->differential[X] = abs(end_point[X] - start_point[X]);
// 	b->differential[Y] = abs(end_point[Y] - start_point[Y]);
// 	b->decision_parameter = 2 * b->differential[Y] - b->differential[X];
// 	b->current[X] = start_point[X];
// 	b->current[Y] = start_point[Y];
// 	if (start_point[X] > end_point[X])
// 	{
// 		b->current[X] = end_point[X];
// 		b->current[Y] = end_point[Y];
// 		b->end[X] = start_point[X];
// 		b->end[Y] = start_point[Y];
// 	} 
// 	else
// 	{
// 		b->end[X] = end_point[X];
// 		b->end[Y] = end_point[Y];
// 	}
// 	return ;
// }

// //using bresenham's optimised algorithm
// /**
//  * @brief 
//  * 
//  *	Calculate difference in x
//  *	Calculate difference in y
//  * @param start_point 
//  * @param end_point 
//  */
// void	draw_line(int start_point[], int end_point[])
// {
// 	t_bresenham b;

// 	bresenham_ini(&b, start_point, end_point);
// 	bresenham_steps(&b, start_point, end_point);
// }

// // int	main() {
// //     int x1, y1, x2, y2;
    
// //     // Input starting and ending points
// //     printf("Enter x1, y1, x2, y2: ");
// //     scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    
// //     // Call the drawLine function
// //     drawLine(x1, y1, x2, y2);
    
// //     return 0;
// // }
