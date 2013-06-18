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

for run in $runs1 ; do
    alien_submit anamy.jdl $run
#    alien_cp alien:///alice/cern.ch/user/m/maszyman/2012/QvectorTest/results/$run/output/Merged.root results/$run.root
done
