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
#include "epiphany.h"

int main(int argc, char *argv[])
{
	Epiphany epiphany("etest.srec", true);
	//change name of getEpip to something like getEpipAddr
	//e_start(epiphany.getEpipAddr(), 0, 0);
	//char input[1024];
	//e_read(epiphany.getEmem(), 0, 0, 0x0, input, 1024);

	//fprintf(stdout, "%s\n", input);

	return EXIT_SUCCESS;
}