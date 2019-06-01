from distutils.core import setup, Extension

spam = Extension('spam',
                    sources = ['spammodule.c'])

setup (name = 'spam',
       version = '1.0',
       description = 'This is a spam demo package',
       ext_modules = [spam])
