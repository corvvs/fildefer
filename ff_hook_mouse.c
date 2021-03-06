#include "fdf.h"

#ifdef MLX_MMS
static int	screen_y(t_master *m, int y)
{
	return (m->window_height - 1 - y);
}

#else

static int	screen_y(t_master *m, int y)
{
	(void)m;
	return (y);
}
#endif

int	hook_mouse_down(int button, int x, int y, t_master *m)
{
	t_vector	v;

	if (button == MOUSE_BUTTON_1 && !m->dragging)
	{
		m->dragging = 1;
		m->do_x = x;
		m->do_y = y;
		return (0);
	}
	if (!m->tr_changed
		&& (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN))
	{
		y = screen_y(m, y);
		v = (t_vector){x, y, 0};
		if (button == MOUSE_SCROLL_UP)
			ff_zoom_camera(m, v.x, v.y, 0.9);
		else
			ff_zoom_camera(m, v.x, v.y, 1.1);
		m->tr_changed = 1;
		return (0);
	}
	return (0);
}

int	hook_mouse_up(int button, int x, int y, t_master *m)
{
	(void)x;
	(void)y;
	if (button == MOUSE_BUTTON_1)
	{
		m->dragging = 0;
		return (0);
	}
	return (0);
}

int	hook_motion(int x, int y, t_master *m)
{
	if (m->dragging && !m->tr_changed)
	{
		ff_pan_camera(m, x - m->do_x, y - m->do_y);
		m->do_x = x;
		m->do_y = y;
		m->tr_changed = 1;
		return (0);
	}
	return (0);
}
