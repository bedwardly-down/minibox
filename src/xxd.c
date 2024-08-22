/* MiniBox is a busybox/toybox like replacement aiming to be lightweight,
 * portable, and memory efficient.
 *
 * Copyright (C) 2024 Robert Johnson et al <mitnew842@gmail.com>.
 * All Rights Reserved.
 *
 * Licensed under Unlicense License, see file LICENSE in this source tree.
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
 * Licensed under Unlicense License, see file LICENSE in this source tree.
 */

#include "minibox.h"

/* xxd program: hex dump */
int xxd(int argc, char *argv[]) {
  FILE *fp;
  unsigned char buffer[16];
  size_t bytesRead;

  // Determine whether to use stdin or a file
  if (argc > 2) {
    fprintf(stderr, "Usage: xxd [file]\n");
    return 1;
  }

  if (argc == 2) {
    fp = fopen(argv[1], "rb");
    if (!fp) {
      perror("fopen");
      return 1;
    }
  } else {
    fp = stdin;
  }

  while ((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
    // ftell might not be accurate with stdin, so using a separate counter
    static long offset = 0;
    printf("%08lx: ", offset);
    for (size_t i = 0; i < bytesRead; i++) {
      printf("%02x ", buffer[i]);
    }
    for (size_t i = bytesRead; i < sizeof(buffer); i++) {
      printf("   ");
    }
    printf("| ");
    for (size_t i = 0; i < bytesRead; i++) {
      printf("%c", (buffer[i] >= 32 && buffer[i] <= 126) ? buffer[i] : '.');
    }
    printf("\n");
    offset += bytesRead;
  }

  // Close the file only if it's not stdin
  if (fp != stdin) {
    fclose(fp);
  }

  return 0;
}
