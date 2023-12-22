/**
 * @file
 * @brief Графическая библиотека
 * @version 1.4.2
 *
 * @mainpage Графическая библиотека sg
 *
 * Список функций по разделам <a href="modules.html">тут</a>.
 *
 * Примеры находятся в директории examples. Для их компиляции наберите
 * make, находясь в директории examples. Примеры:
 * - ex1 - использование функций рисования
 * - ex2 - использование различных режимов смешивания цветов
 * - ex3 - вывод текста с помощью sg_draw_text()
 * - ex4 - получение событий(нажатие клавиши и т.п.) с помощью sg_event_poll()
 * - ex5 - режимы отображения сцены
 * - ex6 - проигрывание звука
 * - ex7 - пример использования текстур
 * - ex8 - пример использования текстур (sg_draw_texture_ext())
 * - ex9 - пример использования изображений (sg_image_load())
 *
 * @todo сделать пример использования sg_image_load()
 *
 * @page pg_scene_present_mode Режим отображения сцены
 * Любые нарисованные объекты не отображаются сразу на
 * экран, а находятся в промежуточном буфере(которых может быть много: буфер
 * видеокарты при double/tripple buffering, буфер библиотеки).
 * Что бы отобразить сцену (все нарисованные объекты) на экран,
 * необходимо вызвать функцию sg_scene_present().
 * По-умолчанию, библиотека работает в режиме автоотображения сцены.
 * В этом режиме каждая функция рисования графической фигуры
 * вызывает sg_scene_present() после отрисовки фигуры.
 * Данный режим отображения сцены имеет минус в виде меньшей
 * проиводительности, чем ручной, и, как следствие, возможности
 * появления мерцаний объектов сцены.
 * Что бы использовать режим ручного отображения сцены
 * необходимо использовать для создания окна функцию sg_create_window_ext(),
 * которая принимает третьим аргументом режим отображения сцены:
 * - 0 - автоотображения сцены
 *       всё рисуется во внутренний буфер библиотеки и каждая
 *       sg_draw_*()-функция в конце рисования вызывает sg_scene_present()
 * - 1 - ручное отображение сцены
 *       всё рисуется во внутренний буфер библиотеки; sg_scene_present()
 *       необходимо вызывать вручную
 * - 2 - ручное отображение сцены, без доп.буфера
 *       всё рисуется в буфер видеокарты; sg_scene_present() необходимо
 *       вызывать вручную
 * Режим 2 является наиболее быстрым, но требует отрисовки всей сцены
 * в каждом кадре перед вызовом sg_scene_present().
 *
 * @page pg_blendmode Режим смешивания цветов
 * При рисовании накладывающихся друг на друга графических фигур итоговый
 * цвет определяется режимом смешивания цветов:
 * - SG_BLENDMODE_NONE - нет смешивания (dstRGBA = srcRGBA)
 * - SG_BLENDMODE_BLEND - смешивание альфа-канала (dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA)),  dstA = srcA + (dstA * (1-srcA)))
 * - SG_BLENDMODE_ADD - суммирующие смешивание (dstRGB = (srcRGB * srcA) + dstRGB,  dstA = dstA)
 * - SG_BLENDMODE_MOD - умножение цветов (dstRGB = srcRGB * dstRGB,  dstA = dstA)
 *
 * По-умолчанию используется режим SG_BLENDMODE_NONE, т.е. итоговый цвет
 * в месте наложения фигур будет цветом фигуры нарисованной последней.
 * SG_BLENDMODE_BLEND и SG_BLENDMODE_ADD используются для прозрачных
 * объектов.
 *
 * @page pg_mouse_mode Режим работы мыши
 * При создании окна с помощью функции sg_create_window_ext() указывается
 * режим работы мыши. Возможные значения:
 * - 0 - работа без захвата мыши (в окне отображается системный указатель мыши,
 *   координаты мыши абсолютные)
 * - не 0 - работа с захватом мыши (в окне не отображается системный указатель
 *   мыши и т.о. невозможно покинуть окно указателем мыши;
 *   координаты мыши относительные - относительно её предыдущего положения)
 *
 * @defgroup Colors Цвета
 * @brief Функции и макросы для работы с цветом
 *
 * @defgroup Init Управление окном
 * @brief Функции управления окном
 *
 * @defgroup SceneFun Управление сценой
 * @brief Функции для управления сценой
 *
 * @defgroup DrawFun Рисование
 * @brief Функции для рисования графических фигур
 *
 * @defgroup TextureFun Текстуры
 * @brief Функции для работы с текстурами
 *
 * Текстура это 2-мерное изображение, которое можно отрисовать на экран.
 * По-умолчанию отрисовка сцены идёт в буфер видеокарты(режим 2 отображения
 * сцены) или во внутренний буфер библиотеки(режимы 0 и 1 отображения сцены).
 * Идея использования текстур в том, что бы временно переключить отрисовку
 * сцены на текстуру, нарисовать туда необходимый объект и, вернув отображение
 * сцены назад, использовать получившуюся текстуру, размещая изображение
 * сохранённое в неё в нужных координатах окна. Т.о. объект отрисовывается
 * быстрее, т.к. текстура это, грубо, прямоугольник с пикселями, а не
 * комбинация линий, прямоугольников, окружностей и т.д. К тому же, библиотека,
 * если возможно, для текстур использует ускорение графического адаптера; что
 * дополнительно ускоряет работу с ними.
 *
 * Т.е. алгоритм такой:
 * 1. создаём текстуру с помощью sg_texture_create() или sg_image_load()
 * 2. переключаем сцену на нашу текстуру с помощью sg_scene_texture()
 * 3. рисуем туда что хотим
 * 4. возвращаем буфер сцены с помощью sg_scene_texture(NULL);
 * 5. рисуем содержимое текстуры на сцену с помощью sg_draw_texture() или
 *    sg_draw_texture_ext()
 *
 * @defgroup TextFun Текст
 * @brief Функции для работы с текстом
 *
 * @defgroup ImgFun Изображения
 * @brief Функции для работы с изображениями
 *
 * @defgroup Events События
 * @brief Функции для получения событий
 *
 * Данные функции используются для определения нажатых кнопок клавиатуры,
 * мыши или движений мыши.
 *
 * @defgroup AudioFun Звук
 * @brief Функции для работы с аудио
 *
 * Разница между звуком и музыкой следующая. Звук вопроизводится на
 * определённом канале. Сколько каналов, столько одновременно может
 * проигрываться звуков. Если мы на том же канале воспроизводим звук
 * до окончания проигрывания прошлого звука, то воспроизведение прошлого
 * просто обрывается. Музыка же воспроизводится на своём отдельном и
 * единственном канале.
 *
 * @defgroup OtherFun Другое
 * @brief Другие функции
 */

 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include "sg.h"


static SDL_Window *__sg_window__;
static SDL_Renderer *__sg_renderer__;
static SDL_Texture *__sg_scene__, *__sg_scene_texture_curr__;
static unsigned int __sg_spmode__ = 0;
static unsigned int __sg_mousemode__ = 0;


static SDL_Texture*
scene_make(unsigned int width, unsigned int height)
{
	SDL_Texture *t;
	
    t = SDL_CreateTexture(__sg_renderer__, SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_TARGET, width, height);
    if (!t) {
    	fprintf(stderr, "Ошибка создания сцены: %s\n", SDL_GetError());
    	exit(EXIT_FAILURE);
    }
    
    return t;
}

static void
scene_free(SDL_Texture* t)
{
	SDL_DestroyTexture(t);
}

static void
scene_clear(SDL_Texture* t)
{
	SDL_Color c;
	SDL_Texture *t_orig;
	
	t_orig = SDL_GetRenderTarget(__sg_renderer__);
	if (SDL_SetRenderTarget(__sg_renderer__, t) != 0) {
		fprintf(stderr, "Ошибка очистки сцены: %s\n", SDL_GetError());
		exit(1);
	}
	if (SDL_GetRenderDrawColor(__sg_renderer__, &c.r, &c.g, &c.b, &c.a) != 0) {
		fprintf(stderr, "Ошибка очистки экрана: ошибка сохранения цвета: "
		  "%s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDL_SetRenderDrawColor(__sg_renderer__, 0, 0, 0, 0) != 0) {
		fprintf(stderr, "Ошибка очистки сцены: %s\n", SDL_GetError());
		exit(1);
	}
	if (SDL_RenderClear(__sg_renderer__) != 0) {
		fprintf(stderr, "Ошибка очистки сцены: %s\n", SDL_GetError());
		exit(1);
	}
	if (SDL_SetRenderDrawColor(__sg_renderer__, c.r, c.g, c.b, c.a) < 0) {
		fprintf(stderr, "Ошибка очистки экрана: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDL_SetRenderTarget(__sg_renderer__, t_orig) != 0) {
		fprintf(stderr, "Ошибка очистки сцены: %s\n", SDL_GetError());
		exit(1);
	}
}

static void
scene_show(SDL_Texture* t)
{
	SDL_Rect rect;
	SDL_Texture *t_orig;
	
	t_orig = SDL_GetRenderTarget(__sg_renderer__);
	if (SDL_SetRenderTarget(__sg_renderer__, NULL) != 0) {
		fprintf(stderr, "Ошибка отображения сцены: %s\n", SDL_GetError());
		exit(1);
	}
	rect.x = 0;
	rect.y = 0;
	SDL_GetWindowSize(__sg_window__, &rect.w, &rect.h);
	if (SDL_RenderCopy(__sg_renderer__, t, NULL, &rect) != 0) {
		fprintf(stderr, "Ошибка отображения сцены: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_RenderPresent(__sg_renderer__);
	if (SDL_SetRenderTarget(__sg_renderer__, t_orig) != 0) {
		fprintf(stderr, "Ошибка отображения сцены: %s\n", SDL_GetError());
		exit(1);
	}
}

/**
 * @ingroup Init
 * @brief Создать окно размерами width на height
 *
 * @param width - ширина в пикселях
 * @param height - высота в пикселях
 * @param scene_pmode - @ref pg_scene_present_mode (0 - автоотображение сцены,
 *   1 - ручное отображение сцены, 2 - ручное отображение без доп.буфера)
 * @param mouse_mode - @ref pg_mouse_mode (0 - без захвата мыши,
 *   1 - с захватом мыши)
 * @param flags - флаги(SG_RENDERER_ACCELERATED - использовать ускорение
 *   графики, SG_RENDERER_PRESENTVSYNC - включить вертикальную синхронизацию)
 *
 * @return <0 - ошибка
 *
 * Создать окно с указанными размерами и инициализировать
 * графическую подсистему.
 * Также создаёт 16 звуковых каналов (т.е. одновременно могут быть
 * возспроизведены 16 звуков).
 */
int
sg_create_window_ext(unsigned int width, unsigned int height,
  unsigned int scene_pmode, unsigned int mouse_mode, unsigned int flags)
{
	uint32_t rflags;
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		fprintf(stderr, "Ошибка инициализации графики: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	__sg_window__ = SDL_CreateWindow("Program", SDL_WINDOWPOS_UNDEFINED,
	  SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	if (!__sg_window__) {
		fprintf(stderr, "Ошибка создания окна: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	rflags = SDL_RENDERER_TARGETTEXTURE;
	if (flags & SG_RENDERER_ACCELERATED)
		rflags |= SDL_RENDERER_ACCELERATED;
	else
		rflags |= SDL_RENDERER_SOFTWARE;
	if (flags & SG_RENDERER_PRESENTVSYNC)
		rflags |= SDL_RENDERER_PRESENTVSYNC;
	__sg_renderer__ = SDL_CreateRenderer(__sg_window__, -1, rflags);
	if (!__sg_renderer__) {
		fprintf(stderr, "Ошибка создания рендера: %s\n", SDL_GetError());
		SDL_DestroyWindow(__sg_window__);
		SDL_Quit();
		return -1;
	}
	
	__sg_spmode__ = scene_pmode;
	if (__sg_spmode__ < 2)
		__sg_scene__ = scene_make(width, height);
	sg_scene_texture(NULL);
	sg_scene_clear();
	
	__sg_mousemode__ = mouse_mode;
	if (SDL_SetRelativeMouseMode(mouse_mode ? SDL_TRUE : SDL_FALSE) != 0) {
		fprintf(stderr, "Ошибка инициализации мыши: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if (TTF_Init() == -1) {
		fprintf(stderr, "Ошибка инициализации шрифтов: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	rflags = IMG_INIT_PNG;
	if ((IMG_Init(rflags) & rflags) != rflags) {
		fprintf(stderr, "Ошибка инициализации подсистемы загрузки изображений:"
		  " %s\n", IMG_GetError());
		exit(EXIT_FAILURE);
	}
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
		fprintf(stderr, "Ошибка инициализации аудио-подсистемы: %s\n",
		  Mix_GetError());
		exit(EXIT_FAILURE);
	}
	Mix_AllocateChannels(16);
	
	return 0;
}

/**
 * @ingroup Init
 * @brief Создать окно размерами width на height
 *
 * @param width - ширина в пикселях
 * @param height - высота в пикселях
 *
 * Создать окно с указанными размерами и инициализировать
 * графическую подсистему.
 * Идентична вызову sg_create_window_ext(width, height, 0, 0, 0).
 */
void
sg_create_window(unsigned int width, unsigned int height)
{
	sg_create_window_ext(width, height, 0, 0, 0);
}

/**
 * @ingroup Init
 * @brief Уничтожить созданное окно
 */
void
sg_destroy_window(void)
{
	Mix_CloseAudio();
	IMG_Quit();
	TTF_Quit();
	scene_free(__sg_scene__);
	SDL_DestroyRenderer(__sg_renderer__);
	SDL_DestroyWindow(__sg_window__);
	SDL_Quit();
}

/**
 * @ingroup Init
 * @brief Получить размеры окна
 *
 * @param width - где сохранить ширину
 * @param height - где сохранить высоту
 */
void
sg_get_window_size(unsigned int *width, unsigned int *height)
{
	int w, h;

	SDL_GetWindowSize(__sg_window__, &w, &h);
	*width = w;
	*height = h;
}

/**
 * @ingroup Colors
 * @brief Установить текущий цвет. на указанный в color (0xRRGGBBAA)
 *
 * @param color - цвет, 32-битное число, формат - 0xRRGGBBAA
 *
 * Текстовые название цветов см. в разделе @ref Colors.
 * Пример установки красного цвета в качестве текущего (две строчки делают одно и то же):
 * @code
 * sg_set_color(0xff0000ff);
 * sg_set_color(SG_COLOR_RED);
 * @endcode
 */
void
sg_set_color(sg_color_t color)
{
	uint8_t r, g, b, a;
	
	r = color >> 24;
	g = (color & 0xff0000) >> 16;
	b = (color & 0xff00) >> 8;
	a = color & 0xff;
	if (SDL_SetRenderDrawColor(__sg_renderer__, r, g, b, a) < 0) {
		fprintf(stderr, "Ошибка установки цвета: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

/**
 * @ingroup SceneFun
 * @brief Отобразить нарисованную сцену
 *
 * Используется в ручном режиме отображения сцены
 *
 * См. @ref pg_scene_present_mode
 */
void
sg_scene_present(void)
{
	if (__sg_spmode__ == 2) {
		SDL_RenderPresent(__sg_renderer__);
		return;
	}
	scene_show(__sg_scene__);
}

/**
 * @ingroup SceneFun
 * @brief Устанавливает режим смешивания цветов для рисования фигур
 *
 * @param mode - режим смешивания (@ref pg_blendmode)
 */
void
sg_scene_blendmode(enum blend_mode mode)
{
	switch (mode) {
	case SG_BLENDMODE_NONE:
		mode = SDL_BLENDMODE_NONE;
		break;
	case SG_BLENDMODE_BLEND:
		mode = SDL_BLENDMODE_BLEND;
		break;
	case SG_BLENDMODE_ADD:
		mode = SDL_BLENDMODE_ADD;
		break;
	case SG_BLENDMODE_MOD:
		mode = SDL_BLENDMODE_MOD;
		break;
	default:
		mode = SDL_BLENDMODE_NONE;
		break;
	}
	if (SDL_SetRenderDrawBlendMode(__sg_renderer__, mode) != 0) {
		fprintf(stderr, "Ошибка установки режима смешивания цветов: %s",
		  SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

/**
 * @ingroup TextureFun
 * @brief Использовать в качестве сцены для отрисовки фигур текстуру.
 *
 * @param texture - текстура
 *
 * После вызова этой функции все функции, которые рисуют фигуры,
 * делают это на указанную текстуру, а не в стандартный буфер сцены.
 * Что бы вернуть использование стандартного буфера сцены для
 * отрисовки сцены, нужно вызвать эту функцию с параметром NULL в
 * качестве текстуры.
 */
void
sg_scene_texture(sg_texture_t texture)
{
	if ((texture == NULL) && (__sg_spmode__ < 2))
		texture = __sg_scene__;
	if (__sg_spmode__ == 0)
		__sg_scene_texture_curr__ = texture;
	if (SDL_SetRenderTarget(__sg_renderer__, texture) != 0) {
		fprintf(stderr, "Ошибка установки текстуры для сцены: %s",
		  SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

/**
 * @ingroup SceneFun
 * @brief Очистить сцену (залить чёрным цветом)
 */
void
sg_scene_clear(void)
{
	SDL_Color c;
	int ret;
	
	if (__sg_spmode__ == 2) {
		ret = SDL_GetRenderDrawColor(__sg_renderer__, &c.r, &c.g, &c.b, &c.a);
		if (ret != 0) {
			fprintf(stderr, "Ошибка очистки экрана: ошибка сохранения цвета: "
			  "%s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		if (SDL_SetRenderDrawColor(__sg_renderer__, 0, 0, 0, 0) < 0) {
			fprintf(stderr, "Ошибка очистки экрана: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		if (SDL_RenderClear(__sg_renderer__) < 0) {
			fprintf(stderr, "Ошибка очистки экрана: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		if (SDL_SetRenderDrawColor(__sg_renderer__, c.r, c.g, c.b, c.a) < 0) {
			fprintf(stderr, "Ошибка очистки экрана: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		return;
	}
	scene_clear(__sg_scene__);
	if ((__sg_spmode__ == 0) &&
	    (__sg_scene_texture_curr__ == __sg_scene__))
		sg_scene_present();
}

/**
 * @ingroup DrawFun
 * @brief Нарисавать точку текущим цветом в координатах (x, y)
 *
 * @param x - координата x в пикселях
 * @param y - координата y в пикселях
 *
 * Пример(Нарисовать точку в координате (305, 250)):
 * @code
 * sg_draw_point(305, 250);
 * @endcode
 */
void
sg_draw_point(int x, int y)
{
	if (SDL_RenderDrawPoint(__sg_renderer__, x, y) < 0) {
		fprintf(stderr, "Ошибка рисования точки: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if ((__sg_spmode__ == 0) &&
	    (__sg_scene_texture_curr__ == __sg_scene__))
		sg_scene_present();
}

/**
 * @ingroup DrawFun
 * @brief Нарисовать прямую линию текущим цветом
 *
 * @param x1 - координата x начальной точки в пикселях
 * @param y1 - координата y начальной точки в пикселях
 * @param x2 - координата x конечной точки в пикселях
 * @param y2 - координата y конечной точки в пикселях
 *
 * Провести линию от точки (x1, y1) до точки (x2, y2)
 *
 * Пример(Нарисовать линию из точки (100, 150) в точку (400, 200)):
 * @code
 * sg_draw_line(100, 150, 400, 200);
 * @endcode
 */
void
sg_draw_line(int x1, int y1, int x2, int y2)
{
	if (SDL_RenderDrawLine(__sg_renderer__, x1, y1, x2, y2) < 0) {
		fprintf(stderr, "Ошибка рисования линии: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if ((__sg_spmode__ == 0) &&
	    (__sg_scene_texture_curr__ == __sg_scene__))
		sg_scene_present();
}

/**
 * @ingroup DrawFun
 * @brief Нарисовать прямоугольник текущим цветом
 *
 * @param x - координата x левого верхнего угла в пикселях
 * @param y - координата y левого верхнего угла в пикселях
 * @param width - ширина в пикселях
 * @param height - высота в пикселях
 *
 * Нарисовать прямоугольник с левым верхним углом в
 * координате (x, y) и шириной width и высотой height
 *
 * Пример(Нарисовать прямоугольник с левым верхним углом в координате
 * (50, 100) шириной 80 и высотой 60):
 * @code
 * sg_draw_rect(50, 100, 80, 60);
 * @endcode
 */
void
sg_draw_rect(int x, int y, int width, int height)
{
	SDL_Rect rect;
	
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	if (SDL_RenderDrawRect(__sg_renderer__, &rect) < 0) {
		fprintf(stderr, "Ошибка рисования прямоугольника: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if ((__sg_spmode__ == 0) &&
	    (__sg_scene_texture_curr__ == __sg_scene__))
		sg_scene_present();
}

/**
 * @ingroup DrawFun
 * @brief Нарисовать закрашенный прямоугольник текущим цветом
 *
 * @param x - координата x левого верхнего угла в пикселях
 * @param y - координата y левого верхнего угла в пикселях
 * @param width - ширина в пикселях
 * @param height - высота в пикселях
 *
 * Нарисовать прямоугольник с левым верхним углом в
 * координате (x, y) и шириной width и высотой height
 *
 * Пример(Нарисовать прямоугольник с левым верхним углом в координате
 * (50, 100) шириной 80 и высотой 60):
 * @code
 * sg_draw_filledrect(50, 100, 80, 60);
 * @endcode
 */
void
sg_draw_filledrect(int x, int y, int width, int height)
{
	SDL_Rect rect;
	
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	if (SDL_RenderFillRect(__sg_renderer__, &rect) < 0) {
		fprintf(stderr, "Ошибка рисования прямоугольника: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if ((__sg_spmode__ == 0) &&
	    (__sg_scene_texture_curr__ == __sg_scene__))
		sg_scene_present();
}

/**
 * @ingroup DrawFun
 * @brief Нарисовать эллипс текущим цветом
 *
 * @param x - x-координата цента в пикселях
 * @param y - y-координата центра в пикселях
 * @param rx - радиус по оси x в пикселях
 * @param ry - радиус по оси y в пикселях
 *
 * Нарисавать эллипс с центром в координате (x, y)
 * и радиусами rx и ry.
 * Алгоритм Брезенхэма
 *
 * Пример(Нарисовать эллипс с центром в координате (200, 300) и радиусами
 * 40 и 80):
 * @code
 * sg_draw_ellipse(200, 300, 40, 80);
 * @endcode
 */
void
sg_draw_ellipse(int x, int y, int rx, int ry)
{
	int xi, yi, dh, dv, dd, rx2, ry2;
	
	rx2 = rx * rx;
	ry2 = ry * ry;
	xi = 0;
	yi = ry;
	while (yi >= 0) {
		if (SDL_RenderDrawPoint(__sg_renderer__, x + xi, y + yi) < 0) {
			fprintf(stderr, "Ошибка рисования окужности: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		if (SDL_RenderDrawPoint(__sg_renderer__, x + xi, y - yi) < 0) {
			fprintf(stderr, "Ошибка рисования окужности: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		if (SDL_RenderDrawPoint(__sg_renderer__, x - xi, y + yi) < 0) {
			fprintf(stderr, "Ошибка рисования окужности: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		if (SDL_RenderDrawPoint(__sg_renderer__, x - xi, y - yi) < 0) {
			fprintf(stderr, "Ошибка рисования окужности: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		dd = ry2*(xi + 1)*(xi + 1) + rx2*(yi - 1)*(yi - 1) - rx2*ry2;
		if (dd < 0) {
			dd = abs(dd);
			dh = abs(ry2*(xi + 1)*(xi + 1) + rx2*yi*yi - rx2*ry2);
			if (dh < dd) {
				xi++;
				continue;
			}
		} else if (dd > 0) {
			dd = abs(dd);
			dv = abs(ry2*xi*xi + rx2*(yi - 1)*(yi - 1) - rx2*ry2);
			if (dv <= dd) {
				yi--;
				continue;
			}
		}	
		xi++;
		yi--;
	}
	if ((__sg_spmode__ == 0) &&
	    (__sg_scene_texture_curr__ == __sg_scene__))
		sg_scene_present();
}

/**
 * @ingroup DrawFun
 * @brief Нарисовать закрашенный эллипс текущим цветом
 *
 * @param x - x-координата цента в пикселях
 * @param y - y-координата центра в пикселях
 * @param rx - радиус по оси x в пикселях
 * @param ry - радиус по оси y в пикселях
 *
 * Нарисавать эллипс с центром в координате (x, y)
 * и радиусами rx и ry.
 * Алгоритм Брезенхэма
 *
 * Пример(Нарисовать эллипс с центром в координате (200, 300) и радиусами
 * 40 и 80):
 * @code
 * sg_draw_filledellipse(200, 300, 40, 80);
 * @endcode
 */
void
sg_draw_filledellipse(int x, int y, int rx, int ry)
{
	int xi, yi, dh, dv, dd, rx2, ry2;
	
	rx2 = rx * rx;
	ry2 = ry * ry;
	xi = 0;
	yi = ry;
	while (yi >= 0) {
		if (SDL_RenderDrawLine(__sg_renderer__, x - xi, y + yi, x + xi,
		  y + yi) < 0) {
			fprintf(stderr, "Ошибка рисования окружности: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		if (SDL_RenderDrawLine(__sg_renderer__, x - xi, y - yi, x + xi,
		  y - yi) < 0) {
			fprintf(stderr, "Ошибка рисования окружности: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		dd = ry2*(xi + 1)*(xi + 1) + rx2*(yi - 1)*(yi - 1) - rx2*ry2;
		if (dd < 0) {
			dd = abs(dd);
			dh = abs(ry2*(xi + 1)*(xi + 1) + rx2*yi*yi - rx2*ry2);
			if (dh < dd) {
				xi++;
				continue;
			}
		} else if (dd > 0) {
			dd = abs(dd);
			dv = abs(ry2*xi*xi + rx2*(yi - 1)*(yi - 1) - rx2*ry2);
			if (dv <= dd) {
				yi--;
				continue;
			}
		}	
		xi++;
		yi--;
	}
	if ((__sg_spmode__ == 0) &&
	    (__sg_scene_texture_curr__ == __sg_scene__))
		sg_scene_present();
}

/**
 * @ingroup DrawFun
 * @brief Нарисовать окружность текущим цветом
 *
 * @param x - x-координата центра в пикселях
 * @param y - y-координата центра в пикселях
 * @param r - радиус в пикселях
 *
 * Нарисовать окружность с центром в координате (x, y) и радиусом r.
 * Алгоритм Брезенхэма
 *
 * Пример(нарисовать окружность в точке (100, 300) и радиусом 25):
 * @code
 * sg_draw_circle(100, 300, 25);
 * @endcode
 */
void
sg_draw_circle(int x, int y, int r)
{
	sg_draw_ellipse(x, y, r, r);
}

/**
 * @ingroup DrawFun
 * @brief Нарисовать закрашенную окружность текущим цветом
 *
 * @param x - x-координата в пикселях
 * @param y - y-координата в пикселях
 * @param r - радиус в пикселях
 *
 * Нарисовать закрашенную окружность с центром в координате (x, y) и радиусом r.
 * Алгоритм Брезенхэма
 *
 * Пример(нарисовать окружность в точке (100, 300) и радиусом 25):
 * @code
 * sg_draw_filledcircle(100, 300, 25);
 * @endcode
 */
void
sg_draw_filledcircle(int x, int y, int r)
{
	sg_draw_filledellipse(x, y, r, r);
}

/**
 * @ingroup OtherFun
 * @brief Пауза
 *
 * @param ms - кол-во миллисекунд паузы
 *
 * Прекратить выполнение программы на указанное кол-во миллисекунд.
 */
void
sg_delay(unsigned int ms)
{
	SDL_Delay(ms);
}

/**
 * @ingroup TextureFun
 * @brief Создать текстуру
 *
 * @param width - ширина текстуры в пикселях
 * @param height - высота текстуры в пикселях
 *
 * @return созданная текстура
 */
sg_texture_t
sg_texture_create(int width, int height)
{
	SDL_Texture *t;
	
	t = SDL_CreateTexture(__sg_renderer__, SDL_PIXELFORMAT_RGBA8888,
	  SDL_TEXTUREACCESS_TARGET, width, height);
	if (!t) {
		fprintf(stderr, "Ошибка создания текстуры: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	return t;
}

/**
 * @ingroup TextureFun
 * @brief Удалить текстуру
 *
 * @param texture текстура, которую надо удалить
 *
 * После того как текстура больше не нужна, её нужно удалить для
 * освобождения оперативной памяти.
 */
void
sg_texture_free(sg_texture_t texture)
{
	SDL_DestroyTexture(texture);
}

/**
 * @ingroup TextureFun
 * @brief Запрашивает ширину и высоту текстуры
 *
 * @param texture - текстура, параметры который хотим узнать
 * @param w - указатель на переменную, куда будет сохранена ширина (может быть NULL)
 * @param h - указатель на переменную, куда будет сохранена высота (может быть NULL)
 *
 * Функция сохраняет ширину и высоту текстуры в переменных, на которые
 * указывают указатели w и h.
 */
void
sg_texture_info(sg_texture_t texture, int *w, int *h)
{
	SDL_QueryTexture(texture, NULL, NULL, w, h);
}

/**
 * @ingroup TextureFun
 * @brief Устанавливает режим смешивания цветов при отрисовки текстуры
 *
 * @param texture - текстура
 * @param mode - желаемый режим смешивания цветов для данной текстуры
 *   @ref pg_blendmode
 */
void
sg_texture_blendmode(sg_texture_t texture, unsigned int mode)
{
	if (SDL_SetTextureBlendMode(texture, mode) != 0) {
		fprintf(stderr, "Ошибка установки режима смешивания цветов для "
		  "текстуры: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

/**
 * @ingroup TextureFun
 * @brief Установка модификации альфа-канала текстуры
 *
 * @param texture - текстура
 * @param a - значение для операции над альфа-каналом
 *
 * Значение альфа-канала текстуры при отрисовке будет умножено на a/255.
 */
void
sg_texture_set_alphamod(sg_texture_t texture, uint8_t a)
{
	if (SDL_SetTextureAlphaMod(texture, a) < 0) {
		fprintf(stderr, "Ошибка установки модицикации альфа-канала для "
		  "текстуры: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

/**
 * @ingroup TextureFun
 * @brief Установка модификации цвета текстуры
 *
 * @param texture - текстура
 * @param r - значение для операции над красным каналом
 * @param g - значение для операции над зелёным каналом
 * @param b - значение для операции над синим каналом
 *
 * Значение красного канала текстуры при отрисовке будет умножено на r/255 и
 * соответственно для других 2х каналов.
 */
void
sg_texture_set_colormod(sg_texture_t texture, uint8_t r, uint8_t g, uint8_t b)
{
	if (SDL_SetTextureColorMod(texture, r, g, b) < 0) {
		fprintf(stderr, "Ошибка установки модицикации цвета для "
		  "текстуры: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

/**
 * @ingroup TextureFun
 * @brief Нарисовать текстуру
 *
 * @param texture - текстура
 * @param x - x-координата в пикселях
 * @param y - y-координата в пикселях
 *
 * Нарисовать указанную текстуру в координатах (x, y), где
 * (x, y) - координаты расположения верхнего левого угла текстуры.
 */
void
sg_draw_texture(sg_texture_t texture, int x, int y)
{
	SDL_Rect dstrect;
	
	dstrect.x = x;
	dstrect.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);
	
	if (SDL_RenderCopy(__sg_renderer__, texture, NULL, &dstrect) != 0) {
		fprintf(stderr, "Ошибка рисования текстуры: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if ((__sg_spmode__ == 0) &&
	    (__sg_scene_texture_curr__ == __sg_scene__))
		sg_scene_present();
}

/**
 * @ingroup TextureFun
 * @brief Нарисовать текстуру с поворотом и отражением
 *
 * @param texture - текстура
 * @param x - x-координата в пикселях
 * @param y - y-координата в пикселях
 * @param w - ширина до которой надо увеличить/уменьшить изображение при
 *            отрисовке
 * @param h - высота до которой надо увеличить/уменьшить изображение при
 *            отрисовке
 * @param angle - угол поворота текстуры в градусах (по часовой стрелке)
 * @param flip - отражение (комбинация SG_FLIP_NONE, SG_FLIP_HORIZONTAL
 *   и SG_FLIP_VERTICAL)
 *
 * Нарисовать указанную текстуру в координатах (x, y), где:
 * (x, y) - координаты расположения верхнего левого угла текстуры
 * w и h - размеры итогового изображения. Если w равно 0, то
 * ширина для итогового изображения при отрисовке текстуры равна ширине
 * текстуры. Тоже самое и с высотой.
 */
void
sg_draw_texture_ext(sg_texture_t texture, int x, int y, int w, int h,
  double angle, int flip)
{
	SDL_Rect dstrect;
	
	dstrect.x = x;
	dstrect.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);
	if (w)
		dstrect.w = w;
	if (h)
		dstrect.h = h;
	
	switch (flip) {
	case SG_FLIP_NONE:
		flip = SDL_FLIP_NONE;
		break;
	case SG_FLIP_HORIZONTAL:
		flip = SDL_FLIP_HORIZONTAL;
		break;
	case SG_FLIP_VERTICAL:
		flip = SDL_FLIP_VERTICAL;
		break;
	default:
		flip = SDL_FLIP_NONE;
		break;
	}
	
	if (SDL_RenderCopyEx(__sg_renderer__, texture, NULL, &dstrect, angle,
	  NULL, flip) != 0) {
		fprintf(stderr, "Ошибка рисования текстуры: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if ((__sg_spmode__ == 0) &&
	    (__sg_scene_texture_curr__ == __sg_scene__))
		sg_scene_present();
}

static sg_texture_t _sg_render_text(const char *font, unsigned int size, const char *text, va_list ap);

/**
 * @ingroup TextFun
 * @brief Нарисовать текст
 *
 * @param font - имя файла шрифта (абсолютное или относительно к текущей директории)
 * @param size - размер шрифта
 * @param x - x-координата для отрисовки текста
 * @param y - y-координата для отрисовки текста
 * @param text - текст(строка формата как в printf)
 *
 * Нарисовать текст указанным шрифтом, размером и текущим цветом в координатах (x, y).
 *
 * Пример:
 * @code
 * sg_draw_text("examples/arial.ttf", 16, 100, 50, "Тест");
 * @endcode
 */
void
sg_draw_text(const char *font, unsigned int size,
  unsigned int x, unsigned int y, const char *text, ...)
{
	SDL_Texture *ttmp;
	va_list ap;

	va_start(ap, text);
	ttmp = _sg_render_text(font, size, text, ap);
	va_end(ap);
	sg_draw_texture(ttmp, x, y);
	SDL_DestroyTexture(ttmp);
}

/**
 * @ingroup TextFun
 * @brief Сгенерировать текстуру с текстом
 *
 * @param font - имя файла шрифта
 * @param size - размер шрифта
 * @param text - текст(строка формата как в printf)
 *
 * @return Текстура с текстом
 *
 * Сгенерировать текст указанным шрифтом, размером и текущим цветом.
 *
 * Пример:
 * @code
 * sg_texture_t text = sg_render_text("arial.ttf", 16, "Тест");
 * @endcode
 */
sg_texture_t
sg_render_text(const char *font, unsigned int size, const char *text, ...)
{
	va_list ap;
	sg_texture_t t;

	va_start(ap, text);
	t = _sg_render_text(font, size, text, ap);
	va_end(ap);

	return t;
}

static sg_texture_t
_sg_render_text(const char *font, unsigned int size, const char *text,
  va_list ap)
{
	SDL_Surface *stmp;
	SDL_Texture *ttmp;
	SDL_Color c;
	TTF_Font *f;
	int len;
	char *str;
	va_list ap1;
	
	f  = TTF_OpenFont(font, size);
	if (!f) {
		fprintf(stderr, "Ошибка загрузки шрифта: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDL_GetRenderDrawColor(__sg_renderer__, &c.r, &c.g, &c.b, &c.a) != 0) {
		fprintf(stderr, "Ошибка рендеринга текста: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	va_copy(ap1, ap);
	len = vsnprintf(NULL, 0, text, ap1);
	va_end(ap1);
	str = malloc(len + 1);
	if (!str) {
		fprintf(stderr, "Ошибка: недостаточно памяти: %d байт\n", len + 1);
		exit(EXIT_FAILURE);
	}
	va_copy(ap1, ap);
	vsnprintf(str, len + 1, text, ap1);
	va_end(ap1);
	stmp = TTF_RenderUTF8_Solid(f, str, c);
	if (!stmp) {
		fprintf(stderr, "Ошибка рендеринга текста: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	ttmp = SDL_CreateTextureFromSurface(__sg_renderer__, stmp);
	if (!ttmp) {
		fprintf(stderr, "Ошибка рендеринга текста: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(stmp);
	free(str);
	TTF_CloseFont(f);
	return ttmp;
}

/**
 * @ingroup ImgFun
 * @brief Загрузить изображение из файла в текстуру
 *
 * @param fname - имя файла с изображением (png-файл)
 *
 * @return текстура с изображением
 */
sg_texture_t
sg_image_load(const char *fname)
{
	SDL_Surface *s;
	SDL_Texture *t;
	
	s = IMG_Load(fname);
	if (!s) {
		fprintf(stderr, "Ошибка загрузки изображения: %s\n", IMG_GetError());
		exit(EXIT_FAILURE);
	}
	t = SDL_CreateTextureFromSurface(__sg_renderer__, s);
	if (!t) {
		fprintf(stderr, "Ошибка загрузки изображения: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(s);
	return t;
}

static int
_sg_event_getkey(SDL_Scancode sc)
{
	switch (sc) {
	case SDL_SCANCODE_0:
		return SG_SCANCODE_0;
	case SDL_SCANCODE_1:
		return SG_SCANCODE_1;
	case SDL_SCANCODE_2:
		return SG_SCANCODE_2;
	case SDL_SCANCODE_3:
		return SG_SCANCODE_3;
	case SDL_SCANCODE_4:
		return SG_SCANCODE_4;
	case SDL_SCANCODE_5:
		return SG_SCANCODE_5;
	case SDL_SCANCODE_6:
		return SG_SCANCODE_6;
	case SDL_SCANCODE_7:
		return SG_SCANCODE_7;
	case SDL_SCANCODE_8:
		return SG_SCANCODE_8;
	case SDL_SCANCODE_9:
		return SG_SCANCODE_9;
	case SDL_SCANCODE_A:
		return SG_SCANCODE_A;
	case SDL_SCANCODE_B:
		return SG_SCANCODE_B;
	case SDL_SCANCODE_BACKSLASH:
		return SG_SCANCODE_BACKSLASH;
	case SDL_SCANCODE_BACKSPACE:
		return SG_SCANCODE_BACKSPACE;
	case SDL_SCANCODE_C:
		return SG_SCANCODE_C;
	case SDL_SCANCODE_CAPSLOCK:
		return SG_SCANCODE_CAPSLOCK;
	case SDL_SCANCODE_COMMA:
		return SG_SCANCODE_COMMA;
	case SDL_SCANCODE_D:
		return SG_SCANCODE_D;
	case SDL_SCANCODE_DELETE:
		return SG_SCANCODE_DELETE;
	case SDL_SCANCODE_E:
		return SG_SCANCODE_E;
	case SDL_SCANCODE_END:
		return SG_SCANCODE_END;
	case SDL_SCANCODE_EQUALS:
		return SG_SCANCODE_EQUALS;
	case SDL_SCANCODE_ESCAPE:
		return SG_SCANCODE_ESCAPE;
	case SDL_SCANCODE_F:
		return SG_SCANCODE_F;
	case SDL_SCANCODE_F1:
		return SG_SCANCODE_F1;
	case SDL_SCANCODE_F2:
		return SG_SCANCODE_F2;
	case SDL_SCANCODE_F3:
		return SG_SCANCODE_F3;
	case SDL_SCANCODE_F4:
		return SG_SCANCODE_F4;
	case SDL_SCANCODE_F5:
		return SG_SCANCODE_F5;
	case SDL_SCANCODE_F6:
		return SG_SCANCODE_F6;
	case SDL_SCANCODE_F7:
		return SG_SCANCODE_F7;
	case SDL_SCANCODE_F8:
		return SG_SCANCODE_F8;
	case SDL_SCANCODE_F9:
		return SG_SCANCODE_F9;
	case SDL_SCANCODE_F10:
		return SG_SCANCODE_F10;
	case SDL_SCANCODE_F11:
		return SG_SCANCODE_F11;
	case SDL_SCANCODE_F12:
		return SG_SCANCODE_F12;
	case SDL_SCANCODE_G:
		return SG_SCANCODE_G;
	case SDL_SCANCODE_GRAVE:
		return SG_SCANCODE_GRAVE;
	case SDL_SCANCODE_H:
		return SG_SCANCODE_H;
	case SDL_SCANCODE_HOME:
		return SG_SCANCODE_HOME;
	case SDL_SCANCODE_I:
		return SG_SCANCODE_I;
	case SDL_SCANCODE_INSERT:
		return SG_SCANCODE_INSERT;
	case SDL_SCANCODE_J:
		return SG_SCANCODE_J;
	case SDL_SCANCODE_K:
		return SG_SCANCODE_K;
	case SDL_SCANCODE_KP_0:
		return SG_SCANCODE_KP_0;
	case SDL_SCANCODE_KP_1:
		return SG_SCANCODE_KP_1;
	case SDL_SCANCODE_KP_2:
		return SG_SCANCODE_KP_2;
	case SDL_SCANCODE_KP_3:
		return SG_SCANCODE_KP_3;
	case SDL_SCANCODE_KP_4:
		return SG_SCANCODE_KP_4;
	case SDL_SCANCODE_KP_5:
		return SG_SCANCODE_KP_5;
	case SDL_SCANCODE_KP_6:
		return SG_SCANCODE_KP_6;
	case SDL_SCANCODE_KP_7:
		return SG_SCANCODE_KP_7;
	case SDL_SCANCODE_KP_8:
		return SG_SCANCODE_KP_8;
	case SDL_SCANCODE_KP_9:
		return SG_SCANCODE_KP_9;
	case SDL_SCANCODE_KP_DIVIDE:
		return SG_SCANCODE_KP_DIVIDE;
	case SDL_SCANCODE_KP_ENTER:
		return SG_SCANCODE_KP_ENTER;
	case SDL_SCANCODE_KP_MINUS:
		return SG_SCANCODE_KP_MINUS;
	case SDL_SCANCODE_KP_MULTIPLY:
		return SG_SCANCODE_KP_MULTIPLY;
	case SDL_SCANCODE_KP_PERIOD:
		return SG_SCANCODE_KP_PERIOD;
	case SDL_SCANCODE_KP_PLUS:
		return SG_SCANCODE_KP_PLUS;
	case SDL_SCANCODE_L:
		return SG_SCANCODE_L;
	case SDL_SCANCODE_LEFTBRACKET:
		return SG_SCANCODE_LEFTBRACKET;
	case SDL_SCANCODE_M:
		return SG_SCANCODE_M;
	case SDL_SCANCODE_MINUS:
		return SG_SCANCODE_MINUS;
	case SDL_SCANCODE_N:
		return SG_SCANCODE_N;
	case SDL_SCANCODE_O:
		return SG_SCANCODE_O;
	case SDL_SCANCODE_P:
		return SG_SCANCODE_P;
	case SDL_SCANCODE_PAGEUP:
		return SG_SCANCODE_PAGEUP;
	case SDL_SCANCODE_PAGEDOWN:
		return SG_SCANCODE_PAGEDOWN;
	case SDL_SCANCODE_PAUSE:
		return SG_SCANCODE_PAUSE;
	case SDL_SCANCODE_PERIOD:
		return SG_SCANCODE_PERIOD;
	case SDL_SCANCODE_Q:
		return SG_SCANCODE_Q;
	case SDL_SCANCODE_R:
		return SG_SCANCODE_R;
	case SDL_SCANCODE_RETURN:
		return SG_SCANCODE_RETURN;
	case SDL_SCANCODE_RIGHTBRACKET:
		return SG_SCANCODE_RIGHTBRACKET;
	case SDL_SCANCODE_S:
		return SG_SCANCODE_S;
	case SDL_SCANCODE_SEMICOLON:
		return SG_SCANCODE_SEMICOLON;
	case SDL_SCANCODE_SLASH:
		return SG_SCANCODE_SLASH;
	case SDL_SCANCODE_SPACE:
		return SG_SCANCODE_SPACE;
	case SDL_SCANCODE_T:
		return SG_SCANCODE_T;
	case SDL_SCANCODE_TAB:
		return SG_SCANCODE_TAB;
	case SDL_SCANCODE_U:
		return SG_SCANCODE_U;
	case SDL_SCANCODE_V:
		return SG_SCANCODE_V;
	case SDL_SCANCODE_W:
		return SG_SCANCODE_W;
	case SDL_SCANCODE_X:
		return SG_SCANCODE_X;
	case SDL_SCANCODE_Y:
		return SG_SCANCODE_Y;
	case SDL_SCANCODE_Z:
		return SG_SCANCODE_Z;
	case SDL_SCANCODE_UP:
		return SG_SCANCODE_UP;
	case SDL_SCANCODE_DOWN:
		return SG_SCANCODE_DOWN;
	case SDL_SCANCODE_LEFT:
		return SG_SCANCODE_LEFT;
	case SDL_SCANCODE_RIGHT:
		return SG_SCANCODE_RIGHT;
	case SDL_SCANCODE_RSHIFT:
		return SG_SCANCODE_RSHIFT;
	case SDL_SCANCODE_RCTRL:
		return SG_SCANCODE_RCTRL;
	case SDL_SCANCODE_RALT:
		return SG_SCANCODE_RALT;
	case SDL_SCANCODE_LSHIFT:
		return SG_SCANCODE_LSHIFT;
	case SDL_SCANCODE_LCTRL:
		return SG_SCANCODE_LCTRL;
	case SDL_SCANCODE_LALT:
		return SG_SCANCODE_LALT;
	default:
		break;
	}
	
	return -1;
}

static int
_sg_event_getmbutton(uint8_t b)
{
	switch (b) {
	case SDL_BUTTON_LEFT:
		return SG_BUTTON_LEFT;
	case SDL_BUTTON_MIDDLE:
		return SG_BUTTON_MIDDLE;
	case SDL_BUTTON_RIGHT:
		return SG_BUTTON_RIGHT;
	default:
		break;
	}
	
	return -1;
}

static int
_sg_event_getwinevent(SDL_WindowEventID ev)
{
	switch (ev) {
	case SDL_WINDOWEVENT_SHOWN:
		return SG_WINDOW_SHOWN;
	case SDL_WINDOWEVENT_HIDDEN:
		return SG_WINDOW_HIDDEN;
	case SDL_WINDOWEVENT_EXPOSED:
		return SG_WINDOW_EXPOSED;
	case SDL_WINDOWEVENT_MOVED:
		return SG_WINDOW_MOVED;
	case SDL_WINDOWEVENT_RESIZED:
		return SG_WINDOW_RESIZED;
	case SDL_WINDOWEVENT_SIZE_CHANGED:
		return SG_WINDOW_SIZE_CHANGED;
	case SDL_WINDOWEVENT_MINIMIZED:
		return SG_WINDOW_MINIMIZED;
	case SDL_WINDOWEVENT_MAXIMIZED:
		return SG_WINDOW_MAXIMIZED;
	case SDL_WINDOWEVENT_RESTORED:
		return SG_WINDOW_RESTORED;
	case SDL_WINDOWEVENT_ENTER:
		return SG_WINDOW_ENTER;
	case SDL_WINDOWEVENT_LEAVE:
		return SG_WINDOW_LEAVE;
	case SDL_WINDOWEVENT_FOCUS_GAINED:
		return SG_WINDOW_FOCUS_GAINED;
	case SDL_WINDOWEVENT_FOCUS_LOST:
		return SG_WINDOW_FOCUS_LOST;
	case SDL_WINDOWEVENT_CLOSE:
		return SG_WINDOW_CLOSE;
	case SDL_WINDOWEVENT_TAKE_FOCUS:
		return SG_WINDOW_TAKE_FOCUS;
	default:
		break;
	}
	
	return -1;
}

/*
 * @todo добавить для window event data1 и data2 - например при изменении размера
 */
static void
_sg_event_fill(SDL_Event *e, sg_event_type_t *type, int *data1, int *data2)
{
	switch (e->type) {
	case SDL_QUIT:
		*type = SG_EVENT_QUIT;
		break;
	case SDL_KEYDOWN:
		*type = SG_EVENT_KEYDOWN;
		*data1 = _sg_event_getkey(e->key.keysym.scancode);
		*data2 = e->key.repeat;
		break;
	case SDL_KEYUP:
		*type = SG_EVENT_KEYUP;
		*data1 = _sg_event_getkey(e->key.keysym.scancode);
		break;
	case SDL_MOUSEMOTION:
		*type = SG_EVENT_MOUSEMOTION;
		if (__sg_mousemode__ == 0)
			*data1 = e->motion.x;
		else
			*data1 = e->motion.xrel;
		if (__sg_mousemode__ == 0)
			*data2 = e->motion.y;
		else
			*data2 = e->motion.yrel;
		break;
	case SDL_MOUSEBUTTONDOWN:
		*type = SG_EVENT_MOUSEBUTTONDOWN;
		*data1 = _sg_event_getmbutton(e->button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		*type = SG_EVENT_MOUSEBUTTONUP;
		*data1 = _sg_event_getmbutton(e->button.button);
		break;
	case SDL_MOUSEWHEEL:
		*type = SG_EVENT_MOUSEWHEEL;
		*data1 = e->wheel.x;
		*data2 = e->wheel.y;
		break;
	case SDL_WINDOWEVENT:
		*type = SG_EVENT_WINDOW;
		*data1 = _sg_event_getwinevent(e->window.event);
		break;
	default:
		*type = SG_EVENT_UNKNOWN;
		break;
	}
}

/**
 * @ingroup Events
 * @brief Получить событие 
 *
 * @param[out] type - тип события
 * @param[out] data1 - данные события
 * @param[out] data2 - данные события
 *
 * @return 0 - нет событий, 1 - есть событие
 *
 * Функция убирает первое событие из очереди произошедших событий
 * и заполняет данные об этом событии в указанных переменных.
 * Возможны следующие типы событий и данных:
 *   - type == SG_EVENT_NONE - нет события
 *   - type == SG_EVENT_QUIT - закрытие окна, нажатие ctrl-C
 *     - data1 - не используется
 *     - data2 - не используется
 *   - type == SG_EVENT_KEYDOWN - нажатие клавиши
 *     - data1 - сканкод клавиши (SG_SCANCODE_*)
 *     - data2 - повторное срабатывание (1 если клавиша нажата долгое время)
 *   - type == SG_EVENT_KEYUP - отпускание клавиши
 *     - data1 - сканкод клавиши (SG_SCANCODE_*)
 *     - data2 - не используется
 *   - type == SG_EVENT_MOUSEMOTION - движение мыши
 *     - если режим захвата мыши включен (см. @ref pg_mouse_mode):
 *       - data1 - относительное смещение по x(-1, 0, 1)
 *       - data2 - относительное смещение по y(-1, 0, 1)
 *     - если режим захвата мыши выключен:
 *       - data1 - абсолютная координата по x
 *       - data2 - абсолютная координата по y
 *   - type == SG_EVENT_MOUSEBUTTONDOWN - нажатии кнопки мыши
 *     - data1 - код кнопки (SG_BUTTON_*)
 *     - data2 - не используется
 *   - type == SG_EVENT_MOUSEBUTTONUP - отпускание кнопки мыши
 *     - data1 - код кнопки (SG_BUTTON_*)
 *     - data2 - не используется
 *   - type == SG_EVENT_MOUSEWHEEL - прокрутка колёсика мыши
 *     - data1 - прокрутка по x(-1, 0, 1)
 *     - data2 - прокрутка по y(-1, 0, 1)
 *
 * Пример обработки нажатия клавиши ESCAPE:
 * @code
 * sg_event_type_t etype;
 * int data1, data2;
 *
 * sg_event_poll(&type, &data1, &data2);
 * if ((type == SG_EVENT_KEYDOWN) && (data1 == SG_SCANCODE_ESCAPE)) {
 *   exit(0);
 * }
 * @endcode
 */
int
sg_event_poll(sg_event_type_t *type, int *data1, int *data2)
{
	SDL_Event e;
	
	if (!SDL_PollEvent(&e)) {
		*type = SG_EVENT_NONE;
		return 0;
	}
	_sg_event_fill(&e, type, data1, data2);
	
	return 1;
}

/**
 * @ingroup Events
 * @brief Ждать событие
 *
 * @param[out] type - тип события
 * @param[out] data1 - данные события
 * @param[out] data2 - данные события
 *
 * @return 0 - нет событий, 1 - есть событие
 *
 * Функция убирает первое событие из очереди произошедших событий
 * и заполняет данные об этом событии в указанных переменных.
 * Если событий нет, то функция ждёт пока не появится хотя бы одно.
 * Типы событий и данных см в описании sg_event_poll().
 */
int
sg_event_wait(sg_event_type_t *type, int *data1, int *data2)
{
	SDL_Event e;
	
	if (!SDL_WaitEvent(&e)) {
		*type = SG_EVENT_NONE;
		return 0;
	}
	_sg_event_fill(&e, type, data1, data2);
	
	return 1;
}

/**
 * @ingroup Events
 * @brief Ждать нажатия клавиши q или escape или закрытия окна
 *
 * Функция останавливает выполнение программы до нажатия клавиш
 * q или escape или закрытия окна. После чего выполнение программы
 * продолжается.
 */
void
sg_wait_escape(void)
{
	int running = 1;
	sg_event_type_t etype;
	int edata1 = 0, edata2 = 0;
	
	while (running) {
		sg_event_wait(&etype, &edata1, &edata2);
		if ((etype == SG_EVENT_QUIT) ||
		    ((etype == SG_EVENT_KEYDOWN) &&
		     ((edata1 == SG_SCANCODE_Q) || (edata1 == SG_SCANCODE_ESCAPE))))
			running = 0;
		if (etype == SG_EVENT_WINDOW)
			if ((__sg_spmode__ == 0) &&
			    (__sg_scene_texture_curr__ == __sg_scene__))
				sg_scene_present();
	}
}

/**
 * @ingroup AudioFun
 * @brief Загрузить звук из файла
 *
 * @param fname - имя звукового файла
 *
 * @return звук (после использования должен быть очищен с помощью
 *   sg_sound_free())
 */
sg_sound_t
sg_sound_load(const char *fname)
{
	Mix_Chunk *snd;
	
	snd = Mix_LoadWAV(fname);
	if (!snd) {
		fprintf(stderr, "Ошибка загрузки звука: %s\n", Mix_GetError());
		exit(EXIT_FAILURE);
	}
	return snd;
}

/**
 * @ingroup AudioFun
 * @brief Очистить занимаемую звуком память
 *
 * @param snd - звук
 */
void
sg_sound_free(sg_sound_t snd)
{
	Mix_FreeChunk(snd);
}

/**
 * @ingroup AudioFun
 * @brief Установить уровень громкости для звука
 *
 * @param snd - звук
 * @param volume - уровень громкости в процентах
 */
void
sg_sound_set_volume(sg_sound_t snd, unsigned int volume)
{
	if (volume > 100)
		volume = 100;
	Mix_VolumeChunk(snd, MIX_MAX_VOLUME * volume / 100);
}

/**
 * @ingroup AudioFun
 * @brief Установить уровень громкости для канала
 *
 * @param channel - номер канала
 * @param volume - уровень громкости в процентах
 */
void
sg_achannel_set_volume(int channel, unsigned int volume)
{
	if (volume > 100)
		volume = 100;
	Mix_Volume(channel, MIX_MAX_VOLUME * volume / 100);
}

/**
 * @ingroup AudioFun
 * @brief Проиграть звук на канале
 *
 * @param channel - номер канала (-1 - первый свободный, >=0 - номер канала)
 * @param snd - звук
 * @param times - кол-во раз (0 - бесконечное проигрывание)
 */
void
sg_achannel_play(int channel, sg_sound_t snd, int times)
{
	if (Mix_PlayChannel(channel, snd, times - 1) < 0) {
		fprintf(stderr, "Ошибка проигрывания звука: %s\n", Mix_GetError());
		exit(EXIT_FAILURE);
	}
}

/**
 * @ingroup AudioFun
 * @brief Остановить проигрывание звука на канале
 *
 * @param channel - номер канала
 */
void
sg_achannel_stop(int channel)
{
	Mix_HaltChannel(channel);
}

/**
 * @ingroup AudioFun
 * @brief Проверить занят ли канал проигрыванием какого-либо звука
 *
 * @param channel - номер канала
 *
 * @return 0 - не занят
 * @return 1 - занят
 */
int
sg_achannel_is_playing(int channel)
{
	return Mix_Playing(channel);
}

/**
 * @ingroup AudioFun
 * @brief Загрузить музыку из файла
 *
 * @param fname - имя звукового файла
 *
 * @return музыка (после использования должна быть очищена с помощью
 *   sg_music_free())
 */
sg_music_t
sg_music_load(const char *fname)
{
	Mix_Music *m;
	
	m = Mix_LoadMUS(fname);
	if (!m) {
		fprintf(stderr, "Ошибка загрузки музыки: %s\n", Mix_GetError());
		exit(EXIT_FAILURE);
	}
	return m;
}

/**
 * @ingroup AudioFun
 * @brief Очистить занимаемую музыкой память
 *
 * @param music - музыка
 */
void
sg_music_free(sg_music_t music)
{
	Mix_FreeMusic(music);
}

/**
 * @ingroup AudioFun
 * @brief Установить уровень громкости для музыки
 *
 * @param volume - уровень громкости в процентах
 */
void
sg_music_set_volume(unsigned int volume)
{
	if (volume > 100)
		volume = 100;
	Mix_VolumeMusic(MIX_MAX_VOLUME * volume / 100);
}

/**
 * @ingroup AudioFun
 * @brief Проиграть музыку
 *
 * @param music - музыка
 * @param times - кол-во раз (0 - бесконечное проигрывание)
 */
void
sg_music_play(sg_music_t music, int times)
{
	if (Mix_PlayMusic(music, times - 1) < 0) {
		fprintf(stderr, "Ошибка проигрывания музыки: %s\n", Mix_GetError());
		exit(EXIT_FAILURE);
	}
}

/**
 * @ingroup AudioFun
 * @brief Остановить проигрывание музыки
 */
void
sg_music_stop(void)
{
	Mix_HaltMusic();
}

/**
 * @ingroup AudioFun
 * @brief Проверить проигрывается ли музыка
 *
 * @return 0 - не проигрывается
 * @return 1 - проигрывается
 */
int
sg_music_is_playing(void)
{
	return Mix_PlayingMusic();
}
