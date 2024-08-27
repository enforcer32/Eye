auto number = 0;
auto cond = true;

if(cond)
{
	number = 5;
}
else
{
	number = 10;
}

if(number == 0)
	number += 10;
else if(number > 5)
	number += 20;
else
	number += 30;

if(number != 30)
	number = 30;
