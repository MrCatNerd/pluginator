# setup common variables
tests_include_dirs = [include_directories('.')]
tests_deps = [pluginator_dep]

# basic test
subdir('basic')
test('basic test', basic_test_exe, args: [])
subdir('basic_dispatch')
test('basic dispatch test', basic_dispatch_test_exe, args: [])
subdir('no_plugin_error_handling')
test('no plugin error handling test', no_plugin_error_handling_test_exe, args: [])
