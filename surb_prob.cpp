/*Calculation of the number of neutrons at the top of the atmosphere.
Considering neutron decay and power law for the neutron energy spectrum.*/
{
  gStyle->SetPalette(1);
  const Float_t R=1.496e11;//1AU[m]
  const Int_t M_n=939.56;//MeV neutron rest-mass
  const Int_t tau=880.3;//mean life of neutrons 886
  const Float_t c=299792458;//celeritas
  const Int_t counts=930;//bin number
  const Float_t npart=1.0e+8;//Number of input events
  const Float_t alpha=-7.0;//Index spectrum
  const Float_t area=64.0;//Detector's Area[m^2] NM64=13.1
  //Hawaii=8[m^2],Chacaltaya=Mexico=Swiss=4.0,Norikura=64.0,Tibet=9.0
  const Int_t D=1;//distance from the source
  char dist[10];
  TGraph *gr[5],*gg[5];
  TMultiGraph *mg=new TMultiGraph;
  TMultiGraph *mp=new TMultiGraph;
  TLegend *legs[2];
  legs[0]=new TLegend(.7,.8,.95,.95);
  legs[1]=new TLegend(.7,.8,.95,.95);
  TCanvas *c1=new TCanvas("c1","Survival",0,0,800,600);
  c1->Divide(2,1,0.001,0.001);
  for(Int_t i=0;i<2;i++){
    c1->cd(i+1)->SetGridx();c1->cd(i+1)->SetGridy();c1->cd(i+1)->SetLogx();}
  c1->cd(1)->SetLogy();
  Float_t E_n[counts],P_E[counts],timmy[counts],sum=0,aux0;
  Float_t deltaT,gamma,beta,Etyp=100.0,suma=0,aux,aux2,omega;
  TH1F *Pow=new TH1F("PowerLaw","PowerLaw",counts/10,70.0,1000.0);
  //Float_t factor[5]={0.1,0.2,0.5,0.7,1.0};
  Float_t factor[D]={1.0};
  for(Int_t j=0;j<D;j++){
    sum=0;gamma=0;
  for(i=0;i<counts;i++){
    E_n[i]=70+(int)930*(i)/counts;
    gamma=1+E_n[i]/M_n;
    beta=TMath::Sqrt(1.0-1.0/(gamma*gamma));
    deltaT=factor[j]*(R/(c*beta));//-R/c);//delay from X-rays
    P_E[i]=TMath::Exp(-deltaT/(gamma*tau));
    timmy[i]=deltaT/60.;
    aux2=E_n[i]/Etyp;
    aux=1.0*P_E[i]*TMath::Power(aux2,alpha);
    sum+=aux;  //aux0=35.19*TMath::Power(aux2,alpha);suma+=aux0;??
    Pow->SetBinContent(i,aux);
    cout << i<<" "<<E_n[i] <<" "<<P_E[i]<<" "<<timmy[i];
    cout <<" "<<aux<<endl;
  }
  gr[j]=new TGraph(counts,E_n,P_E);
  gr[j]->SetLineColor(j+2);gr[j]->SetLineWidth(2);gr[j]->SetFillColor(0);
  //gr->Draw("AC");
  mg->Add(gr[j]);
  sprintf(dist,"%.1f AU",factor[j]);
  legs[0]->AddEntry(gr[j],dist);
  gg[j]=new TGraph(counts,E_n,timmy);
  gg[j]->SetLineColor(j+2);gg[j]->SetLineWidth(2);gg[j]->SetFillColor(0);
  legs[1]->AddEntry(gg[j],dist);
  mp->Add(gg[j]);
  //gg->Draw("AC");
  }
  gr[0]->GetYaxis()->SetRangeUser(0.001,1);
  //mg->GetXaxis()->SetTitle("Kinetic Energy[MeV]");
  //mg->GetYaxis()->SetTitle("Probability");
  c1->cd(1);
  mg->Draw("AC");  legs[0]->Draw();
  //mp->GetXaxis()->SetTitle("Kinetic Energy[MeV]");
  //mp->GetYaxis()->SetTitle("#Delta t[mins]");
  c1->cd(2);
  mp->Draw("AC");  //legs[1]->Draw();
  /**** Power Spectrum ******/
  TCanvas *c2=new TCanvas("c2","Neutron_Flux",0,0,800,600);
  c2->cd(1)->SetLogy();  c2->cd(1)->SetLogx();
  Pow->Draw(); Pow->Print();omega=(area/(4*TMath::Pi()*R*R));
  Float_t F01=npart/(omega*sum*10);suma=0;
  cout<<"Area "<<area<<" Sum "<<sum<<", F0 "<<F01<<" neutrons/MeV/sr"<<endl;
  for(i=0;i<counts;i++){//<=750
    E_n[i]=70+(int)930*(i)/counts;//(i*1)+50;
    aux2=E_n[i]/Etyp;
    aux0=E_n[i]*TMath::Power(aux2,alpha);
    suma+=aux0;
    //cout << i<<" "<<E_n[i] <<" "<<aux0<<endl;//1.8*aux0
  }
  Float_t f_E=F01*0.033*suma*10;//1.8*suma*10;
  cout << "Flux @Sun "<< f_E<<" neutrons/sr"<<endl;
}
