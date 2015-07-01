from MitAna.TreeMod.bambu import mithep
import os
import sys

def goodLumiFilter(fileName, jsonDir = None):
    """
    Find the good lumi list JSON file and return a RunLumiSelectionMod instance.
    """

    if jsonDir is None:
        try:
            jsonDir = os.environ['MIT_JSON_DIR']
        except KeyError:
            print 'goodLumiFilter requires environment MIT_JSON_DIR to be set.'
            sys.exit(1)

    if type(fileName) is str:
        fileNames = [fileName]
    elif type(fileName) is list:
        fileNames = fileName
    else:
        print 'Invalid argument given as file name'
        sys.exit(1)

    mod = mithep.RunLumiSelectionMod()

    for name in fileNames:
        fullPath = jsonDir + '/' + name
        if not os.path.exists(fullPath):
            print 'Could not find json file', fullPath
            sys.exit(1)

        print 'Adding JSON file', fullPath
        mod.AddJSONFile(fullPath)

    return mod
