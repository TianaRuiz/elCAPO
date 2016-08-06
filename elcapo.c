#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "elcapo.h"

static char *program_name;

void print_usage_and_exit(int status) {

  printf("Usage: %s -c config_file [-h] [-d] [-r retries]\n", program_name);
  printf("Where\n");
  printf("\t-c config_file\t\tSet elCAPO configuration file\n");
  printf("\t-h\t\t\tShow this help and terminate\n");
  printf("\t-d\t\t\tRun as a daemon\n");
  printf("\t-r retries\t\tRetry failed commands for `retries` times\n");
  printf("\t-l log_file\t\tUse log_file for stdout and stderr when running as daemon\n");
  exit(status);
}

void parse_program_options(int argc, char **argv, struct program_options *options) {

  bool set_config = false, set_logfile = false;
  char opt;

  bzero(options->config_file, MAX_PATH_LENGTH);
  bzero(options->log_file, MAX_PATH_LENGTH);
  options->daemonize = false;
  options->retries = DEFAULT_RETRIES;

  while((opt = getopt(argc, argv, "hdc:r:l:")) != -1) {
    switch(opt) {
    case 'd':
      options->daemonize = true;
      break;
    case 'c':
      set_config = true;
      strncpy(options->config_file, optarg, MAX_PATH_LENGTH-1);
      break;
    case 'r':
      options->retries = atoi(optarg);
      if (options->retries < 1) {
        fprintf(stderr, "Invalid retries number: %d\n", options->retries);
        print_usage_and_exit(1);
      }
      break;
    case 'l':
      set_logfile = true;
      strncpy(options->log_file, optarg, MAX_PATH_LENGTH-1);
      break;
    case 'h':
      print_usage_and_exit(0);
    default:
      print_usage_and_exit(1);
    }
  }

  if (!set_config) {
    fprintf(stderr, "Must specify configuration file\n");
    print_usage_and_exit(1);
  }

}


int main(int argc, char **argv) {

  struct program_options options;

  program_name = argv[0];

  // -- Parse command line options
  parse_program_options(argc, argv, &options);

#ifdef DEBUG
  printf("*** Starting ElCAPO ***\n");
  printf("*** PID : %d ***\n", getpid());
  printf("*** PPID: %d ***\n", getppid());
  printf("*** PGID: %d ***\n", getpgrp());
  printf("*** SSID: %d ***\n", getsid(0));

  printf("*** Config file: %s ***\n", options.config_file);
  printf("*** Daemonize: %d ***\n", options.daemonize);
  printf("*** Retries: %d ***\n", options.retries);
#endif


  // -- Read configuration file

  // -- If daemonized, create session, process group, and go to background
  //   -- Then close file descriptors and redirect stdout / stderr to /dev/null or log file

  // -- Start child processes

  // -- Set up signal handlers for SIGHUP to show the number of running processes

	// -- Wait for processes to terminate
  //   -- When a process terminates, check if it needs to be restarted.
  //   -- If it does, check if the exit status is != 0 and if it already used max retries

  // -- After waiting for all processes (including those that were restarted), terminate

}
