#include "Parsers.h"

const int max_letter_pairs = 13;

Reflector_Parser::Reflector_Parser (const char* name)
	{
		fileName = name;
		for (int index = 0; index<alph_size;index++)
		{
			mapping[index] = index;
		}
	}

bool Reflector_Parser::mapped_before(const int num1, 
									 const std::vector<int> prev_val_array, 
									 const int nr_of_vals) const
	{
		if (nr_of_vals == 0)
			return false;
			
		for (int index = 0; index < nr_of_vals; index++)
		{
			if (prev_val_array[index] == num1)
				return true;
		}
		
		return false;
	} 
		
bool Reflector_Parser::the_same(const int num1, const int num2) const
	{
		return num1==num2; 
	}
	
bool Reflector_Parser::in_range(const int number) const
	{ 
		return 0<= number && number <alph_size;
	} 

void Reflector_Parser::print_mapping() const
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
	
int Reflector_Parser::configure_map()
	{
		int number;
		int number_pair;
		int val_nr = 0; // keeps count of values
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
			std::cout<< "No mapping specified"<<std::endl;
			inStream.close();
			return INVALID_REFLECTOR_MAPPING;
		}
		
		while (true)
		{	

			if (val_nr/2 >max_letter_pairs) // checks if more than 13 pairs
			{	inStream.close();
				return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
			}

			inStream >> number>>std::ws;
			if (inStream.fail()) // checks that input was of type int 
			{
				std::cout<<"Non-numeric character in reflector file "<<
				fileName<<std::endl;
				return NON_NUMERIC_CHARACTER;
			}

			if (inStream.peek() == EOF) 
			{
				std::cout<<'\n' <<
				"Incorrect (odd) number of parameters in reflector file "<<
				fileName<<std::endl;
				inStream.close();
				return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
			}
			
			if (!in_range(number))
				{	
					std::cout<<'\n'<< (char)(number+alph_adj) <<
					" is not a valid letter"<<std::endl;
					inStream.close();
					return INVALID_INDEX;
				}
			if (mapped_before(number,previous_values,val_nr))
				{	
					std::cout << (char)(number+alph_adj) << 
					" has already been mapped."<<std::endl;
					inStream.close();
					return INVALID_REFLECTOR_MAPPING;
				}

			inStream>>number_pair>>std::ws;
			if (inStream.fail()) // checks that input was of type int 
			{
				std::cout<<"Non-numeric character in reflector file "<<
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
			
			if (mapped_before(number_pair,previous_values,val_nr))
				{	
					std::cout << (char)(number+alph_adj) <<
					" has already been mapped."<<std::endl;
					inStream.close();
					return INVALID_REFLECTOR_MAPPING;
				}
				// checking that letters are not being mapped to each other
			else if (the_same(number, number_pair)) 
				{	
					std::cout << "Attempting to map "<<(char)(number+alph_adj)
					<< " to itself."<<std::endl;
					inStream.close();
					return INVALID_REFLECTOR_MAPPING;
				}

			mapping[number] = number_pair;
			mapping[number_pair] = number;
			previous_values.push_back(number);
			previous_values.push_back(number_pair);
			val_nr+=2;
			if (inStream.peek() == EOF) // check for end of file
				break;
		}
		
		if (val_nr/2 != max_letter_pairs) //effectively checks for less than 13 pairs
		{
			return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS; 
		} 
		inStream.close();
		return NO_ERROR;
	}
