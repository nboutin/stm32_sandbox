#!/bin/bash

# On error, exit immediately
set -e

source env_arm_gnu.sh

cmake --build build/MinSizeRel

cmake --install build/MinSizeRel --prefix .
