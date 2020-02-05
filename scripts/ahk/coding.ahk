;------------------------------------------------------------------------------------------------------------------;|||
;不同窗口之间输入法协调, 需要将中文输入法快捷键切换到ctrl+shift+1, 英文输入法切换到ctrl+shift+0才能工作            ;|||
;切换方法为点击状态栏到语言首选项进入高级键盘设置, 点击语言栏选项点击高级.                                         ;|||
;------------------------------------------------------------------------------------------------------------------;|||
																												   ;|||
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;                     ;|||
; AHK版本：		1.1.23.01                                                                                          ;|||
; 语言：		中文                                                                                               ;|||
; 作者：		lspcieee <lspcieee@gmail.com>                                                                      ;|||
; 网站：		http://www.lspcieee.com/                                                                           ;|||
; 脚本功能：	自动切换输入法                                                                                     ;|||
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;                     ;|||
;---edit by lon---                                                                                                 ;|||
																												   ;|||
;=====分组配置                                                                                                     ;|||
;新开窗口时，切换到中文输入法的分组                                                                                ;|||
GroupAdd,cn,ahk_exe QQ.exe  ;QQ                                                                                    ;|||
GroupAdd,cn,ahk_exe TIM.exe  ;TIM                                                                                  ;|||
GroupAdd,cn,ahk_exe WINWORD.EXE ;word                                                                              ;|||
GroupAdd,cn,ahk_exe wps.exe ;wps                                                                                   ;|||
GroupAdd,cn,ahk_exe DingTalk.exe                                                                                   ;|||
																												   ;|||
;新开窗口时，切换到英文输入法的分组                                                                                ;|||
GroupAdd,en,ahk_exe devenv.exe  ;Visual Studio                                                                     ;|||
GroupAdd,en,ahk_exe Code.exe  ;Visual Studio                                                                       ;|||
GroupAdd,en,ahk_class Notepad++                                                                                    ;|||
GroupAdd,en,ahk_class Listary_WidgetWin_0                                                                          ;|||
																												   ;|||
;窗口切换时，切换到中文输入法                                                                                      ;|||
GroupAdd,cn32772,ahk_exe TIM.exe  ;TIM                                                                             ;|||
GroupAdd,cn32772,ahk_exe DingTalk.exe  ;钉钉                                                                       ;|||
GroupAdd,cn32772,ahk_exe chrome.exe	;谷歌浏览器																	   ;|||
;窗口切换时，切换到英文输入法                                                                                      ;|||
GroupAdd,en32772,ahk_class Listary_WidgetWin_0                                                                     ;|||
GroupAdd,en32772,ahk_exe Code.exe  ;Visual Studio Code                                                             ;|||
GroupAdd,en32772,ahk_exe devenv.exe  ;Visual Studio                                                                ;|||
                                                                                                                   ;|||
;编辑器分组                                                                                                        ;|||
GroupAdd,editor,ahk_exe devenv.exe  ;Visual Studio                                                                 ;|||
GroupAdd,editor,ahk_exe Code.exe  ;Visual Studio                                                                   ;|||
GroupAdd,editor,ahk_exe notepad.exe ;记事本                                                                        ;|||
GroupAdd,editor,ahk_class Notepad++                                                                                ;|||
                                                                                                                   ;|||
GroupAdd,visualstudio,ahk_exe devenv.exe                                                                           ;|||
GroupAdd,visualstudiocode,ahk_exe Code.exe																		   ;|||
																												   ;|||
																												   ;|||
																												   ;|||
;函数                                                                                                              ;|||
;从剪贴板输入到界面                                                                                                ;|||
sendbyclip(var_string)                                                                                             ;|||
{                                                                                                                  ;|||
    ClipboardOld = %ClipboardAll%                                                                                  ;|||
    Clipboard =%var_string%                                                                                        ;|||
	ClipWait, 2                                                                                                    ;|||
    send ^v                                                                                                        ;|||
    sleep 100                                                                                                      ;|||
    Clipboard = %ClipboardOld%  ; Restore previous contents of clipboard.                                          ;|||
}                                                                                                                  ;|||
																												   ;|||
																												   ;|||
setChineseLayout(){                                                                                                ;|||
	;发送中文输入法切换快捷键，请根据实际情况设置。                                                                ;|||
	; send {Ctrl Down}{Shift}                                                                                      ;|||
	; send {Ctrl Down},                                                                                            ;|||
	; send {Ctrl Down}{Shift}                                                                                      ;|||
	send {Ctrl Down}                                                                                              ;|||
	send {Ctrl Up}                                                                                                 ;|||
	;send !+0                                                                                                      ;|||
}                                                                                                                  ;|||
setEnglishLayout(){                                                                                                ;|||
	;发送英文输入法切换快捷键，请根据实际情况设置。                                                                ;|||
	setChineseLayout()                                                                                             ;|||
	send {LWin Down}{Space}                                                                                        ;|||
	send {LWin Up}                                                                                                 ;|||
}                                                                                                                  ;|||
																												   ;|||
;监控消息回调ShellMessage，并自动设置输入法                                                                        ;|||
Gui +LastFound                                                                                                     ;|||
hWnd := WinExist()                                                                                                 ;|||
DllCall( "RegisterShellHookWindow", UInt,hWnd )                                                                    ;|||
MsgNum := DllCall( "RegisterWindowMessage", Str,"SHELLHOOK" )                                                      ;|||
OnMessage( MsgNum, "ShellMessage")                                                                                 ;|||
																												   ;|||
ShellMessage( wParam,lParam ) {                                                                                    ;|||
																												   ;|||
;1 顶级窗体被创建                                                                                                  ;|||
;2 顶级窗体即将被关闭                                                                                              ;|||
;3 SHELL 的主窗体将被激活                                                                                          ;|||
;4 顶级窗体被激活                                                                                                  ;|||
;5 顶级窗体被最大化或最小化                                                                                        ;|||
;6 Windows 任务栏被刷新，也可以理解成标题变更                                                                      ;|||
;7 任务列表的内容被选中                                                                                            ;|||
;8 中英文切换或输入法切换                                                                                          ;|||
;9 显示系统菜单                                                                                                    ;|||
;10 顶级窗体被强制关闭                                                                                             ;|||
;11                                                                                                                ;|||
;12 没有被程序处理的APPCOMMAND。见WM_APPCOMMAND                                                                    ;|||
;13 wParam=被替换的顶级窗口的hWnd                                                                                  ;|||
;14 wParam=替换顶级窗口的窗口hWnd                                                                                  ;|||
;&H8000& 掩码                                                                                                      ;|||
;53 全屏                                                                                                           ;|||
;54 退出全屏                                                                                                       ;|||
;32772 窗口切换                                                                                                    ;|||
	If ( wParam = 1 )                                                                                              ;|||
	{                                                                                                              ;|||
		;WinGetclass, WinClass, ahk_id %lParam%                                                                    ;|||
		;MsgBox,%Winclass%                                                                                         ;|||
		Sleep, 1000                                                                                                ;|||
		;WinActivate,ahk_class %Winclass%                                                                          ;|||
		;WinGetActiveTitle, Title                                                                                  ;|||
		;MsgBox, The active window is "%Title%".                                                                   ;|||
		IfWinActive,ahk_group cn                                                                                   ;|||
		{                                                                                                          ;|||
			setChineseLayout()                                                                                     ;|||
			;TrayTip,AHK, 1已自动切换到中文输入法                                                                  ;|||
			return                                                                                                 ;|||
		}                                                                                                          ;|||
		IfWinActive,ahk_group en                                                                                   ;|||
		{                                                                                                          ;|||
			setEnglishLayout()                                                                                     ;|||
			;TrayTip,AHK, 2已自动切换到英文输入法                                                                  ;|||
			return                                                                                                 ;|||
		}                                                                                                          ;|||
	}                                                                                                              ;|||
	If ( wParam = 32772 )                                                                                          ;|||
	{                                                                                                              ;|||
		IfWinActive,ahk_group cn32772                                                                              ;|||
		{                                                                                                          ;|||
			setChineseLayout()                                                                                     ;|||
			;TrayTip,AHK, 3已自动切换到中文输入法                                                                  ;|||
			return                                                                                                 ;|||
		}                                                                                                          ;|||
		IfWinActive,ahk_group en32772                                                                              ;|||
		{                                                                                                          ;|||
            if WinActive("JetPopupMenuView")
				return
			setEnglishLayout()                                                                                     ;|||
			;TrayTip,AHK, 4已自动切换到英文输入法                                                                  ;|||
			return                                                                                                 ;|||
		}                                                                                                          ;|||
	}                                                                                                              ;|||
}                                                                                                                  ;|||
																												   ;|||
;在所有编辑器中自动切换中英文输入法                                                                                ;|||
#IfWinActive,ahk_group editor                                                                                      ;|||
:*://  ::                                                                                                          ;|||
	;//加空格 时 切换到中文输入法                                                                                  ;|||
	sendbyclip("// ")                                                                                              ;|||
	setChineseLayout()                                                                                             ;|||
return                                                                                                             ;|||
:Z*:/// ::                                                                                                         ;|||
	;///注释时 切换到中文输入法（也可以输入///加空格）                                                             ;|||
	sendbyclip("//")                                                                                               ;|||
	SendInput /                                                                                                    ;|||
	setChineseLayout()                                                                                             ;|||
return                                                                                                             ;|||
:*:" ::                                                                                                            ;|||
	;引号加空格 时 切换到中文输入法                                                                                ;|||
	SendInput "                                                                                                    ;|||
	setChineseLayout()                                                                                             ;|||
return                                                                                                             ;|||
#IfWinActive                                                                                                       ;|||
;------------------------------------------------------------------------------------------------------------------;|||



;------------------------------------------------------------------------------------------------------------------;|||
;======================编辑器中的小键盘改成调试功能================================================================;|||
;------------------------------------------------------------------------------------------------------------------;|||
;0:开始调试/停止/继续                                                                                              ;|||
;1:step in                                                                                                         ;|||
;2:step over                                                                                                       ;|||
;3:step out                                                                                                        ;|||
;------------------------------------------------------------------------------------------------------------------;|||
#IfWinActive,ahk_group visualstudio                                                                                ;|||
Numpad0::                                                                                                          ;|||
	SendInput, {F5}                                                                                                ;|||
	return                                                                                                         ;|||
Numpad1::                                                                                                          ;|||
	SendInput, {F11}                                                                                               ;|||
	return                                                                                                         ;|||
Numpad2::                                                                                                          ;|||
	SendInput, {F10}                                                                                               ;|||
	return                                                                                                         ;|||
;step out                                                                                                          ;|||
Numpad3::                                                                                                          ;|||
	SendInput, +{F11}                                                                                              ;|||
	return                                                                                                         ;|||
                                                                                                                   ;|||
Numpad6::                                                                                                          ;|||
	SendInput, !g                                                                                                  ;|||
	return                                                                                                         ;|||
;断点                                                                                                              ;|||
Numpad9::                                                                                                          ;|||
	SendInput, {F9}                                                                                                ;|||
	return                                                                                                         ;|||
;注释                                                                                                              ;|||
Numpad7::                                                                                                          ;|||
	SendInput, ^k                                                                                                  ;|||
	SendInput, ^c                                                                                                  ;|||
	return                                                                                                         ;|||
Numpad8::                                                                                                          ;|||
	SendInput, ^k                                                                                                  ;|||
	SendInput, ^u                                                                                                  ;|||
	return                                                                                                         ;|||
#IfWinActive                                                                                                       ;|||
                                                                                                                   ;|||
#IfWinActive,ahk_group visualstudiocode                                                                            ;|||
Numpad0::                                                                                                          ;|||
	SendInput, {F5}                                                                                                ;|||
	return                                                                                                         ;|||
Numpad1::                                                                                                          ;|||
	SendInput, {F11}                                                                                               ;|||
	return                                                                                                         ;|||
Numpad2::                                                                                                          ;|||
	SendInput, {F10}                                                                                               ;|||
	return                                                                                                         ;|||
;step out                                                                                                          ;|||
Numpad3::                                                                                                          ;|||
	SendInput, +{F11}                                                                                              ;|||
	return                                                                                                         ;|||
                                                                                                                   ;|||
Numpad6::                                                                                                          ;|||
	SendInput, !g                                                                                                  ;|||
	return                                                                                                         ;|||
;断点                                                                                                              ;|||
Numpad9::                                                                                                          ;|||
	SendInput, {F9}                                                                                                ;|||
	return                                                                                                         ;|||
;注释                                                                                                              ;|||
Numpad7::                                                                                                          ;|||
	SendInput, ^k                                                                                                  ;|||
	SendInput, ^c                                                                                                  ;|||
	return                                                                                                         ;|||
Numpad8::                                                                                                          ;|||
	SendInput, ^k                                                                                                  ;|||
	SendInput, ^u                                                                                                  ;|||
	return                                                                                                         ;|||
#IfWinActive                                                                                                       ;|||
;------------------------------------------------------------------------------------------------------------------;|||


;switch header & source between editors.
^1::
	IfWinActive,ahk_group visualstudio                                                                                   
	{                                                                                                          
		SendInput, ^k
		Sleep, 100
		SendInput, ^o
		return                                                                                             
	}
	IfWinActive,ahk_group visualstudiocode                                                                                   
	{                                                                                                          
		SendInput, !o
		return                                                                                             
	}
	return

^Space::
	Sleep, 200
	send {LWin Down}{Space}{LWin Up}
	return





;暂停脚本
!^p::Suspend
^r::
	SendInput,^+!{Backspace}
	return
	
