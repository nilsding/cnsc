#include "menu.h"
#include "log.h"

static size_t
menu_types_array_size(const struct type_t types[])
{
    int i;
    for (i = 0; types[i].prefix != NULL; i++) {}
    return i;
}

//!
//! \brief menu_render_list_item renders a single list item to a new allocated
//!     string.  Make sure to call `free()` after you've finished doing things
//!     with the new string to prevent memory leaks.
//! \param type The type to render.
//! \param selected 1, if this item is selected, 0 otherwise.
//! \return A pointer to the first character of the rendered string.
//!
static char *
menu_render_list_item(const struct type_t *type, int selected)
{
    assert(type != NULL);
    size_t size =
            strlen(selected ? MENU_SELECTED_COLOR : MENU_DESELECTED_COLOR) +
            strlen(selected ? MENU_SELECTED_CHARS : MENU_DESELECTED_CHARS) +
            strlen(type->prefix) +
            strlen(COLOR_RESET) +
            strlen(": ") +
            strlen(type->description) + 1;
    char *str = (char *) malloc(size * sizeof(char));

    assert(str != NULL);

    snprintf(str, size, "%s%s%s%s: %s",
            selected ? MENU_SELECTED_COLOR : MENU_DESELECTED_COLOR,
            selected ? MENU_SELECTED_CHARS : MENU_DESELECTED_CHARS,
            type->prefix,
            COLOR_RESET,
            type->description);

    return str;
}

static void
menu_render_types(const struct type_t types[], size_t types_size, int selected)
{
    int i;
    char *str = NULL;

    for (i = 0; i < types_size; i++) {
        str = menu_render_list_item(types + i, i == selected);
        puts(str);
        free(str);
    }
}

static void
menu_cursor_show(void)
{
    printf("\033[?25h");
    fflush(stdout);
}

static void
menu_cursor_hide(void)
{
    printf("\033[?25l");
    fflush(stdout);
}

static void
menu_cursor_move_up(unsigned int lines)
{
    printf("\033[%dA", lines);
    fflush(stdout);
}

static void
menu_clear_to_end_of_screen(void)
{
    printf("\033[J");
    fflush(stdout);
}

//!
//! \brief menu_set_buffered_input
//! \param buffered if set to 1, set unbuffered IO, unset it otherwise
//!
static void
menu_set_buffered_input(int buffered)
{
    static struct termios tio;

    // get terminal settings for stdin
    tcgetattr(STDIN_FILENO, &tio);

    log_logf(3, "tio.c_lflag before: %x", tio.c_lflag);
    if (buffered) {
        // enable canonical mode (i.e. buffered I/O) and local echo
        tio.c_lflag |= (ICANON | ECHO);
    } else {
        // same as above, but reversed
        tio.c_lflag &= (~ICANON & ~ECHO);
    }
    log_logf(3, ", after: %x\n", tio.c_lflag);

    tcsetattr(STDIN_FILENO, TCSANOW, &tio);
}

static int
menu_read_input(int *selected, int *return_pressed)
{
    switch (getchar()) {
    case 'q':
        menu_cursor_move_up(1);
        return 1;
    case '\n':
        menu_cursor_move_up(1);
        *return_pressed = 1;
        return 1;
    case 033:  // escape sequence
        if (getchar() == '[') {
            switch (getchar()) {
            case 'A':  // up
                (*selected)--;
                break;
            case 'B':  // down
                (*selected)++;
                break;
            }
        }
    }

    return 0;
}

struct type_t *
menu_ask_type(const char *question, const struct type_t types[])
{
    int selected = 0, should_quit = 0, return_pressed = 0;
    struct type_t *selected_type = NULL;
    size_t types_size = menu_types_array_size(types);
    log_logf(3, "cnsc was compiled with %d log types\n", types_size);

    menu_cursor_hide();
    printf("%s:\n", question);

    menu_set_buffered_input(0);

    do {
        if (selected <= 0) {
            selected = 0;
        } else if (selected >= types_size) {
            selected = types_size - 1;
        }
        menu_render_types(types, types_size, selected);
        menu_cursor_move_up(types_size);
    } while ((should_quit = menu_read_input(&selected, &return_pressed)) == 0);

    if (return_pressed) {
        selected_type = (struct type_t *) types + selected;
        printf("%s: %s%s%s: %s\n", question, MENU_SELECTED_COLOR,
               selected_type->prefix, COLOR_RESET,
               selected_type->description);
    }

    menu_clear_to_end_of_screen();

    menu_set_buffered_input(1);
    menu_cursor_show();

    return selected_type;
}

char *
menu_ask_string(const char *question)
{
    char *str = NULL;
    size_t cap = 0;
    ssize_t len = 0;

    printf("%s: ", question);
    fflush(stdout);

    if ((len = getline(&str, &cap, stdin)) <= 0) {
        return NULL;
    }

    // strip newline
    str[strlen(str) - 1] = 0x00;

    return str;
}

void
menu_reset_console(void)
{
    menu_clear_to_end_of_screen();
    menu_set_buffered_input(1);
}
