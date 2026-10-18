#!/bin/bash
unset XDG_DATA_DIRS
cmake --build build/
exec ./build/black-hole