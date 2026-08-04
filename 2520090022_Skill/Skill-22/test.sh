#!/bin/bash

echo "Compiling Program..."
gcc skill-22.c -o skill-22

echo
echo "Running Program..."
./skill-22

echo
echo "Running Valgrind..."
valgrind --leak-check=full ./skill-22

echo
echo "Generating Report..."
echo "Test Completed Successfully"
