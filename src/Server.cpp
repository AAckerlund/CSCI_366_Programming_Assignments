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
#include "Server.hpp"

int get_file_length(ifstream *file)
{
}

void Server::initialize(unsigned int board_size, string p1_setup_board, string p2_setup_board)
{
	ifstream file;
	this->board_size = board_size;
	//opens and reads in data from the given file
	file.open(p1_setup_board);
	if(!file)//file was not opened for whatever reason
	{
		throw ServerException("Unable to open player 1 setup board file. Program Terminating.");
	}
	string line;
	int lineCount = 0;
	while(file >> line)
	{
		if(line.length() == board_size)
		{
			lineCount++;
		}
		else
		{
			throw ServerException("Player 1 setup board contains an invalid line length. Program Terminating." );
		}
	}
	if(lineCount != board_size)
	{
		throw ServerException("Player 1 setup board contains an invalid number of lines. Program Terminating.");
	}
	file.close();

	//do it again for the other player
	file.open(p2_setup_board);
	if(!file)//file was not opened for whatever reason
	{
		throw ServerException("Unable to open player 1 setup board file. Program Terminating.");
	}
	line = "";
	lineCount = 0;
	while(file >> line)
	{
		if(line.length() == board_size)
		{
			lineCount++;
		}
		else
		{
			throw ServerException("Player 2 setup board contains an invalid line length. Program Terminating.");
		}
	}
	if(lineCount != board_size)
	{
		throw ServerException("Player 2 setup board contains an invalid number of lines. Program Terminating.");
	}
	file.close();
}

int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y)//TODO: not finished
{
	//make sure values are correct
	if(player > MAX_PLAYERS)//Player number is too high
		throw ServerException("Player Number too high. Program Terminating.");
	if(player <= 0)//Player number is too low
		throw ServerException("Player number too low. Program Terminating.");
	if(x < 0 || x > board_size || y < 0 || y > board_size)//one of the coordinates is outside the range of the board.
		return OUT_OF_BOUNDS;

	//flip to the opponents player number
	if(player == 1)
		player = 2;
	else
		player = 1;

	string filePath = "player_" + to_string(player) + ".setup_board.txt";
	ifstream file;
	file.open(filePath);
	if(!file) //file not opened for whatever reason.
		return NO_SHOT_FILE;
	string board[board_size];
	string line;
	int i = 0;
	while(file>>line)
	{
		board[i] = line;
		i++;
	}
	file.close();

	if(board[y][x] == '_')//(x,y) is indexed at [y][x]
	{
		return -1;//miss
	}
	return 1;//hit
}

int Server::process_shot(unsigned int player)
{
	if(player > MAX_PLAYERS)//Player number is too high
		throw ServerException("Player Number too high. Program Terminating.");
	if(player <= 0)//Player number is too low
		throw ServerException("Player number too low. Program Terminating.");

	string filePath = "player_" + to_string(player) + ".shot.json";
	ifstream file;
	file.open(filePath);
	if(!file) //file not opened for whatever reason.
	{
		return NO_SHOT_FILE;
	}
	int x,y;

	cereal::JSONInputArchive archive(file);
	archive(x,y);

	remove(filePath.c_str());//delete the shot file so the sever doesn't continue to detect it.

	//check shot and generate shot.json file
	filePath = "player_" + to_string(player) + ".result.json";
	ofstream out (filePath);
	cereal::JSONOutputArchive ar(out);

	int result;
	if(x < 0 || x >= board_size || y < 0 || y >= board_size)
	{
		result = 0;
		ar(CEREAL_NVP(result));
		return 0;
	}
	file.close();

	result = evaluate_shot(player,x,y);
	ar(CEREAL_NVP(result));
	if(result == NO_SHOT_FILE)
	{
		return NO_SHOT_FILE;
	}
    return SHOT_FILE_PROCESSED;
}