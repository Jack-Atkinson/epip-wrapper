/*
	etest.cpp

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


#include <e-lib.h>
#include <cstdio>

char output[64] SECTION("shared_dram");

int main(void) {
	e_coreid_t coreid;

	coreid = e_get_coreid();

	e_coreid_t *test = (e_coreid_t *)0x2000;

	sprintf(output, "Hello from Epiphany");
	test[0] = coreid;

	return E_OK;
}