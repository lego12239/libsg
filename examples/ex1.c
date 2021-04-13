#include <sg.h>

int
main()
{
	sg_create_window(1024, 768);
	sg_set_color(SG_COLOR_RED);
	sg_draw_point(100, 100);
	
	sg_set_color(SG_COLOR_GREEN);
	sg_draw_line(110, 110, 210, 110);
	
	sg_set_color(SG_COLOR_BLUE);
	sg_draw_circle(400, 400, 50);
	sg_draw_ellipse(400, 400, 200, 50);
	
	sg_set_color(SG_COLOR_YELLOW);
	sg_draw_filledellipse(200, 100, 40, 60);

	sg_set_color(SG_COLOR_CYAN);
	sg_draw_filledrect(500, 100, 200, 200);

	sg_wait_escape();
	sg_destroy_window();
}
