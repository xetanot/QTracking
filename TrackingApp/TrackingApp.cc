//_____________________________________________________________________________
// Standard Headers:
#include <fstream>
#include <cmath>
#include <iostream>
#include <unistd.h>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2F.h"
#include "TF1.h"
#include "TMath.h"
#include "TString.h"
#include "TSystem.h"
#include "TFile.h"
#include "TROOT.h"
#include <TVector3.h>
#include "TLorentzVector.h"
#include "TApplication.h"
#include <string.h>
#include "TRandom.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "TStopwatch.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

using namespace std;

int main(int __argc,char *__argv[]){
  
  Int_t Argc = __argc;
  char **Input = __argv;
  std::vector<string> w;
  w.assign(__argv, __argv + __argc);  
  TApplication* theApp = new TApplication("App", &__argc, __argv);   
  
  TString outFileName = "resultTree.root";
  TFile outFile(outFileName,"recreate");  
  
  TString myMethodList = "";
  
  //---------------------------------------------------------------
  // This loads the library
  TMVA::Tools::Instance();
  
  // Default MVA methods to be trained + tested
  std::map<std::string,int> Use;
  
  // --- Mutidimensional likelihood and Nearest-Neighbour methods
  Use["PDERS"]           = 0;
  Use["PDEFoam"]         = 0; 
  Use["KNN"]             = 0;
  // 
  // --- Linear Discriminant Analysis
  Use["LD"]		        = 0;
  // 
  // --- Function Discriminant analysis
  Use["FDA_GA"]          = 0;
  Use["FDA_MC"]          = 0;
  Use["FDA_MT"]          = 0;
  Use["FDA_GAMT"]        = 0;
  // 
  // --- Neural Network
  Use["MLP"] = 1;
#ifdef R__HAS_TMVACPU
  Use["DNN_CPU"] = 0;
#else
  Use["DNN_CPU"] = 0;
#endif
  
  // 
  // --- Support Vector Machine 
  Use["SVM"]             = 0;
  // 
  // --- Boosted Decision Trees
  Use["BDT"]             = 0;
  Use["BDTG"]            = 0;
  // ---------------------------------------------------------------
  
  std::cout << std::endl;
  std::cout << "==> Start Processing" << std::endl;
  
  // Select methods (don't look at this code - not of interest)
  if (myMethodList != "") {
    for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
    
    std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
    for (UInt_t i=0; i<mlist.size(); i++) {
      std::string regMethod(mlist[i]);
      
      if (Use.find(regMethod) == Use.end()) {
	std::cout << "Method \"" << regMethod << "\" not known. Choose among the following:" << std::endl;
	for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
	std::cout << std::endl;
	return 0;
      }
      Use[regMethod] = 1;
    }
  }
  
  // --------------------------------------------------------------------------------------------------
  
  // --- Create the Reader object
  
  TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    
  
  // Create a set of variables and declare them to the reader
  // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
  Int_t n_tracks=0;
  Int_t weight=0;
  float sq_x_st1[100];
  float sq_y_st1[100];
  float sq_z_st1[100];
  float sq_px_st1[100];
  float sq_py_st1[100];
  float sq_pz_st1[100];
  float sq_x_st2[100];
  float sq_y_st2[100];
  float sq_z_st2[100];
  float sq_px_st2[100];
  float sq_py_st2[100];
  float sq_pz_st2[100];
  float D0U_x[100];
  float D0U_y[100];
  float D0U_z[100];
  float D0Up_x[100];
  float D0Up_y[100];
  float D0Up_z[100];
  float D0X_x[100];
  float D0X_y[100];
  float D0X_z[100];
  float D0Xp_x[100];
  float D0Xp_y[100];
  float D0Xp_z[100];
  float D0V_x[100];
  float D0V_y[100];
  float D0V_z[100];
  float D0Vp_x[100];
  float D0Vp_y[100];
  float D0Vp_z[100];
  float D2U_x[100];
  float D2U_y[100];
  float D2U_z[100];
  float D2Up_x[100];
  float D2Up_y[100];
  float D2Up_z[100];
  float D2X_x[100];
  float D2X_y[100];
  float D2X_z[100];
  float D2Xp_x[100];
  float D2Xp_y[100];
  float D2Xp_z[100];
  float D2V_x[100];
  float D2V_y[100];
  float D2V_z[100];
  float D2Vp_x[100];
  float D2Vp_y[100];
  float D2Vp_z[100];
  float D3pU_x[100];
  float D3pUp_x[100];
  float D3pX_x[100];
  float D3pXp_x[100];
  float D3pV_x[100];
  float D3pVp_x[100];
  float D3pU_y[100];
  float D3pUp_y[100];
  float D3pX_y[100];
  float D3pXp_y[100];
  float D3pV_y[100];
  float D3pVp_y[100];
  float D3pU_z[100];
  float D3pUp_z[100];
  float D3pX_z[100];
  float D3pXp_z[100];
  float D3pV_z[100];
  float D3pVp_z[100];
  float D3mU_x[100];
  float D3mUp_x[100];
  float D3mX_x[100];
  float D3mXp_x[100];
  float D3mV_x[100];
  float D3mVp_x[100];
  float D3mU_y[100];
  float D3mUp_y[100];
  float D3mX_y[100];
  float D3mXp_y[100];
  float D3mV_y[100];
  float D3mVp_y[100];
  float D3mU_z[100];
  float D3mUp_z[100];
  float D3mX_z[100];
  float D3mXp_z[100];
  float D3mV_z[100];
  float D3mVp_z[100];   
  float gpx[100];
  float gpy[100];
  float gpz[100];
  float gvz[100];   
  
  Float_t Sq_px_st1=0;
  Float_t Sq_py_st1=0;
  Float_t Sq_pz_st1=0;
  Float_t Sq_px_st2=0;
  Float_t Sq_py_st2=0;
  Float_t Sq_pz_st2=0;
  Float_t d0X_x=0;
  Float_t d0X_y=0;
  Float_t d0X_z=0;
  Float_t d0Xp_x=0;
  Float_t d0Xp_y=0;
  Float_t d0Xp_z=0;
  Float_t d0U_x=0;
  Float_t d0U_y=0;
  Float_t d0U_z=0;
  Float_t d0Up_x=0;
  Float_t d0Up_y=0;
  Float_t d0Up_z=0;
  Float_t d0V_x=0;
  Float_t d0V_y=0;
  Float_t d0V_z=0;
  Float_t d0Vp_x=0;
  Float_t d0Vp_y=0;
  Float_t d0Vp_z=0;
  Float_t d2X_x=0;
  Float_t d2X_y=0;
  Float_t d2X_z=0;
  Float_t d2Xp_x=0;
  Float_t d2Xp_y=0;
  Float_t d2Xp_z=0;
  Float_t d2U_x=0;
  Float_t d2U_y=0;
  Float_t d2U_z=0;
  Float_t d2Up_x=0;
  Float_t d2Up_y=0;
  Float_t d2Up_z=0;
  Float_t d2V_x=0;
  Float_t d2V_y=0;
  Float_t d2V_z=0;
  Float_t d2Vp_x=0;
  Float_t d2Vp_y=0;
  Float_t d2Vp_z=0;
  Float_t d3pX_X=0;
  Float_t d3pX_Y=0;
  Float_t d3pX_Z=0;
  Float_t d3pXp_X=0;
  Float_t d3pXp_Y=0;
  Float_t d3pXp_Z=0;
  Float_t d3pU_X=0;
  Float_t d3pU_Y=0;
  Float_t d3pU_Z=0;
  Float_t d3pUp_X=0;
  Float_t d3pUp_Y=0;
  Float_t d3pUp_Z=0;
  Float_t d3pV_X=0;
  Float_t d3pV_Y=0;
  Float_t d3pV_Z=0;
  Float_t d3pVp_X=0;
  Float_t d3pVp_Y=0;
  Float_t d3pVp_Z=0;
  Float_t d3mX_X=0;
  Float_t d3mX_Y=0;
  Float_t d3mX_Z=0;
  Float_t d3mXp_X=0;
  Float_t d3mXp_Y=0;
  Float_t d3mXp_Z=0;
  Float_t d3mU_X=0;
  Float_t d3mU_Y=0;
  Float_t d3mU_Z=0;
  Float_t d3mUp_X=0;
  Float_t d3mUp_Y=0;
  Float_t d3mUp_Z=0;
  Float_t d3mV_X=0;
  Float_t d3mV_Y=0;
  Float_t d3mV_Z=0;
  Float_t d3mVp_X=0;
  Float_t d3mVp_Y=0;
  Float_t d3mVp_Z=0;
  Float_t Gpx;
  Float_t Gpy;
  Float_t Gpz;
  Float_t Gvz;
  Float_t px;
  Float_t py;
  Float_t pz;
  
  reader->AddVariable("d0X_x", &d0X_x );
  reader->AddVariable("d0X_y", &d0X_y );
  reader->AddVariable("d0Xp_x", &d0Xp_x );
  reader->AddVariable("d0Xp_y", &d0Xp_y );
  reader->AddVariable("d0U_x", &d0U_x );
  reader->AddVariable("d0U_y", &d0U_y );
  reader->AddVariable("d0Up_x", &d0Up_x );
  reader->AddVariable("d0Up_y", &d0Up_y );
  reader->AddVariable("d0V_x", &d0V_x );
  reader->AddVariable("d0V_y", &d0V_y );
  reader->AddVariable("d0Vp_x", &d0Vp_x );
  reader->AddVariable("d0Vp_y", &d0Vp_y );
  reader->AddVariable("d2X_y", &d2X_y );
  reader->AddVariable("d2X_x", &d2X_x );
  reader->AddVariable("d2Xp_y", &d2Xp_y );
  reader->AddVariable("d2Xp_x", &d2Xp_x );
  reader->AddVariable("d2U_y", &d2U_y );
  reader->AddVariable("d2U_x", &d2U_x );
  reader->AddVariable("d2Up_y", &d2Up_y );
  reader->AddVariable("d2Up_x", &d2Up_x );
  reader->AddVariable("d2V_y", &d2V_y );
  reader->AddVariable("d2V_x", &d2V_x );
  reader->AddVariable("d2Vp_y", &d2Vp_y );
  reader->AddVariable("d2Vp_x", &d2Vp_x );
  reader->AddVariable("d3pX_X", &d3pX_X );
  reader->AddVariable("d3pX_Y", &d3pX_Y );
  reader->AddVariable("d3pXp_X", &d3pXp_X );
  reader->AddVariable("d3pXp_Y", &d3pXp_Y );
  reader->AddVariable("d3pU_X", &d3pU_X );
  reader->AddVariable("d3pU_Y", &d3pU_Y );
  reader->AddVariable("d3pUp_X", &d3pUp_X );
  reader->AddVariable("d3pUp_Y", &d3pUp_Y );
  reader->AddVariable("d3pV_X", &d3pV_X );
  reader->AddVariable("d3pV_Y", &d3pV_Y );
  reader->AddVariable("d3pVp_X", &d3pVp_X );
  reader->AddVariable("d3pVp_Y", &d3pVp_Y );
  reader->AddVariable("d3mX_X", &d3mX_X );
  reader->AddVariable("d3mX_Y", &d3mX_Y );
  reader->AddVariable("d3mXp_X", &d3mXp_X );
  reader->AddVariable("d3mXp_Y", &d3mXp_Y );
  reader->AddVariable("d3mU_X", &d3mU_X );
  reader->AddVariable("d3mU_Y", &d3mU_Y );
  reader->AddVariable("d3mUp_X", &d3mUp_X );
  reader->AddVariable("d3mUp_Y", &d3mUp_Y );
  reader->AddVariable("d3mV_X", &d3mV_X );
  reader->AddVariable("d3mV_Y", &d3mV_Y );
  reader->AddVariable("d3mVp_X", &d3mVp_X );
  reader->AddVariable("d3mVp_Y", &d3mVp_Y );   
  reader->AddSpectator( "Gpx",  &Gpx );
  reader->AddSpectator( "Gpy",  &Gpy );   
  reader->AddSpectator( "Gpz",  &Gpz );    
  
  TString dir    = "dataset/weights/";
  TString prefix = "TMVARegression";
  
  // Book method(s)
  for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
    if (it->second) {
      TString methodName = it->first + " method";
      TString weightfile = dir + prefix + "_" + TString(it->first) + ".weights.xml";
      reader->BookMVA( methodName, weightfile ); 
    }
  }
  
  TTree regout("TreeFin","TreeFin");
  regout.Branch("d0X_x", &d0X_x );
  regout.Branch("d0X_y", &d0X_y );
  regout.Branch("d0Xp_x", &d0Xp_x );
  regout.Branch("d0Xp_y", &d0Xp_y );
  regout.Branch("d0U_x", &d0U_x );
  regout.Branch("d0U_y", &d0U_y );
  regout.Branch("d0Up_x", &d0Up_x );
  regout.Branch("d0Up_y", &d0Up_y );
  regout.Branch("d0V_x", &d0V_x );
  regout.Branch("d0V_y", &d0V_y );
  regout.Branch("d0Vp_x", &d0Vp_x );
  regout.Branch("d0Vp_y", &d0Vp_y );
  regout.Branch("d2X_y", &d2X_y );
  regout.Branch("d2X_x", &d2X_x );
  regout.Branch("d2Xp_y", &d2Xp_y );
  regout.Branch("d2Xp_x", &d2Xp_x );
  regout.Branch("d2U_y", &d2U_y );
  regout.Branch("d2U_x", &d2U_x );
  regout.Branch("d2Up_y", &d2Up_y );
  regout.Branch("d2Up_x", &d2Up_x );
  regout.Branch("d2V_y", &d2V_y );
  regout.Branch("d2V_x", &d2V_x );
  regout.Branch("d2Vp_y", &d2Vp_y );
  regout.Branch("d2Vp_x", &d2Vp_x );
  regout.Branch("d3pX_X", &d3pX_X );
  regout.Branch("d3pX_Y", &d3pX_Y );
  regout.Branch("d3pXp_X", &d3pXp_X );
  regout.Branch("d3pXp_Y", &d3pXp_Y );
  regout.Branch("d3pU_X", &d3pU_X );
  regout.Branch("d3pU_Y", &d3pU_Y );
  regout.Branch("d3pUp_X", &d3pUp_X );
  regout.Branch("d3pUp_Y", &d3pUp_Y );
  regout.Branch("d3pV_X", &d3pV_X );
  regout.Branch("d3pV_Y", &d3pV_Y );
  regout.Branch("d3pVp_X", &d3pVp_X );
  regout.Branch("d3pVp_Y", &d3pVp_Y );
  regout.Branch("d3mX_X", &d3mX_X );
  regout.Branch("d3mX_Y", &d3mX_Y );
  regout.Branch("d3mXp_X", &d3mXp_X );
  regout.Branch("d3mXp_Y", &d3mXp_Y );
  regout.Branch("d3mU_X", &d3mU_X );
  regout.Branch("d3mU_Y", &d3mU_Y );
  regout.Branch("d3mUp_X", &d3mUp_X );
  regout.Branch("d3mUp_Y", &d3mUp_Y );
  regout.Branch("d3mV_X", &d3mV_X );
  regout.Branch("d3mV_Y", &d3mV_Y );
  regout.Branch("d3mVp_X", &d3mVp_X );
  regout.Branch("d3mVp_Y", &d3mVp_Y );
  regout.Branch("Gpy", &Gpy );
  regout.Branch("Gpx", &Gpx );  
  regout.Branch("Gpz", &Gpz );
  regout.Branch("px", &px );    
  regout.Branch("py", &py );
  regout.Branch("pz", &pz );
  
  
  for(int n_arg = optind; n_arg < Argc; n_arg++){ 
    
    TString input =w[n_arg];
    TFile inFile(input); // open the input file      
    
    if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
    }
    std::cout << " Using input file: " << inFile.GetName() << std::endl;
    
    TTree* theTree = (TTree*)inFile.Get("QA_ana");
    theTree->SetBranchAddress("n_tracks",    &n_tracks); 
    theTree->SetBranchAddress("sq_px_st1",    &sq_px_st1);
    theTree->SetBranchAddress("sq_py_st1",    &sq_py_st1);
    theTree->SetBranchAddress("sq_pz_st1",    &sq_pz_st1);
    theTree->SetBranchAddress("sq_px_st2",    &sq_px_st2);
    theTree->SetBranchAddress("sq_py_st2",    &sq_py_st2);
    theTree->SetBranchAddress("sq_pz_st2",    &sq_pz_st2);
    theTree->SetBranchAddress("D0U_x",    &D0U_x);
    theTree->SetBranchAddress("D0U_y",    &D0U_y);
    theTree->SetBranchAddress("D0U_z",    &D0U_z);
    theTree->SetBranchAddress("D0Up_x",    &D0Up_x);
    theTree->SetBranchAddress("D0Up_y",    &D0Up_y);
    theTree->SetBranchAddress("D0Up_z",    &D0Up_z);
    theTree->SetBranchAddress("D0X_x",    &D0X_x);
    theTree->SetBranchAddress("D0X_y",    &D0X_y);
    theTree->SetBranchAddress("D0X_z",    &D0X_z);
    theTree->SetBranchAddress("D0Xp_x",    &D0Xp_x);
    theTree->SetBranchAddress("D0Xp_y",    &D0Xp_y);
    theTree->SetBranchAddress("D0Xp_z",    &D0Xp_z);
    theTree->SetBranchAddress("D0V_x",    &D0V_x);
    theTree->SetBranchAddress("D0V_y",    &D0V_y);
    theTree->SetBranchAddress("D0V_z",    &D0V_z);
    theTree->SetBranchAddress("D0Vp_x",    &D0Vp_x);
    theTree->SetBranchAddress("D0Vp_y",    &D0Vp_y);
    theTree->SetBranchAddress("D0Vp_z",    &D0Vp_z);
    theTree->SetBranchAddress("D2U_x",    &D2U_x);
    theTree->SetBranchAddress("D2U_y",    &D2U_y);
    theTree->SetBranchAddress("D2U_z",    &D2U_z);
    theTree->SetBranchAddress("D2Up_x",    &D2Up_x);
    theTree->SetBranchAddress("D2Up_y",    &D2Up_y);
    theTree->SetBranchAddress("D2Up_z",    &D2Up_z);
    theTree->SetBranchAddress("D2X_x",    &D2X_x);
    theTree->SetBranchAddress("D2X_y",    &D2X_y);
    theTree->SetBranchAddress("D2X_z",    &D2X_z);
    theTree->SetBranchAddress("D2Xp_x",    &D2Xp_x);
    theTree->SetBranchAddress("D2Xp_y",    &D2Xp_y);
    theTree->SetBranchAddress("D2Xp_z",    &D2Xp_z);
    theTree->SetBranchAddress("D2V_x",    &D2V_x);
    theTree->SetBranchAddress("D2V_y",    &D2V_y);
    theTree->SetBranchAddress("D2V_z",    &D2V_z);
    theTree->SetBranchAddress("D2Vp_x",    &D2Vp_x);
    theTree->SetBranchAddress("D2Vp_y",    &D2Vp_y);
    theTree->SetBranchAddress("D2Vp_z",    &D2Vp_z);
    theTree->SetBranchAddress("D3pU_x",    &D3pU_x);
    theTree->SetBranchAddress("D3pUp_x",    &D3pUp_x);
    theTree->SetBranchAddress("D3pX_x",    &D3pX_x);
    theTree->SetBranchAddress("D3pXp_x",    &D3pXp_x);
    theTree->SetBranchAddress("D3pV_x",    &D3pV_x);
    theTree->SetBranchAddress("D3pVp_x",    &D3pVp_x);
    theTree->SetBranchAddress("D3pU_y",    &D3pU_y);
    theTree->SetBranchAddress("D3pUp_y",    &D3pUp_y);
    theTree->SetBranchAddress("D3pX_y",    &D3pX_y);
    theTree->SetBranchAddress("D3pXp_y",    &D3pXp_y);
    theTree->SetBranchAddress("D3pV_y",    &D3pV_y);
    theTree->SetBranchAddress("D3pVp_y",    &D3pVp_y);
    theTree->SetBranchAddress("D3pU_z",    &D3pU_z);
    theTree->SetBranchAddress("D3pUp_z",    &D3pUp_z);
    theTree->SetBranchAddress("D3pX_z",    &D3pX_z);
    theTree->SetBranchAddress("D3pXp_z",    &D3pXp_z);
    theTree->SetBranchAddress("D3pV_z",    &D3pV_z);
    theTree->SetBranchAddress("D3pVp_z",    &D3pVp_z);
    theTree->SetBranchAddress("D3mU_x",    &D3mU_x);
    theTree->SetBranchAddress("D3mUp_x",    &D3mUp_x);
    theTree->SetBranchAddress("D3mX_x",    &D3mX_x);
    theTree->SetBranchAddress("D3mXp_x",    &D3mXp_x);
    theTree->SetBranchAddress("D3mV_x",    &D3mV_x);
    theTree->SetBranchAddress("D3mVp_x",    &D3mVp_x);
    theTree->SetBranchAddress("D3mU_y",    &D3mU_y);
    theTree->SetBranchAddress("D3mUp_y",    &D3mUp_y);
    theTree->SetBranchAddress("D3mX_y",    &D3mX_y);
    theTree->SetBranchAddress("D3mXp_y",    &D3mXp_y);
    theTree->SetBranchAddress("D3mV_y",    &D3mV_y);
    theTree->SetBranchAddress("D3mVp_y",    &D3mVp_y);
    theTree->SetBranchAddress("D3mU_z",    &D3mU_z);
    theTree->SetBranchAddress("D3mUp_z",    &D3mUp_z);
    theTree->SetBranchAddress("D3mX_z",    &D3mX_z);
    theTree->SetBranchAddress("D3mXp_z",    &D3mXp_z);
    theTree->SetBranchAddress("D3mV_z",    &D3mV_z);
    theTree->SetBranchAddress("D3mVp_z",    &D3mVp_z);      
    theTree->SetBranchAddress("gpx",    &gpx);
    theTree->SetBranchAddress("gpy",    &gpy);
    theTree->SetBranchAddress("gpz",    &gpz);
    theTree->SetBranchAddress("gvz",    &gvz);
    
    std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
    TStopwatch sw;
    sw.Start();
    
    Int_t nentries = (Int_t)theTree->GetEntries(); 
    for(Long64_t ientry=0; ientry< nentries; ientry++){theTree->GetEntry(ientry);        
      if(n_tracks > 0 ){
	for(Long64_t itrack=0; itrack< n_tracks; itrack++){
	  if(D0Xp_x[itrack]<100 && D0Xp_x[itrack]<100 && D0Xp_y[itrack]<100 && D0Xp_y[itrack]<100 && D0U_x[itrack]<100 && D0U_x[itrack]<100 && D0U_y[itrack]<100 && D0U_y[itrack]<100 && D0Up_x[itrack]<100 && D0Up_x[itrack]<100 && D0Up_y[itrack]<100 && D0Up_y[itrack]<100
	     && D0V_x[itrack]<100 && D0V_x[itrack]<100 && D0V_y[itrack]<100 && D0V_y[itrack]<100 && D0Vp_x[itrack]<100 && D0Vp_x[itrack]<100 && D0Vp_y[itrack]<100 && D0Vp_y[itrack]<100 && D2Xp_x[itrack]<100 && D2Xp_x[itrack]<100 && D2Xp_y[itrack]<100 && D2Xp_y[itrack]<100
	     && D2X_x[itrack]<100 && D2X_x[itrack]<100 && D2X_y[itrack]<100 && D2X_y[itrack]<100 && D2U_x[itrack]<100 && D2U_x[itrack]<100 && D2U_y[itrack]<100 && D2U_y[itrack]<100 && D2Up_x[itrack]<100 && D2Up_x[itrack]<100 && D2Up_y[itrack]<100 && D2Up_y[itrack]<100
	     && D2V_x[itrack]<100 && D2V_x[itrack]<100 && D2Vp_y[itrack]<100 && D2Vp_y[itrack]<100 ){
	    if(D3pU_x[itrack]<100 || D3mU_x[itrack]<100){
	      
	      Sq_px_st1=sq_px_st1[itrack];
	      Sq_py_st1=sq_py_st1[itrack];
	      Sq_pz_st1=sq_pz_st1[itrack];
	      Sq_px_st2=sq_px_st2[itrack];
	      Sq_py_st2=sq_py_st2[itrack];
	      Sq_pz_st2=sq_pz_st2[itrack];
	      d0X_x=D0X_x[itrack];
	      d0X_y=D0X_y[itrack];
	      d0X_z=D0X_z[itrack];
	      d0Xp_x=D0Xp_x[itrack];
	      d0Xp_y=D0Xp_y[itrack];
	      d0Xp_z=D0Xp_z[itrack];
	      d0U_x=D0U_x[itrack];
	      d0U_y=D0U_y[itrack];
	      d0U_z=D0U_z[itrack];
	      d0Up_x=D0Up_x[itrack];
	      d0Up_y=D0Up_y[itrack];
	      d0Up_z=D0Up_z[itrack];
	      d0V_x=D0V_x[itrack];
	      d0V_y=D0V_y[itrack];
	      d0V_z=D0V_z[itrack];
	      d0Vp_x=D0Vp_x[itrack];
	      d0Vp_y=D0Vp_y[itrack];
	      d0Vp_z=D0Vp_z[itrack];
	      d2X_x=D2X_x[itrack];
	      d2X_y=D2X_y[itrack];
	      d2X_z=D2X_z[itrack];
	      d2Xp_x=D2Xp_x[itrack];
	      d2Xp_y=D2Xp_y[itrack];
	      d2Xp_z=D2Xp_z[itrack];
	      d2U_x=D2U_x[itrack];
	      d2U_y=D2U_y[itrack];
	      d2U_z=D2U_z[itrack];
	      d2Up_x=D2Up_x[itrack];
	      d2Up_y=D2Up_y[itrack];
	      d2Up_z=D2Up_z[itrack];
	      d2V_x=D2V_x[itrack];
	      d2V_y=D2V_y[itrack];
	      d2V_z=D2V_z[itrack];
	      d2Vp_x=D2Vp_x[itrack];
	      d2Vp_y=D2Vp_y[itrack];
	      d2Vp_z=D2Vp_z[itrack];
	      
	      if(D3pU_x[itrack] < 100 && D3pX_x[itrack] < 100 && D3pXp_x[itrack] < 100 && D3pV_x[itrack]){	      
		d3pU_X=D3pU_x[itrack];
		d3pUp_X=D3pUp_x[itrack];
		d3pX_X=D3pX_x[itrack];
		d3pXp_X=D3pXp_x[itrack];
		d3pV_X=D3pV_x[itrack];
		d3pVp_X=D3pVp_x[itrack];
		d3pU_Y=D3pU_y[itrack];
		d3pUp_Y=D3pUp_y[itrack];
		d3pX_Y=D3pX_y[itrack];
		d3pXp_Y=D3pXp_y[itrack];
		d3pV_Y=D3pV_y[itrack];
		d3pVp_Y=D3pVp_y[itrack];
		d3pU_Z=D3pU_z[itrack];
		d3pUp_Z=D3pUp_z[itrack];
		d3pX_Z=D3pX_z[itrack];
		d3pXp_Z=D3pXp_z[itrack];
		d3pV_Z=D3pV_z[itrack];
		d3pVp_Z=D3pVp_z[itrack];
	      }
	      
	      if(D3mU_x[itrack] < 100 && D3mX_x[itrack] < 100 && D3mXp_x[itrack] < 100 && D3mV_x[itrack]){		 
		d3mU_X=D3mU_x[itrack];
		d3mUp_X=D3mUp_x[itrack];
		d3mX_X=D3mX_x[itrack];
		d3mXp_X=D3mXp_x[itrack];
		d3mV_X=D3mV_x[itrack];
		d3mVp_X=D3mVp_x[itrack];
		d3mU_Y=D3mU_y[itrack];
		d3mUp_Y=D3mUp_y[itrack];
		d3mX_Y=D3mX_y[itrack];
		d3mXp_Y=D3mXp_y[itrack];
		d3mV_Y=D3mV_y[itrack];
		d3mVp_Y=D3mVp_y[itrack];
		d3mU_Z=D3mU_z[itrack];
		d3mUp_Z=D3mUp_z[itrack];
		d3mX_Z=D3mX_z[itrack];
		d3mXp_Z=D3mXp_z[itrack];
		d3mV_Z=D3mV_z[itrack];
		d3mVp_Z=D3mVp_z[itrack];
	      }
	      
	      Gpx = gpx[itrack];
	      Gpy = gpy[itrack];
	      Gpz = gpz[itrack];
	      Gvz = gvz[itrack];   
	      
	      TString title = "MLP method";
	      px = (reader->EvaluateRegression( title ))[0];
	      py = (reader->EvaluateRegression( title ))[1];	 
	      pz = (reader->EvaluateRegression( title ))[2];	 
	      
	      regout.Fill();
	      
	    }
	  }
	}
      }
    }
    
    sw.Stop();
    std::cout << "--- End of event loop: "; sw.Print();  
    
  }//n_arg  
  
  delete reader;
  
  std::cout << "Data Processing is Compete!" << std::endl << std::endl; 
  
  outFile.Write(); // write to the output file
  outFile.Close(); // close the output file
  
}//end of main

