#include <fstream>
#include <iostream>
#include <iomanip>
#include <getopt.h>

static std::string filepath;
static int option_addressoffset = 1;
static int option_ascii = 1;

static void
usage(char* program)
{
	std::cout << "Usage: << " << program << "[OPTIONS] FILE" << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "-A\t Don't show address offsets." << std::endl;
	std::cout << "-a\t Show address offsets." << std::endl;
	std::cout << "-P\t Don't print readable ASCII characters." << std::endl;
	std::cout << "-H\t Only print hexadecimal values.\n  \t This is a combination of -A and -P switches." << std::endl;
	std::cout << "-h\t Help messages." << std::endl;
}

static int
parseargs(int argc, char** argv)
{
	int opt;
	while ((opt = getopt(argc, argv, "AahPH")) != EOF)
	{
		switch(opt)
		{
		case 'a':
			option_addressoffset = 1;
			break;
		case 'A':
			option_addressoffset = 0;
			break;
		case 'H':
			option_addressoffset = 0;
		case 'P':
			option_ascii = 0;
			break;
		case 'h':
		default:
			usage(argv[0]);
			return 1;
		}
	}
	if (optind >= argc)
	{
		std::cerr << "File was not given." << std::endl;
		usage(argv[0]);
		return 1;
	}
	filepath = argv[optind];
	return 0;
}

int
main(int argc, char** argv)
{
	std::ifstream file;
	unsigned char buffer[16];
	long int readcount;
	int offset;

	if (parseargs(argc, argv))
	{
		return 1;
	}

	file.open(filepath);
	if (!file)
	{
		std::cerr << "File could not be loaded!" << std::endl;
		std::cerr << "Faulty file: \"" << filepath << "\"."  << std::endl;
		return 2;
	}
	offset = 0;
	for(;;)
	{
		file.read((char*) buffer, 16);
		readcount = file.gcount();
		if (readcount <= 0)
		{
			break;
		}
		/* Address offset */
		if (option_addressoffset)
		{
			std::cout << std::setfill('0') << std::setw(8) << std::hex << offset << ' ';
			offset += 16;
			std::cout << ' ';
		}
		/* Hexadecimal values */
		for (int i = 0; i < 16; i++)
		{
			if (i == 8)
			{
				std::cout << ' ';
			}
			if (i < readcount)
			{
				std::cout << std::hex << std::setw(2) << std::setfill('0') << (int) buffer[i] << ' ';
			}
			else
			{
				std::cout << std::setw(2) << "   ";
			}
		}
		/* ASCII values */
		if (option_ascii)
		{
			std::cout << " |";
			for (int i = 0; i < 16; i++)
			{
				char c;
				if (i < readcount)
				{
						if (buffer[i] < 32 || 126 < buffer[i])
						{
							c = '.';
						}
						else
						{
							c = buffer[i];
						}
						std::cout << c;
				}
				else
				{
					std::cout << ' ';
				}
			}
			std::cout << "|";
		}
		std::cout << std::endl;
		if (file.eof())
		{
			break;
		}
	}
	return 0;
}
