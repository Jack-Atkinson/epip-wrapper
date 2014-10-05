/*
	main.cpp

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

/*
	For fast.ldf and internal.ldf, the address of SRAM where you can start to place data begins
	two words after the address of the .bss section in the elf file that gets
	converted to srec format. Ex: If the .bss section is at 000002c8, then you
	should start writing data to address 0x02d0
*/

#include <cstdlib>
#include <e-hal.h>
#include <unistd.h>

#include "epiphany.h"


int main(int argc, char *argv[])
{
	Epiphany epiphany("etest.srec", false);

	e_start(epiphany.getEpipAddr(), 0, 0);

	char dataFromShared[64];
	unsigned dataFromLocal;
	usleep(10000);
	e_read(epiphany.getEmemAddr(), 0, 0, 0x0, dataFromShared, 64);
	e_read(epiphany.getEpipAddr(), 0, 0, 0x2000, &dataFromLocal, sizeof(unsigned));
	fprintf(stdout, "Data from shared mem (string): %s\nData from local mem (coreid): %x\n", dataFromShared, dataFromLocal);

	return EXIT_SUCCESS;
}