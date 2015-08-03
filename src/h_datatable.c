/*
 * h_datatable.c
 *
 *  Created on: 2015. 7. 17.
 *      Author: root
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "h_arraylist.h"
#include "h_strtok.h"
#include "h_datatable.h"

void h_datatable_data_free(void *data)
{
	free(data);
}

void h_datatable_row_free(void *data)
{
	Harraylist *row = (Harraylist*)data;
	h_arraylist_free(row);
}

Hdatatable* h_datatable_init()
{
	Hdatatable *table = (Hdatatable*)calloc(1, sizeof(Hdatatable));
	if(!table)
		return NULL;

	memset(table, 0, sizeof(*table));

	table->rows = h_arraylist_init(h_datatable_row_free);
	if(table->rows == NULL) {
		h_datatable_free(table);
		return NULL;
	}

	return table;
}

void h_datatable_free(Hdatatable *table)
{
	if(table == NULL)
		return;

	h_arraylist_free(table->rows);
	free(table);
}


int h_datatable_add_row(Hdatatable *table, Harraylist *row)
{
	if(table == NULL)
		return 0;

	return h_arraylist_add(table->rows, row);
}

int h_datatable_insert_row(Hdatatable *table, unsigned int idx, Harraylist *row)
{
	if(table == NULL)
		return 0;

	return h_arraylist_insert(table->rows, idx, row);
}

int h_datatable_remove_row(Hdatatable *table, unsigned int idx)
{
	if(table == NULL)
		return 0;

	return h_arraylist_remove(table->rows, idx);
}

int h_datatable_get_row_count(Hdatatable *table)
{
	if(table == NULL)
		return 0;

	return h_arraylist_get_length(table->rows);
}

int h_datatable_get_column_count(Hdatatable *table, unsigned int row_idx)
{
	if(table == NULL)
		return 0;

	Harraylist* row = h_arraylist_get(table->rows, row_idx);
	if(row == NULL)
		return 0;

	return h_arraylist_get_length(row);
}

Harraylist* h_datatable_get_row(Hdatatable *table, unsigned int row_idx)
{
	if(table == NULL)
		return NULL;

	return h_arraylist_get(table->rows, row_idx);
}

void* h_datatable_get_idx(Hdatatable *table, unsigned int row_idx, unsigned int column_idx)
{
	if(table == NULL)
		return NULL;

	Harraylist *row = h_arraylist_get(table->rows, row_idx);
	if(!row)
		return NULL;

	return h_arraylist_get(row, column_idx);
}

/*
 * load from string data.
 */
Hdatatable* h_datatable_load(char* str, char delim)
{
	char *curline, *nextline;

	Hdatatable *table = h_datatable_init();
	if(!table)
		return NULL;

	curline = str;
	while (curline) {
		nextline = strchr(curline, '\n');
		if(nextline) *nextline = '\0';				//temporary

		Harraylist *row = h_strtok(curline, delim);
		if(!row) {
			h_datatable_free(table);
			return NULL;
		}

		if(!h_datatable_add_row(table, row)) {
			h_datatable_free(table);
			return NULL;
		}


		if (nextline) *nextline = '\n'; 			//restore
		curline = nextline ? (nextline + 1) : NULL;
	}

	return table;
}

/*
 * load from file.
 */
Hdatatable* h_datatable_load_from_file(const char* filepath, char delim)
{
	char *tmp;
	char buffer[10240];
	int buffer_size = sizeof(buffer);

	Hdatatable *table = h_datatable_init();
	if(!table)
		return NULL;

	FILE *fp = fopen(filepath, "r");
	if(!fp) {
		h_datatable_free(table);
		return NULL;
	}


	while( fgets( buffer, buffer_size, fp) ) {

		if( (tmp = strchr(buffer, '\n')) != NULL)
			*tmp = '\0';				// remove \n


		Harraylist *row = h_strtok(buffer, delim);
		if(!row) {
			h_datatable_free(table);
			fclose(fp);
			return NULL;
		}

		if(!h_datatable_add_row(table, row)) {
			h_datatable_free(table);
			fclose(fp);
			return NULL;
		}
	}

	fclose(fp);
	return table;
}
