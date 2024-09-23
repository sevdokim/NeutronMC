#!/bin/bash
#SBATCH --array=0-9
#SBATCH --hint=nomultithread
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --mem-per-cpu=1000
#SBATCH -o /home/evdokimov/hyperon/neutronMCStudy/simulations/W10x25_Be2C30x45-%A_%a.out

job_name=W10x25_Be2C30x45
NEVENTS=10000
phys_list=ShieldingLEND
#phys_list=QGSP_BERT_HP
project_dir=~/hyperon/neutronMCStudy/source
work_dir=~/hyperon/neutronMCStudy/simulations/$phys_list
source $project_dir/env.sh
if [ -z $SLURM_ARRAY_TASK_ID ]  ; then job_id=$SLURM_JOB_ID; else job_id=$SLURM_ARRAY_TASK_ID; fi

echo "Starting job $job"
mkdir -p $work_dir/${job_name}/${job_id}
cd $project_dir
cp run_g4_${job_name}.C g4tgeoConfig_${phys_list}.C load_g4.C $work_dir/${job_name}/${job_id}
cd $work_dir/${job_name}/${job_id}
mv run_g4_${job_name}.C run_g4.C
mv g4tgeoConfig_${phys_list}.C g4tgeoConfig.C
ln -s ~/hyperon/neutronMCStudy/source/macro .
root -b -q load_g4.C run_g4.C"(${NEVENTS}, ${job_id})" >& log
