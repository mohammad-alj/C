#include <stdio.h>
#include <stdlib.h>

char *f_to_s(float);
float prompt(char *);

int main()
{
    float x = prompt("x: ");

    char operator;
    while (1)
    {
        printf("operator (+, -, *, /): ");
        if (scanf(" %c", &operator) == 1 && (operator== '+' || operator== '-' || operator== '*' || operator== '/'))
            break;

        // Clear input buffer in case of invalid input
        while (getchar() != '\n')
            ;
    }

    float y = prompt("y: ");

    float result = 0; // Initialize result
    switch (operator)
    {
    case '+':
        result = x + y;
        break;
    case '-':
        result = x - y;
        break;
    case '*':
        result = x * y;
        break;
    case '/':
        if (y == 0)
        {
            printf("Error: Can't divide by zero.\n");
            return 1;
        }
        result = x / y;
        break;
    }

    char *formatted_result = f_to_s(result);
    char *formatted_x = f_to_s(x);
    char *formatted_y = f_to_s(y);

    if (formatted_result == NULL || formatted_x == NULL || formatted_y == NULL)
    {
        // Handle the error (printing an error message or performing cleanup)
        printf("Error: Formatting failed.\n");

        // Free the dynamically allocated memory before exiting
        free(formatted_result);
        free(formatted_x);
        free(formatted_y);
        return 1; // Indicate an error
    }

    printf("%s %c %s = %s\n", formatted_x, operator, formatted_y, formatted_result);

    // Free the dynamically allocated memory
    free(formatted_result);
    free(formatted_x);
    free(formatted_y);
    return 0;
}

/*
 * @brief prompts the user for a floating point number
 * @param string message to display
 * @return prompted float
 */
float prompt(char *message)
{
    float x;
    while (1)
    {
        printf("%s", message);
        if (scanf("%f", &x) == 1)
        {
            // Clear input buffer in case of invalid input
            while (getchar() != '\n')
                ;
            return x;
        }
        else
        {
            // Clear input buffer
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter a valid floating-point number.\n");
        }
    }
}

/*
 * @brief converts a floating point number to a string, if the floating point number has no fractunal parts it will remove the decimal point.
 * @param x the floating point number
 * @return x as a string
 */
char *f_to_s(float x)
{
    // Determine the required size
    int str_len = snprintf(NULL, 0, (x - (int)x == 0) ? "%.0f" : "%.2f", x);

    // Allocate memory for the string
    char *str = malloc(str_len + 1);
    if (str == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return NULL;
    }

    // Format
    sprintf(str, (x - (int)x == 0) ? "%.0f" : "%.2f", x);
    return str;
}
