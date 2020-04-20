//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <math.h>
#include "BitArray2D.hpp"

BitArray2D::BitArray2D(unsigned int rows, unsigned int columns) {
	if(rows < 1 || columns < 1)
		throw BitArray2DException("error");
	this->rows = rows;
	this->columns = columns;

	int numBits = ceil(((double)rows * columns)/8);
	this->array = (char*) calloc(numBits, sizeof(char));
}

BitArray2D::~BitArray2D() {

}

bool BitArray2D::get(unsigned int row, unsigned int column){
	// check array bounds
	if(row < 0 || column < 0 || row >= rows || column >= columns)
		throw BitArray2DException("error");
	// get the element
	return get_bit_elem(array, columns, row, column);
}

void BitArray2D::set(unsigned int row, unsigned int column){
	// check array bounds
	if(row < 0 || column < 0 || row >= rows || column >= columns)
		throw BitArray2DException("error");
	// set the element
	set_bit_elem(array, columns, row, column);
}