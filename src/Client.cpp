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
		fstream file;
		file.open(fileName, ios::trunc | ios::out);
		file << "{\n"
				"    \"x\": " + to_string(x) + ",\n"
				"    \"y\": " + to_string(y) + "\n"
				"}";
	}
}

/**
	* Checks if a result file is available for
	* @return true if result is available, false otherwise
	*/
bool Client::result_available()//TODO: Not working
{
	/*Leaving this function empty passes more tests than putting code in it.*/
	int opponent;
	if(player == 1)
		opponent = 2;
	else
		opponent = 1;

	string fileName = "player_" + to_string(opponent) + ".result.json";
	ofstream file;
	file.open(fileName);
	return !!file;
}


/**
 * Gets the result from the player_#.result.json
 * @return the result as either HIT, MISS, or OUT_OF_BOUNDS
 */
int Client::get_result()//TODO: Not working
{
	if(result_available())
	{
		vector<int> result(1);
		int opponent;
		if(player == 1)
			opponent = 2;
		else
			opponent = 1;

		string fileName = "player_" + to_string(opponent) + ".result.json";
		ifstream file;
		file.open(fileName);

		cereal::JSONInputArchive archive(file);
		archive(result);
		//write to the file
		fileName = "player_" + to_string(player) + ".result.json";

		ofstream out (fileName);
		cereal::JSONOutputArchive ar(out);
		ar(CEREAL_NVP(result[0]));
		out.close();
		file.close();
//		cout << result[0] << " woeifhowie fwhr goilwi ufibgibw flibrvibrgibribirb arblieriua eilf ibviuaburvbifiiueriharlaergilh" << endl;
		//hit = 1, miss = -1
		if(result[0] == 1)
			return HIT;
		return MISS;
	}
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
}