#include "ei_draw.h"
#ifndef EI_UTILS_H
#include "ei_utils.h"
#include <stdlib.h>
#endif // EI_UTILS_H

#ifndef NULL
#define NULL 0
#endif


uint32_t ei_map_rgba(ei_surface_t surface, const ei_color_t * color) {
	int ir, ig, ib, ia;
	hw_surface_get_channel_indices(surface, &ir, &ig, &ib, &ia);
	return (uint32_t)color->red << (8 * ir) | color->green << (8 * ig) | color->blue << (8 * ib) | (ia >= 0 ? color->alpha << (8 * ia) : 0);
}

void ei_draw_polyline(ei_surface_t surface, const ei_linked_point_t* first_point,
	const ei_color_t color, const ei_rect_t* clipper) {

	if (!first_point) return;

	//dans tous les cas, on va tracer les polylines sur surface

	ei_surface_t destination_surface = NULL;

	ei_size_t size = hw_surface_get_size(surface);
	int x_max = size.width;
	int y_max = size.height;
	int x_min = x_max;
	int y_min = y_max;
	ei_linked_point_t* p_linked_point = first_point;

	ei_bool_t need_offscreen = (clipper != NULL);
	//true si on doit clipper, ou si la figure depasse par en bas ou a droite

	//on cherche a connaitre la potentielle taille de l'offscreen
	do {
		ei_point_t point = p_linked_point->point;

		if (point.x > x_max) x_max = point.x;
		else if (point.x < x_min) x_min = point.x;
		if (point.y > y_max) y_max = point.y;
		else if (point.y < y_min) y_min = point.y;

		p_linked_point = p_linked_point->next;
	} while (p_linked_point != NULL);

	//si la figure depasse et que l'on a un clipper NULL, on creer un nouveau clipper
	ei_bool_t depasse_screen = (x_max > size.width || y_max > size.height);
	ei_rect_t clipper_depasse;
	if (depasse_screen && !need_offscreen) {
		need_offscreen = EI_TRUE;

		ei_point_t point_depasse = { x_min, y_min };

		int width_depasse = x_max > size.width ? size.width : x_max;
		int height_depasse = y_max > size.height ? size.height : y_max;
		ei_size_t size_depasse = { width_depasse - x_min, height_depasse - y_min };
		clipper_depasse.top_left = point_depasse;
		clipper_depasse.size = size_depasse;
		clipper = &clipper_depasse;
	}


	if (need_offscreen) {
		destination_surface = surface;
		//s'il y a besoin d'un offscreen, on va y tracer les polylines.
		//A la fin on fera une ei_copy_surface sur la destination_surface qui est la 'vrai' surface

		size.width = x_max + 1;
		size.height = y_max + 1;

		surface = hw_surface_create(destination_surface, &size, EI_FALSE);
		hw_surface_lock(surface);


		ei_copy_surface(surface, clipper, destination_surface, clipper, EI_FALSE);
	}

	ei_point_t point_1 = first_point->point;
	ei_point_t point_i = point_1;
	ei_point_t point_j;
	uint32_t* pixel = (uint32_t*) hw_surface_get_buffer(surface);
	int px = 0;

	int w = size.width;
	//int h = size.height;
	uint32_t col = ei_map_rgba(surface, &color);
	int done = 0;
	int x = point_i.x;
	   int y = point_i.y;
	px = x + w * y;
	if (color.alpha<255) {
		int color_indices[4];
		hw_surface_get_channel_indices(surface, &color_indices[0], &color_indices[1], &color_indices[2], &color_indices[3]);
		uint8_t s_alpha = color.alpha;

		while (first_point->next != NULL) {
			first_point = first_point->next;
			point_j = first_point->point;
			int dx = point_j.x - point_i.x;
			int dy = point_j.y - point_i.y;
			if (point_i.x != point_j.x || point_i.y != point_j.y) {
				done = 1;
			}
			x = point_i.x;
			y = point_i.y;
			px = x + w * y;
			int E = 0;
			int pmax = point_j.x + w * point_j.y;
			if (dx > 0) {
				if (dy >= 0) {
					if (dx >= dy) {
						while (px < pmax) {
							uint32_t final_pixel = 0;
							uint8_t* p_8_src = (uint8_t*) &col;
							uint8_t* p_8_dst = (uint8_t*)(pixel + px);
							for (int i = 0; i < 3; i++) {
								int d_i = color_indices[i];
								uint8_t s_val = *(p_8_src + d_i);
								uint8_t d_val = *(p_8_dst + d_i);
								final_pixel += (d_val * (255 - s_alpha) + s_alpha * s_val) / 255 << 8 * d_i;
							}
							*(pixel + px) = final_pixel;
							px++;
							E += dy;
							if (E << 1 > dx) {
								px += w;
								E -= dx;
							}
						}
					}
					else {
						while (px < pmax) {
							uint32_t final_pixel = 0;
							uint8_t* p_8_src = (uint8_t*) &col;
							uint8_t* p_8_dst = (uint8_t*)(pixel + px);
							for (int i = 0; i < 3; i++) {
								int d_i = color_indices[i];
								uint8_t s_val = *(p_8_src + d_i);
								uint8_t d_val = *(p_8_dst + d_i);
								final_pixel += (d_val * (255 - s_alpha) + s_alpha * s_val) / 255 << 8 * d_i;
							}
							*(pixel + px) = final_pixel;
							px += w;
							E += dx;
							if (E << 1 > dy) {
								px++;
								E -= dy;
							}
						}
					}
				}
				else {
					if (dx > -dy) {
						while (px > pmax) {
							uint32_t final_pixel = 0;
							uint8_t* p_8_src = (uint8_t*) &col;
							uint8_t* p_8_dst = (uint8_t*)(pixel + px);
							for (int i = 0; i < 3; i++) {
								int d_i = color_indices[i];
								uint8_t s_val = *(p_8_src + d_i);
								uint8_t d_val = *(p_8_dst + d_i);
								final_pixel += (d_val * (255 - s_alpha) + s_alpha * s_val) / 255 << 8 * d_i;
							}
							*(pixel + px) = final_pixel;
							px++;
							E -= dy;
							if (E << 1 > dx) {
								px -= w;
								E -= dx;
							}
						}
					}
					else {
						while (px > pmax) {
							uint32_t final_pixel = 0;
							uint8_t* p_8_src = (uint8_t*) &col;
							uint8_t* p_8_dst = (uint8_t*)(pixel + px);
							for (int i = 0; i < 3; i++) {
								int d_i = color_indices[i];
								uint8_t s_val = *(p_8_src + d_i);
								uint8_t d_val = *(p_8_dst + d_i);
								final_pixel += (d_val * (255 - s_alpha) + s_alpha * s_val) / 255 << 8 * d_i;
							}
							*(pixel + px) = final_pixel;
							px -= w;
							E += dx;
							if (E << 1 > -dy) {
								px++;
								E += dy;
							}
						}
					}
				}
			}
			else {
				if (dy > 0) {
					if (-dx >= dy) {
						while (px < pmax) {
							uint32_t final_pixel = 0;
							uint8_t* p_8_src = (uint8_t*) &col;
							uint8_t* p_8_dst = (uint8_t*)(pixel + px);
							for (int i = 0; i < 3; i++) {
								int d_i = color_indices[i];
								uint8_t s_val = *(p_8_src + d_i);
								uint8_t d_val = *(p_8_dst + d_i);
								final_pixel += (d_val * (255 - s_alpha) + s_alpha * s_val) / 255 << 8 * d_i;
							}
							*(pixel + px) = final_pixel;
							px--;
							E += dy;
							if (E << 1 > -dx) {
								px += w;
								E += dx;
							}
						}
					}
					else {
						while (px < pmax) {
							uint32_t final_pixel = 0;
							uint8_t* p_8_src = (uint8_t*) &col;
							uint8_t* p_8_dst = (uint8_t*)(pixel + px);
							for (int i = 0; i < 3; i++) {
								int d_i = color_indices[i];
								uint8_t s_val = *(p_8_src + d_i);
								uint8_t d_val = *(p_8_dst + d_i);
								final_pixel += (d_val * (255 - s_alpha) + s_alpha * s_val) / 255 << 8 * d_i;
							}
							*(pixel + px) = final_pixel;
							px += w;
							E -= dx;
							if (E << 1 > dy) {
								px--;
								E -= dy;
							}
						}
					}
				}
				else {
					if (-dx >= -dy) {
						while (px > pmax) {
							uint32_t final_pixel = 0;
							uint8_t* p_8_src = (uint8_t*) &col;
							uint8_t* p_8_dst = (uint8_t*)(pixel + px);
							for (int i = 0; i < 3; i++) {
								int d_i = color_indices[i];
								uint8_t s_val = *(p_8_src + d_i);
								uint8_t d_val = *(p_8_dst + d_i);
								final_pixel += (d_val * (255 - s_alpha) + s_alpha * s_val) / 255 << 8 * d_i;
							}
							*(pixel + px) = final_pixel;
							px--;
							E -= dy;
							if (E << 1 > -dx) {
								px -= w;
								E += dx;
							}
						}
					}
					else {
						while (px > pmax) {
							uint32_t final_pixel = 0;
							uint8_t* p_8_src = (uint8_t*) &col;
							uint8_t* p_8_dst = (uint8_t*)(pixel + px);
							for (int i = 0; i < 3; i++) {
								int d_i = color_indices[i];
								uint8_t s_val = *(p_8_src + d_i);
								uint8_t d_val = *(p_8_dst + d_i);
								final_pixel += (d_val * (255 - s_alpha) + s_alpha * s_val) / 255 << 8 * d_i;
							}
							*(pixel + px) = final_pixel;
							px -= w;
							E -= dx;
							if (E << 1 > -dy) {
								px--;
								E += dy;
							}
						}
					}
				}
			}
			point_i = point_j;
		}
		if (point_1.x != point_j.x || point_1.y != point_j.y || !done) {
			*(pixel + px) = col;
		}
	}
	else {	
		while (first_point->next != NULL) {
			first_point = first_point->next;
			point_j = first_point->point;
			int dx = point_j.x - point_i.x;
			int dy = point_j.y - point_i.y;
			if (point_i.x != point_j.x || point_i.y != point_j.y) {
				done = 1;
			}
			x = point_i.x;
			y = point_i.y;
			px = x + w * y;
			int E = 0;
			int pmax = point_j.x + w * point_j.y;
			if (dx > 0) {
				if (dy >= 0) {
					if (dx >= dy) {
						while (px < pmax) {
							*(pixel + px) = col;
							px++;
							E += dy;
							if (E << 1 > dx) {
								px += w;
								E -= dx;
							}
						}
					}
					else {
						while (px < pmax) {
							*(pixel + px) = col;
							px += w;
							E += dx;
							if (E << 1 > dy) {
								px++;
								E -= dy;
							}
						}
					}
				}
				else {
					if (dx > -dy) {
						while (px > pmax) {
							*(pixel + px) = col;
							px++;
							E -= dy;
							if (E << 1 > dx) {
								px -= w;
								E -= dx;
							}
						}
					}
					else {
						while (px > pmax) {
							*(pixel + px) = col;
							px -= w;
							E += dx;
							if (E << 1 > -dy) {
								px++;
								E += dy;
							}
						}
					}
				}
			}
			else {
				if (dy > 0) {
					if (-dx >= dy) {
						while (px < pmax) {
							*(pixel + px) = col;
							px--;
							E += dy;
							if (E << 1 > -dx) {
								px += w;
								E += dx;
							}
						}
					}
					else {
						while (px < pmax) {
							*(pixel + px) = col;
							px += w;
							E -= dx;
							if (E << 1 > dy) {
								px--;
								E -= dy;
							}
						}
					}
				}
				else {
					if (-dx >= -dy) {
						while (px > pmax) {
							*(pixel + px) = col;
							px--;
							E -= dy;
							if (E << 1 > -dx) {
								px -= w;
								E += dx;
							}
						}
					}
					else {
						while (px > pmax) {
							*(pixel + px) = col;
							px -= w;
							E -= dx;
							if (E << 1 > -dy) {
								px--;
								E += dy;
							}
						}
					}
				}
			}
			point_i = point_j;
		}
		if (point_1.x != point_j.x || point_1.y != point_j.y || !done) {
			*(pixel + px) = col;
		}
	}

	if (need_offscreen) {
		ei_copy_surface(destination_surface, clipper, surface, clipper, EI_FALSE);
		hw_surface_unlock(surface);
		hw_surface_free(surface);
	}
	//TODO: valeur negative pr les points?
	//TODO: gerer les erreurs (genre pas reussi a ouvrir la surface)
}


typedef struct double_linked_point_t {
	ei_point_t point;
	struct double_linked_point_t* next;
	struct double_linked_point_t* prev;
	int way;
} double_linked_point_t;

typedef struct weeping_willow {
	double_linked_point_t* leaf;
	struct weeping_willow* next;
} weeping_willow;

typedef struct linked_int {
	int value;
	struct linked_int* next;
} linked_int;

linked_int* append(linked_int* l, int value) {
	linked_int* cell = malloc(sizeof(linked_int));
	linked_int* first = l;
	cell->value = value;
	cell->next = NULL;
	if (l) {
		while (l->next) {
			l = l->next;
		}
		l->next = cell;
	}
	if (l) {
		return first;
	}
	else {
		return cell;
	}
}

typedef struct progress {
	linked_int* xs;
	double_linked_point_t* points;
	struct progress* next;
} progress;

linked_int* limit(ei_point_t p1, ei_point_t p2) {
	linked_int* xs = NULL;
	int x, y, dx, dy, deltax, E;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	x = p1.x;
	y = p1.y;
	if (dx > 0) {
		if (dy < dx) {
			E = 0;
			deltax = 0;
			while (y <= p2.y) {
				deltax++;
				x++;
				E += dy;
				if (E << 1 > dx) {
					xs = append(xs, x - ((deltax - 1) >> 1));
					y++;
					E -= dx;
					deltax = 0;
				}
			}
		}
		else {
			E = 0;
			while (y <= p2.y) {
				y++;
				xs = append(xs, x);
				E += dx;
				if (E << 1 > dy) {
					x++;
					E -= dy;
				}
			}
		}
	}
	else {
		if (dy < -dx) {
			E = 0;
			deltax = 0;
			while (y <= p2.y) {
				deltax++;
				x--;
				E += dy;
				if (E << 1 > -dx) {
					xs = append(xs, x + ((deltax - 1) >> 1));
					y++;
					E += dx;
					deltax = 0;
				}
			}
		}
		else {
			E = 0;
			while (y <= p2.y) {
				y++;
				E -= dx;
				xs = append(xs, x);
				if (E << 1 > dy) {
					x--;
					E -= dy;
				}
			}
		}
	}
	return xs;
}


void			ei_draw_polygon(ei_surface_t			surface,
	const ei_linked_point_t* first_point,
	const ei_color_t		color,
	const ei_rect_t* clipper) {

	if (!first_point) {
		return;
	}

	ei_linked_point_t* current = first_point;

	// First : build a double-linked list of points
	double_linked_point_t* pol = malloc(sizeof(double_linked_point_t));
	double_linked_point_t* first = pol;
	pol->point = current->point;
	pol->way = 0;
	current = current->next;
	while (current != NULL) {
		double_linked_point_t* cell = malloc(sizeof(double_linked_point_t));
		cell->point = current->point;
		cell->way = 0;
		cell->prev = pol;
		pol->next = cell;
		pol = pol->next;
		current = current->next;
	}
	pol->next = first;
	first->prev = pol;
	pol = first;

	//printf("Conversion complete\n");


	// Second : cut it in "weeping willows"
	weeping_willow* structure = malloc(sizeof(weeping_willow));
//	weeping_willow* structure2;
	weeping_willow* first_willow = structure;
	ei_point_t p = pol->point;
	ei_point_t pc = (pol->next)->point;
	while (p.y <= pc.y) {
		pol = pol->next;
		p = pol->point;
		pc = (pol->next)->point;
	}
	double_linked_point_t* starting_point = pol;

	int done = 0;
	int leave = 0;

	//printf("Starting point chosen\n");

	weeping_willow* last = NULL;
	double_linked_point_t* to_free_double = NULL;

	while (pol) {

		// Ascending
		pol->prev = NULL;
		p = pol->point;
		if (!pol->next) {
			break;
		}
		pc = (pol->next)->point;
		while (p.y > pc.y) {
			pol->way = -1;
			pol = pol->next;
			pol->prev->next = NULL;
			p = pol->point;
			if (!pol->next) {
				leave = 1;
				break;
			}
			pc = (pol->next)->point;
		}
		if (leave) {
			break;
		}
		pol->way = 0;
		if (!done) {
			starting_point = pol;
		}
		if (done && starting_point == pol) {
			break;
		}
		done = 1;
		last = structure;
		structure->leaf = pol;
		weeping_willow* n_structure = malloc(sizeof(weeping_willow));
		structure->next = n_structure;
		structure = n_structure;

		// Descending
		while (p.y < pc.y) {
			pol = pol->next;
			if (!pol->next) {
				leave = 1;
				break;
			}
			p = pol->point;
			pol->way = 1;
			pc = (pol->next)->point;
		}
		if (leave) {
			break;
		}
		double_linked_point_t* copy = malloc(sizeof(double_linked_point_t));
		copy->point = pol->point;
		copy->next = pol->next;
		copy->way = -pol->way;
		copy->prev = NULL;
		copy->next->prev = copy;
		pol->next = NULL;
		pol = copy;

		// Erasing flats
		p = pol->point;
		if (pol->next) {
			pc = (pol->next)->point;
		}
		else {
			break;
		}
		while (pc.y == p.y) {
			to_free_double = pol;
			pol = pol->next;
			free(to_free_double);
			p = pol->point;
			if (pol->next) {
				pc = (pol->next)->point;
			}
			else {
				leave = 1;
				break;
			}
		}
		pol->prev = NULL;
		if (leave) {
			break;
		}
	}

	free(last->next);
	last->next = NULL;

	//printf("Blossoming complete\n");

	// Ordering blossoms / merging cut blossoms

	linked_int* ordinates = malloc(sizeof(linked_int));
	linked_int* first_ordinate = ordinates;

	weeping_willow* ordered_structure = NULL;
	weeping_willow* first_ordered = ordered_structure;
	weeping_willow* last_willow = NULL;
	weeping_willow* min;
	weeping_willow* pre_min;
	weeping_willow* to_free_willow = NULL;


	while (first_willow) {
		structure = first_willow;
		min = structure;
		pre_min = NULL;
		while (structure->next) {
			if (structure->leaf->point.x == structure->next->leaf->point.x && structure->leaf->point.y == structure->next->leaf->point.y && (!structure->leaf->next || !structure->leaf->prev)) {
				if (structure->leaf->next) {
					structure->leaf->prev = structure->next->leaf->prev;
					structure->leaf->prev->next = structure->leaf;
				}
				else {
					structure->leaf->next = structure->next->leaf->next;
					structure->leaf->next->prev = structure->leaf;
				}
				to_free_willow = structure->next;
				structure->next = structure->next->next;
				free(to_free_willow);
			}
			if (structure->next) {
				if (structure->next->leaf->point.y < min->leaf->point.y) {
					pre_min = structure;
					min = structure->next;
				}
				structure = structure->next;
			}
		}
		ordered_structure = min;
		if (pre_min) {
			pre_min->next = min->next;
		}
		else {
			first_willow = min->next;
		}
		min->next = NULL;
		if (last_willow) {
			last_willow->next = min;
		}
		else {
			first_ordered = min;
		}
		last_willow = min;

		ordinates->value = min->leaf->point.y;
		if (first_willow) {
			ordinates->next = malloc(sizeof(linked_int));
			ordinates = ordinates->next;
		}
		else {
			ordinates->next = NULL;
		}
	}


	// Drawing

	//printf("Ordering complete\n");

	progress* first_p = NULL;
	progress* last_p = NULL;
	progress* current_p = NULL;
	progress* next_p = NULL;
	progress* cell1 = NULL;
	progress* cell2 = NULL;
	progress* mem = NULL;
	weeping_willow* next_active = first_ordered;
	int x = 0;
	int y = 0;
	int x1 = 0;
	int x2 = 0;
	int mem2 = 0;
	uint32_t* col = malloc(sizeof(uint32_t));
	*col = ei_map_rgba(surface, &color);
	linked_int* xs = NULL;
	ordinates = first_ordinate;
	linked_int* to_free_xs = NULL;


	uint32_t* pixel = (uint32_t*)hw_surface_get_buffer(surface);
	uint32_t* first_pixel = pixel;
	ei_size_t size = hw_surface_get_size(surface);
	int w = size.width;



	if (color.alpha<255) {
		int color_indices[4];
		hw_surface_get_channel_indices(surface, &color_indices[0], &color_indices[1], &color_indices[2], &color_indices[3]);
		while (first_p || ordinates) {

			// Reading next active ordinate and loading new tasks.
			if (ordinates && (y == ordinates->value || !first_p)) {
				y = ordinates->value;
				pixel = first_pixel + w * y;

				// Making prev leaf active
				while (next_active->leaf->point.y == y) {
					ordinates = ordinates->next;
					if (next_active->leaf->prev) {
						ei_point_t p1 = next_active->leaf->point;
						ei_point_t p2 = next_active->leaf->prev->point;
						xs = limit(p1, p2);
						cell1 = malloc(sizeof(progress));
						cell1->xs = xs;
						cell1->points = next_active->leaf->prev;
						cell1->next = NULL;
					}
					// Making next leaf active
					if (next_active->leaf->next) {
						ei_point_t p1 = next_active->leaf->point;
						ei_point_t p2 = next_active->leaf->next->point;
						xs = limit(p1, p2);
						cell2 = malloc(sizeof(progress));
						cell2->xs = xs;
						cell2->points = next_active->leaf->next;
						cell2->next = NULL;
					}
					// cell1 will come after cell2
					if (cell1 && cell2) {
						if (cell1->points->point.x > cell2->points->point.x) {
							mem = cell1;
							cell1 = cell2;
							cell2 = mem;
						}
						cell1->next = cell2;
					}
					else {
						if (cell1) {
							cell2 = cell1;
						}
						else {
							cell1 = cell2;
						}
					}

					// Inserting them in the progress list

					if (!first_p) {
						first_p = cell1;
						cell2->next = NULL;
					}
					else {
						last_p = NULL;
						current_p = first_p;
						while (current_p->next && current_p->next->points->point.x < cell1->points->point.x) {
							last_p = current_p;
							current_p = current_p->next;
						}
						if (last_p) {
							last_p->next = cell1 ? cell1 : cell2;
						}
						else {
							first_p = cell1 ? cell1 : cell2;
						}
						if (current_p != cell1) {
							cell2->next = current_p;
						}
					}
					cell1 = NULL;
					cell2 = NULL;
					next_active = next_active->next;
					if (!next_active) {
						break;
					}
				}
			}

			// Updating / Deleting ending tasks.
			current_p = first_p;
			last_p = NULL;
			//printf("Cleaning up tasks\n");
			while (current_p) {
				next_p = current_p->next;
				if (!current_p->xs->next) {
					// Try to go to the next segment.
					if (current_p->points->way == 1 && current_p->points->next) {
						ei_point_t p1 = current_p->points->point;
						ei_point_t p2 = current_p->points->next->point;
						to_free_double = current_p->points;
						current_p->points = current_p->points->next;
						free(to_free_double);
						xs = limit(p1, p2);
						current_p->xs = xs;
						last_p = current_p;
					}
					else {
						if (current_p->points->way == -1 && current_p->points->prev) {
							ei_point_t p1 = current_p->points->point;
							ei_point_t p2 = current_p->points->prev->point;
							to_free_double = current_p->points;
							current_p->points = current_p->points->prev;
							free(to_free_double);
							xs = limit(p1, p2);
							current_p->xs = xs;
							last_p = current_p;
						}
						else {
							// We cannot : This task is definitely over !!!
							if (last_p) {
								last_p->next = current_p->next;
								free(current_p);
							}
							else {
								first_p = current_p->next;
								next_p = first_p;
								last_p = current_p;
							}
							if (!first_p || !last_p->next) {
								first_p = NULL;
							}
						}
					}
				}
				else {
					last_p = current_p;
				}
				current_p = next_p;
			}

			// Drawing one scanline.


			current_p = first_p;

			while (current_p) {
				x1 = current_p->xs->value;
				to_free_xs = current_p->xs;
				current_p->xs = current_p->xs->next;
				free(to_free_xs);
				current_p = current_p->next;
				if (!current_p) {
					break;
				}
				x2 = current_p->xs->value;
				if (!clipper || (y >= clipper->top_left.y && y < clipper->top_left.y + clipper->size.height)) {
					if (x1 > x2) {
						mem2 = x2;
						x2 = x1;
						x1 = mem2;
					}
					if (clipper) {
						if (x1 < clipper->top_left.x) {
							x1 = clipper->top_left.x;
						}
						if (x2 > clipper->top_left.x + clipper->size.width) {
							x2 = clipper->top_left.x + clipper->size.width;
						}
					}
					for (x = x1; x < x2; x++) {
						uint32_t final_pixel = 0;
						uint8_t* p_8_src = (uint8_t*)col;
						uint8_t* p_8_dst = (uint8_t*)(pixel+x);
						uint8_t s_alpha = color.alpha;

						for (int i = 0; i < 3; i++) {
							int d_i = color_indices[i];
							uint8_t s_val = *(p_8_src + d_i);
							uint8_t d_val = *(p_8_dst + d_i);
							final_pixel += (d_val * (255 - s_alpha) + s_alpha * s_val) / 255 << 8 * d_i;
						}
						*(pixel+x) = final_pixel;
					}
				}
				to_free_xs = current_p->xs;
				current_p->xs = current_p->xs->next;
				free(to_free_xs);
				current_p = current_p->next;
			}
			y++;
			pixel += w;
		}
	}
	else {
		while (first_p || ordinates) {

			// Reading next active ordinate and loading new tasks.
			if (ordinates && (y == ordinates->value || !first_p)) {
				y = ordinates->value;
				pixel = first_pixel + w * y;

				// Making prev leaf active
				while (next_active->leaf->point.y == y) {
					ordinates = ordinates->next;
					if (next_active->leaf->prev) {
						ei_point_t p1 = next_active->leaf->point;
						ei_point_t p2 = next_active->leaf->prev->point;
						xs = limit(p1, p2);
						cell1 = malloc(sizeof(progress));
						cell1->xs = xs;
						cell1->points = next_active->leaf->prev;
						cell1->next = NULL;
					}
					// Making next leaf active
					if (next_active->leaf->next) {
						ei_point_t p1 = next_active->leaf->point;
						ei_point_t p2 = next_active->leaf->next->point;
						xs = limit(p1, p2);
						cell2 = malloc(sizeof(progress));
						cell2->xs = xs;
						cell2->points = next_active->leaf->next;
						cell2->next = NULL;
					}
					// cell1 will come after cell2
					if (cell1 && cell2) {
						if (cell1->points->point.x > cell2->points->point.x) {
							mem = cell1;
							cell1 = cell2;
							cell2 = mem;
						}
						cell1->next = cell2;
					}
					else {
						if (cell1) {
							cell2 = cell1;
						}
						else {
							cell1 = cell2;
						}
					}

					// Inserting them in the progress list

					if (!first_p) {
						first_p = cell1;
						cell2->next = NULL;
					}
					else {
						last_p = NULL;
						current_p = first_p;
						while (current_p->next && current_p->next->points->point.x < cell1->points->point.x) {
							last_p = current_p;
							current_p = current_p->next;
						}
						if (last_p) {
							last_p->next = cell1 ? cell1 : cell2;
						}
						else {
							first_p = cell1 ? cell1 : cell2;
						}
						if (current_p != cell1) {
							cell2->next = current_p;
						}
					}
					cell1 = NULL;
					cell2 = NULL;
					next_active = next_active->next;
					if (!next_active) {
						break;
					}
				}
			}

			// Updating / Deleting ending tasks.
			current_p = first_p;
			last_p = NULL;
			//printf("Cleaning up tasks\n");
			while (current_p) {
				next_p = current_p->next;
				if (!current_p->xs->next) {
					// Try to go to the next segment.
					if (current_p->points->way == 1 && current_p->points->next) {
						ei_point_t p1 = current_p->points->point;
						ei_point_t p2 = current_p->points->next->point;
						to_free_double = current_p->points;
						current_p->points = current_p->points->next;
						free(to_free_double);
						xs = limit(p1, p2);
						current_p->xs = xs;
						last_p = current_p;
					}
					else {
						if (current_p->points->way == -1 && current_p->points->prev) {
							ei_point_t p1 = current_p->points->point;
							ei_point_t p2 = current_p->points->prev->point;
							to_free_double = current_p->points;
							current_p->points = current_p->points->prev;
							free(to_free_double);
							xs = limit(p1, p2);
							current_p->xs = xs;
							last_p = current_p;
						}
						else {
							// We cannot : This task is definitely over !!!
							if (last_p) {
								last_p->next = current_p->next;
								free(current_p);
							}
							else {
								first_p = current_p->next;
								next_p = first_p;
								last_p = current_p;
							}
							if (!first_p || !last_p->next) {
								first_p = NULL;
							}

						}
					}
				}
				else {
					last_p = current_p;
				}
				current_p = next_p;
			}

			// Drawing one scanline.


			current_p = first_p;

			while (current_p) {
				x1 = current_p->xs->value;
				to_free_xs = current_p->xs;
				current_p->xs = current_p->xs->next;
				free(to_free_xs);
				current_p = current_p->next;
				if (!current_p) {
					break;
				}
				x2 = current_p->xs->value;
				if (!clipper || (y >= clipper->top_left.y && y < clipper->top_left.y + clipper->size.height)) {
					if (x1 > x2) {
						mem2 = x2;
						x2 = x1;
						x1 = mem2;
					}
					if (clipper) {
						if (x1 < clipper->top_left.x) {
							x1 = clipper->top_left.x;
						}
						if (x2 > clipper->top_left.x + clipper->size.width) {
							x2 = clipper->top_left.x + clipper->size.width;
						}
					}
					for (x = x1; x < x2; x++) {
						*(pixel + x) = *col;
					}
				}
				to_free_xs = current_p->xs;
				current_p->xs = current_p->xs->next;
				free(to_free_xs);
				current_p = current_p->next;
			}
			y++;
			pixel += w;
		}
	}
	free(col);
	//printf("Drawing complete\n");
}

void ei_fill(ei_surface_t surface,
	const ei_color_t* color,
	const ei_rect_t* clipper) {
	int color_int;
	uint8_t alpha;
	if (color == NULL) {
		ei_color_t black = {0, 0, 0, 255};
		color_int = ei_map_rgba(surface, &black);
	}
	else {
		color_int = ei_map_rgba(surface, color);
		alpha = color->alpha;
	}
	 
	ei_size_t size_surface = hw_surface_get_size(surface);
	int surface_height = size_surface.height;
	int surface_width = size_surface.width;
	
	int color_indices[4];
	
	hw_surface_get_channel_indices(surface, &color_indices[0], &color_indices[1],
								   &color_indices[2], &color_indices[3]);
	
	uint8_t* color_uint8_t = (uint8_t*) &color_int;
	
	if (clipper == NULL) {
		uint32_t* pixel = (uint32_t*) hw_surface_get_buffer(surface);
		int nb_pixel = surface_height * surface_width;
		int compteur = 1;
		while (compteur <= nb_pixel) {
			uint32_t new_pixel = 0;
			//uint8_t* pixel_component = (uint8_t*) pixel;
			for (int i = 0; i < 3; i++) {
				int d_i = color_indices[i];
				uint8_t p_i = *(color_uint8_t + color_indices[i]);
				uint8_t s_i = *(pixel + color_indices[i]);
				new_pixel += (p_i * alpha + (255 - alpha) * s_i)/255	<< 8*d_i;		
			}
			*pixel = new_pixel;
			pixel++;
			compteur++;
		}
	}
	else {
		int rect_height = clipper->size.height;
		int rect_width = clipper->size.width;
		ei_point_t first_pixel = clipper->top_left;
		int x_max = first_pixel.x + rect_width;
		int y_max = first_pixel.y + rect_height;
		int x = first_pixel.x;
		int y = first_pixel.y;
		uint32_t* pixel = (uint32_t*) hw_surface_get_buffer(surface);
		pixel += y * surface_width + x;
		int decalage = surface_width - rect_width;
		while (y < y_max) {
			while (x < x_max) {
				uint32_t new_pixel = 0;
				//uint8_t* pixel_component = (uint8_t*) pixel;
				for (int i = 0; i < 3; i++) {
					int d_i = color_indices[i];
					uint8_t p_i = *(color_uint8_t + color_indices[i]);
					uint8_t s_i = *(pixel + color_indices[i]);
					new_pixel += (p_i * alpha + (255 - alpha) * s_i)/255	<< 8*d_i;		
				}
				*pixel = new_pixel;
				pixel++;
				x++;
			}
			pixel += decalage;
			y++;
			x = first_pixel.x;
		}
	}
}

int	ei_copy_surface(ei_surface_t destination, const ei_rect_t* dst_rect, const ei_surface_t source,
	const ei_rect_t* src_rect, const ei_bool_t	alpha) {

	ei_size_t size_subpart_dest, size_subpart_src;

	if (dst_rect != NULL) size_subpart_dest = dst_rect->size;
	else size_subpart_dest = hw_surface_get_size(destination);

	if (dst_rect != NULL) size_subpart_src = src_rect->size;
	else size_subpart_src = hw_surface_get_size(source);

	if (size_subpart_dest.width != size_subpart_src.width ||
		size_subpart_dest.height != size_subpart_src.height) {
		puts("Subparts de tailles différentes donc peut pas copy surface");
		return 1;
	}

	int w = size_subpart_dest.width;
	int h = size_subpart_dest.height;

	int dst_w = hw_surface_get_size(destination).width;
	int src_w = hw_surface_get_size(source).width;

	uint32_t* p_pixel_dst = (uint32_t*) hw_surface_get_buffer(destination);
	p_pixel_dst += dst_rect->top_left.x + dst_w * dst_rect->top_left.y;

	uint32_t* p_pixel_src = (uint32_t*) hw_surface_get_buffer(source);
	p_pixel_src += src_rect->top_left.x + src_w * src_rect->top_left.y;

	int color_indices[2][4];
	hw_surface_get_channel_indices(source, &color_indices[0][0], &color_indices[0][1], &color_indices[0][2], &color_indices[0][3]);
	hw_surface_get_channel_indices(destination, &color_indices[1][0], &color_indices[1][1], &color_indices[1][2], &color_indices[1][3]);

	if (alpha) {
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				uint32_t final_pixel = 0;
				uint8_t* p_8_src = (uint8_t*)p_pixel_src;
				uint8_t* p_8_dst = (uint8_t*)p_pixel_dst;
				uint8_t s_alpha = *(p_8_src + color_indices[0][3]);

				for (int i = 0; i < 3; i++) {
					int d_i = color_indices[1][i];
					uint8_t s_val = *(p_8_src + color_indices[0][i]);
					uint8_t d_val = *(p_8_dst + d_i);
					final_pixel += (d_val * (255 - s_alpha) + s_alpha * s_val) / 255 << 8 * d_i;
				}
				//destination transparency set to max if handled by dest_surface
				if (color_indices[1][3] != -1) final_pixel += 255 << 8 * color_indices[1][3];
				*p_pixel_dst = final_pixel;
				p_pixel_dst++;
				p_pixel_src++;
			}
			p_pixel_dst += (dst_w - w);
			p_pixel_src += (src_w - w);
		}
	}
	else {
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				uint32_t final_pixel = 0;
				uint8_t* p_8_src = (uint8_t*)p_pixel_src;
				uint8_t* p_8_dst = (uint8_t*)p_pixel_dst;
				uint8_t s_alpha = *(p_8_src + color_indices[0][3]);

				for (int i = 0; i < 4; i++) {
					int d_i = color_indices[1][i];
					uint8_t s_val = *(p_8_src + color_indices[0][i]);
					final_pixel += s_val << 8 * d_i;
				}
				*p_pixel_dst = final_pixel;
				p_pixel_dst++;
				p_pixel_src++;
			}
			p_pixel_dst += (dst_w - w);
			p_pixel_src += (src_w - w);
		}
	}


	return 0;
}


//returns the intersection of 2 rect (can be zero)
ei_rect_t intersect_rect(ei_rect_t rect1, ei_rect_t rect2){
	ei_rect_t zero = {{0, 0}, {0, 0}};
	
	ei_rect_t rect;
	ei_size_t size;
	ei_point_t top_left;

	if(rect1.top_left.x > rect2.top_left.x){
		if(rect1.top_left.x > rect2.top_left.x + rect2.size.width) return zero;

		top_left.x = rect1.top_left.x;
		
		if(rect1.top_left.x + rect1.size.width < rect2.top_left.x + rect2.size.width)
			size.width = rect1.size.width;
		else
			size.width = rect2.top_left.x + rect2.size.width - rect1.top_left.x;
	}
	else{
		if(rect2.top_left.x > rect1.top_left.x + rect1.size.width) return zero;

		top_left.x = rect2.top_left.x;
		
		if(rect2.top_left.x + rect2.size.width < rect1.top_left.x + rect1.size.width)
			size.width = rect2.size.width;
		else
			size.width = rect1.top_left.x + rect1.size.width - rect2.top_left.x;
	}

	if(rect1.top_left.y > rect2.top_left.y){
		if(rect1.top_left.y > rect2.top_left.y + rect2.size.height) return zero;

		top_left.y = rect1.top_left.y;
		
		if(rect1.top_left.y + rect1.size.height < rect2.top_left.y + rect2.size.height)
			size.height = rect1.size.height;
		else
			size.height = rect2.top_left.y + rect2.size.height - rect1.top_left.y;
	}
	else{
		if(rect2.top_left.y > rect1.top_left.y + rect1.size.height) return zero;

		top_left.y = rect2.top_left.y;
		
		if(rect2.top_left.y + rect2.size.height < rect1.top_left.y + rect1.size.height)
			size.height = rect2.size.height;
		else
			size.height = rect1.top_left.y + rect1.size.height - rect2.top_left.y;
	}

	rect.size = size;
	rect.top_left = top_left;
	return rect;
}

ei_rect_t union_rect(ei_rect_t rect1, ei_rect_t rect2) {
	ei_point_t u_top_left = { rect1.top_left.x < rect2.top_left.x ? rect1.top_left.x : rect2.top_left.x, rect1.top_left.y < rect2.top_left.y ? rect1.top_left.y : rect2.top_left.y };
	ei_point_t p1 = ei_point_add(rect1.top_left, ei_size_as_point(rect1.size));
	ei_point_t p2 = ei_point_add(rect2.top_left, ei_size_as_point(rect2.size));
	ei_point_t u_bottom_right = { p1.x < p2.x ? p2.x : p1.x,p1.y < p2.y ? p2.y : p1.y };
	ei_size_t u_size = ei_point_as_size(ei_point_sub(u_bottom_right, u_top_left));
	ei_rect_t u_rect = { u_top_left, u_size };
	return u_rect;
}

void ei_draw_text(ei_surface_t	surface, const ei_point_t*	where, const char* text,
				  const ei_font_t	font, const ei_color_t*	color, const ei_rect_t*	clipper){

	ei_surface_t text_surface;
	if(font == NULL) text_surface = hw_text_create_surface(text, ei_default_font, color);
	else text_surface = hw_text_create_surface(text, font, color);
	hw_surface_lock(text_surface);
	
	ei_size_t destination_size = hw_surface_get_size(surface);
	ei_size_t text_size = hw_surface_get_size(text_surface);

	ei_rect_t destination_clipper = {{0,0}, destination_size};
	if(clipper != NULL) destination_clipper = intersect_rect(destination_clipper, *clipper);

	ei_rect_t ideal_clipper = {*where, text_size};
	ei_rect_t text_clipper = {{0,0}, text_size};

	// on force le alpha
	ei_size_t offscreen_size = hw_surface_get_size(surface);
	ei_surface_t offscreen = hw_surface_create(surface, &offscreen_size, EI_TRUE);
	hw_surface_lock(offscreen);
	ei_copy_surface(offscreen, &ideal_clipper, text_surface, &text_clipper, EI_FALSE);	
	
	destination_clipper = intersect_rect(destination_clipper, ideal_clipper);

	ei_copy_surface(surface, &destination_clipper, offscreen, &destination_clipper , EI_TRUE);
	hw_surface_unlock(offscreen);
	hw_surface_unlock(text_surface);
	hw_surface_free(offscreen);
	hw_surface_free(text_surface);
}
