

;------------------------依赖函数---------------------
;获取选中的文字
getSelText()
{
    ;ClipboardOld:=ClipboardAll
    Clipboard:=""
    SendInput, ^{insert}
    ClipWait, 0.1
    if(!ErrorLevel)
    {
        selText:=Clipboard
        ;Clipboard:=ClipboardOld
        StringRight, lastChar, selText, 1
        return selText
    }
    ;Clipboard:=ClipboardOld
    return
}

;绕过输入法
ascinput(string){
u :=  A_IsUnicode ? 2 : 1 ;Unicode版ahk字符长度是2
length:=StrPut(string,"CP0")
if(A_IsUnicode)
    {
    VarSetCapacity(address,length),StrPut(string,&address,"CP0")
    }
else
    address:=string
VarSetCapacity(out,2*length*u)
index =0
Loop
{
index += 1
if (index>length-1)
    Break
asc := NumGet(address,index-1,"UChar")
if asc > 126
    {
    index += 1
    asc2 := NumGet(address,index-1,"UChar")
    asc := asc*256+asc2
    }
SendInput, % "{ASC " asc "}"
}
}

;--------------------------------------------------------;|||
;取消CapsLock与某些键按下时会改变大写锁定状态------------;|||
;-------------------------按键功能-----------------------;|||
Capslock::return                                         ;|||
Capslock & Enter::return                                 ;|||
;Capslock & t::return                                    ;|||
+Capslock::return                                        ;|||
!Capslock::return                                        ;|||
Capslock & z::return                                     ;|||
;Capslock & a::return                                    ;|||
Capslock & x::return                                     ;|||
Capslock & b::return                                     ;|||
;Capslock & t::return                                    ;|||
Capslock & ,::return                                     ;|||
;Capslock & .::return                                    ;|||
Capslock & \::return                                     ;|||
Capslock & -::return                                     ;|||
Capslock & =::return                                     ;|||
Capslock & /::return                                     ;|||
														 ;|||
														 ;|||
Capslock & 4::return                                     ;|||
Capslock & 5::return                                     ;|||
Capslock & 6::return                                     ;|||
Capslock & 7::return                                     ;|||
Capslock & 8::return                                     ;|||
;Capslock & 9::return                                    ;|||
Capslock & 0::return                                     ;|||
;--------------------------------------------------------;|||


;----------------------- 改变大写锁定状态 ------------------------------------------------;|||
LAlt & Capslock::                                                                         ;|||
	SetCapsLockState, % GetKeyState("CapsLock", "T") ? "Off" : "On"                       ;|||
return                                                                                    ;|||
Shift & Capslock::                                                                        ;|||
	SetCapsLockState, % GetKeyState("CapsLock", "T") ? "Off" : "On"                       ;|||
return                                                                                    ;|||
;-----------------------------------------------------------------------------------------;|||

;----------------------- 调用wox的有道翻译插件实现翻译功能--------------------------------;|||
!t::                                                                                      ;|||
  ;获取选中的文字                                                                         ;|||
  ClipSaved := ClipboardAll                                                               ;|||
  selText:=getSelText()                                                                   ;|||
																						  ;|||
 ; 发送 Listary的呼出快捷键），呼出Listary                                                ;|||
  SendInput, !^+f                                                                         ;|||
																						  ;|||
  ; 等待 Listary 输入框打开                                                               ;|||
  sleep, 50                                                                               ;|||
																						  ;|||
  ; 如果有选中文字的话                                                                    ;|||
  if(selText){                                                                            ;|||
	selText:="fy " . selText                                                              ;|||
    ;ClipSaved := ClipboardAll       ; save clipboard                                     ;|||
    clipboard := selText                                                                  ;|||
     ClipWait, 0.1                                                                        ;|||
     Send, ^v                                                                             ;|||
     clipboard := ClipSaved                                                               ;|||
	}                                                                                     ;|||
	else                                                                                  ;|||
	{                                                                                     ;|||
		ascinput("fy ")                                                                   ;|||
	}                                                                                     ;|||
	SendInput, {Alt}                                                                      ;|||
return                                                                                    ;|||
;-----------------------------------------------------------------------------------------;|||



;-------------------------------------------调用listary-----------------------------------;|||
Capslock & q::                                                                            ;|||
 ; 获取选中的文字                                                                         ;|||
  ClipSaved := ClipboardAll                                                               ;|||
  selText:=getSelText()                                                                   ;|||
																						  ;|||
  ; 发送 Listary的呼出快捷键），呼出Listary                                               ;|||
  SendInput, !^+f                                                                         ;|||
																						  ;|||
  ; 等待 Listary 输入框打开                                                               ;|||
  sleep, 50                                                                               ;|||
																						  ;|||
  ; 如果有选中文字的话                                                                    ;|||
  if(selText){                                                                            ;|||
    ;ClipSaved := ClipboardAll       ; save clipboard                                     ;|||
    clipboard := selText                                                                  ;|||
     ClipWait, 0.1                                                                        ;|||
     Send, ^v                                                                             ;|||
     clipboard := ClipSaved                                                               ;|||
	sendInput, {home}                                                                     ;|||
	}                                                                                     ;|||
																						  ;|||
return                                                                                    ;|||
;=========================================================================================;|||




;-------------------------Capslock快捷键--------------------------------------------------;|||
Capslock & Backspace::                                                                    ;|||
	SendInput, {Backspace}                                                                ;|||
	return                                                                                ;|||
																						  ;|||
;=======上下左右======;||                                                                 ;|||
Capslock & e::        ;||                                                                 ;|||
SendInput,{up}        ;||                                                                 ;|||
return                ;||                                                                 ;|||
					  ;||                                                                 ;|||
Capslock & s::        ;||                                                                 ;|||
 SendInput,{left}     ;||                                                                 ;|||
    return            ;||                                                                 ;|||
					  ;||                                                                 ;|||
Capslock & d::        ;||                                                                 ;|||
 SendInput,{down}     ;||                                                                 ;|||
    Return            ;||                                                                 ;|||
					  ;||                                                                 ;|||
Capslock & f::        ;||                                                                 ;|||
 SendInput,{right}    ;||                                                                 ;|||
    Return            ;||                                                                 ;|||
;=====================;||	                                                              ;|||
																						  ;|||
;===shfit+上下左右======;||                                                               ;|||
Capslock & i::          ;||                                                               ;|||
 SendInput,+{up}        ;||                                                               ;|||
 SendInput,+{home}      ;||                                                               ;|||
    Return              ;||                                                               ;|||
Capslock & j::          ;||                                                               ;|||
 SendInput,+{left}      ;||                                                               ;|||
    Return              ;||                                                               ;|||
Capslock & k::          ;||                                                               ;|||
 SendInput,{home}       ;||                                                               ;|||
 SendInput,+{end}       ;||                                                               ;|||
 SendInput,+{down}      ;||                                                               ;|||
 SendInput,+{end}       ;||                                                               ;|||
    Return              ;||                                                               ;|||
Capslock & l::          ;||                                                               ;|||
	SendInput,+{right}  ;||                                                               ;|||
    Return              ;||                                                               ;|||
;=======================;||                                                               ;|||
																						  ;|||
;====左右选一个词=======;||                                                               ;|||
Capslock & h::          ;||                                                               ;|||
	SendInput,^+{left}  ;||                                                               ;|||
	Return              ;||                                                               ;|||
Capslock & `;::         ;||                                                               ;|||
	SendInput,^+{right} ;||                                                               ;|||
    Return              ;||                                                               ;|||
;=======================;||                                                               ;|||
																						  ;|||
;======其它=============================;||	                                              ;|||
Capslock & u::                          ;||                                               ;|||
	SendInput,+{home}                   ;||                                               ;|||
    Return                              ;||                                               ;|||
Capslock & o::                          ;||                                               ;|||
	SendInput,+{end}                    ;||                                               ;|||
    Return                              ;||                                               ;|||
										;||                                               ;|||
;Backspace                              ;||                                               ;|||
Capslock & y::                          ;||                                               ;|||
 SendInput,{Backspace}                  ;||                                               ;|||
    Return                              ;||                                               ;|||
										;||                                               ;|||
;home                                   ;||                                               ;|||
Capslock & a::                          ;||                                               ;|||
 SendInput,{Home}                       ;||                                               ;|||
    Return                              ;||                                               ;|||
										;||                                               ;|||
;end                                    ;||                                               ;|||
Capslock & g::                          ;||                                               ;|||
  SendInput,{End}                       ;||                                               ;|||
    Return                              ;||                                               ;|||
										;||                                               ;|||
;删除一整行                             ;||                                               ;|||
Capslock & r::                          ;||                                               ;|||
										;||                                               ;|||
 SendInput,{End}                        ;||                                               ;|||
 SendInput,+{home}                      ;||                                               ;|||
 SendInput,+{home}                      ;||                                               ;|||
 SendInput,{bs}                         ;||                                               ;|||
    Return                              ;||                                               ;|||
========================================;||                                               ;|||
;;打开f盘                                                                                 ;|||
;Capslock & w::                                                                           ;|||
; Run, explore F:                                                                         ;|||
; ;Run, C:\Program Files (x86)\FreeCommander XE\FreeCommander.exe F:                      ;|||
; Return                                                                                  ;|||
																						  ;|||
 ;选取一整行                                                                              ;|||
 Capslock & Space::                                                                       ;|||
   SendInput,{End}+{home}                                                                 ;|||
    Return                                                                                ;|||
																						  ;|||
;复制粘贴                                                                                 ;|||
Capslock & c::                                                                            ;|||
   SendInput,^c                                                                           ;|||
    Return                                                                                ;|||
Capslock & v::                                                                            ;|||
   SendInput,^v                                                                           ;|||
    Return                                                                                ;|||
																						  ;|||
																						  ;|||
Capslock & t::                                                                            ;|||
     SendInput,{End}{Enter}                                                               ;|||
    Return                                                                                ;|||
																						  ;|||
																						  ;|||
Capslock & 9::                                                                            ;|||
	ClipSaved := ClipboardAll                                                             ;|||
	selText:=getSelText()                                                                 ;|||
	selText:="(" selText ")"                                                              ;|||
    clipboard := selText                                                                  ;|||
     ClipWait, 0.1                                                                        ;|||
     Send, ^v                                                                             ;|||
     clipboard := ClipSaved                                                               ;|||
	return                                                                                ;|||
Capslock & [::                                                                            ;|||
	ClipSaved := ClipboardAll                                                             ;|||
	selText:=getSelText()                                                                 ;|||
	selText:="{" selText "}"                                                              ;|||
    clipboard := selText                                                                  ;|||
     ClipWait, 0.1                                                                        ;|||
     Send, ^v                                                                             ;|||
     clipboard := ClipSaved                                                               ;|||
	return                                                                                ;|||
Capslock & ]::                                                                            ;|||
	ClipSaved := ClipboardAll                                                             ;|||
	selText:=getSelText()                                                                 ;|||
	selText:="[" selText "]"                                                              ;|||
    clipboard := selText                                                                  ;|||
     ClipWait, 0.1                                                                        ;|||
     Send, ^v                                                                             ;|||
     clipboard := ClipSaved                                                               ;|||
	return                                                                                ;|||
 Capslock & '::                                                                           ;|||
	ClipSaved := ClipboardAll                                                             ;|||
	selText:=getSelText()                                                                 ;|||
	var="                                                                                 ;|||
	selText:=var . selText                                                                ;|||
	selText:=selText . var                                                                ;|||
    clipboard := selText                                                                  ;|||
     ClipWait, 0.1                                                                        ;|||
     Send, ^v                                                                             ;|||
     clipboard := ClipSaved                                                               ;|||
	return                                                                                ;|||
;实现chrome的标签页切换                                                                   ;|||
Capslock & n::                                                                            ;|||
	SendInput, ^k                                                                         ;|||
	sleep, 500                                                                            ;|||
	SendInput, ^o                                                                         ;|||
	return                                                                                ;|||
Capslock & m::                                                                            ;|||
	SendInput, ^{Tab}                                                                     ;|||
	return                                                                                ;|||
;;;;;;编辑器操作                                                                          ;|||

																						  ;|||
;-------------快速跳转-----------------------------;|                                     ;|||
;------o                                           ;|                                     ;|||
Capslock & 1::                                     ;|                                     ;|||
	loop, 2                                        ;|                                     ;|||
		SendInput, {Up}                            ;|                                     ;|||
	return                                         ;|                                     ;|||
                                                   ;|                                     ;|||
Capslock & 2::                                     ;|                                     ;|||
	loop, 4                                        ;|                                     ;|||
		SendInput, {Up}                            ;|                                     ;|||
	return                                         ;|                                     ;|||
                                                   ;|                                     ;|||
Capslock & 3::                                     ;|                                     ;|||
	loop, 6                                        ;|                                     ;|||
		SendInput, {Up}                            ;|                                     ;|||
	return                                         ;|                                     ;|||
;--------------------------------------------------;|                                     ;|||
;=========================================================================================;|||
	
;------------alt快捷键---------------------------+++++++++++++++++++++++++++++++++++++++++


;==调试快捷键==
!q::F5
!w::+

	
;numspad快捷键
;Numpad0::Numpad0
Ctrl & Numpad1::
	SoundSet +3 ; 将主音量增加 10%
	return
Ctrl & Numpad2::
	Send {Volume_Mute} ;静音
	return
Ctrl & Numpad3::
	SoundSet -3 ; 将主音量减小 10%
	return
Ctrl & Numpad8::
	SoundSet, 1, Microphone, mute  ; 对麦克风进行静音
	return

;媒体播放
Ctrl & Numpad4::
	SendInput, {Media_Prev}
	return
Ctrl & Numpad5::
	SendInput, {Media_Play_Pause}
	return
Ctrl & Numpad6::
	SendInput, {Media_Next}
	return

	
;----------------热字串----------------
:R:;qm::1017027609@qq.com
:R:;gm::lonelycooler.xcl@gmail.com
:*:;nm::18838957569
:R:;fnm::15179368691

;代码相关
;functions:
doPastePar()
{
	Sleep, 100
	ClipSaved := ClipboardAll
	selText:="/// <param name: > </param>"
    clipboard := selText
     ClipWait, 0.1
     Send, ^v
     clipboard := ClipSaved
	Loop, 10
	{
		Send, {Left}
	}
	return
}

doPastePointer()
{
	Send, -
	Sleep, 15
	Send, >
	return
}

doPasteSum()
{
	Sleep, 100
	ClipSaved := ClipboardAll
	selText:="/// <summary> </summary>"
    clipboard := selText
     ClipWait, 0.1
     Send, ^v
     clipboard := ClipSaved
	Loop, 10
	{
		Send, {Left}
	}
	return
}

doPasteRet()
{
	Sleep, 100
	ClipSaved := ClipboardAll
	selText:="/// <returns> </returns>"
    clipboard := selText
     ClipWait, 0.1
     Send, ^v
     clipboard := ClipSaved
	Loop, 10
	{
		Send, {Left}
	}
	return
}

doPasteCom() 
{
		Sleep, 100
	ClipSaved := ClipboardAll
	selText:="/////////////////////////////`r`n//`r`n/////////////////////////////"
    clipboard := selText
     ClipWait, 0.1
     Send, ^v
     clipboard := ClipSaved
	return
}

;实现->的操作                                                                             
Capslock & .::                                                                            
	doPastePointer()                                                                         
	return                                                                                

:R:;par::
    doPastePar()
	return
:R:;sum::
    doPasteSum()
	return
:R:;ret::
	doPasteRet()
	return
:R:;com::
	doPasteCom()
	return


;---------------快捷打开应用------------+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++;|||
::;vbox::                                                                                                          ;|||
	run, F:\programs\虚拟机\virtual box\VirtualBox.exe                                                             ;|||
	return                                                                                                         ;|||
::;qmusic::                                                                                                        ;|||
	run, C:\Program Files (x86)\Tencent\QQMusic\QQMusic.exe                                                        ;|||
	return                                                                                                         ;|||
::;note::                                                                                                          ;|||
	run, C:\Program Files (x86)\Notepad++\notepad++.exe                                                            ;|||
	return                                                                                                         ;|||
;打开vscode                                                                                                        ;|||
::;vscode::                                                                                                        ;|||
	run, F:\programs\编辑器\Microsoft VS Code\Code.exe                                                             ;|||
	return                                                                                                         ;|||
;打开vs                                                                                                            ;|||
::;vs::                                                                                                            ;|||
	run, C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.exe                      ;|||
	return                                                                                                         ;|||
;打开idea                                                                                                          ;|||
::;idea::                                                                                                          ;|||
	run, F:\programs\IDE\IntelliJ IDEA 2017.2.5\bin\idea64.exe                                                     ;|||
	return                                                                                                         ;|||
;打开网易云                                                                                                        ;|||
!m::                                                                                                               ;|||
	run, E:\CloudMusic\CloudMusic\cloudmusic.exe                                                                   ;|||
	return                                                                                                         ;|||
;打开androidStudio                                                                                                 ;|||
::;android::                                                                                                       ;|||
	run, F:\programs\IDE\Android\AndroidStudio\bin\studio64.exe                                                    ;|||
	return                                                                                                         ;|||
																												   ;|||
;打开code文件夹                                                                                                    ;|||
::;co::                                                                                                            ;|||
	run, F:\Code                                                                                                   ;|||
	return                                                                                                         ;|||
																												   ;|||
;打开codeOfself文件夹                                                                                              ;|||
::;cos::                                                                                                           ;|||
	run, F:\Code\CodeOfself                                                                                        ;|||
	return                                                                                                         ;|||
																												   ;|||
;打开下载文件夹                                                                                                    ;|||
::;dl::                                                                                                            ;|||
	run, F:\下载                                                                                                   ;|||
	return                                                                                                         ;|||
;打开桌面文件夹                                                                                                    ;|||
::;desk::                                                                                                          ;|||
	run, C:\Users\10170\Desktop                                                                                    ;|||
	return                                                                                                         ;|||
;打开虎牙                                                                                                          ;|||
::;huya::                                                                                                          ;|||
	run, F:\programs\视频\huya\HuyaClient\Net45\HuyaClient.exe                                                     ;|||
	return                                                                                                         ;|||
::;py::                                                                                                            ;|||
	run, C:\Users\10170\AppData\Local\Programs\Python\Python36\python.exe                                          ;|||
	return                                                                                                         ;|||
::;fy::                                                                                                            ;|||
	run, https://translate.google.cn                                                                               ;|||
	return                                                                                                         ;|||
::;cmd::                                                                                                           ;|||
	run, F:\programs\cmder\Cmder.exe                                                                               ;|||
	return                                                                                                         ;|||
;++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++;|||

;+++窗口置顶+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++;|||
!Up::                                                                                                              ;|||
																												   ;|||
    WinGet ow, id, A                                                                                               ;|||
																												   ;|||
    WinTopToggle(ow)                                                                                               ;|||
																												   ;|||
    return                                                                                                         ;|||
																												   ;|||
WinTopToggle(w) {                                                                                                  ;|||
																												   ;|||
    WinGetTitle, oTitle, ahk_id %w%                                                                                ;|||
																												   ;|||
    Winset, AlwaysOnTop, Toggle, ahk_id %w%                                                                        ;|||
																												   ;|||
    WinGet, ExStyle, ExStyle, ahk_id %w%                                                                           ;|||
																												   ;|||
    if (ExStyle & 0x8)                                                                                             ;|||
																												   ;|||
    oTop = 置顶                                                                                                    ;|||
																												   ;|||
    else                                                                                                           ;|||
																												   ;|||
    oTop = 取消置顶                                                                                                ;|||
																												   ;|||
    tooltip %oTitle% %oTop%                                                                                        ;|||
																												   ;|||
    SetTimer, RemoveToolTip, 1000                                                                                  ;|||
																												   ;|||
    return                                                                                                         ;|||
																												   ;|||
    RemoveToolTip:                                                                                                 ;|||
																												   ;|||
    SetTimer, RemoveToolTip, Off                                                                                   ;|||
																												   ;|||
    ToolTip                                                                                                        ;|||
																												   ;|||
    return                                                                                                         ;|||
																												   ;|||
}                                                                                                                  ;|||