;功能：输入法状态提示
;环境：win10+搜狗输入法，输入法状态切换用默认的shift键。
;作者：sunwind
;时间：2018年9月1日
;更新链接：https://blog.csdn.net/liuyukuan/article/details/82291632
 

 
~LButton::
If  (A_Cursor = "IBeam" ) {
	Edit_Mode := 1
} else if(A_Cursor = "Arrow" ) {
   Edit_Mode := 0
} 
 
MouseGetPos, , , WhichWindow, WhichControl
WinGetPos,winx,winy,,,%WhichWindow%
ControlGetPos, x, y, w, h, %WhichControl%, ahk_id %WhichWindow%
;~ ToolTip, %WhichControl%`nX%X%`tY%Y%`nW%W%`t%H%
if ( 0 = not_Edit_InFocus())
{
	If (IME_GET()=1)
		ToolTip,中
	else
		ToolTip, EN
}
return

~Lbutton up::
Sleep,1000
ToolTip
return
 
not_Edit_InFocus(){
Global Edit_Mode
ControlGetFocus theFocus, A ; 取得目前活動窗口 的焦點之控件标识符
return  !(inStr(theFocus , "Edit") or  (theFocus = "Scintilla1")   ;把查到是文字編輯卻不含Edit名的theFucus加進來
or (theFocus ="DirectUIHWND1") or  (Edit_Mode = 1))
}
 
IME_GET(WinTitle="")
;-----------------------------------------------------------
; IMEの状態の取得
;    対象： AHK v1.0.34以降
;   WinTitle : 対象Window (省略時:アクティブウィンドウ)
;   戻り値  1:ON 0:OFF
;-----------------------------------------------------------
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