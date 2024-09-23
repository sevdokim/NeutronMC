#!/bin/bash
job_name=W10x25_H2C20x35
job_prefix=${job_name}_25K
NEVENTS=25000

for job in {1..4}
do
    echo "Starting job $job"
    mkdir -p ${job_prefix}_${job}
    cd ${job_prefix}_$job
    cp ../g4tgeoConfig.C g4tgeoConfig.C
    cp ../load_g4.C .
    cp ../run_g4_${job_name}.C run_g4.C
    nohup root -b -q ../runSim.C"(${NEVENTS}, ${job})" >& log &
    cd ..
done
