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
#include <tclap/CmdLine.h>

int main(int argc, char** argv)
{
	TCLAP::CmdLine cmd("A tools to dump 3d model files to mesh format", ' ', "1.5.5");

	// add input file argument
	TCLAP::ValueArg<std::string> inputFileArg("i", "input", "input file", true, "", "path");
	cmd.add(inputFileArg);

	// add output file argument
	TCLAP::ValueArg<std::string> outputFileArg("o", "output", "output file", true, "", "path");
	cmd.add(outputFileArg);

	cmd.parse(argc, argv);

	spank::Convertor conv;
	if (!conv.openModelFile(inputFileArg.getValue().c_str()))
	{
		std::cout << "Error, open file failed, " << inputFileArg.getValue() << std::endl;
		return 1;
	}

	if (!conv.saveFile(outputFileArg.getValue().c_str()))
	{
		std::cout << "Error, save file failed, " << outputFileArg.getValue() << std::endl;
		return 1;
	}

	return 0;
}
