# Minishell

## Overview
`minishell` is a simple shell program designed to simulate the functionality of a standard shell. Created by Martín Sotelo Aguirre on October 11, 2023, the program is written in C and demonstrates basic shell functionalities like command execution, input/output redirection, and pipe handling.

## Version
1.0.0

## Features
- **Command execution**
- **Input/output redirection** using `>` and `>>`
- **Pipe handling** with `|`
- **Line, word, and character counting** with `<`
- **Error management**

## Usage
To use `minishell`, compile the source file `minishell.c` and run the executable. The shell prompts for user input with `minishell\>`. Enter your command and press enter to execute. To exit the shell, type `exit`.

### Examples of Commands
- Pipe handling: `more kk.txt | grep hola`
- Output redirection: `ls > file.txt`
- Append redirection: `ls >> file.txt`
- Count lines, words, and characters: `wc < file.txt`

## Compilation
To compile the program use the makefile

