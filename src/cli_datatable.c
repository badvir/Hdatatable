/*
 * cli_datatable.c
 *
 *  Created on: 2015. 7. 20.
 *      Author: root
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli_datatable.h"


void cli_datatable_free(Cdatatable *ctable)
{
	if(ctable == NULL)
		return;

	h_datatable_free(ctable->table);
	free(ctable);
}

Cdatatable* cli_datatable_init()
{
	Cdatatable *ctable = (Cdatatable*)calloc(1, sizeof(Cdatatable));
	if(!ctable)
		return NULL;

	memset(ctable, 0, sizeof(*ctable));
	return ctable;
}

int cli_datatable_get_row_count(Cdatatable *ctable)
{
	if(ctable == NULL)
		return 0;

	return h_arraylist_get_length(ctable->table->rows);
}

int cli_datatable_get_column_count(Cdatatable *ctable, unsigned int row_idx)
{
	if(ctable == NULL)
		return 0;

	Harraylist* row = h_arraylist_get(ctable->table->rows, row_idx);
	if(row == NULL)
		return 0;

	return h_arraylist_get_length(row);
}


Harraylist* cli_datatable_get_row(Cdatatable *ctable, unsigned int row_idx)
{
	if(ctable == NULL)
		return NULL;

	return h_arraylist_get(ctable->table->rows, row_idx);
}

void* cli_datatable_get_idx(Cdatatable *ctable, unsigned int row_idx, unsigned int column_idx)
{
	if(ctable == NULL)
		return NULL;

	Harraylist *row = h_arraylist_get(ctable->table->rows, row_idx);
	if(!row)
		return NULL;

	return h_arraylist_get(row, column_idx);
}

Cdatatable* cli_datatable_load(char* str)
{
	Cdatatable *ctable = cli_datatable_init();
	if(!ctable)
		return NULL;

	Hdatatable *table = h_datatable_load(str, '^');
	if(!table) {
		cli_datatable_free(ctable);
		return NULL;
	}

	char *result = h_datatable_get_idx(table, 0, 0);
	if(result != NULL && strcmp(result, CLI_RESULT_OK_STR) == 0) {
		ctable->result = CLI_RESULT_OK_CODE;

		//remove OK Sting
		h_datatable_remove_row(ctable->table, 0);

	} else if(result != NULL && strcmp(result, CLI_RESULT_ERROR_STR) == 0) {
		ctable->result = CLI_RESULT_ERROR_CODE;

		char *err_code = h_datatable_get_idx(table, 1, 0);
		char *err_msg =  h_datatable_get_idx(table, 1, 1);

		if(err_code) ctable->error_code = strtoull(err_code, NULL, 10);
		if(err_msg) ctable->error_msg = err_msg;

	} else {
		ctable->result = CLI_RESULT_INVALID_CODE;
		ctable->error_msg =  CLI_RESULT_INVALID_STR;
	}

	ctable->table = table;
	return ctable;
}

Cdatatable* cli_datatable_load_from_file(const char* filepath)
{
	Cdatatable *ctable = cli_datatable_init();
	if(!ctable)
		return NULL;

	Hdatatable *table = h_datatable_load_from_file(filepath, '^');
	if(!table) {
		cli_datatable_free(ctable);
		return NULL;
	}

	char *result = h_datatable_get_idx(table, 0, 0);
	if(result != NULL && strcmp(result, CLI_RESULT_OK_STR) == 0) {
		ctable->result = CLI_RESULT_OK_CODE;

	} else if(result != NULL && strcmp(result, CLI_RESULT_ERROR_STR) == 0) {
		ctable->result = CLI_RESULT_ERROR_CODE;

		char *err_code = h_datatable_get_idx(table, 1, 0);
		char *err_msg =  h_datatable_get_idx(table, 1, 1);

		if(err_code) ctable->error_code = strtoull(err_code, NULL, 10);
		if(err_msg) ctable->error_msg = err_msg;

	} else {
		ctable->result = CLI_RESULT_INVALID_CODE;
		ctable->error_msg =  CLI_RESULT_INVALID_STR;
	}

	//remove OK/ERROR Sting
	if(ctable->result != CLI_RESULT_INVALID_CODE)
		h_datatable_remove_row(table, 0);

	ctable->table = table;
	return ctable;
}

