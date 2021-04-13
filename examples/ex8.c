#include <sg.h>

void draw_figure(int x, int y);


void
main()
{
	sg_texture_t figure_tex, figure2_tex;
	int x, dx = 1, running = 1, ev_data1, ev_data2;
	enum event_type ev_type;
	int angle = 0, dangle = 1;

	sg_create_window_ext(800, 600, 2, 0, 0);

	/* создаём 2 текстуры */
	figure_tex = sg_texture_create(201, 201);
	figure2_tex = sg_texture_create(201, 201);
	/* используем в качестве сцены созданную текстуру и рисуем на неё нашу фигуру */
	sg_scene_texture(figure_tex);
	draw_figure(0, 0);
	/* используем в качестве сцены созданную текстуру и рисуем на неё нашу фигуру */
	sg_scene_texture(figure2_tex);
	draw_figure(0, 0);
	/* возвращаем обратно в качестве сцены буфер видеокарты */
	sg_scene_texture(NULL);
	/* устанавливаем режим смешивания цветов для 2й текстуры */
	sg_texture_blendmode(figure2_tex, SG_BLENDMODE_BLEND);
	
	x = 0;
	while (running) {
		/* отрисовка сцены */
		sg_set_color(SG_COLOR_ORANGE);
		sg_draw_filledrect(0, 0, 800, 600);
		/* всё место текстуры, где мы не рисовали, будет чёрным - режим смешивания
		 * цветов по-умолчанию SG_BLENDMODE_NONE
		 */
		sg_draw_texture_ext(figure_tex, x, 100, 0, 0, angle, 0);
		/* всё место текстуры, где мы не рисовали, будет прозрачным - режим 
		 * смешивания цветов SG_BLENDMODE_BLEND
		 */
		sg_draw_texture_ext(figure2_tex, x, 400, 100, 100, angle, 0);
		sg_scene_present();
		sg_delay(2);
		
		/* расчёт следующей позиции */
		x += dx;
		if (x > (800 - 200)) {
			dx = -dx;
			x += 2*dx;
			dangle = -dangle;
		}
		if (x < 0) {
			dx = -dx;
			x += 2*dx;
			dangle = -dangle;
		}
		angle += dangle;
		if (angle > 360)
			angle = 0;
		if (angle < 0)
			angle = 360;
		
		/* проверка нажатия Esc */
		if (sg_event_poll(&ev_type, &ev_data1, &ev_data2)) {
			if ((ev_type == SG_EVENT_KEYDOWN) &&
			    (ev_data1 == SG_SCANCODE_ESCAPE)) 
				running = 0;
		}
	}

	sg_texture_free(figure_tex);
	sg_texture_free(figure2_tex);
	sg_destroy_window();
}

void
draw_figure(int x, int y)
{
	int j, k;
	
	sg_set_color(SG_COLOR_RED);
	sg_draw_filledcircle(x + 100, y + 100, 100);
	sg_set_color(SG_COLOR_BLACK);
	sg_draw_filledcircle(x + 100, y + 100, 20);
	sg_set_color(SG_COLOR_BLUE);
	for(j = 0; j < 8; j++)
		for(k = 0; k < 8; k++)
			sg_draw_filledcircle(x + 24*k + 12, y + 24*j + 12, 10);
}
