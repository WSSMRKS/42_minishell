#!/bin/bash

# Run valgrind with empty input (Ctrl+D)
(echo -n "" | valgrind --leak-check=full --show-leak-kinds=all --gen-suppressions=all --log-file=memcheck.log ./minishell) 2>/dev/null

# Process the suppressions and add simple numbered names, skip placeholder lines
awk '
BEGIN { count = 1 }
/^{/ {
    print "{"
    printf "   %d\n", count++    # Removed "name="
    next
}
/<insert_a_suppression_name_here>/ { next }
{ print }' memcheck.log | awk '/^{/,/^}/' > suppressions.supp

# Clean up
rm memcheck.log
