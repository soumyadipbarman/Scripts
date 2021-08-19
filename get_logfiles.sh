# Module for downloding log files from TIFR T2 and untar it
# USAGE : ./get_logfiles.sh logfile_path output_directory_name

# Author : Soumyadip Barman
# Date : 24 Oct 2020

###############################################################

#! /bin/bash


if [[ $# -ne 2 ]]; then
    echo "Must have two arguments: get_logfiles.sh <logfile path> <output file name>"
    exit 1
fi

rfdir /dpm/indiacms.res.in/home/cms/store/user/sobarman/$1/ | grep "tar.gz"| awk '{print $9}' >> "$2".sh &&
sed -i -e 's#^#xrdcopy root://se01.indiacms.res.in//cms/store/user/sobarman/'$1'/#' "$2".sh &&
sed -i -e 's/$/ ./' "$2".sh &&
chmod 755 "$2".sh &&
./"$2".sh && 
#for file in *.tar.gz; do tar -zxf "$file"; done
for file in *.tar.gz; do tar -xavf "$file"; done

