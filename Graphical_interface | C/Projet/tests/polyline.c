#include <stdlib.h>

#include "ei_types.h"
#include "ei_main.h"
#include "ei_event.h"
#include "ei_utils.h"
#include "ei_draw.h"
#include "hw_interface.h"

int ei_main(int argc, char** argv)
{
	ei_surface_t			main_window		= NULL;
	ei_size_t			main_window_size	= ei_size(640, 480);
	ei_event_t			event;
	uint32_t			white			= 0xffffffff;
	uint32_t*			pixel_ptr;
	int				i;

	// Init acces to hardware.
	hw_init();

	// Create the main window.
	main_window = hw_create_window(&main_window_size, EI_FALSE);

	// Lock the surface for drawing, fill in white, unlock, update screen.
	hw_surface_lock(main_window);

	ei_point_t point1 = {1,1};
	ei_point_t point2 = {300,300}; 
	ei_linked_point_t linked_point2 = {point2, NULL};	
	ei_linked_point_t linked_point1 = {point1, &linked_point2};
	ei_color_t color = {0x80, 0x80, 0x80, 0xFF};
	
	ei_draw_polyline(main_window, &linked_point1, color, NULL);

	ei_draw_text(main_window, &point1, "hello world!", NULL, &color, NULL);
	
	hw_surface_unlock(main_window);
	hw_surface_update_rects(main_window, NULL);

	// Wait for a key press.
	event.type = ei_ev_none;
	while (event.type != ei_ev_keydown)
		hw_event_wait_next(&event);

	// Free hardware resources.
	hw_quit();

	// Terminate program with no error code.
	return 0;
}
