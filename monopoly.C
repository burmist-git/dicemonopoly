#if !defined(__CLING__)
//my
#include "monopolyHist.h"
#else 
//my
#include "monopolyHist.C"
#endif

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TList.h>
#include <TRandom3.h>

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <vector>

using namespace std;

Int_t getBinID(Int_t totnn);
Int_t genDice(TRandom3 *rnd);
Int_t genDice2(TRandom3 *rnd);

Int_t monopoly(TString layerName = "up", TString parName = "n"){
  TString h2name = "h2_monopoly";
  h2name += "_";
  h2name += layerName;
  h2name += "_";
  h2name += parName;
  TString h2title = "monopoly";
  h2title += " ";
  h2title += layerName;
  h2title += " ";
  h2title += parName;
  monopolyHist *monopo = new monopolyHist( h2name.Data(), h2title.Data());

  TRandom3 *rnd = new TRandom3(115);


  Int_t ntot = 1;
  //for(Int_t i = 0;i<50;i++)
  //monopo->SetBinContent(i,i);
  
  for(Int_t i = 0;i<20;i++){
    ntot = ntot + genDice(rnd) + genDice(rnd);
    //ntot = ntot + genDice2(rnd) + genDice2(rnd);
    monopo->SetBinContent(getBinID(ntot),monopo->GetBinContent(getBinID(ntot))+1);
  }

  monopo->DrawHisto("ZCOLOT text same","./");
  return 0;
}

Int_t getBinID(Int_t totnn){
  Int_t nn = totnn/40;
  return totnn - nn*40 + 1;
}

Int_t genDice(TRandom3 *rnd){
  Double_t x1 = rnd->Uniform(0,6);
  if(x1>=0 && x1<1){
    return 1;
  }
  if(x1>=1 && x1<2){
    return 2;
  }
  if(x1>=2 && x1<3){
    return 3;
  }
  if(x1>=3 && x1<4){
    return 4;
  }
  if(x1>=4 && x1<5){
    return 5;
  }
  if(x1>=5 && x1<6){
    return 6;
  }
  return 99;
}

Int_t genDice2(TRandom3 *rnd){
  Double_t x1 = rnd->Uniform(0,6);
  if(x1>=0 && x1<1){
    return 3;
  }
  if(x1>=1 && x1<2){
    return 3;
  }
  if(x1>=2 && x1<3){
    return 3;
  }
  if(x1>=3 && x1<4){
    return 4;
  }
  if(x1>=4 && x1<5){
    return 3;
  }
  if(x1>=5 && x1<6){
    return 3;
  }
  return 99;
}
