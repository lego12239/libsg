#include "libsg/sg.h"

void
main()
{
	sg_create_window(200, 400);

	sg_set_color(SG_COLOR_RED);
	sg_draw_line(10, 10, 100, 200);

	sg_wait_escape();
	sg_destroy_window();
}
