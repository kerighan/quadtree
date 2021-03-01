from setuptools import setup, find_packages, Extension
from glob import glob
import pybind11


extension_kwargs = dict(
        language='c++',
        include_dirs=[
            pybind11.get_include(),
            pybind11.get_include(True)],
        extra_compile_args=["-Ofast"])


ext_modules = [
    Extension('quadtree', sorted(glob("src/*.cpp")), **extension_kwargs)
]


setup(
    name="quadtree",
    version="0.0.0",
    packages=find_packages(),
    include_package_data=True,
    ext_modules=ext_modules
)
