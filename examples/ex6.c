#include <sg.h>

void method1(void);
void method2(void);
void draw_figure(int x, int y, sg_color_t color);


void
main()
{
	/* Проигрывание фонового звука на общем канале со звуками отскока */
	method1();
	/* Проигрывание фонового звука как музыки (т.е. отдельно от звуков). */
	method2();
}

void
method1(void)
{
	sg_sound_t snd_left, snd_middle, snd_right;
	int x, dx = 1, running = 1, ev_data1, ev_data2;
	enum event_type ev_type;

	sg_create_window_ext(800, 600, 2, 0, 0);

	snd_left = sg_sound_load("snd1.mp3");
	snd_middle = sg_sound_load("snd2.mp3");
	snd_right = sg_sound_load("snd3.mp3");
	sg_sound_set_volume(snd_left, 100);
	sg_sound_set_volume(snd_middle, 100);
	sg_sound_set_volume(snd_right, 100);
	sg_achannel_set_volume(0, 100);
	
	sg_achannel_play(0, snd_middle, 0);
	x = 0;
	while (running) {
		/* отрисовка сцены */
		sg_scene_clear();
		draw_figure(x, 100, SG_COLOR_RED);
		sg_draw_text("arial.ttf", 16, 100, 300, 
		  "Нажмите Esc для второго варианта");
		sg_scene_present();
		sg_delay(2);
		
		/* расчёт следующей позиции */
		x += dx;
		if (x > (800 - 100)) {
			sg_achannel_play(0, snd_right, 1);
			dx = -dx;
			x += 2*dx;
		}
		if (x < 0) {
			sg_achannel_play(0, snd_left, 1);
			dx = -dx;
			x += 2*dx;
		}
		
		/* проверка нажатия Esc */
		if (sg_event_poll(&ev_type, &ev_data1, &ev_data2)) {
			if ((ev_type == SG_EVENT_KEYDOWN) &&
			    (ev_data1 == SG_SCANCODE_ESCAPE)) 
				running = 0;
		}
		
		/* если звук отскока закончился, то проигрывать фоновый звук.
		 * Данная манипуляция нужна из-за того, что мы проигрываем фоновый
		 * звук не как музыку, а как звук на общем канале с другими звуками.
		 */
		if (!sg_achannel_is_playing(0))
			sg_achannel_play(0, snd_middle, 0);
	}

	sg_destroy_window();
}

void
method2(void)
{
	sg_sound_t snd_left, snd_right;
	sg_music_t music;
	int x, dx = 10, running = 1, ev_data1, ev_data2;
	enum event_type ev_type;

	sg_create_window_ext(800, 600, 2, 0, 0);

	snd_left = sg_sound_load("snd1.mp3");
	music = sg_music_load("snd2.mp3");
	snd_right = sg_sound_load("snd3.mp3");
	sg_sound_set_volume(snd_left, 100);
	sg_music_set_volume(100);
	sg_sound_set_volume(snd_right, 100);
	sg_achannel_set_volume(0, 100);
	
	sg_music_play(music, 0);
	x = 0;
	while (running) {
		/* отрисовка сцены */
		sg_scene_clear();
		draw_figure(x, 100, SG_COLOR_RED);
		sg_scene_present();
		sg_delay(50);
		
		/* расчёт следующей позиции */
		x += dx;
		if (x > (800 - 100)) {
			sg_achannel_play(0, snd_right, 1);
			dx = -dx;
			x += 2*dx;
		}
		if (x < 0) {
			sg_achannel_play(0, snd_left, 1);
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
draw_figure(int x, int y, sg_color_t color)
{
	sg_set_color(color);
	sg_draw_filledcircle(x + 50, y + 50, 50);
	sg_draw_filledcircle(x + 25, y + 25, 25);
	sg_draw_filledcircle(x + 75, y + 25, 25);
	sg_draw_filledcircle(x + 25, y + 75, 25);
	sg_draw_filledcircle(x + 75, y + 75, 25);
}
