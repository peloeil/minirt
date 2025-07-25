# GitHub Copilot Instructions for Code Review

Please review pull requests focusing on the following aspects. Your feedback is crucial for maintaining the quality and integrity of the codebase.

## Review Focus

1.  **Logic and Bugs**: Identify potential logic errors, race conditions, memory leaks, or other bugs.
2.  **Clarity and Readability**: Assess whether the code is easy to understand and maintain. Suggest improvements for complex logic, and check for clear variable and function names.
3.  **Project Structure**: Ensure that new code adheres to the project's file structure, with source files in `src/` and header files in `include/`.
4.  **Library Usage**: Verify the correct and efficient use of the `minilibx` library.
5.  **Error Handling**: Check for consistent and robust error handling that matches the project's existing patterns.
6.  **Best Practices**: Suggest improvements based on general C programming best practices, such as avoiding magic numbers and ensuring proper resource management.

## Comment Labels

Please use the following labels at the beginning of each comment:

*   `[must]`: Required changes.
*   `[imo]`: In my opinion. Suggestions for improvement.
*   `[nits]`: Minor issues, such as typos or formatting.
*   `[ask]`: Questions for the author.
*   `[good]`: Positive feedback.
*   `[help]`: Need help to understand the code.

## Language for Comments

**All review comments must be written in Japanese.**
