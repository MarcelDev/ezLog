project('ezlog', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

ezlog = declare_dependency(include_directories: [include_directories('include')])

executable('ezlog_example', 'example/loggers.cpp', dependencies: ezlog)