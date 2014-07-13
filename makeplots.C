#include <cmath>

void makeplots() {
   TFile *f = new TFile("TMVAReg.root");
   TTree* tree = (TTree*) f->Get("TestTree");

   tree->SetAlias("mWW_gen", "sqrt(pow(muE_gen+nuE_gen+jet1E_gen+jet2E_gen,2) - pow(muPx_gen+nuPx_gen+jet1Px_gen+jet2Px_gen,2) - pow(muPy_gen+nuPy_gen+jet1Py_gen+jet2Py_gen,2) - pow(muPz_gen+nuPz_gen+jet1Pz_gen+jet2Pz_gen,2))"); 

   tree->SetAlias("mWW_reco", "sqrt(pow(muE+ sqrt(W_pzNu1**2+met**2)+jet1E+jet2E,2) - pow(muPx+nuPx+jet1Px+jet2Px,2) - pow(muPy+nuPy+jet1Py+jet2Py,2) - pow(muPz+W_pzNu1+jet1Pz+jet2Pz,2))"); 

   tree->SetAlias("mWW_reco2", "sqrt(pow(muE+ sqrt(W_pzNu2**2+met**2)+jet1E+jet2E,2) - pow(muPx+nuPx+jet1Px+jet2Px,2) - pow(muPy+nuPy+jet1Py+jet2Py,2) - pow(muPz+W_pzNu2+jet1Pz+jet2Pz,2))"); 


   tree->SetAlias("mWW_reg", "sqrt(pow(muE+ sqrt(BDT**2+met**2)+jet1E+jet2E,2) - pow(muPx+nuPx+jet1Px+jet2Px,2) - pow(muPy+nuPy+jet1Py+jet2Py,2) - pow(muPz+BDT+jet1Pz+jet2Pz,2))"); 


   TCut mycut = "";


   TH1D* diffPz = new TH1D("diffPz", "", 100, -100, 100);
   diffPz->GetXaxis()->SetTitle("#nu_pz - #nu_pz_gen (GeV)");
   diffPz->GetXaxis()->SetTitleSize(0.05);
   diffPz->GetXaxis()->SetLabelSize(0.05);
   diffPz->GetYaxis()->SetLabelSize(0.05);
   diffPz->GetXaxis()->SetTitleOffset(0.9);
   diffPz->SetLineWidth(2);
   diffPz->SetLineColor(2);
   tree->Draw("(BDT - W_neutrino_pz_gen) >> diffPz", mycut, "goff");

   TH1D* diffPza = diffPz->Clone("diffPza");
   diffPza->SetLineColor(4);
   TH1D* diffPza2 = diffPza->Clone("diffPza2");
   diffPza2->SetLineStyle(2);
   tree->Draw("(W_pzNu1 - W_neutrino_pz_gen) >> diffPza", mycut, "goff");
   tree->Draw("(W_pzNu2 - W_neutrino_pz_gen) >> diffPza2", mycut, "goff");


   TH1D* mWWreco = new TH1D("mWWreco", "", 70, 100, 800);
   mWWreco->GetXaxis()->SetTitle("m_{WW} (GeV)");
   mWWreco->GetXaxis()->SetTitleSize(0.05);
   mWWreco->GetXaxis()->SetLabelSize(0.05);
   mWWreco->GetYaxis()->SetLabelSize(0.05);
   mWWreco->GetXaxis()->SetTitleOffset(0.9);
   mWWreco->SetLineWidth(2);
   mWWreco->SetLineColor(4);
   TH1D* mWWreco2 = mWWreco->Clone("mWWreco2");
   mWWreco2->SetLineStyle(2);
   TH1D* mWWgen = mWWreco->Clone("mWWgen");
   mWWgen->SetLineColor(1);
   tree->Draw("mWW_reco >> mWWreco", mycut, "goff");
   tree->Draw("mWW_reco2 >> mWWreco2", mycut, "goff");
   tree->Draw("mWW_gen >> mWWgen", mycut, "goff");

   TH1D* mWWreg = mWWreco->Clone("mWWreg");
   mWWreg->SetLineColor(2);
   tree->Draw("mWW_reg >> mWWreg", mycut, "goff");


   gStyle->SetOptStat("mer"); 
   TCanvas *c1 = new TCanvas("c1","", 500, 500);
   diffPz->Draw();
   gPad->Update();
   TPaveStats *st0 = (TPaveStats*) diffPz->FindObject("stats");
   st0->SetName("stats0");
   st0->SetX1NDC(0.65); //new x start position
   st0->SetX2NDC(0.97); //new x end position
   st0->SetTextColor(2);
   diffPz->GetListOfFunctions()->Add(st0);
   diffPza->Draw("sames");
   gPad->Update();
   TPaveStats *st00 = (TPaveStats*) diffPza->FindObject("stats");
   st00->SetName("stats2");
   st00->SetX1NDC(0.65); //new x start position
   st00->SetX2NDC(0.97); //new x end position
   st00->SetY1NDC(0.68); //new y start position
   st00->SetY2NDC(0.8); //new y end position
   st00->SetTextColor(4);
   diffPza->GetListOfFunctions()->Add(st00);
   diffPza2->Draw("same");
   TLine* l1 = new TLine(0, 0, 0, 1640);
   l1->SetLineWidth(2);
   l1->Draw();
   TLegend* legend = new TLegend(0.6,0.4,0.97,0.6);
   legend->AddEntry( l1, "MC generated", "l");  
   legend->AddEntry( diffPza, "Analytic solution 1", "l"); 
   legend->AddEntry( diffPza2, "Analytic solution 2", "l");  
   legend->AddEntry( diffPz, "Regression", "l");  
   legend->SetFillColor(0);
   legend->Draw();
   c1->SaveAs("NuPz_diff.pdf");
   c1->SaveAs("NuPz_diff.png");
   c1->SaveAs("NuPz_diff.root");



   TCanvas *c2 = new TCanvas("c2","", 500, 500);
   mWWgen->Draw();
   gPad->Update();
   TPaveStats *st0 = (TPaveStats*) mWWgen->FindObject("stats");
   st0->SetName("stats0");
   st0->SetX1NDC(0.3); //new x start position
   st0->SetX2NDC(0.52); //new x end position
   mWWgen->GetListOfFunctions()->Add(st0);
   mWWreco->Draw("sames");
   gPad->Update();
   TPaveStats *st = (TPaveStats*) mWWreco->FindObject("stats");
   st->SetName("stats1");
   st->SetX1NDC(0.53); //new x start position
   st->SetX2NDC(0.75); //new x end position
   st->SetTextColor(4);
   mWWreco->GetListOfFunctions()->Add(st);
   mWWreg->Draw("sames");
   gPad->Update();
   TPaveStats *st2 = (TPaveStats*) mWWreg->FindObject("stats");
   st2->SetName("stats2");
   st2->SetX1NDC(0.76); //new x start position
   st2->SetX2NDC(0.98); //new x end position
   st2->SetTextColor(2);
   mWWreg->GetListOfFunctions()->Add(st2);
   mWWreg->Draw("same");
   mWWreco2->Draw("same");
   TLegend* legend = new TLegend(0.51,0.45,0.88,0.65);
   legend->AddEntry( mWWgen, "MC generated", "l");  
   legend->AddEntry( mWWreco, "Analytic solution 1", "l");  
   legend->AddEntry( mWWreco2, "Analytic solution 2", "l");  
   legend->AddEntry( mWWreg, "Regression", "l");  
   legend->SetFillColor(0);
   legend->Draw();
   c2->SaveAs("NuPz_mWW.pdf");
   c2->SaveAs("NuPz_mWW.png");
   c2->SaveAs("NuPz_mWW.root");
}
