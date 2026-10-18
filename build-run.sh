#!/bin/bash
unset XDG_DATA_DIRS
cmake --build build/
echo "Running engine ... "
exec ./build/black-hole