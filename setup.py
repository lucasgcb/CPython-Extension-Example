import os
import sys

from setuptools import setup,Extension
from setuptools.command.install import install
#https://circleci.com/blog/continuously-deploying-python-packages-to-pypi-with-circleci/
# circleci.py version


module1 = Extension('pyextensions.lilterminal',
                    sources = ['src/pyextensions/lilterminal.c'])

module2 = Extension('pyextensions.mymath',
                    sources = ['src/pyextensions/mymath.c'])


VERSION = "0.2.0"

def readme():
    """print long description"""
    with open('README.rst') as f:
        return f.read()


class VerifyVersionCommand(install):
    """Custom command to verify that the git tag matches our version"""
    description = 'verify that the git tag matches our version'

    def run(self):
        tag = os.getenv('CIRCLE_TAG')

        if tag != VERSION:
            info = "Git tag: {0} does not match the version of this app: {1}".format(
                tag, VERSION
            )
            sys.exit(info)


setup (name = 'pyextensions',
       version = VERSION,
       description = 'This is a demo package for C extensions. It implements a little terminal interface and some math',
       url="https://github.com/lucasgcb/CPython-Extensions",
       license="WTFPL",
       packages=["pyextensions"],
       package_dir = {'': 'src'},
       classifiers=[
        "Development Status :: 5 - Production/Stable",
        "Intended Audience :: Developers",
        "Intended Audience :: System Administrators",
        "License :: OSI Approved :: MIT License",
        "Operating System :: POSIX :: Linux",
        "Programming Language :: Python :: 3",
       ],
	   python_requires='>=3',
       ext_modules = [ module1,
       		           module2 ],
       cmdclass={
        'verify': VerifyVersionCommand,
            }
       )
