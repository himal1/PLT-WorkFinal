#include "Riostream.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
using namespace RooFit;
ifstream in;
void rootFileOpen()
{
  //Lets define the parameters we will need
  //Variables, root files and the ntuples 
  
  TString root,root1,Timestamp,fill;
  Float_t meanX,sigmaX,nFill,nTime,meanErrX,sigmaErrX,BeamSpot_x,BeamSpot_y;
  Float_t meanY,sigmaY,meanErrY,sigmaErrY;

  TFile *f = new TFile("basicFromTrack.root","RECREATE");
  TNtuple *ntuple1 = new TNtuple("ntuple1","Data for file","nFill:nTime:meanX:sigmaX:meanY:sigmaY:meanErrX:meanErrY");
  int n=0;
  
  //open the input file
  in.open("NewInputFilesHimal.txt");
  //in.open("test.txt");
  //make loop over the input files
  while (1) {
    in >> root;
    if (!in.good()) break;
    //cout<<root<<endl;
    TFile * f = TFile::Open(root.Data());

    //Define the ntuple
  
    TTree *datatree = (TTree*)(f->Get("T"));
    TBranch *branchGx = datatree->GetBranch("GlobalOX");
    TBranch *branchGy = datatree->GetBranch("GlobalOY");
    TBranch *branchGz = datatree->GetBranch("GlobalOZ");
    TBranch *branchGVx = datatree->GetBranch("GlobalVX");
    TBranch *branchGVy = datatree->GetBranch("GlobalVY");
    TBranch *branchGVz = datatree->GetBranch("GlobalVZ");
    
    TCanvas *c2 = new TCanvas("c2","c2");

    //Now identify the fill using root fle name
    root1 = root;
    int l = root1.Length();
    int l1=l-18;
    root.Remove(0,18);
    root.Remove(4,l1);
    fill = root;
    //root1.Remove(0,24);
    
    l=l-20;
    //cout<<l<<endl;
    root1.Remove(0,l);
    root1.Remove(15,20);
    Timestamp=root1;
    if (root=="Time"){
      cout<<"No Fill Information for "<<Timestamp<<" TimeStamp"<<endl;
      c2->Close();
    }
    else{
      cout<<"Start"<<endl;
      cout<<root<<endl;
      int numEntry = datatree->GetEntries();
      if (numEntry< 4000) continue;
      cout<<"The entries in the ntuple are : "<<numEntry<<endl;
      cout<<"The entries in the branch are : "<<branchGx->GetEntries()<<endl;

      Float_t Gx[6];
      Float_t Gy[6];
      Float_t Gz[6];
      Float_t GVx[6];
      Float_t GVy[6];
      Float_t GVz[6];
      
      branchGx->SetAddress(Gx);
      branchGy->SetAddress(Gy);
      branchGz->SetAddress(Gz);

      branchGVx->SetAddress(GVx);
      branchGVy->SetAddress(GVy);
      branchGVz->SetAddress(GVz);

      float x,y;
      //Now Maximum Likelihood Fit
      
      RooRealVar x1("x1", "x1", -5., 5.);
      RooRealVar y1("y1", "y1", -5., 5.);
      RooRealVar x2("x2", "x2", -5., 5.);
      RooRealVar y2("y2", "y2", -5., 5.);
      
      RooArgSet m_arg(x1,y1,"m_args");

      RooDataSet * dataset = new RooDataSet("dataset","dataset",m_arg);

      for(int i=0;i<datatree->GetEntries();i++){
        datatree->GetEvent(i);
	
	int count=0;
	for (int k=0;k<6;k++){
	  if (!(Gx[k]==-999)){
	    count++;
	    //cout<< "The Beamspot for "<<k<<" is "<<Bx[k]<<endl;
	  }
	}
	if (count!=2) continue;
	//Now use the formula to get beamspot x and y
	float x_A,x_B,y_A,y_B,z_A,z_B;
	float a_x,a_y,a_z,b_x,b_y,b_z;
	float A_c, A_d, B_c, B_d, C_c, C_d;
	
	float a1,a2,b1,b2,c1,c2;
	// TNtuple *ntuple=new TNtuple ("ntuple","data1","x:y:z:r");                                                                                                                                      
	float Mu, Lambda;
	float x_C, y_C, z_C, x_D, y_D, z_D;
	//Ch=Channel[0];
	//Ch1=Channel[1];


	//cout<<"The Two channel are "<<Ch<<" and "<<Ch1<<endl;                                                                                                                                           
         x_A=Gx[0];
         y_A=Gy[0];
         z_A=Gz[0];

         x_B=Gx[1];
         y_B=Gy[1];
         z_B=Gz[1];

         a_x=GVx[0];
         a_y=GVy[0];
         a_z=GVz[0];

         b_x=GVx[1];
         b_y=GVy[1];
         b_z=GVz[1];
	 
	 if (x_A==-999 || y_A==-999 || z_A==-999) continue;
	 if (x_B==-999 || y_B==-999 || z_B==-999) continue;
	 if (a_x==-999 || a_y==-999 || a_z==-999) continue;
	 if (b_x==-999 || b_y==-999 || b_z==-999) continue;
	 
	 A_c = ((x_B - x_A) * a_x) + ((y_B -y_A) * a_y) + ((z_B - z_A) * a_z);
         A_d = ((x_B - x_A) * b_x) + ((y_B -y_A) * b_y) + ((z_B - z_A) * b_z);
         B_c = (a_x * b_x) + (a_y * b_y) + (a_z * b_z);
         B_d = (b_x * b_x) + (b_y * b_y) + (b_z * b_z);
         C_c = -((a_x * a_x) + (a_y * a_y) + (a_z * a_z));
         C_d = -((a_x * b_x) + (a_y * b_y) + (a_z * b_z));

         a1=B_c; b1=C_c ; c1=A_c;
         a2=B_d; b2=C_d; c2=A_d;

         Mu = (b1*c2 -c1*b2) / (a1*b2 -a2* b1);
         Lambda = (a2*c1 -a1*c2) /(a1*b2 - a2*b1);

         //intersection of the track                                                                                                                                                                       

         x_C = x_A + (Lambda * a_x);
         y_C = y_A + (Lambda * a_y);
         z_C = z_A + (Lambda * a_z);

         x_D = x_B + (Mu * b_x);
         y_D = y_B + (Mu * b_y);
         z_D = z_B + (Mu * b_z);

         x=(x_C+x_D)/2;
         y=(y_C+y_D)/2;
         //z=(z_C+z_D)/2;
         //now using the intersection formula                                                                                                                                                              
         float C_1, C_2, M_1, M_2;
         C_1=(y_A - ((y_C-y_A)/(x_C-x_A)*x_A));
         C_2=(y_B - ((y_D-y_B)/(x_D-x_B)*x_B));
         M_1=(y_C-y_A)/(x_C-x_A);
         M_2=(y_D-y_B)/(x_D-x_B);

	 if ( abs((C_2-C_1)/(M_1-M_2)) > 5 ) continue;
	 if ( abs((M_1*(C_2-C_1)/(M_1-M_2)) + C_1 ) > 5 ) continue;
	 
         x= (C_2-C_1)/(M_1-M_2);
         y= (M_1*(C_2-C_1)/(M_1-M_2)) + C_1;
	 //sscanf(fill, "%f", &nFill);
	 //ntuple1->Fill(nFill,x,y);
	 x1=x;
	 y1=y;

	//end

	
	//cout<<"Value of C "<<count<<endl;
	//x=Bx[0];
	//y=By[0];
	//cout<<"The beamSpot x is ; "<<x<<endl;
        //BeamSpotZ_x = BeamSpotZ_x[0];
        dataset->add(m_arg,1.0);
      }
      dataset->write("Himal.txt");
      RooDataSet *dataReadBack =
	RooDataSet::read("Himal.txt",
                       RooArgList(x2, y2), // variables to be read. If the file has more fields, these are ignored.
                       "D"); // Prints if a RooFit message stream listens for debug messages. Use Q for quiet.
     
      RooRealVar meanX1("meanX1", "meanX1", 0, -5., 5.);
      RooRealVar meanY1("meanY1", "meanY1", 0, -5, 5.);
      RooRealVar sigmaX1("sigmaX1", "sigmaX1", 0.5, 0.10, 5.0);
      RooRealVar sigmaY1("sigmaY1", "sigmaY1", 0.5, 0.10, 5.0);
      RooRealVar sigmaX2("sigmaX2", "sigmaX2", 1.0, 0.5, 7.0);
      RooRealVar sigmaY2("sigmaY2", "sigmaY2", 1.0, 0.5, 7.0);
      RooGaussian gaussX("gaussX", "gaussX", x2, meanX1, sigmaX1);
      RooGaussian gaussX1("gaussX1", "gaussX1", x2, meanX1, sigmaX2);
      RooGaussian gaussY("gaussY", "gaussY", y2, meanY1, sigmaY1);
      RooGaussian gaussY1("gaussY1", "gaussY1", y2, meanY1, sigmaY2);
      RooRealVar nsigx("nsigx","nsignalx",500000,0,10000000);                             
      RooRealVar nsig1x("nsig1x","nsignal1x",50000,0,10000000);
      RooRealVar nsigy("nsigy","nsignaly",500000,0,10000000);                             
      RooRealVar nsig1y("nsig1y","nsignal1y",500000,0,10000000);
      RooAddPdf sumx("sumx","S+S1x",RooArgList(gaussX,gaussX1),RooArgList(nsigx,nsig1x));
      RooAddPdf sumy("sumy","S+S1y",RooArgList(gaussY,gaussY1),RooArgList(nsigy,nsig1y)); 

      sumx.fitTo(*dataReadBack);//fit data from the ntuple
      sumy.fitTo(*dataReadBack);//fit data from the ntuple
      //sum.fitTo(*data_s);//fit data from the text input
      RooPlot *frame = x2.frame(25);
      dataReadBack->plotOn(frame);
      sumx.plotOn(frame, Components("gaussX"), LineColor(kRed), LineStyle(kDashed));
      sumx.plotOn(frame, Components("gaussX1"), LineColor(kGreen), LineStyle(kDashed));
      sumx.plotOn(frame);
      frame->Draw();
      //name the fit Channel
      TString str;
      str="FitChannel2Y-";
      str=str+fill;
      str=str+".png";
      //c2->Print(str);
      
      //cout the imporatant variables
      cout<<"The New mean X is : "<<meanX1.getVal()<<endl;
      cout<<"The New mean error X is : "<<meanX1.getError()<<endl;
      cout<<"The New sigma X is : "<<sigmaX1.getVal()<<endl;
      cout<<"The New sigma1 X is : "<<sigmaX2.getVal()<<endl;
      cout<<"The New mean Y is : "<<meanY1.getVal()<<endl;
      cout<<"The New mean error Y is : "<<meanY1.getError()<<endl;
      cout<<"The New sigma Y is : "<<sigmaY1.getVal()<<endl;
      cout<<"The New sigma1 Y is : "<<sigmaY2.getVal()<<endl;
      //add the 
      meanX=meanX1.getVal();
      meanErrX= meanX1.getError();
      if (sigmaX1.getVal()<sigmaX2.getVal()){
	sigmaX=sigmaX1.getVal();
	sigmaErrX=sigmaX1.getError();
      }
      else {
	sigmaX=sigmaX2.getVal();
        sigmaErrX=sigmaX2.getError();
      }
      
      meanY=meanY1.getVal();
      meanErrY=meanY1.getError();
      if (sigmaY1.getVal()<sigmaY2.getVal()){
	sigmaY=sigmaY1.getVal();
	sigmaErrY=sigmaY1.getError();
      }
      else {
	sigmaY=sigmaY2.getVal();
        sigmaErrY=sigmaY2.getError();
      }
      //convert string to float
      sscanf(Timestamp, "%f", &nTime);
      sscanf(fill, "%f", &nFill);
      
      //store the info in ntuple
      ntuple1->Fill(nFill,nTime,meanX,sigmaX,meanY,sigmaY,meanErrX,meanErrY);
      //c2->Close();
      //New calculation for Beamspotx;
      //float x_New;
      //x_New=BeamSpotZ_x + (SlopeX * ( (BeamSpotZ_x * SlopeX) + ((BeamSpotZ_y * SlopeY) ) ) /( (SlopeX * SlopeX )+(SlopeY * SlopeY) ) );
      //cout<<"compare  the beamspot x "<<BeamSpotZ_x<<"is old and new is "<<x_New<<endl; 
      
    }
    
  }
  in.close();
  //out.close();
  f->Write();
}


