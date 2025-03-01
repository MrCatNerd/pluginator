no_dispatch_function_error_handling_test_plugin = library(
  'no_dispatch_function_error_handling_test_plugin',
  'plugin.c',
)
no_dispatch_function_error_handling_test_exe = executable(
  'no_dispatch_function_error_handling_test',
  'test.c',
  dependencies: tests_deps,
  include_directories: tests_include_dirs,
)

no_dispatch_function_error_handling_test_conf = configuration_data()
no_dispatch_function_error_handling_test_conf.set_quoted(
  'PLUGIN_PATH',
  no_dispatch_function_error_handling_test_plugin.full_path(),
  description: 'The path to the plugin binary',
)
configure_file(
  output: 'config.h',
  configuration: no_dispatch_function_error_handling_test_conf,
)
