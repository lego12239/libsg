#include <sg.h>

void scene_mode_0(void);
void scene_mode_1(void);
void scene_mode_2(void);
void draw_figure(int x, int y, sg_color_t color);


void
main()
{
	/* режим автоотображения сцены. Здесь мы видим мигающий объект - мы
	 *  замечаем как он отрисовывается.
	 */
	scene_mode_0();

	/* режим ручного отображения сцены. Здесь уже мерцания нет. */
	scene_mode_1();

	/* режим ручного отображения сцены без дополнительного буфера.
	 * Самый быстрый.
	 */
	scene_mode_2();
}

void
scene_mode_0(void)
{
	int x, dx = 10;

	/* тоже самое что и sg_create_window_ext(800, 600, 0, 0, 0) */
	sg_create_window(800, 600);

	x = 0;
	while (x < (800 - 100)) {
		sg_scene_clear();
		draw_figure(x, 100, SG_COLOR_RED);
		sg_delay(50);
		x += dx;
	}

	sg_draw_text("arial.ttf", 16, 100, 300, "Нажмите Esc для продолжения");

	sg_wait_escape();
	sg_destroy_window();
}

void
scene_mode_1(void)
{
	int x, dx = 10;

	sg_create_window_ext(800, 600, 1, 0, 0);

	x = 0;
	while (x < (800 - 100)) {
		sg_scene_clear();
		draw_figure(x, 100, SG_COLOR_RED);
		sg_scene_present();
		sg_delay(50);
		x += dx;
	}

	sg_draw_text("arial.ttf", 16, 100, 300, "Нажмите Esc для продолжения");
	sg_scene_present();

	sg_wait_escape();
	sg_destroy_window();
}

void
scene_mode_2(void)
{
	int x, dx = 10;

	sg_create_window_ext(800, 600, 2, 0, 0);

	x = 0;
	while (x < (800 - 100)) {
		sg_scene_clear();
		draw_figure(x, 100, SG_COLOR_RED);
		sg_scene_present();
		sg_delay(50);
		x += dx;
	}

	sg_draw_text("arial.ttf", 16, 100, 300, "Нажмите Esc для выхода");
	sg_scene_present();

	sg_wait_escape();
	sg_destroy_window();
}

void
draw_figure(int x, int y, sg_color_t color)
{
	sg_set_color(color);
	sg_draw_filledcircle(x + 50, y + 50, 50);
	sg_draw_filledcircle(x + 25, y + 25, 25);
	sg_draw_filledcircle(x + 75, y + 25, 25);
	sg_draw_filledcircle(x + 25, y + 75, 25);
	sg_draw_filledcircle(x + 75, y + 75, 25);
}