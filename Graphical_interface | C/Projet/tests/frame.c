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

	ei_widget_t*	frame;
	ei_size_t	frame_size		= {500,500};
	int		frame_x			= 100;
	int		frame_y			= 100;
	ei_color_t	frame_color		= {0x20,0x20, 0xE0, 0xff};
	ei_relief_t	frame_relief		= ei_relief_none;
	int		frame_border_width	= 6;
	ei_anchor_t anchor = ei_anc_south;
	
	/* Create the application and change the color of the background. */
	ei_app_create(&screen_size, EI_FALSE);
	ei_frame_configure(ei_app_root_widget(), NULL, &root_bgcol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);


	/* Create an image */	
	ei_surface_t img = hw_image_load("misc/klimt.jpg", ei_app_root_surface());
	ei_rect_t img_rect = {{200,200}, {200,200}};
	ei_rect_t *p_img_rect = &img_rect;
	
	/* Create, configure and place the frame on screen. */
	frame = ei_widget_create("frame", ei_app_root_widget());
	char* text = "hello world";
	ei_frame_configure	(frame, &frame_size, &frame_color,
				 &frame_border_width, &frame_relief, &text, NULL, NULL, &anchor,
				 NULL, NULL, NULL);
	/* ei_frame_configure	(frame, &frame_size, &frame_color, */
	/* 			 &frame_border_width, &frame_relief, NULL, NULL, NULL, NULL, */
	/* 					 &img, &p_img_rect,  &anchor); */

    ei_place(frame, NULL ,&frame_x, &frame_y, NULL, NULL,NULL, NULL, NULL, NULL );
	ei_placer_run(frame);

	/* Run the application's main loop. */
	ei_app_run();

	/* /\* We just exited from the main loop. Terminate the application (cleanup). *\/ */
	ei_widget_destroy(frame);
	ei_app_free();
	hw_surface_free(img);


	//my tests for testing frame.c
	/* ei_widget_t* frame2; */
	
	/* frame_register_class(); */
	/* frame = ei_widget_create("frame", NULL); */
	/* frame2 = ei_widget_create("frame", frame); */
	/* ei_widget_destroy(frame); */
	/* ei_widget_destroy(frame2); */
	/* ei_widgetclass_free(); */

	
	return (EXIT_SUCCESS);
}
