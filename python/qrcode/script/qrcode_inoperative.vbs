Set objShell = CreateObject("WScript.Shell")
objShell.Run "cmd /c ""C:\Users\User\anaconda3\Scripts\activate.bat"" C:\Users\User\anaconda3 && python ""D:\Tools\qrcode_interface.py""", 0, True
Set WshShell = Nothing