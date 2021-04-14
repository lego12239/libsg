#include "libsg/sg.h"

void
main()
{
	sg_create_window(200, 400);

	sg_wait_escape();
	sg_destroy_window();
}
