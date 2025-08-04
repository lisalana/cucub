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

// static void	draw_minimap_inner_background(t_data *game, int start_x,
// 		int start_y)
// {
// 	int x, y;
// 	y = start_y;
// 	while (y < start_y + MINIMAP_SIZE)
// 	{
// 		x = start_x;
// 		while (x < start_x + MINIMAP_SIZE)
// 		{
// 			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
// 				put_pixel(game, x, y, 0x404040);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// static void	draw_minimap_background(t_data *game)
// {
// 	int	start_x;
// 	int	start_y;

// 	int x, y;
// 	start_x = MINIMAP_MARGIN;
// 	start_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN;
// 	y = start_y - 2;
// 	while (y < start_y + MINIMAP_SIZE + 2)
// 	{
// 		x = start_x - 2;
// 		while (x < start_x + MINIMAP_SIZE + 2)
// 		{
// 			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
// 				put_pixel(game, x, y, 0x000000);
// 			x++;
// 		}
// 		y++;
// 	}
// 	draw_minimap_inner_background(game, start_x, start_y);
// }

// static void	draw_minimap_tile(t_data *game, int screen_x, int screen_y,
// 		int color)
// {
// 	int	pixel_x;
// 	int	pixel_y;

// 	int x, y;
// 	y = 0;
// 	while (y < MINIMAP_TILE_SIZE)
// 	{
// 		x = 0;
// 		while (x < MINIMAP_TILE_SIZE)
// 		{
// 			pixel_x = screen_x + x;
// 			pixel_y = screen_y + y;
// 			if (pixel_x >= MINIMAP_MARGIN && pixel_x < MINIMAP_MARGIN
// 				+ MINIMAP_SIZE && pixel_y >= WINDOW_HEIGHT - MINIMAP_SIZE
// 				- MINIMAP_MARGIN && pixel_y < WINDOW_HEIGHT - MINIMAP_MARGIN)
// 			{
// 				put_pixel(game, pixel_x, pixel_y, color);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

// static void	draw_player_square(t_data *game, int center_x, int center_y)
// {
// 	int	pixel_x;
// 	int	pixel_y;

// 	int x, y;
// 	y = -MINIMAP_PLAYER_SIZE / 2;
// 	while (y <= MINIMAP_PLAYER_SIZE / 2)
// 	{
// 		x = -MINIMAP_PLAYER_SIZE / 2;
// 		while (x <= MINIMAP_PLAYER_SIZE / 2)
// 		{
// 			pixel_x = center_x + x;
// 			pixel_y = center_y + y;
// 			if (pixel_x >= MINIMAP_MARGIN && pixel_x < MINIMAP_MARGIN
// 				+ MINIMAP_SIZE && pixel_y >= WINDOW_HEIGHT - MINIMAP_SIZE
// 				- MINIMAP_MARGIN && pixel_y < WINDOW_HEIGHT - MINIMAP_MARGIN)
// 			{
// 				put_pixel(game, pixel_x, pixel_y, 0xFF0000);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

// static void	draw_minimap_player(t_data *game)
// {
// 	int		center_x;
// 	int		center_y;
// 	double	dir_length;
// 	int		end_x;
// 	int		end_y;

// 	center_x = MINIMAP_MARGIN + MINIMAP_SIZE / 2;
// 	center_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + MINIMAP_SIZE / 2;
// 	draw_player_square(game, center_x, center_y);
// 	dir_length = MINIMAP_TILE_SIZE * 1.5;
// 	end_x = center_x + (int)(game->player.dir[0] * dir_length);
// 	end_y = center_y + (int)(game->player.dir[1] * dir_length);
// 	draw_line(game, center_x, center_y, end_x, end_y, 0xFF4444);
// }

// static int	get_tile_color(char tile)
// {
// 	int	color;

// 	if (tile == '1')
// 		color = 0x808080;
// 	else if (tile == '0')
// 		color = 0xE0E0E0;
// 	else if (tile == ' ')
// 		color = 0x404040;
// 	else
// 		color = 0x604040;
// 	return (color);
// }

// static void	process_minimap_tile(t_data *game, double player_map_y,
// 		int minimap_center_y, int minimap_x, int minimap_y, int map_x)
// {
// 	int		map_y;
// 	int		screen_x;
// 	int		screen_y;
// 	char	tile;
// 	int		color;

// 	map_y = (int)player_map_y + (minimap_y - minimap_center_y);
// 	screen_x = MINIMAP_MARGIN + minimap_x * MINIMAP_TILE_SIZE;
// 	screen_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + minimap_y
// 		* MINIMAP_TILE_SIZE;
// 	if (map_x >= 0 && map_x < game->map_width && map_y >= 0
// 		&& map_y < game->map_height)
// 	{
// 		if (map_x < (int)ft_strlen(game->map[map_y]))
// 		{
// 			tile = game->map[map_y][map_x];
// 			color = get_tile_color(tile);
// 			draw_minimap_tile(game, screen_x, screen_y, color);
// 		}
// 	}
// }

// static void	render_minimap_tiles(t_data *game, double player_map_x,
// 		double player_map_y)
// {
// 	int	minimap_center_x;
// 	int	minimap_center_y;
// 	int	minimap_x;
// 	int	minimap_y;
// 	int	map_x;

// 	minimap_center_x = MINIMAP_SIZE / 2 / MINIMAP_TILE_SIZE;
// 	minimap_center_y = MINIMAP_SIZE / 2 / MINIMAP_TILE_SIZE;
// 	minimap_y = 0;
// 	while (minimap_y < MINIMAP_SIZE / MINIMAP_TILE_SIZE)
// 	{
// 		minimap_x = 0;
// 		while (minimap_x < MINIMAP_SIZE / MINIMAP_TILE_SIZE)
// 		{
// 			map_x = (int)player_map_x + (minimap_x - minimap_center_x);
// 			process_minimap_tile(game, player_map_y, minimap_center_y,
// 				minimap_x, minimap_y, map_x);
// 			minimap_x++;
// 		}
// 		minimap_y++;
// 	}
// }

// void	render_minimap(t_data *game)
// {
// 	double player_map_x;
// 	double player_map_y;

// 	player_map_x = game->player.pos[0] / TILESIZE;
// 	player_map_y = game->player.pos[1] / TILESIZE;
// 	draw_minimap_background(game);
// 	render_minimap_tiles(game, player_map_x, player_map_y);
// 	draw_minimap_player(game);
// }


// ===== FONCTION POUR DESSINER UN CERCLE (JOUEUR ROND) =====
static void draw_circle(t_data *game, int center_x, int center_y, int radius, int color)
{
    int x, y;
    
    for (y = -radius; y <= radius; y++)
    {
        for (x = -radius; x <= radius; x++)
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
        }
    }
}

// ===== FOND AVEC EFFET DE TRANSPARENCE =====
static void draw_modern_minimap_background(t_data *game)
{
    int start_x = MINIMAP_MARGIN;
    int start_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN;
    
    // Bordure extérieure avec coins arrondis (simulés)
    for (int y = start_y - MINIMAP_BORDER_SIZE; y < start_y + MINIMAP_SIZE + MINIMAP_BORDER_SIZE; y++)
    {
        for (int x = start_x - MINIMAP_BORDER_SIZE; x < start_x + MINIMAP_SIZE + MINIMAP_BORDER_SIZE; x++)
        {
            if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
            {
                // Coins arrondis
                int dx = (x < start_x) ? start_x - x : (x >= start_x + MINIMAP_SIZE) ? x - (start_x + MINIMAP_SIZE - 1) : 0;
                int dy = (y < start_y) ? start_y - y : (y >= start_y + MINIMAP_SIZE) ? y - (start_y + MINIMAP_SIZE - 1) : 0;
                
                if (dx * dx + dy * dy <= MINIMAP_BORDER_SIZE * MINIMAP_BORDER_SIZE)
                    put_pixel(game, x, y, COLOR_MINIMAP_BORDER);
            }
        }
    }
    
    // Fond intérieur
    for (int y = start_y; y < start_y + MINIMAP_SIZE; y++)
    {
        for (int x = start_x; x < start_x + MINIMAP_SIZE; x++)
        {
            if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
                put_pixel(game, x, y, COLOR_MINIMAP_BG);
        }
    }
}

// ===== TILES AVEC ANTI-ALIASING SIMPLE =====
static void draw_smooth_tile(t_data *game, int screen_x, int screen_y, int color)
{
    for (int y = 0; y < MINIMAP_TILE_SIZE; y++)
    {
        for (int x = 0; x < MINIMAP_TILE_SIZE; x++)
        {
            int pixel_x = screen_x + x;
            int pixel_y = screen_y + y;
            
            if (pixel_x >= MINIMAP_MARGIN && pixel_x < MINIMAP_MARGIN + MINIMAP_SIZE &&
                pixel_y >= WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN && 
                pixel_y < WINDOW_HEIGHT - MINIMAP_MARGIN)
            {
                // Bordures plus douces pour les murs
                if (color == COLOR_WALL)
                {
                    // Créer un effet de dégradé sur les bords
                    if (x == 0 || y == 0 || x == MINIMAP_TILE_SIZE - 1 || y == MINIMAP_TILE_SIZE - 1)
                        put_pixel(game, pixel_x, pixel_y, color - 0x101010); // Légèrement plus sombre
                    else
                        put_pixel(game, pixel_x, pixel_y, color);
                }
                else
                {
                    put_pixel(game, pixel_x, pixel_y, color);
                }
            }
        }
    }
}

static int get_modern_tile_color(char tile)
{
    switch (tile)
    {
        case '1': return COLOR_WALL;
        case '0': return COLOR_FLOOR;
        case ' ': return COLOR_VOID;
        case 'D': return 0x8B4513;  // Marron pour les portes
        default:  return COLOR_VOID;
    }
}

// ===== JOUEUR AVEC DIRECTION ET CHAMP DE VISION =====
static void draw_modern_player(t_data *game)
{
    int center_x = MINIMAP_MARGIN + MINIMAP_SIZE / 2;
    int center_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + MINIMAP_SIZE / 2;
    
    // Dessiner le champ de vision (FOV) en premier
    double fov_angle = M_PI / 3.0; // 60 degrés
    double player_angle = atan2(game->player.dir[1], game->player.dir[0]);
    int fov_length = MINIMAP_TILE_SIZE * 3;
    
    // Lignes du FOV
    for (int i = -1; i <= 1; i += 2) // -1 pour gauche, +1 pour droite
    {
        double angle = player_angle + (fov_angle / 2.0) * i;
        int end_x = center_x + (int)(cos(angle) * fov_length);
        int end_y = center_y + (int)(sin(angle) * fov_length);
        draw_line(game, center_x, center_y, end_x, end_y, COLOR_FOV_LINE);
    }
    
    // Cercle extérieur du joueur (contour)
    draw_circle(game, center_x, center_y, MINIMAP_PLAYER_SIZE / 2 + 1, 0x000000);
    
    // Cercle principal du joueur
    draw_circle(game, center_x, center_y, MINIMAP_PLAYER_SIZE / 2, COLOR_PLAYER);
    
    // Direction du joueur (ligne plus épaisse)
    double dir_length = MINIMAP_PLAYER_SIZE * 1.8;
    int end_x = center_x + (int)(game->player.dir[0] * dir_length);
    int end_y = center_y + (int)(game->player.dir[1] * dir_length);
    
    // Ligne de direction avec épaisseur
    draw_line(game, center_x, center_y, end_x, end_y, COLOR_DIRECTION);
    draw_line(game, center_x + 1, center_y, end_x + 1, end_y, COLOR_DIRECTION);
    draw_line(game, center_x, center_y + 1, end_x, end_y + 1, COLOR_DIRECTION);
}

// ===== POSITION PRÉCISE DU JOUEUR =====
static void render_precise_tiles(t_data *game)
{
    // Position précise du joueur
    double player_map_x = game->player.pos[0] / TILESIZE;
    double player_map_y = game->player.pos[1] / TILESIZE;
    
    // Centre de la minimap en tiles
    int tiles_per_row = MINIMAP_SIZE / MINIMAP_TILE_SIZE;
    int center_tile_x = tiles_per_row / 2;
    int center_tile_y = tiles_per_row / 2;
    
    // Rendu des tiles avec position précise
    for (int minimap_y = 0; minimap_y < tiles_per_row; minimap_y++)
    {
        for (int minimap_x = 0; minimap_x < tiles_per_row; minimap_x++)
        {
            // Calcul de la position réelle dans la map
            int map_x = (int)player_map_x + (minimap_x - center_tile_x);
            int map_y = (int)player_map_y + (minimap_y - center_tile_y);
            
            // Position à l'écran
            int screen_x = MINIMAP_MARGIN + minimap_x * MINIMAP_TILE_SIZE;
            int screen_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + minimap_y * MINIMAP_TILE_SIZE;
            
            // Vérifier les limites de la map
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
        }
    }
}

// ===== FONCTION PRINCIPALE =====
void render_minimap(t_data *game)
{
    draw_modern_minimap_background(game);
    render_precise_tiles(game);
    draw_modern_player(game);
}