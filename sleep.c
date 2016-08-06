#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define DEFAULT_SLEEP 5

static const char interrupt_message[] = "Sleep interrupted!\n";

void interrupt_handler(int signo) {
  write(STDERR_FILENO, interrupt_message, sizeof(interrupt_message));
  exit(128 + SIGINT);
}

/**
 * Sleeps for a given amount of seconds.
 * Usage: sleep [n]
 *  where n is a positive integer
 * It sleeps a default time (5 secs) if n is incorrect or not specified
 */
int main(int argc, char **argv) {

  int sleep_time = DEFAULT_SLEEP;

  signal(SIGINT, interrupt_handler);

  if (argc > 1) {
    sleep_time = atoi(argv[1]);
    if (sleep_time <= 0) {
      sleep_time = DEFAULT_SLEEP;
    }
  }

  printf("About to sleep for %d seconds\n", sleep_time);
  fflush(stdout);
  sleep((unsigned int)sleep_time);
  printf("Done sleeping\n");

}
