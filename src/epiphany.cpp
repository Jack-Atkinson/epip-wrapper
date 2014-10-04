/*
	epiphany.cpp

	Contributed by Jack Atkinson <jack.atkinson@outlook.com>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program, see the file COPYING. If not, see
	<http://www.gnu.org/licenses/>.
*/

#include "epiphany.h"

Epiphany::Epiphany(void)
{
	fprintf(stdout, "[+] Starting the Epiphany....");
	switch(setup()) {
		case 0:    //Everything setup successfully
			fprintf(stdout, "OK\n");
			break;

		case 1:    //Error initializing the epiphany
			fprintf(stderr, "FAIL\n    - Could not initialize the Epiphany\n");
			break;

		case 2:    //Error getting platform info
			fprintf(stderr, "FAIL\n    - Could not get platform info\n");
			break;

		case 3:    //Error resetting the epiphany
			fprintf(stderr, "FAIL\n    - Could not reset the Epiphany\n");
			break;

		case 4:    //Error allocating memory to shared DRAM
			fprintf(stderr, "FAIL\n    - Could not allocate memory to shared DRAM\n");
			break;

		case 5:    //Error opening workgroup
			fprintf(stderr, "FAIL\n    - Could not open the eCore workgroup\n");
			break;
	}
}

Epiphany::Epiphany(char *executable, bool runOnLoad)
{
	fprintf(stdout, "[+] Starting the Epiphany and loading SREC....");
	switch(setup()) {
		case 0:    //Everything setup successfully
			fprintf(stdout, "OK\n");
			break;

		case 1:    //Error initializing the epiphany
			fprintf(stderr, "FAIL\n    - Could not initialize the Epiphany\n");
			break;

		case 2:    //Error getting platform info
			fprintf(stderr, "FAIL\n    - Could not get platform info\n");
			break;

		case 3:    //Error resetting the epiphany
			fprintf(stderr, "FAIL\n    - Could not reset the Epiphany\n");
			break;

		case 4:    //Error allocating memory to shared DRAM
			fprintf(stderr, "FAIL\n    - Could not allocate memory to shared DRAM\n");
			break;

		case 5:    //Error opening workgroup
			fprintf(stderr, "FAIL\n    - Could not open the eCore workgroup\n");
			break;
	}

	fprintf(stdout, "[+] Loading SREC on all cores....");
	if(e_load_group(executable, &myEpipData_.epip_, 0, 0, WORKGRP_ROWS, WORKGRP_COLS, E_FALSE) == E_ERR)
			fprintf(stdout, "FAIL\n    - Could not load SREC file onto the Epiphany\n");
	fprintf(stdout, "OK\n");
	
	if(runOnLoad == true) {
		fprintf(stdout, "[+] Executing SREC on all cores....");
		if(e_start_group(&myEpipData_.epip_) == E_ERR)
			fprintf(stdout, "FAIL\n    - Could not execute SREC file onto the Epiphany\n");
		fprintf(stdout, "OK\n");
	}
}

Epiphany::~Epiphany(void)
{
	fprintf(stdout, "[+] Stopping the Epiphany....");
	switch(finalize()){
		case 0:    //Everything setup successfully
			fprintf(stdout, "OK\n");
			break;

		case 1:    //Error closing the epiphany
			fprintf(stderr, "FAIL\n    - Could not close the Epiphany\n");
			break;

		case 2:    //Error freeing memory in shared DRAM
			fprintf(stderr, "FAIL\n    - Could not free memory in shared DRAM\n");
			break;

		case 3:    //Error finalizing the epiphany
			fprintf(stderr, "FAIL\n    - Could not finalize connection with the Epiphany\n");
			break;
	}
}

int
Epiphany::setup(void)
{
	if(e_init(NULL) == E_ERR)
		return 1;

	if(e_get_platform_info(&myEpipData_.platform_) == E_ERR)
		return 2;

	if(e_reset_system() == E_ERR)
		return 3;

	if(e_alloc(&myEpipData_.emem_, E_BUFF_OFFSET, E_BUFF))
		return 4;

	if(e_open(&myEpipData_.epip_, 0, 0, WORKGRP_ROWS, WORKGRP_COLS) == E_ERR)
		return 5;

	myEpipData_.workgroupSize_ = WORKGRP_ROWS * WORKGRP_COLS;

	return 0;
}

int
Epiphany::finalize(void)
{
	if(!e_close(&myEpipData_.epip_) == E_ERR)
		return 1;

	if(!e_free(&myEpipData_.emem_) == E_ERR)
		return 2;

	if(!e_finalize() == E_ERR)
		return 3;

	return 0;
}

e_platform_t*
Epiphany::getPlatform(void)
{
	return &myEpipData_.platform_;
}

e_epiphany_t*
Epiphany::getEpipAddr(void)
{
	return &myEpipData_.epip_;
}

e_mem_t*
Epiphany::getEmemAddr(void)
{
	return &myEpipData_.emem_;
}

unsigned
Epiphany::getWorkgroupSize(void)
{
	return myEpipData_.workgroupSize_;
}