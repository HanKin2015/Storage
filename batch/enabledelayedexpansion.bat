::
:: �� �� ��: enabledelayedexpansion.bat
:: �ļ�����: �����ӳٱ�����չ�����ҽ��������������ڽű���ű���һ������
:: ��    ע: �����ӳٱ�����չ�������ͨ��ʹ�� ! ������ % �����ñ��������� !variable!���������Ϳ��Ի�ȡ�������ڴ����ִ�й����е�ʵʱֵ
:: ��    ��: HanKin
:: ��������: 2024.08.28
:: �޸����ڣ�2024.08.28
:: 
:: Copyright (c) 2024 HanKin. All rights reserved.
::

@echo off
setlocal enabledelayedexpansion

set "count=0"

:: ������û��enabledelayedexpansion���Ʒ�%cout%�������0����!count!�����֮�Ƿ���Ч
for /l %%i in (1,1,5) do (
    set /a count+=1
    echo Without delayed expansion: %count%
    echo With delayed expansion: !count!
)

endlocal
pause