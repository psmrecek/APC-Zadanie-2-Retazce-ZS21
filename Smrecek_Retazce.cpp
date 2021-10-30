#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>

/// <summary>
/// Function translates absolute file coordinates of occurence to line format.
/// </summary>
/// <param name="position">absolute coordinates of occurrence</param>
/// <param name="lineSizes">vector of line sizes</param>
void decoder(const uint64_t& position, std::vector<size_t>& lineSizes)
{
	uint64_t sumOfLines = 0;

	for (size_t i = 0; i < lineSizes.size(); i++)
	{
		sumOfLines += lineSizes[i];
		if (sumOfLines > position)
		{
			sumOfLines -= lineSizes[i];
			std::cout << i << " " << position - sumOfLines << std::endl;
			return;
		}
	}
}

/// <summary>
/// Function finds the size of all lines and stores them in the vector.
/// </summary>
/// <param name="buffer">chunk of text loaded from file</param>
/// <param name="sizeBuff">size of chunk</param>
/// <param name="pendingCharacters">number of characters that have not yet been added to the line</param>
/// <param name="lineSizes">vector of line sizes</param>
void findNL(const std::string& buffer, const size_t& sizeBuff, size_t& pendingCharacters, std::vector<size_t>& lineSizes)
{
	std::string newLine = "\n";
	size_t off = 0;

	size_t positionNL = buffer.find(newLine, off);
	size_t lastPositionNL = 0;

	while (positionNL != std::string::npos)
	{
		lineSizes.push_back(pendingCharacters + positionNL - lastPositionNL);

		lastPositionNL = positionNL;
		pendingCharacters = 0;
		off = positionNL;
		positionNL = buffer.find(newLine, off + 1);
	}

	pendingCharacters += sizeBuff - lastPositionNL;
}

/// <summary>
/// Function looks for the string X in the chunk.
/// </summary>
/// <param name="buffer">chunk of text loaded from file</param>
/// <param name="sizeBuff">size of chunk</param>
/// <param name="X">search string</param>
/// <param name="sizeX">size of search string</param>
/// <param name="N">distance</param>
/// <param name="buffCounter">buffer counter</param>
/// <param name="lastCharsEmpty">false if chunk contains characters from the previous chunk, true otherwise</param>
/// <param name="lastPosition">number of last occurrence</param>
/// <param name="lastPositionPrinted">true if the last occurrence was printed, else otherwise</param>
/// <param name="lineSizes">vector of line sizes</param>
void findX(const std::string& buffer, const size_t& sizeBuff, const std::string& X, const size_t& sizeX, const uint32_t N, const size_t buffCounter, bool lastCharsEmpty, uint64_t& lastPosition, bool& lastPositionPrinted, std::vector<size_t>& lineSizes)
{
	uint64_t positionX = buffer.find(X, 0);

	uint64_t currentPosition = 0;
	bool currentPositionPrinted = false;

	while (positionX != std::string::npos)
	{
		if (lastCharsEmpty)
		{
			currentPosition = positionX;	
		}
		else
		{
			currentPosition = positionX - sizeX + buffCounter * sizeBuff;
		}

		if (lastPosition != std::string::npos && currentPosition - lastPosition <= N)
		{
			if (!lastPositionPrinted)
			{
				decoder(lastPosition, lineSizes);
				lastPositionPrinted = true;
			}
			
			if (!currentPositionPrinted)
			{
				decoder(currentPosition, lineSizes);
				currentPositionPrinted = true;
			}
			
		}

		lastPosition = currentPosition;
		lastPositionPrinted = currentPositionPrinted;
		positionX = buffer.find(X, positionX + 1);
		currentPositionPrinted = false;
	}
}

/// <summary>
/// Control function for searching.
/// </summary>
/// <param name="ifs">file stream</param>
/// <param name="X">search string</param>
/// <param name="N">distance</param>
/// <param name="sizeBuff">size of chunk</param>
/// <returns>true if the search was performed correctly, false otherwise</returns>
bool file_read(std::ifstream& ifs, const std::string X, const uint32_t N, size_t sizeBuff = 1024)
{
	size_t sizeX = X.size() - 1;
	size_t buffCounter = 0;

	std::string buffer;
	buffer.resize(sizeBuff);

	std::string lastChars;
	lastChars.resize(sizeX);
	bool lastCharsEmpty = true;
	bool lastPositionPrinted = false;

	std::string buffLast;
	buffLast.resize(sizeBuff + sizeX);

	uint64_t lastPosition = std::string::npos;

	std::vector<size_t> lineSizes;
	size_t pendingCharacters = 1;

	// Fill the line size vector
	while (ifs.read(buffer.data(), buffer.size()))
	{
		findNL(buffer, sizeBuff, pendingCharacters, lineSizes);
	}
	buffer.resize(ifs.gcount());
	findNL(buffer, ifs.gcount(), pendingCharacters, lineSizes);
	lineSizes.push_back(pendingCharacters);
	ifs.clear();
	ifs.seekg(0, std::ios::beg);
	buffer.resize(sizeBuff);

	// Read the file and do the search
	while (ifs.read(buffer.data(), buffer.size()))
	{
		if (lastCharsEmpty)
		{
			findX(buffer, sizeBuff, X, sizeX, N, buffCounter, lastCharsEmpty, lastPosition, lastPositionPrinted, lineSizes);
			lastCharsEmpty = false;
		}
		else
		{
			buffLast = buffLast + buffer;
			findX(buffLast, sizeBuff, X, sizeX, N, buffCounter, lastCharsEmpty, lastPosition, lastPositionPrinted, lineSizes);
		}

		buffLast = buffer.substr(buffer.size() - sizeX);
		buffCounter++;
	}

	buffer.resize(ifs.gcount());
	
	if (lastCharsEmpty)
	{
		findX(buffer, sizeBuff, X, sizeX, N, buffCounter, lastCharsEmpty, lastPosition, lastPositionPrinted, lineSizes);
	}
	else
	{
		buffLast = buffLast + buffer;
		buffLast.resize((ifs.gcount() + sizeX));
		findX(buffLast, sizeBuff, X, sizeX, N, buffCounter, lastCharsEmpty, lastPosition, lastPositionPrinted, lineSizes);
	}

	if (ifs.eof())
	{
		return true;
	}

	return false;
}

/// <summary>
/// The main function of the program. The function checks inputs, sets the values of the variables and starts the search
/// </summary>
/// <param name="argc">Argument count</param>
/// <param name="argv">Argument vector</param>
/// <returns>0 if the program worked properly, something else otherwise</returns>
int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		return 1;
	}
	char* inputFileName = argv[1];

	std::ifstream ifs{ inputFileName };
	if (!ifs.is_open())
	{
		return 1;
	}

	if (!(strlen(argv[2]) < 256) || strlen(argv[2]) == 0)
	{
		return 2;
	}

	std::string X{ argv[2] };
	for (size_t i = 0; i < X.size(); i++)
	{
		if (int(X[i]) < 0 || int(X[i]) > 127)
		{
			return 2;
		}
	}

	std::string nHelp{ argv[3] };

	for (size_t i = 0; i < nHelp.length(); i++)
	{
		auto character = nHelp[i];
		if (character < '0' || character > '9')
		{
			return 3;
		}
	}

	uint32_t N = 0;

	try
	{
		N = std::stoul(nHelp);
	}
	catch (const std::exception&)
	{
		return 3;
	}
	
	if (N == 0)
	{
		return 3;
	}

	if (!(file_read(ifs, X, N)))
	{
		return 4;
	}

	return 0;
}
