function int add(const int x, const int y)
{
	return x + y;
}

print("Calculator App!");

while (true)
{
	int x = getInput();
	int y = getInput();
	int result = add(x, y);
	print("Result: " + result);
}
///////////////////////////////////////////////////////////////////////////////////
