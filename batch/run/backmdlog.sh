tar -cf $1.tar ./qmarket_tcp/flow/* ./qmarket_tcp/bin/Syslog.log ./qmarket_tcp/bin/*.csv
gzip $1.tar
