export targDiameter=50
export targThickness=100
export phys_list=Shielding
export NEVENTS=1000

export targMaterial
export initial_energy

for targMaterial in 232Thorium Wolfram
do
    for initial_energy in 2 3.5 4 #8 16 32 64 128
    #for initial_energy in 256 512 1024
    #for initial_energy in 400 800
    do
	job_name=${targMaterial}${targDiameter}x${targThickness}_E${initial_energy}GeV
	sbatch submit.sh -o "/home/evdokimov/hyperon/neutronMCStudy/simulations/${phys_list}/${job_name}/${job_name}-%j.out"
    done
done
	
