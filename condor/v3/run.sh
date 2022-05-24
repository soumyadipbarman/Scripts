#!/bin/bash
set -x
#source /cvmfs/cms.cern.ch/cmsset_default.sh
export home=/home/sobarman
#export x509_user_proxy=/home/sobarman/.globus/
cd /home/sobarman/t3store3/Generator/UNLOPS/Analysis/date_30042022/py8306/

root -l .x ZJets.C
#root -l .x ZJets_nw.C
