function int test(int args = 15)
{
	if(args == 12)
	{
		return 10;
	}

	return 5 * 2;
}

function float add(int x, float y, str z)
{
	return x + y + z;
}

function bool defaultValue(bool def = false)
{
	return def;
}

function auto nothing()
{
}

{
	function auto empty()
	{
		return;
	}
}
