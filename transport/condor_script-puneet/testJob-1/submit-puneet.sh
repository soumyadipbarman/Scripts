executable=run.sh
universe=vanilla
arguments=Example.$(Cluster).$(Process) 100
error=results.error.$(Process)
log=results.log.$(Process)
notification=never
should_transfer_files=YES
when_to_transfer_output = ON_EXIT
queue

