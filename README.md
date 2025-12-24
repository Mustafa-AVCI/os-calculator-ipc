# os-calculator-ipc

# OS Calculator (Fork / Exec / Pipe IPC)

A mini calculator project built for **Operating Systems** course to demonstrate:
- **Process creation (fork)**
- **Program replacement (exec / execl)**
- **Inter-process communication (pipe)**
- (Optional / Extended) A **Saver process** that writes results into a file via pipe.

## Features
- Menu-driven CLI calculator
- Each operation runs as a **separate child process**
- Parent process collects result through **pipe**
- Supported operations:
  - Addition
  - Subtraction
  - Multiplication
  - Division (with divide-by-zero protection)

## Project Structure
```txt
src/
  calculator.c
  addition.c
  subtraction.c
  multiplication.c
  division.c
