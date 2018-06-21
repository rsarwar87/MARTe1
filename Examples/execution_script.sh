#############################################################
#
# Copyright 2011 EFDA | European Fusion Development Agreement
#
# Licensed under the EUPL, Version 1.1 or - as soon they 
# will be approved by the European Commission - subsequent  
# versions of the EUPL (the "Licence"); 
# You may not use this work except in compliance with the 
# Licence. 
# You may obtain a copy of the Licence at: 
#  
# http://ec.europa.eu/idabc/eupl
#
# Unless required by applicable law or agreed to in 
# writing, software distributed under the Licence is 
# distributed on an "AS IS" basis, 
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either 
# express or implied. 
# See the Licence for the specific language governing 
# permissions and limitations under the Licence. 
#
# $Id$
#
#############################################################
#Start-up script for the MARTe WaterTank example
#!/bin/sh 

args=("$@")
BUILD_DIRECTORY=${args[0]}
configFile=${args[1]}
nargs=$#

if [ $nargs -gt 2 ]; then
		echo "Invalid number of arguments ["$nargs"]. Usage: compile.MARTe <build directory> <configFile>"	
		exit
	fi


target=`uname`
case ${target} in
    Darwin)
    TARGET=macosx
    ;;
    SunOS)
    TARGET=solaris
    ;;
    *)
    TARGET=linux
    ;;
esac

echo "Target is $TARGET"

LD_LIBRARY_PATH=.

myls() {
    for item in "$1"/* "$1"/.*; do
        [ -z "${item##*/.}" -o -z "${item##*/..}" -o -z "${item##*/\*}" ] && continue
        if [ -d "$item" ]; then
            LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$item/
            myls "$item"
        fi    
    done
}
myls $BUILD_DIRECTORY


echo $LD_LIBRARY_PATH

$BUILD_DIRECTORY/MARTe/MARTe.ex $configFile

