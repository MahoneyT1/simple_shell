#include "custom_shell.h"

/**
 * main - Function serving as entry point for the custom shell
 * @argc: Argument counter
 * @argv: Array of arguments
 * @env: Environment variables
 *
 * Return: Return code
 */
int main(int argc, char **argv, char **env) {
  char *input = NULL, *pathEnvVar = NULL;
  size_t bufferSize = 0;
  char *argsArray[20], *pathDirsArray[20];
  int returnValue = 0, i;

  (void)argc;
  (void)argv;

  while (1) {
    i = 0;
    while (env[i] != NULL) {
      if (_strncmp(env[i], "PATH=", 5) == 0) {
        pathEnvVar = duplicateString((env[i] + 5));
        break;
      }
      i++;
    }
    splitAndTokenizeString(pathEnvVar, ":", pathDirsArray);

    if (isatty(STDIN_FILENO))
      write(STDOUT_FILENO, "Victor_shell $ ", 14);

    if (getline(&input, &bufferSize, stdin) == -1) {
      free(input);
      free(pathEnvVar);
      exit(EXIT_SUCCESS);
    }
    splitAndTokenizeString(input, " \n\t", argsArray);

    if (!argsArray[0]) {
      free(pathEnvVar);
      continue;
    }

    if (_strcmp(argsArray[0], "exit") == 0) {
      free(input);
      free(pathEnvVar);
      exit(EXIT_SUCCESS);
    }

    if (_strcmp(argsArray[0], "env") == 0) {
      for (i = 0; env[i] != NULL; i++) {
        write(STDOUT_FILENO, env[i], _strlen(env[i]));
        write(STDOUT_FILENO, "\n", 1);
      }
      free(pathEnvVar);
      continue;
    }

    if (access(argsArray[0], X_OK) == 0)
      createChildProcess(pathEnvVar, argsArray[0], argsArray);
    else
      returnValue = checkCommandInPath(pathEnvVar, pathDirsArray, argsArray);
  }

  return (returnValue);
}

/**
 * splitAndTokenizeString - Tokenizes a string using specified delimiters
 * @inputString: The string to tokenize
 * @delimiters: Delimiters to use
 * @tokens: Array to store the tokens
 * Return: void
 */

void splitAndTokenizeString(char *inputString, char *delimiters,
                            char **tokens) {
  char *token = strtok(inputString, delimiters);
  int i = 0;

  while (token != NULL) {
    tokens[i] = token;
    i++;
    token = strtok(NULL, delimiters);
  }
  tokens[i] = NULL;
}

/**
 * checkCommandInPath - Checks if the command exists in any of the directories
 * in PATH
 * @pathEnv: The PATH environment variable
 * @pathDirs: Array containing PATH directories
 * @args: Array of arguments
 * Return: 127 if the command is not found
 */

int checkCommandInPath(char *pathEnv, char **pathDirs, char **args) {
  int i = 0;
  char *composedPath = NULL;
  struct stat status;

  while (pathDirs[i] != NULL) {
    composedPath = malloc(_strlen(args[0]) + _strlen(pathDirs[i]) + 2);
    _strcpy(composedPath, pathDirs[i]);
    _strcat(composedPath, "/");
    _strcat(composedPath, args[0]);

    if (stat(composedPath, &status) == 0) {
      createChildProcess(pathEnv, composedPath, args);
      free(composedPath);

      return (0);
    }
    free(composedPath);
    i++;
  }

  return (127);
}

/**
 * createChildProcess - Creates a child process to execute a command
 * @pathEnv: The PATH environment variable
 * @commandPath: Path to the command
 * @args: Array of arguments
 * Return: Status code of the child process
 */

int createChildProcess(char *pathEnv, char *commandPath, char **args) {
  pid_t childProcess;
  pid_t signal;
  int status = 0;

  free(pathEnv);
  childProcess = fork();

  if (childProcess == 0) {
    if (execve(commandPath, args, NULL) == -1) {
      exit(EXIT_FAILURE);
    }
  }

  else if (childProcess < 0) {
    exit(EXIT_FAILURE);
  }

  else {
    do {
      signal = waitpid(childProcess, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  (void)signal;

  return (status);
}

/**
 * duplicateString - Duplicates a string
 * @originalString: The original string
 * Return: A pointer to the duplicated string
 */
char *duplicateString(char *originalString) {
  int i = 0;
  int n = 0;
  char *copy;

  if (originalString == NULL) {
    return (NULL);
  }

  while (originalString[i] != '\0') {
    i++;
    n++;
  }
  n++;

  copy = malloc(n * sizeof(char));

  if (copy == NULL) {
    return (NULL);
  }

  for (i = 0; i < n; i++) {
    copy[i] = originalString[i];
  }

  return (copy);
}
