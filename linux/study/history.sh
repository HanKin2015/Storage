#export HISTSIZE=
#export HISTFILESIZE=
USER_IP=`who -u am i 2>/dev/null| awk '{print $NF}'|sed -e 's/[()]//g'`
export HISTORY_FILE=$LROOT/log/today/audit_log/${LOGNAME}/$(date +%Y%m%d%H%M)_${USER_IP}.log
dir=`dirname $HISTORY_FILE`
if [ ! -d "$dir" ]
then
mkdir -p $dir
chmod 300 $dir
fi
> /${LOGNAME}/.bash_history
export PROMPT_COMMAND='HISTTIMEFORMAT="[%F %T] " history 1 >> $HISTORY_FILE'
