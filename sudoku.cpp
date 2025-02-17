#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>

// easy
// int board[9][9] = {

// {1,8,5 , 6,0,0 , 0,9,3}, //3!*3!*1!*2!*3!*2!*2!*3!*2! = 20'736
// {6,2,7 , 0,0,0 , 8,1,5},
// {9,4,3 , 0,5,1 , 2,6,7},

// {5,9,1 , 0,0,3 , 7,2,6},
// {7,3,4 , 0,6,0 , 0,8,1},
// {2,6,0 , 0,1,5 , 3,4,9},

// {3,5,0 , 1,4,8 , 0,7,2},
// {8,1,0 , 0,7,0 , 9,3,4},
// {4,7,0 , 0,3,6 , 1,5,8}
// };

// medium
// int board[9][9] = {

// {0,0,6 , 0,0,0 , 5,0,8}, //6!*4!*6!*5!*3!*5!*6!*4!*6! = 13'374'150'672'384'000'000
// {1,0,2 , 3,8,0 , 0,0,4},
// {0,0,0 , 2,0,0 , 1,9,0},

// {0,0,0 , 0,6,3 , 0,4,5},
// {0,6,3 , 4,0,5 , 8,7,0},
// {5,4,0 , 9,2,0 , 0,0,0},

// {0,8,7 , 0,0,4 , 0,0,0},
// {2,0,0 , 0,9,8 , 4,0,7},
// {4,0,9 , 0,0,0 , 3,0,0}
// };

// hard
int board[9][9] = {
	
{8,0,0 , 0,0,0 , 0,0,0}, //8!*7!*6!*7!*6!*7!*6!*6!*7! = 6'991'536'913'309'973'348'352'000'000'000
{0,0,3 , 6,0,0 , 0,0,0}, // 
{0,7,0 , 0,9,0 , 2,0,0},	
	
{0,5,0 , 0,0,7 , 0,0,0},
{0,0,0 , 0,4,5 , 7,0,0},
{0,0,0 , 1,0,0 , 0,3,0},
	
{0,0,1 , 0,0,0 , 0,6,8},
{0,0,8 , 5,0,0 , 0,1,0},
{0,9,0 , 0,0,0 , 4,0,0}
	
};


void print_board(int board[9][9])
{	
	std::cout << "+-------+-------+-------+\n";
	
	int count_horiz = 1;
	for (int x = 0; x < 9; x++)
	{
		int count_vert = 1;
		for (int y = 0; y < 9; y++)
		{	
			if (count_vert == 1) std::cout << "| ";

			if (board[x][y] != 0) std::cout << board[x][y] << " ";
			else std::cout << "  ";
			
			if (count_vert % 3 == 0) std::cout << "| ";
			count_vert++;
		}
		std::cout << "\n";
		
		if (count_horiz % 3 == 0) std::cout << "+-------+-------+-------+\n";
		count_horiz++;
	}
}


int identify_square(std::pair<int,int> coords)
{
	switch (coords.first)
	{
	case 0 ... 2:
		switch (coords.second)
		{
		case 0 ... 2: return 0;
		case 3 ... 5: return 1;
		case 6 ... 8: return 2;
		}
	
	case 3 ... 5:
		switch (coords.second)
		{
		case 0 ... 2: return 3;
		case 3 ... 5: return 4;
		case 6 ... 8: return 5;
		}
	
	case 6 ... 8:
		switch (coords.second)
		{
		case 0 ... 2: return 6;
		case 3 ... 5: return 7;
		case 6 ... 8: return 8;
		}
		
	default: std::cout << "oh no" << std::endl; return -1;
	}
}


bool is_in_array(int num, int group[9])
{
	for(int x = 0; x < 9; x++)
	{
		if (group[x] == num)
			return true;
	}

	return false;
}


std::vector<std::pair<int,int>> unknown_numbers()
{
	std::vector<std::pair<int,int>> v;
	
	for(int x = 0; x < 9; x++)
	{
		for(int y = 0; y < 9; y++)
		{
			if(board[x][y] == 0)
			{
				std::pair<int,int> coords = {x,y};
				v.push_back(coords);
			}
		}
	}

	return v;
}


std::vector<std::vector<int>> find_possible_numbers(int board_columns[9][9], int board_squares[9][9], std::vector<std::pair<int,int>> empty_boxes)
{
	std::vector<std::vector<int>> final_nums;
	std::vector<int> possible_nums;
	
	for(std::pair<int,int> pair : empty_boxes)
	{
		possible_nums = {};
		
		for(int x = 1; x < 10; x++)
		{
			if (
				not is_in_array(x,board[pair.first]) && 
				not is_in_array(x,board_columns[pair.second]) && 
				not is_in_array(x,board_squares[identify_square(pair)])
			   )
				
				possible_nums.push_back(x);
	
		
		}
		final_nums.push_back(possible_nums);
	}
	
	return final_nums;
}


void create_colmun_and_square_board(int board[9][9], int board_columns[9][9], int board_squares[9][9])
{
	
	for(int x = 0; x < 9; x++)
	{
		board_columns[0][x] = board[x][0];
		board_columns[1][x] = board[x][1];
		board_columns[2][x] = board[x][2];

		board_columns[3][x] = board[x][3];
		board_columns[4][x] = board[x][4];
		board_columns[5][x] = board[x][5];

		board_columns[6][x] = board[x][6];
		board_columns[7][x] = board[x][7];
		board_columns[8][x] = board[x][8];
	}

	int it = 0;
	for(int y = 0; y < 9; y += 3)
	{
		int itter = 0;
		
		for(int x = 0; x < 3; x++)
		{
			board_squares[y][0 + itter] = board[x + it][0];
			board_squares[y][1 + itter] = board[x + it][1];
			board_squares[y][2 + itter] = board[x + it][2];
			
			board_squares[y+1][0 + itter] = board[x + it][3];
			board_squares[y+1][1 + itter] = board[x + it][4];
			board_squares[y+1][2 + itter] = board[x + it][5];
			
			board_squares[y+2][0 + itter] = board[x + it][6];
			board_squares[y+2][1 + itter] = board[x + it][7];
			board_squares[y+2][2 + itter] = board[x + it][8];
			
			itter += 3;
		}
		it += 3;
	}
}


bool number_cannot_be_in_board(int x, std::pair<int,int> position, int board[9][9])
{	
	int board_columns[9][9];
	int board_squares[9][9];
	
	create_colmun_and_square_board(board, board_columns, board_squares);
	
	if (is_in_array(x,board[position.first])) return true;
	if (is_in_array(x,board_columns[position.second])) return true;
	if (is_in_array(x,board_squares[identify_square(position)])) return true;
	
	return false;
}

void backtracking_solver(int board[9][9], int &guess_number)
{
	std::vector<std::vector<int>> possible_numbers;
	std::vector<std::pair<int,int>> empty_boxes;
	int board_columns[9][9];
	int board_squares[9][9];
	
	create_colmun_and_square_board(board, board_columns, board_squares);

	empty_boxes = unknown_numbers();
	possible_numbers = find_possible_numbers(board_columns, board_squares, empty_boxes);
	
	int num_of_unknown = empty_boxes.size();
	
	int most_recent_position[num_of_unknown];
	for(int x = 0; x < num_of_unknown; x++)
		most_recent_position[x] = 0;
	
	bool gone_back = false;
	
	
	
	for (int coords = 0; coords < empty_boxes.size(); coords++)
	{
		bool number_given = false;
		
		for (int possibles = most_recent_position[coords]; possibles < possible_numbers[coords].size(); possibles++)
		{
			
			for (int x = coords; x < empty_boxes.size()-1; x++)
				most_recent_position[coords+1] = 0;
			
			
			if (gone_back)
			{
				gone_back = false;
				board[empty_boxes[coords].first][empty_boxes[coords].second] = 0;
				possibles++;
			}
			
			if (possibles == possible_numbers[coords].size())
				break;
			
			if (not number_cannot_be_in_board(possible_numbers[coords][possibles], empty_boxes[coords], board))
			{
				board[empty_boxes[coords].first][empty_boxes[coords].second] = possible_numbers[coords][possibles];
				guess_number++;
				number_given = true;
				most_recent_position[coords] = possibles;
				
				break;
			}
		
		}
		
		if (not number_given)
		{
			coords -= 2;
			gone_back = true;
		}
	}
}


int main()
{
	int guess_number = 0;
	
	auto start = std::chrono::high_resolution_clock::now();

    backtracking_solver(board, guess_number);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Duration: " << duration.count() << " seconds" << std::endl;
	
	
	
	std::cout << "total guesses: " <<  guess_number << std::endl;
	
	print_board(board);
	
	return 0;
}
