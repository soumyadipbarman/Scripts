executable=run.sh
universe=vanilla
output = $Fp(filename)cdr.$(Process).stdout
error = $Fp(filename)cdr.$(Process).stderr
log = $Fp(filename)cdr.$(Process).log
notification=never
should_transfer_files=YES
when_to_transfer_output = ON_EXIT
queue filename matching (run.sh)
