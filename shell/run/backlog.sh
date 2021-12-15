tar -cf $1.tar ./qtrade/flow/* ./qtrade/dump/* ./qtrade/bin/Syslog.log ./qdata/bin/Syslog.log ./qmdb/bin/Syslog.log ./qquery/bin/Syslog.log
gzip $1.tar
