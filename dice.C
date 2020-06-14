Int_t genDice(TRandom3 *rnd);

Int_t dice(){

  TH1D *h1 = new TH1D("h1","h1",19,-0.5,18.5);

  TRandom3 *rnd = new TRandom3(123123);

  for(Int_t i = 0;i<100000;i++){
    //h1->Fill(rnd->Uniform(-0.5,12.5));
    //h1->Fill(rnd->Uniform(0.5,6.5) + rnd->Uniform(0.5,6.5));
    h1->Fill(genDice(rnd) + genDice(rnd) + genDice(rnd),1.0/1000.0);
  }

  h1->Draw();

  h1->SetMinimum(0);


  return 0;
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
