rm chkconfig.tmp
localpath=`pwd`
cd ../../bin
./mcall chkini > $localpath/chkconfig.tmp
#cd ../binmd
#./mcall.md chkconfig >> /cffex/trade/mctrl/script/chkconfig.tmp
cd ../mctrl/script
ls -la chkconfig.static
ls -la chkconfig.tmp
diff chkconfig.static chkconfig.tmp
