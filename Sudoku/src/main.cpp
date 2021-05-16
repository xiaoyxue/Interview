#include <iostream>
#include <vector>

constexpr int n = 9;
int bitMap[1 << 9];
std::vector<unsigned short> rowBit, columnBit, blockBit;
int blockIndex[81];

int BlockIndex(int i, int j) 
{
	return (i / 3) * 3 + (j / 3);
}

void Init(const std::vector<std::vector<char>>& board) 
{
	rowBit = std::vector<unsigned short>(n, 0);
	columnBit = std::vector<unsigned short>(n, 0);
	blockBit = std::vector<unsigned short>(n, 0);
	for (int i = 0; i < n; ++i) {
		bitMap[1 << i] = i + 1;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			blockIndex[i * 9 + j] = BlockIndex(i, j);
			if (board[i][j] != '.') {
				rowBit[i] |= (1 << (board[i][j] - '0' - 1));
				columnBit[j] |= (1 << (board[i][j] - '0' - 1));
				blockBit[blockIndex[i * 9 + j]] |= (1 << (board[i][j] - '0' - 1));
			}
		}
	}
}

bool Dfs(int depth, std::vector<std::vector<char>>& board) {
	if (depth == 81) {
		return true;
	}
	int i = depth / n, j = depth % n;
	if (board[i][j] == '.')
	{
		unsigned short bits = (~((rowBit[i]) | (columnBit[j]) | (blockBit[blockIndex[depth]]))) & (0x01FF);
		for (; bits > 0; bits &= (bits - 1)) {
			int num = bitMap[bits & (bits - 1) ^ bits];
			int moveLength = num - 1;
			board[i][j] = num + '0';
			rowBit[i] |= (1 << moveLength);
			columnBit[j] |= (1 << moveLength);
			blockBit[blockIndex[depth]] |= (1 << moveLength);
			if (Dfs(depth + 1, board)) return true;
			blockBit[blockIndex[depth]] &= ~(1 << moveLength);
			columnBit[j] &= (~(1 << moveLength));
			rowBit[i] &= ~(1 << moveLength);
			board[i][j] = '.';
		}
	}
	else {
		if (Dfs(depth + 1, board)) return true;
	}
	return false;
}

void SolveSudoku(std::vector<std::vector<char>> &board)
{
	Init(board);
	Dfs(0, board);
}

void Print(const std::vector<std::vector<char>>& board)
{
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			std::cout << board[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	const char input[9][9] =
	{
		{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
		{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
		{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
		{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
		{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
		{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
		{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
		{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
		{'.', '.', '.', '.', '8', '.', '.', '7', '9'}
	};
	std::vector<std::vector<char>> board(9);
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			board[i].push_back(input[i][j]);
		}
	}
	SolveSudoku(board);
	Print(board);
	return 0;
}