#include <iostream>
#include <string>

void MoveOne(const std::string& from, const std::string& to)
{
	std::cout << from << " to " << to << std::endl;
}

void Hanoi(int n, const std::string& from, const std::string& to, const std::string& other)
{
	if (n == 1) {
		MoveOne(from, to);
		return;
	}
	Hanoi(n - 1, from, other, to);
	MoveOne(from, to);
	Hanoi(n - 1, other, to, from);
}

int main() 
{
	Hanoi(5, "A", "C", "B");
	return 0;
}