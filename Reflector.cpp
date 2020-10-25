#include "EnigmaParts.h"

Reflector::Reflector(std::map<int,int> encodingMap)
    {
        mapping = encodingMap;
    }

void Reflector::processB(const int letter) const
    {	
        left_member->processB(mapping.at(letter));
    }
void Reflector::processF(const int letter) const
{
	processB(letter);
}

void Reflector::print_mapping() const
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

void Reflector::linkLeftMember(Node* member)
{
	left_member = member;
}

void Reflector::rotate(const int size){}
