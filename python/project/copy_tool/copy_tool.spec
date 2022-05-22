# -*- mode: python ; coding: utf-8 -*-

block_cipher = None


<<<<<<< HEAD
a = Analysis(['copy_tool.py'],
=======
a = Analysis(['copy_tool.py', 'D:\\Github\\Storage\\python\\libary\\entrywithplaceholder.py'],
>>>>>>> 1d36228e2a4f62604d4c94b336da5b53ed28546e
             pathex=['D:\\Github\\Storage\\python\\project\\copy_tool'],
             binaries=[],
             datas=[],
             hiddenimports=[],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
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
          name='copy_tool',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          upx_exclude=[],
          runtime_tmpdir=None,
          console=False )
