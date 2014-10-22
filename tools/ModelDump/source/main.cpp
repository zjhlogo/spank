/*!
 * \file main.cpp
 * \date 10-22-2014 10:59:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "main.h"
#include "Convertor.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cout << "usage: ModelDump input_file output_file" << std::endl;

		return 1;
	}

	spank::Convertor conv;
	conv.openModelFile(argv[1]);
	conv.saveFile(argv[2]);

	return 0;
}