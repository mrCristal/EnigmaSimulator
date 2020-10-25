#include "Parsers.h"


Plugboard_Parser::Plugboard_Parser(const char* name)
	{
		fileName = name;
		for (int index = 0; index<alph_size;index++)
		{
			mapping[index] = index; // set each letter mapping to itself
		}
		
	}

bool Plugboard_Parser::mapped_before(const int num1, 
									 const std::vector<int> prev_val_array, 
									 const int nr_of_vals) const
	{
		if (nr_of_vals == 0)
		{return false;}
		for (int index = 0; index < nr_of_vals; index++)
		{
			if (prev_val_array[index] == num1)
				return true;
		}
		return false;
	} 
		
bool Plugboard_Parser::the_same(const int num1, const int num2) const
	{
		return num1==num2; 
	}
	
bool Plugboard_Parser::in_range(const int number) const
	{ 
		return 0<= number && number <alph_size;
	} 
	
void Plugboard_Parser::print_mapping() const
	{
		std::cout <<"Key ";
		for (int index = 0; index <alph_size; index++)
		{
			std::cout << (char)(index + alph_adj) << " ";
		}
		std::cout << std::endl;

		std::cout << "    ";
		for (int index = 0; index <alph_size; index++)
		{
			std::cout << "|" << " ";
		}
		std::cout << std::endl;

		std::cout << "Val ";
		for (int index = 0; index <alph_size; index++)
		{
			std::cout << (char)(mapping.at(index) + alph_adj) << " ";
		}
		std::cout << std::endl;
	}
	
int Plugboard_Parser::configure_map()
	{
		int number;
		int number_pair;
		int nr_index = 0; // keeps count of paired ints
		std::vector<int> previous_values;
		std::ifstream inStream;		
		inStream.open(fileName);
		
		if (inStream.fail())
		{
			std::cout << "Could not open file."<<std::endl;
			return ERROR_OPENING_CONFIGURATION_FILE;// add a return error code here
		}
		
		if (inStream.peek() == EOF) // checks that the file is not empty 
		{
			inStream.close(); // no config for plugboard
			return NO_ERROR;
		}
		
		while (true) // how do you check for non numeric characters???
		{	

			inStream>>number>>std::ws;
			if (inStream.fail()) //fail flag implies number was not of type int 
			{
				std::cout<<"Non-numeric character in plugboard file "<<
				fileName<<std::endl;
				return NON_NUMERIC_CHARACTER;
			}
			
			if (!in_range(number))
				{	
					std::cout<< (char)(number+alph_adj) <<
					" is not a valid letter"<<std::endl;
					inStream.close();
					return INVALID_INDEX;
				}		
			// lack of int after odd nrs implies INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
			if (inStream.peek() == EOF) 
			{
				std::cout << '\n'<<
				"Incorrect number of parameters in plugboard file "<<
				fileName<<std::endl;
				inStream.close();
				return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
			}
			
			if (mapped_before(number,previous_values,nr_index))
				{	
					std::cout << (char)(number+alph_adj) <<
					" has already been mapped."<<std::endl;
					inStream.close();
					return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
				}			


			inStream>>number_pair>>std::ws;
			if (inStream.fail()) //fail flag implies number_pair was not of type int
			{
				std::cout<<"Non-numeric character in plugboard file "<<
				fileName<<std::endl;
				return NON_NUMERIC_CHARACTER;
			}
			
			if (!in_range(number_pair))
				{
					std::cout<< (char)(number_pair+alph_adj) <<
					" is not a valid letter"<<std::endl;
					inStream.close();
					return INVALID_INDEX;
				}
				// checking that letters are not being mapped to each other
			else if (the_same(number, number_pair)) 
				{	
					std::cout << "Attempting to map "<<(char)(number+alph_adj)
					<< " to itself."<<std::endl;
					inStream.close();
					return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
				}
				
			mapping[number] = number_pair;
			mapping[number_pair] = number;
			previous_values.push_back(number); // keeps log of mapped numbers
			nr_index++;
			if (inStream.peek() == EOF) // checks for end of file
				break;
		}
		
		inStream.close();
		return NO_ERROR;
	}
