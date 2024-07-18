# MPC Package
## How to use this package
### 1 OpenMPI Environment
#### 1.1 For macOS
- execute
`brew install openmpi`
#### 1.2 For Linux (Ubuntu)
- use source code to compile and install.
1. `wget https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.5.tar.gz` (use same version for devices)
2. `tar -xzvf openmpi-x.x.x.tar.gz`
3. `cd openmpi-x.x.x`
4. `./configure --prefix=/usr/local/openmpi`
5. `make`
6. `sudo make install`
7. Add the following content into environment variable configuration file like `.bashrc`
    ```shell
    export PATH=/usr/local/openmpi/bin:$PATH
    export LD_LIBRARY_PATH=/usr/local/openmpi/lib:$LD_LIBRARY_PATH
    ```
8. `source ~/.bashrc`

### 2 Install this package
1. Download the whole project
2. `cd <project root>`
3. `sh install.sh`
### 3 Import this package in your project
> **PS:** A demo project has been placed in this package project 

CMakeLists.txt should contain the following content:
```txt
find_package(mpc_package REQUIRED)

target_link_directories(demo PUBLIC ${mpc_package_LIBRARY_DIRS})
target_link_libraries(demo mpc_package)
target_include_directories(demo PUBLIC ${mpc_package_INCLUDE_DIRS})
```
which will imports the package.
### 4 Use classes
> Currently only addition share is implemented as a demo
1. Include like this `#include "./executor/arithmetic/AddictiveExecutor.h"` 
2. `AddictiveExecutor` is an abstract class but only method `setXA` and `setYA` needs implementing, which is used to describe how current device gets its own data to be calculated later as a parameter.
3. `result` method is for getting the calculated result. `finalize` can be defined with some other process to be executed before the result returned.
### 5 Execute
1. Use the same username of Linux/macOS.
2. Set up non-password login between 2 machines. Using `ssh-keygen` and `ssh-copy-id`.
3. Place the executable file on the same path of 2 machines.
4. Edit a **hostfile.txt**, which records IP addresses of the 2 machines. (Or use host name by editing **/etc/hosts**) Write slot number for each machine.
   <br>(The format of host file can be referred in **hostfile.txt** in this project)
5. To distinguish executing machine, edit their hostnames by executing `sudo hostnamectl set-hostname ub1`. **ub1** is the new host name.
6. Your project should be complied by **CMake** instead of `mpicxx`. 
7. Then use `mpirun` to execute it. Here is an example shell:
    ```shell
    mpirun -np 2 -hostfile hostfile.txt a.out
    ```