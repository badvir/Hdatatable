/*
 * harraylist.h
 *
 *  Created on: 2015. 6. 23.
 *      Author: root
 */

#ifndef H_ARRAYLIST_H_
#define H_ARRAYLIST_H_

#define H_ARRAYLIST_DEFAULT_SIZE 32

typedef void (harray_list_free_callback) (void *data);

struct _h_array_list {
	void **array;
	int length;
	int size;
	harray_list_free_callback *free_fun;
};

typedef struct _h_array_list Harraylist;

Harraylist* h_arraylist_init(harray_list_free_callback *free_fun);

void h_arraylist_free(Harraylist *arr);

inline int h_arraylist_get_length(Harraylist *arr);

int h_arraylist_put_idx(Harraylist *arr, int unsigned idx, void *data);

int h_arraylist_add(Harraylist *arr, void *data);

int h_arraylist_insert(Harraylist *arr, unsigned int idx, void *data);

int h_arraylist_remove(Harraylist *arr, unsigned int idx);

void* h_arraylist_get(Harraylist *arr, unsigned int idx);

//void h_arraylist_sort(Harraylist *arr, int(*sort_fun)(const void*, const void*));
//void* h_arraylist_bsearch(const void **key, Harraylist *arr, int (*sort_fun)(const void*, const void*));

#endif /* H_ARRAYLIST_H_ */
