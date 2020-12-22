#define ZMinPlot_cxx
#include "ZMinPlot.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void ZMinPlot::Loop()
{
//   In a ROOT session, you can do:
//      root> .L ZMinPlot.C
//      root> ZMinPlot t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   
   float x,y,z,sly,resx0;
   int N=0;
   gROOT->cd();
   TCanvas *c = new TCanvas("c","Graph2D example",1000,1000);
   c->SetLogz();
   TNtuple ntuple("ntuple","data from ascii file","x:y:z:sly:resx0");
   //TGraph2D *dt = new TGraph2D();
   //TH2F *h = new TH2F("TH2F","TH2F",50,-0.1,0.1,50,100,400);   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      int count=0;
      // if (Cut(ientry) < 0) continue;
      for (int i=0; i<6;i++){
	if (ResidualX_ROC0[i]==-999) continue;
	count++;
      }
      if (count==1){
	if (ResidualX_ROC0[0]==0) continue;
	if (ResidualX_ROC1[0]==0) continue;
	if (ResidualX_ROC2[0]==0) continue;
	if (ResidualY_ROC0[0]==0) continue;
	if (ResidualY_ROC1[0]==0) continue;
	if (ResidualY_ROC2[0]==0) continue;
	
	x=ResidualX_ROC0[0]*ResidualX_ROC0[0] + ResidualX_ROC1[0]*ResidualX_ROC1[0] + ResidualX_ROC2[0]*ResidualX_ROC2[0];
	y=ResidualY_ROC0[0]*ResidualY_ROC0[0] + ResidualY_ROC1[0]*ResidualY_ROC1[0] + ResidualY_ROC2[0]*ResidualY_ROC2[0];
	//z=(((LocalOY[0]+4.7)/SlopeY[0]));
	//if (SlopeY[0]<0.)
	N++;
	ntuple.Fill(x,y,z,SlopeY[0],ResidualY_ROC1[0]);
	//if (N>10000) break;
	//cout<<"adding point "<<N<<"times"<<endl;
      }   
   }
   //--------------------------------------------------
  //--- plotting
   
   //-------
   
   gROOT->SetStyle("Plain");   
   
   gStyle->SetOptStat(0);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   c->SetTitle("");
   c->Modified();

   
   gStyle->SetOptTitle(kFALSE);
   gPad->SetRightMargin(15/100.);
   gPad->SetLeftMargin(15/100.);
   gPad->SetTopMargin(15/100.);
   gPad->SetBottomMargin(15/100.);
   gStyle->SetPalette(1);

   //gPad->Clear();
   //gPad->Update();
   // ntuple.Draw("sqrt(y):sly>>K(40,-0.025,0.08,40,0.01,0.083)","sqrt(y) > 0.01","colz");
   //ntuple.Draw("sqrt(y):sly>>K","sqrt(y)>0.01","colz");
   ntuple.Draw("sqrt(y):resx0>>K","","colz");
   //ntuple.Draw("sqrt(x+y)","","colz");
   //ntuple.Draw("resx0","","colz");

   
   TH1* hist = (TH1*) gPad->GetListOfPrimitives()->FindObject("K");
   hist->SetMaximum(1000);
   hist->GetXaxis()->SetTitle("Slope_{Y}");
   //hist->GetXaxis()->SetTitle("Residual Y_{ROC1} [cm]");
   //hist->GetYaxis()->SetTitle("#sqrt{(#chi^{2}_{x} + #chi^{2}_{y})} [cm]");
   hist->GetYaxis()->SetTitle("#sqrt{#chi^{2}_{y}} [cm]");
   hist->GetXaxis()->SetTitleOffset(1.2);
   hist->GetYaxis()->SetTitleOffset(1.7);

   //K->SetTitle("");
   //K->GetXaxis->SetTitle("#sqrt(#Chi_{x}^{2} + #Chi_{y}^{2} )");
   //ntuple.Draw("sly","","colz");

   //latex work
   TLatex latex;
   //latex.SetTextAlign(32);                                                                                                                                                                              
   latex.SetTextFont(61);
   latex.DrawTextNDC(.15,.87,"CMS");
   latex.SetTextFont(52);
   latex.DrawTextNDC(.30,.87,"Preliminary");
   latex.SetTextFont(42);
   latex.DrawTextNDC(.62,.87,"2016 (13 TeV)");
}
