Eye Programming Language Specification

Syntax: 
Function Options: (Closures)
Grammar: 

Keywords:
{
	auto, const, true, false
	if,	else,
	for, while, continue, break,
	function, return,
	null,
}

Operators:
{
	+, -, *, /, %, ++, --, 
	=, +=, -=, *=, /=, %=, &=, |=, ^=, >>=, <<=
	==, !=, <, >, <=, >=,
	&&, ||, !,
	&, |, ^, <<, >>, ~,
	(, [, ?, ,
}

Symbols:
{
	), ], {, }, :, ;, \,
}

Commenting:
{
	Single Line -> // Comment
	Multi Line -> /* Comment */
}

Numbers:
{
	Decimal->Base 10
	Hex->Base 15
	Binary->Base 2
}

Escape Characters:
{
	\\, \t, \n, \'
}

TODO:
	Module/Include System
	Macros
	Namespace
