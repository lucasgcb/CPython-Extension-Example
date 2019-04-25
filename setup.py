from distutils.core import setup, Extension
import os
module1 = Extension('pyextensions.lilterminal',
                    sources = ['src/pyextensions/lilterminal.c'])

module2 = Extension('pyextensions.mymath',
                    sources = ['src/pyextensions/mymath.c'])

setup (name = 'pyextensions',
       version = '1.0',
       description = 'This is a demo package for C extensions. It implements a little terminal interface and some math',
       packages=["pyextensions"],
       package_dir = {'': 'src'},
       ext_modules = [ module1,
       		  module2 ],)
