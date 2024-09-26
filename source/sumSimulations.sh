if [ -z $1 ]; then
    search_pattern=*
else
    search_pattern=*$1*
fi

wd=$(pwd)
sim_dir=/home/evdokimov/hyperon/neutronMCStudy/simulations

#phys_lists="ShieldingLEND Shielding QGSP_BERT_HP"
phys_lists="ShieldingLEND"
#phys_lists="QGSP_BERT_HP"

if ! cd $sim_dir ; then
    echo $sim_dir "does not exist. exiting!"
    return 1
fi
    
for phys_list in $phys_lists
do
    for dirs in $(ls $phys_list/$search_pattern/ -d)
    do
	prod=$(echo $dirs | awk -F/ '{ print $2 }')
	ls $sim_dir/$phys_list/$prod/*/histos.root > $phys_list/$prod/histos.list
	cd $wd
	./addhisto.sh $sim_dir/$phys_list/$prod/histos.list $sim_dir/$phys_list/$prod/histos.root
	cp $sim_dir/$phys_list/$prod/histos.root ${phys_list}_${prod}.root
    root -b -q drawHistos.C\(\"${phys_list}_${prod}.root\"\)
	cd -
    done
done
cd $wd
