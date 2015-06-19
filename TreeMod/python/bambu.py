import os

import ROOT
ROOT.gROOT.SetBatch(True)
ROOT.gSystem.Load('libMitAnaTreeMod.so')

class _Sequenceable(object):
    """
    Base class for objects that can be in a sequence or be a sequence itself
    """

    def __init__(self):
        pass

    def __add__(self, next):
        return _Bundle([self, next])

    def __mul__(self, next):
        return _Chain([self, next])

    def build(self, modlist = []):
        return ([], [])


class _Module(_Sequenceable):
    """
    PyROOT wrapper for mithep TAModules
    """

    def __init__(self, cls, *args, **kwargs):
        self._core = cls(*args)

        for key, value in kwargs.items():
            getattr(self._core, 'Set' + key)(value)

    def __getattr__(self, name):
        attr = getattr(self._core, name)
        setattr(self, name, attr)
        return attr

    def build(self, modlist = []):
        if self._core in modlist:
            raise RuntimeError('Module ' + self._core.GetName() + ' used multiple times')

        modlist.append(self._core)
        return ([self._core], [self._core])


class _Chain(_Sequenceable):
    """
    Linear sequence of sequenceables
    """
    
    def __init__(self, nodes):
        self._nodes = list(nodes)

    def build(self, modlist = []):
        head = []
        tail = []
        for node in self._nodes:
            hm, tm = node.build(modlist)
            if len(tail) != 0:
                for mod in hm:
                    tail[-1].Add(mod)

            tail = list(tm)

            if len(head) == 0:
                head = list(hm)

        return (head, tail)


class _Bundle(_Sequenceable):
    """
    List of parallel chains
    """

    def __init__(self, chains):
        self._chains = list(chains)

    def __mul__(self, next):
        raise RuntimeError("Cannot make a module dependent on two parallel chains")

    def build(self, modlist = []):
        head = []
        tail = []
        for chain in self._chains:
            hm, tm = chain.build(modlist)
            head += hm
            tail += tm

        return (head, tail)


class _ModClass(object):
    """
    Constructor class for mithep TAModules
    """

    def __init__(self, cls):
        self._cls = cls

    def __call__(self, *args, **kwargs):
        return _Module(self._cls, *args, **kwargs)


class _mithep(object):
    """
    PyROOT wrapper for mithep namespace
    """

    def __init__(self):
        self._core = ROOT.mithep

    def __getattr__(self, name):
        try:
            cls = getattr(self._core, name)
        except:
            # search in the standard library directory and find a possible match
            try:
                loaded = map(os.path.basename, ROOT.gSystem.GetLibraries('libMit', '', False).split())
    
                mangled = '_ZN6mithep'
                if '<' in name:
                    # templated class - can only deal with simple templates
                    op = name.find('<')
                    if name.rfind('<') != op:
                        raise Exception()
    
                    cl = name.find('>')
                    mangled += str(op) + 'INS_' + str(cl - op - 1) + name[op + 1:cl] + 'EE'
    
                else:
                    mangled += str(len(name)) + name

                mangled += '5ClassEv'
                    
                libdirs = os.environ['LD_LIBRARY_PATH'].split(':')
                for libdir in libdirs:
                    for libname in os.listdir(libdir):
                        if not libname.startswith('libMit') or libname in loaded:
                            continue
    
                        with open(libdir + '/' + libname, 'rb') as lib:
                            if lib.read().find(mangled) < 0:
                                continue
                      
                            print '(mithep): Auto-loading library', libname
                            ROOT.gSystem.Load(libname)
                            loaded.append(libname)
                            try:
                                cls = getattr(self._core, name)
                                break
                            except:
                                continue
                    else:
                        continue
    
                    break
                else:
                    raise Exception()

            except:
                raise RuntimeError('No class "' + name + '" found in namespace mithep. Perhaps a missing library?')

        try:
            if cls.Class().InheritsFrom(ROOT.mithep.BaseMod.Class()):
                cls = _ModClass(cls)
        except:
            pass

        setattr(self, name, cls)

        return cls

    def loadlib(self, package, module):
        ROOT.gSystem.Load('lib' + package + 'module' + '.so')


class _Analysis(object):
    """
    PyROOT wrapper for mithep::Analysis
    """

    def __init__(self):
        self._core = ROOT.mithep.Analysis()
        self._core.SetKeepHierarchy(False)

    def setSequence(self, seq):
        for mod in seq.build()[0]:
            self._core.AddSuperModule(mod)

    def __getattr__(self, name):
        attr = getattr(self._core, name)
        setattr(self, name, attr)
        return attr


mithep = _mithep()
analysis = _Analysis()
