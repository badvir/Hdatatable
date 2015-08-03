/*
 * h_strtok.h
 *
 *  Created on: 2015. 6. 23.
 *      Author: root
 */

#ifndef H_STRTOK_H_
#define H_STRTOK_H_

#include "h_arraylist.h"

Harraylist* h_strtok(char* str, char delim);

void h_strtok_free(Harraylist *arr);

int h_strtok_get_length(Harraylist *arr);

char* h_strtok_get(Harraylist *arr, unsigned int idx);

int h_strtok_contains(Harraylist *arr, const char* str);

#endif /* H_STRTOK_H_ */
