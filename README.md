# Minishell Project - Abstract

**Minishell** is a lightweight and educational shell implementation developed in C for Ubuntu as part of the **42 School curriculum**. This project immerses developers in system-level programming, offering practical experience in managing processes, file descriptors, and inter-process communication. With a focus on simplicity and educational value, **Minishell** replicates essential behaviors of standard Unix shells while adhering to strict coding standards.

## Features

- **Prompt Display**: Provides an interactive prompt when waiting for commands.
- **Command Execution**:
  - Execute commands using absolute paths, relative paths, or the `PATH` environment variable.
  - Supports advanced features such as pipelines and I/O redirections.
- **Built-in Commands**:
  - `echo` – Display text with the `-n` option.
  - `cd` – Change directories using relative or absolute paths.
  - `pwd` – Display the current working directory.
  - `export` – Manage environment variables without options.
  - `unset` – Remove environment variables without options.
  - `env` – List environment variables without options.
  - `exit` – Exit the shell with proper cleanup.
- **Redirection Operators**:
  - `<` – Redirect standard input.
  - `>` – Redirect standard output.
  - `>>` – Append to standard output.
  - `<<` – Handle heredoc input until a specified delimiter is reached.
- **Pipes (`|`)**: Implemented to connect commands in pipelines.
- **Environment Variable Handling**:
  - Expand variables prefixed with `$`.
  - Support `$?` to reflect the exit status of the last executed pipeline.
- **Signal Handling**:
  - `Ctrl-C`: Interrupts the current command and displays a new prompt.
  - `Ctrl-D`: Exits the shell.
  - `Ctrl-\`: No action (default behavior in `bash`).
- **Input Parsing**:
  - Handles single (`'`) and double (`"`) quotes correctly, with double quotes allowing `$` expansion.
  - Avoids interpreting unclosed quotes or special characters like `;` or `\`.
- **Error Management**:
  - Includes robust handling for invalid commands and runtime errors.
  - Prevents undefined behavior (e.g., segmentation faults).

## Objectives

1. Develop a deeper understanding of:
   - Process creation and management using `fork`, `exec`, and related system calls.
   - File descriptor operations, including redirection and pipe handling.
   - Input parsing and tokenization.
2. Build an educational shell that adheres strictly to the **42 School's Norm** and constraints.
3. Provide a framework to explore system programming concepts through a hands-on approach.

### Current Scope
The mandatory implementation includes:
- Core built-ins.
- Pipelines and redirection.
- Proper handling of shell-specific behavior (e.g., `Ctrl+C`, environment variables).

## Development Environment

- **Language**: C
- **Platform**: Ubuntu Linux
- **Libraries**: `readline`, `ncurses` (for terminal capabilities).
- **Compilation**:
  - Complies with `gcc` and adheres to `-Wall -Wextra -Werror` flags.
  - Includes a Makefile with standard rules (`all`, `clean`, `fclean`, `re`, `bonus`).
- **Memory Management**:
  - Ensures all heap allocations are freed (excluding known leaks in external libraries like `readline`).

## Collaboration and Credits

Developed collaboratively by:
- **@kjzl** – Main contributor and collaborator.
- **@wssmrks** – Main contributor and collaborator.
- **@dafneko** – Contributed to initial phases.

## Contributing

Contributions are welcome! To contribute:
1. Fork the repository.
2. Clone your fork locally.
3. Create a feature branch.
4. Commit changes with clear messages.
5. Submit a pull request for review.

## Future Directions

Potential enhancements for **Minishell**:
- Add job control (e.g., background processes with `&`).
- Improve scripting capabilities with logical operators and advanced syntax.
- Implement additional built-ins or custom shell features.
- Logical operators `&&` and `||`, including precedence management using parentheses.
- Wildcard `*` support for matching files in the current directory.

## Educational Insights

The project not only reinforces knowledge of shell operations but also builds expertise in debugging, memory management, and handling edge cases. Aspiring developers gain a foundation for advanced Linux programming and systems-level projects.
