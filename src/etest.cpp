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

int output[1024] SECTION("shared_dram");

int main(void) {
	e_coreid_t coreid;

	coreid = e_get_coreid();

	e_coreid_t *test = (e_coreid_t *)0x2000;

	test[0] = 0xdeadbeef;

	return E_OK;
}

int startCore(int row, int col)
{
	int sync = 1;
	e_coreid_t coreid;
	coreid = e_coreid_from_coords(row, col);
	if(!(coreid == e_get_coreid())) {
		coreid <<= 20; //turns the local coreid into a global core address ex: 0x00000809 -> 0x80900000
		coreid += E_REG_ILATST; //address of ILATST reg
		e_write(&e_group_config, &sync, row, col, (e_coreid_t *)coreid, sizeof(int));
	}
	return E_OK;
}