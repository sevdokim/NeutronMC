#!/bin/bash
#SBATCH --hint=nomultithread
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --mem-per-cpu=1000

job_name=${targMaterial}${targDiameter}x${targThickness}_E${initial_energy}GeV
#phys_list=QGSP_BERT_HP
project_dir=~/hyperon/neutronMCStudy/source
work_dir=~/hyperon/neutronMCStudy/simulations/$phys_list
source $project_dir/env_new.sh
if [ -z $SLURM_ARRAY_TASK_ID ]  ; then job_id=$SLURM_JOB_ID; else job_id=$SLURM_ARRAY_TASK_ID; fi

echo "Starting job $job"
mkdir -p $work_dir/${job_name}/${job_id}
cd $project_dir
cp run_g4.C g4tgeoConfig_${phys_list}.C load_g4.C $work_dir/${job_name}/${job_id}
cd $work_dir/${job_name}/${job_id}
mv g4tgeoConfig_${phys_list}.C g4tgeoConfig.C
ln -s $project_dir/macro .
root -b -q load_g4.C run_g4.C"(${NEVENTS}, ${job_id}, ${initial_energy}, ${targThickness}, ${targDiameter}, \"${targMaterial}\")" >& log
