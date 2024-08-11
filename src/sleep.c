/* MiniBox is a busybox/toybox like replacement aiming to be lightweight,
 * portable, and memory efficient.
 *
 * Copyright (C) 2024 Robert Johnson et al <mitnew842@gmail.com>.
 * All Rights Reserved.
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 * minibox-shell.c is the main shell source with all shell builtins.
 *
 * When adding programs or features, please consider if they can be
 * accomplished in a sane way with standard unix tools. If they're
 * programs or features you added, please make sure they are read-
 * able and understandable by a novice-advanced programmer, if not,
 * add comments or let me know. Use common sense and please don't
 * bloat sources.
 *
 * I haven't tested but it could compile on windows systems with MSYS/MinGW or
 * Cygwin. MiniBox should be fairly portable for POSIX systems.
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */

#include "minibox.h"

/* sleep program */
/* Usage: sleep [seconds] */
int _sleep(int argsc, char *argsv[]) {
  char *endptr;
  errno = 0;
  long secs;

  if (argsc != 2) {
    fprintf(stderr, "Usage: sleep [seconds]\n");
    return 1;
  }

  secs = strtol(argsv[1], &endptr, 10);

  if (errno != 0 || *endptr != '\0' || secs < 0) {
    fprintf(stderr, "Invalid number of seconds: %s\n", argsv[1]);
    return 1;
  }

  sleep((unsigned int)secs);
  return 0;
}
