/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:30:05 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/29 12:03:27 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

 // Marquer la touche comme pressée
int key_press(int key, t_data *game)
{
	if (key == 65307)  // Échap
        close_game(game);

    if (key >= 0 && key < 65536)
        game->keys[key] = 1;
    return (0);
}
 // Marquer la touche comme relâchée
int key_release(int key, t_data *game)
{
    if (key >= 0 && key < 65536)
        game->keys[key] = 0;
    return (0);
}

int	close_game(t_data *game)
{
	// free_textures(game);
	mlx_loop_end(game->mlx);
	return (0);
}


int main_loop(t_data *game)
{
    static bool at_start = true;
    bool moved;
    double oldX;
    double oldY;

    game->player.turnDirection = 0;
    game->player.walkDirection = 0;
    if (game->keys[MOVE_UP]    || game->keys[ARROW_UP])    game->player.walkDirection =  1;
    if (game->keys[MOVE_DOWN]  || game->keys[ARROW_DOWN])  game->player.walkDirection = -1;
    if (game->keys[MOVE_LEFT]  || game->keys[ARROW_LEFT])  game->player.turnDirection  = -1;
    if (game->keys[MOVE_RIGHT] || game->keys[ARROW_RIGHT]) game->player.turnDirection  =  1;
    
    oldX = game->player.pos[0];
    oldY = game->player.pos[1];

    if (game->player.turnDirection != 0 || game->player.walkDirection != 0)
        update(game);
    moved = (fabs(game->player.pos[0] - oldX) > 1e-6)
              || (fabs(game->player.pos[1] - oldY) > 1e-6);

    if (!moved)
    {
        if (at_start)
        {
            game->player.pos[0] = oldX - game->player.dir[0] * (TILESIZE * 0.1);
            game->player.pos[1] = oldY - game->player.dir[1] * (TILESIZE * 0.1);

            at_start = false;
        }
        else
        {
            if (game->player.walkDirection ==  1)
                game->keys[MOVE_UP] = game->keys[ARROW_UP] = 0;
            if (game->player.walkDirection == -1)
                game->keys[MOVE_DOWN] = game->keys[ARROW_DOWN] = 0;
            if (game->player.turnDirection == -1)
                game->keys[MOVE_LEFT] = game->keys[ARROW_LEFT] = 0;
            if (game->player.turnDirection ==  1)
                game->keys[MOVE_RIGHT] = game->keys[ARROW_RIGHT] = 0;
        }
    }
    render_map(game);
    usleep(1000);
    return (0);
}
