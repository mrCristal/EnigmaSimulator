allParsers: Reflector_Parser.o Plugboard_Parser.o Rotor_Parser.o Rotor_Position_Parser.o 

Rotor_Parser.o: Rotor_Parser.cpp Parsers.h
	g++ -Wall -g -c Rotor_Parser.cpp -o Rotor_Parser.o

Plugboard_Parser.o: Plugboard_Parser.cpp Parsers.h
	g++ -Wall -g -c Plugboard_Parser.cpp -o Plugboard_Parser.o

Reflector_Parser.o: Reflector_Parser.cpp Parsers.h
	g++ -Wall -g -c Reflector_Parser.cpp -o Reflector_Parser.o

Rotor_Position_Parser.o: Rotor_Position_Parser.cpp Parsers.h
	g++ -Wall -g -c Rotor_Position_Parser.cpp -o Rotor_Position_Parser.o 

allEnigmaParts: Plugboard.o Reflector.o Rotor.o OutputBoard.o InputBoard.o

Plugboard.o: EnigmaParts.h Plugboard.cpp
	g++ -Wall -g -c Plugboard.cpp -o Plugboard.o

Reflector.o: EnigmaParts.h Reflector.cpp
	g++ -Wall -g -c Reflector.cpp -o Reflector.o

Rotor.o: EnigmaParts.h Rotor.cpp
	g++ -Wall -g -c Rotor.cpp -o Rotor.o

OutputBoard.o: EnigmaParts.h OutputBoard.cpp
	g++ -Wall -g -c OutputBoard.cpp -o OutputBoard.o

InputBoard.o:EnigmaParts.h InputBoard.cpp
	g++ -Wall -g -c InputBoard.cpp -o InputBoard.o

enigma:InputBoard.o OutputBoard.o Rotor.o Reflector.o Plugboard.o Reflector_Parser.o Plugboard_Parser.o Rotor_Parser.o Rotor_Position_Parser.o  main.cpp 
	g++ -Wall -g InputBoard.o OutputBoard.o Rotor.o Reflector.o Plugboard.o Reflector_Parser.o Plugboard_Parser.o Rotor_Parser.o Rotor_Position_Parser.o  main.cpp -o enigma
