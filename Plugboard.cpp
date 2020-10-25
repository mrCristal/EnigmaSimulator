#include "EnigmaParts.h"
    
Plugboard::Plugboard(std::map<int,int> encodingMap)
    {
			mapping = encodingMap;
	}
    
void Plugboard::processF(const int letter) const
    {
        right_member->rotate(1); // always rotates the next member
        						 // if its a reflector then nothing happens	
        right_member->processF(mapping.at(letter));
	}
	
void Plugboard::processB(const int letter) const
	{
		outBoard->print(mapping.at(letter));
	}

void Plugboard::print_mapping() const
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

void Plugboard::linkRightMember(Node* member)
{
	right_member = member;
}

void Plugboard::linkOutputBoard(OutputBoard* board)
{
	outBoard = board;
}
	
void Plugboard::rotate(const int size){};
