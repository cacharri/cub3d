/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:43:10 by dabel-co          #+#    #+#             */
/*   Updated: 2024/01/16 15:37:47 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_input(int x, int y, t_game *g)
{
	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		if (x < g->player.mouse)
			g->player.angle -= PLAYER_ROTATE;
		if (x > g->player.mouse)
			g->player.angle += PLAYER_ROTATE;
	}
	g->player.mouse = x;
	return (0);
}

int	key_pressed(int key, t_game *g)
{
	if (key == KEY_ESC || key == 17)
		close_game(g);
	if (key == KEY_W)
		g->player.key.w = 1;
	else if (key == KEY_A)
		g->player.key.a = 1;
	else if (key == KEY_S)
		g->player.key.s = 1;
	else if (key == KEY_D)
		g->player.key.d = 1;
	else if (key == KEY_LEFT)
		g->player.key.left = 1;
	else if (key == KEY_RIGHT)
		g->player.key.right = 1;
	return (0);
}

int	key_released(int key, t_game *g)
{
	if (key == KEY_W)
		g->player.key.w = 0;
	else if (key == KEY_A)
		g->player.key.a = 0;
	else if (key == KEY_S)
		g->player.key.s = 0;
	else if (key == KEY_D)
		g->player.key.d = 0;
	else if (key == KEY_LEFT)
		g->player.key.left = 0;
	else if (key == KEY_RIGHT)
		g->player.key.right = 0;
	return (0);
}

static void	move_player(t_game *g, int dir, float angle)
{
	float	new_pos_x;
	float	new_pos_y;
	float	check_pos_x;
	float	check_pos_y;

	g->player.step_x = dir * (cos(angle) * PLAYER_SPEED);
	g->player.step_y = dir * (sin(angle) * PLAYER_SPEED);
	new_pos_x = g->player.x + g->player.step_x;
	new_pos_y = g->player.y + g->player.step_y;
	check_pos_x = g->player.x + 0.5 + (5 * g->player.step_x);
	check_pos_y = g->player.y + 0.5 + (5 * g->player.step_y);
	if (g->map[(int)check_pos_y][(int)(g->player.x + 0.5)] != '1')
		g->player.y = new_pos_y;
	if (g->map[(int)(g->player.y + 0.5)][(int)check_pos_x] != '1')
		g->player.x = new_pos_x;
}

void	check_movement(t_game *g)
{
	if (g->player.key.w)
		move_player(g, 1, g->player.angle);
	if (g->player.key.s)
		move_player(g, -1, g->player.angle);
	if (g->player.key.a)
		move_player(g, -1, g->player.angle + DEGREES_90);
	if (g->player.key.d)
		move_player(g, 1, g->player.angle + DEGREES_90);
	if (g->player.key.left)
		g->player.angle -= PLAYER_ROTATE;
	if (g->player.key.right)
		g->player.angle += PLAYER_ROTATE;
}
