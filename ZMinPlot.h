//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Dec 16 16:54:22 2020 by ROOT version 6.10/04
// from TTree T/simple tree
// found on file: NewFinalOutputFill5277TimeStamp20160830.234009.root
//////////////////////////////////////////////////////////

#ifndef ZMinPlot_h
#define ZMinPlot_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class ZMinPlot {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         event;
   Float_t         track;
   Float_t         Channel[6];
   Float_t         BeamSpotX_x[6];
   Float_t         BeamSpotX_y[6];
   Float_t         BeamSpotY_x[6];
   Float_t         BeamSpotY_y[6];
   Float_t         BeamSpotZ_x[6];
   Float_t         BeamSpotZ_y[6];
   Float_t         ResidualX_ROC0[6];
   Float_t         ResidualX_ROC1[6];
   Float_t         ResidualX_ROC2[6];
   Float_t         ResidualY_ROC0[6];
   Float_t         ResidualY_ROC1[6];
   Float_t         ResidualY_ROC2[6];
   Float_t         SlopeX[6];
   Float_t         SlopeY[6];
   Float_t         GlobalVX[6];
   Float_t         GlobalVY[6];
   Float_t         GlobalVZ[6];
   Float_t         LocalVX[6];
   Float_t         LocalVY[6];
   Float_t         LocalVZ[6];
   Float_t         GlobalOX[6];
   Float_t         GlobalOY[6];
   Float_t         GlobalOZ[6];
   Float_t         LocalOX[6];
   Float_t         LocalOY[6];
   Float_t         LocalOZ[6];

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_track;   //!
   TBranch        *b_Channel;   //!
   TBranch        *b_BeamSpotX_x;   //!
   TBranch        *b_BeamSpotX_y;   //!
   TBranch        *b_BeamSpotY_x;   //!
   TBranch        *b_BeamSpotY_y;   //!
   TBranch        *b_BeamSpotZ_x;   //!
   TBranch        *b_BeamSpotZ_y;   //!
   TBranch        *b_ResidualX_ROC0;   //!
   TBranch        *b_ResidualX_ROC1;   //!
   TBranch        *b_ResidualX_ROC2;   //!
   TBranch        *b_ResidualY_ROC0;   //!
   TBranch        *b_ResidualY_ROC1;   //!
   TBranch        *b_ResidualY_ROC2;   //!
   TBranch        *b_SlopeX;   //!
   TBranch        *b_SlopeY;   //!
   TBranch        *b_GlobalVX;   //!
   TBranch        *b_GlobalVY;   //!
   TBranch        *b_GlobalVZ;   //!
   TBranch        *b_LocalVX;   //!
   TBranch        *b_LocalVY;   //!
   TBranch        *b_LocalVZ;   //!
   TBranch        *b_GlobalOX;   //!
   TBranch        *b_GlobalOY;   //!
   TBranch        *b_GlobalOZ;   //!
   TBranch        *b_LocalOX;   //!
   TBranch        *b_LocalOY;   //!
   TBranch        *b_LocalOZ;   //!

   ZMinPlot(TTree *tree=0);
   virtual ~ZMinPlot();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ZMinPlot_cxx
ZMinPlot::ZMinPlot(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("NewFinalOutputFill5277TimeStamp20160830.234009.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("NewFinalOutputFill5277TimeStamp20160830.234009.root");
      }
      f->GetObject("T",tree);

   }
   Init(tree);
}

ZMinPlot::~ZMinPlot()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ZMinPlot::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ZMinPlot::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ZMinPlot::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("track", &track, &b_track);
   fChain->SetBranchAddress("Channel", Channel, &b_Channel);
   fChain->SetBranchAddress("BeamSpotX_x", BeamSpotX_x, &b_BeamSpotX_x);
   fChain->SetBranchAddress("BeamSpotX_y", BeamSpotX_y, &b_BeamSpotX_y);
   fChain->SetBranchAddress("BeamSpotY_x", BeamSpotY_x, &b_BeamSpotY_x);
   fChain->SetBranchAddress("BeamSpotY_y", BeamSpotY_y, &b_BeamSpotY_y);
   fChain->SetBranchAddress("BeamSpotZ_x", BeamSpotZ_x, &b_BeamSpotZ_x);
   fChain->SetBranchAddress("BeamSpotZ_y", BeamSpotZ_y, &b_BeamSpotZ_y);
   fChain->SetBranchAddress("ResidualX_ROC0", ResidualX_ROC0, &b_ResidualX_ROC0);
   fChain->SetBranchAddress("ResidualX_ROC1", ResidualX_ROC1, &b_ResidualX_ROC1);
   fChain->SetBranchAddress("ResidualX_ROC2", ResidualX_ROC2, &b_ResidualX_ROC2);
   fChain->SetBranchAddress("ResidualY_ROC0", ResidualY_ROC0, &b_ResidualY_ROC0);
   fChain->SetBranchAddress("ResidualY_ROC1", ResidualY_ROC1, &b_ResidualY_ROC1);
   fChain->SetBranchAddress("ResidualY_ROC2", ResidualY_ROC2, &b_ResidualY_ROC2);
   fChain->SetBranchAddress("SlopeX", SlopeX, &b_SlopeX);
   fChain->SetBranchAddress("SlopeY", SlopeY, &b_SlopeY);
   fChain->SetBranchAddress("GlobalVX", GlobalVX, &b_GlobalVX);
   fChain->SetBranchAddress("GlobalVY", GlobalVY, &b_GlobalVY);
   fChain->SetBranchAddress("GlobalVZ", GlobalVZ, &b_GlobalVZ);
   fChain->SetBranchAddress("LocalVX", LocalVX, &b_LocalVX);
   fChain->SetBranchAddress("LocalVY", LocalVY, &b_LocalVY);
   fChain->SetBranchAddress("LocalVZ", LocalVZ, &b_LocalVZ);
   fChain->SetBranchAddress("GlobalOX", GlobalOX, &b_GlobalOX);
   fChain->SetBranchAddress("GlobalOY", GlobalOY, &b_GlobalOY);
   fChain->SetBranchAddress("GlobalOZ", GlobalOZ, &b_GlobalOZ);
   fChain->SetBranchAddress("LocalOX", LocalOX, &b_LocalOX);
   fChain->SetBranchAddress("LocalOY", LocalOY, &b_LocalOY);
   fChain->SetBranchAddress("LocalOZ", LocalOZ, &b_LocalOZ);
   Notify();
}

Bool_t ZMinPlot::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ZMinPlot::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ZMinPlot::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ZMinPlot_cxx
