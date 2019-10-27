#include "ei_application.h"
#include <stdio.h>

#ifndef HW_INTERFACE_H
#include "hw_interface.h"
#endif // HW_INTERFACE_H
#ifndef EI_EVENT_H
#include "ei_event.h"
#endif // EI_EVENT_H

extern ei_bool_t is_inside(ei_rect_t rect, ei_point_t p);
extern ei_rect_t intersect_rect(ei_rect_t rect1, ei_rect_t rect2);
extern ei_rect_t union_rect(ei_rect_t rect1, ei_rect_t rect2);
extern void ei_widgetclass_free();
static ei_widget_t* root_widget = NULL;
static ei_linked_rect_t* to_update;

static ei_surface_t* main_window;


void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen){
	hw_init();
	//to_update = (ei_linked_rect_t*) calloc(1, sizeof(ei_linked_rect_t));

	//registering every predefine classes
	ei_frame_register_class();
	ei_button_register_class();
	ei_toplevel_register_class();

	//building of main_window, and of its widget
	main_window = hw_create_window(main_window_size, fullscreen);
	
	if(fullscreen) *(main_window_size) = hw_surface_get_size(main_window);

	root_widget = ei_widget_create("frame", NULL);
}

void ei_app_free(){
	hw_quit();
	ei_widget_destroy(root_widget);
	ei_widgetclass_free(root_widget);
}

ei_bool_t intersect_rect_b(ei_rect_t rect1, ei_rect_t rect2) {
	ei_point_t p1[4];
	p1[0] = rect1.top_left;
	p1[1] = p1[0];
	p1[1].x += rect1.size.width;
	p1[2] = p1[1];
	p1[2].y += rect1.size.height;
	p1[3] = p1[0];
	p1[3].y += rect1.size.height;
	ei_point_t p2[4];
	p2[0] = rect2.top_left;
	p2[1] = p2[0];
	p2[1].x += rect2.size.width;
	p2[2] = p2[1];
	p2[2].y += rect2.size.height;
	p2[3] = p2[0];
	p2[3].y += rect2.size.height;
	for (int i = 0; i < 4; i++) {
		if (is_inside(rect2, p1[i]) || is_inside(rect1, p2[i])) {
			return EI_TRUE;
		}
	}
	return EI_FALSE;
}

void ei_app_invalidate_rect(ei_rect_t* rect) {
	if (!to_update) {
		to_update = calloc(1,sizeof(ei_linked_rect_t));
		to_update->rect = *rect;
	}
	else {
		ei_linked_rect_t* current = to_update;
		while (current->next) {
			if (intersect_rect_b(current->rect, *rect)) {
				current->rect = union_rect(current->rect, *rect);
				return;
			}
			current = current->next;
		}
		if (intersect_rect_b(current->rect, *rect)) {
			current->rect = union_rect(current->rect, *rect);
			return;
		}
		current->next = calloc(1, sizeof(ei_linked_rect_t));
		current = current->next;
		current->rect = *rect;
	}
}

static ei_bool_t running = EI_TRUE;

void ei_app_quit_request() {
	running = EI_FALSE;
}

void ei_do_nothing(void) {
}

void ei_app_run(){
	if(root_widget == NULL){
		puts("No application available, forgot to call ei_app_create() ?\n");
		return;
	}

	ei_rect_t main_rect = hw_surface_get_rect(main_window);
	hw_surface_lock(main_window);
	ei_deep_draw_widget_family(root_widget, main_rect);

	ei_linked_rect_t* to_free_rect = NULL;


	hw_surface_unlock(main_window);
	hw_surface_update_rects(main_window, NULL);

	if (0) {
		// Static mode
		getchar();
	}
	else {


		// The main loop

		// We allocate the space for the events that will pass by.
		ei_event_t* event = calloc(1, sizeof(ei_event_t));
		ei_widget_t* target = NULL;
		ei_widget_t* child_target = NULL;
		ei_widget_t* child_iter = NULL;
		ei_default_handle_func_t def = NULL;

		while (running) {
			hw_event_wait_next(event);
			hw_surface_lock(main_window);
			if (event->type == ei_ev_mouse_buttondown || event->type == ei_ev_mouse_buttonup) {
				ei_do_nothing();
			}
			switch (event->type)
			{
				// All the events that can change the active widget / use position
			case ei_ev_mouse_buttondown:
			case ei_ev_mouse_buttonup:
			case ei_ev_mouse_move:
				target = ei_event_get_active_widget();
				if (target) {
					// There is an active widget
					target->wclass->handlefunc(target, event);
						if (event->type == ei_ev_mouse_buttonup) {
							ei_event_set_active_widget(NULL);
						}
				}
				else {
					// we need to find the top-front widget handling this event.
					child_target = root_widget;
					while (child_target) {
						target = child_target;
						child_target = NULL;
						if (is_inside(*(target->content_rect), event->param.mouse.where)) {
							child_iter = target->children_head;
							while (child_iter) {
								if (is_inside(child_iter->screen_location, event->param.mouse.where)) {
									child_target = child_iter;
								}
								child_iter = child_iter->next_sibling;
							}
						}
					}
					ei_bool_t found = EI_FALSE;
					while (!found && target) {
						found = target->wclass->handlefunc(target, event);
						if (!found) {
							target = target->parent;
						}
					}
					if (!found) {
						def = ei_event_get_default_handle_func();
						if (def) {
							def(event);
						}
					}
					// Try calling its handler_func. Or the one of its parent if its does not give a f***...
					// Else try ei_default_handle_func
					// But don't forget, you must set its top_level host on top of its siblings (recursively) no matter what!
				}
				break;
				// All the events that will ignore which widget is active
			case ei_ev_app:
			case ei_ev_keydown:
			case ei_ev_keyup:
				// Nothing else to do here ...
				def = ei_event_get_default_handle_func();
				if (def) {
					def(event);
				}
				break;
			default:
				break;
			}
			hw_surface_unlock(main_window);
			if (to_update) {
				hw_surface_update_rects(main_window, to_update);
				while (to_update) {
					to_free_rect = to_update->next;
					free(to_update);
					to_update = to_free_rect;
				}
			}
		}
		free(event);
		while (to_update) {
			to_free_rect = to_update->next;
			free(to_update);
			to_update = to_free_rect;
		}
	}
}

//hidden func, draws the hierarchy of widgets in right order (en profondeur)
void ei_deep_draw_widget_family(ei_widget_t* widget, ei_rect_t true_parent_content_rect){
	ei_widget_t* child_widget = widget->children_head;
	
	if(widget->screen_location.size.width == 0 || widget->screen_location.size.height == 0) return;

	widget->wclass->geomnotifyfunc(widget, widget->screen_location);
	
	widget->wclass->drawfunc(widget, main_window, NULL, &true_parent_content_rect);

	true_parent_content_rect = intersect_rect(*(widget->content_rect), true_parent_content_rect);


	
	while(child_widget != NULL){
		if(child_widget->placer_params != NULL){

			ei_placer_run(child_widget);
			ei_deep_draw_widget_family(child_widget, true_parent_content_rect);
		}
		child_widget = child_widget->next_sibling;
	}
}

ei_widget_t* ei_app_root_widget(){
	return root_widget;
}

ei_surface_t ei_app_root_surface(){
	return main_window;
}

