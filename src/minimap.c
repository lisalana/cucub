/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:31:05 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/07 12:37:17 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_modern_tile_color(char tile)
{
	if (tile == '1')
		return (COLOR_WALL);
	else if (tile == '0')
		return (COLOR_FLOOR);
	else
		return (COLOR_VOID);
}

static int	is_pixel_in_minimap_bounds(int pixel_x, int pixel_y)
{
	if (pixel_x >= MINIMAP_MARGIN && pixel_x < MINIMAP_MARGIN + MINIMAP_SIZE
		&& pixel_y >= WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN
		&& pixel_y < WINDOW_HEIGHT - MINIMAP_MARGIN)
		return (1);
	return (0);
}

static void	draw_circle_pixel(t_data *game, t_point center, t_point offset,
		int color)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = center.x + offset.x;
	pixel_y = center.y + offset.y;
	if (is_pixel_in_minimap_bounds(pixel_x, pixel_y))
		put_pixel(game, pixel_x, pixel_y, color);
}

static void	draw_circle(t_data *game, t_point center, int radius, int color)
{
	t_point	offset;

	offset.y = -radius;
	while (offset.y <= radius)
	{
		offset.x = -radius;
		while (offset.x <= radius)
		{
			if (offset.x * offset.x + offset.y * offset.y <= radius * radius)
				draw_circle_pixel(game, center, offset, color);
			offset.x++;
		}
		offset.y++;
	}
}

static t_point	calculate_border_distance(t_point pos, t_point start)
{
	t_point	distance;

	distance.x = 0;
	distance.y = 0;
	if (pos.x < start.x)
		distance.x = start.x - pos.x;
	else if (pos.x >= start.x + MINIMAP_SIZE)
		distance.x = pos.x - (start.x + MINIMAP_SIZE - 1);
	if (pos.y < start.y)
		distance.y = start.y - pos.y;
	else if (pos.y >= start.y + MINIMAP_SIZE)
		distance.y = pos.y - (start.y + MINIMAP_SIZE - 1);
	return (distance);
}

static void	draw_minimap_border(t_data *game, t_point start)
{
	t_point	pos;
	t_point	distance;

	pos.y = start.y - MINIMAP_BORDER_SIZE;
	while (pos.y < start.y + MINIMAP_SIZE + MINIMAP_BORDER_SIZE)
	{
		pos.x = start.x - MINIMAP_BORDER_SIZE;
		while (pos.x < start.x + MINIMAP_SIZE + MINIMAP_BORDER_SIZE)
		{
			if (pos.x >= 0 && pos.x < WINDOW_WIDTH && pos.y >= 0
				&& pos.y < WINDOW_HEIGHT)
			{
				distance = calculate_border_distance(pos, start);
				if (distance.x * distance.x + distance.y
					* distance.y <= MINIMAP_BORDER_SIZE * MINIMAP_BORDER_SIZE)
					put_pixel(game, pos.x, pos.y, COLOR_MINIMAP_BORDER);
			}
			pos.x++;
		}
		pos.y++;
	}
}

static void	draw_minimap_background(t_data *game, t_point start)
{
	t_point	pos;

	pos.y = start.y;
	while (pos.y < start.y + MINIMAP_SIZE)
	{
		pos.x = start.x;
		while (pos.x < start.x + MINIMAP_SIZE)
		{
			if (pos.x >= 0 && pos.x < WINDOW_WIDTH && pos.y >= 0
				&& pos.y < WINDOW_HEIGHT)
				put_pixel(game, pos.x, pos.y, COLOR_MINIMAP_BG);
			pos.x++;
		}
		pos.y++;
	}
}

static void	draw_modern_minimap_background(t_data *game)
{
	t_point	start;

	start.x = MINIMAP_MARGIN;
	start.y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN;
	draw_minimap_border(game, start);
	draw_minimap_background(game, start);
}

static int	get_wall_pixel_color(int x, int y, int color)
{
	if (x == 0 || y == 0 || x == MINIMAP_TILE_SIZE - 1 || y == MINIMAP_TILE_SIZE
		- 1)
		return (color - 0x101010);
	else
		return (color);
}

static void	draw_tile_pixel(t_data *game, t_point screen_pos, t_point offset,
		int color)
{
	t_point	pixel_pos;
	int		final_color;

	pixel_pos.x = screen_pos.x + offset.x;
	pixel_pos.y = screen_pos.y + offset.y;
	if (is_pixel_in_minimap_bounds(pixel_pos.x, pixel_pos.y))
	{
		if (color == COLOR_WALL)
			final_color = get_wall_pixel_color(offset.x, offset.y, color);
		else
			final_color = color;
		put_pixel(game, pixel_pos.x, pixel_pos.y, final_color);
	}
}

static void	draw_smooth_tile(t_data *game, t_point screen_pos, int color)
{
	t_point	offset;

	offset.y = 0;
	while (offset.y < MINIMAP_TILE_SIZE)
	{
		offset.x = 0;
		while (offset.x < MINIMAP_TILE_SIZE)
		{
			draw_tile_pixel(game, screen_pos, offset, color);
			offset.x++;
		}
		offset.y++;
	}
}

static void	calculate_map_position(t_data *game, int minimap_x, int minimap_y,
		t_point *map_pos)
{
	double	player_map_x;
	double	player_map_y;
	int		tiles_per_row;
	int		center_tile_x;
	int		center_tile_y;

	player_map_x = game->player.pos[0] / TILESIZE;
	player_map_y = game->player.pos[1] / TILESIZE;
	tiles_per_row = MINIMAP_SIZE / MINIMAP_TILE_SIZE;
	center_tile_x = tiles_per_row / 2;
	center_tile_y = tiles_per_row / 2;
	map_pos->x = (int)player_map_x + (minimap_x - center_tile_x);
	map_pos->y = (int)player_map_y + (minimap_y - center_tile_y);
}

static void	draw_minimap_tile(t_data *game, t_point minimap_pos,
		t_point map_pos)
{
	t_point	screen_pos;
	char	tile;
	int		color;

	screen_pos.x = MINIMAP_MARGIN + minimap_pos.x * MINIMAP_TILE_SIZE;
	screen_pos.y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + minimap_pos.y
		* MINIMAP_TILE_SIZE;
	if (map_pos.y >= 0 && map_pos.y < game->map_height)
	{
		if (map_pos.x >= 0 && map_pos.x < (int)ft_strlen(game->map[map_pos.y]))
		{
			tile = game->map[map_pos.y][map_pos.x];
			color = get_modern_tile_color(tile);
			draw_smooth_tile(game, screen_pos, color);
		}
		else
			draw_smooth_tile(game, screen_pos, COLOR_VOID);
	}
	else
		draw_smooth_tile(game, screen_pos, COLOR_VOID);
}

static void	render_precise_tiles(t_data *game)
{
	int		tiles_per_row;
	t_point	minimap_pos;
	t_point	map_pos;

	tiles_per_row = MINIMAP_SIZE / MINIMAP_TILE_SIZE;
	minimap_pos.y = 0;
	while (minimap_pos.y < tiles_per_row)
	{
		minimap_pos.x = 0;
		while (minimap_pos.x < tiles_per_row)
		{
			calculate_map_position(game, minimap_pos.x, minimap_pos.y,
				&map_pos);
			draw_minimap_tile(game, minimap_pos, map_pos);
			minimap_pos.x++;
		}
		minimap_pos.y++;
	}
}

static double	calculate_fov_angle(t_data *game, int direction)
{
	double	player_angle;
	double	fov_angle;

	player_angle = atan2(game->player.dir[1], game->player.dir[0]);
	fov_angle = M_PI / 3.0;
	return (player_angle + (fov_angle / 2.0) * direction);
}

static void	draw_single_fov_line(t_data *game, t_point center, int direction)
{
	double	angle;
	int		fov_length;
	t_point	end;

	angle = calculate_fov_angle(game, direction);
	fov_length = MINIMAP_TILE_SIZE * 3;
	end.x = center.x + (int)(cos(angle) * fov_length);
	end.y = center.y + (int)(sin(angle) * fov_length);
	draw_line(game, center, end, COLOR_FOV_LINE);
}

static void	draw_fov_lines(t_data *game, int center_x, int center_y)
{
	t_point	center;
	int		i;

	center.x = center_x;
	center.y = center_y;
	i = -1;
	while (i <= 1)
	{
		draw_single_fov_line(game, center, i);
		i += 2;
	}
}

static void	draw_player_direction(t_data *game, int center_x, int center_y)
{
	double	dir_length;
	t_point	center;
	t_point	dir_end;

	dir_length = MINIMAP_PLAYER_SIZE * 1.8;
	center.x = center_x;
	center.y = center_y;
	dir_end.x = center_x + (int)(game->player.dir[0] * dir_length);
	dir_end.y = center_y + (int)(game->player.dir[1] * dir_length);
	draw_line(game, center, dir_end, COLOR_DIRECTION);
	center.x++;
	dir_end.x++;
	draw_line(game, center, dir_end, COLOR_DIRECTION);
	center.x--;
	center.y++;
	dir_end.x--;
	dir_end.y++;
	draw_line(game, center, dir_end, COLOR_DIRECTION);
}

static void	draw_modern_player(t_data *game)
{
	t_point	center;

	center.x = MINIMAP_MARGIN + MINIMAP_SIZE / 2;
	center.y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + MINIMAP_SIZE / 2;
	draw_fov_lines(game, center.x, center.y);
	draw_circle(game, center, MINIMAP_PLAYER_SIZE / 2 + 1, 0x000000);
	draw_circle(game, center, MINIMAP_PLAYER_SIZE / 2, COLOR_PLAYER);
	draw_player_direction(game, center.x, center.y);
}

void	render_minimap(t_data *game)
{
	draw_modern_minimap_background(game);
	render_precise_tiles(game);
	draw_modern_player(game);
}
