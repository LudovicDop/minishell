#!/bin/bash

# Ensure the script exits if any command fails
set -e

# Define the first program and suppression file
PROGRAM1="/home/alphan/Documents/minishell_merge/./minishell"
SUPPRESSION_FILE1="/home/alphan/Documents/minishell_merge/ignore_readline.supp"

# Define the second program and suppression file
PROGRAM2="/home/ldoppler/Desktop/minishell_merge/./minishell"
SUPPRESSION_FILE2="/home/ldoppler/Desktop/minishell_merge/ignore_readline.supp"

# Function to run Valgrind with the specified program and suppression file
run_valgrind() {
  local program=$1
  local suppression_file=$2
  valgrind --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s --trace-children=yes --suppressions="$suppression_file" "$program"
}

# Try to run Valgrind with the first program and suppression file
if ! run_valgrind "$PROGRAM1" "$SUPPRESSION_FILE1"; then
  echo "First attempt failed. Trying with the second program and suppression file..."
  run_valgrind "$PROGRAM2" "$SUPPRESSION_FILE2"
fi
