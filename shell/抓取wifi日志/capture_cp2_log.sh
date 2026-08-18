#!/system/bin/sh

# 不用修改脚本中的echo，这样也是一种创建日志文件的方法
#nohup /data/log_monitor.sh > /data/log_monitor.out 2>&1 &

# 配置参数
LOG_FILE="/data/cp2.log"
COMPRESSED_LOG="/data/cp2.log.gz"
KERNEL_LOG="/data/kernel.log"
MAX_SIZE_MB=300
MAX_SIZE_BYTES=$((MAX_SIZE_MB * 1024 * 1024))
SLOG_DEVICE="/dev/slog_wcn0"
CAT_PROCESS_NAME="cat /dev/slog_wcn0"
ASSERT_KEYWORD="sprdwl_atcmd_assert"

# 函数：获取文件大小（字节）
get_file_size() {
    if [ -f "$1" ]; then
        stat -c %s "$1" 2>/dev/null || ls -l "$1" | awk '{print $5}'
    else
        echo "0"
    fi
}

# 函数：压缩日志文件
compress_log() {
    local src_file="$1"
    local dst_file="$2"
    
    if [ -f "$src_file" ]; then
        echo "[$(date)] 开始压缩日志文件: $src_file -> $dst_file"
        
        # 使用gzip压缩，-f强制覆盖已存在的压缩文件
        gzip -c -f "$src_file" > "$dst_file"
        
        if [ $? -eq 0 ]; then
            # 压缩成功后，清空原日志文件（而不是删除，保持文件句柄有效）
            stop_log_capture
            > "$src_file"
            echo "[$(date)] 压缩成功，原日志文件已清空"
            start_log_capture
            
            # 显示压缩后的大小
            local compressed_size=$(get_file_size "$dst_file")
            local compressed_size_mb=$((compressed_size / 1024 / 1024))
            echo "[$(date)] 压缩后大小: ${compressed_size_mb}MB"
        else
            echo "[$(date)] 压缩失败！"
            return 1
        fi
    fi
}

# 函数：检查内核日志中是否包含特定关键词
check_kernel_assert() {
    # 尝试从不同的内核日志源读取，这种方式太费时间
    #local kernel_sources="/proc/last_kmsg /proc/console /dev/kmsg"
    #for src in $kernel_sources; do
    #    if [ -r "$src" ]; then
    #        if grep -q "$ASSERT_KEYWORD" "$src" 2>/dev/null; then
    #            return 0  # 找到关键词
    #        fi
    #    fi
    #done
    
    # 如果上述都不可读，尝试使用dmesg
    if command -v dmesg >/dev/null 2>&1; then
        if dmesg | grep -q "$ASSERT_KEYWORD"; then
            return 0
        fi
    fi
    
    return 1  # 未找到关键词
}

# 函数：保存内核日志
save_kernel_log() {
    echo "[$(date)] 检测到内核assert，开始保存内核日志..."
    
    # 尝试多种方式保存内核日志
    if [ -r "/proc/last_kmsg" ]; then
        cp /proc/last_kmsg "$KERNEL_LOG"
        echo "[$(date)] 已从/proc/last_kmsg保存内核日志到 $KERNEL_LOG"
    elif command -v dmesg >/dev/null 2>&1; then
        dmesg -T > "$KERNEL_LOG"
        echo "[$(date)] 已通过dmesg保存内核日志到 $KERNEL_LOG"
    elif [ -r "/dev/kmsg" ]; then
        # 注意：直接读取/dev/kmsg可能需要特殊权限且会消耗消息
        cat /dev/kmsg > "$KERNEL_LOG" 2>&1 &
        sleep 2
        kill $! 2>/dev/null
        echo "[$(date)] 已从/dev/kmsg保存内核日志到 $KERNEL_LOG"
    else
        echo "[$(date)] 警告：无法访问内核日志源"
        # 至少尝试保存当前dmesg输出
        dmesg 2>/dev/null > "$KERNEL_LOG" || echo "[$(date)] 完全无法保存内核日志"
    fi
    
    # 设置合适的权限
    chmod 644 "$KERNEL_LOG" 2>/dev/null
}

# 函数：停止日志抓取进程
stop_log_capture() {
    echo "[$(date)] 停止日志抓取进程..."
    
    # 查找并杀死cat /dev/slog_wcn0进程
    local pid=$(ps -ef | grep "[c]at /dev/slog_wcn0" | awk '{print $2}')
    
    if [ -n "$pid" ]; then
        kill -9 "$pid"
        echo "[$(date)] 已杀死进程 PID: $pid"
        
        # 等待一下确保进程已终止
        sleep 1
        
        # 再次检查是否还有残留进程
        if ps -ef | grep -q "[c]at /dev/slog_wcn0"; then
            echo "[$(date)] 警告：仍有残留进程，尝试再次杀死"
            pkill -9 -f "cat /dev/slog_wcn0" 2>/dev/null
        fi
    else
        echo "[$(date)] 未找到cat /dev/slog_wcn0进程"
    fi
}

start_log_capture() {
    echo "[$(date)] 开始日志抓取进程..."
    echo "debug_level=2" >/sys/kernel/debug/sprdwl_debug/log_level
    echo -e "at+armlog=1\r" >/proc/mdbg/at_cmd
    cat /dev/slog_wcn0 > "$LOG_FILE" &
}

# 主循环
echo "[$(date)] 启动日志监控脚本"
echo "[$(date)] 监控文件: $LOG_FILE"
echo "[$(date)] 最大文件大小: ${MAX_SIZE_MB}MB"
echo "[$(date)] 压缩文件: $COMPRESSED_LOG"
echo "[$(date)] 内核日志保存位置: $KERNEL_LOG"
echo "[$(date)] 检测关键词: $ASSERT_KEYWORD"
echo ""

# 确保日志文件存在
if [ ! -f "$LOG_FILE" ]; then
    setprop persist.capture.cp2.log 1
    touch "$LOG_FILE"
fi

# 是否继续抓取日志
if [ "$(getprop persist.capture.cp2.log)" = "0" ]; then
    echo "[$(date)] 检测到内核assert不再继续抓取日志"
    exit 0
fi

# 脚本执行唯一
pid=$(ps -ef | grep "$0" | grep -v grep | awk '{print $2}')
if [ -n "$pid" ]; then
    kill -9 "$pid"
fi

# 抓取cp2日志
echo "[$(date)] exec script[$0] uid[$(id -u)]" > /dev/kmsg
start_log_capture

while true; do
    # 检查当前日志文件大小
    current_size=$(get_file_size "$LOG_FILE")
    current_size_mb=$((current_size / 1024 / 1024))
    
    # 显示当前状态
    echo "[$(date)] 当前日志大小: ${current_size_mb}MB (阈值: ${MAX_SIZE_MB}MB)"
    
    # 检查是否超过大小限制
    if [ "$current_size" -ge "$MAX_SIZE_BYTES" ]; then
        echo "[$(date)] 日志文件超过${MAX_SIZE_MB}MB，开始压缩转存..."
        compress_log "$LOG_FILE" "$COMPRESSED_LOG"
        
        if [ $? -ne 0 ]; then
            echo "[$(date)] 压缩失败，等待10秒后重试..."
            sleep 10
        fi
    fi
    
    # 检查内核中是否包含assert关键词
    if check_kernel_assert; then
        echo "[$(date)] *** 检测到内核assert关键词: $ASSERT_KEYWORD ***"
        
        # 保存内核日志
        save_kernel_log
        
        # 停止日志抓取进程
        stop_log_capture
        
        # 设置停止日志抓取属性
        setprop persist.capture.cp2.log 0
        
        echo "[$(date)] 已完成assert处理，退出监控循环"
        break
    fi
    
    # 等待一段时间后再次检查（避免过于频繁的检查）
    sleep 30
done

echo "[$(date)] 日志监控脚本结束"

#!/system/bin/sh

echo "hejian exec script" > /dev/kmsg
# 获取当前用户的UID
current_uid=$(id -u)

if [ "$current_uid" -eq 0 ]; then
    echo "当前用户是 root (UID: $current_uid)"
    # 在这里执行需要root权限的操作
else
    echo "当前用户是普通用户 (UID: $current_uid)，用户名: $(whoami)"
    # 在这里执行普通用户操作或提示错误
    # exit 1  # 如果脚本必须用root运行，可以在此退出
fi


    
