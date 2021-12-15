echo Femas LoopTime:
grep LoopTime uskernel1/bin/Syslog.log | awk '{print $11}' | awk -F = '{print $2}' | awk '$1>1000' | awk '$1<8000 ' > looptimeall.csv
cat looptimeall.csv | awk '{sum=sum+$1;count=count+1;print sum/count}' | tail -1
echo Femas InterLoopTime:
grep LoopTime uskernel1/bin/Syslog.log | awk '{print $12}' | awk -F = '{print $2}' | awk '$1>100' | awk '$1<600 ' > looptimeinter.csv
cat looptimeinter.csv | awk '{sum=sum+$1;count=count+1;print sum/count}' | tail -1
cat looptimeinter.csv | awk '{count=count+1;print count}' | tail -1
rm -rf $1.tar.gz
tar -cvf $1.tar ./looptimeall.csv ./looptimeinter.csv ./uskernel1/bin/Syslog.log
gzip $1.tar
rm -rf looptimeall.csv looptimeinter.csv
