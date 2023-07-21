#include <iostream>

#include "loki/virtual_machine.hpp"

#include "compiler.hpp"

static int compile_option(int argc, char** argv);
static int run_option(int argc, char** argv);
static int compile_run_option(int argc, char** argv);

extern int main(int argc, char** argv) {
  std::string mode(argc >= 2 ? argv[1] : "");
  if (mode == "-c") {
    return compile_option(argc, argv);
  }

  if (mode == "-r") {
    return run_option(argc, argv);
  }

  if (mode == "-a") {
    return compile_run_option(argc, argv);
  }

  std::cerr << "ERROR: The running mode was expected as the first argument.\n"
    << "  1. '-c' => Compile\n"
    << "  2. '-r' => Run bytecode\n"
    << "  3. '-a' => Compile and run\n";
  return 1;
}

static int compile_option(int argc, char** argv) {
  if (argc < 4) {
    std::cerr << "ERROR: The paths to the input (.lk) and output (.lkc) files were expected after '-c'.\n";
    return 1;
  }

  demo::compiler(argv[2], argv[3])
    .compile();
  return 0;
}

static int run_option(int argc, char** argv) {
  if (argc < 3) {
    std::cerr << "ERROR: The path to the loki bytecode (.lkc) file was expected after '-r'.\n";
    return 1;
  }

  loki::virtual_machine(argv[2])
    .evaluate();
  return 0;
}

static int compile_run_option(int argc, char** argv) {
  if (argc < 4) {
    std::cerr << "ERROR: The paths to the input (.lk) and output (.lkc) files were expected after '-a'.\n";
    return 1;
  }

  demo::compiler(argv[2], argv[3])
    .compile();

  loki::virtual_machine(argv[3])
    .evaluate();
  return 0;
}
