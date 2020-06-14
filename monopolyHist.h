#pragma once

//root
#include <TObject.h>
#include <TH2Poly.h>
#include <TGraph.h>
#include <TVector2.h>

//c, c++
#include <string>
#include <vector>
#include <map>

class monopolyHist: public TH2Poly {
 public:
  
  monopolyHist(const char* name, const char* title);
  ~monopolyHist();
  void DrawHisto( TString opt, TString outDirName);
  //Int_t GetBinIDFromRingColumn( Int_t ring, Int_t column);
  
 private:

  void SetInitialParametersByDefault();

  void SetUpVerticesMap();

  //void dumpVerticesMap();

  void makeTranslation( Double_t dx, Double_t dy, Double_t *x, Double_t *y);

  //Verbose level
  Int_t m_verboseLevel;
  Double_t m_l;
  Double_t m_dl;
  Double_t m_x0;
  Double_t m_y0;

  Double_t m_verticesMapX[5];
  Double_t m_verticesMapY[5];

  TString m_histName;
  TString m_histTitle;

};
