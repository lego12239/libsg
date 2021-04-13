#include <sg.h>

void without_texture(void);
void with_texture(void);
void draw_figure(int x, int y);


void
main()
{
	without_texture();
	with_texture();
}

void
without_texture(void)
{
	int x, dx = 1, running = 1, ev_data1, ev_data2;
	enum event_type ev_type;

	sg_create_window_ext(800, 600, 2, 0, 0);

	x = 0;
	while (running) {
		/* отрисовка сцены */
		sg_scene_clear();
		draw_figure(x, 100);
		sg_draw_text("arial.ttf", 16, 100, 300, 
		  "Нажмите Esc для второго варианта");
		sg_scene_present();
		sg_delay(2);
		
		/* расчёт следующей позиции */
		x += dx;
		if (x > (800 - 200)) {
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

	sg_destroy_window();
}

void
with_texture(void)
{
	sg_texture_t figure_tt;
	int x, dx = 1, running = 1, ev_data1, ev_data2;
	enum event_type ev_type;

	sg_create_window_ext(800, 600, 2, 0, 0);

	/* создаём текстуру */
	figure_tt = sg_texture_create(201, 201);
	/* используем в качестве сцены созданную текстуру и рисуем на неё нашу фигуру */
	sg_scene_texture(figure_tt);
	draw_figure(0, 0);
	/* возвращаем обратно в качестве сцены буфер видеокарты */
	sg_scene_texture(NULL);
	sg_set_color(SG_COLOR_RED);
	
	x = 0;
	while (running) {
		/* отрисовка сцены */
		sg_scene_clear();
		sg_draw_texture(figure_tt, x, 100);
		sg_draw_text("arial.ttf", 16, 100, 300, "Нажмите Esc для выхода");
		sg_scene_present();
		sg_delay(2);
		
		/* расчёт следующей позиции */
		x += dx;
		if (x > (800 - 200)) {
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

	sg_texture_free(figure_tt);
	sg_destroy_window();
}

void
draw_figure(int x, int y)
{
	int i, j, k;
	
	sg_set_color(SG_COLOR_RED);
	sg_draw_filledcircle(x + 100, y + 100, 100);
	sg_set_color(SG_COLOR_BLUE);
	/* имитируем рисование множества различных элементов */
	for(i = 0; i < 200; i++)
		for(j = 0; j < 8; j++)
			for(k = 0; k < 8; k++)
				sg_draw_filledcircle(x + 24*k + 12, y + 24*j + 12, 10);
}
