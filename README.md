# Minishell

## About
Minishell is a simple Unix shell implementation written in C that mimics basic bash functionality. This project is part of the 42 School curriculum, designed to deepen understanding of processes, file descriptors, and Unix system programming.

## Features
- Custom prompt display with username
- Command history management
- Command execution with relative or absolute paths
- Environment variable support (`$VAR` and `$?`)
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
- Input/Output redirections:
  - `<` Input redirection
  - `>` Output redirection
  - `<<` Here-document
  - `>>` Output redirection in append mode
- Pipeline implementation (`|`)
- Quote handling:
  - Single quotes (`'`) prevent shell from interpreting metacharacters
  - Double quotes (`"`) prevent shell from interpreting metacharacters except for `$`
- Built-in commands:
  - `echo` with `-n` option
  - `cd` with relative or absolute path
  - `pwd` without options
  - `export` without options
  - `unset` without options
  - `env` without options or arguments
  - `exit` without options

## Technical Requirements
- C language
- Compilation using `gcc` with flags: `-Wall -Wextra -Werror`
- External functions allowed:
  - readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
  - printf, malloc, free, write, access, open, read, close
  - fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit
  - getcwd, chdir, stat, lstat, fstat, unlink, execve
  - dup, dup2, pipe, opendir, readdir, closedir
  - strerror, perror, isatty, ttyname, ttyslot, ioctl
  - getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

## Project Structure
```
.
├── includes/
│   └── minishell.h
├── libft/
│   └── [libft source files]
└── src/
    ├── exit.c
    ├── expander.c
    ├── init_data.c
    ├── lexer.c
    ├── main.c
    ├── mini_builtins.c
    ├── mini_here.c
    ├── node_management.c
    ├── signals.c
    ├── split.c
    ├── subsplit.c
    ├── utils_lexer.c
    ├── utils_tab.c
    └── var_env.c
```

## Building the Project
```bash
make            # Compile the project
make clean      # Remove object files
make fclean     # Remove object files and executable
make re         # Rebuild the project
```

## Implementation Details
- Uses a single global variable (`g_exit_status`) for signal handling
- Implements a custom lexer for command parsing
- Features a robust environment variable management system
- Handles command history using readline library
- Custom memory management with proper cleanup

## Error Handling
- Custom error messages for various scenarios
- Proper memory management with leak prevention
- Signal handling for interactive mode
- Quote and syntax error detection

## Authors
- [OlivierMar8](https://github.com/OlivierMar8)
- [Emiliano Presa](https://github.com/eprei)

## License
This project is part of 42 School's curriculum and is subject to its academic honor code.

## Acknowledgments
- 42 School for the project subject
- Bash documentation for reference implementation details

## Status
Project Status: Completed

## Note
This project is a learning exercise in Unix system programming and shell implementation. It is not intended for production use.
