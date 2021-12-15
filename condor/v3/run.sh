#!/bin/bash
set -x
#source /cvmfs/cms.cern.ch/cmsset_default.sh
export home=/home/sobarman
#export x509_user_proxy=/home/sobarman/.globus/
cd /home/sobarman/t3store3/Generator/UNLOPS/Analysis/date_18112021/date_29112021/hadd_output/job/

root -l .x ZJets.C
