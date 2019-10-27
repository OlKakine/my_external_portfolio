/* 
 * File:   coherence.h
 * Author: checchio
 *
 * Created on April 15, 2019, 5:28 PM
 */

#ifndef COHERENCE_H
#define COHERENCE_H

#include "mesh.h"

extern bool coherence_maillage(struct mesh);
extern bool coherence_null(struct mesh);

extern bool coherence_fermeture(struct list *hedges);

#endif /* COHERENCE_H */
