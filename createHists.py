#USAGE : python createHists.py --in input.root --out output.root 
import os
import sys
import optparse
import ROOT
import math

from ROOT import TH1F, TFile, TTree, TLorentzVector, TVectorD
from optparse import OptionParser
from math import cos, sin, sinh
MW_=80.379

class extend_p4:
  p4_vector=ROOT.TLorentzVector()
  pdgid=11
  def __init__(self, ltvector, pid):
    self.p4_vector=ltvector
    self.pdgid=pid

def main():
  usage = 'usage: %prog [options]'
  parser = optparse.OptionParser(usage)
  parser.add_option('-i', '--in', dest='inputfiles', help='name of input files', default=None, type='string')
  parser.add_option('-o', '--out', dest='outputfiles', help='name output files', default=None, type='string')
  (opt, args) = parser.parse_args()

  histo_array = {}
  
  h_weight = TH1F('weight','weight',2,-1,1)
  #LHE histos
  h_Zpt_LHE = TH1F('Zpt_LHE', 'Zpt_LHE', 100, 0, 500)
  h_Zmass_LHE = TH1F('Zmass_LHE', 'Zmass_LHE', 75, 0, 1500)
  #GEN histos
  h_Zpt_GEN = TH1F('Zpt_GEN', 'Zpt_GEN', 30, 0, 300)
  h_Zmass_GEN = TH1F('Zmass_GEN', 'Zmass_GEN', 40, 0, 200)
  h_Zeta_GEN = TH1F('Zeta_GEN', 'Zeta_GEN', 30, -5, 5)
  h_Zphi_GEN = TH1F('Zphi_GEN', 'Zphi_GEN', 30, -3, 3)
  h_njet_GEN = TH1F('njet_GEN', 'njet_GEN', 10, 0, 10) 

  #add histos
  histo_array['h_weight']=h_weight
  histo_array['h_Zpt_LHE']=h_Zpt_LHE
  histo_array['h_Zmass_LHE']=h_Zmass_LHE
  histo_array['h_Zpt_GEN']=h_Zpt_GEN
  histo_array['h_Zmass_GEN']=h_Zmass_GEN
  histo_array['h_Zeta_GEN']=h_Zeta_GEN
  histo_array['h_Zphi_GEN']=h_Zphi_GEN
  histo_array['h_njet_GEN']=h_njet_GEN

  for key in histo_array:
    histo_array[key].SetStats(0)
    histo_array[key].Sumw2()
    histo_array[key].GetYaxis().SetTitle("a.u.")
    histo_array[key].GetYaxis().SetTitleSize(0.05);
    histo_array[key].GetYaxis().SetTitleOffset(0.75);
    histo_array[key].GetXaxis().SetTitle(key)
    histo_array[key].SetMinimum(0)

  if not os.path.isfile(opt.inputfiles): 
    print 'inputfile does not exist'
  filein=TFile.Open(opt.inputfiles)
  treein=filein.Get('Events')
  npos=treein.GetEntries('genWeight>0')
  nneg=treein.GetEntries('genWeight<0')
  h_weight.SetBinContent(1,nneg)
  h_weight.SetBinContent(2,npos)
  
  for entry in range(0,treein.GetEntries()):
    p4temp = TLorentzVector()
    LHEzp4 = TLorentzVector()
    GENzp4 = TLorentzVector()
    LHElep = []
    GENDressLep = []

    treein.GetEntry(entry)
    weight=(treein.genWeight)/(abs(treein.genWeight))
    njets=treein.nGenJet

    #LHE info
    for iLHE in range(2,treein.nLHEPart):
      if not (abs(treein.LHEPart_pdgId[iLHE])==11 or abs(treein.LHEPart_pdgId[iLHE])==13): continue
      p4temp.SetPtEtaPhiM(treein.LHEPart_pt[iLHE], treein.LHEPart_eta[iLHE], treein.LHEPart_phi[iLHE], treein.LHEPart_mass[iLHE])
      LHElep.append(p4temp.Clone())

    if len(LHElep)==2: 
      LHEzp4 = LHElep[0]+LHElep[1]
      histo_array['h_Zpt_LHE'].Fill(LHEzp4.Pt(), weight)
      histo_array['h_Zmass_LHE'].Fill(LHEzp4.M(), weight)

    for idressedlep in range(0, treein.nGenDressedLepton):
      if treein.GenDressedLepton_hasTauAnc[idressedlep]: continue
      p4temp.SetPtEtaPhiM(treein.GenDressedLepton_pt[idressedlep],treein.GenDressedLepton_eta[idressedlep],treein.GenDressedLepton_phi[idressedlep],treein.GenDressedLepton_mass[idressedlep])
      GENDressLep.append(extend_p4(p4temp.Clone(), treein.GenDressedLepton_pdgId[idressedlep]))
      GENDressLep.sort(key=lambda x: x.p4_vector.Pt(), reverse=True)

    if len(GENDressLep)==2:
      GENzp4=GENDressLep[0].p4_vector+GENDressLep[1].p4_vector
      histo_array['h_Zpt_GEN'].Fill(GENzp4.Pt(), weight)
      histo_array['h_Zmass_GEN'].Fill(GENzp4.M(), weight)
      histo_array['h_Zeta_GEN'].Fill(GENzp4.Eta(), weight)
      histo_array['h_Zphi_GEN'].Fill(GENzp4.Phi(), weight)

    #for ijet in range(0, treein.nGenJet):
    histo_array['h_njet_GEN'].Fill(njets, weight)

  fileout=TFile.Open(opt.outputfiles,'RECREATE')
  fileout.cd()

  for key in histo_array:
    histo_array[key].Write()
  fileout.Close()

if __name__ == "__main__":
  sys.exit(main())
