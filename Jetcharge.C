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

using namespace std;


void Jetcharge(){

	TFile *f = new TFile("1C7EEEB5-60AA-234B-B2E1-90B4C0142D5C.root");

	TTree *tree = (TTree*)f->Get("Events");

	ofstream myfile;
	myfile.open("jet_charge.txt");

	Float_t Jet_pt[100];
	UInt_t nJet=0;
	Int_t numjet=0;
//	Int_t events=0;
	Int_t dijet=0;
	Int_t njets=0;
	Int_t jets=0;
//	auto x=0;

	tree->SetBranchAddress("Jet_pt", &Jet_pt);
        tree->SetBranchAddress("nJet", &nJet);

	TH1F *hpt   = new TH1F("hpt","pt_of_jets",100,0,2000);
	TH1F *hpt1  = new TH1F("hpt1","pt_of_leading_jet",100,0,2000);
	TH1F *hpt2  = new TH1F("hpt2","pt_of_sub-leading_jet",100,0,2000);

	Int_t nentries = Int_t(tree->GetEntries());
        cout << "Total Event count ="<< nentries << endl;

//start event loop ********************************************* get entries from the tree

        for (Int_t ievt=0; ievt<nentries ; ievt++){
	       tree->GetEntry(ievt);
//	       events++;                            		//total no of events after loop
	       
	       numjet = nJet;
	       
	       for (Int_t ij =0; ij < numjet ; ij++ ){ 
		       jets++;		       //total no of jets
//		       x = Jet_pt[ij].size();
	       }
	       
	       if (numjet ==2){                      		//select events with 2 jets

		       dijet++;                     		//total no of dijet events

		       if(Jet_pt[0]>400){
		       
			       hpt1->Fill(Jet_pt[0]);
		       }
		       
		       hpt2->Fill(Jet_pt[1]);

	      	       myfile << "Dijet event No. :"<< dijet << endl;
	      	       myfile << "Leading jet pt :"<< Jet_pt[0] << endl;
	      	       myfile << "Sub leading jet pt :" <<Jet_pt[1] << endl;
		       myfile << "**********************************"<< endl;
		       myfile << endl;
	
	       for (Int_t ij =0; ij < numjet ; ij++ ){      	//loop over dijet events
		       
		       njets++;
		       hpt->Fill(Jet_pt[ij]);
		       
		       myfile << "Total No. of jets :"<< njets << endl;	       
	      	       myfile << "Jet No. :" << ij << ":"<< "Pt :" << Jet_pt[ij]<< endl;
		       myfile << "#####################################################" << endl;
		       myfile << "#####################################################" << endl;		       
		       myfile <<endl;

	       	       }

	        }

	}

//	cout << "Total No. of events after loop over trees :"<< events << endl;
	cout << "Total No.of jets found :" << jets << endl;
//	cout << "Total No. of x jets found :" << x << endl;
        cout << "Total No. of dijet events :"<< dijet << endl;
	cout << "Total No. of jets in the dijet events :"<< njets << endl;
}
