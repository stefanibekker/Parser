// Stefani Bekker
// CS530, Spring 2019
// Assignment 3 Parser
// README

Files:
main.cpp
Header.h
makefile
ex.txt
README

Instructions:
To compile type "make". To run, type ./ and the name of the program which is "exp".

What I Learned:
I learned more about the C++ language, as well as how a proper parser operates.

Grammar:
<assignment>	::= <identifier> <equal> <expression> <semi-colon>
<expression>	::= <identifier> <operator> <identifier> | "(" <opt-whitespace> <expression> <opt-whitespace> ")" | <identifier> <operator> <expression> | <expression> <operator> <identifier> | <expression> <operator> <expression>
<opt-whitespace>::= "" | " "
<identifier>	::= <char> | <identifier> <digit> | <identifier> <char>
<char>		    ::= "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z"
<digit>		    ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<op>		    ::= "+" | "-" | "*" | "/" | "%"
<equal> 	    ::= "="
<semi-colon>	::= ";"

