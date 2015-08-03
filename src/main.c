/*
 * main.c
 *
 *  Created on: 2015. 6. 23.
 *      Author: root
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "h_strtok.h"
#include "h_datatable.h"
#include "cli_datatable.h"

int sortfun(const void *s1,const void *s2) {

	 return strcmp( (char *)s1, (char *)s2);

}

int main(int argc, char** argv)
{

	int i,j;
	int c = 1;

	/*
	Hdatatable *table = h_datatable_load_from_file("/root/ips", '\t');
	if(!table) {
		printf("invalid \n");
		return 0;
	}

	int rows = h_datatable_get_row_count(table);
	for(i=0; i<rows; i++) {
		printf("%s=%s\n", (char*)h_datatable_get_idx(table, i, 0),  (char*)h_datatable_get_idx(table, i, 1));
	}

	h_datatable_free(table);
	return 0;
*/

	char buffer[1280];

	while(c) {
		char *str = (char *)malloc(20240);
		sprintf(str, "a");

		for(j=0; j< 10; j++) {
			for(i=100; i>0; i--) {
				sprintf(buffer, "%d_asdfasdf_%d^", i, i);
				strcat(str, buffer);
			}

			strcat(str, "\n");
		}

		Hdatatable *table = h_datatable_load(str, '^');
		for(i=0; i<h_datatable_get_row_count(table); i++) {
			for(j=0; j<105; j++) {
				printf("%d:%d : %s\n", i, j, h_datatable_get_idx(table, i, j));
			}
		}

		h_datatable_free(table);

		c++;

		free(str);

		if(c > 10)
			break;
	}



	/*
	Cdatatable *ctable = cli_datatable_load_from_file("/root/app_list_stms");
	if(!ctable) {
		printf("%s\n", "ctable is null");
		return 0;
	}

	if(ctable->result != CLI_RESULT_OK_CODE) {
		printf("errcode : %llu\n", ctable->error_code);
		printf("errmsg : %s\n", ctable->error_msg);
	}

//	if(!h_datatable_remove_row(ctable->table, 0)) {
//
//		return;
//	}

//	Harraylist *row = h_strtok("test", '^');
//
//	if(!h_datatable_insert_row(ctable->table, 2667, row)) {
//		h_arraylist_free(row);
//		cli_datatable_free(ctable);
//		return 0;
//	}


	for(i=0; i<cli_datatable_get_row_count(ctable); i++) {

		int column = cli_datatable_get_column_count(ctable, i);
		for(j=0; j<column; j++) {

//			char *pp = (char*)h_datatable_get_idx(table, i, j);
			char *c = (char*)cli_datatable_get_idx(ctable, i, j);
			printf("%d:%d : %s\n", i, j, c);
		}

		if(i == 3)
			break;
//		Harraylist* row = cli_datatable_get_row(ctable, i);
//		if(h_strtok_contains(row, "web-based")) {
//			printf("!!!!!!!!!!!!!!!!! %d:%d : %s\n", i, j, (char*)cli_datatable_get_idx(ctable, i, j));
////			break;
//		}
	}

	cli_datatable_free(ctable);
*/
}
