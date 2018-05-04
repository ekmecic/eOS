project('eOS', 'c', default_options: ['c_std=c11'])

compilerArgs = ['-Wall',
                '-Wextra',
                '-Werror',
                '-Wduplicated-cond',
                '-Wlogical-op',
                '-Wnull-dereference',
                '-Wdouble-promotion',
                '-Wshadow',
                '-pedantic',
                '-ffreestanding',
                '-DSTM32F3']
add_project_arguments(compilerArgs, language: 'c')

linkerArgs = ['-T' + meson.current_source_dir() + '/src/startup/stm32f303re.ld']
add_project_link_arguments(linkerArgs, language: 'c')

inc = include_directories('src')

src = ['src/core/mem.h',
       'src/core/mem.c',
       'src/core/usart.h',
       'src/core/usart.c',
       'src/core/systick.h',
       'src/core/systick.c',
       'src/startup/startup.c',
       'src/startup/startup.h',
       'src/startup/interrupt_vector_table.h',
       'src/main.c',
      ]

# Libraries we're using: CMSIS (dep for libopencm3) and libopencm3
cmsis = subproject('cmsis')
libopencm3 = subproject('libopencm3')

elf = executable('eOS',
                 sources: src,
                 include_directories: inc,
                 dependencies: [libopencm3.get_variable('dep')])

bin = custom_target('eOS binary file',
                    input: elf,
                    output: 'eOS.bin',
                    command: ['arm-none-eabi-objcopy', '-O', 'binary', '@INPUT@', '@OUTPUT@'],
                    build_by_default: true)

stflash = find_program('st-flash')
run_target('flash', command: [stflash, '--reset', 'write', bin.full_path() , '0x08000000'], depends: bin)
run_target('erase', command: [stflash, 'erase'])
run_target('gdb', command: ['st-util'])
run_target('size', depends: elf, command: ['arm-none-eabi-size', elf.full_path()])
run_target('sections', depends: elf, command: ['arm-none-eabi-readelf', '--sections', elf.full_path()])
