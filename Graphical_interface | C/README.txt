minimal.c -> affichage de la main windows en rouge sans rien et quitter en appuyant sur un bouton (aucun test)

lines.c -> test of ei_draw_polyline, ei_draw_polygon, ei_fill, with transparency and clipping

polyline.c -> test of ei_draw_text with a line

frame.c -> test of frame_structure, ei_frame_configure, ei_place, ei_placer_run, and frame_drawfunc

draw_button.c -> test of button_structure, ei_button_configure, button_drawfunc

button.c -> event management with a button (callback and raised/sunken depending on your click)

draw_toplevel.c -> drawing a toplevel (resizable) with a frame(containing a text) and a button(containing an image), the button comes to the foreground when you click on it

hello_world.c -> didn't work, some problem with anchor

puzzle.c -> the toplevel with all the image is drawn but there is a problem with the pieces movement (the update of the screen is only done when you move the toplevel and not when you click on a piece)

two048.c -> We haven't got the time to do it
