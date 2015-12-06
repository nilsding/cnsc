#include <stdlib.h>
#include "cnsc.h"

const struct type_t TYPES[] = {
    { "feat", "a new feature" },
    { "fix", "a bug fix" },
    { "docs", "documentation only changes" },
    { "style", "changes that do not affect the meaning of the code" },
    { "refactor", "a code change that neither fixes a bug nor adds a new "
                  "feature" },
    { "perf", "a code change that improves performance" },
    { "test", "adds missing tests" },
    { "chore", "changes to the build process or auxiliary tools or libraries "
               "such as documentation generation" },
    { NULL, NULL }
};
