#include <sg.h>

void
main()
{
	sg_create_window(1024, 768);
	sg_set_color(SG_COLOR_CYAN);
	sg_draw_filledrect(100, 100, 200, 200);
	sg_draw_filledrect(400, 100, 200, 200);
	sg_draw_filledrect(700, 100, 200, 200);

	sg_delay(1000);
	sg_set_color(0xffa50080);
	sg_scene_blendmode(SG_BLENDMODE_BLEND);
	sg_draw_filledrect(50, 50, 300, 300);
	sg_scene_blendmode(SG_BLENDMODE_ADD);
	sg_draw_filledrect(350, 50, 300, 300);
	sg_scene_blendmode(SG_BLENDMODE_MOD);
	sg_draw_filledrect(650, 50, 300, 300);

	sg_wait_escape();
	sg_destroy_window();
}
