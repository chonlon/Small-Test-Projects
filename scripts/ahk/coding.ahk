Numpad0::
	SendInput, {F5}
	return
Numpad1::
	SendInput, {F11}
	return
Numpad2::
	SendInput, {F10}
	return
;step out
Numpad3::
	SendInput, +{F11}
	return
;断点
Numpad9::
	SendInput, {F9}
	return
;注释
Numpad7::
	SendInput, ^k
	SendInput, ^c
	return
Numpad8::
	SendInput, ^k
	SendInput, ^u
	return


;暂停脚本
!^p::Suspend
	