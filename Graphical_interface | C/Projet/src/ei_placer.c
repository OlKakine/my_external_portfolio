#ifndef EI_TYPES_H
#include "ei_types.h"
#endif // EI_TYPES_H
#ifndef EI_WIDGET_H
#include "ei_widget.h"
#endif // EI_WIDGET_H
#include "ei_placer.h"
#ifndef NULL
#define NULL 0
#endif


void			ei_place(struct ei_widget_t* widget,
	ei_anchor_t* anchor,
	int* x,
	int* y,
	int* width,
	int* height,
	float* rel_x,
	float* rel_y,
	float* rel_width,
	float* rel_height) {


	// Had the widget been given placer_params?
	if (!widget->placer_params) {
		widget->placer_params = calloc(1,sizeof(ei_placer_params_t));
	}


	// Setting given values / default values

	if (anchor) {
		widget->placer_params->anchor_data = *anchor;
		widget->placer_params->anchor = &(widget->placer_params->anchor_data);
	}
	else {
		widget->placer_params->anchor_data = ei_anc_northwest;
		widget->placer_params->anchor = NULL;
	}


	if (x) {
		widget->placer_params->x_data = *x;
		widget->placer_params->x = &(widget->placer_params->x_data);
	}
	else {
		widget->placer_params->x_data = 0;
		widget->placer_params->x = NULL;
	}


	if (y) {
		widget->placer_params->y_data = *y;
		widget->placer_params->y = &(widget->placer_params->y_data);
	}
	else {
		widget->placer_params->y_data = 0;
		widget->placer_params->y = NULL;
	}
	

	if (height) {
		widget->placer_params->h_data= *height;
		widget->placer_params->h = &(widget->placer_params->h_data);
	}
	else {
		if (rel_height) {
			widget->placer_params->h_data = 0;
		}
		else {
			widget->placer_params->h_data = widget->requested_size.height;
		}
		widget->placer_params->h = NULL;
	}


	if (width) {
		widget->placer_params->w_data = *width;
		widget->placer_params->w = &(widget->placer_params->w_data);
	}
	else {
		if (rel_width) {
			widget->placer_params->w_data = 0;
		}
		else {
			widget->placer_params->w_data = widget->requested_size.width;
		}
		widget->placer_params->w = NULL;
	}
	

	if (rel_x) {
		widget->placer_params->rx_data = *rel_x;
		widget->placer_params->rx = &(widget->placer_params->rx_data);
	}
	else {
		widget->placer_params->rx_data = 0.0;
		widget->placer_params->rx = NULL;
	}


	if (rel_y) {
		widget->placer_params->ry_data = *rel_y;
		widget->placer_params->ry = &(widget->placer_params->ry_data);
	}
	else {
		widget->placer_params->ry_data = 0.0;
		widget->placer_params->ry = NULL;
	}


	if (rel_height) {
		widget->placer_params->rh_data = *rel_height;
		widget->placer_params->rh = &(widget->placer_params->rh_data);
	}
	else {
		widget->placer_params->rh_data = 0.0;
		widget->placer_params->rh = NULL;
	}


	if (rel_width) {
		widget->placer_params->rw_data = *rel_width;
		widget->placer_params->rw = &(widget->placer_params->rw_data);
	}
	else {
		widget->placer_params->rw_data = 0.0;
		widget->placer_params->rw = NULL;
	}
}



void ei_placer_run(struct ei_widget_t* widget) {

	/* Since we've set the default values in the data fields in ei_place, we don't need the pointers anymore... */

	// Parent's size

	int hp, wp;
	hp = widget->parent->content_rect->size.height;
	wp = widget->parent->content_rect->size.width;

	// Widget size and position

	int h, w;
	h = widget->placer_params->h_data + (int)(((float)hp) * widget->placer_params->rh_data);
	w = widget->placer_params->w_data + (int)(((float)wp) * widget->placer_params->rw_data);
	int x, y;
	x = widget->placer_params->x_data + (int)(((float)hp) * widget->placer_params->rx_data);
	y = widget->placer_params->y_data + (int)(((float)wp) * widget->placer_params->ry_data);
	x += widget->parent->content_rect->top_left.x;
	y += widget->parent->content_rect->top_left.y;

	// Anchors

	switch (widget->placer_params->anchor_data)
	{
	case ei_anc_north:
		x -= w >> 1;
		break;
	case ei_anc_northeast:
		x -= w;
		break;
	case ei_anc_east:
		x -= w;
		y -= h >> 1;
		break;
	case ei_anc_southeast:
		x -= w;
		y -= h;
		break;
	case ei_anc_south:
		x -= w >> 1;
		y -= h;
		break;
	case ei_anc_southwest:
		y -= h;
		break;
	case ei_anc_west:
		y -= h >> 1;
		break;
	case ei_anc_center:
		x -= w >> 1;
		y -= h >> 1;
		break;
	default:
		break;
	}

	// Writing position in the widget's screen location

	widget->screen_location.size.height = h;
	widget->screen_location.size.width = w;
	widget->screen_location.top_left.x = x;
	widget->screen_location.top_left.y = y;

	/* ei_widget_t* child = widget->children_head; */
	/* while (child) { */
	/* 	ei_placer_run(child); */
	/* 	child = child->next_sibling; */
	/* } */

}

void ei_placer_forget(struct ei_widget_t* widget) {


	// Freeing its placer_params

	free(widget->placer_params);
	widget->placer_params = NULL;

	// Making it disapears

	widget->screen_location.size.height = 0;
	widget->screen_location.size.width = 0;


}
