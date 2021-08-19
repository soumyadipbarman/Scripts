# Module for downloding root files from TIFR T2
# USAGE : ./get_rootfiles.sh rootfile_path output_directory_name

# Author : Soumyadip Barman
# Date : 24 Oct 2020

################################################################

#! /bin/bash

if [[ $# -ne 2 ]]; then
    echo "Must have two arguments: get_rootfiles.sh <rootfile path> <output file name>"
    exit 1
fi

rfdir /dpm/indiacms.res.in/home/cms/store/user/sobarman/$1/ | grep "root"| awk '{print $9}' >> "$2".sh &&
sed -i -e 's#^#xrdcopy root://se01.indiacms.res.in//cms/store/user/sobarman/'$1'/#' "$2".sh &&
sed -i -e 's/$/ ./' "$2".sh &&
chmod 755 "$2".sh &&
./"$2".sh

