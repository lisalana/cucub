/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:31:05 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/25 13:47:59 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int get_modern_tile_color(char tile)
{
    switch (tile)
    {
        case '1': return COLOR_WALL;
        case '0': return COLOR_FLOOR;
        case ' ': return COLOR_VOID;
        default:  return COLOR_VOID;
    }
}

static void draw_circle(t_data *game, int center_x, int center_y, int radius, int color)
{
    int x, y = -radius;

    while (y <= radius)
    {
        x = -radius;
        while (x <= radius)
        {
            if (x * x + y * y <= radius * radius)
            {
                int pixel_x = center_x + x;
                int pixel_y = center_y + y;

                if (pixel_x >= MINIMAP_MARGIN && pixel_x < MINIMAP_MARGIN + MINIMAP_SIZE &&
                    pixel_y >= WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN &&
                    pixel_y < WINDOW_HEIGHT - MINIMAP_MARGIN)
                {
                    put_pixel(game, pixel_x, pixel_y, color);
                }
            }
            x++;
        }
        y++;
    }
}

static void draw_modern_minimap_background(t_data *game)
{
    int start_x = MINIMAP_MARGIN;
    int start_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN;
    int y = start_y - MINIMAP_BORDER_SIZE;

    while (y < start_y + MINIMAP_SIZE + MINIMAP_BORDER_SIZE)
    {
        int x = start_x - MINIMAP_BORDER_SIZE;
        while (x < start_x + MINIMAP_SIZE + MINIMAP_BORDER_SIZE)
        {
            if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
            {
                int dx = 0;
                int dy = 0;

                if (x < start_x)
                    dx = start_x - x;
                else if (x >= start_x + MINIMAP_SIZE)
                    dx = x - (start_x + MINIMAP_SIZE - 1);

                if (y < start_y)
                    dy = start_y - y;
                else if (y >= start_y + MINIMAP_SIZE)
                    dy = y - (start_y + MINIMAP_SIZE - 1);

                if (dx * dx + dy * dy <= MINIMAP_BORDER_SIZE * MINIMAP_BORDER_SIZE)
                    put_pixel(game, x, y, COLOR_MINIMAP_BORDER);
            }
            x++;
        }
        y++;
    }

    y = start_y;
    while (y < start_y + MINIMAP_SIZE)
    {
        int x = start_x;
        while (x < start_x + MINIMAP_SIZE)
        {
            if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
                put_pixel(game, x, y, COLOR_MINIMAP_BG);
            x++;
        }
        y++;
    }
}

static void draw_smooth_tile(t_data *game, int screen_x, int screen_y, int color)
{
    int y = 0;
    while (y < MINIMAP_TILE_SIZE)
    {
        int x = 0;
        while (x < MINIMAP_TILE_SIZE)
        {
            int pixel_x = screen_x + x;
            int pixel_y = screen_y + y;

            if (pixel_x >= MINIMAP_MARGIN && pixel_x < MINIMAP_MARGIN + MINIMAP_SIZE &&
                pixel_y >= WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN &&
                pixel_y < WINDOW_HEIGHT - MINIMAP_MARGIN)
            {
                if (color == COLOR_WALL)
                {
                    if (x == 0 || y == 0 || x == MINIMAP_TILE_SIZE - 1 || y == MINIMAP_TILE_SIZE - 1)
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

static void render_precise_tiles(t_data *game)
{
    double player_map_x = game->player.pos[0] / TILESIZE;
    double player_map_y = game->player.pos[1] / TILESIZE;

    int tiles_per_row = MINIMAP_SIZE / MINIMAP_TILE_SIZE;
    int center_tile_x = tiles_per_row / 2;
    int center_tile_y = tiles_per_row / 2;

    int minimap_y = 0;
    while (minimap_y < tiles_per_row)
    {
        int minimap_x = 0;
        while (minimap_x < tiles_per_row)
        {
            int map_x = (int)player_map_x + (minimap_x - center_tile_x);
            int map_y = (int)player_map_y + (minimap_y - center_tile_y);

            int screen_x = MINIMAP_MARGIN + minimap_x * MINIMAP_TILE_SIZE;
            int screen_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + minimap_y * MINIMAP_TILE_SIZE;

            if (map_x >= 0 && map_x < game->map_width &&
                map_y >= 0 && map_y < game->map_height)
            {
                if (map_x < (int)ft_strlen(game->map[map_y]))
                {
                    char tile = game->map[map_y][map_x];
                    int color = get_modern_tile_color(tile);
                    draw_smooth_tile(game, screen_x, screen_y, color);
                }
                else
                {
                    draw_smooth_tile(game, screen_x, screen_y, COLOR_VOID);
                }
            }
            else
            {
                draw_smooth_tile(game, screen_x, screen_y, COLOR_VOID);
            }

            minimap_x++;
        }
        minimap_y++;
    }
}

static void draw_modern_player(t_data *game)
{
    int center_x = MINIMAP_MARGIN + MINIMAP_SIZE / 2;
    int center_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + MINIMAP_SIZE / 2;

    // Dessiner le champ de vision (FOV) en premier
    double fov_angle = M_PI / 3.0; // 60 degrés
    double player_angle = atan2(game->player.dir[1], game->player.dir[0]);
    int fov_length = MINIMAP_TILE_SIZE * 3;

    // Lignes du FOV
    int i = -1;
    while (i <= 1)
    {
        double angle = player_angle + (fov_angle / 2.0) * i;
        int end_x = center_x + (int)(cos(angle) * fov_length);
        int end_y = center_y + (int)(sin(angle) * fov_length);
        draw_line(game, center_x, center_y, end_x, end_y, COLOR_FOV_LINE);
        i += 2;
    }

    // Cercle extérieur du joueur (contour)
    draw_circle(game, center_x, center_y, MINIMAP_PLAYER_SIZE / 2 + 1, 0x000000);

    // Cercle principal du joueur
    draw_circle(game, center_x, center_y, MINIMAP_PLAYER_SIZE / 2, COLOR_PLAYER);

    // Direction du joueur (ligne plus épaisse)
    double dir_length = MINIMAP_PLAYER_SIZE * 1.8;
    int end_x = center_x + (int)(game->player.dir[0] * dir_length);
    int end_y = center_y + (int)(game->player.dir[1] * dir_length);

    draw_line(game, center_x, center_y, end_x, end_y, COLOR_DIRECTION);
    draw_line(game, center_x + 1, center_y, end_x + 1, end_y, COLOR_DIRECTION);
    draw_line(game, center_x, center_y + 1, end_x, end_y + 1, COLOR_DIRECTION);
}


// ===== FONCTION PRINCIPALE =====
void render_minimap(t_data *game)
{
    draw_modern_minimap_background(game);
    render_precise_tiles(game);
    draw_modern_player(game);
}