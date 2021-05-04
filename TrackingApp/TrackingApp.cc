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
   Use["MLP"] = 1;

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
Float_t D0X_x_1=0;
Float_t D0X_y_1=0;
Float_t D0X_z_1=0;
Float_t D0X_x_2=0;
Float_t D0X_y_2=0;
Float_t D0X_z_2=0;
Float_t D0Xp_x_1=0;
Float_t D0Xp_y_1=0;
Float_t D0Xp_z_1=0;
Float_t D0Xp_x_2=0;
Float_t D0Xp_y_2=0;
Float_t D0Xp_z_2=0;
Float_t D0U_x_1=0;
Float_t D0U_y_1=0;
Float_t D0U_z_1=0;
Float_t D0U_x_2=0;
Float_t D0U_y_2=0;
Float_t D0U_z_2=0;
Float_t D0Up_x_1=0;
Float_t D0Up_y_1=0;
Float_t D0Up_z_1=0;
Float_t D0Up_x_2=0;
Float_t D0Up_y_2=0;
Float_t D0Up_z_2=0;
Float_t D0V_x_1=0;
Float_t D0V_y_1=0;
Float_t D0V_z_1=0;
Float_t D0V_x_2=0;
Float_t D0V_y_2=0;
Float_t D0V_z_2=0;
Float_t D0Vp_x_1=0;
Float_t D0Vp_y_1=0;
Float_t D0Vp_z_1=0;
Float_t D0Vp_x_2=0;
Float_t D0Vp_y_2=0;
Float_t D0Vp_z_2=0;
Float_t D2X_x_1=0;
Float_t D2X_y_1=0;
Float_t D2X_z_1=0;
Float_t D2X_x_2=0;
Float_t D2X_y_2=0;
Float_t D2X_z_2=0;
Float_t D2Xp_x_1=0;
Float_t D2Xp_y_1=0;
Float_t D2Xp_z_1=0;
Float_t D2Xp_x_2=0;
Float_t D2Xp_y_2=0;
Float_t D2Xp_z_2=0;
Float_t D2U_x_1=0;
Float_t D2U_y_1=0;
Float_t D2U_z_1=0;
Float_t D2U_x_2=0;
Float_t D2U_y_2=0;
Float_t D2U_z_2=0;
Float_t D2Up_x_1=0;
Float_t D2Up_y_1=0;
Float_t D2Up_z_1=0;
Float_t D2Up_x_2=0;
Float_t D2Up_y_2=0;
Float_t D2Up_z_2=0;
Float_t D2V_x_1=0;
Float_t D2V_y_1=0;
Float_t D2V_z_1=0;
Float_t D2V_x_2=0;
Float_t D2V_y_2=0;
Float_t D2V_z_2=0;
Float_t D2Vp_x_1=0;
Float_t D2Vp_y_1=0;
Float_t D2Vp_z_1=0;
Float_t D2Vp_x_2=0;
Float_t D2Vp_y_2=0;
Float_t D2Vp_z_2=0;
Float_t D3pX_X=0;
Float_t D3pX_Y=0;
Float_t D3pX_Z=0;
Float_t D3pXp_X=0;
Float_t D3pXp_Y=0;
Float_t D3pXp_Z=0;
Float_t D3pU_X=0;
Float_t D3pU_Y=0;
Float_t D3pU_Z=0;
Float_t D3pUp_X=0;
Float_t D3pUp_Y=0;
Float_t D3pUp_Z=0;
Float_t D3pV_X=0;
Float_t D3pV_Y=0;
Float_t D3pV_Z=0;
Float_t D3pVp_X=0;
Float_t D3pVp_Y=0;
Float_t D3pVp_Z=0;
Float_t D3mX_X=0;
Float_t D3mX_Y=0;
Float_t D3mX_Z=0;
Float_t D3mXp_X=0;
Float_t D3mXp_Y=0;
Float_t D3mXp_Z=0;
Float_t D3mU_X=0;
Float_t D3mU_Y=0;
Float_t D3mU_Z=0;
Float_t D3mUp_X=0;
Float_t D3mUp_Y=0;
Float_t D3mUp_Z=0;
Float_t D3mV_X=0;
Float_t D3mV_Y=0;
Float_t D3mV_Z=0;
Float_t D3mVp_X=0;
Float_t D3mVp_Y=0;
Float_t D3mVp_Z=0;
Float_t gpx_1;
Float_t gpx_2;
Float_t gpy_1;
Float_t gpy_2;
Float_t gpz_1;
Float_t gpz_2;
Float_t gvz_1;
Float_t gvz_2;
Float_t px_1;
Float_t py_1;
Float_t pz_1;
Float_t px_2;
Float_t py_2;
Float_t pz_2;
Float_t vz_1;
Float_t vz_2;

   reader->AddVariable("D0X_x_1", &D0X_x_1 );
   reader->AddVariable("D0X_y_1", &D0X_y_1 );
   reader->AddVariable("D0X_x_2", &D0X_x_2 );
   reader->AddVariable("D0X_y_2", &D0X_y_2 );
   reader->AddVariable("D0Xp_x_1", &D0Xp_x_1 );
   reader->AddVariable("D0Xp_y_1", &D0Xp_y_1 );
   reader->AddVariable("D0Xp_x_2", &D0Xp_x_2 );
   reader->AddVariable("D0Xp_y_2", &D0Xp_y_2 );
   reader->AddVariable("D0U_x_1", &D0U_x_1 );
   reader->AddVariable("D0U_y_1", &D0U_y_1 );
   reader->AddVariable("D0Up_x_1", &D0Up_x_1 );
   reader->AddVariable("D0Up_y_1", &D0Up_y_1 );
   reader->AddVariable("D0U_x_2", &D0U_x_2 );
   reader->AddVariable("D0U_y_2", &D0U_y_2 );
   reader->AddVariable("D0Up_x_2", &D0Up_x_2 );
   reader->AddVariable("D0Up_y_2", &D0Up_y_2 );
   reader->AddVariable("D0V_x_1", &D0V_x_1 );
   reader->AddVariable("D0V_y_1", &D0V_y_1 );
   reader->AddVariable("D0Vp_x_1", &D0Vp_x_1 );
   reader->AddVariable("D0Vp_y_1", &D0Vp_y_1 );
   reader->AddVariable("D0V_x_2", &D0V_x_2 );
   reader->AddVariable("D0V_y_2", &D0V_y_2 );
   reader->AddVariable("D0Vp_x_2", &D0Vp_x_2 );
   reader->AddVariable("D0Vp_y_2", &D0Vp_y_2 );
   reader->AddVariable("D2X_y_1", &D2X_y_1 );
   reader->AddVariable("D2X_x_1", &D2X_x_1 );
   reader->AddVariable("D2Xp_y_1", &D2Xp_y_1 );
   reader->AddVariable("D2Xp_x_1", &D2Xp_x_1 );
   reader->AddVariable("D2X_y_2", &D2X_y_2 );
   reader->AddVariable("D2X_x_2", &D2X_x_2 );
   reader->AddVariable("D2Xp_y_2", &D2Xp_y_2 );
   reader->AddVariable("D2Xp_x_2", &D2Xp_x_2 );
   reader->AddVariable("D2U_y_1", &D2U_y_1 );
   reader->AddVariable("D2U_x_1", &D2U_x_1 );
   reader->AddVariable("D2Up_y_1", &D2Up_y_1 );
   reader->AddVariable("D2Up_x_1", &D2Up_x_1 );
   reader->AddVariable("D2U_y_2", &D2U_y_2 );
   reader->AddVariable("D2U_x_2", &D2U_x_2 );
   reader->AddVariable("D2Up_y_2", &D2Up_y_2 );
   reader->AddVariable("D2Up_x_2", &D2Up_x_2 );
   reader->AddVariable("D2V_y_1", &D2V_y_1 );
   reader->AddVariable("D2V_x_1", &D2V_x_1 );
   reader->AddVariable("D2Vp_y_1", &D2Vp_y_1 );
   reader->AddVariable("D2Vp_x_1", &D2Vp_x_1 );
   reader->AddVariable("D2V_y_2", &D2V_y_2 );
   reader->AddVariable("D2V_x_2", &D2V_x_2 );
   reader->AddVariable("D2Vp_y_2", &D2Vp_y_2 );
   reader->AddVariable("D2Vp_x_2", &D2Vp_x_2 );
   reader->AddVariable("D3pX_X", &D3pX_X );
   reader->AddVariable("D3pX_Y", &D3pX_Y );
   reader->AddVariable("D3pXp_X", &D3pXp_X );
   reader->AddVariable("D3pXp_Y", &D3pXp_Y );
   reader->AddVariable("D3pU_X", &D3pU_X );
   reader->AddVariable("D3pU_Y", &D3pU_Y );
   reader->AddVariable("D3pUp_X", &D3pUp_X );
   reader->AddVariable("D3pUp_Y", &D3pUp_Y );
   reader->AddVariable("D3pV_X", &D3pV_X );
   reader->AddVariable("D3pV_Y", &D3pV_Y );
   reader->AddVariable("D3pVp_X", &D3pVp_X );
   reader->AddVariable("D3pVp_Y", &D3pVp_Y );
   reader->AddVariable("D3mX_X", &D3mX_X );
   reader->AddVariable("D3mX_Y", &D3mX_Y );
   reader->AddVariable("D3mXp_X", &D3mXp_X );
   reader->AddVariable("D3mXp_Y", &D3mXp_Y );
   reader->AddVariable("D3mU_X", &D3mU_X );
   reader->AddVariable("D3mU_Y", &D3mU_Y );
   reader->AddVariable("D3mUp_X", &D3mUp_X );
   reader->AddVariable("D3mUp_Y", &D3mUp_Y );
   reader->AddVariable("D3mV_X", &D3mV_X );
   reader->AddVariable("D3mV_Y", &D3mV_Y );
   reader->AddVariable("D3mVp_X", &D3mVp_X );
   reader->AddVariable("D3mVp_Y", &D3mVp_Y );
   
   reader->AddSpectator( "gpx_1",  &gpx_1 );
   reader->AddSpectator( "gpy_1",  &gpy_1 );   
   reader->AddSpectator( "gpz_1",  &gpz_1 );    
   reader->AddSpectator( "gpx_2",  &gpx_2 );
   reader->AddSpectator( "gpy_2",  &gpy_2 );   
   reader->AddSpectator( "gpz_2",  &gpz_2 );
   reader->AddSpectator( "gvz_1",  &gvz_1 );   
   reader->AddSpectator( "gvz_2",  &gvz_2 );    
   
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
   regout.Branch("D0X_x_1", &D0X_x_1 );
   regout.Branch("D0X_y_1", &D0X_y_1 );
   regout.Branch("D0X_x_2", &D0X_x_2 );
   regout.Branch("D0X_y_2", &D0X_y_2 );
   regout.Branch("D0Xp_x_1", &D0Xp_x_1 );
   regout.Branch("D0Xp_y_1", &D0Xp_y_1 );
   regout.Branch("D0Xp_x_2", &D0Xp_x_2 );
   regout.Branch("D0Xp_y_2", &D0Xp_y_2 );
   regout.Branch("D0U_x_1", &D0U_x_1 );
   regout.Branch("D0U_y_1", &D0U_y_1 );
   regout.Branch("D0Up_x_1", &D0Up_x_1 );
   regout.Branch("D0Up_y_1", &D0Up_y_1 );
   regout.Branch("D0U_x_2", &D0U_x_2 );
   regout.Branch("D0U_y_2", &D0U_y_2 );
   regout.Branch("D0Up_x_2", &D0Up_x_2 );
   regout.Branch("D0Up_y_2", &D0Up_y_2 );
   regout.Branch("D0V_x_1", &D0V_x_1 );
   regout.Branch("D0V_y_1", &D0V_y_1 );
   regout.Branch("D0Vp_x_1", &D0Vp_x_1 );
   regout.Branch("D0Vp_y_1", &D0Vp_y_1 );
   regout.Branch("D0V_x_2", &D0V_x_2 );
   regout.Branch("D0V_y_2", &D0V_y_2 );
   regout.Branch("D0Vp_x_2", &D0Vp_x_2 );
   regout.Branch("D0Vp_y_2", &D0Vp_y_2 );
   regout.Branch("D2X_y_1", &D2X_y_1 );
   regout.Branch("D2X_x_1", &D2X_x_1 );
   regout.Branch("D2Xp_y_1", &D2Xp_y_1 );
   regout.Branch("D2Xp_x_1", &D2Xp_x_1 );
   regout.Branch("D2X_y_2", &D2X_y_2 );
   regout.Branch("D2X_x_2", &D2X_x_2 );
   regout.Branch("D2Xp_y_2", &D2Xp_y_2 );
   regout.Branch("D2Xp_x_2", &D2Xp_x_2 );
   regout.Branch("D2U_y_1", &D2U_y_1 );
   regout.Branch("D2U_x_1", &D2U_x_1 );
   regout.Branch("D2Up_y_1", &D2Up_y_1 );
   regout.Branch("D2Up_x_1", &D2Up_x_1 );
   regout.Branch("D2U_y_2", &D2U_y_2 );
   regout.Branch("D2U_x_2", &D2U_x_2 );
   regout.Branch("D2Up_y_2", &D2Up_y_2 );
   regout.Branch("D2Up_x_2", &D2Up_x_2 );
   regout.Branch("D2V_y_1", &D2V_y_1 );
   regout.Branch("D2V_x_1", &D2V_x_1 );
   regout.Branch("D2Vp_y_1", &D2Vp_y_1 );
   regout.Branch("D2Vp_x_1", &D2Vp_x_1 );
   regout.Branch("D2V_y_2", &D2V_y_2 );
   regout.Branch("D2V_x_2", &D2V_x_2 );
   regout.Branch("D2Vp_y_2", &D2Vp_y_2 );
   regout.Branch("D2Vp_x_2", &D2Vp_x_2 );
   regout.Branch("D3pX_X", &D3pX_X );
   regout.Branch("D3pX_Y", &D3pX_Y );
   regout.Branch("D3pXp_X", &D3pXp_X );
   regout.Branch("D3pXp_Y", &D3pXp_Y );
   regout.Branch("D3pU_X", &D3pU_X );
   regout.Branch("D3pU_Y", &D3pU_Y );
   regout.Branch("D3pUp_X", &D3pUp_X );
   regout.Branch("D3pUp_Y", &D3pUp_Y );
   regout.Branch("D3pV_X", &D3pV_X );
   regout.Branch("D3pV_Y", &D3pV_Y );
   regout.Branch("D3pVp_X", &D3pVp_X );
   regout.Branch("D3pVp_Y", &D3pVp_Y );
   regout.Branch("D3mX_X", &D3mX_X );
   regout.Branch("D3mX_Y", &D3mX_Y );
   regout.Branch("D3mXp_X", &D3mXp_X );
   regout.Branch("D3mXp_Y", &D3mXp_Y );
   regout.Branch("D3mU_X", &D3mU_X );
   regout.Branch("D3mU_Y", &D3mU_Y );
   regout.Branch("D3mUp_X", &D3mUp_X );
   regout.Branch("D3mUp_Y", &D3mUp_Y );
   regout.Branch("D3mV_X", &D3mV_X );
   regout.Branch("D3mV_Y", &D3mV_Y );
   regout.Branch("D3mVp_X", &D3mVp_X );
   regout.Branch("D3mVp_Y", &D3mVp_Y );
   regout.Branch("gpy_1", &gpy_1 );
   regout.Branch("gpx_1", &gpx_1 );  
   regout.Branch("gpz_1", &gpz_1 );
   regout.Branch("gpy_2", &gpy_2 );
   regout.Branch("gpx_2", &gpx_2 );  
   regout.Branch("gpz_2", &gpz_2 );
   regout.Branch("gvz_1", &gvz_1 );
   regout.Branch("gvz_2", &gvz_2 );         
   regout.Branch("px_1", &px_1 );    
   regout.Branch("py_1", &py_1 );
   regout.Branch("pz_1", &pz_1 );
   regout.Branch("px_2", &px_2 );    
   regout.Branch("py_2", &py_2 );
   regout.Branch("pz_2", &pz_2 );
   regout.Branch("vz_1", &vz_1 );      
   regout.Branch("vz_2", &vz_2 );    
   
       
  for(int n_arg = optind; n_arg < Argc; n_arg++){ 
    
    TString input =w[n_arg];
    TFile inFile(input); // open the input file      
    
    if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
    }
    std::cout << " Using input file: " << inFile.GetName() << std::endl;


   TTree* theTree = (TTree*)inFile.Get("TreeR");
   std::cout << "--- Select signal sample" << std::endl;
   theTree->SetBranchAddress("D0X_x_1", &D0X_x_1 );
   theTree->SetBranchAddress("D0X_y_1", &D0X_y_1 );
   theTree->SetBranchAddress("D0X_x_2", &D0X_x_2 );
   theTree->SetBranchAddress("D0X_y_2", &D0X_y_2 );
   theTree->SetBranchAddress("D0Xp_x_1", &D0Xp_x_1 );
   theTree->SetBranchAddress("D0Xp_y_1", &D0Xp_y_1 );
   theTree->SetBranchAddress("D0Xp_x_2", &D0Xp_x_2 );
   theTree->SetBranchAddress("D0Xp_y_2", &D0Xp_y_2 );
   theTree->SetBranchAddress("D0U_x_1", &D0U_x_1 );
   theTree->SetBranchAddress("D0U_y_1", &D0U_y_1 );
   theTree->SetBranchAddress("D0Up_x_1", &D0Up_x_1 );
   theTree->SetBranchAddress("D0Up_y_1", &D0Up_y_1 );
   theTree->SetBranchAddress("D0U_x_2", &D0U_x_2 );
   theTree->SetBranchAddress("D0U_y_2", &D0U_y_2 );
   theTree->SetBranchAddress("D0Up_x_2", &D0Up_x_2 );
   theTree->SetBranchAddress("D0Up_y_2", &D0Up_y_2 );
   theTree->SetBranchAddress("D0V_x_1", &D0V_x_1 );
   theTree->SetBranchAddress("D0V_y_1", &D0V_y_1 );
   theTree->SetBranchAddress("D0Vp_x_1", &D0Vp_x_1 );
   theTree->SetBranchAddress("D0Vp_y_1", &D0Vp_y_1 );
   theTree->SetBranchAddress("D0V_x_2", &D0V_x_2 );
   theTree->SetBranchAddress("D0V_y_2", &D0V_y_2 );
   theTree->SetBranchAddress("D0Vp_x_2", &D0Vp_x_2 );
   theTree->SetBranchAddress("D0Vp_y_2", &D0Vp_y_2 );
   theTree->SetBranchAddress("D2X_y_1", &D2X_y_1 );
   theTree->SetBranchAddress("D2X_x_1", &D2X_x_1 );
   theTree->SetBranchAddress("D2Xp_y_1", &D2Xp_y_1 );
   theTree->SetBranchAddress("D2Xp_x_1", &D2Xp_x_1 );
   theTree->SetBranchAddress("D2X_y_2", &D2X_y_2 );
   theTree->SetBranchAddress("D2X_x_2", &D2X_x_2 );
   theTree->SetBranchAddress("D2Xp_y_2", &D2Xp_y_2 );
   theTree->SetBranchAddress("D2Xp_x_2", &D2Xp_x_2 );
   theTree->SetBranchAddress("D2U_y_1", &D2U_y_1 );
   theTree->SetBranchAddress("D2U_x_1", &D2U_x_1 );
   theTree->SetBranchAddress("D2Up_y_1", &D2Up_y_1 );
   theTree->SetBranchAddress("D2Up_x_1", &D2Up_x_1 );
   theTree->SetBranchAddress("D2U_y_2", &D2U_y_2 );
   theTree->SetBranchAddress("D2U_x_2", &D2U_x_2 );
   theTree->SetBranchAddress("D2Up_y_2", &D2Up_y_2 );
   theTree->SetBranchAddress("D2Up_x_2", &D2Up_x_2 );
   theTree->SetBranchAddress("D2V_y_1", &D2V_y_1 );
   theTree->SetBranchAddress("D2V_x_1", &D2V_x_1 );
   theTree->SetBranchAddress("D2Vp_y_1", &D2Vp_y_1 );
   theTree->SetBranchAddress("D2Vp_x_1", &D2Vp_x_1 );
   theTree->SetBranchAddress("D2V_y_2", &D2V_y_2 );
   theTree->SetBranchAddress("D2V_x_2", &D2V_x_2 );
   theTree->SetBranchAddress("D2Vp_y_2", &D2Vp_y_2 );
   theTree->SetBranchAddress("D2Vp_x_2", &D2Vp_x_2 );
   theTree->SetBranchAddress("D3pX_X", &D3pX_X );
   theTree->SetBranchAddress("D3pX_Y", &D3pX_Y );
   theTree->SetBranchAddress("D3pXp_X", &D3pXp_X );
   theTree->SetBranchAddress("D3pXp_Y", &D3pXp_Y );
   theTree->SetBranchAddress("D3pU_X", &D3pU_X );
   theTree->SetBranchAddress("D3pU_Y", &D3pU_Y );
   theTree->SetBranchAddress("D3pUp_X", &D3pUp_X );
   theTree->SetBranchAddress("D3pUp_Y", &D3pUp_Y );
   theTree->SetBranchAddress("D3pV_X", &D3pV_X );
   theTree->SetBranchAddress("D3pV_Y", &D3pV_Y );
   theTree->SetBranchAddress("D3pVp_X", &D3pVp_X );
   theTree->SetBranchAddress("D3pVp_Y", &D3pVp_Y );
   theTree->SetBranchAddress("D3mX_X", &D3mX_X );
   theTree->SetBranchAddress("D3mX_Y", &D3mX_Y );
   theTree->SetBranchAddress("D3mXp_X", &D3mXp_X );
   theTree->SetBranchAddress("D3mXp_Y", &D3mXp_Y );
   theTree->SetBranchAddress("D3mU_X", &D3mU_X );
   theTree->SetBranchAddress("D3mU_Y", &D3mU_Y );
   theTree->SetBranchAddress("D3mUp_X", &D3mUp_X );
   theTree->SetBranchAddress("D3mUp_Y", &D3mUp_Y );
   theTree->SetBranchAddress("D3mV_X", &D3mV_X );
   theTree->SetBranchAddress("D3mV_Y", &D3mV_Y );
   theTree->SetBranchAddress("D3mVp_X", &D3mVp_X );
   theTree->SetBranchAddress("D3mVp_Y", &D3mVp_Y );
   theTree->SetBranchAddress("gpy_1", &gpy_1 );
   theTree->SetBranchAddress("gpx_1", &gpx_1 );     
   theTree->SetBranchAddress("gpz_1", &gpz_1 );
   theTree->SetBranchAddress("gpy_2", &gpy_2 );
   theTree->SetBranchAddress("gpx_2", &gpx_2 );     
   theTree->SetBranchAddress("gpz_2", &gpz_2 );
   theTree->SetBranchAddress("gvz_1", &gvz_1 );
   theTree->SetBranchAddress("gvz_2", &gvz_2 );      
           

   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {

      theTree->GetEntry(ievt);

         TString title = "MLP method";
         px_1 = (reader->EvaluateRegression( title ))[0];
         py_1 = (reader->EvaluateRegression( title ))[1];	 
         pz_1 = (reader->EvaluateRegression( title ))[2];
         px_2 = (reader->EvaluateRegression( title ))[3];
         py_2 = (reader->EvaluateRegression( title ))[4];	 
         pz_2 = (reader->EvaluateRegression( title ))[5];
         vz_1 = (reader->EvaluateRegression( title ))[6];
         vz_2 = (reader->EvaluateRegression( title ))[7];	 	 	 
	 	 
         regout.Fill();
   }
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();

  }//n_arg  

   delete reader;
   
   std::cout << "Data Processing is Compete!" << std::endl << std::endl; 
    
   outFile.Write(); // write to the output file
   outFile.Close(); // close the output file

}//end of main

