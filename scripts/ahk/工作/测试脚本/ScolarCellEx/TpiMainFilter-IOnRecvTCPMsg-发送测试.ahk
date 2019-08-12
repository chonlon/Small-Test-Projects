i := 0
str1 := "@C3,"
F6::
{
	loop, 10000
	{
		i := i + 1
		str := str1 i
		Send, %str%
		Send, {#}
		Send, {Enter}
		Sleep, 10
		Send, ^a
		Send, {BackSpace}
		Sleep, 100
	}
	return
}

!^p::Suspend