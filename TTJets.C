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

using namespace std;

void TTJets(){

	TFile *f = new TFile("input.root");

	TTree *tree = (TTree*)f->Get("Events");
	
	Float_t genWeight;
	UInt_t nGenPart; //4274
	Float_t GenPart_pt[4615];
	Float_t GenPart_phi[4615];
	Int_t GenPart_pdgId[4615];
	Int_t GenPart_status[4615];
	
	tree->SetBranchAddress("genWeight", &genWeight);
	tree->SetBranchAddress("nGenPart", &nGenPart);
	tree->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId);
	tree->SetBranchAddress("GenPart_status", &GenPart_status);
	tree->SetBranchAddress("GenPart_pt", &GenPart_pt);
	tree->SetBranchAddress("GenPart_phi", &GenPart_phi);

	TH1F* pairPT_mg273 = new TH1F ("pairPT_mg273", "top quark pair PT", 20, 0, 200);
	TH1F* PT_mg273 = new TH1F ("PT_mg273", "top quark PT", 20, 0, 400);

	Long64_t nentries = tree->GetEntries();       
	
	Int_t nevt = 0;	      
	for (Long64_t jentry=0; jentry<nentries;jentry++) { // event loop starts
		tree->GetEntry(jentry);
		nevt++;

        cout << "No. of events processed : "<<nevt<<endl;

// for all top and anti-top
		for(int igenpart=0; igenpart<nGenPart; igenpart++) { //gen loop
 			if( std::abs(GenPart_pdgId[igenpart]) == 6  && GenPart_status[igenpart] > 60 ) {   // check top and antitop quaark
				PT_mg273->Fill(GenPart_pt[igenpart],genWeight);
                		}
        		}	
//for pair
		for(int igenpart1=0; igenpart1<nGenPart-1; igenpart1++) {//gen loop
        		if(((GenPart_pdgId[igenpart1]) == 6 ||  (GenPart_pdgId[igenpart1]) == -6) && (GenPart_status[igenpart1] > 60 )){
                		for(int igenpart2=igenpart1+1; igenpart2<nGenPart; igenpart2++) {//gen loop
                        			if(((GenPart_pdgId[igenpart2]) == 6 ||  (GenPart_pdgId[igenpart2]) == -6) && GenPart_status[igenpart2] > 60 ){
                                			if(((GenPart_pdgId[igenpart1])*(GenPart_pdgId[igenpart2])) < 0){
                                                			Float_t px1 = GenPart_pt[igenpart1]*cos(GenPart_phi[igenpart1]);
                                                			Float_t py1 = GenPart_pt[igenpart1]*sin(GenPart_phi[igenpart1]);
                                                			Float_t px2 = GenPart_pt[igenpart2]*cos(GenPart_phi[igenpart2]);
                                                			Float_t py2 = GenPart_pt[igenpart2]*sin(GenPart_phi[igenpart2]);
                                                			Float_t pt = sqrt(px1*px2 + py1*py2);
                                                			pairPT_mg273->Fill(pt,genWeight);
                                                			}	
                                				}
                        				}		
                				}
        				}

}//event loop

   TFile* of = TFile::Open("output.root", "RECREATE");
   pairPT_mg273->Write();
   PT_mg273->Write();
   of->Close();

}
