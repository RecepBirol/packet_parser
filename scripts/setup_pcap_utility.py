from setuptools import setup, find_packages

setup(
    name='pcap_utility', 
    version='1.0', 
    author='Recep Birol Gül',
    description='libpcap wrapper, utility for capture network packets',
    packages=find_packages(),
    setup_requires=["cffi>=1.0.0", "path.py"],
    cffi_modules=["build_pcap_utility.py:ffi_builder"],
    install_requires=["cffi>=1.0.0"]
)
