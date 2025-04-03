import FWCore.ParameterSet.Config as cms

from Configuration.Generator.Pyquen2025Settings_cff import *
from GeneratorInterface.Core.ExternalGeneratorFilter import ExternalGeneratorFilter

import sys, os
# Check if variable "energy" is defined in the main script
if "energy" in sys.modules["__main__"].__dict__:
    energy = sys.modules["__main__"].__dict__["energy"]
else: energy = os.getenv("HJENERGY", "5362")

generator = ExternalGeneratorFilter(cms.EDFilter("HydjetGeneratorFilter",
                         locals()[f"collisionParameters{energy}GeV"],   #tune CELLO
                         locals()[f"qgpParameters{energy}GeV"],         #tune CELLO
                         locals()[f"hydjetParameters{energy}GeV"],      #tune CELLO
                         hydjetMode = cms.string('kHydroQJets'),
                         PythiaParameters = cms.PSet(pyquenPythiaDefaultBlock,
                                                     # Quarkonia and Weak Bosons added back upon dilepton group's request.
                                                     parameterSets = cms.vstring('pythiaUESettings',
                                                                                 'hydjetPythiaDefault'+energy, #tune CELLO
                                                                                 'myParameters',
                                                                                 'pythiaJets',
                                                                                 'pythiaPromptPhotons',
                                                                                 'pythiaZjets',
                                                                                 'pythiaBottomoniumNRQCD',
                                                                                 'pythiaCharmoniumNRQCD',
                                                                                 'pythiaQuarkoniaSettings',
                                                                                 'pythiaWeakBosons'
                                                                                 )
                                                     ),
                         cFlag = cms.int32(1),
                         bMin = cms.double(0),
                         bMax = cms.double(22),
                         bFixed = cms.double(0)
                         ))
