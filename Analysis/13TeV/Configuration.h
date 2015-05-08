#include <vector>
#include <string>
#include <iostream>

#include "TROOT.h"
#include "TChain.h"
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TSystem.h"
#include "TFile.h"
#include "TDatime.h"
#include "TLegend.h"
#include "TMath.h"
#include "TGraphErrors.h"


int version = 41;
bool OnlyEssential=true;
TString BabyDir = "/net/cms26/cms26r0/jaehyeok/baby/Fatjet/13TeV/";
//TString BabyDir = "/Users/heller/Jae/ntuples/Z_sample/";
//TString BabyDir = "/cms5r0/ald77/archive/20150428/skim/";

bool status =true;
bool manuel=false;
bool hasQ=false;
float lumi = 3.0;

    //"/Users/heller/Jae/ntuples/JetPt20_04April_NoSkim/";

  //"/Users/heller/Jae/ntuples/HT750MET250_JetPt20_04April/";
  //"/Users/heller/Jae/ntuples/HT750MET250_JetPt20/";
  //"/Users/heller/Jae/ntuples/HT750MET250/";
  //"/net/top/homes/rohan/MJ/Analysis/13TeV/Phys14/";
  //  "/net/cms26/cms26r0/jaehyeok/baby/Fatjet/13TeV/Phys14NoSkim/";
  // "/net/cms26/cms26r0/jaehyeok/baby/Fatjet/13TeV/";
  //"/net/cms26/cms26r0/jaehyeok/baby/Fatjet/13TeV/Phys14/HT750MET250/";
  //"/Users/jaehyeok/Research/Tools/fastjet-3.0.6/example/babies/13TeV/HT750MET250/";


/*
TString study = "mT_extrapolation";



char* sysname[] = {"_nISR","_ISRpT3","_ISRpT4"};
int nsys=3;

int nregion=8;
char* Regions[] = {"1B_hi_mT","1B_lo_mT","1B_sl","1B_ll","2B_hi_mT","2B_lo_mT","2B_sl","2B_ll"};
//int SRthres=8;
*/
/*
TString study = "B_FJ";

char* sysname[] = {""};
int nsys=1;

int nregion=4;
char* Regions[] = {"SR0_lowmT","SR1_lowmT","SRstats1_lowmT","SRstats_lowmT"};
//"SRincl","SR0","SR1","SRstats1","SRstats"
int SRthres=5; */

/*TString study = "counts";

char* sysname[] = {""};
int nsys=1;

int nregion=1;
char* Regions[] = {"baseline_1B"};
int SRthres=2;
*/
/*
TString study = "full_analysis";

char* sysname[] = {"_nISR","_ISRpT3"};
int nsys=2;

int nregion=5;
char* Regions[] = {"1BCRincl","1BCRincl_lowMET","VR_2l","SRincl","SRincl_lowMET"};
int SRthres=1;
*/
//39
TString study = "Residuals_3ifb";

char* sysname[] = {"_MC_is_infallible","_ISRpT3","_nISR"};
int nsys=3;

int nregion=10;
char* Regions[] = {"1BCRincl","1BCRincl_lowMET","lowmTCR","lowmTlowMETCR","VR_2l","VR_2l_and_1l1vl","VR_2l_and_1l1vlalt","SRincl_lowMET","SRincl","SRincl_highMET"};
int SRthres=3;
/*
TString study = "counts";

char* sysname[] = {""};
int nsys=1;

int nregion=1;
char* Regions[] = {"baseline"};
int SRthres=2;
  */
/*
TString study = "weird_event_dump";

char* sysname[] = {""};
int nsys=1;

int nregion=1;
char* Regions[] = {"nothing"};
int SRthres=1;
*/



