#!/bin/bash
#
# 文 件 名: interesting_get_os_info.sh
# 文件描述: 很有意思的脚本写法
# 作    者: HanKin
# 创建日期: 2022.12.09
# 修改日期：2022.12.09
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

cat >&2 <<EOF
$0: unable to guess system type

This script, last modified $timestamp, has failed to recognize
the operating system you are using. It is advised that you
download the most up to date version of the config scripts from

  http://git.savannah.gnu.org/gitweb/?p=config.git;a=blob_plain;f=config.guess;hb=HEAD
and
  http://git.savannah.gnu.org/gitweb/?p=config.git;a=blob_plain;f=config.sub;hb=HEAD

If the version you run ($0) is already up to date, please
send the following data and any information you think might be
pertinent to <config-patches@gnu.org> in order to provide the needed
information to handle your system.

config.guess timestamp = $timestamp

uname -m = `(uname -m) 2>/dev/null || echo unknown`
uname -r = `(uname -r) 2>/dev/null || echo unknown`
uname -s = `(uname -s) 2>/dev/null || echo unknown`
uname -v = `(uname -v) 2>/dev/null || echo unknown`

/usr/bin/uname -p = `(/usr/bin/uname -p) 2>/dev/null`
/bin/uname -X     = `(/bin/uname -X) 2>/dev/null`

hostinfo               = `(hostinfo) 2>/dev/null`
/bin/universe          = `(/bin/universe) 2>/dev/null`
/usr/bin/arch -k       = `(/usr/bin/arch -k) 2>/dev/null`
/bin/arch              = `(/bin/arch) 2>/dev/null`
/usr/bin/oslevel       = `(/usr/bin/oslevel) 2>/dev/null`
/usr/convex/getsysinfo = `(/usr/convex/getsysinfo) 2>/dev/null`

UNAME_MACHINE = ${UNAME_MACHINE}
UNAME_RELEASE = ${UNAME_RELEASE}
UNAME_SYSTEM  = ${UNAME_SYSTEM}
UNAME_VERSION = ${UNAME_VERSION}
EOF

exit 1

# Local variables:
# eval: (add-hook 'write-file-hooks 'time-stamp)
# time-stamp-start: "timestamp='"
# time-stamp-format: "%:y-%02m-%02d"
# time-stamp-end: "'"
# End: