basic_test_plugin = library('basic_test_plugin', 'basic_plugin.c')
basic_test_exe = executable(
  'basic_test',
  'test.c',
  dependencies: tests_deps,
  include_directories: tests_include_dirs,
)

basic_test_conf = configuration_data()
basic_test_conf.set_quoted(
  'PLUGIN_PATH',
  basic_test_plugin.full_path(),
  description: 'The path to the plugin binary',
)
configure_file(output: 'config.h', configuration: basic_test_conf)
