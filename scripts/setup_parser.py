from setuptools import setup, find_packages

setup(
    name='parser', 
    version='1.0', 
    author='Recep Birol Gül',
    description='parser library L2-L4 Network packet parser',
    packages=find_packages(),
    setup_requires=["cffi>=1.0.0", "path.py"],
    cffi_modules=["build_parser.py:ffi_builder"],
    install_requires=["cffi>=1.0.0"]
)
