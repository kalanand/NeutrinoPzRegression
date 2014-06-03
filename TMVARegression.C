// @(#)root/tmva $Id: TMVARegression.C,v 1.32 2009-03-07 16:42:15 stelzer Exp $
/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Root Macro: TMVARegression                                                     *
 *                                                                                *
 * This macro provides examples for the training and testing of the               *
 * TMVA classifiers.                                                              *
 *                                                                                *
 * As input data is used a toy-MC sample consisting of four Gaussian-distributed  *
 * and linearly correlated input variables.                                       *
 *                                                                                *
 * The methods to be used can be switched on and off by means of booleans, or     *
 * via the prompt command, for example:                                           *
 *                                                                                *
 *    root -l TMVARegression.C\(\"LD,MLP\"\)                                      *
 *                                                                                *
 * (note that the backslashes are mandatory)                                      *
 * If no method given, a default set is used.                                     *
 *                                                                                *
 * The output file "TMVAReg.root" can be analysed with the use of dedicated       *
 * macros (simply say: root -l <macro.C>), which can be conveniently              *
 * invoked through a GUI that will appear at the end of the run of this macro.    *
 **********************************************************************************/

#include <cstdlib>
#include <iostream> 
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TPluginManager.h"

#include "TMVARegGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#endif

using namespace TMVA;
   
void TMVARegression() 
{

   // this loads the library
   TMVA::Tools::Instance();

   //---------------------------------------------------------------
   std::cout << std::endl;
   std::cout << "==> Start TMVARegression" << std::endl;


   // Create a new root output file
   TString outfileName( "TMVAReg.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory will
   // then run the performance analysis for you.
   //
   // The first argument is the base of the name of all the
   // weightfiles in the directory weight/ 
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in 
   // front of the "Silent" argument in the option string
   TMVA::Factory *factory = new TMVA::Factory( "TMVARegression", outputFile, 
                                               "Color:DrawProgressBar" );


   // Define the input variables that shall be used for the MVA training
   factory->AddVariable("jet1Pt := JetPFCor_Pt[0]", 'F');
   factory->AddVariable("jet2Pt := JetPFCor_Pt[1]", 'F');
   factory->AddVariable("jet1Eta := JetPFCor_Eta[0]", 'F');
   factory->AddVariable("jet2Eta := JetPFCor_Eta[1]", 'F');
   // factory->AddVariable("jet1Phi := JetPFCor_Phi[0]", 'F');
   // factory->AddVariable("jet2Phi := JetPFCor_Phi[1]", 'F');
   // factory->AddVariable("jet1E := JetPFCor_E[0]", 'F');
   // factory->AddVariable("jet2E := JetPFCor_E[1]", 'F');


   factory->AddVariable("muE := W_muon_e", 'F');
   factory->AddVariable("muPt := W_muon_pt", 'F');
   factory->AddVariable("muEta := W_muon_eta", 'F');
   factory->AddVariable("muPhi := W_muon_phi", 'F');
   factory->AddVariable("met := event_met_pfmet", 'F');
   factory->AddVariable("metPhi := event_met_pfmetPhi", 'F');
   //factory->AddVariable("nPU := event_nPV", 'F');



   // ---------- spectators ----------------
   factory->AddSpectator("nuPt_gen := W_neutrino_pt_gen", "F");
   factory->AddSpectator("nuPz_gen := W_neutrino_pz_gen", "F");
   factory->AddSpectator("nuEta_gen := W_neutrino_eta_gen", "F");
   factory->AddSpectator("nuPhi_gen := W_neutrino_phi_gen", "F");
   factory->AddSpectator("muPt_gen := W_muon_pt_gen", "F");
   factory->AddSpectator("muPz_gen := W_muon_pz_gen", "F");
   factory->AddSpectator("muEta_gen := W_muon_eta_gen", "F");
   factory->AddSpectator("muPhi_gen := W_muon_phi_gen", "F");
   factory->AddSpectator("W_mass", "F");
   factory->AddSpectator("W_mt", "F");
   factory->AddSpectator("muPx := W_muon_px", "F");
   factory->AddSpectator("muPy := W_muon_py", "F");
   factory->AddSpectator("muPz := W_muon_pz", "F");
   factory->AddSpectator("nuPx := event_met_pfmet * cos(event_met_pfmetPhi)", "F");
   factory->AddSpectator("nuPy := event_met_pfmet * sin(event_met_pfmetPhi)", "F");
   factory->AddSpectator("W_pzNu1", "F");
   factory->AddSpectator("W_pzNu2", "F");


   // Add the variable carrying the regression target
   //factory->AddTarget  ( "W_mass_gen" ); 
   factory->AddTarget  ( "W_neutrino_pz_gen" ); 


   // read training and test data 
   TFile *input(0);
   TString fname = "RD_mu_HWWMH500_CMSSW532_private.root";
   input = TFile::Open( fname ); 
   std::cout << "--- TMVARegression : Using input file: " << input->GetName() << std::endl;
   TTree *regTree = (TTree*)input->Get("WJet");
   regTree->SetAlias("W_mass_gen", "sqrt(pow(W_muon_e_gen+W_neutrino_e_gen,2) - pow(W_muon_px_gen+W_neutrino_px_gen,2) - pow(W_muon_py_gen+W_neutrino_py_gen,2) - pow(W_muon_pz_gen+W_neutrino_pz_gen, 2))"); 

   // global event weights per tree (see below for setting event-wise weights)
   Double_t regWeight  = 1.0;   
 
   // ====== register trees ====================================================
   //
   factory->AddRegressionTree( regTree, regWeight );

   // Apply additional cuts on the signal and background samples (can be different)
   // TCut mycut = "(ggdevt == 2) && (W_mass_gen > 77.0 && W_mass_gen < 84.0)"; 
   // TCut mycut = "(ggdevt == 2) && (W_mass_gen > 77.0 && W_mass_gen < 84.0) && abs(W_neutrino_pz_gen -W_muon_pz_gen)<20.0"; 


   TCut mycut = "abs(W_mass_gen-80.4)< 6.3 && abs(W_neutrino_pz_gen - W_muon_pz_gen) < 80.4"; 

   // tell the factory to use all remaining events in the trees after training for testing:
  factory->PrepareTrainingAndTestTree( mycut, 
                                       "nTrain_Regression=0:nTest_Regression=0:SplitMode=Random:NormMode=NumEvents:!V" );


   // ---- Book MVA methods: Boosted Decision Trees

  // factory->BookMethod( TMVA::Types::kBDT, "BDT",
  //                      "!H:!V:NTrees=20:nEventsMin=5:BoostType=AdaBoostR2:SeparationType=RegressionVariance:nCuts=20:PruneMethod=CostComplexity:PruneStrength=30" );

  //  factory->BookMethod( TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=100:nEventsMin=5:BoostType=AdaBoostR2" );


  // factory->BookMethod( TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=200:BoostType=AdaBoostR2");

  factory->BookMethod( TMVA::Types::kBDT, "BDT","!H:!V:NTrees=200:BoostType=Bagging:nCuts=100" ); // 1st best


   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();    

   // --------------------------------------------------------------
   
   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVARegression is done!" << std::endl;      

   delete factory;

   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVARegGui( outfileName );
}
