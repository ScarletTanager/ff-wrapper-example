#!/usr/bin/env python

"""
setup.py file for SWIG example
"""

from distutils.core import setup, Extension


proto_module = Extension('_proto',
                         sources=['proto_wrap.c', '../../lib/proto.c'],
                         )

setup(name='proto',
      version='0.1',
      author="Sandy Cash",
      description="""Doing stuff with SWIG""",
      ext_modules=[proto_module],
      py_modules=["proto"],
      )
