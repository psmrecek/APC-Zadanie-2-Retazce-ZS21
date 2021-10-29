#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

uint32_t convert(size_t number)
{
	if (number > UINT_MAX) {
		throw "Overflow";
	}
	return static_cast<uint32_t>(number);
}

size_t internal_line_num(std::vector<size_t>& positionsNewLines, size_t& found)
{
	for (size_t i = 0; i < positionsNewLines.size(); i++)
	{
		if (found < positionsNewLines[i])
		{
			return i;
		}
	}
	return 0;
}

size_t minimum(const size_t a, const size_t b)
{
	if ((a != std::string::npos) && (b != std::string::npos))
	{
		if (a < b)
		{
			return a;
		}
		else
		{
			return b;
		}
	}
	else if (a != std::string::npos)
	{
		return a;
	}
	else if (b != std::string::npos)
	{
		return b;
	}
}

int substract_correction(const size_t& lineNum)
{
	if (lineNum == 0)
	{
		return 0;
	}
	
	return 1;
}

void find(const std::string& buffer, const std::string& X, const size_t& sizeX, const size_t& sizeBuff, size_t& lineNum, size_t& pendingChars, const bool lastCharsEmpty)
{
	size_t off = 0;
	size_t posX = buffer.find(X, off);
	size_t posNewLine = buffer.find('\n', off);

	size_t lastNewLine = 0;

	if (lastCharsEmpty)
	{
		while ((posX != std::string::npos) || (posNewLine != std::string::npos))
		{
			
			off = minimum(posX, posNewLine);
			if (off == posNewLine)
			{
				if (off == posX)
				{
					std::cout << lineNum << " " << posX + pendingChars - lastNewLine - substract_correction(lineNum) << std::endl;
				}
				lineNum++;
				pendingChars = 0;
				lastNewLine = posNewLine;
				//std::cout << lineNum << std::endl;
			}

			if (off == posX)
			{
				std::cout << lineNum << " " << posX + pendingChars - lastNewLine - substract_correction(lineNum) << std::endl;
				//std::cout << " " << posX << " " << pendingChars << " " << lastNewLine << std::endl;
			}

			posX = buffer.find(X, off + 1);
			posNewLine = buffer.find('\n', off + 1);
		}

		if ((posX != std::string::npos) || (posNewLine != std::string::npos))
		{
			off = minimum(posX, posNewLine);

			if (off == posNewLine)
			{
				lineNum++;
				pendingChars = 0;
				lastNewLine = posNewLine;
				//std::cout << lineNum << std::endl;
			}

			if (off == posX)
			{
				std::cout << lineNum << " " << posX + pendingChars - lastNewLine - substract_correction(lineNum) << std::endl;
			}
		}
		pendingChars += sizeBuff - lastNewLine;

	}
	else
	{
		while ((posX != std::string::npos) || (posNewLine != std::string::npos))
		{
			//if (lineNum == 17)
			//{
			//	std::cout << posX << " " << posNewLine << " " << pendingChars << " " << buffer << std::endl;
			//}
			off = minimum(posX, posNewLine);
			if (off == posNewLine && off >= sizeX)
			{
				if (off == posX)
				{
					std::cout << lineNum << " " << posX + pendingChars - lastNewLine - substract_correction(lineNum) - sizeX << std::endl;
				}
				lineNum++;
				pendingChars = 0;
				lastNewLine = posNewLine - sizeX;
				//std::cout << lineNum << std::endl;
			}

			if (off == posX && off != posNewLine)
			{
				if (off < sizeX)
				{
					//Toto
					std::cout << lineNum << " " << posX + pendingChars - lastNewLine - 1 << std::endl;
					std::cout << " " << posX << " " << pendingChars << " " << lastNewLine << std::endl;
				}
				else
				{
					std::cout << lineNum << " " << posX + pendingChars - lastNewLine - substract_correction(lineNum) - sizeX << std::endl;
				}

				
				
			}

			posX = buffer.find(X, off + 1);
			posNewLine = buffer.find('\n', off + 1);
		}

		if ((posX != std::string::npos) || (posNewLine != std::string::npos))
		{
			off = minimum(posX, posNewLine);

			if (off == posNewLine && off >= sizeX)
			{
				lineNum++;
				pendingChars = 0;
				lastNewLine = posNewLine - sizeX;
				//std::cout << lineNum << std::endl;
			}

			if (off == posX)
			{
				std::cout << lineNum << " " << posX + pendingChars - lastNewLine - substract_correction(lineNum) - sizeX << std::endl;
			}
		}
		pendingChars += sizeBuff - lastNewLine - sizeX;
	}
	

	//size_t found = buffer.find(X, 0);

	//size_t originalPendingChars = pendingChars;
	////std::cout << originalPendingChars << " ";

	//std::vector<size_t> positionsNewLines;
	//size_t posNewLine = buffer.find('\n', 0);

	//while (posNewLine != std::string::npos)
	//{
	//	positionsNewLines.push_back(posNewLine);
	//	posNewLine = buffer.find('\n', posNewLine + 1);
	//}

	//for (size_t i = 0; i < positionsNewLines.size(); i++)
	//{
	//	if (pendingChars != 0)
	//	{
	//		lineSizes.push_back(positionsNewLines[i] + pendingChars);
	//		pendingChars = 0;
	//	}
	//	else if (i > 0)
	//	{
	//		lineSizes.push_back(positionsNewLines[i] - positionsNewLines[i-1] - 1);
	//	}
	//	else
	//	{
	//		lineSizes.push_back(positionsNewLines[i] + pendingChars);
	//	}
	//}

	//if (positionsNewLines.size() > 0)
	//{ 
	//	pendingChars = buffer.length() - positionsNewLines.back() - 1;
	//}
	//else
	//{
	//	pendingChars += size;
	//}
	//std::cout << pendingChars << std::endl;

	//if (originalPendingChars == 0 && pendingChars == 0)
	//{
	//	lineSizes.push_back(0);
	//}
	//size_t lineNumInternal = 0;

	//while (found != std::string::npos)
	//{
	//	lineNumInternal = internal_line_num(positionsNewLines, found);
	//	std::cout << lineNumInternal + lineNumGlob << " " << found << " (" << lineNumInternal << " " << lineNumGlob << " " << found << ")" << std::endl;
	//	found = buffer.find(X, found + 1);
	//}

	//lineNumGlob += positionsNewLines.size();

	//std::cout << size << X << std::endl;
}

bool file_read(std::ifstream& ifs, const std::string X, const std::uint32_t N, size_t sizeBuff = 10)
{
	//std::cout << "----------" << std::endl;

	size_t sizeX = X.size() - 1;
	//std::cout << sizeX << std::endl;

	std::string buffer;
	buffer.resize(sizeBuff);

	size_t lineNum = 0;
	size_t pendingChars = 0;

	std::string lastChars;
	lastChars.resize(sizeX);
	bool lastCharsEmpty = true;

	std::string buffLast;
	buffLast.resize(sizeBuff + sizeX);

	while (ifs.read(buffer.data(), buffer.size()))
	{
		if (lastCharsEmpty)
		{
			//std::cout << buffer << std::endl;
			find(buffer, X, sizeX, sizeBuff, lineNum, pendingChars, lastCharsEmpty);
			lastCharsEmpty = false;
		}
		else
		{
			buffLast = buffLast + buffer;
			//std::cout << buffLast << std::endl;
			find(buffLast, X, sizeX, (sizeBuff + sizeX), lineNum, pendingChars, lastCharsEmpty);
		}

		buffLast = buffer.substr(buffer.size() - sizeX);

		//find(buffer, X, sizeBuff, lineNum, pendingChars, lastCharsEmpty);
	}

	// Zabezpeci, ze po poslednej iteracii ostane zostane pole iba novych charakterov
	if (lastCharsEmpty)
	{
		buffer.resize(ifs.gcount());
		find(buffer, X, sizeX, sizeBuff, lineNum, pendingChars, lastCharsEmpty);
	}
	else
	{
		buffLast = buffLast + buffer;
		//std::cout << ifs.gcount() << std::endl;

		buffLast.resize((ifs.gcount() + sizeX));
		//std::cout << buffLast << std::endl;
		find(buffLast, X, sizeX, (ifs.gcount() + sizeX), lineNum, pendingChars, lastCharsEmpty);
	}

	


	//std::cout << buffer << std::endl;

	//find(buffer, X, ifs.gcount(), lineNum, pendingChars, lastCharsEmpty);

	//std::cout << "----------" << std::endl;


	//std::cout << "----------" << std::endl << X << " " << N << std::endl;

	//bool ok = lineSizes[0] == 13 && lineSizes[1] == 11 && lineSizes[2] == 0 && lineSizes[3] == 0 &&
	//	lineSizes[4] == 0 && lineSizes[5] == 9 && lineSizes[6] == 7 && lineSizes[7] == 5 &&
	//	lineSizes[8] == 3;

	//return ok;

	if (ifs.eof())
	{
		return true;
	}

	return false;
}

void test(std::ifstream& ifs, const std::string X, const std::uint32_t N)
{
	for (size_t i = 1; i < 100; i++)
	{
		ifs.clear();
		ifs.seekg(0, std::ios::beg);
		if (!(file_read(ifs, X, N, i)))
		{
			std::cout << "Error on size " << i << std::endl;
		}
	}
	
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		return 1;
	}
	std::cout << argv[1] << " " << argv[2] << " " << argv[3] << std::endl;

	char* inputFileName = argv[1];
	//auto inputFileName = "input.txt";

	std::ifstream ifs{ inputFileName };
	if (!ifs.is_open())
	{
		return 1;
	}

	if (!(strlen(argv[2]) < 256))
	{
		return 2;
	}
	
	//std::string X{ argv[2] };
	std::string X{ "bb\nb" };

	std::cout << strlen(argv[2]) << " " << sizeof(argv[2]) << " " << X.length() << std::endl;

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


	std::cout << argv[3] << " " << N << std::endl << std::endl;
	std::cout << inputFileName << " " << X << " " << N << std::endl;
	std::cout << "----------------" << std::endl;
	//test(ifs, X, N);

	

	if (!(file_read(ifs, X, N)))
	{
		return 4;
	}

	return 0;
}
