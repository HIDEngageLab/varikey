#!/bin/bash

pushd ..
workspace=`pwd`

# clean up

rm -f ${workspace}/bin/CMakeCache.txt
rm -Rf ${workspace}/bin/CMakeFiles

# configure
cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -H${workspace} -B${workspace}/bin -G "Unix Makefiles"

# clean
cmake --build ${workspace}/bin --config Debug --target clean -j 6

# build all
cmake --build ${workspace}/bin --config Debug --target all -j 6

popd
