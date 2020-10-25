#include "Parsers.h"

Rotor_Parser::Rotor_Parser()
    {
        for (int index = 0; index < alph_size; index++)
        {
            mapping[index] = index;
        }
    }
    

bool Rotor_Parser::in_range(const int number) const
    {
		return 0<=number && number<alph_size;
	}
	
bool Rotor_Parser::mapped_before(const int num1, 
								 const std::vector<int> prev_val_array, 
								 const int nr_of_vals) const
	{
		if (nr_of_vals == 0)
		{return false;}
		for (int index = 0; index < nr_of_vals; index++)
		{
			if (prev_val_array[index] == num1)
			{return true;}
		}
		return false;
	}
	
bool Rotor_Parser::the_same(const int num1, const int num2) const
	{
		return num1==num2; 
	}

void Rotor_Parser::print_notches() const
    {
		std::cout << "Notches at ";
		for(int index = 0; notches.at(index) != -1; index++)
		{
			std::cout << (char)(notches.at(index)+alph_adj) << " ";
		}
		std::cout << std::endl;
	}

void Rotor_Parser::print_mapping() const
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

int Rotor_Parser::configure_map()
    {
        int number;
        int count = 0;
        std::vector<int> previous_values;
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
				return INVALID_ROTOR_MAPPING;
			}

        while(true)
        {
            // if have valid 26 ints then will store the next values as notches
			if (count >alph_size-1) 
			{
				inStream>>number>>std::ws;
				if (inStream.fail())
				{
					std::cout<<"Non-numeric character entered in file "<<
					fileName<<std::endl;
				return NON_NUMERIC_CHARACTER;
				}
				if (!in_range(number))
				{	
					std::cout<<'\n'<< (char)(number+alph_adj) <<
					" is not a valid letter"<<std::endl;
					inStream.close();
					return INVALID_INDEX;
				}
				
				notches.push_back(number);
				count++;
				
				if (inStream.peek() == EOF)
				{
					break;
				}
				continue;
			}
				 
			inStream>>number>>std::ws;
			
			if (inStream.fail()) // check for int type 
			{
				std::cout<<"Non numeric character in rotor file "<<
				fileName<<std::endl;
				return NON_NUMERIC_CHARACTER;
			}
			
			if (!in_range(number))
				{	
					std::cout<<'\n'<< (char)(number+alph_adj) <<
					" is not a valid letter"<<std::endl;
					inStream.close();
					return INVALID_INDEX;
				}
			
			if (mapped_before(number,previous_values,count))
			{
				std::cout << (char)(number+alph_adj) <<
				" has already been mapped."<<std::endl;
				inStream.close();
				return INVALID_ROTOR_MAPPING;
			}
			
			mapping[count] = number;
			previous_values.push_back(number);
			count++;
			// file must contain notches, only way to exit loop without errors 
			// is if nr of values > 26 and all values are valid
			if (inStream.peek() == EOF) 
            {
            	std::cout<<"Not all inputs have been mapped in rotor file "<<
            	fileName<<std::endl;
				inStream.close();
				return INVALID_ROTOR_MAPPING;
			}
			
        }
        
        inStream.close();
        return NO_ERROR;
    }
