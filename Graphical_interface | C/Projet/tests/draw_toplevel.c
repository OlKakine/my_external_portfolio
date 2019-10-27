#include <stdio.h>
#include <stdlib.h>

#include "ei_application.h"
#include "ei_event.h"
#include "hw_interface.h"
#include "ei_widget.h"
#include "ei_draw.h"


/*
 * ei_main --
 *
 *	Main function of the application.
 */
int ei_main(int argc, char** argv)
{
	ei_size_t	screen_size		= {600, 600};
	ei_color_t	root_bgcol		= {0x52, 0x7f, 0xb4, 0xff};

	ei_widget_t*	toplevel;
	ei_size_t	toplevel_size		= {400,400};
	int		toplevel_x			= 100;
	int		toplevel_y			= 0;
	ei_color_t	toplevel_color		= {0x20,0x20, 0xE0, 0xff};
	ei_relief_t	toplevel_relief		= ei_relief_none;
	int		toplevel_border_width	= 6;
	char* toplevel_title = "Test";
	ei_anchor_t anchor = ei_anc_center;
	ei_bool_t bo = EI_TRUE;
	
	/* Create the application and change the color of the background. */
	ei_app_create(&screen_size, EI_FALSE);
	ei_frame_configure(ei_app_root_widget(), NULL, &root_bgcol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);


	/* Create, configure and place the toplevel on screen. */
	toplevel = ei_widget_create("toplevel", ei_app_root_widget());

	ei_toplevel_configure	(toplevel, &toplevel_size, NULL,
							 &toplevel_border_width, &toplevel_title, &bo, NULL, NULL);

    ei_place(toplevel, NULL ,&toplevel_x, &toplevel_y, NULL, NULL,NULL, NULL, NULL, NULL );
	ei_placer_run(toplevel);

	ei_widget_t*	button;
	int		button_x			= 200;
	int		button_y			= 200;
	int button_height = 200;
	int button_width = 200;
	ei_color_t	button_color		= {200, 20, 20, 255};
	ei_relief_t	button_relief		= ei_relief_raised;
	int radius = 99;
	int border = 10;
	button = ei_widget_create("button", toplevel);

	ei_surface_t img = hw_image_load("misc/klimt.jpg", ei_app_root_surface());

	char* text = "hello world";
	ei_button_configure (button, NULL, &button_color, &border, &radius, &button_relief, NULL,
						 NULL, NULL, &anchor, &img, NULL, NULL, NULL, NULL);
	ei_place(button, NULL, &button_x, &button_y, &button_width, &button_height, NULL, NULL, NULL, NULL);

	//frame
	ei_widget_t* frame;
	frame = ei_widget_create("frame", toplevel);
	ei_anchor_t frame_anchor = ei_anc_south;
	ei_size_t	frame_size		= {300,300};
	ei_color_t	frame_color		= {20, 200, 20, 255};
	
	int		frame_x			= 0;
	int		frame_y			= 0;


	ei_frame_configure	(frame, &frame_size, &frame_color,
				 NULL, NULL, NULL, NULL, NULL, &frame_anchor,
				 NULL, NULL, NULL);
	/* ei_frame_configure	(frame, &frame_size, &frame_color, */
	/* 			 NULL, NULL, NULL, NULL, NULL, NULL, */
	/* 					 &img, NULL,  &frame_anchor); */

    ei_place(frame, NULL ,&frame_x, &frame_y, NULL, NULL,NULL, NULL, NULL, NULL );

	/* Run the application's main loop. */
	ei_app_run();

	/* /\* We just exited from the main loop. Terminate the application (cleanup). *\/ */
	ei_widget_destroy(toplevel);
	ei_widget_destroy(frame);
	ei_widget_destroy(button);
	hw_surface_free(img);
	ei_app_free();
	
	
	return (EXIT_SUCCESS);
}
