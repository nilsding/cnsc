#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <termios.h>
#include "cnsc.h"

//!
//! \brief menu_ask_type shows a selection screen for the types `types`.
//! \param question The question to show.
//! \param types A `NULL`-terminated array of `struct type_t`s.
//! \return The selected `struct type_t` entry, or `NULL` if the user
//!     aborted the selection.
//!
struct type_t *menu_ask_type(const char *question,
                             const struct type_t types[]);

//!
//! \brief menu_ask_string shows an input prompt and reads a string from
//!     `stdin`.  The read string is allocated dynamically, so make sure to
//!     use `free()` on the allocated string afterwards to prevent memory
//!     leaks.
//! \param qustion The question to show.
//! \return A pointer to the first character of the string.
//!
char *menu_ask_string(const char *question);

#endif // MENU_H
