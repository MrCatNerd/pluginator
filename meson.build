project(
  'pluginator',
  'c',
  version: run_command('cat', join_paths(meson.project_source_root(), 'VERSION'), check: true).stdout().strip(),
  default_options: [
    'warning_level=3',
    'debug=false',
    'buildtype=release',
  ],
)

cc = meson.get_compiler('c')

src_files = ['main.c', 'pluginator.c']
include_dirs = [include_directories('.')]

pluginator_lib = static_library(
  'pluginator',
  src_files,
  include_directories: include_dirs,
  c_args: ['-rdynamic', '-D_GNU_SOURCE'],
)

pluginator_dep = declare_dependency(
  link_with: pluginator_lib,
  include_directories: include_dirs,
  dependencies: cc.find_library('dl'),
)

# unit tests
if not meson.is_subproject()
  subdir('tests')
endif
