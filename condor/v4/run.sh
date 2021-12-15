#!/bin/bash
set -x
source /cvmfs/cms.cern.ch/cmsset_default.sh
export home=/home/sobarman
export x509_user_proxy=/home/sobarman/.globus/
cd /home/sobarman/t3store3/Generator/UNLOPS/Analysis/date_18112021/date_29112021/hadd_output/

python /home/sobarman/t3store3/Scripts/haddnano.py dyeej_2NLO3LO_5f_NLO_UNLOPS_NanoAOD_29112021.root /home/sobarman/t3store3/Generator/UNLOPS/Analysis/date_18112021/date_29112021/root_files/*.root 
