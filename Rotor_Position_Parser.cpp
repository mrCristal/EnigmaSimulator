#include "Parsers.h"

Rotor_Position_Parser::Rotor_Position_Parser(const char* file)
{
	fileName = file;	
}

bool Rotor_Position_Parser::in_range(const int number) const
{
	return 0<=number && number<alph_size;
}

int  Rotor_Position_Parser::read_positions()
{
	int position;
	
	std::ifstream inStream;
	
	inStream.open(fileName);
	
	if (inStream.fail())
	{
		std::cout << "Could not open file."<<std::endl;
        return ERROR_OPENING_CONFIGURATION_FILE;
    }
    
    if (inStream.peek() == EOF)
    {
		std::cout<< "No mapping specified"<<std::endl;
		inStream.close();
		return INVALID_ROTOR_POSITIONS;
	}
	
	while (true)
	{
		inStream>>position>>std::ws;
		if (inStream.fail()) // check for int type 
		{
			std::cout<<"Non-numeric character in file "<<fileName<<std::endl;
			return NON_NUMERIC_CHARACTER;
		}
		
		if (!in_range(position))
		{	
			std::cout<<'\n'<< (char)(position+alph_adj) << 
			" is not a valid starting position."<<std::endl;
			inStream.close();
			return INVALID_INDEX;
		}
		positions.push_back(position);
	
		if (inStream.peek() == EOF)
			break;
	}
	inStream.close();
	return NO_ERROR;	
}	
