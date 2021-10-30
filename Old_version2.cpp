//#include <iostream>
//#include <vector>
//#include <string>
//#include <fstream>
//#include <algorithm>
//
//size_t minimum(const size_t a, const size_t b)
//{
//	if ((a != std::string::npos) && (b != std::string::npos))
//	{
//		if (a < b)
//		{
//			return a;
//		}
//		else
//		{
//			return b;
//		}
//	}
//	else if (a != std::string::npos)
//	{
//		return a;
//	}
//	else if (b != std::string::npos)
//	{
//		return b;
//	}
//}
//
//int substract_correction(const size_t& lineNum)
//{
//	if (lineNum == 0)
//	{
//		return 0;
//	}
//
//	return 1;
//}
//
//int add_correction(const size_t& lineNum)
//{
//	if (lineNum == 0)
//	{
//		return 1;
//	}
//
//	return 0;
//}
//
//void find(const std::string& buffer, const size_t& sizeBuff, const std::string& X, const size_t& sizeX, size_t& lineNum, size_t& pendingChars, const bool lastCharsEmpty, size_t& lastLineSize, size_t& lastPendingChars)
//{
//	size_t off = 0;
//	size_t posX = buffer.find(X, off);
//	size_t posNewLine = buffer.find('\n', off);
//	size_t lastNewLine = 0;
//	lastPendingChars = pendingChars;
//
//	if (lastCharsEmpty)
//	{
//		while ((posX != std::string::npos) || (posNewLine != std::string::npos))
//		{
//			off = minimum(posX, posNewLine);
//			if (off == posNewLine)
//			{
//				lastLineSize = posNewLine - lastNewLine + pendingChars + add_correction(lineNum);
//				if (off == posX)
//				{
//					std::cout << lineNum << " " << posX + pendingChars - lastNewLine - substract_correction(lineNum) << std::endl;
//				}
//				lineNum++;
//				lastPendingChars = pendingChars;
//				pendingChars = 0;
//				lastNewLine = posNewLine;
//				//std::cout << lastLineSize << std::endl;
//			}
//
//			if (off == posX)
//			{
//				std::cout << lineNum << " " << posX + pendingChars - lastNewLine - substract_correction(lineNum) << std::endl;
//				//std::cout << " " << posX << " " << pendingChars << " " << lastNewLine << std::endl;
//			}
//
//			posX = buffer.find(X, off + 1);
//			posNewLine = buffer.find('\n', off + 1);
//		}
//
//		if ((posX != std::string::npos) || (posNewLine != std::string::npos))
//		{
//			off = minimum(posX, posNewLine);
//
//			if (off == posNewLine)
//			{
//				lastLineSize = posNewLine - lastNewLine + pendingChars + add_correction(lineNum);
//				lineNum++;
//				lastPendingChars = pendingChars;
//				pendingChars = 0;
//				lastNewLine = posNewLine;
//				//std::cout << lastLineSize << std::endl;
//			}
//
//			if (off == posX)
//			{
//				std::cout << lineNum << " " << posX + pendingChars - lastNewLine - substract_correction(lineNum) << std::endl;
//			}
//		}
//		pendingChars += sizeBuff - lastNewLine;
//	}
//	else
//	{
//		while ((posX != std::string::npos) || (posNewLine != std::string::npos))
//		{
//			//if (lineNum == 17)
//			//{
//			//	std::cout << posX << " " << posNewLine << " " << pendingChars << " " << buffer << std::endl;
//			//}
//			off = minimum(posX, posNewLine);
//			if (off == posNewLine && off >= sizeX)
//			{
//				lastLineSize = posNewLine - lastNewLine + pendingChars - sizeX + add_correction(lineNum);
//				if (off == posX)
//				{
//					std::cout << lineNum << " " << posX + pendingChars - lastNewLine - substract_correction(lineNum) - sizeX << std::endl;
//				}
//				lineNum++;
//				lastPendingChars = pendingChars;
//				pendingChars = 0;
//				lastNewLine = posNewLine - sizeX;
//				//std::cout << lastLineSize << std::endl;
//			}
//
//			if (off == posX && off != posNewLine)
//			{
//				if (off <= sizeX && lineNum != 0)
//				{
//					size_t posNewLineX = X.find('\n', 0) + 1;
//					std::cout << lineNum - 1 << " " << lastLineSize - posNewLineX << std::endl;
//					//std::cout << " " << posX << ": " << lastLineSize << "-" << sizeX << "+" << off << "+" << 1 << "|" << "" << std::endl;
//				}
//				else
//				{
//					std::cout << lineNum << " " << posX + pendingChars - lastNewLine - substract_correction(lineNum) - sizeX << std::endl;
//					//std::cout << " " << posX << "+" << pendingChars << "-" << lastNewLine << "-" << substract_correction(lineNum) << "-" << sizeX << "|" << lastLineSize << std::endl;
//				}
//			}
//			posX = buffer.find(X, off + 1);
//			posNewLine = buffer.find('\n', off + 1);
//		}
//
//		if ((posX != std::string::npos) || (posNewLine != std::string::npos))
//		{
//			off = minimum(posX, posNewLine);
//
//			if (off == posNewLine && off >= sizeX)
//			{
//				lastLineSize = posNewLine - lastNewLine + pendingChars - sizeX + add_correction(lineNum);
//				lineNum++;
//				lastPendingChars = pendingChars;
//				pendingChars = 0;
//				lastNewLine = posNewLine - sizeX;
//				//std::cout << lastLineSize << std::endl;
//			}
//
//			if (off == posX && off != posNewLine)
//			{
//				if (off <= sizeX && lineNum != 0)
//				{
//					size_t posNewLineX = X.find('\n', 0) + 1;
//					std::cout << lineNum - 1 << " " << lastLineSize - posNewLineX << std::endl;
//					//std::cout << " " << posX << ": " << lastLineSize << "-" << sizeX << "+" << off << "+" << 1 << "|" << "" << std::endl;
//				}
//				else
//				{
//					std::cout << lineNum << " " << posX + pendingChars - lastNewLine - substract_correction(lineNum) - sizeX << std::endl;
//					//std::cout << " " << posX << "+" << pendingChars << "-" << lastNewLine << "-" << substract_correction(lineNum) << "-" << sizeX << "|" << lastLineSize << std::endl;
//				}
//			}
//		}
//		pendingChars += sizeBuff - lastNewLine - sizeX;
//	}
//}
//
//bool file_read(std::ifstream& ifs, const std::string X, const std::uint32_t N, size_t sizeBuff = 12)
//{
//	//std::cout << "----------" << std::endl;
//
//	size_t sizeX = X.size() - 1;
//	//std::cout << sizeX << std::endl;
//
//	std::string buffer;
//	buffer.resize(sizeBuff);
//
//	size_t lineNum = 0;
//	size_t pendingChars = 0;
//	size_t lastLineSize = 0;
//	size_t lastPendingChars = 0;
//
//	std::string lastChars;
//	lastChars.resize(sizeX);
//	bool lastCharsEmpty = true;
//
//	std::string buffLast;
//	buffLast.resize(sizeBuff + sizeX);
//
//	while (ifs.read(buffer.data(), buffer.size()))
//	{
//		if (lastCharsEmpty)
//		{
//			//std::cout << buffer << std::endl;
//			find(buffer, sizeBuff, X, sizeX, lineNum, pendingChars, lastCharsEmpty, lastLineSize, lastPendingChars);
//			lastCharsEmpty = false;
//		}
//		else
//		{
//			buffLast = buffLast + buffer;
//			//std::cout << buffLast << std::endl;
//			find(buffLast, (sizeBuff + sizeX), X, sizeX, lineNum, pendingChars, lastCharsEmpty, lastLineSize, lastPendingChars);
//		}
//
//		buffLast = buffer.substr(buffer.size() - sizeX);
//
//		//find(buffer, X, sizeBuff, lineNum, pendingChars, lastCharsEmpty);
//	}
//
//	// Zabezpeci, ze po poslednej iteracii ostane zostane pole iba novych charakterov
//	if (lastCharsEmpty)
//	{
//		buffer.resize(ifs.gcount());
//		find(buffer, sizeBuff, X, sizeX, lineNum, pendingChars, lastCharsEmpty, lastLineSize, lastPendingChars);
//	}
//	else
//	{
//		buffLast = buffLast + buffer;
//		//std::cout << ifs.gcount() << std::endl;
//
//		buffLast.resize((ifs.gcount() + sizeX));
//		//std::cout << buffLast << std::endl;
//		find(buffLast, (ifs.gcount() + sizeX), X, sizeX, lineNum, pendingChars, lastCharsEmpty, lastLineSize, lastPendingChars);
//	}
//
//	if (ifs.eof())
//	{
//		return true;
//	}
//
//	return false;
//}
//
//int main(int argc, char* argv[])
//{
//	if (argc != 4)
//	{
//		return 1;
//	}
//	std::cout << argv[1] << " " << argv[2] << " " << argv[3] << std::endl;
//
//	char* inputFileName = argv[1];
//	//auto inputFileName = "input.txt";
//
//	std::ifstream ifs{ inputFileName };
//	if (!ifs.is_open())
//	{
//		return 1;
//	}
//
//	if (!(strlen(argv[2]) < 256))
//	{
//		return 2;
//	}
//
//	//std::string X{ argv[2] };
//	std::string X{ "bb\nb" };
//
//	std::cout << strlen(argv[2]) << " " << sizeof(argv[2]) << " " << X.length() << std::endl;
//
//	std::string nHelp{ argv[3] };
//
//	for (size_t i = 0; i < nHelp.length(); i++)
//	{
//		auto character = nHelp[i];
//		if (character < '0' || character > '9')
//		{
//			return 3;
//		}
//	}
//
//	uint32_t N = 0;
//
//	try
//	{
//		N = std::stoul(nHelp);
//	}
//	catch (const std::exception&)
//	{
//		return 3;
//	}
//
//	if (N == 0)
//	{
//		return 3;
//	}
//
//
//	std::cout << argv[3] << " " << N << std::endl << std::endl;
//	std::cout << inputFileName << " " << X << " " << N << std::endl;
//	std::cout << "----------------" << std::endl;
//	//test(ifs, X, N);
//
//
//	for (size_t i = 12; i <= 100; i++)
//	{
//		ifs.clear();
//		ifs.seekg(0, std::ios::beg);
//		std::cout << "------" << i << " " << std::endl;
//		if (!(file_read(ifs, X, N, i)))
//		{
//			return 4;
//		}
//	}
//
//	//if (!(file_read(ifs, X, N, 13)))
//	//{
//	//	return 4;
//	//}
//
//	return 0;
//}
