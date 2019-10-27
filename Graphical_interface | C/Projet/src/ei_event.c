#include "ei_event.h"

static ei_widget_t* current_widget;

void ei_event_set_active_widget(ei_widget_t* widget) {
	current_widget = widget;
}

ei_widget_t* ei_event_get_active_widget() {
	return current_widget;
}

static ei_default_handle_func_t def_func;

void ei_event_set_default_handle_func(ei_default_handle_func_t func) {
	def_func = func;
}

ei_default_handle_func_t ei_event_get_default_handle_func() {
	return def_func;
}
