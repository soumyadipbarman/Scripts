#!/bin/bash
set -x
source /cvmfs/cms.cern.ch/cmsset_default.sh
export home=/home/sobarman
export x509_user_proxy=/home/sobarman/.globus/
cd /home/sobarman/t3store3/JetCharge/Observables/date_16012022_test/output/

hadd Test_Data_2017UL_16012022_testrun_v2-puneet.root /home/sobarman/t3store3/JetCharge/Observables/date_16012022_test/root_files/*.root 
