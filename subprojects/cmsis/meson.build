project('cmsis', 'c', version: '5.2.0')

src = ['cmsis_gcc.h',
       'cmsis_version.h',
       'cmsis_compiler.h',
       'mpu_armv7.h',
       'core_cm4.h',
       'stm32f303xe.h',
       'system_stm32f3xx.h']

incs = include_directories('.')
lib = static_library('cmsis', sources: src, include_directories: incs)
dep = declare_dependency(link_with: lib, include_directories: incs)
