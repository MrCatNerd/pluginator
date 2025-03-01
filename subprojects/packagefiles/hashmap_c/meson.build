project('hashmap_c', 'c')
hashmap_c_lib = static_library(
  meson.project_name(),
  'hashmap.c',
)

hashmap_c_dep = declare_dependency(
  link_with: hashmap_c_lib,
  include_directories: [include_directories('.')],
)
