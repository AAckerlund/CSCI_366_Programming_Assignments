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
	/*
	Calculate the length of a file (helper function)
	@param file - the file whose length we want to query
	@return length of the file in bytes
	*/
}


void Server::initialize(unsigned int board_size, string p1_setup_board, string p2_setup_board)
{
	/*
	Performs Server initialization
	Need to do initialization outside of the constructor, so that the object may be initialized inside the googletest SetUp() method.
	The method opens player setup boards containing ship positions and checks the size of boards compared to board_size parameter.
	@param board_size - the size of a square board
	@param p1_setup_board - file name of player 1's board
	@param p2_setup_board - file name of player 2's board
	 */
	ifstream file;
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
	//cout << "Player 1 setup board is correct." << endl;

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
	//cout << "Player 2 setup board is correct." << endl;
}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y)//TODO: not finished
{
	/*
	Checks the coordinates of a shot against setup board of player
	Check that player number within bounds, checks that shot coordinates within bounds, determines if the shot results in a HIT, or a MISS.
	@param player - player number
	@param x - coordinate (what character in the given line)
	@param y - coordinate (What line the character is in)
	@return returns shot result as either HIT, MISS, or OUT_OF_BOUNDS
	*/
	//make sure values are correct
	if(player > MAX_PLAYERS)//Player number is too high
		throw ServerException("Player Number too high. Program Terminating.");
	if(player <= 0)//Player number is too low
		throw ServerException("Player number too low. Program Terminating.");
	if(x < 0 || x > board_size || y < 0 || y > board_size)//one of the coordinates is outside the range of the board.
		return OUT_OF_BOUNDS;

	string filePath = "player_" + to_string(player) + ".setup_board.txt";
	ifstream file;
	file.open(filePath);
	if(!file) //file not opened for whatever reason.
		return NO_SHOT_FILE;
	string line;

	char spot = '_';
	for(int lineNum = 0; file >> line; lineNum ++)
	{
		if(lineNum == y)
		{
			spot = line[y];
			cout << spot;
		}
	}
	if(spot == '_')//miss
		return MISS;
	return HIT;
}


int Server::process_shot(unsigned int player)//TODO: using the player number, looks for a file created by them. Reads in the x and y guess from that file and then passes them to evaluate_shot
{
	/*
	Processes a shot issued by player
    Gets the shot from player, extracts coordinates, passes the information of evaluate_shot, and writes the result into player_#.result.json.
    @param player - player number
    @return returns SHOT_PROCESSED, or NO_SHOT_FILE if nothing to process
    */
	if(player > MAX_PLAYERS)//Player number is too high
		throw ServerException("Player Number too high. Program Terminating.");
	if(player <= 0)//Player number is too low
		throw ServerException("Player number too low. Program Terminating.");

	string filePath = "player_" + to_string(player) + ".shot.json";
	ifstream file;
	file.open(filePath);
	if(!file) //file not opened for whatever reason.
		return NO_SHOT_FILE;

/*	vector<vector<int>> board(board_size, vector<int> (board_size));


	cereal::JSONInputArchive archive(file);
	archive(board);

	board[2][3] = 7;// how to access a value*/
	file.close();

	//need to actually get the values from the file.
	//evaluate_shot(player, 1,1);
    return SHOT_FILE_PROCESSED;
}