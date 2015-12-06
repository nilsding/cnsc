/* -*- C -*- */
#ifndef CNSC_H
#define CNSC_H

struct type_t {
    char *prefix;
    char *description;
};

//! If this is set to 1, cnsc will run `git add -a` first (similar to
//! `git commit -a`).
extern int COMMIT_ALL;

//! Verbosity level.
extern int VERBOSE;

//! An array containing the different types.  You can change it in `types.c`,
//! but make sure that the array ends with `{ NULL, NULL }`.
extern const struct type_t TYPES[];

#define COLOR_RESET   "\033[0m"
#define COLOR_BLACK   "\033[30m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

#define MENU_SELECTED_CHARS   "==> "
#define MENU_DESELECTED_CHARS "    "
#define MENU_SELECTED_COLOR   COLOR_CYAN
#define MENU_DESELECTED_COLOR COLOR_RESET

#endif // CNSC_H
