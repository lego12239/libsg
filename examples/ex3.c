#include <sg.h>

void
main()
{
	sg_create_window(1024, 768);
	sg_set_color(SG_COLOR_CYAN);
	sg_draw_text("arial.ttf", 16, 100, 100, "Привет!");

	sg_set_color(SG_COLOR_ORANGE);
	sg_draw_text("arial.ttf", 26, 200, 100, 
	  "Текст может быть разного размера и цвета");

	sg_set_color(SG_COLOR_YELLOW);
	sg_draw_text("arial.ttf", 26, 100, 130, 
	  "Текст может быть с параметрами как тут: %d и %d", 27, -138);

	sg_wait_escape();
	sg_destroy_window();
}
