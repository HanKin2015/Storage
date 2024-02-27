;
; 快捷输入密码.ahk
;
; author: hankin
; time  : 2021.02.07   
;
; Copyright (c) 2021 HanKin. All rights reserved.
;
; # win
; ! alt
; ^ ctrl
; + shift

!1::
Send Hankin@123{enter}
return

!2::
Send Hankin123{enter}
return

!3::
Send custom123{enter}
return

!4::
Send custom@123{enter}
return

!5::
Send Hankin123{enter}
return

!6::
Send test@123HankinHankin{enter}
return

!7::
Send Hankin@123{enter}
return

!8::
Send Hankin@123HankinHankin{enter}
return

!9::
Send test@123HankinHankin{enter}
return

!+1::
Send admin{tab}
return

!+2::
Send Administrator{tab}
return