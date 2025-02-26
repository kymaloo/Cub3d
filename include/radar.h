
#ifndef RADAR_H
# define RADAR_H

# define RADAR_POS_Y 0
# define RADAR_POS_X 0

# define RADAR_BLOCKS_RADIUS	5
# define RADAR_SQUARE_SIDE		16

//radar colors
# define COLOR_OUT_OF_BOUNDS	0x8c8c8cFF
# define COLOR_INVALID			0xFF00FFFF
# define COLOR_FLOOR			0xdbdbdbFF
# define COLOR_WALL				0x000000FF
# define COLOR_DOOR				0x007dFFFF
# define COLOR_PLAYER			0xAA0000FF
# define COLOR_VOID				0x442266FF

# define RADAR_PLAYER_CIRCLE_RADIUS 5

void	draw_radar(t_game *g);
#endif