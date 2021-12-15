cp ../sourceapp/qtrade/*/lib*.so ./qtrade/
cp ../sourceapp/qtrade/*/lib*.so ./qtrade/bin/

cp ../sourceapp/qtrade/*/lib*.so ./qquery/
cp ../sourceapp/qtrade/*/lib*.so ./qquery/bin/
cp ../sourceapp/qquery/*/lib*.so ./qquery/
cp ../sourceapp/qquery/*/lib*.so ./qquery/bin/

cp ../sourcebase/db/sqlapiso/lib*.so ./qdata/
cp ../sourcebase/db/sqlapiso/lib*.so ./qdata/bin/
cp ../sourcebase/db/sqlapiso/lib*.so ./qquery/
cp ../sourcebase/db/sqlapiso/lib*.so ./qquery/bin/

cp ./qdataup/qdataup ./qdata/
cp ./qdataup/qdataup ./qdata/bin/
cp ../datamodel/envGenerated/dbmt.cmd qdata/
cp ../datamodel/envGenerated/dbmt.cmd qdata/bin/

cp ./qdata/bin/lib*.so ./qdata/
cp ./qquery/bin/lib*.so ./qquery/

tarstr=''
tarinistr=''
for project in qtrade qdata qquery qfixfront
do
	cp $project/bin/$project ./$project/
	cp $project/bin/$project.ini ./$project/
	tarstr+=' '
	tarstr+=` echo  $project/$project $project/lib*.so `
	tarinistr+=' '
	tarinistr+=` echo  $project/$project.ini `
	if [[ $project == 'qfixfront' ]]; then
		tarinistr+=' '
		cp $project/bin/FIX42.xml ./$project/
		tarinistr+=` echo  $project/FIX42.xml `
	fi

done

tarstr+=` echo ' ' qdata/qdataup ' ' qdata/dbmt.cmd `

echo $tarstr
tar -cvf run.tar $tarstr
gzip run.tar
echo $tarinistr
tar -cvf ini.tar $tarinistr
gzip ini.tar

tarstr=''
cd ../tools
for project in dumptool testapi tload slogparser
do
        tarstr+=' '
        tarstr+=` echo  $project/$project $project/$project.ini `
done

tarstr+=` echo ' ' flowviewer/flowviewer`

tarstr+=` echo ' ' testapi/Order.csv ' '  tload/readme.txt ' '  tload/test.in ' ' slogparser/slogparser`
echo $tarstr
tar -cvf tools.tar $tarstr
gzip tools.tar
