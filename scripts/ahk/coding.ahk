;--------------------------------------------------------------------|
;切换方法为点击状态栏到语言首选项进入高级键盘设置, 点击语言栏选项点击高级.  |
;--------------------------------------------------------------------|

; 注意, 新加的ahk需要加到这段下面, 不然这段代码不能执行成功.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 原作者：		lspcieee <lspcieee@gmail.com>
; 网站：		http://www.lspcieee.com/     
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;---edit by lon---
;=====分组配置
;分组分配的程序名字可以通过右键托盘ahk找到winspy, 使用它查看.
;新开窗口时，切换到中文输入法的分组
GroupAdd,cn,ahk_exe QQ.exe  ;QQ
GroupAdd,cn,ahk_exe TIM.exe  ;TIM
GroupAdd,cn,ahk_exe WINWORD.EXE ;word
GroupAdd,cn,ahk_exe wps.exe ;wps
GroupAdd,cn,ahk_exe DingTalk.exe
;新开窗口时，切换到英文输入法的分组
GroupAdd,en,ahk_exe devenv.exe  ;Visual Studio
GroupAdd,en,ahk_exe Code.exe  ;Visual Studio Code
GroupAdd,en,ahk_exe clion64.exe  ;clion
GroupAdd,en,ahk_class Notepad++
GroupAdd,en,ahk_class Listary_WidgetWin_0
GroupAdd,en,ahk_exe MobaXterm.exe ;terminal
;窗口切换时，切换到中文输入法
GroupAdd,cn32772,ahk_exe TIM.exe  ;TIM
GroupAdd,cn32772,ahk_exe DingTalk.exe  ;钉钉
GroupAdd,cn32772,ahk_exe chrome.exe	;谷歌浏览器
;窗口切换时，切换到英文输入法
GroupAdd,en32772,ahk_class Listary_WidgetWin_0
GroupAdd,en32772,ahk_exe Code.exe  ;Visual Studio Code
GroupAdd,en32772,ahk_exe devenv.exe  ;Visual Studio
GroupAdd,en32772,ahk_exe clion64.exe  ;clion
GroupAdd,en32772,ahk_exe MobaXterm.exe  ;terminal
;编辑器分组
GroupAdd,editor,ahk_exe devenv.exe  ;Visual Studio
GroupAdd,editor,ahk_exe clion64.exe  ;clion
GroupAdd,editor,ahk_exe Code.exe  ;Visual Studio Code
GroupAdd,editor,ahk_exe notepad.exe ;记事本
GroupAdd,editor,ahk_class Notepad++
;单独分组是因为在下面会对两个编辑器应用不同快捷键.
GroupAdd,visualstudio,ahk_exe devenv.exe
GroupAdd,visualstudiocode,ahk_exe Code.exe
GroupAdd,clion,ahk_exe clion64.exe  ;clion


;监控消息回调ShellMessage，并自动设置输入法
Gui +LastFound
hWnd := WinExist()
DllCall( "RegisterShellHookWindow", UInt,hWnd )
MsgNum := DllCall( "RegisterWindowMessage", Str,"SHELLHOOK" )
OnMessage( MsgNum, "ShellMessage")
ShellMessage( wParam,lParam ) {
;1 顶级窗体被创建
;2 顶级窗体即将被关闭
;3 SHELL 的主窗体将被激活
;4 顶级窗体被激活
;5 顶级窗体被最大化或最小化
;6 Windows 任务栏被刷新，也可以理解成标题变更
;7 任务列表的内容被选中
;8 中英文切换或输入法切换
;9 显示系统菜单
;10 顶级窗体被强制关闭
;11
;12 没有被程序处理的APPCOMMAND。见WM_APPCOMMAND
;13 wParam=被替换的顶级窗口的hWnd
;14 wParam=替换顶级窗口的窗口hWnd
;&H8000& 掩码
;53 全屏
;54 退出全屏
;32772 窗口切换
	If ( wParam = 1 ) ;新窗口被创建
	{
		;WinGetclass, WinClass, ahk_id %lParam%
		;MsgBox,%Winclass%
		Sleep, 1000
		;WinActivate,ahk_class %Winclass%
		;WinGetActiveTitle, Title
		;MsgBox, The active window is "%Title%".
		IfWinActive,ahk_group cn
		{
			setChineseLayout()
			;TrayTip,AHK, 1已自动切换到中文输入法
			return
		}
		IfWinActive,ahk_group en
		{
			setEnglishLayout()
			;TrayTip,AHK, 2已自动切换到英文输入法
			return
		}

		;setChineseLayout() ;有的弹窗会对{space}有响应, 所以也关了自动切换了..
		;TrayTip,AHK, 1已自动切换到中文输入法
		return
	}
	If ( wParam = 32772 ) ;窗口切换
	{
		IfWinActive,ahk_group cn32772
		{
			setChineseLayout()
			;TrayTip,AHK, 3已自动切换到中文输入法
			return
		}
		IfWinActive,ahk_group en32772
		{
            if WinActive("JetPopupMenuView")
				return
			setEnglishLayout()
			;TrayTip,AHK, 4已自动切换到英文输入法
			return
		}

		;setChineseLayout() ;sourcetail会对ctrl+space响应..., 想了想, 其它程序不自动切换了... 当然如果你设切换中英快捷键和我不一样可以开启.
		;TrayTip,AHK, 1已自动切换到中文输入法
		return
	}
}



;----------------------------------------------------------------------------
;switch header & source between editors.
; 这里是ctrl + 1
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
	IfWinActive,ahk_group clion
	{
		SendInput, {F10}
		return
	}
return
;------------------------------------------------------------------------------

;-------------------------------------------
;使用和vscode一样的快捷键format文档.
^!l::
	IfWinActive,ahk_group visualstudio
	{
		SendInput, ^k
		SendInput, ^d
		return
	}
	IfWinActive,ahk_group clion
	{
		SendInput, ^!l
		return
	}
	IfWinActive,ahk_group visualstudiocode
	{
		SendInput, +!f
	}
return
;--------------------------------------------

;--------------------------------------------
; editors back & forward

;--------------------------------------------

;暂停脚本
!^p::Suspend
^r::
	SendInput,^+!{Backspace}
	return

; 编程相关字串

^2::
	sendbyclip("#include ")
	return

;---------------------------------------------|
; 鼠标左键按下显示输入法状态.
; 如果不需要把这 LButton和LButton up两段删掉就行.
~LButton::
	If  (A_Cursor = "IBeam" ) {
		Edit_Mode := 1
	} 
	else {
		Edit_Mode := 0
	}
	; else if(A_Cursor = "Arrow" ) {
	; 	Edit_Mode := 0
	; }
	

	MouseGetPos, , , WhichWindow, WhichControl
	WinGetPos,winx,winy,,,%WhichWindow%
	ControlGetPos, x, y, w, h, %WhichControl%, ahk_id %WhichWindow%
;~ ToolTip, %WhichControl%`nX%X%`tY%Y%`nW%W%`t%H%
	showIMEStatus()
return

; ~Lbutton up::
; return
;--------------------------------------------|


;-----------以下是依赖函数--------------------------------------------|
;从剪贴板输入到界面
sendbyclip(var_string)
{
    ClipboardOld = %ClipboardAll%
    Clipboard =%var_string%
	ClipWait, 2
    send ^v
    sleep 100
    Clipboard = %ClipboardOld%  ; Restore previous contents of clipboard.
}


setChineseLayout(){
	;发送中文输入法切换快捷键，请根据实际情况设置。

	If (IME_GET()=1)
		return
	else
		; 输入法切换中英快捷键, 如果是ctrl+shift, 把下面Space替换成shift就行了
		send {Ctrl Down}{Space}
		send {Ctrl Up}
}
setEnglishLayout(){
	;发送英文输入法切换快捷键，请根据实际情况设置。
	If (IME_GET()=0)
		return
	else
		; 输入法切换中英快捷键
		send {Ctrl Down}{Space}
		send {Ctrl Up}
}


showIMEStatus() {
	if ( 0 = not_Edit_InFocus())
	{
		Sleep,100
		If (IME_GET()=1)
			ToolTip,中
		else
			ToolTip, EN

		Sleep,200 ;tooltip显示时间.
		ToolTip
	}
}
 
not_Edit_InFocus(){
	Global Edit_Mode
	ControlGetFocus theFocus, A ; 取得目前活動窗口 的焦點之控件标识符
	return  !(inStr(theFocus , "Edit") or  (theFocus = "Scintilla1")   ;把查到是文字編輯卻不含Edit名的theFucus加進來
	or (theFocus ="DirectUIHWND1") or  (Edit_Mode = 1))
}
 
IME_GET(WinTitle="")
; 获取当前输入法状态
{
    ifEqual WinTitle,,  SetEnv,WinTitle,A
    WinGet,hWnd,ID,%WinTitle%
    DefaultIMEWnd := DllCall("imm32\ImmGetDefaultIMEWnd", Uint,hWnd, Uint)
 
    ;Message : WM_IME_CONTROL  wParam:IMC_GETOPENSTATUS
    DetectSave := A_DetectHiddenWindows
    DetectHiddenWindows,ON
    SendMessage 0x283, 0x005,0,,ahk_id %DefaultIMEWnd%
    DetectHiddenWindows,%DetectSave%
    Return ErrorLevel
}

;在所有编辑器中注释时自动切换中文输入法
#IfWinActive,ahk_group editor
:*://  ::
	;//加空格 时 切换到中文输入法
	sendbyclip("// ")
	setChineseLayout()
return
:Z*:/// ::
	;///注释时 切换到中文输入法（也可以输入///加空格）
	sendbyclip("//")
	SendInput /
	setChineseLayout()
return
; :*:" ::
; 	;引号加空格 时 切换到中文输入法
; 	SendInput "
; 	setChineseLayout()
; return
#IfWinActive
;------------------------------------------------------------------------------------------------------------------


;------------------------------------------------------------|
;======================编辑器中的小键盘改成调试功能=============|
;------------------------------------------------------------|
;0:开始调试/停止/继续                                          |
;1:step in                                                   |
;2:step over                                                 |
;3:step out                                                  |
;------------------------------------------------------------|
#IfWinActive,ahk_group visualstudio
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
Numpad6::
	SendInput, !g
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
;取消注释
Numpad8::
	SendInput, ^k
	SendInput, ^u
	return
#IfWinActive
#IfWinActive,ahk_group visualstudiocode
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
Numpad6::
	SendInput, !g
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
#IfWinActive

#IfWinActive,ahk_group clion
!-::
	SendInput, ^!{Left}
	return
return
!=::
	SendInput, ^!{Right}
	return
return
;------------------------------------------------------------------------

