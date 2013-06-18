#!/bin/bash


runs1="
168464
169591
169588
169557
169550
"

runs2="
169512
169504
169498
169475
169419
"

runs3="
169417
169415
169411
169238
169160
"
runs4="
169156
169144
169035
168826
168512
"

runs5="
168511
168464
168458
168361
167988
"

runs6="
167987
167920
167915
"

runs="
168464
169591
169588
169557
169550
169512
169504
169498
169475
169419
169417
169415
169411
169238
169160
169156
169144
169035
168826
168512
168511
168464
168458
168361
167988
167987
167920
167915
"

for run in $runs ; do
    #alien_submit anamyf1.jdl $run # do runs6
     # alien_submit mymergef1.jdl $run # do runs6 wlacznie

    alien_cp alien:///alice/cern.ch/user/m/maszyman/2012/ttc/ttc16dca24/output_f1/$run/output/Merged.root resultsf1/$run.root # runs2 poszlo
    root -l -b -x -q 'listtodir.C("resultsf1/'$run'.root")';
    rm resultsf1/$run.root


done
