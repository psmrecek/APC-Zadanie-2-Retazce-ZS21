//#include <iostream>
//#include <vector>
//#include <string>
//#include <fstream>
//#include <algorithm>
//
//uint32_t convert(size_t number)
//{
//	if (number > UINT_MAX) {
//		throw "Overflow";
//	}
//	return static_cast<uint32_t>(number);
//}
//
//size_t internal_line_num(std::vector<size_t>& positionsNewLines, size_t& found)
//{
//	for (size_t i = 0; i < positionsNewLines.size(); i++)
//	{
//		if (found < positionsNewLines[i])
//		{
//			return i;
//		}
//	}
//	return 0;
//}
//
//void find(const std::string& buffer, const std::string& X, const size_t& size, std::vector<size_t>& lineSizes, size_t& pendingChars)
//{
//
//	//size_t found = buffer.find(X, 0);
//
//	size_t originalPendingChars = pendingChars;
//	//std::cout << originalPendingChars << " ";
//
//	std::vector<size_t> positionsNewLines;
//	size_t posNewLine = buffer.find('\n', 0);
//
//	while (posNewLine != std::string::npos)
//	{
//		positionsNewLines.push_back(posNewLine);
//		posNewLine = buffer.find('\n', posNewLine + 1);
//	}
//
//	for (size_t i = 0; i < positionsNewLines.size(); i++)
//	{
//		if (pendingChars != 0)
//		{
//			lineSizes.push_back(positionsNewLines[i] + pendingChars);
//			pendingChars = 0;
//		}
//		else if (i > 0)
//		{
//			lineSizes.push_back(positionsNewLines[i] - positionsNewLines[i - 1] - 1);
//		}
//		else
//		{
//			lineSizes.push_back(positionsNewLines[i] + pendingChars);
//		}
//	}
//
//	if (positionsNewLines.size() > 0)
//	{
//		pendingChars = buffer.length() - positionsNewLines.back() - 1;
//	}
//	else
//	{
//		pendingChars += size;
//	}
//	//std::cout << pendingChars << std::endl;
//
//	//if (originalPendingChars == 0 && pendingChars == 0)
//	//{
//	//	lineSizes.push_back(0);
//	//}
//	//size_t lineNumInternal = 0;
//
//	//while (found != std::string::npos)
//	//{
//	//	lineNumInternal = internal_line_num(positionsNewLines, found);
//	//	std::cout << lineNumInternal + lineNumGlob << " " << found << " (" << lineNumInternal << " " << lineNumGlob << " " << found << ")" << std::endl;
//	//	found = buffer.find(X, found + 1);
//	//}
//
//	//lineNumGlob += positionsNewLines.size();
//
//	//std::cout << size << X << std::endl;
//}
//
//bool file_read(std::ifstream& ifs, const std::string X, const std::uint32_t N, size_t size = 10)
//{
//	//std::cout << "----------" << std::endl;
//
//	//size_t size = 1;
//
//	std::string buffer;
//	buffer.resize(size);
//
//	std::vector<size_t> lineSizes;
//	size_t pendingChars = 0;
//
//	while (ifs.read(buffer.data(), buffer.size()))
//	{
//		//std::cout << buffer << std::endl;
//		find(buffer, X, size, lineSizes, pendingChars);
//	}
//
//	// Zabezpeci, ze po poslednej iteracii ostane zostane pole iba novych charakterov
//	buffer.resize(ifs.gcount());
//	//std::cout << buffer << std::endl;
//	find(buffer, X, ifs.gcount(), lineSizes, pendingChars);
//
//	//std::cout << "----------" << std::endl;
//
//	for (size_t line : lineSizes)
//	{
//		std::cout << line << std::endl;
//	}
//
//	//std::cout << "----------" << std::endl << X << " " << N << std::endl;
//
//	//bool ok = lineSizes[0] == 13 && lineSizes[1] == 11 && lineSizes[2] == 0 && lineSizes[3] == 0 &&
//	//	lineSizes[4] == 0 && lineSizes[5] == 9 && lineSizes[6] == 7 && lineSizes[7] == 5 &&
//	//	lineSizes[8] == 3;
//
//	//return ok;
//
//	if (ifs.eof())
//	{
//		return true;
//	}
//
//	return false;
//}
//
//void test(std::ifstream& ifs, const std::string X, const std::uint32_t N)
//{
//	for (size_t i = 1; i < 100; i++)
//	{
//		ifs.clear();
//		ifs.seekg(0, std::ios::beg);
//		if (!(file_read(ifs, X, N, i)))
//		{
//			std::cout << "Error on size " << i << std::endl;
//		}
//	}
//
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
//	//char* inputFileName = argv[1];
//	auto inputFileName = "input.txt";
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
//	std::string X{ argv[2] };
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
//	std::cout << argv[3] << " " << N << std::endl;
//
//	//test(ifs, X, N);
//
//	if (!(file_read(ifs, X, N)))
//	{
//		return 4;
//	}
//
//	return 0;
//}
