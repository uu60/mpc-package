#!/bin/zsh

hosts=("ub1" "ub2" "ub3")
cd "$(dirname $(readlink -f "$0"))"
cd ../
dir_to_upload="$PWD"
cd ../
demo_dir="$PWD/demo"

for host in "${hosts[@]}"; do
    echo "Handling $host..."
    ssh "$host" "rm -rf ~/$(basename "$dir_to_upload") ~/demo"
    scp -r "$dir_to_upload" "$host:~/" > /dev/null
    scp -r "$demo_dir" "$host:~/" > /dev/null
    nohup ssh "$host" "export PATH=/usr/local/openmpi/bin:\$PATH && export LD_LIBRARY_PATH=/usr/local/openmpi/lib:\$LD_LIBRARY_PATH && cd ~/demo && sh ../mpc-package/shell_scripts/install.sh && cmake . && make" > /dev/null 2>&1 &
done
echo "DONE"
echo "Please run 'mpirun -np 3 -hostfile ../hostfile.txt demo -case 5' on a client."