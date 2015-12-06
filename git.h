/* -*- C -*- */
#ifndef GIT_H
#define GIT_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include "cnsc.h"

//!
//! \brief git_check checks whether `git` is installed on the system.
//! \return 1 if `git` is installed, 0 otherwise.
//!
int git_check(void);

//!
//! \brief git_is_repo checks whether the current directory is a valid git
//!     repository using `git status`.
//! \return 1 if the current directory is part of a valid git repository,
//!     0 otherwise.
//!
int git_is_repo(void);

//!
//! \brief git_commit_message_new creates a new commit message with the `type`
//!     prefixed.  This function uses `malloc`, so make sure that you call
//!     `git_commit_message_free` after doing something with the returned
//!     value to prevent memory leaks.
//! \param type The type of the commit.
//! \param message The commit message
//! \return A pointer to the first character of the commit message, or `NULL`
//!     if allocation of memory failed.
//!
char *git_commit_message_new(struct type_t *type, const char *message);

//!
//! \brief git_commit_message_free Frees the memory allocated by
//!     `git_commit_message_new`.
//! \param message The pointer to the commit message allocated by
//!     `git_commit_message_new`.
//!
void git_commit_message_free(char *message);

//!
//! \brief git_commit runs `git commit` with the commit message `message` and
//!     an optional commit body `body`.
//! \param message The commit message.  Required.
//! \param body The commit body.  Can be ommitted by setting this argument to
//!     `NULL`.
//! \return -1 if something failed while starting `git`, otherwise the return
//!     value of `git commit`.
//!
int git_commit(const char *message, const char *body);

#endif // GIT_H
