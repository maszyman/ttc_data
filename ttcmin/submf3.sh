#!/bin/bash

runss="
170593
170228
170155
170083
169965
169923
169859
169858
169855
169846
169838
169837
169835
"

runs1="
170593
170572
170312
170311
170309
"

runs2="
170308
170270
170269
170268
170230
"

runs3="
170228
170207
170204
170203
170193
"

runs4="
170155
170083
169965
169923
169859
"

runs5="
169858
169855
169846
169838
169837
169835
"

runs="
170593
170572
170312
170311
170309
170308
170270
170269
170268
170230
170228
170207
170204
170203
170193
170155
170083
169965
169923
169859
169858
169855
169846
169838
169837
169835
"

for run in $runs3 ; do

    # alien_submit anamyf3.jdl $run # do runs5 wlaczenie (error split!)
    alien_submit mymergef3.jdl $run # do runs3 wlacznie

    # alien_cp alien:///alice/cern.ch/user/m/maszyman/2012/ttc/ttcmin/output_f3/$run/output/Merged.root resultsf3/$run.root # runs2 poszlo
    # root -l -b -x -q 'listtodir.C("resultsf3/'$run'.root")';
    # rm resultsf3/$run.root

done
