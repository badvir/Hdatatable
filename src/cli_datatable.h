/*
 * cli_datatable.h
 *
 *  Created on: 2015. 7. 20.
 *      Author: root
 */

#ifndef CLI_DATATABLE_H_
#define CLI_DATATABLE_H_

#include "h_datatable.h"

#define CLI_RESULT_OK_CODE			1
#define CLI_RESULT_ERROR_CODE		2
#define CLI_RESULT_INVALID_CODE		3


#define CLI_RESULT_OK_STR			"OK"
#define CLI_RESULT_ERROR_STR		"ERROR"
#define CLI_RESULT_INVALID_STR		"INVALID"


struct _cli_datatable {

	Hdatatable *table;

	int result;

	unsigned long long error_code;
	char *error_msg;
};

typedef struct _cli_datatable Cdatatable;

void cli_datatable_free(Cdatatable *ctable);
Cdatatable* cli_datatable_init();
int cli_datatable_get_row_count(Cdatatable *ctable);
int cli_datatable_get_column_count(Cdatatable *ctable, unsigned int row_idx);
Harraylist* cli_datatable_get_row(Cdatatable *ctable, unsigned int row_idx);
void* cli_datatable_get_idx(Cdatatable *ctable, unsigned int row_idx, unsigned int column_idx);
Cdatatable* cli_datatable_load(char* str);
Cdatatable* cli_datatable_load_from_file(const char* filepath);

#endif /* CLI_DATATABLE_H_ */
