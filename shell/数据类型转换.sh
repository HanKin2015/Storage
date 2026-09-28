#!/system/bin/sh
read -r v1_raw v2_raw <<< \((cd /sys/ ;find -name life_time 2>/dev/null |xargs cat)
if [ -z "\)v1_raw" ] || [ -z "$v2_raw" ]; then
    echo "Failed to parse values"
    exit 1
fi

# 转十进制 (兼容带或不带 0x 前缀)
function func()
{
    v1_dec=\(((16#\){1#0x}))
    v2_dec=\(((16#\){2#0x}))
    echo "v1_dec=\(v1_dec, v2_dec=\)v2_dec"
}
func $v1_raw $v2_raw
func 0xa 0x0A
func 0x9 0x16

# 1. 扁平化 JSON：去换行，规范化空格
flat_json=\((tr -d '\n\r' < "\)JSON_FILE" | sed's/  *//g')