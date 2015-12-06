#include <stdio.h>
#include <unistd.h>
#include "cnsc.h"
#include "log.h"
#include "git.h"
#include "menu.h"

int COMMIT_ALL = 0;
int COMMIT_MESSAGE_FROM_ARGS = 0;
int VERBOSE = 0;

static void
usage() {
    log_errlogf(0, "usage: cnsc [-ahmv]\n");
}

//!
//! \brief This is the main entry point of cnsc.
//! \return 0 on success, a non-zero value on failure.
//!
int
main(int argc, char **argv)
{
    int ch, retval = 0;
    char *commit_message = NULL;

    // read command line arguments
    while ((ch = getopt(argc, argv, "ahm:v")) != -1) {
        switch (ch) {
        case 'a':
            COMMIT_ALL = 1;
            break;
        case 'v':
            VERBOSE++;
            break;
        case 'm':
            commit_message = optarg;
            COMMIT_MESSAGE_FROM_ARGS = 1;
            break;
        case 'h':
            usage();
            log_errlogf(0, "https://github.com/nilsding/cnsc\n");
            return 0;
        case '?':
        default:
            usage();
            return 1;
        }
    }

    log_logf(3, "COMMIT_ALL = %s\nCOMMIT_MESSAGE_FROM_ARGS = %s\n",
             COMMIT_ALL ? "T" : "F", COMMIT_MESSAGE_FROM_ARGS ? "T" : "F");
    if (COMMIT_MESSAGE_FROM_ARGS) {
        log_logf(3, "commit_message = \"%s\"\n", commit_message);
    }
    log_logf(3, "VERBOSE = %d\n", VERBOSE);

    if (!git_check()) {
        log_errlogf(0, "Could not find git in $PATH.\n"
                       "Please install git using a package manager of your"
                       "choice.\n");
        return 2;
    }

    if (!git_is_repo()) {
        log_errlogf(0, "The current directory is not a valid git"
                       "repository.\n");
        return 2;
    }

    struct type_t *selected_type = menu_ask_type("Choose a type", TYPES);
    if (!selected_type) {
        log_logf(0, "No type selected.  Aborting.\n");
        return 1;
    }

    if (!COMMIT_MESSAGE_FROM_ARGS) {
        commit_message = menu_ask_string("Enter a commit message");
    } else {
        printf("%s: %s\n", "Enter a commit message", commit_message);
    }
    if (commit_message == NULL || commit_message[0] == 0x00) {
        log_errlogf(0, "Aborting due to empty commit message.\n");
        return 1;
    }

    char *new_commit_message = git_commit_message_new(selected_type,
                                                      commit_message);

    if (!COMMIT_MESSAGE_FROM_ARGS) {
        git_commit_message_free(commit_message);
    }

    // TODO: read commit body

    retval = git_commit(new_commit_message, NULL);

    // cleanup
    git_commit_message_free(new_commit_message);

    return retval;
}

