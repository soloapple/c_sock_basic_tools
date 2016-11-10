# autobuilder.sh
#!/bin/sh

run ()
{
	$@
		if test $? -ne 0;then
			echo "Failed: $@"
				exit 1
				fi
}

tomake ()
{
	echo " ======>start make!"
	sleep 1.1
		make
}


run aclocal -I m4
run libtoolize --copy --force
run autoheader
run automake --add-missing --foreign --copy
run autoconf
cp /usr/bin/libtool .

tomake
