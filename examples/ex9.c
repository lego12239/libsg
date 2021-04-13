#include <sg.h>

void
main()
{
	sg_texture_t cross_tex;
	int x, w, dx = 1, running = 1, ev_data1, ev_data2;
	enum event_type ev_type;

	sg_create_window_ext(800, 600, 2, 0, 0);

	/* загружаем картинку */
	cross_tex = sg_image_load("cross.png");
	
	x = 0;
	sg_texture_info(cross_tex, &w, NULL);
	while (running) {
		/* отрисовка сцены */
		sg_set_color(SG_COLOR_ORANGE);
		sg_draw_filledrect(0, 0, 800, 600);
		sg_draw_texture_ext(cross_tex, x, 50, 0, 0, 0, 0);
		sg_scene_present();
		sg_delay(5);
		
		/* расчёт следующей позиции */
		x += dx;
		if (x > (800 - w)) {
			dx = -dx;
			x += 2*dx;
		}
		if (x < 0) {
			dx = -dx;
			x += 2*dx;
		}
		
		/* проверка нажатия Esc */
		if (sg_event_poll(&ev_type, &ev_data1, &ev_data2)) {
			if ((ev_type == SG_EVENT_KEYDOWN) &&
			    (ev_data1 == SG_SCANCODE_ESCAPE)) 
				running = 0;
		}
	}

	sg_texture_free(cross_tex);
	sg_destroy_window();
}

