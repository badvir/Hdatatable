/*
 * h_arraylist.c
 *
 *  Created on: 2015. 6. 23.
 *      Author: root
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "h_arraylist.h"

Harraylist* h_arraylist_init(harray_list_free_callback *free_fun)
{
	Harraylist *arr;
	arr = (Harraylist*)calloc(1, sizeof(Harraylist));
	if(!arr)
		return NULL;

	arr->size = H_ARRAYLIST_DEFAULT_SIZE;
	arr->length = 0;
	arr->array = (void*)calloc(sizeof(void*), arr->size);
	if(arr->array == NULL) {
		free(arr);
		return NULL;
	}

	arr->free_fun = free_fun;

	return arr;
}

void h_arraylist_free(Harraylist *arr)
{
	if(arr == NULL)
		return;

	int i=0;
	for(i=0; i<arr->length; i++) {
		if(arr->array[i] != NULL && arr->free_fun != NULL)
			arr->free_fun(arr->array[i]);
	}

	free(arr->array);
	free(arr);
}


inline int h_arraylist_get_length(Harraylist *arr)
{
	if(!arr)
		return 0;

	return arr->length;
}

int h_arraylist_expand_internal(Harraylist *arr, unsigned int max)
{
	void *p;
	int new_size;

	if(!arr)
		return 0;

	if(max < arr->size)
		return 1;

	new_size = arr->size << 1;

	if(new_size < max)
		new_size = max;

	p = realloc(arr->array, new_size * sizeof(void*));
	if(!p)
		return 0;

	arr->array = (void**)p;
	memset(arr->array + arr->size, 0, (new_size-arr->size) * sizeof(void*));
	arr->size = new_size;

	return 1;
}

int h_arraylist_put_idx(Harraylist *arr, unsigned int idx, void *data)
{
	if(!h_arraylist_expand_internal(arr, idx+1))
		return 0;

	if(arr->array[idx]) arr->free_fun(arr->array[idx]);

	arr->array[idx] = data;
	if(arr->length <= idx) arr->length = idx + 1;

	return 1;

}

int h_arraylist_add(Harraylist *arr, void *data)
{
	if(!arr)
		return 0;

	return h_arraylist_put_idx(arr, arr->length, data);
}

int h_arraylist_insert(Harraylist *arr, unsigned int idx, void *data)
{
	if(!arr)
		return 0;

	if(!h_arraylist_expand_internal(arr, arr->length + 1))
		return 0;

	if(arr->length < idx)
		return 0;

	memmove(arr->array + idx + 1, arr->array + idx, (arr->length - idx) * sizeof(void *));
	arr->array[idx] = data;
	++arr->length;

	return 1;
}

int h_arraylist_remove(Harraylist *arr, unsigned int idx)
{
	if(!arr)
		return 0;

	if(arr->length <= idx)
		return 0;

	void* value = arr->array[idx];

	memmove(arr->array + idx, arr->array + idx + 1, (arr->length - idx) * sizeof(void *));
	--arr->length;

	if(arr->free_fun)
		arr->free_fun(value);

	return 1;
}

void* h_arraylist_get(Harraylist *arr, unsigned int idx)
{
	if(!arr)
		return NULL;

	if(arr->length < idx)
		return NULL;

	return arr->array[idx];
}

/*
void h_arraylist_sort(Harraylist *arr, int(*sort_fun)(const void*, const void*))
{
	qsort(arr->array, arr->length, sizeof(arr->array[0]), sort_fun);
}

void* h_arraylist_bsearch(const void **key, Harraylist *arr, int (*sort_fun)(const void*, const void*))
{
	return bsearch(key, arr->array, arr->length, sizeof(arr->array[0]), sort_fun);
}
*/
