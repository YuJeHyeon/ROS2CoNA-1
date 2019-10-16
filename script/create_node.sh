#!/bin/bash

workspace=ROS2CoNA

cd 
echo -e "Please input node(package) name: \c "
read node 
tput setaf 1
echo "======================="
echo "$node node location is ~/${workspace}/src/$node/"
echo "======================="
tput sgr0
cd ~/${workspace}/src/
catkin_create_pkg $node std_msgs roscpp
echo "source ~/${workspace}/devel/setup.bash" >> ~/.bashrc

cd ~/${workspace}/src/$node/src/
cp ~/${workspace}/templete/templete.cpp ./
cp ~/${workspace}/templete/CMakeLists.txt ../ 
cp ~/${workspace}/templete/package.xml ../ 
mv templete.cpp $node.cpp
cd ~/${workspace} 

tput setaf 2
echo "======================="
echo "$node package is created. Please change few word in CMakeLists.txt and package.xml.."
echo "======================="
tput sgr0

source ~/.bashrc
