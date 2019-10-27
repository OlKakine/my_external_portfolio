#include "ei_widget.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#ifndef EI_APPLICATION_H
#include "ei_application.h"
#endif // EI_APPLICATION_H
#ifndef EI_EVENT_H
#include "ei_event.h"
#endif // EI_EVENT_H
#ifndef EI_UTILS_H
#include "ei_utils.h"
#endif // EI_UTILS_H


#ifndef NULL
#define NULL 0
#endif
#define M_PI 3.14159265358979323846
#define square(a)  (a)*(a)

extern ei_widget_t* ei_app_root_widget();
extern ei_surface_t ei_app_root_surface();
extern void			ei_fill			(ei_surface_t		surface,
						 const ei_color_t*	color,
						 const ei_rect_t*	clipper);
extern ei_rect_t intersect_rect(ei_rect_t rect1, ei_rect_t rect2);
extern ei_rect_t union_rect(ei_rect_t rect1, ei_rect_t rect2);
static ei_size_t toplevel_default_min_size = {160,120};

//TODO: enregistrer les rect a update

extern ei_rect_t union_rect(ei_rect_t rect1, ei_rect_t rect2);
extern void ei_deep_draw_widget_family(ei_widget_t* widget, ei_rect_t true_parent_content_rect);

typedef struct ei_frame_t{
	ei_widget_t widget;
	ei_color_t color;
	int border_width;
	ei_relief_t relief;
	char* text;
	ei_font_t text_font;
	
	ei_color_t		text_color;
	ei_anchor_t		text_anchor;
	
	ei_surface_t		img;
	ei_rect_t*		img_rect;
	ei_anchor_t		img_anchor;
} ei_frame_t;

typedef struct ei_button_t{
	ei_widget_t widget;
	ei_color_t color;
	int border_width;
	ei_relief_t relief;
	char* text;
	ei_font_t text_font;
	
	ei_color_t		text_color;
	ei_anchor_t		text_anchor;
	
	ei_surface_t		img;
	ei_rect_t*		img_rect;
	ei_anchor_t		img_anchor;

	int corner_radius;
	ei_callback_t callback;
	void* user_param;
} ei_button_t;

typedef struct ei_toplevel_t{
	ei_widget_t widget;
	ei_color_t		color;
	int			border_width;
	char*			title;
	ei_bool_t		closable;
	ei_axis_set_t		resizable;
	ei_size_t*		min_size;
} ei_toplevel_t;

ei_bool_t is_inside(ei_rect_t rect, ei_point_t p) {
	if (rect.size.width == 0 || rect.size.height == 0) {
		return 0;
	}
	return (p.x >= rect.top_left.x && p.x <= (rect.top_left.x + rect.size.width) && p.y >= rect.top_left.y && p.y <= (rect.top_left.y + rect.size.height));
}

ei_widget_t* ei_widget_create(ei_widgetclass_name_t class_name, ei_widget_t* parent){

	ei_widgetclass_t* wclass = ei_widgetclass_from_name(class_name);
	if(wclass == NULL){
		printf("Error, %s is not a class name.\n", (char*) class_name);
		return NULL;		
	}
	ei_widget_t* widget = wclass->allocfunc();

	//default parameters common to every widgets
	
	widget->wclass = wclass;
	//pick_id
	widget->pick_color =  (ei_color_t*) &(widget->pick_id);

	if(parent != NULL){
		widget->parent = parent;
		if(parent->children_head == NULL){
			parent->children_head = widget;
			parent->children_tail = widget;
		}
		else{
			parent->children_tail->next_sibling = widget;
			parent->children_tail = widget;
		}
	}
	else{
		widget->screen_location = hw_surface_get_rect(ei_app_root_surface());
	}

	//those params shouldn't be initialized (tabun)
	//placer_params
	//screen_location
	//requested_size

	widget->content_rect = &(widget->screen_location);
	
	//default parameters specific to the widget class
	widget->wclass->setdefaultsfunc(widget);
	
	return widget;
}

void ei_widget_destroy(ei_widget_t* widget){
	ei_widget_t* child = widget->children_head;
	while (child) {
		ei_widget_t* sibling = child->next_sibling;
		ei_widget_destroy(child);
		child = sibling;
	}
	if(widget->wclass->releasefunc != NULL)
		widget->wclass->releasefunc(widget);
	if(widget->content_rect != &widget->screen_location)
		free(widget->content_rect);
	if (widget->parent){
		ei_widget_t* current = widget->parent->children_head;
		if (current == widget) {
			if (current == widget->parent->children_tail)
				widget->parent->children_tail = NULL;
			widget->parent->children_head = widget->next_sibling;
		}
		else {
			ei_widget_t* prev = NULL;
			while (current != widget) {
				prev = current;
				current = current->next_sibling;
			}
			prev->next_sibling = current->next_sibling;
			if (current == widget->parent->children_tail)
				widget->parent->children_tail = prev;
		}
	}
	
	free(widget);	

}












/**************************        FRAME          **************************/












void frame_releasefunc(struct ei_widget_t*	widget){
	ei_frame_t* frame = (ei_frame_t*) widget;
	if(frame->text != NULL) free(frame->text);
	if(frame->img_rect != NULL) free(frame->img_rect);
}

void ei_frame_configure(ei_widget_t* widget, ei_size_t*	requested_size,
						const ei_color_t* color, int* border_width,
						ei_relief_t* relief, char**text, ei_font_t* text_font,
						ei_color_t* text_color, ei_anchor_t* text_anchor,
						ei_surface_t* img, ei_rect_t** img_rect,
						ei_anchor_t* img_anchor){

	//TODO: free les malloc de text et img_rect

	ei_frame_t* frame = (ei_frame_t*) widget;

	if(color == NULL){
		if( *((uint32_t*) &(frame->color)) == 0)
			frame->color = ei_default_background_color;
	}		
	else frame->color = *(color);

	if(border_width != NULL) frame->border_width = *(border_width);
	
	if(relief != NULL) frame->relief = *(relief);

	if(text != NULL) {
		if(frame->text != NULL) free(frame->text);
		frame->text = calloc(1, strlen(*text) + 1);
		strcpy(frame->text, *text);
	}

	if(text_font == NULL){
		if(frame->text_font == NULL)
			frame->text_font = ei_default_font;
	}
	else frame->text_font = *(text_font);

	if(text_color == NULL){
		if( *((uint32_t*) &(frame->text_color)) == 0)
			frame->text_color = ei_font_default_color;
	} 
	else frame->text_color = *(text_color);

	if(text_anchor == NULL){
		if( frame->text_anchor == ei_anc_none)
			frame->text_anchor = ei_anc_center;
	}		
	else frame->text_anchor = *(text_anchor);

	if(img != NULL) frame->img = *(img);

	if(img_rect != NULL) {
		if(frame->img_rect != NULL) free(frame->img_rect);
		frame->img_rect = calloc(1, sizeof(ei_rect_t));
		*(frame->img_rect) = **img_rect;
	}

	if(img_anchor == NULL){		
		if(frame->img_anchor == ei_anc_none)
			frame->img_anchor = ei_anc_center;
	}		
	else frame->img_anchor = *(img_anchor);

	if(requested_size == NULL){
		if( *((uint64_t*) &(widget->requested_size)) == 0 ){
			if(frame->text != NULL){
				hw_text_compute_size(*text, frame->text_font, &(widget->requested_size.width), &(widget->requested_size.height));
			}
			    
			else if(frame->img != NULL){
				if(img_rect != NULL)
					widget->requested_size = (*img_rect)->size;
				else
					widget->requested_size = hw_surface_get_size(frame->img);
			}
			int border_width_x2 = frame->border_width << 1;
			widget->requested_size.width += border_width_x2;
			widget->requested_size.height += border_width_x2;
		} 
	} 
	else widget->requested_size = *(requested_size);
}

//returns the top_left point where to anchor
ei_point_t where_to_anchor(ei_rect_t rect_disponible, ei_size_t taille_widget, ei_anchor_t anchor){
	ei_size_t taille_disponible = rect_disponible.size;
	ei_point_t top_left = rect_disponible.top_left;

	//si les 2 compo de la size du widget ne sont pas plus grande, on retourne le top_left
	if(taille_disponible.width < taille_widget.width || taille_disponible.height < taille_widget.height) return top_left;

	// Widget size and position

	int h_d, w_d;
	h_d = taille_disponible.height;
	w_d = taille_disponible.width;

	int h_w = taille_widget.height;
	int w_w = taille_widget.width;

	int x = top_left.x;
	int y = top_left.y;
	int x_c = x + w_d/2;
	int y_c = y + h_d/2;

	// Anchors

	switch (anchor)
	{
	case ei_anc_north:
		x = x_c - w_w/2;
		break;
	case ei_anc_northeast:
		x += w_d - w_w;
		break;
	case ei_anc_east:
		x += w_d - w_w;
		y = y_c - h_w/2;
		break;
	case ei_anc_southeast:
		x += w_d - w_w;
		y += h_d - h_w;
		break;
	case ei_anc_south:
		x = x_c - w_w/2;
		y += h_d - h_w; 
		break;
	case ei_anc_southwest:
		y += h_d - h_w;
		break;
	case ei_anc_west:
		y = y_c - h_w/2;
		break;
	case ei_anc_center:
		x = x_c - w_w/2;
		y = y_c - h_w/2;
		break;
	default:
		break;
	}

	ei_point_t final_top_left = {x, y};
	return final_top_left;	
}

void frame_drawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface,
					ei_rect_t* clipper){

	ei_frame_t* frame = (ei_frame_t*) widget;
	ei_rect_t final_clipper;
	ei_rect_t widget_clipper = widget->screen_location;
	ei_rect_t true_content_rect = *(widget->content_rect);

	if(clipper != NULL)	final_clipper = intersect_rect(*(clipper), widget_clipper);
	else final_clipper = widget_clipper;

	ei_point_t point_tr = {widget_clipper.top_left.x + widget_clipper.size.width, widget_clipper.top_left.y};
	ei_point_t point_bl = {widget_clipper.top_left.x, widget_clipper.top_left.y + widget_clipper.size.height};
	ei_point_t point_tl = widget_clipper.top_left;
	ei_point_t point_br ={point_tr.x, point_bl.y};
	
	ei_linked_point_t linked_point4 = {point_br, NULL};
	ei_linked_point_t linked_point3 = {point_tr, &linked_point4};
	ei_linked_point_t linked_point2 = {point_tl, &linked_point3};
	ei_linked_point_t linked_point1 = {point_bl, &linked_point2};
	
	if(frame->border_width > 0){
		int border = frame->border_width;
		int border_x2 = border << 1;

		point_tr.x -= border;
		point_br.x -= border;
		point_tl.x += border;
		point_bl.x += border;
		point_tr.y += border;
		point_br.y -= border;
		point_tl.y += border;
		point_bl.y -= border;
		ei_linked_point_t linked_point8 = {point_br, NULL};
		ei_linked_point_t linked_point7 = {point_tr, &linked_point8};
		ei_linked_point_t linked_point6 = {point_tl, &linked_point7};
		ei_linked_point_t linked_point5 = {point_bl, &linked_point6};
		ei_draw_polygon(surface, &linked_point5, frame->color, &final_clipper);

		linked_point3.next = &linked_point7;
		linked_point7.next = &linked_point6;
		linked_point6.next = &linked_point5;
		linked_point5.next = NULL;

		ei_color_t color = frame->color;
		
		ei_color_t dark = {(int) (0.5*color.red),(int) (0.5*color.green),(int) (0.5*color.blue), color.alpha};
		ei_color_t light = {color.red + (int) (0.25*(255 - color.red)), color.green + (int) (0.25*(255 - color.green)),
							color.blue + (int) (0.25*(255 - color.blue)), color.alpha};
		
		ei_color_t bas = light; 
		ei_color_t haut = light;
		if (frame->relief == 1) {
			haut = light;
			bas = dark;
		}
		if (frame->relief == 2) {
			haut = dark;
			bas = light;
		}
		
		ei_draw_polygon(surface, &linked_point1, haut, &final_clipper);
			
		linked_point1.next = &linked_point4;
		linked_point4.next = &linked_point3;
		linked_point7.next = &linked_point8;
		linked_point8.next = &linked_point5;

		ei_draw_polygon(surface, &linked_point1, bas, &final_clipper);

		final_clipper.top_left.x += border;
		final_clipper.top_left.y += border;
		final_clipper.size.width -= border_x2;
		final_clipper.size.height -= border_x2;

		true_content_rect.top_left.x += border;
		true_content_rect.top_left.y += border;
		true_content_rect.size.width -= border_x2;
		true_content_rect.size.height -= border_x2;
    
	}
	else ei_draw_polygon(surface, &linked_point1, frame->color, &final_clipper);

	if(frame->img != NULL){
		ei_surface_t img_surface = frame->img;
		
		hw_surface_lock(img_surface);
		ei_size_t img_size;
		if(frame->img_rect != NULL) img_size = frame->img_rect->size;
		else img_size = hw_surface_get_size(img_surface);		

		ei_point_t where = where_to_anchor(true_content_rect, img_size , frame->img_anchor);
		ei_rect_t ideal_clipper = {where, img_size};
		ei_rect_t true_available_widget_clipper = intersect_rect(true_content_rect, hw_surface_get_rect(surface));
		ei_rect_t feasible_widget_clipper = intersect_rect(ideal_clipper, true_available_widget_clipper);
		feasible_widget_clipper = intersect_rect(*clipper, feasible_widget_clipper);
		ei_rect_t feasible_img_clipper = {{0,0}, feasible_widget_clipper.size};
		if(frame->img_rect != NULL){
			feasible_img_clipper.top_left = frame->img_rect->top_left;
			feasible_img_clipper = intersect_rect(feasible_img_clipper, *(frame->img_rect));
			feasible_widget_clipper.size = feasible_img_clipper.size;
		}
		
		ei_copy_surface(surface, &feasible_widget_clipper, img_surface, &feasible_img_clipper, EI_TRUE);
		hw_surface_unlock(img_surface);		
	}
	else if(frame->text != NULL){
		ei_size_t widget_size;
		hw_text_compute_size(frame->text, frame->text_font, &widget_size.width, &widget_size.height);
		
		ei_point_t where = where_to_anchor(true_content_rect, widget_size , frame->text_anchor);
		ei_rect_t ideal_clipper = {where, widget_size};
		ei_rect_t true_available_widget_clipper = intersect_rect(true_content_rect, hw_surface_get_rect(surface));
		ei_rect_t feasible_widget_clipper = intersect_rect(ideal_clipper, true_available_widget_clipper);
		feasible_widget_clipper = intersect_rect(*clipper, feasible_widget_clipper);
		ei_draw_text(surface, &where, frame->text, frame->text_font, &(frame->text_color), &feasible_widget_clipper);		
	}	
}








/***********************            BUTTON          ***********************/









void ei_button_configure (ei_widget_t* widget, ei_size_t* requested_size,
						  const ei_color_t* color, int* border_width, int* corner_radius,
						  ei_relief_t* relief, char** text, ei_font_t* text_font,
						  ei_color_t* text_color, ei_anchor_t* text_anchor, ei_surface_t* img,
						  ei_rect_t** img_rect, ei_anchor_t*	img_anchor,
						  ei_callback_t* callback, void**	user_param) {	
	ei_frame_configure (widget, requested_size, color, border_width, relief, text, text_font,
						text_color, text_anchor, img, img_rect, img_anchor);
	ei_button_t* button = (ei_button_t*) widget;
	if (border_width == NULL) {
		if (button->border_width == 0)
			button->border_width = k_default_button_border_width;
	}
	
	if (relief == NULL){
		if (button->relief == 0) 
			button->relief = ei_relief_raised;
	}

	if (corner_radius == NULL){
		if (button->corner_radius == 0)
			button->corner_radius = k_default_button_corner_radius;
	}
	else button->corner_radius = *(corner_radius);

	if (callback != NULL)
		button->callback = *(callback);

	if (user_param != NULL)
		button->user_param = *(user_param);
}


/** Prend en argument le point du centre, le rayon,les angles de début et de fin en rad, un pointeur vers le suivant du dernier point si nécessaire  
 * Renvoie le pointeur vers le premier point lié
 */
ei_linked_point_t* arc(ei_point_t center, int radius, double start_angle, double end_angle, ei_linked_point_t* next_of_last_point) {
	ei_point_t first_point;
	first_point.x = (int)((double)radius*cos(start_angle)) + center.x;
	first_point.y = (int)((double)radius*sin(start_angle)) + center.y;
	ei_point_t last_point;
	last_point.x = (int)((double) radius*cos(end_angle) + center.x);
	last_point.y = (int)((double) radius*sin(end_angle) + center.y);
	int gauche = 0;
	if (start_angle < 3*M_PI/2 && start_angle >= M_PI/2) gauche = 1;
	int sens = (first_point.y) < (last_point.y); /* 1 on augmente y, 0 on diminue y */
	int y = first_point.y + ((sens) ? 1: -1);
	int nb_elem = abs(first_point.y - last_point.y) + 1;
	ei_linked_point_t* pts = NULL;
	/* pts = calloc(nb_elem, sizeof(ei_linked_point_t)); */
	pts = calloc(1, sizeof(ei_linked_point_t));
	pts->point = first_point;
	ei_linked_point_t* current = pts;
	int i;
	int x;
	for (i = 1; i < nb_elem - 1; i++) {
		x = (int) floor(sqrt(square(radius) - square(y - center.y))*((gauche) ? -1: 1) + center.x);
		ei_linked_point_t* new = NULL;
		new = calloc(1, sizeof(ei_linked_point_t));
		new->point.x = x;
		new->point.y = y;
		current->next = new;
		current = new;
		y = y + ((sens) ? 1: -1);
	}
	ei_linked_point_t* last = NULL;
	last = calloc(1, sizeof(ei_linked_point_t));
	last->point = last_point;
	current->next = last;
	last->next = next_of_last_point;
	return pts;
}

/* choix de faire que la partie haute, que la partie basse  pour tout faire */
typedef enum {ALL = 0, HIGH = 1, LOW = 2}part_to_draw;


ei_linked_point_t* rounded_frame(ei_rect_t rect, part_to_draw part, int radius){ 
	int rect_width = rect.size.width;
	int rect_height = rect.size.height;
	int x = rect.top_left.x;
	int y = rect.top_left.y;
	int r = radius;
	ei_point_t* centers = (ei_point_t*) calloc(4, sizeof(ei_point_t));
	for (int i = 0; i < 4; i++) {
		centers[i].x = x + r*(i%2 ? -1 :1) + (i%2)*rect_width;
		centers[i].y = y + r*(i<2 ? 1 :-1) + (i/2)*rect_height;
	}
	if (part == 1) {
		/* point en haut à droite */
		ei_linked_point_t* third_part = arc(centers[1], r, (double) 3*M_PI/2, (double) 7*M_PI/4, NULL);
		/* point en haut à gauche */
		ei_linked_point_t* second_part = arc(centers[0], r, (double) M_PI, (double) 3*M_PI/2, third_part);
		/* on part du point en bas à gauche */
		ei_linked_point_t* first_part = arc(centers[2], r, (double) 3*M_PI/4, (double) M_PI, second_part);
		free(centers);
		return first_part;
		
	}
	if (part == 2) {
		/* point en bas à gauche */
		ei_linked_point_t* third_part = arc(centers[2], r, (double) M_PI/2, (double) 3*M_PI/4, NULL);
		/* point en bas à droite */
		ei_linked_point_t* second_part = arc(centers[3], r, (double) 0, (double) M_PI/2, third_part);
		/* on part d'en haut à droite */
		ei_linked_point_t* first_part = arc(centers[1], r, (double) 7*M_PI/4, (double) 0, second_part);
		free(centers);
		return first_part;
	}
	else {
		ei_linked_point_t* fourth_part = arc(centers[3], r, (double) 0,(double) M_PI/2, NULL);
		ei_linked_point_t* third_part = arc(centers[1], r, (double) 3*M_PI/2, (double) 0, fourth_part);
		ei_linked_point_t* second_part = arc(centers[0], r, (double) M_PI, (double) 3*M_PI/2, third_part);
		ei_linked_point_t* first_part = arc(centers[2], r, (double) M_PI/2, (double) M_PI, second_part);
		free(centers);
		return first_part;
	}
}



/* supprime une liste chainée de points en prenant en arguments un pointeur sur le premier point lié */
void free_linked_point(ei_linked_point_t* first_point) {
	ei_linked_point_t* current = first_point;
	while (current->next != NULL) {
		ei_linked_point_t* next = current->next;
		free(current);
		current = next;
	}
	free(current);
}

/*** fonction de dessin du bouton ***/

void button_drawfunc(ei_widget_t* widget, ei_surface_t  surface,
						   ei_surface_t  pick_surface, ei_rect_t* clipper) {
	part_to_draw high = HIGH;
	part_to_draw low = LOW;
	part_to_draw all = ALL;
	ei_rect_t location = widget->screen_location;
	int h = (location.size.height < location.size.width ? location.size.height : location.size.width)/2;
	ei_button_t* button = (ei_button_t*) widget;
	ei_color_t color = button->color;
	ei_color_t color_low;
	ei_color_t color_high;
	ei_color_t dark = {(int) (0.5*color.red),(int) (0.5*color.green),(int) (0.5*color.blue), color.alpha};
	ei_color_t light = {color.red + (int) (0.25*(255 - color.red)), color.green + (int) (0.25*(255 - color.green)),
						color.blue + (int) (0.25*(255 - color.blue)), color.alpha};
	if (button->relief == 1) {
		color_high = light;
		color_low = dark;
	}
	if (button->relief == 2) {
		color_high = dark;
		color_low = light;
	}
	
	int border = button->border_width;
	int radius = button->corner_radius;
	if (radius == 1) radius = 2;
	/* point h1 = point milieu bouton droit */
	ei_linked_point_t point_h1;
	point_h1.point.x = location.top_left.x + location.size.width - h;
	point_h1.point.y = location.top_left.y + h;
	/* point h0 = point milieu bouton gauche */
	ei_linked_point_t point_h0;
	point_h0.point.x = location.top_left.x + h;
	point_h0.point.y = location.top_left.y + location.size.height - h;
	ei_linked_point_t* frame;
	
	/***** dessin cadre haut ******/
	
	frame = rounded_frame(location, high, radius);
	point_h0.next = frame;
	point_h1.next = &point_h0;
	ei_draw_polygon(surface, &point_h1, color_high, clipper);
	free_linked_point(frame);
	

	/***** dessin cadre bas *****/
	
	frame = rounded_frame(location, low, radius);
	point_h1.next = frame;
	point_h0.next = &point_h1;
	ei_draw_polygon(surface, &point_h0, color_low, clipper);
	free_linked_point(frame);
	

	/***** dessin cadre intérieur *****/
	
	ei_rect_t inside_frame = {
		{location.top_left.x + border, location.top_left.y + border}, /* top_left */
		{location.size.width - 2*border, location.size.height - 2*border} /* size */
	};
	frame = rounded_frame(inside_frame, all, border < radius ? radius - border : 0);
	ei_draw_polygon(surface, frame, color, clipper);
	free_linked_point(frame);

	ei_rect_t true_content_rect = *(widget->content_rect);

	if(button->img != NULL){
		ei_surface_t img_surface = button->img;
		
		hw_surface_lock(img_surface);
		ei_size_t img_size;
		if(button->img_rect != NULL) img_size = button->img_rect->size;
		else img_size = hw_surface_get_size(img_surface);

		ei_point_t where = where_to_anchor(true_content_rect, img_size , button->img_anchor);
		ei_rect_t ideal_clipper = {where, img_size};
		ei_rect_t true_available_widget_clipper = intersect_rect(true_content_rect, hw_surface_get_rect(surface));
		ei_rect_t feasible_widget_clipper = intersect_rect(ideal_clipper, true_available_widget_clipper);
		feasible_widget_clipper = intersect_rect(*clipper, feasible_widget_clipper);
		ei_rect_t feasible_img_clipper = {{0,0}, feasible_widget_clipper.size};
		
		if(button->img_rect != NULL){
			feasible_img_clipper.top_left = button->img_rect->top_left;
			feasible_img_clipper = intersect_rect(feasible_img_clipper, *(button->img_rect));
			feasible_widget_clipper.size = feasible_img_clipper.size;
		}
		
		ei_copy_surface(surface, &feasible_widget_clipper, img_surface, &feasible_img_clipper, EI_TRUE);
		hw_surface_unlock(img_surface);		
	}
	else if(button->text != NULL){
		ei_size_t widget_size;
		hw_text_compute_size(button->text, button->text_font, &widget_size.width, &widget_size.height);
		
		ei_point_t where = where_to_anchor(true_content_rect, widget_size , button->text_anchor);
		ei_rect_t ideal_clipper = {where, widget_size};
		ei_rect_t surface_rect = hw_surface_get_rect(surface);
		ei_rect_t true_available_widget_clipper = intersect_rect(true_content_rect, surface_rect);
		ei_rect_t feasible_widget_clipper = intersect_rect(ideal_clipper, true_available_widget_clipper);
		feasible_widget_clipper = intersect_rect(*clipper, feasible_widget_clipper);
		ei_draw_text(surface, &where, button->text, button->text_font, &(button->text_color), &feasible_widget_clipper);		
	}
}












/**************         TOPLEVEL      *******************/














void toplevel_releasefunc(struct ei_widget_t*	widget){
	ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;
	if(toplevel->title != NULL) free(toplevel->title);
}

void			ei_toplevel_configure		(ei_widget_t*		widget,
							 ei_size_t*		requested_size,
							 ei_color_t*		color,
							 int*			border_width,
							 char**			title,
							 ei_bool_t*		closable,
							 ei_axis_set_t*		resizable,
											 ei_size_t**		min_size){
	ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;

	if(color == NULL){
		if( *((uint32_t*) &(toplevel->color)) == 0)
			toplevel->color = ei_default_background_color;
	}		
	else toplevel->color = *(color);

	if(border_width != NULL) toplevel->border_width = *(border_width);
	else if(toplevel->border_width == 0) toplevel->border_width = 4;
	
	if(title != NULL){
		if(toplevel->title != NULL) free(toplevel->title);
		toplevel->title = calloc(1, strlen(*title)+1);
		strcpy(toplevel->title, *title);
	} 
	else if(toplevel->title == NULL){
		toplevel->title = calloc(1, 9);
		strcpy(toplevel->title, "Toplevel");
	}

	if(requested_size == NULL){
		if( *((uint64_t*) &(widget->requested_size)) == 0 ){
			widget->requested_size.width = 320;
			widget->requested_size.height = 240;
		} 
	} 
	else {
		widget->requested_size = *(requested_size);
		widget->requested_size.width += toplevel->border_width * 2;
		widget->requested_size.height += 30 + toplevel->border_width;		
	}

	if(closable != NULL) toplevel->closable = *closable;
	else if(toplevel->closable == 0) toplevel->closable = EI_TRUE;

	if(resizable != NULL) toplevel->resizable = *resizable;
	else if(toplevel->resizable == ei_axis_none) toplevel->resizable = ei_axis_both;

	if(min_size != NULL) toplevel->min_size = *(min_size);
	else if(toplevel->min_size != NULL) return;
	else toplevel->min_size = &toplevel_default_min_size;
}

void toplevel_drawfunc(ei_widget_t* widget, ei_surface_t  surface,
					 ei_surface_t  pick_surface, ei_rect_t* clipper){
	ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;
	
	ei_color_t	frame_color	= {0x20,0x20, 0xE0, 0xff};
	int title_bar_size = 30;
	int border = toplevel->border_width;
	int border_x2 = border << 1;

	ei_rect_t final_clipper;
	ei_rect_t widget_clipper = widget->screen_location;
	ei_rect_t true_content_rect = *(widget->content_rect);

	if(clipper != NULL)	final_clipper = intersect_rect(*(clipper), widget_clipper);
	else final_clipper = widget_clipper;

	ei_point_t point_tr_title = {widget_clipper.top_left.x + widget_clipper.size.width, widget_clipper.top_left.y};
	ei_point_t point_tl_title = widget_clipper.top_left;	
	ei_point_t point_bl_title = {widget_clipper.top_left.x, widget_clipper.top_left.y + title_bar_size};
	ei_point_t point_br_title ={point_tr_title.x, point_bl_title.y};
	
	ei_linked_point_t linked_point4 = {point_br_title, NULL};
	ei_linked_point_t linked_point3 = {point_tr_title, &linked_point4};
	ei_linked_point_t linked_point2 = {point_tl_title, &linked_point3};
	ei_linked_point_t linked_point1 = {point_bl_title, &linked_point2};

	//on trace la title bar
	ei_draw_polygon(surface, &linked_point1, frame_color, &final_clipper);
	
	ei_point_t point_bl_frame = {widget_clipper.top_left.x, widget_clipper.top_left.y + widget_clipper.size.height};
	ei_point_t point_br_frame = {point_tr_title.x, point_bl_frame.y};

	ei_linked_point_t linked_point5 = {point_br_frame, NULL};
	ei_linked_point_t linked_point6 = {point_bl_frame, &linked_point1};
	linked_point1.next = &linked_point4;
	linked_point4.next = &linked_point5;

	
	true_content_rect.top_left.y += title_bar_size;
	true_content_rect.size.height -= border + title_bar_size;

	//on trace le fond de la true content rect
	ei_draw_polygon(surface, &linked_point6, toplevel->color, &final_clipper);

	ei_point_t point_tl_resize = point_br_frame;
	point_tl_resize.x -= 8 + border_x2;
	point_tl_resize.y -= 8 + border_x2;
	ei_point_t point_tr_resize = {point_tr_title.x, point_tl_resize.y};
	ei_point_t point_bl_resize = {point_tl_resize.x, point_bl_frame.y};

	ei_linked_point_t linked_point13 = {point_bl_resize, NULL};
	linked_point5.next = &linked_point13;
	ei_linked_point_t linked_point12 = {point_tr_resize, &linked_point5};
	ei_linked_point_t linked_point11 = {point_tl_resize, &linked_point12};

	//on trace le carre de resizement
	if(toplevel->resizable != 0)ei_draw_polygon(surface, &linked_point11, frame_color, &final_clipper);
	
	if(border > 0){		
		ei_point_t point_tl_cont = point_bl_title;
		point_tl_cont.x += border;
		ei_point_t point_tr_cont = point_br_title;
		point_tr_cont.x -= border;
		ei_point_t point_br_cont = {point_tr_cont.x, point_br_frame.y - border};
		ei_point_t point_bl_cont = {point_tl_cont.x, point_br_cont.y};

		ei_linked_point_t linked_point8 = {point_tr_cont, &linked_point4};
		ei_linked_point_t linked_point9 = {point_br_cont, &linked_point8};
		ei_linked_point_t linked_point10 = {point_bl_cont, &linked_point9};
		ei_linked_point_t linked_point7 = {point_tl_cont, &linked_point10};
		linked_point1.next = &linked_point7;
		linked_point5.next = &linked_point6;
		linked_point6.next = NULL;

		ei_draw_polygon(surface, &linked_point1, frame_color, &final_clipper);			    
	}
	

	ei_widget_t*	button;
	ei_color_t	button_color		= {200, 20, 20, 255};
	ei_relief_t	button_relief		= ei_relief_raised;
	int radius = 9;
	border = 1;
	button = ei_widget_create("button", NULL);
	ei_button_configure (button, NULL, &button_color, &border, &radius, &button_relief, NULL,
						 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	ei_rect_t button_location = {{point_tl_title.x + 8, point_tl_title.y + 4},{20,20}};
	button->screen_location = button_location;
	if(toplevel->closable == EI_TRUE) button_drawfunc(button, surface, NULL, &final_clipper);

	//TODO: create a white font
	ei_point_t text_tl = button_location.top_left;
	text_tl.x+= radius <<2;
	text_tl.y = point_tl_title.y;
	ei_draw_text(surface, &text_tl , toplevel->title, ei_default_font, &ei_font_default_color, &final_clipper);
}

ei_bool_t set_front_toplevel(ei_widget_t* widget) {
	ei_widget_t* starting_w = widget;
	while (widget && strcmp(widget->wclass->name, "toplevel")) {
		widget = widget->parent;
	}
	if (widget) {
		ei_widget_t* parent = widget->parent;
		if (widget && parent->children_tail != widget) {
			ei_widget_t* first_sibling = parent->children_head;
			// do we use the "next_sibling" field? / Do we actually need to update it?
			if (first_sibling == widget) {
				parent->children_head = widget;
			}
			else {
				while (first_sibling->next_sibling != widget) {
					first_sibling = first_sibling->next_sibling;
				}
				first_sibling->next_sibling = widget->next_sibling;
			}
			parent->children_tail->next_sibling = widget;
			parent->children_tail = widget;
			widget->next_sibling = NULL;
		}
	}
	if (!widget) {
		return EI_FALSE;
	}
	ei_bool_t has_toplevel_parent = set_front_toplevel(widget->parent);
	if (!has_toplevel_parent) {
		ei_deep_draw_widget_family(starting_w->parent, intersect_rect(starting_w->screen_location, hw_surface_get_rect(ei_app_root_surface())));
		ei_rect_t rect = intersect_rect(starting_w->screen_location, hw_surface_get_rect(ei_app_root_surface()));
		ei_app_invalidate_rect(&rect);
	}
	return EI_TRUE;
}








/**************         HANDLEFUNC       *******************/










ei_bool_t frame_handlefunc(ei_widget_t* frame, ei_event_t* event) {
	// We will only receive mouse events here ... and frames doesn't have to give a f*** about mice.
	return EI_FALSE;
}

ei_bool_t toplevel_handlefunc(ei_widget_t* widget, ei_event_t* event) {
	ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;
	static ei_point_t last_mouse_pos;
	static ei_rect_t last_pos;
	static int status = 0;

	ei_rect_t rect_quit = widget->screen_location;
	rect_quit.top_left.x += 8; //hard coded values, see toplevel_drawfunc
	rect_quit.top_left.x += 4;
	rect_quit.size.width = 20;
	rect_quit.size.height = 20;

	int rect_resize_width = 8 + toplevel->border_width * 2;
	ei_point_t rect_resize_point = widget->screen_location.top_left;
	rect_resize_point.x += widget->screen_location.size.width - rect_resize_width;
	rect_resize_point.y += widget->screen_location.size.height - rect_resize_width;
	ei_rect_t rect_resize = {rect_resize_point, {rect_resize_width, rect_resize_width}};

	ei_rect_t rect_title_bar = widget->screen_location;
	rect_title_bar.size.height = 30;
		
	ei_rect_t rect;

	if (event->type == ei_ev_mouse_buttonup && ei_event_get_active_widget()) {
		// This the active top level and the user released the mouse key.		
		if (is_inside(rect_quit, event->param.mouse.where)) {
			// What should we actually do? Just delete the widget without telling anyone???
			ei_widget_t* parent = widget->parent;
			ei_widget_destroy(widget);
			rect = intersect_rect(last_pos, hw_surface_get_rect(ei_app_root_surface()));
			ei_deep_draw_widget_family(parent, rect);
			ei_app_invalidate_rect(&rect);

			
		}
		ei_event_set_active_widget(NULL);
	}
	else {
		if (event->type == ei_ev_mouse_buttondown) {
			//The user started pressing the mouse key
			if (is_inside(rect_quit, event->param.mouse.where)) {
				status = 0;
				// We should redraw the exit button.
			}
			else {
				if (is_inside(rect_resize, event->param.mouse.where)) {
					status = 1;
				}
				else {
					if (is_inside(rect_title_bar, event->param.mouse.where)) {
						status = 2;
					}
				}
			}
			ei_event_set_active_widget(widget);
			// It must become the first top_level of all its siblings
		}
		else {
			if (event->type == ei_ev_mouse_move && ei_event_get_active_widget()) {
				ei_point_t delta = ei_point_sub(event->param.mouse.where, last_mouse_pos);
				switch (status)
				{
				case 0:	// Pressing the quit button
					// Well, nothing to do actually...
					break;
				case 1:	// Resizing

					// Needs to handle the resize limits (Where are they?)
					if (((ei_toplevel_t*)widget)->resizable == ei_axis_x || ((ei_toplevel_t*)widget)->resizable == ei_axis_both) {
						widget->placer_params->w_data += delta.x;
						if (widget->placer_params->w_data < ((ei_toplevel_t*)widget)->min_size->width) {
							widget->placer_params->w_data = ((ei_toplevel_t*)widget)->min_size->width;
						}
					}
					if (((ei_toplevel_t*)widget)->resizable == ei_axis_y || ((ei_toplevel_t*)widget)->resizable == ei_axis_both) {
						widget->placer_params->h_data += delta.y;
						if (widget->placer_params->h_data < ((ei_toplevel_t*)widget)->min_size->height) {
							widget->placer_params->h_data = ((ei_toplevel_t*)widget)->min_size->height;
						}
					}
					ei_placer_run(widget);
					rect = intersect_rect(union_rect(last_pos, widget->screen_location), hw_surface_get_rect(ei_app_root_surface()));
					ei_deep_draw_widget_family(widget->parent, rect);
					ei_app_invalidate_rect(&rect);
					break;
				case 2:	// Moving

					// Needs to handle the limits of movement (mouse still inside the parent's content_rect?)
					widget->placer_params->x_data += delta.x;
					widget->placer_params->y_data += delta.y;
					ei_placer_run(widget);
					rect = intersect_rect(union_rect(last_pos, widget->screen_location), hw_surface_get_rect(ei_app_root_surface()));
					ei_deep_draw_widget_family(widget->parent,rect);
					ei_app_invalidate_rect(&rect);
					break;
				default:
					break;
				}
			}
		}
	}
	if (ei_event_get_active_widget()) {
		last_mouse_pos = event->param.mouse.where;
		last_pos = widget->screen_location;
	}
	return EI_TRUE;
}


ei_bool_t button_handlefunc(ei_widget_t* widget, ei_event_t* event) {
	static ei_bool_t inside = EI_TRUE;
	static ei_bool_t active = EI_FALSE;
	static ei_point_t last_mouse_location;
	if (active) {
		switch (event->type) {
		case ei_ev_mouse_buttonup:
			if (inside) {
				((ei_button_t*) widget)->relief = ei_relief_raised;
				ei_deep_draw_widget_family(widget, intersect_rect(widget->screen_location,
																  hw_surface_get_rect(ei_app_root_surface())));
				ei_rect_t rect = intersect_rect(widget->screen_location,
												hw_surface_get_rect( ei_app_root_surface() ));
				ei_app_invalidate_rect(&rect);
				ei_event_set_active_widget(NULL);
				ei_callback_t func = ((ei_button_t*)widget)->callback;
				if (func) {
					func(widget, event, ((ei_button_t*)widget)->user_param);
				}
				active = EI_FALSE;
				return EI_TRUE;
			}
			else {
				ei_event_set_active_widget(NULL);
				return EI_TRUE;
			}
			active = EI_FALSE;
		case ei_ev_mouse_move:
			if ( is_inside (widget->screen_location, event->param.mouse.where ) &&
				 !is_inside (widget->screen_location, last_mouse_location) ) {
				inside = EI_TRUE;
				((ei_button_t*) widget)->relief = ei_relief_sunken;
				ei_deep_draw_widget_family(widget, intersect_rect(widget->screen_location,
																  hw_surface_get_rect(ei_app_root_surface())));
				ei_rect_t rect =  intersect_rect(widget->screen_location,
												 hw_surface_get_rect( ei_app_root_surface() ));
				ei_app_invalidate_rect(&rect);
				last_mouse_location = event->param.mouse.where;
				return EI_TRUE;
			}
			if ( !is_inside (widget->screen_location, event->param.mouse.where ) &&
				 is_inside (widget->screen_location, last_mouse_location) ) {
				inside = EI_FALSE;
				((ei_button_t*)widget)->relief = ei_relief_raised;
				ei_deep_draw_widget_family(widget, intersect_rect(widget->screen_location,
																  hw_surface_get_rect(ei_app_root_surface())));
				ei_rect_t rect = intersect_rect(widget->screen_location,
												hw_surface_get_rect( ei_app_root_surface() ));
				ei_app_invalidate_rect( &rect);
				last_mouse_location = event->param.mouse.where;
				return EI_TRUE;
			}
			else {
				last_mouse_location = event->param.mouse.where;
				return EI_TRUE; 
			}
		default:
			return EI_TRUE;
		}
	}
	else {
		switch (event->type) {
		case ei_ev_mouse_buttondown:
			((ei_button_t*) widget)->relief = ei_relief_sunken;
			ei_event_set_active_widget(widget);
			active = EI_TRUE;
			last_mouse_location = event->param.mouse.where;
			if ( !set_front_toplevel(widget)) {
				ei_deep_draw_widget_family(widget, intersect_rect(widget->screen_location,
					hw_surface_get_rect(ei_app_root_surface())));
				ei_rect_t rect = intersect_rect(widget->screen_location,
					hw_surface_get_rect(ei_app_root_surface()));
				ei_app_invalidate_rect(&rect);
			}
			return EI_TRUE;
		case ei_ev_mouse_buttonup:
		case ei_ev_mouse_move:
			return EI_TRUE;
		default:
			return EI_TRUE;
		}
	}
}






/**************         GEOMNOTIFYFUNCS       *******************/









void	button_geomnotifyfunc(struct ei_widget_t*	widget,
											 ei_rect_t		rect){
	ei_button_t* button = (ei_button_t*) widget;
	int radius = button->corner_radius;
	int magical_nb = (int) radius*cos(M_PI/4);

	ei_rect_t true_content_rect = widget->screen_location;
	
	true_content_rect.top_left.x += magical_nb;
	true_content_rect.top_left.y += magical_nb;
	true_content_rect.size.width -= magical_nb << 1;
	true_content_rect.size.height -= magical_nb << 1;

	if(widget->content_rect == &widget->screen_location)
		widget->content_rect = calloc(1, sizeof(ei_rect_t));
		
	*(widget->content_rect) = true_content_rect;
}

void	frame_geomnotifyfunc(struct ei_widget_t*	widget,
								ei_rect_t		rect){
	ei_toplevel_t* frame = (ei_frame_t*) widget;	
	ei_rect_t true_content_rect = widget->screen_location;
	int border = frame->border_width;
	int border_x2 = border << 1;
	
	true_content_rect.top_left.x += border;
	true_content_rect.top_left.y += border;
	true_content_rect.size.width -= border_x2;
	true_content_rect.size.height -= border_x2;

	if(widget->content_rect == &widget->screen_location)
		widget->content_rect = calloc(1, sizeof(ei_rect_t));
		
	*(widget->content_rect) = true_content_rect;
}
void	toplevel_geomnotifyfunc(struct ei_widget_t*	widget,
								ei_rect_t		rect){
	ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;
	ei_rect_t true_content_rect = widget->screen_location;
	
	int border = toplevel->border_width;
	int border_x2 = border << 1;
	int title_bar_size = 30;
	
	true_content_rect.top_left.y += title_bar_size;
	true_content_rect.size.height -= border + title_bar_size;

	if(border > 0){		
		true_content_rect.top_left.x += border;
		true_content_rect.size.width -= border_x2;			    
	}
	
	if(widget->content_rect == &widget->screen_location)
			widget->content_rect = calloc(1, sizeof(ei_rect_t));
		
	   	*(widget->content_rect) = true_content_rect;
}
