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

#include "common.hpp"
#include "Client.hpp"

Client::~Client()
{
}


/*struct Cereal
{
	int arr[][];

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(arr); // serialize things by passing them to the archive
	}
};*/

void Client::initialize(unsigned int player, unsigned int board_size)
{
/*
	cereal::JSONOutputArchive archive( std::cout );
	int arr[board_size][board_size];
	archive(arr);
*/
	this->board_size = board_size;
	this->player = player;
	string fileName = "player_" + to_string(player) + ".action_board.json";


	int board[board_size];
	for(int i = 0; i < board_size; i++)
		for(int j = 0; j < board_size; j++)
		{
			board[i] = 0;
		}

	cereal::JSONOutputArchive archive(std::cout);



//	archive(board);

	ofstream file;
	file.open(fileName, ios::trunc | ios::out);

	file << "{\n"
			"    \"board\": [\n"
			"        [\n"
			"            0,\n"
			"            0\n"
			"        ],\n"
			"        [\n"
			"            0,\n"
			"            0\n"
			"        ]\n"
			"    ]\n"
			"}";
	file.close();
	initialized = true;
}


void Client::fire(unsigned int x, unsigned int y)
{
	if(x >= 0 && x < board_size && y >= 0 && y < board_size)
	{
		string fileName = "player_" + to_string(player) + ".shot.json";
		fstream file;
		file.open(fileName, ios::trunc | ios::out);
		file << "{\n"
				"    \"x\": " + to_string(x) + ",\n"
				"    \"y\": " + to_string(y) + "\n"
				"}";
	}
}


bool Client::result_available()
{
}


int Client::get_result()
{
}


void Client::update_action_board(int result, unsigned int x, unsigned int y)
{
}


string Client::render_action_board()
{
}