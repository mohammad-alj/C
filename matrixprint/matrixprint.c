#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    const char *lower_chars = "abcdefghijklmnopqrstuvwxyz";
    const char *upper_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *special_chars = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    const char *numbers = "0123456789";

    char *input_buffer;
    size_t buffer_size = 100;
    input_buffer = (char *)malloc(buffer_size * sizeof(char));

    if (input_buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }

    printf("Text: ");

    size_t input_size;
    if (fgets(input_buffer, buffer_size, stdin) != NULL)
    {
        input_size = strlen(input_buffer);
        if (input_size > 0 && input_buffer[input_size - 1] == '\n')
        {
            input_size[input_buffer - 1] = '\0';
            input_size--;
        }
    }
    else
    {
        fprintf(stderr, "Failed to read text!");
        return 1;
    }

    char input[input_size];
    strcpy(input, input_buffer);
    free(input_buffer);

    char *result = malloc(input_size * sizeof(char) + sizeof(char));
    result[0] = '\0';

    for (int i = 0; i < input_size; i++)
    {
        const char c = input[i];
        if (isupper(c))
        {
            for (int j = 0; j < strlen(upper_chars); j++)
            {
                printf("%s%c\n", result, upper_chars[j]);
                usleep(50000);
                if (upper_chars[j] == c)
                    break;
            }
        }
        else if (islower(c))
        {

            for (int j = 0; j < strlen(lower_chars); j++)
            {
                printf("%s%c\n", result, lower_chars[j]);
                usleep(50000);
                if (upper_chars[j] == c)
                    break;
            }
        }
        else if (c == ' ')
        {
            printf("%s%c\n", result, c);
            usleep(50000);
        }
        else if (ispunct(c))
        {
            for (int j = 0; j < strlen(special_chars); j++)
            {
                printf("%s%c\n", result, special_chars[j]);
                usleep(50000);
                if (special_chars[j] == c)
                    break;
            }
        }
        else
        {
            printf("%s%c\n", result, c);
            usleep(50000);
        }

        result[i] = c;
        result[i + 1] = '\0';
    }

    return 0;
}