
#include <LibRobus.h>

const int DiametreRouePouce = 3;
const double DiametreRoueMM = 76.2;
double circonferanceRoueMM = PI * DiametreRoueMM;

const int NbPulseParTour = 3200;
double DistanceMMParPulse = circonferanceRoueMM/ NbPulseParTour;

float rayonRobusMM = 56;
int angleRef = 15;

const float VitesseArret = 0;

const float vitesseAvancerDroit = 1;
const float vitesseAvancerGauche = 1;

const float vitesseRotionDroit  =   1;
const float vitessRotationGauche =  1;

const float offSetDroit = 0;
const float offSetGauche = 0;

void executeAller();
void executeEtape(int scalaireAngle, double distancemm);
void executeRotation(int scalaireAngle);
void executeDeplacement(double distanceMM);
void Bouger(int NbPulsGauche ,float vitesseGauche,int Nbpulsedroit ,float vitesseDroit);
bool EstDeplacementComplete(int NbPulsGauche, int Nbpulsedroit);
int determinerNbPulseDeplacement(double distanceMM);
void resetEncoder(bool Gauche, bool Droit);


const int NbEtape = 3; // modifier en fontion du parcour-----------------------------

 int scalaireAngleEtape [NbEtape] = {0,0,0}; // modifier selon le parcour  angle relatif
double distancMMEtape [NbEtape] = {0,0,0}; // same

void setup() {
  
  void BoardInit();
}

void loop() {

   executeAller();
   //éxécutéRetour();
}



   void executeAller()
   {
    for(int i =0 ; i < NbEtape ; ++i)
   {
    executeEtape(scalaireAngleEtape[i], distancMMEtape[i]);
     }
  }


void executeEtape(int scalaireAngle, double distancemm)
{
 executeRotation(scalaireAngle);
 executeDeplacement(distancemm);
}

void executeRotation(int scalaireAngle) // rotion par rapport à sa position relative angle négatif(Gauche) angle positif(droit)
{
  if(scalaireAngle== !0)
  {
    
  
 float distanceMM = 2*PI*rayonRobusMM*((scalaireAngle * angleRef) / 360);
 int NbPulse = determinerNbPulseDeplacement(distanceMM);

 int multipleVitesseGauche = 1;
 int multipleVitesseDroit = 1;

 // si angle positif v gauche +
 // si angle négatif v gauche -
  if( scalaireAngle > 0 )
  {
    multipleVitesseGauche = 1;
    multipleVitesseDroit = -1;

  }
  else
  {
    multipleVitesseGauche = -1;
    multipleVitesseDroit = 1;
  }
  Bouger(NbPulse, vitessRotationGauche * multipleVitesseGauche, NbPulse, vitesseAvancerDroit * multipleVitesseDroit);
  }
}

void executeDeplacement(double distanceMM) // avancer en ligne droite distance en millimètre
{
  if(distanceMM != 0)
  {
  int NbPulse = determinerNbPulseDeplacement(distanceMM);
  // ajuster l'offset si nécéssaire
  Bouger(NbPulse, vitesseAvancerGauche, NbPulse, vitesseAvancerDroit);
  }
}




void Bouger(int NbPulsGauche ,float vitesseGauche,int Nbpulsedroit ,float vitesseDroit)
{
 resetEncoder(true, true);
  MOTOR_SetSpeed(0, vitesseGauche);
  MOTOR_SetSpeed(1, vitesseDroit);
   while (EstDeplacementComplete(NbPulsGauche, Nbpulsedroit)  )
   {
    // moteur gauche
    // moteur droit 
    // on roule temps que on est pas à destination
  
   }
  MOTOR_SetSpeed(0, VitesseArret);
  MOTOR_SetSpeed(1, VitesseArret);

}

bool EstDeplacementComplete(int NbPulsGauche, int Nbpulsedroit)
{
  return (NbPulsGauche > ENCODER_Read(1) ) && (Nbpulsedroit > ENCODER_Read(0)); // peut être plus présise
}
   



int determinerNbPulseDeplacement(double distanceMM) 
{
return distanceMM / DistanceMMParPulse;
}

void resetEncoder(bool Gauche, bool Droit)
{
 if(Gauche)
 ENCODER_Reset(0);
 if(Droit)
 ENCODER_Reset(1);
}

