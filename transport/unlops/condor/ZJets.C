#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <TArrayC.h>
#include <string>
#include "TH1.h"                  
#include "TH2D.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TVirtualPad.h"
#include "TApplication.h"
#include "TBranch.h"
#include "TBranchElement.h"
#include "TFile.h"                  
#include  <string>
#include  <map>
#include "TTree.h"                    
#include "TROOT.h"
#include <fstream>
#include <ostream>
#include "TMath.h"
#include "TFile.h"
#include "TChain.h"
#include "TAttMarker.h"
#include <TCanvas.h>
#include <sstream>
#include <stdio.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
//#include <bits/stdc++.h>
#include "TObject.h"

//g++ -g  -Wno-deprecated Gen_macro.C -o Gen_macro.exe  -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs`

using namespace std;
//using namespace CLHEP;

int main()
{
    return 0;
}

void ZJets(){

	//TFile *f = new TFile("/home/sobarman/t3store3/Generator/UNLOPS/date_23052021/dyee012j_5f_NLO_UNLOPS_23052021.root");
	//TFile *f = new TFile("/home/sobarman/t3store3/Generator/UNLOPS/date_26052021/dyee012j_5f_NLO_UNLOPS_26052021.root");	
	//TFile *f = new TFile("/home/sobarman/t3store3/Generator/UNLOPS/date_23052021/dyee012j_5f_NLO_FXFX_23052021.root");
	TFile *f = new TFile("/home/sobarman/t3store3/Generator/UNLOPS/Analysis/date_18112021/dyeej_2NLO3LO_5f_NLO_UNLOPS_24112021.root");
	//TFile *f = new TFile("/home/sobarman/t3store3/Generator/UNLOPS/Analysis/date_18112021/dyee012j_5f_NLO_FXFX_24112021.root");
      

	TTree *tree = (TTree*)f->Get("Events");
	
	//Int_t num = 1000000;
	Float_t genWeight;

	UInt_t nGenPart; //4292
	Float_t GenPart_pt[4292];
	Float_t GenPart_phi[4292];
	Float_t GenPart_eta[4292];
	Float_t GenPart_mass[4292];
	Int_t GenPart_pdgId[4292];
	Int_t GenPart_status[4292];
	
	UInt_t nGenJet;  // 22
	Float_t GenJet_pt[22];
	Float_t GenJet_eta[22];
	Float_t GenJet_phi[22];
	
	UInt_t nGenDressedLepton; // 4
	Float_t GenDressedLepton_pt[4];
	Float_t GenDressedLepton_eta[4];
	Float_t GenDressedLepton_phi[4];
	Float_t GenDressedLepton_mass[4];
	Int_t GenDressedLepton_pdgId[4];

	Float_t GenMET_pt;
	Float_t GenMET_phi;
	
	tree->SetBranchAddress("genWeight", &genWeight);
	tree->SetBranchAddress("nGenPart", &nGenPart);
	tree->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId);
	tree->SetBranchAddress("GenPart_status", &GenPart_status);
	tree->SetBranchAddress("GenPart_pt", &GenPart_pt);
	tree->SetBranchAddress("GenPart_eta", &GenPart_eta);
	tree->SetBranchAddress("GenPart_phi", &GenPart_phi);
	tree->SetBranchAddress("GenPart_mass", &GenPart_mass);
	
	tree->SetBranchAddress("nGenJet", &nGenJet);
	tree->SetBranchAddress("GenJet_pt", &GenJet_pt);
	tree->SetBranchAddress("GenJet_eta", &GenJet_eta);
	tree->SetBranchAddress("GenJet_phi", &GenJet_phi);
	
	tree->SetBranchAddress("nGenDressedLepton", &nGenDressedLepton);
	tree->SetBranchAddress("GenDressedLepton_pt", &GenDressedLepton_pt);
	tree->SetBranchAddress("GenDressedLepton_eta", &GenDressedLepton_eta);
	tree->SetBranchAddress("GenDressedLepton_phi", &GenDressedLepton_phi);
	tree->SetBranchAddress("GenDressedLepton_mass", &GenDressedLepton_mass);
	tree->SetBranchAddress("GenDressedLepton_pdgId", &GenDressedLepton_pdgId);

	tree->SetBranchAddress("GenMET_pt", &GenMET_pt);
        tree->SetBranchAddress("GenMET_phi", &GenMET_phi);

	//TH1F* pairPT_mg273 = new TH1F ("pairPT_mg273", "top quark pair PT", 20, 0, 200);
	//TH1F* PT_mg273 = new TH1F ("PT_mg273", "top quark PT", 20, 0, 400);
	
	TH1F* njet = new TH1F ("njet", "No. of jets", 10, 0, 10);
	TH1F* jetpt = new TH1F ("jetpt", "Pt of all jets", 60, 0, 600);
	TH1F* jeteta = new TH1F ("jeteta", "eta of all jets", 30, -5, 5);
	TH1F* jetphi = new TH1F ("jetphi", "Phi of all jets", 30, -3, 3);

	TH1F* jet1pt = new TH1F ("jet1pt", "Pt of leading jets", 60, 0, 600);
	TH1F* jet1eta = new TH1F ("jet1eta", "eta of leading jets", 30, -5, 5);
        TH1F* jet1phi = new TH1F ("jet1phi", "Phi of leading jets", 30, -3, 3);

	TH1F* jet2pt = new TH1F ("jet2pt", "Pt of sub-leading jets", 60, 0, 600);
        TH1F* jet2eta = new TH1F ("jet2eta", "eta of sub-leading jets", 30, -5, 5);
        TH1F* jet2phi = new TH1F ("jet2phi", "Phi of sub-leading jets", 30, -3, 3);

	TH1F* jet3pt = new TH1F ("jet3pt", "Pt of 3rd jets", 60, 0, 600);
        TH1F* jet3eta = new TH1F ("jet3eta", "eta of 3rd jets", 30, -5, 5);
        TH1F* jet3phi = new TH1F ("jet3phi", "Phi of 3rd jets", 30, -3, 3);
	
	TH1F* genpartpt = new TH1F ("genpartpt", "Pt of gen particles", 30, 0, 300);
        TH1F* genparteta = new TH1F ("genparteta", "eta of gen particles", 100, -5, 5);
        TH1F* genpartphi = new TH1F ("genpartphi", "Phi of gen particles", 100, -3, 3);
	
	TH1F* genleptonpt = new TH1F ("genleptonpt", "Pt of leptons", 20, 0, 200);
        TH1F* genleptoneta = new TH1F ("genleptoneta", "eta of leptons", 30, -5, 5);
        TH1F* genleptonphi = new TH1F ("genleptonphi", "Phi of leptons", 30, -3, 3);

	TH1F* metpt = new TH1F ("metpt", "pt of met", 20, 0, 200);
        TH1F* metphi = new TH1F ("metphi", "Phi of met", 30, -3, 3);

	TH1F* zmass = new TH1F ("zmass", "mass of z", 40, 0, 200);
	TH1F* zpt = new TH1F ("zpt", "pt of z", 60, 0, 600);
	TH1F* zeta = new TH1F ("zeta", "eta of z", 30, -5, 5);
	TH1F* zphi = new TH1F ("zphi", "phi of z", 30, -3, 3);

	TH1F* genwt_bf = new TH1F ("genwt_bf", "genwt_bf", 2, -1, 1);
        TH1F* genwt_af = new TH1F ("genwt_af", "genwt_af", 2, -1, 1);


	Long64_t nentries = tree->GetEntries();       
        //cout << "No. of Entries in the root file : " << nentries <<endl; 		      
	
	Int_t nevt = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
	//for (Long64_t jentry=0; jentry<1949564;jentry++) { // event loop starts
		tree->GetEntry(jentry);
		nevt++;
	//cout << "No. of events processed : "<<nevt<<endl;
	
	genwt_bf->Fill(genWeight);

	if (!std::isfinite(genWeight)) {
        	//std::cout << "Entry = " << myReader.GetCurrentEntry() << " *genWeight = " << *genWeight << std::endl;
                continue;}

	genwt_af->Fill(genWeight);
                
/*
// for all top and anti-top
		for(int igenpart=0; igenpart<nGenPart; igenpart++) { //gen loop
 			if( std::abs(GenPart_pdgId[igenpart]) == 6  && GenPart_status[igenpart] > 60 ) {   // check top and antitop quaark
				PT_mg273->Fill(GenPart_pt[igenpart]);
                		}
        
//for top pair
		for(int igenpart1=0; igenpart1<nGenPart-1; igenpart1++) {//gen loop
                        if(((GenPart_pdgId[igenpart1]) == 6 ||  (GenPart_pdgId[igenpart1]) == -6) && (GenPart_status[igenpart1] > 60 )){
                                for(int igenpart2=igenpart1+1; igenpart2<nGenPart; igenpart2++) {//gen loop
                                                if(((GenPart_pdgId[igenpart2]) == 6 ||  (GenPart_pdgId[igenpart2]) == -6) && GenPart_status[igenpart2] > 60 {
                                                        if(((GenPart_pdgId[igenpart1])*(GenPart_pdgId[igenpart2])) < 0){
                                                                        Float_t px1 = GenPart_pt[igenpart1]*cos(GenPart_phi[igenpart1]);
                                                                        Float_t py1 = GenPart_pt[igenpart1]*sin(GenPart_phi[igenpart1]);
                                                                        Float_t px2 = GenPart_pt[igenpart2]*cos(GenPart_phi[igenpart2]);
                                                                        Float_t py2 = GenPart_pt[igenpart2]*sin(GenPart_phi[igenpart2]);
                                                                        Float_t pt = sqrt(px1*px2 + py1*py2);
                                                                        pairPT_mg273->Fill(pt);
                                                                	}
                                                        	}
                                        		}
                                		}
                        		}
*/
		TLorentzVector el1, el2, el;

		for(int igenpart1=0; igenpart1<nGenDressedLepton; igenpart1++) { // z loop
        		if(((GenDressedLepton_pdgId[igenpart1]) == 11 ||  (GenDressedLepton_pdgId[igenpart1]) == -11)){
				el1.SetPtEtaPhiM(GenDressedLepton_pt[igenpart1], GenDressedLepton_eta[igenpart1], GenDressedLepton_phi[igenpart1], GenDressedLepton_mass[igenpart1]);
                		for(int igenpart2=igenpart1+1; igenpart2<nGenDressedLepton; igenpart2++){ 
                        			if(((GenDressedLepton_pdgId[igenpart2]) == 11 ||  (GenDressedLepton_pdgId[igenpart2]) == -11)){
							el2.SetPtEtaPhiM(GenDressedLepton_pt[igenpart2], GenDressedLepton_eta[igenpart2], GenDressedLepton_phi[igenpart2], GenDressedLepton_mass[igenpart2]);	
							el = (el1+el2);
                                			if(((GenDressedLepton_pdgId[igenpart1])*(GenDressedLepton_pdgId[igenpart2])) < 0){
									//el1.SetPtEtaPhiM(GenDressedLepton_pt[igenpart1], GenDressedLepton_eta[igenpart1], GenDressedLepton_phi[igenpart1], GenDressedLepton_mass[igenpart1]);
                                				        //el2.SetPtEtaPhiM(GenDressedLepton_pt[igenpart2], GenDressedLepton_eta[igenpart2], GenDressedLepton_phi[igenpart2], GenDressedLepton_mass[igenpart2]);
                                        				//el = (el1+el2);
                                                			zmass->Fill(el.M(),genWeight);
									zpt->Fill(el.Pt(),genWeight);
									zeta->Fill(el.Eta(),genWeight);
									zphi->Fill(el.Phi(),genWeight);
                                                			}	
                                				}
                        				}		
                				}
        				}

		for (int njets=0; njets<nGenJet; njets++){  // jet loop
			njet->Fill(njets,genWeight);
			jetpt->Fill(GenJet_pt[njets],genWeight);
			jeteta->Fill(GenJet_eta[njets],genWeight);
			jetphi->Fill(GenJet_phi[njets],genWeight);
			if (njets==0){
				jet1pt->Fill(GenJet_pt[njets],genWeight);
				jet1eta->Fill(GenJet_eta[njets],genWeight);
				jet1phi->Fill(GenJet_phi[njets],genWeight); 
				}
			if (njets==1){
				jet2pt->Fill(GenJet_pt[njets],genWeight);
                                jet2eta->Fill(GenJet_eta[njets],genWeight);
                                jet2phi->Fill(GenJet_phi[njets],genWeight);
				}
			if (njets==2){
                                jet3pt->Fill(GenJet_pt[njets],genWeight);
                                jet3eta->Fill(GenJet_eta[njets],genWeight);
                                jet3phi->Fill(GenJet_phi[njets],genWeight);
                                }
			}

		for (int igenpart=0; igenpart<nGenPart; igenpart++){  // gen particle loop
			genpartpt->Fill(GenPart_pt[igenpart],genWeight);
			genparteta->Fill(GenPart_eta[igenpart],genWeight);
			genpartphi->Fill(GenPart_phi[igenpart],genWeight);
			}
		
		for (int igenleptons=0;igenleptons<nGenDressedLepton; igenleptons++){ // gendressedlepton loop
			genleptonpt->Fill(GenDressedLepton_pt[igenleptons],genWeight);
			genleptoneta->Fill(GenDressedLepton_eta[igenleptons],genWeight);
			genleptonphi->Fill(GenDressedLepton_phi[igenleptons],genWeight);
			//if (igenleptons==2){
				//if(((GenDressedLepton_pdgId[igenleptons]) == 11) || ((GenDressedLepton_pdgId[igenleptons]) == -11)) {
				//	TLorentzVector mu1;
				//	mu1.SetPtEtaPhiM(GenDressedLepton_pt[0], GenDressedLepton_eta[0], GenDressedLepton_phi[0], GenDressedLepton_mass[0]);
				//	TLorentzVector mu2;
				//	mu2.SetPtEtaPhiM(GenDressedLepton_pt[1], GenDressedLepton_eta[1], GenDressedLepton_phi[1], GenDressedLepton_mass[1]);
				//	TLorentzVector mu = (mu1+mu2);
				//	if (((GenDressedLepton_pdgId[0])*(GenDressedLepton_pdgId[1])) < 0){
				//		zmass->Fill(mu.M(),genWeight);
				//		}
		//	}
		}
	//}

		metpt->Fill(GenMET_pt,genWeight);
		metphi->Fill(GenMET_phi,genWeight);
}//event loop

   	//TFile* of = TFile::Open("dyee012j_5f_NLO_UNLOPS_output_23052021.root", "RECREATE");
   	//TFile* of = TFile::Open("dyee012j_5f_NLO_UNLOPS_output_26052021_v2.root", "RECREATE");
	//TFile* of = TFile::Open("dyee012j_5f_NLO_FXFX_output_23052021.root", "RECREATE");
	//TFile* of = TFile::Open("output.root", "RECREATE");
	TFile* of = TFile::Open("dyeej_2NLO3LO_5f_NLO_UNLOPS_output_04012022.root", "RECREATE");
	//TFile* of = TFile::Open("dyee012j_5f_NLO_FXFX_output_14122021.root", "RECREATE");

   	//pairPT_mg273->Write();
   	//PT_mg273->Write();

   	njet->Write();
   	jetpt->Write();
   	jeteta->Write();
   	jetphi->Write();

	jet1pt->Write();
	jet1eta->Write();
	jet1phi->Write();

	jet2pt->Write();
        jet2eta->Write();
        jet2phi->Write();

	jet3pt->Write();
        jet3eta->Write();
        jet3phi->Write();
   	
	genpartpt->Write();
   	genparteta->Write();
   	genpartphi->Write();
	
	genleptonpt->Write();
	genleptoneta->Write();
	genleptonphi->Write();
	
	metpt->Write();
	metphi->Write();

	zmass->Write();
	zpt->Write();
	zeta->Write();
	zphi->Write();

	genwt_bf->Write();
        genwt_af->Write();
   	
	of->Close();

}
