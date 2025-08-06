/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:27:03 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/23 14:12:35 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_data *game)
{
    game->player.pos[0] = game->player.pos[0] * TILESIZE + TILESIZE / 2;
    game->player.pos[1] = game->player.pos[1] * TILESIZE + TILESIZE / 2;
    
    if (game->player.direction == 'N')
    {
        game->player.dir[0] = 0.0;
        game->player.dir[1] = -1.0;
    }
    else if (game->player.direction == 'S')
    {
        game->player.dir[0] = 0.0;
        game->player.dir[1] = 1.0;
    }
    else if (game->player.direction == 'E')
    {
        game->player.dir[0] = 1.0;
        game->player.dir[1] = 0.0;
    }
    else if (game->player.direction == 'W')
    {
        game->player.dir[0] = -1.0;
        game->player.dir[1] = 0.0;
    }
    game->player.plane[0] = -game->player.dir[1] * 0.66;
    game->player.plane[1] = game->player.dir[0] * 0.66;
    game->player.turnDirection = 0;
    game->player.walkDirection = 0;
    game->player.moveSpeed = 0.5; //4.0;
    game->player.rotationSpeed = 0.5; //0.1;
}

void rotate_player(t_data *game, double angle)
{
    double old_dir_x;
    double old_plane_x;
    double cos_angle;
    double sin_angle;
    
    old_dir_x = game->player.dir[0];
    old_plane_x = game->player.plane[0];
    cos_angle = cos(angle);
    sin_angle = sin(angle);
    
    game->player.dir[0] = old_dir_x * cos_angle - game->player.dir[1] * sin_angle;
    game->player.dir[1] = old_dir_x * sin_angle + game->player.dir[1] * cos_angle;
    
    game->player.plane[0] = old_plane_x * cos_angle - game->player.plane[1] * sin_angle;
    game->player.plane[1] = old_plane_x * sin_angle + game->player.plane[1] * cos_angle;
}

void update(t_data *game)
{
    double moveStep;
    double newX;
    double newY;
    int mapX;
    int mapY;
    double rotation_angle;
    
    // Rotation
    if (game->player.turnDirection != 0)
    {
        rotation_angle = game->player.turnDirection * 0.02;
        rotate_player(game, rotation_angle);
    }
    // Mouvement
    if (game->player.walkDirection != 0)
    {
        moveStep = game->player.walkDirection * game->player.moveSpeed;
        newX = game->player.pos[0] + game->player.dir[0] * moveStep;
        newY = game->player.pos[1] + game->player.dir[1] * moveStep;
        mapX = (int)(newX / TILESIZE);
        mapY = (int)(newY / TILESIZE);
        
        if (!has_wall_at(game, mapX, mapY))
        {
            game->player.pos[0] = newX;
            game->player.pos[1] = newY;
        }
    }
}

