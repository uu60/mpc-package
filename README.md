# MPC Package
## How to use this package
### 1 OpenMPI Environment
- For macOS, execute `brew install openmpi`
- For Linux (Ubuntu), use source code to compile and install.
  <br>According to https://blog.csdn.net/qq_43259903/article/details/131805431
  <br>If some dependencies are missing during installation, try using apt to install.
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
1. Include like this `#include "./executor/arithmetic/AbstractAdditionShareExecutor.h"` 
2. `AbstractAdditionShareExecutor` is an abstract class but only method `obtainX` needs implementing, which is used to describe how current device gets its own data to be calculated later as a parameter.
3. `result` method is for getting the calculated result. `customFinalize` can be defined with some other process to be executed before the result returned.
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