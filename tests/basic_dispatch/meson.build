basic_dispatch_plugin = library('basic_dispatch_plugin', 'basic_plugin.c')
basic_dispatch_test_exe = executable(
  'basic_dispatch',
  'test.c',
  dependencies: tests_deps,
  include_directories: tests_include_dirs,
)

basic_dispatch_conf = configuration_data()
basic_dispatch_conf.set_quoted(
  'PLUGIN_PATH',
  basic_dispatch_plugin.full_path(),
  description: 'The path to the plugin binary',
)
configure_file(output: 'config.h', configuration: basic_dispatch_conf)
