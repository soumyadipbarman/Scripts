#include "TMath.h"
#include "TFile.h"
#include "TH1F.h"
#include "TChain.h"
#include "TAttMarker.h"
#include <TCanvas.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

int OpenTChain(std::string listFileName, TChain *chain, int nFileMax = -1)
{
    std::ifstream inFileList;
    inFileList.open(listFileName.c_str());

    std::string inFileName;


    int nFile = 0;

    while(std::getline(inFileList, inFileName))
    {
        char inFileName_mod[1000];

        if(inFileName.find("/eos/cms") == 0)
        {
            sprintf(inFileName_mod, "root://eoscms.cern.ch/%s", inFileName.c_str());
        }

        else
        {
            sprintf(inFileName_mod, "%s", inFileName.c_str());
        }

        printf("Checking file: %s \n", inFileName_mod);
        TFile *inFile = (TFile*) TFile::Open(inFileName_mod);

        if(inFile && !inFile->IsZombie())
        {
            printf("Adding to chain...\n");

            chain->Add(inFileName_mod);

            inFile->Close();

            nFile++;
        }

        if(nFileMax > 0 && nFile >= nFileMax)
        {
            break;
        }
    }


    return 0;
}

void hist_maker_1(){
gROOT->Reset();



TH1F *LeadJet_pt = new TH1F("LeadJet_pt","LeadJet_pt",100 ,0  ,1500 );
TH1F *LeadJet_eta = new TH1F("LeadJet_eta", "LeadJet_eta", 100, -5.0, 5.0);
TH1F *Nvtx = new TH1F("Nvtx", "Nvtx", 100, 0, 100);



const Int_t XBINS1 = 32;
Double_t xEdges1[XBINS1 + 1] = {0 ,10 , 20, 30 ,40 ,50 , 60 ,70 ,80, 90, 100, 110, 120 ,130, 140 ,150, 160, 170, 180, 190,200,210,220,230,240,250, 260,270, 280,290,300,350,500};

const Int_t XBINS3 = 40;
Double_t xEdges3[XBINS3 + 1] = {0 ,10 , 20, 30 ,40 ,50 , 60 ,70 ,80, 90, 100, 110, 120 ,130, 140 ,150, 160, 170, 180, 190,200,210,220,230,240,250, 260,270, 280,290,300,350,400, 450,500,550,600,700,800,1000, 1500};

TH1F *RawMET_pt = new TH1F("RawMET_pt", "RawMET_pt", XBINS1 , xEdges1);
TH1F *PFMET_pt = new TH1F("PFMET_pt", "PFMET_pt",  XBINS1 , xEdges1);
TH1F *PuppiMET_pt = new TH1F("PuppiMET_pt", "PuppiMET_pt", XBINS1 , xEdges1);

TH1F *lead_pt = new TH1F("lead_pt", "lead_pt", XBINS3 , xEdges3);
TH1F *sublead_pt = new TH1F("sublead_pt", "sublead_pt", XBINS3 , xEdges3);

TH1F *diele_mass = new TH1F("diele_mass", "diele_mass", 20 ,81 , 101);


const Int_t XBINS4 = 46;
Double_t xEdges4[XBINS4 + 1] = {-400, -300, -250, -200, -190, -180, -170, -160, -150, -140, -130, -120, -110, -100, -90, -80, -70, -60, -50, -40, -30, -20, -10, 0 ,10 , 20, 30 ,40 ,50 , 60 ,70 ,80, 90, 100, 110, 120 ,130, 140 ,150, 160, 170, 180, 190,200, 250, 300, 400};

TH1F *RawUper = new TH1F("RawUper", "RawUper", XBINS4 , xEdges4);
TH1F *RawUpar = new TH1F("RawUpar", "RawUpar", XBINS4 , xEdges4);

TH1F *PFUper = new TH1F("PFUper", "PFUper", XBINS4 , xEdges4);
TH1F *PFUpar = new TH1F("PFUpar", "PFUpar", XBINS4 , xEdges4);

TH1F *PUper = new TH1F("PUper", "PUper", XBINS4 , xEdges4);
TH1F *PUpar = new TH1F("PUpar", "PUpar", XBINS4 , xEdges4);


Int_t ps50=1, ps75=1, ps90=1, ps120=1, ps165=1;
TChain *fchain = new TChain("Events");
OpenTChain("TXT_Data_file_name/TTZToLL_Zee.txt", fchain);
if (fchain == 0) return;
Long64_t nentries = fchain->GetEntries();
fchain->SetMakeClass(1);


Float_t uparapf, uparapu, uparar;
Float_t uperpf, uperpu, uperr;
Int_t nv;
UInt_t nJet;
Float_t mee;
Float_t pt_1, pt_2;
Float_t px, py;
Float_t pt;
Float_t pfpt, ppt, rpt;
Float_t pfphi, pphi, rphi;


 //fchain->SetBranchAddress("nJet", &nJet);
 //fchain->SetBranchAddress("ele_lead_pt", &pt_1);
 //fchain->SetBranchAddress("ele_sublead_pt", &pt_2);


 fchain->SetBranchAddress("PV_npvsGood", &nv);
 fchain->SetBranchAddress("diele_mass", &mee);


 fchain->SetBranchAddress("PuppiMET_pt", &ppt );
 fchain->SetBranchAddress("MET_pt", &pfpt);
 fchain->SetBranchAddress("RawMET_pt", &rpt);


 fchain->SetBranchAddress("PuppiMET_phi", &pphi );
 fchain->SetBranchAddress("MET_phi", &pfphi);
 fchain->SetBranchAddress("RawMET_phi", &rphi);


// fchain->SetBranchAddress("uparallel_PFMET",&uparapf);
// fchain->SetBranchAddress("uparpendicular_PFMET", &uperpf);


// fchain->SetBranchAddress("uparallel_PuppiMET", &uparapu);
// fchain->SetBranchAddress("uparpendicular_PuppiMET",&uperpu);


// fchain->SetBranchAddress("uparallel_RawMET",&uparar);
// fchain->SetBranchAddress("uparpendicular_RawMET",&uperr);
 
 
 fchain->SetBranchAddress("ele_px", &px);
 fchain->SetBranchAddress("ele_py", &py);


Long64_t count;
// cout << n1 << endl;
float wt;
for (Long64_t jentry=0; jentry<nentries;jentry++) {
fchain->GetEntry(jentry);
if(mee > 0)
{
pt = sqrt((px*px)+(py*py));
count = count + 1;
if (count%10000 == 0)
{
std::cout << "*****************************************************************" << std::endl;
std::cout << "*                                                               *" << std::endl;
std::cout << "*           Congrats 10000 events done successfully             *" << std::endl;
std::cout << "*                                                               *" << std::endl;
std::cout << "*****************************************************************" << std::endl;
}
//lead_pt->Fill(pt_1);
//sublead_pt->Fill(pt_2);
//(-pfmet_px-ele_px)*ele_px+(-pfmet_py-ele_py)*ele_py)/ele_pt


uparapf = ( (-pfpt*cos(pfphi) - px)*px + (-pfpt*sin(pfphi) - py)*py )/pt + pt;
uparapu = ( (-ppt*cos(pphi)   - px)*px + (-ppt*sin(pphi)   - py)*py )/pt + pt;
uparar  = ( (-rpt*cos(rphi)   - px)*px + (-rpt*sin(rphi)   - py)*py )/pt + pt;


//uparpendicular_pf= ((-pfmet_px-ele_px)*ele_py-(-pfmet_py-ele_py)*ele_px)/ele_pt


uperpf = ( (-pfpt*cos(pfphi) - px)*py - (-pfpt*sin(pfphi) - py)*px )/pt;
uperpu = ( (-ppt*cos(pphi)   - px)*py - (-ppt*sin(pphi)   - py)*px )/pt;
uperr  = ( (-rpt*cos(rphi)   - px)*py - (-rpt*sin(rphi)   - py)*px )/pt;


//diele_mass->Fill(mee);
//Nvtx->Fill(nv);


RawUpar->Fill(uparar); 
RawUper->Fill(uperr); 


PFUpar->Fill(uparapf); 
PFUper->Fill(uperpf); 


PUpar->Fill(uparapu); 
PUper->Fill(uperpu); 


/*RawMET_pt->Fill(rpt); 
PFMET_pt->Fill(pfpt); 
PuppiMET_pt->Fill(ppt);*/


}
}


TFile f("New_TTZToLL.root","recreate");
//Nvtx->Write();

//diele_mass->Write();
//lead_pt->Write();
//sublead_pt->Write();

//RawMET_pt->Write();
//PFMET_pt->Write();
//PuppiMET_pt->Write();

RawUper->Write();
RawUpar->Write();

PFUper->Write();
PFUpar->Write();

PUper->Write();
PUpar->Write();


return 0;
if (gROOT->IsBatch()) return;
}





