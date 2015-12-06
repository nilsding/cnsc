#include "git.h"
#include "log.h"

int
git_check(void)
{
    log_logf(2, "Checking if git is installed...\n");
    return !system("git help > /dev/null 2>&1");
}

int
git_is_repo(void)
{
    log_logf(2, "Checking if the current directory is a valid git repo...\n");
    return !system("git status > /dev/null 2>&1");
}

char *
git_commit_message_new(struct type_t *type, const char *message)
{
    char *str;
    assert(type != NULL);
    assert(message != NULL);
    size_t size = strlen(type->prefix) + strlen(": ") + strlen(message) + 1;
    assert(size > 0);

    str = (char *) malloc(size * sizeof(char));
    if (str != NULL) {
        strcpy(str, type->prefix);
        strcat(str, ": ");
        strcat(str, message);
    }

    return str;
}

void
git_commit_message_free(char *message)
{
    if (message != NULL) {
        free(message);
    }
}

int
git_commit(const char *message, const char *body)
{
    assert(message != NULL);
    pid_t pid = fork();

    if (pid == -1) {
        log_errlogf(0, "fork() failed: %s\n", strerror(errno));
        return -1;
    } else if (pid == 0) {
        char *argv[] = {
            // 0,  1
            "git", "commit",
            // 2, 3
            COMMIT_ALL ? "-am" : "-m", (char *) message,
            // 4, 5, 6
            "-m", (char *) body, NULL
        };

        if (body) {
            log_logf(1, "Command: git commit %s \"%s\" -m \"%s\"\n",
                     COMMIT_ALL ? "-am" : "-m", message, body);
        } else {
            log_logf(1, "Command: git commit %s \"%s\"\n",
                     COMMIT_ALL ? "-am" : "-m", message);
            argv[4] = NULL;
        }
        execvp("git", argv);

        log_errlogf(0, "execvp() for \"git commit\" failed: %s\n", strerror(errno));
        _exit(-1);
    }

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        log_errlogf(0, "waitpid() failed: %s\n", strerror(errno));
        return -1;
    }
    log_logf(2, "Return status: %d\n", WEXITSTATUS(status));
    return WEXITSTATUS(status);
}
