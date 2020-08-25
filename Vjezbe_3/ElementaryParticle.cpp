#include <ElementaryParticle.h>


    ElementaryParticle::ElementaryParticle(string name, bool is, double mass){
        nameParticle=name;
        isBoson = is;
        massParticle = mass;
        px = 0;
        py = 0;
        pz = 0;
        E = sqrt(px*px + py*py + pz*pz + massParticle*massParticle);
     

    }
    void ElementaryParticle::SetInfo( string name, bool is, double mass)
     {
       nameParticle = name;
       massParticle = mass;
       isBoson = is;
     }
    void ElementaryParticle::SetP(double _px, double _py, double _pz){
        px = _px;
        py = _py;
        pz = _pz;

    }
    ElementaryParticle::ElementaryParticle(){
        nameParticle="";
        isBoson = false;
        massParticle = 0.;
        px = 0;
        py = 0;
        pz = 0;
        E = sqrt(px*px + py*py + pz*pz + massParticle*massParticle);

    }
  
    // Member Functions() 
    void ElementaryParticle::printInfo() 
    { 
        if(isBoson==true)
        {
    
       cout << "Name of particle is " << nameParticle << ",mass of the particle is " << massParticle << "and the particle is boson"<<endl;
        }
       else
       {
           cout << "Name of particle is " << nameParticle << ",mass of the particle is " << massParticle << "and the particle isn't boson"<<endl;

       }
        
    } 
    void ElementaryParticle::printPt()
    {
       cout<< "P_t je " << sqrt(px*px+py*py) <<endl;
    }
    double ElementaryParticle::pt()
    {
       return sqrt(px*px+py*py);
    }

    void ElementaryParticle::bosonDecay(ElementaryParticle *particle1, ElementaryParticle *particle2)
    {
      if(isBoson != true)
     {
      cout<< "Raspad nije moguć"<< endl;
      return;
     }
     //srand((unsigned) time(0));
     randomNumber = (rand() % 1000) + 1;
     if(randomNumber<214)
     {
     particle1 -> SetInfo("W_boson", true, 80.38);
     particle2 -> SetInfo("W_boson", true, 80.38);
     }
     else if(randomNumber<214+64)
     {
     particle1 -> SetInfo("Tau_lepton", false, 1.77);
     particle2 -> SetInfo("Tau_lepton", false, 1.77);
     }
     else if(randomNumber<214+64+26)
     {
     particle1 -> SetInfo("Z_boson", true, 91.18);
     particle2 -> SetInfo("Z_boson", true, 91.18);
     }
     else
     {
     particle1 -> SetInfo("b_quark", false, 4.18);
     particle2 -> SetInfo("b_quark", false, 4.18);
     }
     //provjere
     /*particle1->printInfo();
     particle2->printInfo();*/

  random_number_x = rand() % 100 + 1;

  if(random_number_x == 100) // handle special case so the code does not crash
  {
    random_number_y = 0;
    random_number_z = 0;
  }
  else
  {
    random_number_y = rand() % (100 - random_number_x) + 1;
    random_number_z = 100 - random_number_x - random_number_y;
  }
     particle1->SetP(px*(random_number_x/100.),py*(random_number_y/100.),pz*(random_number_z/100.));
     particle2->SetP(px - particle1->px, py-particle1->py, pz-particle1->pz);
     
     //provjere
     /*cout << px*(random_number_x/100.)<< endl;
     cout << px - particle1->px<<endl;
     cout << px << endl;
     cout << py << endl;
     cout << pz << endl;*/

      
    }
