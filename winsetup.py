from distutils.core import setup
import os
import os.path, sys
import shutil

# make sure dll exists
ale_c_lib = 'visual_studio\\x64\Release\\ale_python_interface.dll'
if not os.path.isfile(ale_c_lib):
    print('ERROR: Unable to find required dll, Please ensure you\'ve built ALE and the ale_python_interface projects')
    sys.exit()

# get dlls from dependencies
dll_files = os.listdir('visual_studio\dependencies\dll_win_x64')
# filter to make sure list only has dlls
dll_files = list(filter(lambda x: x[-3:] == 'dll', dll_files))
# copy dependency dlls
for dll in dll_files:
    shutil.copy('visual_studio\dependencies\dll_win_x64\\' + dll, 'ale_python_interface')

# copy compiled dll
shutil.copy(ale_c_lib, 'ale_python_interface')

setup(name = 'ale_python_interface',
      version='0.0.1',
      description = 'Arcade Learning Environment Python Interface',
      url='https://github.com/bbitmaster/ale_python_interface',
      author='Ben Goodrich',
      license='GPL',
      packages=['ale_python_interface'],
      package_dir={'ale_python_interface': 'ale_python_interface'},
      package_data={'ale_python_interface': ['*.dll']})

# remove dlls after setup
dll_files = os.listdir('ale_python_interface')
# filter to make sure list only has dlls
dll_files = list(filter(lambda x: x[-3:] == 'dll', dll_files))
# remove dlls
for dll in dll_files:
    os.remove('ale_python_interface\\'+ dll)
