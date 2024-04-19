#!/bin/fish
if ! test -f ./minishell; then
	make
	make clean
fi
$leak ./minishell $1