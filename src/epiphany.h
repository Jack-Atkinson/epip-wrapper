/*
	epiphany.h

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

#ifndef _H_EPIP_HOST
#define _H_EPIP_HOST

#include <e-hal.h>
#include <cstdio>

/* Define the desired workgroup size.
   If it exceeds the chip's capabilites it will default to max possible. */
#define WORKGRP_ROWS 4 //add check to make sure these are not 0 or negative
#define WORKGRP_COLS 4


/* Define the shared memory buffer and offset */
#define E_BUFF 64
#define E_BUFF_OFFSET 0x01000000

class Epiphany {
  public:
	Epiphany(void);
	Epiphany(char*, bool); //srec filename, runOnLoad(true/false)
	~Epiphany(void);

	int setup(void);
	int finalize(void);

	e_platform_t* getPlatform(void);
	e_epiphany_t* getEpipAddr(void);
	e_mem_t*      getEmemAddr(void);
	unsigned      getWorkgroupSize(void);

  private:
	struct {
		e_platform_t  platform_;
		e_epiphany_t  epip_;
		e_mem_t       emem_;
		unsigned      workgroupSize_;
	} myEpipData_;
};

#endif