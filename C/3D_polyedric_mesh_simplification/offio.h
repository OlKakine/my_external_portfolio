/* 
 * File:   offio.h
 * Author: checchio
 *
 * Created on April 15, 2019, 6:50 PM
 */

#ifndef OFFIO_H
#define OFFIO_H
#include <string.h>
#include <stdio.h>
#include "mesh.h"
#include "list.h"

extern struct mesh* off_load(char* file_name);
extern void off_save(char* file_name, struct mesh* mesh);

#endif /* OFFIO_H */
