#!/bin/bash
#
# Copyright 2013 Mantas Norvaiša
# 
# This file is part of wb.
# 
# wb is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# wb is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with wb.  If not, see <http://www.gnu.org/licenses/>.
#

echo
echo "======================="
echo "Running tests:"
echo "======================="

FAILED=0
TESTS=$#

for testfile in "$@"; do
	echo
	echo "-----------------------"
	echo $testfile
	echo "-----------------------"
	./$testfile

	if [ "$?" == "1" ]; then
		FAILED=$(($FAILED + 1))
	fi
done

echo
echo "======================="
echo "$TESTS Test files $FAILED Failures"
echo "======================="
echo

if [ "$FAILED" != "0" ]; then
	exit 1
fi