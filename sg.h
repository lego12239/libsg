/**
 * @file
 * @brief Графическая библиотека
 * @version 1.4.3
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
#ifndef __SG_H__
#define __SG_H__

#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

/**
 * @addtogroup Colors
 * @{
 */
#define SG_COLOR_RED    0xff0000ff
#define SG_COLOR_ORANGE 0xffa500ff
#define SG_COLOR_YELLOW 0xffff00ff
#define SG_COLOR_GREEN  0x00ff00ff
#define SG_COLOR_CYAN   0x00ffffff
#define SG_COLOR_BLUE   0x0000ffff
#define SG_COLOR_VIOLET 0x8a2be2ff
#define SG_COLOR_WHITE  0xffffffff
#define SG_COLOR_BLACK  0x000000ff
#define SG_COLOR_BROWN  0x8b4513ff
#define SG_COLOR_GREY   0x808080ff
#define SG_COLOR_PINK   0xffc0cbff
/**
 * @}
 */

/**
 * @ingroup SceneFun
 * @{
 */
#define SG_RENDERER_ACCELERATED 1
#define SG_RENDERER_PRESENTVSYNC 2
/**
 * @}
 */

/**
 * @ingroup SceneFun
 * @{
 */
enum blend_mode {
	SG_BLENDMODE_NONE,
	SG_BLENDMODE_BLEND,
	SG_BLENDMODE_ADD,
	SG_BLENDMODE_MOD
};
/**
 * @}
 */

#define SG_FLIP_NONE 0
#define SG_FLIP_HORIZONTAL 1
#define SG_FLIP_VERTICAL 2

/**
 * @addtogroup Events
 * @{
 */
enum event_type {
	SG_EVENT_UNKNOWN = -1,
	SG_EVENT_NONE = 0,
	SG_EVENT_QUIT,
	SG_EVENT_KEYDOWN,
	SG_EVENT_KEYUP,
	SG_EVENT_MOUSEMOTION,
	SG_EVENT_MOUSEBUTTONDOWN,
	SG_EVENT_MOUSEBUTTONUP,
	SG_EVENT_MOUSEWHEEL,
	SG_EVENT_WINDOW
};
/**
 * @}
 */

/**
 * @addtogroup Events
 * @{
 */
#define SG_SCANCODE_0 0
#define SG_SCANCODE_1 1
#define SG_SCANCODE_2 2
#define SG_SCANCODE_3 3
#define SG_SCANCODE_4 4
#define SG_SCANCODE_5 5
#define SG_SCANCODE_6 6
#define SG_SCANCODE_7 7
#define SG_SCANCODE_8 8
#define SG_SCANCODE_9 9
#define SG_SCANCODE_A 10
#define SG_SCANCODE_B 11
#define SG_SCANCODE_BACKSLASH 12
#define SG_SCANCODE_BACKSPACE 13
#define SG_SCANCODE_C 14
#define SG_SCANCODE_CAPSLOCK 15
#define SG_SCANCODE_COMMA 16
#define SG_SCANCODE_D 17
#define SG_SCANCODE_DELETE 18
#define SG_SCANCODE_E 20
#define SG_SCANCODE_END 21
#define SG_SCANCODE_EQUALS 22
#define SG_SCANCODE_ESCAPE 23
#define SG_SCANCODE_F 24
#define SG_SCANCODE_F1 25
#define SG_SCANCODE_F2 26
#define SG_SCANCODE_F3 27
#define SG_SCANCODE_F4 28
#define SG_SCANCODE_F5 29
#define SG_SCANCODE_F6 30
#define SG_SCANCODE_F7 31
#define SG_SCANCODE_F8 32
#define SG_SCANCODE_F9 33
#define SG_SCANCODE_F10 34
#define SG_SCANCODE_F11 35
#define SG_SCANCODE_F12 36
#define SG_SCANCODE_G 37
#define SG_SCANCODE_GRAVE 38
#define SG_SCANCODE_H 39
#define SG_SCANCODE_HOME 40
#define SG_SCANCODE_I 41
#define SG_SCANCODE_INSERT 42
#define SG_SCANCODE_J 43
#define SG_SCANCODE_K 44
#define SG_SCANCODE_KP_0 45
#define SG_SCANCODE_KP_1 46
#define SG_SCANCODE_KP_2 47
#define SG_SCANCODE_KP_3 48
#define SG_SCANCODE_KP_4 49
#define SG_SCANCODE_KP_5 50
#define SG_SCANCODE_KP_6 51
#define SG_SCANCODE_KP_7 52
#define SG_SCANCODE_KP_8 53
#define SG_SCANCODE_KP_9 54
#define SG_SCANCODE_KP_DIVIDE 55
#define SG_SCANCODE_KP_ENTER 56
#define SG_SCANCODE_KP_MINUS 57
#define SG_SCANCODE_KP_MULTIPLY 58
#define SG_SCANCODE_KP_PERIOD 59
#define SG_SCANCODE_KP_PLUS 60
#define SG_SCANCODE_L 61
#define SG_SCANCODE_LEFTBRACKET 62
#define SG_SCANCODE_M 63
#define SG_SCANCODE_MINUS 64
#define SG_SCANCODE_N 65
#define SG_SCANCODE_O 66
#define SG_SCANCODE_P 67
#define SG_SCANCODE_PAGEUP 68
#define SG_SCANCODE_PAGEDOWN 69
#define SG_SCANCODE_PAUSE 70
#define SG_SCANCODE_PERIOD 71
#define SG_SCANCODE_Q 72
#define SG_SCANCODE_R 73
#define SG_SCANCODE_RETURN 74
#define SG_SCANCODE_RIGHTBRACKET 75
#define SG_SCANCODE_S 76
#define SG_SCANCODE_SEMICOLON 77
#define SG_SCANCODE_SLASH 78
#define SG_SCANCODE_SPACE 79
#define SG_SCANCODE_T 80
#define SG_SCANCODE_TAB 81
#define SG_SCANCODE_U 82
#define SG_SCANCODE_V 83
#define SG_SCANCODE_W 84
#define SG_SCANCODE_X 85
#define SG_SCANCODE_Y 86
#define SG_SCANCODE_Z 87
#define SG_SCANCODE_UP 88
#define SG_SCANCODE_DOWN 89
#define SG_SCANCODE_LEFT 90
#define SG_SCANCODE_RIGHT 91
#define SG_SCANCODE_RSHIFT 92
#define SG_SCANCODE_RCTRL 93
#define SG_SCANCODE_RALT 94
#define SG_SCANCODE_LSHIFT 95
#define SG_SCANCODE_LCTRL 96
#define SG_SCANCODE_LALT 97
/**
 * @}
 */

/**
 * @addtogroup Events
 * @{
 */
#define SG_BUTTON_LEFT 0
#define SG_BUTTON_MIDDLE 1
#define SG_BUTTON_RIGHT 2
/**
 * @}
 */

/**
 * @addtogroup Events
 * @{
 */
#define SG_WINDOW_SHOWN 0
#define SG_WINDOW_HIDDEN 1
#define SG_WINDOW_EXPOSED 2
#define SG_WINDOW_MOVED 3
#define SG_WINDOW_RESIZED 4
#define SG_WINDOW_SIZE_CHANGED 5
#define SG_WINDOW_MINIMIZED 6
#define SG_WINDOW_MAXIMIZED 7
#define SG_WINDOW_RESTORED 8
#define SG_WINDOW_ENTER 9
#define SG_WINDOW_LEAVE 10
#define SG_WINDOW_FOCUS_GAINED 11
#define SG_WINDOW_FOCUS_LOST 12
#define SG_WINDOW_CLOSE 13
#define SG_WINDOW_TAKE_FOCUS 14
/**
 * @}
 */

typedef uint32_t sg_color_t;
typedef SDL_Texture* sg_texture_t;
typedef Mix_Chunk* sg_sound_t;
typedef Mix_Music* sg_music_t;
typedef enum event_type sg_event_type_t;


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
void sg_create_window(unsigned int width, unsigned int height);

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
int sg_create_window_ext(unsigned int width, unsigned int height,
  unsigned int scene_pmode, unsigned int mouse_mode, unsigned int flags);

/**
 * @ingroup Init
 * @brief Уничтожить созданное окно
 */
void sg_destroy_window(void);

/**
 * @ingroup Init
 * @brief Получить размеры окна
 *
 * @param width - где сохранить ширину
 * @param height - где сохранить высоту
 */
void sg_get_window_size(unsigned int *width, unsigned int *height);

/**
 * @ingroup Init
 * @brief Получить объект window
 *
 * Данный объект может быть использован для вызова SDL-функций, которые требуют его
 * в качестве параметра.
 */
SDL_Window* sg_get_window(void);

/**
 * @ingroup Init
 * @brief Получить объект renderer
 *
 * Данный объект может быть использован для вызова SDL-функций, которые требуют его
 * в качестве параметра.
 */
SDL_Renderer* sg_get_renderer(void);

/**
 * @ingroup Init
 * @brief Получить режим экрана текущего окна
 *
 * @param width - ширина
 * @param height - высота
 * @param refresh_rate - частота обновления экрана (Гц)
 */
void sg_get_window_dispmode(unsigned int *width, unsigned int *height, unsigned int *refresh_rate);

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
void sg_set_color(sg_color_t color);

/**
 * @ingroup SceneMode
 * @brief Отобразить нарисованную сцену
 *
 * Используется в ручном режиме отображения сцены
 *
 * См. @ref pg_scene_present_mode
 */
void sg_scene_present(void);

/**
 * @ingroup SceneFun
 * @brief Устанавливает режим смешивания цветов для рисования фигур
 *
 * @param mode - режим смешивания (@ref pg_blendmode)
 */
void sg_scene_blendmode(enum blend_mode mode);

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
void sg_scene_texture(sg_texture_t texture);

/**
 * @ingroup SceneFun
 * @brief Очистить сцену (залить чёрным цветом)
 */
void sg_scene_clear(void);

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
void sg_draw_point(int x, int y);

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
void sg_draw_line(int x1, int y1, int x2, int y2);

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
 * Пример(Нарисовать прямоугольник с левым верхним углом в координате (50, 100)
 * шириной 80 и высотой 60):
 * @code
 * sg_draw_rect(50, 100, 80, 60);
 * @endcode
 */
void sg_draw_rect(int x, int y, int width, int height);

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
 * Пример(Нарисовать прямоугольник с левым верхним углом в координате (50, 100)
 * шириной 80 и высотой 60):
 * @code
 * sg_draw_filledrect(50, 100, 80, 60);
 * @endcode
 */
void sg_draw_filledrect(int x, int y, int width, int height);

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
void sg_draw_ellipse(int x, int y, int rx, int ry);

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
void sg_draw_filledellipse(int x, int y, int rx, int ry);

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
void sg_draw_circle(int x, int y, int r);

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
void sg_draw_filledcircle(int x, int y, int r);

/**
 * @ingroup OtherFun
 * @brief Пауза
 *
 * @param ms - кол-во миллисекунд паузы
 *
 * Приостановить выполнение программы на указанное кол-во миллисекунд.
 */
void sg_delay(unsigned int ms);

/**
 * @ingroup TextureFun
 * @brief Создать текстуру
 *
 * @param width - ширина текстуры в пикселях
 * @param height - высота текстуры в пикселях
 *
 * @return созданная текстура
 */
sg_texture_t sg_texture_create(int width, int height);

/**
 * @ingroup TextureFun
 * @brief Удалить текстуру
 *
 * @param texture текстура, которую надо удалить
 *
 * После того как текстура больше не нужна, её нужно удалить для
 * освобождения оперативной памяти.
 */
void sg_texture_free(sg_texture_t texture);

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
void sg_texture_info(sg_texture_t texture, int *w, int *h);

/**
 * @ingroup TextureFun
 * @brief Устанавливает режим смешивания цветов при отрисовки текстуры
 *
 * @param texture - текстура
 * @param mode - желаемый режим смешивания цветов для данной текстуры
 *   @ref pg_blendmode
 */
void sg_texture_blendmode(sg_texture_t texture, unsigned int mode);

/**
 * @ingroup TextureFun
 * @brief Установка модификации альфа-канала текстуры
 *
 * @param texture - текстура
 * @param a - значение для операции над альфа-каналом
 *
 * Значение альфа-канала текстуры при отрисовке будет умножено на a/255.
 */
void sg_texture_set_alphamod(sg_texture_t texture, uint8_t a);

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
void sg_texture_set_colormod(sg_texture_t texture, uint8_t r, uint8_t g, uint8_t b);

/**
 * @ingroup DrawFun
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
void sg_draw_texture(sg_texture_t texture, int x, int y);

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
 * Если w равно -1, то ширина для итогового изображения при отрисовке текстуры
 * будет такой, что бы сохранить пропорции изображения. Тоже самое и с высотой.
 * w и h одновременно не могут быть -1.
 */
void sg_draw_texture_ext(sg_texture_t texture, int x, int y, int w, int h, double angle, int flip);

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
void sg_draw_text(const char *font, unsigned int size, unsigned int x, unsigned int y, const char *text, ...);

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
sg_texture_t sg_render_text(const char *font, unsigned int size, const char *text, ...);

/**
 * @ingroup ImgFun
 * @brief Загрузить изображение из файла в текстуру
 *
 * @param fname - имя файла с изображением (png-файл)
 *
 * @return текстура с изображением
 */
sg_texture_t sg_image_load(const char *fname);

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
int sg_event_poll(sg_event_type_t *type, int *data1, int *data2);

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
int sg_event_wait(sg_event_type_t *type, int *data1, int *data2);

/**
 * @ingroup Events
 * @brief Ждать нажатия клавиши q или escape или закрытия окна
 *
 * Функция останавливает выполнение программы до нажатия клавиш
 * q или escape или закрытия окна. После чего выполнение программы
 * продолжается.
 */
void sg_wait_escape(void);

/**
 * @ingroup AudioFun
 * @brief Загрузить звук из файла
 *
 * @param fname - имя звукового файла
 *
 * @return звук (после использования должен быть очищен с помощью
 *   sg_sound_free())
 */
sg_sound_t sg_sound_load(const char *fname);

/**
 * @ingroup AudioFun
 * @brief Очистить занимаемую звуком память
 *
 * @param snd - звук
 */
void sg_sound_free(sg_sound_t snd);

/**
 * @ingroup AudioFun
 * @brief Установить уровень громкости для звука
 *
 * @param snd - звук
 * @param volume - уровень громкости в процентах
 */
void sg_sound_set_volume(sg_sound_t snd, unsigned int volume);

/**
 * @ingroup AudioFun
 * @brief Установить уровень громкости для канала
 *
 * @param channel - номер канала
 * @param volume - уровень громкости в процентах
 */
void sg_achannel_set_volume(int channel, unsigned int volume);

/**
 * @ingroup AudioFun
 * @brief Проиграть звук на канале
 *
 * @param channel - номер канала (-1 - первый свободный, >=0 - номер канала)
 * @param snd - звук
 * @param times - кол-во раз (0 - бесконечное проигрывание)
 */
void sg_achannel_play(int channel, sg_sound_t snd, int times);

/**
 * @ingroup AudioFun
 * @brief Остановить проигрывание звука на канале
 *
 * @param channel - номер канала
 */
void sg_achannel_stop(int channel);

/**
 * @ingroup AudioFun
 * @brief Проверить занят ли канал проигрыванием какого-либо звука
 *
 * @param channel - номер канала
 *
 * @return 0 - не занят
 * @return 1 - занят
 */
int sg_achannel_is_playing(int channel);

/**
 * @ingroup AudioFun
 * @brief Загрузить музыку из файла
 *
 * @param fname - имя звукового файла
 *
 * @return музыка (после использования должна быть очищена с помощью
 *   sg_music_free())
 */
sg_music_t sg_music_load(const char *fname);

/**
 * @ingroup AudioFun
 * @brief Очистить занимаемую музыкой память
 *
 * @param music - музыка
 */
void sg_music_free(sg_music_t music);

/**
 * @ingroup AudioFun
 * @brief Установить уровень громкости для музыки
 *
 * @param volume - уровень громкости в процентах
 */
void sg_music_set_volume(unsigned int volume);

/**
 * @ingroup AudioFun
 * @brief Проиграть музыку
 *
 * @param music - музыка
 * @param times - кол-во раз (0 - бесконечное проигрывание)
 */
void sg_music_play(sg_music_t music, int times);

/**
 * @ingroup AudioFun
 * @brief Остановить проигрывание музыки
 */
void sg_music_stop(void);

/**
 * @ingroup AudioFun
 * @brief Проверить проигрывается ли музыка
 *
 * @return 0 - не проигрывается
 * @return 1 - проигрывается
 */
int sg_music_is_playing(void);


#endif /* __SG_H__ */
