#!/bin/bash
set -x
source /cvmfs/cms.cern.ch/cmsset_default.sh
export home=/home/sobarman
export x509_user_proxy=/home/sobarman/.globus/
cd /home/sobarman/t3store3/Generator/UNLOPS/Analysis/date_30042022/py8306/condor/

hadd -fk dyeej_2NLO3LO_5f_NLO_UNLOPS_py8306_30042022.root /home/sobarman/t3store3/Generator/UNLOPS/Analysis/date_30042022/py8306/root_files/*.root

#python /home/sobarman/t3store3/Scripts/haddnano.py dyeej_2NLO3LO_5f_NLO_UNLOPS_NanoAOD_29112021.root /home/sobarman/t3store3/Generator/UNLOPS/Analysis/date_18112021/date_29112021/root_files/*.root 
