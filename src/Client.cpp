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


void Client::initialize(unsigned int player, unsigned int board_size)
{
	this->board_size = board_size;
	this->player = player;
	string fileName = "player_" + to_string(player) + ".action_board.json";

	vector<vector<int>> board(board_size, vector<int> (board_size, 0));

	ofstream file (fileName);

	cereal::JSONOutputArchive archive(file);
	archive(CEREAL_NVP(board));

	initialized = true;
}

void Client::fire(unsigned int x, unsigned int y)
{
	if(x >= 0 && x < board_size && y >= 0 && y < board_size)
	{
		string fileName = "player_" + to_string(player) + ".shot.json";
		ofstream file (fileName);

		cereal::JSONOutputArchive archive(file);
		archive(CEREAL_NVP(x),CEREAL_NVP(y));
	}
}

bool Client::result_available()
{
	string fileName = "player_" + to_string(player) + ".result.json";
	ifstream file (fileName);
	if(!file)
		return false;
	return true;
}

int Client::get_result()
{
	int result;

	string fileName = "player_" + to_string(player) + ".result.json";
	ifstream file(fileName);
	if(!file)
	{
		throw ClientException("File does not exist. Program Terminating.");
	}
	cereal::JSONInputArchive archive(file);
	archive(result);
	file.close();

	remove(fileName.c_str());//deletes the result file so that the sever doesn't continue to read it.
	//hit = 1, miss = -1, oob = 0
	if(result == 1)
	{
		return HIT;
	}
	else if(result == 0)
	{
		return OUT_OF_BOUNDS;
	}
	else if(result == -1)
	{
		return MISS;
	}
	throw ClientException("Bad result value. Program Terminating.");
}

void Client::update_action_board(int result, unsigned int x, unsigned int y)
{
	vector<vector<int>> board(board_size, vector<int> (board_size, 0));

	string fileName = "player_" + to_string(player) + ".action_board.json";
	ifstream file;
	file.open(fileName);

	cereal::JSONInputArchive archive(file);
	archive(board);
	file.close();

	if(result == HIT)
		board[x][y] = HIT;
	else
		board[x][y] = MISS;

	ofstream out (fileName);

	cereal::JSONOutputArchive ar(out);
	ar(CEREAL_NVP(board));

}

string Client::render_action_board()
{
	vector<vector<int>> board(board_size, vector<int>(board_size, 0));

	string fileName = "player_" + to_string(player) + ".action_board.json";
	ifstream file;
	file.open(fileName);

	cereal::JSONInputArchive archive(file);
	archive(board);
	file.close();
	for(int i = 0; i < board_size; i++)
	{
		for(int j = 0; j < board_size; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	return "done";
}