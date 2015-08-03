/*
 * h_datatable.h
 *
 *  Created on: 2015. 7. 17.
 *      Author: root
 */

#ifndef H_DATATABLE_H_
#define H_DATATABLE_H_

#include "h_arraylist.h"

struct _h_datatable {

	Harraylist *rows;

};

typedef struct _h_datatable Hdatatable;

void h_datatable_data_free(void *data);
void h_datatable_row_free(void *data);
Hdatatable* h_datatable_init();
void h_datatable_free(Hdatatable *table);

int h_datatable_add_row(Hdatatable *table, Harraylist *row);
int h_datatable_insert_row(Hdatatable *table, unsigned int idx, Harraylist *row);
int h_datatable_remove_row(Hdatatable *table, unsigned int idx);

int h_datatable_get_row_count(Hdatatable *table);
int h_datatable_get_column_count(Hdatatable *table, unsigned int row_idx);
Harraylist* h_datatable_get_row(Hdatatable *table, unsigned int row_idx);
void* h_datatable_get_idx(Hdatatable *table, unsigned int row_idx, unsigned int column_idx);

Hdatatable* h_datatable_load(char* str, char delim);
Hdatatable* h_datatable_load_from_file(const char* filepath, char delim);

#endif /* H_DATATABLE_H_ */
