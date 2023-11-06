#include "custom_shell.h"

/**
 * _strcat - Concatenates two strings together
 * @destination: The destination string to be concats together
 * @source: The source file to concats from
 * Return: The processed string
 */
char *_strcat(char *destination, char *source) {
  int i = 0, j = 0;

  while (destination[i]) {
    i++;
  }
  while (source[j]) {
    destination[i] = source[j];
    i++;
    j++;
  }
  destination[i] = '\0';

  return (destination);
}

/**
 * _strcpy - function that Copies a string
 * @source: The source string to be copied from
 * @destination: The destination string to be copied to to
 *
 * Return:destination
 */
char *_strcpy(char *destination, char *source) {
  int a = 0;

  while (*(source + a)) {
    *(destination + a) = *(source + a);
    a++;
  }
  destination[a] = '\0';

  return (destination);
}

/**
 * _strlen - Function thar finds the length of a string
 * @string: The string as an argument
 *
 * Return: returns the length of the string
 */

int _strlen(char *string) {
  int a = 0;

  while (*(string + a) != '\0') {
    a++;
  }

  return (a);
}

/**
 * _strncmp - Function that compares two strings up to number of characters
 * @string1: argument as a string
 * @string2: The second string
 * @n: The number of characters to compare
 *
 * Return: The first difference or 0 if none
 */
int _strncmp(char *string1, char *string2, int n) {
  int i = 0, difference = 0;

  while (string1[i] && string2[i] && (i < n)) {
    if (string1[i] == string2[i]) {
      i++;
      continue;
    } else {
      difference = string1[i] - string2[i];
      break;
    }
  }

  return (difference);
}

/**
 * _strcmp - Compares two strings using ASCII values
 * @string1: The first string
 * @string2: The second string
 *
 * Return: The number of differences
 */
int _strcmp(char *string1, char *string2) {
  int i = 0, difference = 0;

  while (string1[i] && string2[i]) {
    if (string1[i] == string2[i]) {
      i++;
      continue;
    } else {
      difference = string1[i] - string2[i];
      break;
    }
  }

  return (difference);
}
