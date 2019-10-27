#include "ei_widgetclass.h"
#include <stdlib.h>
#include <stdio.h>
#ifndef NULL
#define NULL 0
#endif

extern ei_frame_t;
extern void frame_drawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface,
						   ei_rect_t* clipper);
extern void button_drawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface,
						   ei_rect_t* clipper);

extern void toplevel_drawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface,
						   ei_rect_t* clipper);
extern ei_bool_t button_handlefunc(struct ei_widget_t* widget, struct ei_event_t* event);
extern ei_bool_t frame_handlefunc(struct ei_widget_t* widget, struct ei_event_t* event);
extern ei_bool_t toplevel_handlefunc(struct ei_widget_t* widget, struct ei_event_t* event);
void toplevel_releasefunc(struct ei_widget_t*	widget);
void frame_releasefunc(struct ei_widget_t*	widget);
extern void	toplevel_geomnotifyfunc(struct ei_widget_t*	widget,
								  ei_rect_t		rect);
extern void	frame_geomnotifyfunc(struct ei_widget_t*	widget,
									  ei_rect_t		rect);
extern void	button_geomnotifyfunc(struct ei_widget_t*	widget,
									  ei_rect_t		rect);

/********       FRAME CLASS       ********/

void* frame_allocfunc(){
	return calloc(1,160);//hard coded value, bcs can't know ei_frame_t size at compile time
}

void frame_setdefaultsfunc(struct ei_widget_t* widget){
	ei_frame_configure(widget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

void ei_frame_register_class(){
	ei_widgetclass_t frameclass_s;
	frameclass_s.name[0]='f';
	frameclass_s.name[1]='r';
	frameclass_s.name[2]='a';
	frameclass_s.name[3]='m';
	frameclass_s.name[4]='e';
	frameclass_s.name[5]='\0';

	frameclass_s.allocfunc = &frame_allocfunc;
	frameclass_s.releasefunc = &frame_releasefunc;

	frameclass_s.drawfunc =  &frame_drawfunc;
	frameclass_s.setdefaultsfunc = &frame_setdefaultsfunc;
	frameclass_s.geomnotifyfunc = &frame_geomnotifyfunc;

	frameclass_s.handlefunc = &frame_handlefunc;

	frameclass_s.next = NULL;
	ei_widgetclass_register(&frameclass_s);
}



/********       BUTTON CLASS       ********/

void* button_allocfunc() {
	return calloc(1, 176);
}
	
void button_setdefaultsfunc(struct ei_widget_t* widget) {
	ei_button_configure(widget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
						NULL, NULL, NULL, NULL, NULL, NULL);
}

void ei_button_register_class() {
	ei_widgetclass_t button_class;
	button_class.name[0] = 'b';
	button_class.name[1] = 'u';
	button_class.name[2] = 't';
	button_class.name[3] = 't';
	button_class.name[4] = 'o';
	button_class.name[5] = 'n';
	button_class.name[6] = '\0';
	
	button_class.allocfunc = &button_allocfunc;
	button_class.releasefunc = &frame_releasefunc;
	button_class.drawfunc = &button_drawfunc;
	button_class.setdefaultsfunc = &button_setdefaultsfunc;
	button_class.geomnotifyfunc = &button_geomnotifyfunc;
	button_class.handlefunc = &button_handlefunc;
	button_class.next = NULL;
	ei_widgetclass_register(&button_class);
}

/********    Toplevel         *********/

void* toplevel_allocfunc(){
	return calloc(1,128);//hard coded value, bcs can't know ei_toplevel_t size at compile time
}

void toplevel_setdefaultsfunc(struct ei_widget_t* widget){
	ei_toplevel_configure(widget, NULL,  NULL, NULL, NULL, NULL, NULL, NULL);
}

void ei_toplevel_register_class(){
	ei_widgetclass_t toplevel_class;
	toplevel_class.name[0]='t';
	toplevel_class.name[1]='o';
	toplevel_class.name[2]='p';
	toplevel_class.name[3]='l';
	toplevel_class.name[4]='e';
	toplevel_class.name[5]='v';
	toplevel_class.name[6]='e';
	toplevel_class.name[7]='l';
	toplevel_class.name[8]='\0';

	toplevel_class.allocfunc = &toplevel_allocfunc;
	toplevel_class.releasefunc = &toplevel_releasefunc;

	toplevel_class.drawfunc =  &toplevel_drawfunc;
	toplevel_class.setdefaultsfunc = &toplevel_setdefaultsfunc;
	toplevel_class.geomnotifyfunc = &toplevel_geomnotifyfunc;

	toplevel_class.handlefunc = &toplevel_handlefunc;

	toplevel_class.next = NULL;
	ei_widgetclass_register(&toplevel_class);
}


/********    Widgetclass      *********/

ei_widgetclass_t* linked_widgetclasses = NULL;

//dans ei_init, register les 3 widgetclasses
//TODO: not forget to free those classes, see ei_widgetclass_free();
void ei_widgetclass_register(ei_widgetclass_t* widgetclass){
    ei_widgetclass_t* new_widgetclass = calloc(1, sizeof(ei_widgetclass_t));
	*(new_widgetclass) = *(widgetclass);
	
	if(linked_widgetclasses == NULL)linked_widgetclasses = new_widgetclass;

	else{
		ei_widgetclass_t* current_class = linked_widgetclasses;
		while(current_class->next != NULL){
			current_class = current_class->next;
		}
		current_class->next = new_widgetclass;
	}
}

ei_widgetclass_t* ei_widgetclass_from_name(ei_widgetclass_name_t name){
	ei_widgetclass_t* current_class = linked_widgetclasses;
	char* current_name;
	while(current_class != NULL){
		current_name = (char*)&(current_class->name);
		for(int i=0; i<20; i++){
			if(current_name[i]!=name[i]) break;
			else if(name[i]=='\0') return current_class;
		}
		current_class = current_class->next;
	}
	return NULL;
}

//hidden func to free linked_widgetclasses
//has to be called at the end of the app
void ei_widgetclass_free(){
	ei_widgetclass_t* current_class = linked_widgetclasses;
	while(linked_widgetclasses != NULL){
		current_class = linked_widgetclasses->next;
		free(linked_widgetclasses);
		linked_widgetclasses = current_class;
	}
}

