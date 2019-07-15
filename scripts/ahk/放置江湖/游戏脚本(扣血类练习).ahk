F12::
loop, 100
{
	loop, 150
	{
		Send, 1
		Random, stime, 1000, 1500
		Sleep, 500
		Send, 2
		Sleep, $stime
	}
	Send, 3
	Sleep, 800
	Send, 4
	loop, 12
	{
		Sleep, 1500
		Send, 5
	}
}
return