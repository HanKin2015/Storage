import os,sys
import usb.core
import usb.util
import usb.control
import logging
 
import usb.backend.libusb1 as libusb1
import usb.backend.libusb0 as libusb0
import usb.backend.openusb as openusb
 
from usb.libloader import *
 
_LOGGER = logging.getLogger(__name__)
 
os.environ['PYUSB_DEBUG'] = 'debug'
 
def _load_locate_library_ex(candidates, cygwin_lib, name,
                        win_cls=None, cygwin_cls=None, others_cls=None,
                        find_library=None):
    """Locates and loads a library.
    Returns: the loaded library
    arguments:
    * candidates    -- candidates list for locate_library()
    * cygwin_lib    -- name of the cygwin library
    * name          -- lib identifier (for logging). Defaults to None.
    * win_cls       -- class that is used to instantiate the library on
                       win32 platforms. Defaults to None (-> ctypes.CDLL).
    * cygwin_cls    -- library class for cygwin platforms.
                       Defaults to None (-> ctypes.CDLL).
    * others_cls    -- library class for all other platforms.
                       Defaults to None (-> ctypes.CDLL).
    * find_library  -- see locate_library(). Defaults to None.
    raises:
    * NoLibraryCandidatesException
    * LibraryNotFoundException
    * LibraryNotLoadedException
    * LibraryMissingSymbolsException
    """
    if sys.platform == 'cygwin':
        if cygwin_lib:
            loaded_lib = load_library(cygwin_lib, name, cygwin_cls)
        else:
            raise NoLibraryCandidatesException(name)
    elif candidates:
        lib = locate_library(candidates, find_library)
        if lib:
            if sys.platform == 'win32':
                loaded_lib = load_library(lib, name, win_cls)
            else:
                loaded_lib = load_library(lib, name, others_cls)
            _LOGGER.info('{}'.format(loaded_lib))
        else:
            _LOGGER.info('%r could not be found', (name or candidates))
            raise LibraryNotFoundException(name)
    else:
        raise NoLibraryCandidatesException(name)
 
    if loaded_lib is None:
        raise LibraryNotLoadedException(name)
    else:
        return loaded_lib
 
 
def _load_library_ex(find_library=None):
    return _load_locate_library_ex(
                ('usb-0.1', 'usb', 'libusb0'),
                'cygusb0.dll', 'Libusb0',
                find_library=find_library
    )
 
def _get_backend_ex():
    try:
        if libusb0._lib is None:
            _LOGGER.info('_get_backend_ex(): using backend "%s"' % libusb0.__name__)
            libusb0._lib = _load_library_ex()#find_library
            libusb0._setup_prototypes(libusb0._lib)
            libusb0._lib.usb_init()
        return libusb0._LibUSB()
    except usb.libloader.LibraryException:
        # exception already logged (if any)
        _LOGGER.error('Error loading libusb 0.1 backend')
        return None
    except Exception:
        _LOGGER.error('Error loading libusb 0.1 backend')
        return None
 
def my_get_backend_ex():
 
    for m in (libusb1, openusb, libusb0):
        backend = m.get_backend()
        if backend is not None:
            _LOGGER.info('my_get_backend_ex(): using backend "%s"' % m.__name__)
            break
        elif m == libusb0:
            backend = _get_backend_ex()
            if backend is not None: break
    else:
        raise ('No backend available')
 
    return backend
 
 
def testFind():
    backend = my_get_backend_ex()
    print(backend)
    print(list(usb.core.find(find_all=True, backend=backend)))
 
if __name__ == '__main__':
    testFind()