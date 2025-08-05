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

// int	handle_input(int key, t_data *game)
// {
// 	if (key == 65307)
// 		close_game(game);
// 	if (key == MOVE_UP || key == ARROW_UP)
// 		update(game);
// 	if (key == MOVE_LEFT || key == ARROW_LEFT)
// 		update(game);
// 	if (key == MOVE_RIGHT || key == ARROW_RIGHT)
// 		update(game);
// 	if (key == MOVE_DOWN || key == ARROW_DOWN)
// 		update(game);
// 	return (0);
// }
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
    // Réinitialiser les directions
    game->player.turnDirection = 0;
    game->player.walkDirection = 0;
    
    // Lire l'état des touches simultanément
    if (game->keys[MOVE_UP] || game->keys[ARROW_UP])
        game->player.walkDirection = 1;
    if (game->keys[MOVE_DOWN] || game->keys[ARROW_DOWN])
        game->player.walkDirection = -1;
    if (game->keys[MOVE_LEFT] || game->keys[ARROW_LEFT])
        game->player.turnDirection = -1;
    if (game->keys[MOVE_RIGHT] || game->keys[ARROW_RIGHT])
        game->player.turnDirection = 1;
    
    // Appliquer les mouvements
    if (game->player.turnDirection != 0 || game->player.walkDirection != 0)
        update(game);
    
    render_map(game);
    usleep(10);
    return (0);
}
