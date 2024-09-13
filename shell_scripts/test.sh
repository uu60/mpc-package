#!/bin/zsh

hosts=("ub1" "ub2" "ub3")
cd "$(dirname $(readlink -f "$0"))"
cd ../
dir_to_upload="$PWD"
cd ../
demo_dir="$PWD/demo"

for host in "${hosts[@]}"; do
    if [ "$host" = "${hosts[${#hosts[@]} - 1]}" ]; then
      ssh "$host" "rm -rf ~/$(basename "$dir_to_upload") ~/demo"
      scp -r "$dir_to_upload" "$host:~/"
      scp -r "$demo_dir" "$host:~/"
      ssh "$host" "export PATH=/usr/local/openmpi/bin:\$PATH && export LD_LIBRARY_PATH=/usr/local/openmpi/lib:\$LD_LIBRARY_PATH && cd ~/demo && sh ../mpc-package/shell_scripts/install.sh && cmake . && make"
    else
      nohup bash -c "
        ssh '$host' 'rm -rf ~/$(basename "$dir_to_upload") ~/demo' > /dev/null 2>&1 &&
        scp -r '$dir_to_upload' '$host:~/' > /dev/null 2>&1 &&
        scp -r '$demo_dir' '$host:~/' > /dev/null 2>&1 &&
        ssh -n '$host' 'nohup bash -c \"
          export PATH=/usr/local/openmpi/bin:\$PATH &&
          export LD_LIBRARY_PATH=/usr/local/openmpi/lib:\$LD_LIBRARY_PATH &&
          cd ~/demo &&
          sh ../mpc-package/shell_scripts/install.sh &&
          cmake . &&
          make
        \" > /dev/null 2>&1 &' > /dev/null 2>&1
      " > /dev/null 2>&1 &
    fi
done
echo "DONE"
echo "Please run 'mpirun -np 3 -hostfile ../hostfile.txt demo -case 5' on a client."