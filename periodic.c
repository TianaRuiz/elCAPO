#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define DEFAULT_LOOPS 5

static const char interrupt_message[] = "Periodic sleep interrupted!\n";

void interrupt_handler(int signo) {
  write(STDERR_FILENO, interrupt_message, sizeof(interrupt_message));
  exit(128 + SIGINT);
}

/**
 * Run a loop sleeping one second per iteration.
 * Usage: periodic [n]
 *  where n is a positive integer
 * It loops n times sleeping one second each iteration, or a default number of times if n is
 * not provided or incorrect
 */
int main(int argc, char **argv) {

  int loops = DEFAULT_LOOPS;

  signal(SIGINT, interrupt_handler);

  if (argc > 1) {
    loops = atoi(argv[1]);
    if (loops <= 0) {
      loops = DEFAULT_LOOPS;
    }
  }

  for (int i = 1; i <= loops; i++) {
    printf("Sleep period: %d\n", i);
    fflush(stdout);
    sleep(1);
  }
}
