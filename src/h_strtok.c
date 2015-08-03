/*
 * h_strtok.c
 *
 *  Created on: 2015. 6. 23.
 *      Author: root
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "h_arraylist.h"

void string_free(void *data)
{
	free(data);
}

Harraylist* h_strtok(char* str, char delim)
{
	char *curstr, *nextstr;
	Harraylist *arr = h_arraylist_init(string_free);
	if(!arr)
		return NULL;


	//parsing
	curstr = str;
	while ( curstr ) {
		nextstr = strchr(curstr, delim);
		if(nextstr) *nextstr = '\0';			//temporary

		char *p = strdup(curstr);
		if(!p) {
			if (nextstr) *nextstr = delim; 		//restore
			h_arraylist_free(arr);
			return NULL;
		}

		if(!h_arraylist_add(arr, (void*)p)) {
			if (nextstr) *nextstr = delim; 		//restore
			h_arraylist_free(arr);
			free(p);
			return NULL;
		}

		if (nextstr) *nextstr = delim; 			//restore
		curstr = nextstr ? (nextstr + 1) : NULL;
	}

	return arr;
}

void h_strtok_free(Harraylist *arr)
{
	h_arraylist_free(arr);
}

int h_strtok_get_length(Harraylist *arr)
{
	return arr->length;
}

char* h_strtok_get(Harraylist *arr, unsigned int idx)
{
	return (char*)h_arraylist_get(arr, idx);
}

int h_strtok_contains(Harraylist *arr, const char* str)
{
	int i;
	for(i=0; i<arr->length; i++)
		if(strcmp((char*)arr->array[i], str) == 0) return 1;

	return 0;
}
