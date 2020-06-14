//my
#include "monopolyHist.h"

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <math.h>
#include <vector>

//root
#include <TVector2.h>
#include <TPolyLine.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TText.h>
#include <TMath.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TCrown.h>
#include <TArc.h>
#include <TROOT.h>
#include <TRandom3.h>
#include <TStyle.h>
#include <TPad.h>
#include <TString.h>
#include <TFile.h>
#include <TAxis.h>
#include <TVector2.h>

using namespace std;

monopolyHist::monopolyHist(const char* name, const char* title) : TH2Poly()
{
  m_histName = name;
  m_histTitle = title;
  SetName(m_histName.Data());
  SetTitle(m_histTitle.Data());
  SetInitialParametersByDefault();
  SetUpVerticesMap();

  Double_t x[5] = {m_verticesMapX[0],m_verticesMapX[1],m_verticesMapX[2],m_verticesMapX[3],m_verticesMapX[4]}; 
  Double_t y[5] = {m_verticesMapY[0],m_verticesMapY[1],m_verticesMapY[2],m_verticesMapY[3],m_verticesMapY[4]}; 

  cout<<m_verticesMapX[3]<<endl;

  Double_t dx;
  Double_t dy;
  Double_t xtop;
  Double_t ytop;

  //TRandom3 *rnd = new TRandom3(123123);

  for(Int_t i = 0;i<11;i++){
    dx = m_x0;
    dy = m_y0 + (m_dl + m_l)*i;
    ytop = dy;
    makeTranslation( dx, dy, x, y);
    AddBin(5,x,y);
  }
  
  for(Int_t i = 1;i<11;i++){
    dx = m_x0 + (m_dl + m_l)*i;
    xtop = dx;
    makeTranslation( dx, dy, x, y);
    AddBin(5,x,y);
  }
  
  for(Int_t i = 1;i<11;i++){
    dx = xtop;
    dy = ytop - (m_dl + m_l)*i;
    makeTranslation( dx, dy, x, y);
    AddBin(5,x,y);
  }
  
  for(Int_t i = 1;i<10;i++){
    dx = xtop - (m_dl + m_l)*i;
    dy = m_y0;
    makeTranslation( dx, dy, x, y);
    AddBin(5,x,y);
  }
  
}

monopolyHist::~monopolyHist(){
}

void monopolyHist::makeTranslation( Double_t dx, Double_t dy, Double_t *x, Double_t *y){
  for(Int_t i = 0;i<5;i++){
    x[i] = m_verticesMapX[i] + dx;
    y[i] = m_verticesMapY[i] + dy;
  }
}

void monopolyHist::DrawHisto( TString opt = "ZCOLOT text same", TString outDirName = "./"){
  TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
  c1->SetTitle(m_histTitle.Data());
  c1->SetName(m_histName.Data());
  c1->SetRightMargin(0.17);
  c1->SetLeftMargin(0.12);
  c1->SetTopMargin(0.15);
  c1->SetBottomMargin(0.15);
  ///////////////////////////////////////////////////////////////
  TH2F *frame = new TH2F("h2","h2",40,-1,12,40, -1,12);
  frame->GetXaxis()->SetTitle("x (mm)");
  frame->GetYaxis()->SetTitle("y (mm)");
  frame->GetXaxis()->CenterTitle();
  frame->GetYaxis()->CenterTitle();
  frame->GetYaxis()->SetTitleOffset(1.5);
  frame->SetStats(kFALSE);
  frame->SetTitle("");
  frame->Draw();
  ///////////////////////////////////////////////////////////////
  Draw(opt.Data());  
  c1->Modified();
  c1->Update();
  if( outDirName.Length() > 0){
    std::cout<<"outDirName.Length() "<<outDirName.Length()<<std::endl;
    TString outnamePDF = outDirName; outnamePDF += m_histName; outnamePDF += ".pdf";
    TString outnameEPS = outDirName; outnameEPS += m_histName; outnameEPS += ".eps";
    c1->SaveAs(outnamePDF.Data());
    c1->SaveAs(outnameEPS.Data());
  }
}

/*
void monopolyHist::dumpVerticesMap(){
  unsigned int i;  
  for (auto& m: m_verticesMap){
    std::cout<<" --> Aerogel ring : "<<m.first << '\n';
    for( i = 0; i < m.second.size(); i++){
      std::cout<<"                    "<<setw(15)<<m.second[i].X()<<setw(15)<<m.second[i].Y()<<std::endl;
    }
  }
}
*/

void monopolyHist::SetUpVerticesMap(){
  m_verticesMapX[0] = m_l/2.0;
  m_verticesMapX[1] = -m_l/2.0;
  m_verticesMapX[2] = -m_l/2.0;
  m_verticesMapX[3] = m_l/2.0;
  m_verticesMapX[4] = m_l/2.0;

  m_verticesMapY[0] = m_l/2.0;
  m_verticesMapY[1] = m_l/2.0;
  m_verticesMapY[2] = -m_l/2.0;
  m_verticesMapY[3] = -m_l/2.0;
  m_verticesMapY[4] = m_l/2.0;
}

void monopolyHist::SetInitialParametersByDefault(){
  m_verboseLevel = 0;
  m_dl = 0.05;
  m_l = 0.95;
  m_x0 = (m_l + m_dl)/2.0;
  m_y0 = (m_l + m_dl)/2.0;
}
