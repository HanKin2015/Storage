cat /sys/class/net/eth0/address | awk '{
                  n=split($0,a,":");
                  sum = 0;
                  tmp = 0;
                  count = 0;
          for(i = 1;i<=n;i++)
          {
                           tmp = strtonum("0x"a[i]);
                           count = (tmp/16)>0 ? count:(count + 1);
                           count = (tmp%16)>0 ? count:(count + 1);
               sum += (tmp%10)*(10**(6-i));
          }
                  count = count<1?9:count;
                  count = count>9?9:count;
                  sum  += count*(10**6);
          printf("HEJIAN%7d", sum);
        }'



root@hankin:/usr/local/bin# SERIAL_NUM=$(printf "HEJIAN%d" "0x$(cat /sys/class/net/eth0/address | tr -d ':
root@hankin:/usr/local/bin# echo $SERIAL_NUM
HEJIAN225207121345651
root@hankin:/usr/local/bin# echo ${SERIAL_NUM:0:10}
HEJIAN2252

