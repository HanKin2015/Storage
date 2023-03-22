# -*- mode: python ; coding: utf-8 -*-

block_cipher = None


a = Analysis(['src\\USBCheck.py'],
             pathex=['D:\\Github\\Storage\\python\\udev\\USBCheck'],
             binaries=[],
             datas=[],
             hiddenimports=[],
             hookspath=[],
             runtime_hooks=[],
             excludes=['alabaster', 'altgraph', 'anaconda-client', 'anaconda-navigator', 'anaconda-project', 'appdirs', 'asn1crypto', 'astroid', 'astropy', 'astunparse', 'atomicwrites', 'attrs', 'autopep8', 'Babel', 'backcall', 'backports.functools-lru-cache', 'backports.os', 'backports.shutil-get-terminal-size', 'backports.tempfile', 'backports.weakref', 'baidu-aip', 'beautifulsoup4', 'bitarray', 'bkcharts', 'bleach', 'bokeh', 'boto', 'Bottleneck', 'capstone', 'certifi', 'cffi', 'chardet', 'Click', 'cloudpickle', 'clyent', 'colorama', 'commonmark', 'comtypes', 'concurrent-log-handler', 'conda', 'conda-build', 'conda-package-handling', 'conda-verify', 'contextlib2', 'cowsay', 'cryptography', 'cycler', 'Cython', 'cytoolz', 'dask', 'decorator', 'defusedxml', 'dill', 'distlib', 'distributed', 'docutils', 'entrypoints', 'et-xmlfile', 'Faker', 'fastcache', 'filelock', 'filetype', 'fire', 'Flask', 'freegames', 'fsspec', 'future', 'gevent', 'glob2', 'greenlet', 'h5py', 'HeapDict', 'html5lib', 'icon-font-to-png', 'idna', 'imageio', 'imagesize', 'imbalanced-learn', 'importlib-metadata', 'ipykernel', 'ipython', 'ipython_genutils', 'ipywidgets', 'isort', 'itsdangerous', 'jdcal', 'jedi', 'Jinja2', 'joblib', 'json5', 'jsonschema', 'jupyter', 'jupyter-client', 'jupyter-console', 'jupyter-core', 'jupyterlab', 'jupyterlab-server', 'jupyterthemes', 'keyring', 'kiwisolver', 'lazy-object-proxy', 'lesscpy', 'libarchive-c', 'lightgbm', 'llvmlite', 'locket', 'lxml', 'MarkupSafe', 'matplotlib', 'mccabe', 'menuinst', 'mistune', 'mkl-fft', 'mkl-random', 'mkl-service', 'mlxtend', 'mock', 'more-itertools', 'MouseInfo', 'mpmath', 'msgpack', 'multipledispatch', 'navigator-updater', 'nbconvert', 'nbformat', 'networkx', 'nltk', 'nose', 'notebook', 'numba', 'numexpr', 'numpy', 'numpydoc', 'olefile', 'opencv-python', 'openpyxl', 'packaging', 'palettable', 'pandas', 'pandocfilters', 'parso', 'partd', 'path.py', 'pathlib2', 'patsy', 'pefile', 'pep8', 'pgzero', 'pickleshare', 'Pillow', 'pip', 'pipenv', 'pkginfo', 'platformdirs', 'plotly', 'pluggy', 'ply', 'portalocker', 'prometheus-client', 'prompt-toolkit', 'psutil', 'py', 'pyasn1', 'PyAutoGUI', 'pycodestyle', 'pycosat', 'pycparser', 'pycrypto', 'pycurl', 'pyflakes', 'pygame', 'PyGetWindow', 'Pygments', 'PyInstaller', 'pylint', 'PyMsgBox', 'pyodbc', 'pyOpenSSL', 'pyparsing', 'pyperclip', 'pypiwin32', 'pypng', 'PyQRCode', 'pyreadline', 'PyRect', 'pyrsistent', 'PyScreeze', 'pyshark', 'PySide6', 'PySocks', 'pytesseract', 'pytest', 'pytest-arraydiff', 'pytest-astropy', 'pytest-doctestplus', 'pytest-openfiles', 'pytest-remotedata', 'python-dateutil', 'pyttsx3', 'pytweening', 'pytz', 'pyusb', 'PyWavelets', 'pywin32', 'pywin32-ctypes', 'pywinpty', 'PyYAML', 'pyzbar', 'pyzmq', 'qrcode', 'QtAwesome', 'qtconsole', 'QtPy', 'recommonmark', 'requests', 'rich', 'rope', 'rsa', 'ruamel_yaml', 'scikit-image', 'scikit-learn', 'scipy', 'seaborn', 'selenium', 'Send2Trash', 'setuptools', 'shiboken6', 'simplegeneric', 'singledispatch', 'six', 'snowballstemmer', 'sortedcollections', 'sortedcontainers', 'soupsieve', 'sourceinspect', 'speedtest-cli', 'Sphinx', 'sphinx-rtd-theme', 'sphinxcontrib-applehelp', 'sphinxcontrib-devhelp', 'sphinxcontrib-htmlhelp', 'sphinxcontrib-jsmath', 'sphinxcontrib-qthelp', 'sphinxcontrib-serializinghtml', 'sphinxcontrib-websupport', 'spyder', 'spyder-kernels', 'SQLAlchemy', 'statsmodels', 'stylecloud', 'sympy', 'tables', 'taichi', 'tblib', 'tenacity', 'termcolor', 'terminado', 'testpath', 'threadpoolctl', 'tifffile', 'tinycss', 'toolz', 'torch', 'torchvision', 'tornado', 'tqdm', 'traitlets', 'typing_extensions', 'unicodecsv', 'unrar', 'urllib3', 'virtualenv', 'virtualenv-clone', 'wcwidth', 'webencodings', 'Werkzeug', 'wheel', 'widgetsnbextension', 'win-inet-pton', 'win-unicode-console', 'win10toast', 'wincertstore', 'windnd', 'WMI', 'wordcloud', 'workbook', 'wrapt', 'xgboost', 'xlrd', 'XlsxWriter', 'xlutils', 'xlwings', 'xlwt', 'xmltodict', 'you-get', 'zict', 'zipp', 'zxing'],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher,
             noarchive=False)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          a.binaries,
          a.zipfiles,
          a.datas,
          [],
          name='USBCheck',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          upx_exclude=[],
          runtime_tmpdir=None,
          console=False , version='doc\\file_version_info.txt', icon='img\\USBCheck.ico')
