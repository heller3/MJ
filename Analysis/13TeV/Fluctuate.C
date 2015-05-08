#include <iostream>
#include <iomanip> // for setw()

#include "TROOT.h"
#include "TChain.h"
#include "TString.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "TH2F.h"
#include "THStack.h"
#include "TSystem.h"
#include "TFile.h"
#include "TDatime.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TInterpreter.h"
#include "TLatex.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TArrow.h"
#include "TPaveStats.h"

#include "Make1DPlots.C"

using namespace std;

void Fluctuate(char* Region_measure, char* Region_check, TString HistName, char* sys, int nfluc)
{
 int NMergeBins=1;

 //Get hists from Region_check. 
 TFile* HistFile = TFile::Open(Form("Out/%s_v%i/HistFiles/Hist_%s_v%i.root",study.Data(),version, Region_check, version));
  TFile* HistFile2 = TFile::Open(Form("Out/%s_v%i/HistFiles/Hist_%s_v%i.root",study.Data(),version, Region_measure, version));
  TString axistitle="blank";
  TString syst = Form("%s",sys);
  if(syst.Contains("toppT")) axistitle = "Top pT SF";
  if(syst.Contains("ISRpT")) axistitle = "ISR pT SF";
  if(syst.Contains("nISR")) axistitle = "nISR SF";

  //TString HistName = "MJ";
  TH1F *h1_check_DATA[7], *h1_check_MC[7], *h1_check_T[7], *h1_check_TT_sl[7], *h1_check_TT_ll[7], *h1_check_TT_sys[7], *h1_check_TT[7], *h1_check_WJets[7], *h1_check_DY[7]; 
  TH1F *h1_check_f1500_100[7], *h1_check_f1200_800[7];


  TH1F *h1_measure_DATA[7], *h1_measure_MC[7], *h1_measure_T[7], *h1_measure_TT_sl[7], *h1_measure_TT_ll[7], *h1_measure_TT_sys[7], *h1_measure_TT[7], *h1_measure_WJets[7], *h1_measure_DY[7]; 
  TH1F *h1_measure_f1500_100[7], *h1_measure_f1200_800[7];

  TH1F * h1_resids[7];
  
  TCanvas *c = new TCanvas("c","c",1200,800); 
  c->Divide(3,2);
  for(unsigned int i=2; i<7; i++) {
    c->cd(i-1);
    
    h1_check_T[i]         = (TH1F*)HistFile->Get(Form("h1_T_%s_%s_%ifatjet", Region_check,HistName.Data(), i));                                                    
    h1_check_TT_sl[i]     = (TH1F*)HistFile->Get(Form("h1_TT_sl_%s_%s_%ifatjet",Region_check, HistName.Data(), i));
    h1_check_TT_ll[i]     = (TH1F*)HistFile->Get(Form("h1_TT_ll_%s_%s_%ifatjet", Region_check,HistName.Data(), i));
    h1_check_TT_sys[i]     = (TH1F*)HistFile->Get(Form("h1_TT_sys_%s%s_%s_%ifatjet", Region_check,sys,HistName.Data(), i));
    h1_check_WJets[i]     = (TH1F*)HistFile->Get(Form("h1_WJets_%s_%s_%ifatjet", Region_check,HistName.Data(), i));
    h1_check_DY[i]        = (TH1F*)HistFile->Get(Form("h1_DY_%s_%s_%ifatjet", Region_check,HistName.Data(), i)); 
    h1_check_f1500_100[i] = (TH1F*)HistFile->Get(Form("h1_T1tttt_f1500_100_%s_%s_%ifatjet", Region_check,HistName.Data(), i)); 
    h1_check_f1200_800[i] = (TH1F*)HistFile->Get(Form("h1_T1tttt_f1200_800_%s_%s_%ifatjet",Region_check, HistName.Data(), i)); 
   
    
    if(!h1_check_T[i]) cout<<"ERROR Fluctuate Histfile Get T"<<endl;    
    if(!h1_check_TT_sl[i]) cout<<"ERROR Fluctuate Histfile Get TT sl"<<endl;  
    if(!h1_check_TT_ll[i]) cout<<"ERROR Fluctuate Histfile Get TT ll"<<endl;
    if(!h1_check_TT_sys[i]) cout<<"ERROR Fluctuate Histfile Get TT sys "<<endl;
    if(!h1_check_WJets[i]) cout<<"ERROR Fluctuate Histfile Get Wjets"<<endl;     
    if(!h1_check_DY[i]) cout<<"ERROR Fluctuate Histfile Get DY"<<endl;
    if(!h1_check_f1500_100[i]) cout<<"ERROR Fluctuate Histfile Get noncomp"<<endl;
    if(!h1_check_f1200_800[i]) cout<<"ERROR Fluctuate Histfile Get compr"<<endl;


    h1_check_T[i]->Rebin(NMergeBins);
    h1_check_TT_sl[i]->Rebin(NMergeBins);
    h1_check_TT_ll[i]->Rebin(NMergeBins);
    h1_check_TT_sys[i]->Rebin(NMergeBins);
    h1_check_WJets[i]->Rebin(NMergeBins);
    h1_check_DY[i]->Rebin(NMergeBins);
    h1_check_f1500_100[i]->Rebin(NMergeBins);
    h1_check_f1200_800[i]->Rebin(NMergeBins);
        
    h1_check_TT[i] = (TH1F*)h1_check_TT_ll[i]->Clone();
    h1_check_TT[i]->Add(h1_check_TT_sl[i]);
   
    h1_measure_T[i]         = (TH1F*)HistFile2->Get(Form("h1_T_%s_%s_%ifatjet", Region_measure,HistName.Data(), i));
    h1_measure_TT_sl[i]     = (TH1F*)HistFile2->Get(Form("h1_TT_sl_%s_%s_%ifatjet",Region_measure, HistName.Data(), i));
    h1_measure_TT_ll[i]     = (TH1F*)HistFile2->Get(Form("h1_TT_ll_%s_%s_%ifatjet", Region_measure,HistName.Data(), i));
    h1_measure_TT_sys[i]     = (TH1F*)HistFile2->Get(Form("h1_TT_sys_%s%s_%s_%ifatjet", Region_measure,sys,HistName.Data(), i));
    h1_measure_WJets[i]     = (TH1F*)HistFile2->Get(Form("h1_WJets_%s_%s_%ifatjet", Region_measure,HistName.Data(), i));
    h1_measure_DY[i]        = (TH1F*)HistFile2->Get(Form("h1_DY_%s_%s_%ifatjet", Region_measure,HistName.Data(), i)); 
    h1_measure_f1500_100[i] = (TH1F*)HistFile2->Get(Form("h1_T1tttt_f1500_100_%s_%s_%ifatjet", Region_measure,HistName.Data(), i)); 
    h1_measure_f1200_800[i] = (TH1F*)HistFile2->Get(Form("h1_T1tttt_f1200_800_%s_%s_%ifatjet",Region_measure, HistName.Data(), i)); 
    
  
    if(!h1_measure_T[i]) cout<<"ERROR Fluctuate Histfile Get T"<<endl;    
    if(!h1_measure_TT_sl[i]) cout<<"ERROR Fluctuate Histfile Get TT sl"<<endl;  
    if(!h1_measure_TT_ll[i]) cout<<"ERROR Fluctuate Histfile Get TT ll"<<endl;
    if(!h1_measure_TT_sys[i]) cout<<"ERROR Fluctuate Histfile Get TT sys "<<endl;
    if(!h1_measure_WJets[i]) cout<<"ERROR Fluctuate Histfile Get Wjets"<<endl;     
    if(!h1_measure_DY[i]) cout<<"ERROR Fluctuate Histfile Get DY"<<endl;
    if(!h1_measure_f1500_100[i]) cout<<"ERROR Fluctuate Histfile Get noncomp"<<endl;
    if(!h1_measure_f1200_800[i]) cout<<"ERROR Fluctuate Histfile Get compr"<<endl;


    h1_measure_T[i]->Rebin(NMergeBins);
    h1_measure_TT_sl[i]->Rebin(NMergeBins);
    h1_measure_TT_ll[i]->Rebin(NMergeBins);
    h1_measure_TT_sys[i]->Rebin(NMergeBins);
    h1_measure_WJets[i]->Rebin(NMergeBins);
    h1_measure_DY[i]->Rebin(NMergeBins);
    h1_measure_f1500_100[i]->Rebin(NMergeBins);
    h1_measure_f1200_800[i]->Rebin(NMergeBins);
        
    h1_measure_TT[i] = (TH1F*)h1_measure_TT_ll[i]->Clone();
    h1_measure_TT[i]->Add(h1_measure_TT_sl[i]);

    

    //get pseudodata central value for Region_check
    h1_check_DATA[i]=(TH1F*)h1_check_TT_sys[i]->Clone(Form("h1_check_sys_data_%s_%ifatjet", HistName.Data(), i));
    h1_check_DATA[i]->Add(h1_check_WJets[i]);
    h1_check_DATA[i]->Add(h1_check_T[i]);
    h1_check_DATA[i]->Add(h1_check_DY[i]);
    Int_t nbins = h1_check_DATA[i]->GetXaxis()->GetNbins();
    float check_pseudodata = h1_check_DATA[i]->GetBinContent(nbins); //last bin

    //get pseudodata central value for Region_measure, and keep track of subtraction of minor backgrounds
    h1_measure_DATA[i]=(TH1F*)h1_measure_DY[i]->Clone(Form("h1_measure_sys_data_%s_%ifatjet", HistName.Data(), i));
    h1_measure_DATA[i]->Add(h1_measure_WJets[i]);
    h1_measure_DATA[i]->Add(h1_measure_T[i]);
    float measure_non_tt_subtraction = h1_measure_DATA[i]->GetBinContent(nbins);
    h1_measure_DATA[i]->Add(h1_measure_TT_sys[i]);
    float measure_pseudodata = h1_measure_DATA[i]->GetBinContent(nbins); //last bin
    

    //get mc prediction for Region_check
    h1_check_MC[i] = (TH1F*)h1_check_TT_sl[i]->Clone(Form("h1_check_MC_%s_%ifatjet", HistName.Data(), i));
    h1_check_MC[i]->Add(h1_check_TT_ll[i]);
    float check_ttbar_pred = h1_check_MC[i]->GetBinContent(nbins);
    h1_check_MC[i]->Add(h1_check_WJets[i]);
    h1_check_MC[i]->Add(h1_check_T[i]);
    h1_check_MC[i]->Add(h1_check_DY[i]);
    float check_MC = h1_check_MC[i]->GetBinContent(nbins); //last bin
    float check_non_tt_pred = check_MC - check_ttbar_pred;
  
    
    //get mc prediction for Region_measure
    h1_measure_MC[i] = (TH1F*)h1_measure_TT_sl[i]->Clone(Form("h1_measure_MC_%s_%ifatjet", HistName.Data(), i));
    h1_measure_MC[i]->Add(h1_measure_TT_ll[i]);
    float measure_ttbar_pred = h1_measure_MC[i]->GetBinContent(nbins);
    h1_measure_MC[i]->Add(h1_measure_WJets[i]);
    h1_measure_MC[i]->Add(h1_measure_T[i]);
    h1_measure_MC[i]->Add(h1_measure_DY[i]);
    float measure_MC = h1_measure_MC[i]->GetBinContent(nbins); //last bin
    

    
    //get SF from Region_measure. To fluctuate, need to know pseudodata central value
    
    //fill residual pseudodata SR - mc SR* SFCR
    //unc = stat unc on SF and stat unc on mc SR
    //mc SR:

    //init resid hist

    float resid_non_fluc = check_pseudodata - ((measure_pseudodata - measure_non_tt_subtraction)*check_ttbar_pred/measure_ttbar_pred +check_non_tt_pred);
    float mc_pred_non_fluc = ((measure_pseudodata - measure_non_tt_subtraction)*check_ttbar_pred/measure_ttbar_pred +check_non_tt_pred);
    h1_resids[i] = new TH1F(Form("h1_resids_%i",i),Form("h1_resids_%i",i),100,-10,10); 
    TRandom3 rand;
    rand.SetSeed(0);
    for(int ifluc=0; ifluc<nfluc; ifluc++){
      //flucuate check_pseudodata
      int fluc_check_pseudodata= rand.Poisson(check_pseudodata);
      //flucuate measure_pseudodata
      int fluc_measure_pseudodata= rand.Poisson(measure_pseudodata);

      //put together prediction for Region_check with fluctuation in measurement sample. Disallow negative SF due to fluctuation
      float prediction;
      if(fluc_measure_pseudodata > measure_non_tt_subtraction)
	{
	  prediction = ( check_ttbar_pred * (fluc_measure_pseudodata - measure_non_tt_subtraction)/measure_ttbar_pred ) + check_non_tt_pred;
	  // float error_on_diff = pow(fluc_measure_pseudodata + pow(unc_measure_non_tt_subtraction,2),0.5);
	  // SF_rel_unc = pow( error on diff ,2) + pow(unc_measure_ttbar_pred/measure_ttbar_pred,2),0.5); // add relative unc in quad
	}
      else prediction = check_non_tt_pred;
      
      //subtract and fill
      float resid = fluc_check_pseudodata - prediction;
      h1_resids[i]->Fill(resid);
      
    }
    TString StackTitle;
    if(i==6) StackTitle = "All fatjets";
    if(i==5) StackTitle = "5+ fatjets";
    h1cosmetic(h1_resids[i],          (char*)StackTitle.Data(),               kBlack, 1, 31,           "Pseudodata - Corrected Prediction [Events]");
    h1_resids[i]->SetStats("mr");
    h1_resids[i]->SetMaximum(nfluc/9);

      //cout<<"Resid non fluc:"<<resid_non_fluc<<endl;
    h1_resids[i]->Draw("hist");
    gPad->Update();
    TPaveStats *st = (TPaveStats*)gPad->GetPrimitive("stats");
    st->SetX1NDC(0.65);
    st->SetX2NDC(0.9);
    st->SetY1NDC(0.7);
    st->SetY2NDC(0.9);
    
    TLine line1 = TLine(resid_non_fluc,0,resid_non_fluc,nfluc/9);
    line1.SetLineStyle(2);
    line1.SetLineColor(13);
    line1.DrawLine(resid_non_fluc,0,resid_non_fluc,nfluc/9);

    TArrow line2 = TArrow(0.5,0.7,0.7,0.7,0.02,"|>");
    line2.SetLineColor(kBlack);
    line2.SetNDC();
    // line2.DrawLineNDC(0.5,0.7,0.7,0.7);
    
    // CMS Labels 
    float textSize = 0.04;

    TLatex *TexEnergyLumi = new TLatex(0.9,0.92,Form("#sqrt{s}=13 TeV, L = %.0f fb^{-1}", lumi));
    TexEnergyLumi->SetNDC();
    TexEnergyLumi->SetTextSize(textSize);
    TexEnergyLumi->SetTextAlign (31);
    TexEnergyLumi->SetLineWidth(2);

    TLatex *TexCMS = new TLatex(0.2,0.92,"CMS Preliminary");
    TexCMS->SetNDC();
    TexCMS->SetTextSize(textSize);
    TexCMS->SetLineWidth(2);
    TString prefluc = "Pre-fluctuation:";
    //TString mcpred = Form("#splitline{corrected MC:%.1f",mc_pred_non_fluc);
    TString datapred = Form("#splitline{Pseudodata:  %.1f}{Corrected MC:  %.1f}",check_pseudodata,mc_pred_non_fluc);
    //TString moretext = Form("Expected mean residual: %.3f",resid_non_fluc);
    // FIXME : need to add lepton flavor
    TString LabelExt = Form("N_{fatjet} = %i", i);
    if(i==5) LabelExt="N_{fatjet} >= 5";
    TLatex *TexExt;
    if(!doData) TexExt = new TLatex(0.85,0.7,LabelExt);
    else TexExt = new TLatex(0.85,0.65,LabelExt);
    TexExt->SetTextAlign (31);
    TexExt->SetNDC();
    TexExt->SetTextSize(textSize);
    TexExt->SetLineWidth(2);
    TLatex *mcpredlatex =  new TLatex(0.40,0.84,prefluc);
    mcpredlatex->SetTextAlign (31);
    mcpredlatex->SetNDC();
    mcpredlatex->SetTextSize(textSize);
    mcpredlatex->SetLineWidth(2);
    /*TLatex *morelatex =  new TLatex(0.40,0.7,moretext);
    morelatex->SetTextAlign (31);
    morelatex->SetNDC();
    morelatex->SetTextSize(textSize);
    morelatex->SetLineWidth(2);*/
    TLatex *datapredlatex =  new TLatex(0.48,0.77,datapred);
    datapredlatex->SetTextAlign (31);
    datapredlatex->SetNDC();
    datapredlatex->SetTextSize(textSize);
    datapredlatex->SetLineWidth(2);
    
    TexEnergyLumi->Draw("SAME");
    TexCMS->Draw("SAME");
    mcpredlatex->Draw("SAME");
    datapredlatex->Draw("SAME");
    //morelatex->Draw("SAME");
    //if(i!=6) TexExt->Draw("SAME");
    
  }


  c->Print( Form("Out/%s_v%i/Figures/Residuals_%s%s_%s_corrected_by_%s_v%i.pdf",study.Data(),version,HistName.Data(),sys,Region_check,Region_measure,version));
  HistFile->Close();
  HistFile2->Close();

  delete c;
}
