rm chkconfig.tmp
cd ../../bin
./mcall chkconfig > /cffex/trade/mctrl/script/chkconfig.tmp
./mcall chksys >> /cffex/trade/mctrl/script/chkconfig.tmp
cd ../binmd
./mcall.md chkconfig >> /cffex/trade/mctrl/script/chkconfig.tmp
cd ../mctrl/script
ls -la chkconfig.static
ls -la chkconfig.tmp
diff chkconfig.static chkconfig.tmp
