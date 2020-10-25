#ifndef Parsers_H
#define Parsers_H
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include "errors.h"
#include "helpers.h"

class Reflector_Parser //object to read reflector configuration files only
{	//checks if number has been read and processed before
	bool mapped_before(const int num1, const std::vector<int> prev_val_array, 
					   const int nr_of_vals) const; 
		
	bool the_same(const int num1, const int num2) const; 
	// checks if given int is between 0 and 25 (inclusive)
	bool in_range(const int number) const; 
	
	public:
	
	const char* fileName;
	
	std::map<int,int> mapping; // a map member used to store what each letter encodes
	
	Reflector_Parser (const char* name); 
	// prints the map to see configuration, used mainly for debugging
	void print_mapping() const; 
	// reads in the data from the file and does all the necessary checks + key->value assignments
	int configure_map(); 
	
};

class Plugboard_Parser{ // object to read plugboard configuration files only
	//checks if number has been read and processed before
	bool mapped_before(const int num1, const std::vector<int> prev_val_array, 
					  const int nr_of_vals) const; 
		
	bool the_same(const int num1, const int num2) const;
	// checks if given int is between 0 and 25 (inclusive)
	bool in_range(const int number) const; 
	
	public:
	
	const char* fileName;
	
	std::map<int, int> mapping; // a map member used to store what each letter encodes
	
	Plugboard_Parser(const char* name);
	// prints the map to see configuration, used mainly for debugging
	void print_mapping() const; 
	// reads in the data from the file and does all the necessary checks + key->value assignments
	int configure_map(); 
	
};

class Rotor_Parser{ // object to read rotor configuration files only
	// checks if given int is between 0 and 25 (inclusive)
	bool in_range(const int number) const; 
	
	//checks if number has been read and processed before
	bool mapped_before(const int num1, const std::vector<int> prev_val_array, 
					   const int nr_of_vals) const; 
	
	bool the_same(const int num1, const int num2) const;
	
	public:

    const char* fileName;

    std::map<int, int> mapping; // a map member used to store what each letter encodes
    
    std::vector<int> notches; // a vector to hold all the notches a given rotor is to have
    
    Rotor_Parser();
    
    void print_notches() const; // prints the notches, used mainly for debugging

    void print_mapping() const; // prints the map to see configuration, used mainly for debugging
	// reads in the data from the file and does all the necessary checks + key->value assignments
    int configure_map(); 

};

class Rotor_Position_Parser
{	 // object to read rotor position configuration files only
	bool in_range(const int number) const;
	 
	public:
	
	const char* fileName;
	
	std::vector<int> positions;
	
	Rotor_Position_Parser(const char* file);
	
	int read_positions();
};

#endif
