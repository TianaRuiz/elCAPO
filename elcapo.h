#define MAX_PATH_LENGTH 256
#define DEFAULT_RETRIES 3

struct program_options {
  char config_file[MAX_PATH_LENGTH];
  char log_file[MAX_PATH_LENGTH];
  int retries;
  bool daemonize;
};

void print_usage_and_exit(int status);
void parse_program_options(int argc, char **argv, struct program_options *options);
