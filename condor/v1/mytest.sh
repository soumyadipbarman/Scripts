#!/bin/sh
echo "Hello from `hostname`"
echo "Going to source the file $OSG_GRID/setup.sh"
source $OSG_GRID/setup.sh
echo "Resulting environment:"
printenv
echo "Output of lcg-cp --help (lcg-cp is a commonly used SRM client):"
lcg-cp --help
echo 'Directories in \$OSG_APP'
ls $OSG_APP
date
sleep 120
date
