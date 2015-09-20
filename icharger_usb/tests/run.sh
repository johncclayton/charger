#!/bin/bash
make && LD_LIBRARY_PATH=../build/lib ../build/bin/tests
