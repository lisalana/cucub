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

static void	draw_circle(t_data *game, int center_x, int center_y, int radius,
		int color)
{
	int	pixel_x;
	int	pixel_y;
	int	x;
	int	y;

	x = -radius;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				pixel_x = center_x + x;
				pixel_y = center_y + y;
				if (pixel_x >= MINIMAP_MARGIN && pixel_x < MINIMAP_MARGIN
					+ MINIMAP_SIZE && pixel_y >= WINDOW_HEIGHT - MINIMAP_SIZE
					- MINIMAP_MARGIN && pixel_y < WINDOW_HEIGHT
					- MINIMAP_MARGIN)
				{
					put_pixel(game, pixel_x, pixel_y, color);
				}
			}
			x++;
		}
		y++;
	}
}

static void	draw_modern_minimap_background(t_data *game)
{
	int	start_x;
	int	start_y;
	int	y;
	int	x;
	int	dx;
	int	dy;

	start_x = MINIMAP_MARGIN;
	start_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN;
	y = start_y - MINIMAP_BORDER_SIZE;
	while (y < start_y + MINIMAP_SIZE + MINIMAP_BORDER_SIZE)
	{
		x = start_x - MINIMAP_BORDER_SIZE;
		while (x < start_x + MINIMAP_SIZE + MINIMAP_BORDER_SIZE)
		{
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
			{
				dx = 0;
				dy = 0;
				if (x < start_x)
					dx = start_x - x;
				else if (x >= start_x + MINIMAP_SIZE)
					dx = x - (start_x + MINIMAP_SIZE - 1);
				if (y < start_y)
					dy = start_y - y;
				else if (y >= start_y + MINIMAP_SIZE)
					dy = y - (start_y + MINIMAP_SIZE - 1);
				if (dx * dx + dy * dy <= MINIMAP_BORDER_SIZE
					* MINIMAP_BORDER_SIZE)
					put_pixel(game, x, y, COLOR_MINIMAP_BORDER);
			}
			x++;
		}
		y++;
	}
	y = start_y;
	while (y < start_y + MINIMAP_SIZE)
	{
		x = start_x;
		while (x < start_x + MINIMAP_SIZE)
		{
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
				put_pixel(game, x, y, COLOR_MINIMAP_BG);
			x++;
		}
		y++;
	}
}

static void	draw_smooth_tile(t_data *game, int screen_x, int screen_y,
		int color)
{
	int	y;
	int	x;
	int	pixel_x;
	int	pixel_y;

	y = 0;
	while (y < MINIMAP_TILE_SIZE)
	{
		x = 0;
		while (x < MINIMAP_TILE_SIZE)
		{
			pixel_x = screen_x + x;
			pixel_y = screen_y + y;
			if (pixel_x >= MINIMAP_MARGIN && pixel_x < MINIMAP_MARGIN
				+ MINIMAP_SIZE && pixel_y >= WINDOW_HEIGHT - MINIMAP_SIZE
				- MINIMAP_MARGIN && pixel_y < WINDOW_HEIGHT - MINIMAP_MARGIN)
			{
				if (color == COLOR_WALL)
				{
					if (x == 0 || y == 0 || x == MINIMAP_TILE_SIZE - 1
						|| y == MINIMAP_TILE_SIZE - 1)
						put_pixel(game, pixel_x, pixel_y, color - 0x101010);
					else
						put_pixel(game, pixel_x, pixel_y, color);
				}
				else
				{
					put_pixel(game, pixel_x, pixel_y, color);
				}
			}
			x++;
		}
		y++;
	}
}

static void	render_precise_tiles(t_data *game)
{
	double	player_map_x;
	double	player_map_y;
	int		tiles_per_row;
	int		center_tile_x;
	int		center_tile_y;
	int		minimap_y;
	int		minimap_x;
	int		map_x;
	int		map_y;
	int		screen_x;
	int		screen_y;
	char	tile;
	int		color;

	player_map_x = game->player.pos[0] / TILESIZE;
	player_map_y = game->player.pos[1] / TILESIZE;
	tiles_per_row = MINIMAP_SIZE / MINIMAP_TILE_SIZE;
	center_tile_x = tiles_per_row / 2;
	center_tile_y = tiles_per_row / 2;
	minimap_y = 0;
	while (minimap_y < tiles_per_row)
	{
		minimap_x = 0;
		while (minimap_x < tiles_per_row)
		{
			map_x = (int)player_map_x + (minimap_x - center_tile_x);
			map_y = (int)player_map_y + (minimap_y - center_tile_y);
			screen_x = MINIMAP_MARGIN + minimap_x * MINIMAP_TILE_SIZE;
			screen_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + minimap_y
				* MINIMAP_TILE_SIZE;
			if (map_y >= 0 && map_y < game->map_height)
			{
				if (map_x >= 0 && map_x < (int)ft_strlen(game->map[map_y]))
				{
					tile = game->map[map_y][map_x];
					color = get_modern_tile_color(tile);
					draw_smooth_tile(game, screen_x, screen_y, color);
				}
				else
					draw_smooth_tile(game, screen_x, screen_y, COLOR_VOID);
			}
			else
				draw_smooth_tile(game, screen_x, screen_y, COLOR_VOID);
			minimap_x++;
		}
		minimap_y++;
	}
}
static void	draw_fov_lines(t_data *game, int center_x, int center_y)
{
	double	player_angle;
	double	fov_angle;
	int		fov_length;
	int		i;
	double	angle;
	t_point	begin;
	t_point	end;

	player_angle = atan2(game->player.dir[1], game->player.dir[0]);
	fov_angle = M_PI / 3.0;
	fov_length = MINIMAP_TILE_SIZE * 3;
	i = -1;
	while (i <= 1)
	{
		angle = player_angle + (fov_angle / 2.0) * i;
		begin.x = center_x;
		begin.y = center_y;
		end.x = center_x + (int)(cos(angle) * fov_length);
		end.y = center_y + (int)(sin(angle) * fov_length);
		draw_line(game, begin, end, COLOR_FOV_LINE);
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
	int	center_x;
	int	center_y;

	center_x = MINIMAP_MARGIN + MINIMAP_SIZE / 2;
	center_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + MINIMAP_SIZE / 2;
	draw_fov_lines(game, center_x, center_y);
	draw_circle(game, center_x, center_y, MINIMAP_PLAYER_SIZE / 2 + 1,
		0x000000);
	draw_circle(game, center_x, center_y, MINIMAP_PLAYER_SIZE / 2,
		COLOR_PLAYER);
	draw_player_direction(game, center_x, center_y);
}

void	render_minimap(t_data *game)
{
	draw_modern_minimap_background(game);
	render_precise_tiles(game);
	draw_modern_player(game);
}
