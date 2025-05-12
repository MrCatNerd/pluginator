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

src_files = ['pluginator.c']
include_dirs = [include_directories('.')]
deps = []

hashmap_c_dep = dependency('hashmap.c')
deps = [hashmap_c_dep, cc.find_library('dl')]

pluginator_lib = static_library(
  'pluginator',
  src_files,
  dependencies: deps,
  include_directories: include_dirs,
  c_args: ['-rdynamic', '-D_GNU_SOURCE'],
)

pluginator_dep = declare_dependency(
  link_with: pluginator_lib,
  include_directories: include_dirs,
  dependencies: deps,
)

# unit tests
if not meson.is_subproject()
  subdir('tests')
endif
