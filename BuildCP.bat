@echo off

rmdir /S /Q build
REM ~ python setup.py build --quiet
python setup.py bdist_msi
python setup.py install
python setup.py clean
rmdir /S /Q build
REM ~ python testMix.py