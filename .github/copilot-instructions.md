# GitHub Copilot Instructions for miniRT

This guide provides essential information for working with the miniRT project, a ray-tracer implementation in C.

## Project Architecture

- **Project Structure**:
  - `src/`: Source code files (.c)
  - `include/minirt/`: Header files (.h)
  - `libft/`: Custom C library with utility functions
  - `mlx_linux/`: MinilibX graphics library for Linux
  - `obj/`: Compiled object files

- **Core Components**:
  - MinilibX (mlx): Graphics library for window management and rendering
  - libft: Custom utility functions for memory, strings, lists

## Development Workflow

### Building the Project

- **Standard Build**: `make all` - Builds the miniRT executable
- **Clean Build**: `make re` - Cleans and rebuilds the project
- **Clean Only**: `make clean` - Removes object files, `make fclean` - Removes executable and object files

### Docker Commands

- **Development Environment**: `make docker-dev` - Starts a dev container with all dependencies
- **Building**: `make docker-build` - Builds the project within a container
- **Testing**: `make docker-test` - Runs tests in an isolated environment
- **Static Analysis**: `make docker-check` - Runs code quality checks including norminette

## Coding Conventions

- **Code Style**: The project follows the 42 School Norm (enforceable with norminette v3.3.55)
- **Commit Style**: Follow Conventional Commits format as outlined in `commit_template.txt`
- **Error Handling**: Return status codes for errors (0 for success, non-zero for failures)

## Library Usage

- **MinilibX (mlx)**: A simple X-Window programming API that provides:
  - Window management (`mlx_new_window`, `mlx_destroy_window`)
  - Event handling (`mlx_hook`, `mlx_loop`)
  - Image manipulation (`mlx_new_image`, `mlx_put_image_to_window`)

## Code Review Guidelines

### Review Focus

1.  **Logic and Bugs**: Identify potential logic errors, race conditions, memory leaks, segmentation faults, or other bugs.
2.  **Clarity and Readability**: Assess whether the code is easy to understand and maintain. Suggest improvements for complex logic, and check for clear variable and function names.
3.  **Project Structure**: Ensure that new code adheres to the project's file structure, with source files in `src/` and header files in `include/`.
4.  **Library Usage**: Verify the correct and efficient use of the `minilibx` library.
5.  **Error Handling**: Check for consistent and robust error handling that matches the project's existing patterns.
6.  **Best Practices**: Suggest improvements based on general C programming best practices, such as avoiding magic numbers and ensuring proper resource management.

### Comment Labels

Please use the following labels at the beginning of each comment:

*   `[must]`: Required changes.
*   `[imo]`: In my opinion. Suggestions for improvement.
*   `[nits]`: Minor issues, such as typos or formatting.
*   `[ask]`: Questions for the author.
*   `[good]`: Positive feedback.
*   `[help]`: Need help to understand the code.

### Language for Comments

**All review comments must be written in Japanese.**
