# Minishell Project - Abstract

**Minishell** is a lightweight and educational shell implementation developed in C for Ubuntu. This project, undertaken as part of the **42 School curriculum**, provides a hands-on opportunity to explore system programming concepts such as process management, file I/O, and inter-process communication. Designed to be compact yet functional, **Minishell** mimics the behavior of standard shells while offering an educational experience in low-level programming.

## Features

- **Full Command Execution**: Support for executing all commands, including complex pipelines.
- **Built-in Commands**: Fully implemented built-in commands include:
  - `cd` – Change the current working directory.
  - `exit` – Exit the shell gracefully.
  - `env` – Display environment variables.
  - `export` – Add or modify environment variables.
  - `unset` – Remove environment variables.
  - `echo` – Display text with support for options like `-n`.
- **Pipes and Redirections**: 
  - **Pipes (`|`)**: Chain multiple commands, passing output from one as input to the next, with robust handling of difficult pipeline scenarios.
  - **Redirections (`<`, `>`, `>>`)**: Handle input and output redirection efficiently.
- **Process Management**: Leverages `fork` and `exec` system calls to handle command execution in child processes.
- **Environment Variable Handling**: Parse, modify, and utilize environment variables dynamically during command execution.
- **Error Handling**: Robust handling of invalid commands, arguments, and runtime errors.
- **Limitations**: Logical operators (`&&` and `||`) are not implemented.

## Objectives

- Provide an in-depth understanding of:
  - Process creation and communication.
  - File descriptor management.
  - Parsing and tokenization of shell input.
- Encourage learning through problem-solving and hands-on implementation.
- Deliver a structured, functional shell while adhering to the constraints and goals of the **42 School** project.

## Why Minishell?

**Minishell** is an educational tool and a stepping stone toward mastering low-level programming and Linux system interaction. It enables developers to:
- Build a functional shell from the ground up.
- Understand the complexities of terminal-based applications.
- Strengthen debugging and optimization skills in C programming.

## Development Environment

- **Language**: C
- **Platform**: Ubuntu Linux
- **Tools**: `gcc`, `make`, and any preferred editor or IDE.

## Collaboration and Credits

This project is developed collaboratively by:
- **@kjzl** – Main collaborator and contributor.
- **@wssmrks** – Collaborator and contributor.

## Future Enhancements

Although **Minishell** already supports pipes, redirections, and full command execution, potential extensions may include:
- Adding job control features (e.g., background processes).
- Enhancing compatibility with advanced shell scripting scenarios.
- Implementing logical operators like `&&` and `||`.

## Contributing

Contributions to the project are welcome! If you'd like to contribute:
1. Fork the repository.
2. Clone it to your local environment.
3. Create a new branch for your feature or fix.
4. Submit a pull request with a clear and detailed description of your changes.

---

This README outlines the foundation and objectives of the **Minishell** project, highlighting its role as an educational endeavor for students and developers alike. Dive in, explore, and enhance your understanding of shell development with **Minishell**!