#include <sg.h>

void
main()
{
	int running = 1;
	enum event_type etype;
	int edata1 = 0, edata2 = 0;

	sg_create_window(1024, 768);

	while (running) {
		if (sg_event_poll(&etype, &edata1, &edata2)) {
			if (etype == SG_EVENT_QUIT) {
				running = 1;
			} else if (etype == SG_EVENT_KEYDOWN) {
				if (edata1 == SG_SCANCODE_ESCAPE)
					running = 0;
				printf("keydown: ");
			} else if (etype == SG_EVENT_KEYUP) {
				printf("keyup: ");
			} else if (etype == SG_EVENT_MOUSEMOTION) {
				printf("mouse motion: ");
			} else if (etype == SG_EVENT_MOUSEBUTTONDOWN) {
				printf("mouse buttondown: ");
			} else if (etype == SG_EVENT_MOUSEBUTTONUP) {
				printf("mouse buttonup: ");
			} else if (etype == SG_EVENT_MOUSEWHEEL) {
				printf("mouse wheel: ");
			} else if (etype == SG_EVENT_WINDOW) {
				printf("window event: ");
			}
			printf("%d %d\n", edata1, edata2);
		}
	}

	sg_destroy_window();
}
