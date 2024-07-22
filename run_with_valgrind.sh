#!/bin/bash

# Ensure the script exits if any command fails
set -e

# Define the program to run
# PROGRAM="/home/alphan/Documents/minishell_merge/./minishell"
PROGRAM="/home/ldoppler/Desktop/minishell_merge/./minishell"

# Define the suppression file
# SUPPRESSION_FILE="/home/alphan/Documents/minishell_merge/ignore_readline.supp"
SUPPRESSION_FILE="/home/ldoppler/Desktop/minishell_merge/ignore_readline.supp"

# Run Valgrind with the specified suppression file
valgrind --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s --trace-children=yes --suppressions=$SUPPRESSION_FILE $PROGRAM
