#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include <cmath>

void ZJets_v2(){
	
		TFile* myFile = TFile::Open("test.root");
		if (myFile == 0){
			printf("Error: cannot open file\n");
			return;
			}

		TTreeReader myReader("Events", myFile);

		TTreeReaderValue<float> genWeight = {myReader, "genWeight"};

                TTreeReaderValue<unsigned int> nGenPart = {myReader, "nGenPart"};
        	TTreeReaderArray<float> GenPart_pt = {myReader, "GenPart_pt"};
        	TTreeReaderArray<float> GenPart_phi = {myReader, "GenPart_phi"};
        	TTreeReaderArray<float> GenPart_eta = {myReader, "GenPart_eta"};
        	TTreeReaderArray<float> GenPart_mass = {myReader, "GenPart_mass"};
        	TTreeReaderArray<int> GenPart_pdgId = {myReader, "GenPart_pdgId"};
        	TTreeReaderArray<int> GenPart_status = {myReader, "GenPart_status"};

		TTreeReaderValue<unsigned int> nGenJet = {myReader, "nGenJet"};
        	TTreeReaderArray<float> GenJet_pt = {myReader, "GenJet_pt"};
        	TTreeReaderArray<float> GenJet_eta = {myReader, "GenJet_eta"};
        	TTreeReaderArray<float> GenJet_phi = {myReader, "GenJet_phi"};

	  	TTreeReaderValue<unsigned int> nGenDressedLepton = {myReader, "nGenDressedLepton"};
        	TTreeReaderArray<float> GenDressedLepton_pt = {myReader, "GenDressedLepton_pt"};
        	TTreeReaderArray<float> GenDressedLepton_eta = {myReader, "GenDressedLepton_eta"};
        	TTreeReaderArray<float> GenDressedLepton_phi = {myReader, "GenDressedLepton_phi"};
        	TTreeReaderArray<float> GenDressedLepton_mass = {myReader, "GenDressedLepton_mass"};
        	TTreeReaderArray<int> GenDressedLepton_pdgId = {myReader, "GenDressedLepton_pdgId"};

        	TTreeReaderValue<float> GenMET_pt = {myReader, "GenMET_pt"};
        	TTreeReaderValue<float> GenMET_phi = {myReader, "GenMET_phi"};


		TH1F* njet = new TH1F ("njet", "No. of jets", 10, 0, 10);
	        TH1F* jetpt = new TH1F ("jetpt", "Pt of all jets", 30, 0, 300);
        	TH1F* jeteta = new TH1F ("jeteta", "eta of all jets", 30, -5, 5);
        	TH1F* jetphi = new TH1F ("jetphi", "Phi of all jets", 30, -3, 3);

        	TH1F* jet1pt = new TH1F ("jet1pt", "Pt of leading jets", 30, 0, 300);
        	TH1F* jet1eta = new TH1F ("jet1eta", "eta of leading jets", 30, -5, 5);
        	TH1F* jet1phi = new TH1F ("jet1phi", "Phi of leading jets", 30, -3, 3);

        	TH1F* jet2pt = new TH1F ("jet2pt", "Pt of sub-leading jets", 30, 0, 300);
        	TH1F* jet2eta = new TH1F ("jet2eta", "eta of sub-leading jets", 30, -5, 5);
        	TH1F* jet2phi = new TH1F ("jet2phi", "Phi of sub-leading jets", 30, -3, 3);

        	TH1F* jet3pt = new TH1F ("jet3pt", "Pt of 3rd jets", 30, 0, 300);
        	TH1F* jet3eta = new TH1F ("jet3eta", "eta of 3rd jets", 30, -5, 5);
       		TH1F* jet3phi = new TH1F ("jet3phi", "Phi of 3rd jets", 30, -3, 3);

        	TH1F* genpartpt = new TH1F ("genpartpt", "Pt of gen particles", 30, 0, 300);
        	TH1F* genparteta = new TH1F ("genparteta", "eta of gen particles", 100, -5, 5);
        	TH1F* genpartphi = new TH1F ("genpartphi", "Phi of gen particles", 100, -3, 3);

        	TH1F* genleptonpt = new TH1F ("genleptonpt", "Pt of leptons", 30, 0, 200);
        	TH1F* genleptoneta = new TH1F ("genleptoneta", "eta of leptons", 30, -5, 5);
        	TH1F* genleptonphi = new TH1F ("genleptonphi", "Phi of leptons", 30, -3, 3);

        	TH1F* metpt = new TH1F ("metpt", "pt of met", 30, 0, 200);
        	TH1F* metphi = new TH1F ("metphi", "Phi of met", 30, -3, 3);

        	TH1F* zmass = new TH1F ("zmass", "mass of z", 40, 0, 200);
        	TH1F* zpt = new TH1F ("zpt", "pt of z", 30, 0, 300);
        	TH1F* zeta = new TH1F ("zeta", "eta of z", 30, -5, 5);
        	TH1F* zphi = new TH1F ("zphi", "phi of z", 30, -3, 3);

		TH1F* genwt_bf = new TH1F ("genwt_bf", "genwt_bf", 2, -1, 1);
		TH1F* genwt_af = new TH1F ("genwt_af", "genwt_af", 2, -1, 1);

		while (myReader.Next()) {
	
			std::cout << "No. of events processed : " << myReader.GetCurrentEntry() << std::endl;
			
			genwt_bf->Fill(*genWeight);

                	if (!std::isfinite(*genWeight)) {
                        //std::cout << "Entry = " << myReader.GetCurrentEntry() << " *genWeight = " << *genWeight << std::endl;
                        continue;}
			
			genwt_af->Fill(*genWeight);
	
			TLorentzVector el1, el2, el;

	                for(int igenpart1=0; igenpart1<*nGenDressedLepton; igenpart1++) { // z loop
				if(((GenDressedLepton_pdgId[igenpart1]) == 11 ||  (GenDressedLepton_pdgId[igenpart1]) == -11)){
                                el1.SetPtEtaPhiM(GenDressedLepton_pt[igenpart1], GenDressedLepton_eta[igenpart1], GenDressedLepton_phi[igenpart1], GenDressedLepton_mass[igenpart1]);
                                for(int igenpart2=igenpart1+1; igenpart2<*nGenDressedLepton; igenpart2++){
                                                if(((GenDressedLepton_pdgId[igenpart2]) == 11 ||  (GenDressedLepton_pdgId[igenpart2]) == -11)){
                                                        el2.SetPtEtaPhiM(GenDressedLepton_pt[igenpart2], GenDressedLepton_eta[igenpart2], GenDressedLepton_phi[igenpart2], GenDressedLepton_mass[igenpart2]);
                                                        el = (el1+el2);
                                                        if(((GenDressedLepton_pdgId[igenpart1])*(GenDressedLepton_pdgId[igenpart2])) < 0){
									zmass->Fill(el.M(),*genWeight);
                                                                        zpt->Fill(el.Pt(),*genWeight);
                                                                        zeta->Fill(el.Eta(),*genWeight);
                                                                        zphi->Fill(el.Phi(),*genWeight);
                                                                        }
                                                                }
                                                        }
                                                }
                                        }

			for (int njets=0; njets<*nGenJet; njets++){  // jet loop
			njet->Fill(njets,*genWeight);
                        jetpt->Fill(GenJet_pt[njets],*genWeight);
                        jeteta->Fill(GenJet_eta[njets],*genWeight);
                        jetphi->Fill(GenJet_phi[njets],*genWeight);
                        if (njets==0){
                                jet1pt->Fill(GenJet_pt[njets],*genWeight);
                                jet1eta->Fill(GenJet_eta[njets],*genWeight);
                                jet1phi->Fill(GenJet_phi[njets],*genWeight);
                                }
                        if (njets==1){
                                jet2pt->Fill(GenJet_pt[njets],*genWeight);
                                jet2eta->Fill(GenJet_eta[njets],*genWeight);
                                jet2phi->Fill(GenJet_phi[njets],*genWeight);
                                }
                        if (njets==2){
                                jet3pt->Fill(GenJet_pt[njets],*genWeight);
                                jet3eta->Fill(GenJet_eta[njets],*genWeight);
                                jet3phi->Fill(GenJet_phi[njets],*genWeight);
                                }
                        }

			for (int igenpart=0; igenpart<*nGenPart; igenpart++){  // gen particle loop
				genpartpt->Fill(GenPart_pt[igenpart],*genWeight);
        	                genparteta->Fill(GenPart_eta[igenpart],*genWeight);
                	        genpartphi->Fill(GenPart_phi[igenpart],*genWeight);
                        	}

 	               for (int igenleptons=0;igenleptons<*nGenDressedLepton; igenleptons++){ // gendressedlepton loop
			 	genleptonpt->Fill(GenDressedLepton_pt[igenleptons],*genWeight);
                        	genleptoneta->Fill(GenDressedLepton_eta[igenleptons],*genWeight);
                        	genleptonphi->Fill(GenDressedLepton_phi[igenleptons],*genWeight);
				}	

                	metpt->Fill(*GenMET_pt,*genWeight);
                	metphi->Fill(*GenMET_phi,*genWeight);                       
}
	TFile* of = TFile::Open("output_ZJets_v2.root", "RECREATE");
	
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
