#include "EnigmaParts.h"

Rotor::Rotor(std::map<int,int> Map, std::vector<int> notches_list, int position) 
	{
		mapping = Map;
		notches = notches_list;
		rotations=position%alph_size;
	}
	
void Rotor::print_mapping() const
	{
		std::cout <<"Key ";
		for (int index = 0; index < alph_size; index++)
		{
			std::cout << (char)(index + alph_adj) << " ";
		}
		std::cout << std::endl;

		std::cout << "    ";
		for (int index = 0; index < alph_size; index++)
		{
			std::cout << "|" << " ";
		}
		std::cout << std::endl;

		std::cout << "Val ";
		for (int index = 0; index < alph_size; index++)
		{
			std::cout << (char)(mapping.at(index) + alph_adj) << " ";
		}
		std::cout << std::endl;
	}

void Rotor::rotate(const int shift_amount)
{
	int temp = rotations;
	rotations = (temp+shift_amount)%alph_size;
}

bool Rotor:: is_a_notch() const
{	
	if (std::find(notches.begin(),notches.end(),rotations) != notches.end())
	{ 
		return true;
	}
						
	return false;
}	
	
void Rotor::processF(const int letter) const
	{	
		if (is_a_notch())
		{
			right_member->rotate(1);
		}	
		
		int key = (letter+rotations)%alph_size;
		
		int value = (mapping.at(key) - rotations+alph_size)%alph_size;	

		right_member->processF(value);
		
	}
	
void Rotor::processB(const int letter) const
	{	
		int value = (letter+rotations)%alph_size;
		
		for (int index = 0; index<alph_size; index++)
		{
			if (mapping.at(index) == value)
			{	
			int key = (index-rotations+alph_size)%alph_size;
			
			left_member->processB(key);
			return;
			}
		} 
		std::cout<<"LETTER NOT FOUND"<<std::endl;
	}
	
void Rotor::linkLeftMember(Node* member)
{
	left_member = member;
}

void Rotor::linkRightMember(Node* member)
{
	right_member = member;
}
	
	
