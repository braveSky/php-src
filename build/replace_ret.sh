#!/bin/sh

infile=$1
shift
doit=$1
shift
awk=$1
shift

if test -z "$infile" ; then
	echo "please supply infile"
	exit 1
fi

if test $doit != "yes" ; then
	exit 0
fi

cat $infile | $awk '
BEGIN {
	in_func=0
	IGNORECASE=0
}
{
	if ($0 ~ /\.type.+@function/) {
		if ($2 ~ /ZEND_[A-Z_]+_HANDLER/) {
			if ($2 ~ /(YIELD|CALL_TRAMPOLINE|GENERATOR_RETURN|FAST_RET|HANDLE_EXCEPTION|USER_OPCODE)/) {
				/* these handler may contains ZEND_VM_RETURN */
				in_func = 0
			} else {
				in_func = 1
			}
		} else if ($2 ~ /_helper_[A-Z_]+/) {
			if ($2 ~ /leave/) {
				in_func = 0
			} else {
				in_func = 1
			}
		} else {
			in_func = 0
		}
	}

	if (in_func && $0 ~ /ret$/) {
		print "\tjmp\t*(%r15)"
		next
	}

	print $0;
}' > "${infile}.tmp"

mv "${infile}.tmp" $infile
