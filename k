kill -9 `ps  | grep -e "./corewar" | grep -v "grep" | cut -c-5`
