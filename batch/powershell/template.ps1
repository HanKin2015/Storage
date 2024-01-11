# 1、注释
# 这是单行注释
<#
这是
多行注释
#>

# 2、变量，区分大小写
$variable = "Hello, World!"
$Variable = "Hello, Powershell!"

# 3、数据类型
[int]$number = 20
[string]$text = "Some text"
[bool]$flag = $true

# 4、运算符
$sum = 5 + 5
$isEqual = $sum -eq 10

# 5、条件语句
if ($variable -eq "Hello, World!") {
    Write-Host "The variable says Hello!"
} elseif ($variable -eq "Goodbye") {
    Write-Host "The variable says Goodbye!"
} else {
    Write-Host "The variable says something else."
}

# 6、循环
foreach ($item in $collection) {
    Write-Host $item
}

for ($i = 0; $i -lt 10; $i++) {
    Write-Host $i
}

$j = 0
while ($j -lt 10) {
    Write-Host $j
    $j++
}

# 7、函数
function Get-MultipliedValue($value, $multiplier) {
    return $value * $multiplier
}

$result = Get-MultipliedValue -value 10 -multiplier 5
Write-Host $result

# 8、错误处理
try {
    # 尝试执行的代码
    $result = 1 / 0
} catch {
    # 发生错误时执行的代码
    Write-Host "An error occurred: $_"
} finally {
    # 无论是否发生错误都会执行的代码
    Write-Host "Cleaning up..."
}

# 9、模块和脚本导入
Import-Module -Name MyCustomModule
. .\AnotherScript.ps1

# 10、输出
Write-Host "This is a message to the host/console."
Write-Output "This is a message to the host/console."
Write-Error "This is a message to the host/console."



