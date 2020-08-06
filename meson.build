project('option', 'c',
  default_options: [
  'warnlevel=3',
  'debug=true',
  'c_std=c11',
  'b_sanitize=address',
  ])

src = [
]

tests = [
  'test_option.c',
]

option_so = library('option', src)

option_dep = declare_dependency(link_with: option_so)

foreach test_src: tests
  bin = executable('bin' + test_src, 'tests/' + test_src,
    dependencies: [
      option_dep]
      )
  test('bin' + test_src, bin, args: [
    '--gtest_color=yes',
    ])
endforeach
