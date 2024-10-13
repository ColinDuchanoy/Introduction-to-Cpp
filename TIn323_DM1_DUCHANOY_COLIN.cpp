#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <unistd.h>
#include <stdlib.h> 
#include <tuple>

using std::cout; using std::cin;
using std::string;
using std::vector; using std::find;
using std::endl; using std::shuffle;



//Création des structures 
struct Carte{
	int valeur;
	string name;
	string enseignes;
};

struct Joueur{
	int score;
	string name;
};



//===========================================================================================
//Création des fonctions 


//---------------------------------------------------
//Fonction d'affichage d'une carte
void dispcarte(Carte *p){
/*
Utlisation des couleurs ANSI pour afficher les cartes avec un fond blanc et le texte de la coueleur de l'enseigne
*/
		string sequence_rouge_fblanc="\033[31m\033[47m";
		string sequence_noire_fblanc="\033[30m\033[47m";
		string sequence_reset="\033[m";
		if(p->enseignes== " ♥ "||p->enseignes==" ♦ "){
		cout <<"["<< sequence_rouge_fblanc <<p->name <<","  << p->enseignes <<sequence_reset <<"]";
		}
		else if(p->enseignes== " ♠ "||p->enseignes==" ♣ "){
		cout <<"[" << sequence_noire_fblanc<<p->name<<","<< p->enseignes <<sequence_reset <<"]";
		}
	}
//---------------------------------------------------

	
//---------------------------------------------------	
//Fonction d'affichage d'un paquet entier
void disp(vector<Carte> paquet){
/*
On récupère taille du paquet et on utilise la fonction d'affichage d'un crate sur chacun des poitneurs du paquet
*/
	int size =paquet.size();
	for(int k=0;k<size;k++){
		Carte *p=&(paquet[k]);
		cout<<'\t';
		dispcarte(p);
		cout<<endl;
	}
}
//---------------------------------------------------


//---------------------------------------------------
//Fonction de mélange du paquet entier
vector<Carte> melange(vector<Carte> paquet){

	cout<<endl<<"On mélange le paquet de 52 cartes"<<endl<<endl;
	int sizep=paquet.size();
	srand(time(NULL)); //permet de générer à chaque lancement du programme des nombres aléatoires (en se basant sur l'heure)
	int j = 0;
	const int min=0;
	
	for (int i=0;i<sizep;i++){
		int max = i;
		j = (rand() % (max + 1 - min)) + min; //Permet de générer un entier "j" alétoire compris entre "min" et "max"
		std::swap(paquet[j],paquet[i]);
	}
	return paquet;
}
//---------------------------------------------------


//---------------------------------------------------
//Fonction de distribution des 2 paquets
std::tuple<vector<Carte>,vector<Carte>> distrib(vector<Carte> paquet){
/*
Utilisation d'un tuple pour récupérer les deux paquets en sortie de fonction
*/
	cout<<"Les paquets se distribuent entre les deux joueurs"<<endl;
	vector<Carte> paquetj1;
	vector<Carte> paquetj2;
	int sizep=paquet.size();
	for (int k=0;k<sizep;k++){
		Carte *p1=&(paquet[k]);
		paquetj1.push_back(*p1);
		k++;
		paquet.pop_back();  
		Carte *p2=&(paquet[k]);
		paquetj2.push_back(*p2);
		paquet.pop_back();
	}
	return std::make_tuple(paquetj1,paquetj2);
}
//---------------------------------------------------


//---------------------------------------------------
//Fonction d'affichage des résultats de la partie
void resultat(Joueur *j1,Joueur *j2){
	string sequence_rouge="\033[31m";
	string sequence_reset="\033[m";
	cout<<"----------------------------------------------------------------------------"<<endl;
	cout<<'\t'<<'\t'<<"La partie est finie !"<<endl;
	cout<<"----------------------------------------------------------------------------"<<endl;
	cout<<endl<<'\t'<<"Scores :"<<endl;
	cout<<'\t'<<"~~~~~~~~"<<endl;
	int j1score = j1->score;
	int j2score = j2->score;
	
	cout<<'\t'<<'\t'<<"-> "<<j1->name<<" à "<<j1score<<" point(s)"<<endl;
	cout<<'\t'<<'\t'<<"-> "<<j2->name<<" à "<<j2score<<" point(s)"<<endl;
	
	if (j1score>j2score){
		string Texte =" remporte cette partie !";
		cout<<endl<<'\t'<<sequence_rouge<<j1->name<<Texte<<sequence_reset<<endl<<endl<<endl;	
	}
	else if (j1score<j2score){
		string Texte =" remporte cette partie !";
		cout<<endl<<'\t'<<sequence_rouge<<j2->name<<Texte<<sequence_reset<<endl<<endl<<endl;	
	}
	else{
		string Texte =" Match nul, personne ne remporte cette partie !";
		cout<<endl<<'\t'<<sequence_rouge<<Texte<<sequence_reset<<endl<<endl;
	}
}
//---------------------------------------------------


//===========================================================================================


int main(){	
	string p = "O" ;
	while (p== "O"||p== "Oui"||p== "oui"||p== "OUI"||p== "oui"||p== "o"){	cout<<"-------------------------------------------------------------------------------------------"<<endl;
		cout<<"		Bienvenue dans ce similateur du jeu de carte de la Bataille"<<endl;	cout<<"-------------------------------------------------------------------------------------------"<<endl;
		
		//Création des deux profils joueurs
		string nom1;
		string nom2;
		cout<<endl<<"Saisir le nom du joueur 1 : ";
		cin >>  nom1;
		Joueur *j1 = new Joueur{0,nom1};
		cout<<'\n'<<"Saisir le nom du joueur 2 : ";
		cin >>  nom2;
		Joueur *j2 = new Joueur{0,nom2};

		//Création du paquet de 52 carte
		const vector<int> valeur = {1,2,3,4,5,6,7,8,9,10,11,12,13};
		const vector<string> name = {" Deux ", " Trois ", " Quatre ", " Cinq ", " Six ", " Sept ", " Huit ", " Neuf ", " Dix ", " Valet ", " Dame ", " Roi ", " As "};
		const vector<string> enseigne = {" ♥ "," ♦ "," ♠ "," ♣ "};
		vector<Carte> paquet;
		for(int i=0;i<4;i++){
			for (int j=0;j<13;j++){
			Carte *c1 = new Carte{valeur[j],name[j],enseigne[i]};
			paquet.push_back(*c1);
			}
		}
		
		//Affichage du paquet inital
		cout<<"Voici les cartes du paquet de base : "<<'\n';
		disp(paquet);
		
		//Mélange du paquet
		vector<Carte> paquetmel = melange(paquet);
		
		//Distribution des paquets aux deux joueurs
		vector<Carte> paquetj1, paquetj2 ;
		tie(paquetj1 , paquetj2)=distrib(paquetmel);

		//Affichage du résultat de chacune des manches
		/*
		On affiche le numéro de la manche, les carte des deux joueurs,
		le résultat de la manche et l'état des points
		*/
		cout<<endl<<"Le jeu débute !"<<endl;
		int sizej1=paquetj1.size();
		for(int l=0;l<sizej1;l++){
			cout<<endl<<"==============================================="<<endl;
			cout<<"Manche "<<l<<endl;
			cout<<"~~~~~~~~~"<<endl<<endl;
			string sequence_rouge="\033[31m\033[47m";
			string sequence_reset="\033[m";
			Carte *p1=&(paquetj1[l]);
			cout<<'\t'<<"Carte de "<< j1->name<<" ";
			dispcarte(p1) ;
			cout<<endl;
			Carte *p2=&(paquetj2[l]);
			cout<<'\t'<<"Carte de "<< j2->name<<" ";
			dispcarte(p2) ;
			cout<<endl;
			int v1 = p1->valeur;
			int v2 = p2->valeur;
			if (v1>v2){
				j1->score++;
				cout<<endl<<'\t'<<j1->name<<" remporte cette manche"<<endl;
			}
			else if (v2>v1){
				j2->score++;
				cout<<endl<<'\t'<<j2->name<<" remporte cette manche"<<endl;
			}
			else{cout<<endl<<'\t'<<"Pas de point attribué"<<endl;}			
			cout<<endl<<"Points :"<<endl;
			cout<<"~~~~~~~~"<<endl;
			cout<<'\t'<<j1->name<<" à "<<j1->score<<" point(s) et "<<j2->name<<" à "<<j2->score<<" point(s)"<<endl<<endl;
			cout<<"==============================================="<<endl<<endl;
			sleep(1);
		}
		
		//Affichage du résultat du jeu
		resultat(j1,j2);
		
		//Gestion  d'une nouvelle partie ou de fin du jeu
		cout<<endl<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
		cout<<endl<<'\t'<<"Voulez vous rejouer ? (O/N): ";
		string play="";
		cin >> play;
		if (play=="N"||play=="NON"||play=="Non"||play=="non"||play=="n"){
			cout<<endl<<'\t'<<'\t'<<"Merci d'avoir joué. Au revoir !"<<endl;
			p="";
		}
		else if(play== "O"||play== "Oui"||play== "oui"||play== "OUI"||play== "o"){	
			cout<<endl<<'\t'<<'\t'<<"Une nouvelle partie va commencer dans 5 secondes!"<<endl;
			cout<<endl<<'\t'<<'\t'<<"'ctrl + C' pour annuler"<<endl;
			sleep(5);
			p=play;
		}
		else{
			cout<<'\t'<<'\t'<<"Saisie inconnue !"<<endl<<endl<<'\t'<<" Saisir 'Oui', 'OUI', 'oui', 'O', ou 'o' pour rejouer."<<endl<<'\t'<<'\t'<<"Toute autre saisie mettra fin au jeu"<<endl;
			cout<<endl<<'\t'<<"Voulez vous rejouer ? (O/N)";
			cin >> p;
			}
		cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
		}
	return 0;
}
