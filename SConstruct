env = Environment(CC = 'clang++')
env.Program('valc', Glob('valc.cpp'))
env.Append(CCFLAGS=['-lm'])
print('..Building sieve')
env.Program('sieve', Glob('sieve.c'))
env.Program('hashing', 'hashing.cpp')
