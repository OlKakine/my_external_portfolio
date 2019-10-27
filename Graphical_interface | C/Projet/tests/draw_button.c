#include <stdio.h>
#include <stdlib.h>

#include "ei_application.h"
#include "ei_event.h"
#include "hw_interface.h"
#include "ei_widget.h"
#include "ei_placer.h"

/*
 * ei_main --
 *
 *	Main function of the application.
 */
int ei_main(int argc, char** argv)
{
	ei_size_t	screen_size		= {600, 600};
	ei_color_t	root_bgcol		= {0x52, 0x7f, 0xb4, 0xff};

	
	ei_widget_t*	button;
	int		button_x			= 200;
	int		button_y			= 200;
	int button_height = 100;
	int button_width = 200;
	ei_color_t	button_color		= {200, 20, 20, 255};
	ei_relief_t	button_relief		= ei_relief_raised;
	int radius = 10;
	int border = 6;
 
	/* Create the application and change the color of the background. */
	ei_app_create(&screen_size, EI_FALSE);
	/* ei_frame_configure(ei_app_root_widget(), NULL, &root_bgcol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL); */

	/* Create, configure and place the frame on screen. */
	button = ei_widget_create("button", ei_app_root_widget());

	ei_surface_t img = hw_image_load("misc/klimt.jpg", ei_app_root_surface());

	char* text = "hello world";
	ei_button_configure (button, NULL, &button_color, &border, &radius, &button_relief, &text,
						 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	ei_place(button, NULL, &button_x, &button_y, &button_width, &button_height, NULL, NULL, NULL, NULL);
	ei_placer_run(button);
	/* Run the application's main loop. */
	ei_app_run();

	/* We just exited from the main loop. Terminate the application (cleanup). */
	ei_app_free();

	return (EXIT_SUCCESS);
}
