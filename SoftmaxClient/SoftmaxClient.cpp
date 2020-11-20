#include <iostream>
#include "SoftmaxLib.h"
#include <string>

const char EOLN = '\n';
const char YES_CHAR = 'Y';
const char NO_CHAR = 'N';
const int LEFT_BOUND = -1000000000;
const int RIGHT_BOUND = +1000000000;
const std::string INCORRECT_MESSAGE =
"Input is incorrect. Try again>";
const std::string OUT_OF_BOUNDS_MESSAGE =
"This number is out of bounds";
const std::string SKIP_CHARACTERS = " ";

void ClearInputStream(std::istream& in)
{
	in.clear();
	while (in.peek() != EOLN && in.peek() != EOF)
	{
		in.get();
	}
}

int Seek(std::istream& in)
{
	while (in.peek() != EOLN && SKIP_CHARACTERS.find((char)in.peek()) != std::string::npos)
	{
		in.get();
	}
	return in.peek();
}

bool CheckBounds(int n)
{
	bool ok = (LEFT_BOUND <= n && n <= RIGHT_BOUND);
	if (!ok)
	{
		std::cout << OUT_OF_BOUNDS_MESSAGE << " [" << LEFT_BOUND << ", " << RIGHT_BOUND << "]" << std::endl;
	}
	return ok;
}

int ReadInt(std::istream& in)
{
	int ans;
	in >> ans;
	while (!in || Seek(in) != EOLN || !CheckBounds(ans))
	{
		ClearInputStream(in);
		std::cout << INCORRECT_MESSAGE;
		in >> ans;
	}
	return ans;
}

bool NeedContinue(std::istream& in)
{
	std::cout << "\nContinue? (Y/N)>";
	char ans;
	in >> ans;
	while (!in || Seek(in) != EOLN || ans != YES_CHAR && ans != NO_CHAR)
	{
		ClearInputStream(in);
		std::cout << INCORRECT_MESSAGE;
		in >> ans;
	}
	return ans == YES_CHAR;
}

int main()
{
	std::cout << "The derivative of softmax function\n\n";
	bool cont = true;
	while (cont)
	{
		std::cout << "Size of an array z> ";
		int n = ReadInt(std::cin);
		std::cout << EOLN;
		int *z = new int[n];
		for (int i = 0; i < n; ++i)
		{
			std::cout << "z[" << i << "] = ";
			z[i] = ReadInt(std::cin);
		}
		std::cout << "\nResult:\n";
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				std::cout << softmax_grad(z, n)[i][j] << ' ';
			}
			std::cout << EOLN;
		}
		cont = NeedContinue(std::cin);
		std::cout << EOLN;
	}
	return 0;
}