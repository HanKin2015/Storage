;Author: Dunchen
;Date: 2014/2/12
^!c::                                      ;设定快捷键，可以根据自己喜好更改（^是ctrl，!是alt，#是Windows键，::是分隔符不可更改）这里默认是ctrl+alt+c
  location=d:\team\log.txt                 ;设定日志生成目录及文件名
  detecthiddentext,on                      ;显示所有窗口信息
  send ^c                                  ;将选中文字放入剪贴板
  wingettitle, d ,A                        ;获取被选中的文件名称
  wingettext, e , A                        ;获取被选中的文件信息
  stringgetpos, f, e,http                  ;若是摘录的浏览器中的网页，则查找url  
    if f>0 
    {
     stringmid, e, e, f
     }
  else
     { 
      e=local file
     }                       
  ;Msgbox %f%
  ;Msgbox %clipboard%
  fileappend, %A_YYYY%-%A_MM%-%A_DD% %A_Hour%:%A_Min%:%A_Sec%`n, %location%    
                                            ;写入摘录时间
  fileappend, %d%`n, %location%             ;写入文件名
  fileappend, %e%`n`n, %location%           ;写入url，如果有的话 
  fileappend, %clipboard%`n, %location%     ;写入摘录的文字
  fileappend, `n, %location%                                                   
  ifwinexist log.txt - 记事本               ;如果不希望日志一直打开（最小化模式），则可以将下面代码（return之前）删除
    {
       winclose
    }
  run %location%                            ;更新日志显示
  winwait, log.txt - 记事本
  winminimize,log.txt - 记事本
return