import os

import ROOT
ROOT.gROOT.SetBatch(True)

class _mithep(object):
    """
    PyROOT wrapper for mithep namespace
    """

    def __init__(self):
        self._core = None

    def __getattr__(self, name):
        if not self._core:
            ROOT.gSystem.Load('libMitAnaTreeMod.so')
            self._core = ROOT.mithep

        try:
            obj = getatrr(self._core, name)
        except:
            # search in the standard library directory and find a possible match
            loaded = map(os.path.basename, ROOT.gSystem.GetLibraries('libMit', '', False).split())
            
            libdirs = os.environ['LD_LIBRARY_PATH'].split(':')
            for libdir in libdirs:
                for libname in os.listdir(libdir):
                    if not libname.startswith('libMit') or libname in loaded:
                        continue

                    with open(libdir + '/' + libname, 'rb') as lib:
                        if lib.read().find(name) < 0:
                            continue
                  
                        print '(mithep): Auto-loading library', libname
                        ROOT.gSystem.Load(libname)
                        try:
                            obj = getattr(self._core, name)
                            break
                        except:
                            continue
                else:
                    continue

                break
            else:
                raise RuntimeError('No object "' + name + '" found in namespace mithep. Perhaps a missing library?')

        setattr(self, name, obj)

        return obj


    def loadlib(self, package, module):
        ROOT.gSystem.Load('lib' + package + 'module' + '.so')


mithep = _mithep()
analysis = mithep.Analysis()
