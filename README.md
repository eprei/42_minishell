# Minishell

## Overview
The **Minishell** project is designed to create a simple Unix shell in C. The shell will emulate some behaviors of Bash and include a prompt for command execution.

## Features
- Display a command prompt.
- Implement command history.
- Search and execute binaries using relative or absolute paths.
- Handle input/output redirections (`<`, `>`, `<<`, `>>`).
- Implement pipes (`|`), connecting commands in a pipeline.
- Handle single (`'`) and double (`"`) quotes.
- Manage environment variables and built-in commands:
  - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

## Signal Handling
- Supports `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`, replicating Bash behavior.

## Builtins
- `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit` (with their respective options).

## Requirements
- No memory leaks are allowed except for those caused by the `readline()` function.
- Must follow the provided C coding Norm and compile with `-Wall -Wextra -Werror` flags.
- Use of a global variable is limited to signal handling.

## Compilation
Use the provided `Makefile` to compile the project:
```bash
make
