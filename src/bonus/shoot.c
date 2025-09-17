#include "../../include/cub3d.h"

static int	sprite_at_cell(t_cub *c, int mx, int my)
{
	int	i;
	int	sx;
	int	sy;

	i = 0;
	while (i < c->sprites.count)
	{
		if (c->sprites.sprites[i].frame_count > 0)
		{
			sx = (int)c->sprites.sprites[i].pos.x;
			sy = (int)c->sprites.sprites[i].pos.y;
			if (sx == mx && sy == my)
				return (i);
		}
		i++;
	}
	return (-1);
}

static void	ray_setup(t_cub *c, t_ray *r)
{
	r->dir.x = c->player.dir.x;
	r->dir.y = c->player.dir.y;
	if (fabs(r->dir.x) < EPS)
		r->dir.x = (r->dir.x < 0) ? -EPS : EPS;
	if (fabs(r->dir.y) < EPS)
		r->dir.y = (r->dir.y < 0) ? -EPS : EPS;
	r->map_x = (int)c->player.pos.x;
	r->map_y = (int)c->player.pos.y;
	r->delta.x = fabs(1.0 / r->dir.x);
	r->delta.y = fabs(1.0 / r->dir.y);
	if (r->dir.x < 0)
	{
		r->step_x = -1;
		r->side.x = (c->player.pos.x - r->map_x) * r->delta.x;
	}
	else
	{
		r->step_x = 1;
		r->side.x = (r->map_x + 1.0 - c->player.pos.x) * r->delta.x;
	}
	if (r->dir.y < 0)
	{
		r->step_y = -1;
		r->side.y = (c->player.pos.y - r->map_y) * r->delta.y;
	}
	else
	{
		r->step_y = 1;
		r->side.y = (r->map_y + 1.0 - c->player.pos.y) * r->delta.y;
	}
}

static int	step_and_check_hit(t_cub *c, t_ray *r)
{
	int	mx;
	int	my;
	int	idx;

	if (r->side.x < r->side.y)
	{
		r->side.x += r->delta.x;
		r->map_x += r->step_x;
	}
	else
	{
		r->side.y += r->delta.y;
		r->map_y += r->step_y;
	}
	mx = r->map_x;
	my = r->map_y;
	if (mx < 0 || my < 0 || mx >= c->map.w || my >= c->map.h)
		return (1);
	idx = sprite_at_cell(c, mx, my);
	if (idx >= 0)
	{
		c->sprites.sprites[idx].frame_count = 0;
		return (1);
	}
	if (c->map.grid[my][mx] == '1' || c->map.grid[my][mx] == 'D')
		return (1);
	return (0);
}

void	shoot_try(t_cub *c)
{
	t_ray	r;
	int		stop;

	ray_setup(c, &r);
	stop = 0;
	while (!stop)
	{
		stop = step_and_check_hit(c, &r);
	}
}
