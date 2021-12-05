// '//α' oder '//ω' als Kommentar sind nur fuer die Verwendung dieses Programms als Programmvorlage wichtig
const double& versnr= //α
#include "versdt"
;
#include "kons.h"
#include "DB.h" 
#include <tiffio.h>
#define VOMHAUPTCODE // um Funktionsdefinition manchmal mit "__attribute__((weak)) " versehen zu können //ω
#include "pznbdt.h"
// fuer verschiedene Sprachen //α
char const *DPROG_T[T_MAX+1][SprachZahl]={
	// T_virtVorgbAllg
	{"virtVorgbAllg()","virtgeneralprefs()"},
	// T_pvirtVorgbSpeziell
	{"pvirtVorgbSpeziell()","pvirtspecialprefs()"},
	// T_virtMusterVorgb
	{"virtMusterVorgb()","virtsampleprefs"},
	// T_pvirtvorrueckfragen
	{"pvirtvorrueckfragen()","pvirtbeforecallbacks()"},
	// T_virtrueckfragen
	{"virtrueckfragen()","virtcallbacks()"},
	// T_virtpruefweiteres
	{"virtpruefweiteres()","virtcheckmore()"},
	// T_virtmacherkl_Tx_lgn
	{"pvirtmacherkl, Tx.lgn: ","pvirtmakeexpl, Tx.lgn: "},
	//	T_Fehler_beim_Pruefen_von
	{"Fehler beim Pruefen von: ","Error while examining: "},
	// T_st_k
	{"st","st"},
	// T_stop_l
	{"stop","stop"},
	// T_DPROG_anhalten
	{DPROG " anhalten","stop " DPROG},
	// T_anhalten
	{"anhalten()","stop()"},
	// T_Cron_Aufruf_von
	{"Cron-Aufruf von '","cron call of '"},
	// T_gestoppt
	{"' gestoppt.","' stopped."},
	// T_n_k
	{"n","n"},
	// T_dszahl_l
	{"dszahl","reccount"},
	// T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt
	{"Zahl der aufzulistenden Datensaetze = <zahl> statt","No. of listed entries = <no> instead of"},
	// T_Datenbank_nicht_initialisierbar_breche_ab
	{"Datenbank nicht initialisierbar, breche ab","database init failed, stopping"},
	// T_Fuege_ein
	{"Fuege ein: ","Inserting: "}, //ω
	// T_pruefdatbdt,
	{"pruefdatbdt()","testdatbdt()"},
	// T_eindeutige_Identifikation
	{"eindeutige Identifikation","distinct identification"},
	// T_Pfad_ohne_Dateinamen
	{"Pfad ohne Dateinamen","path without file name"},
	// T_Dateiname
	{"Dateiname","file name"},
	// T_verarbeitet
	{"verarbeitet","processed"},
	// T_datbdt
	{"für PZN-Ermittlung verarbeitete BDT-Dateien","bdt files processed to find the pzns"},
	// T_bdtvz_k
	{"vz","dir"},
	// T_bdtvz_l
  {"bdtvz","bdtdir"},
	// T_Verzeichnis_der_BDT_Dateien
	{"Verzeichnis der BDT-Dateien","directory of the bdt files"},
	// T_Fehler_beim_Oeffnen_der_Datenbank
	{" Fehler beim Oeffnen der Datenbank "," Error while opening database "},
	// T_dbn_k,
	{"dbn","dbn"},
	// T_dbn_l,
	{"dbname","dbname"},
	// T_Name_der_Datenbank,
	{"Name der Datebank","name of the database"},
	{"",""} //α
}; // char const *DPROG_T[T_MAX+1][SprachZahl]=

class TxB Tx((const char* const* const* const*)DPROG_T);
const char sep = 9; // geht auch: "[[:blank:]]"
const char *logdt="/var/log/" DPROG "vorgabe.log";//darauf wird in kons.h verwiesen;
pidvec pidw;
const unsigned ktage=1; // kurzes Intervall fuer Faxtabellenkorrektur, 1 Tag
const unsigned mtage=30; // mittleres Intervall fuer Faxtabellenkorrektur, 1 Monat
const unsigned ltage=73000; // langes Intervall fuer Faxtabellenkorrektur, 200 Jahre

using namespace std; //ω
hhcl::hhcl(const int argc, const char *const *const argv):dhcl(argc,argv,DPROG,/*mitcron*/1) //α
{
 // mitcron=0; //ω
} // hhcl::hhcl //α
// Hier neue Funktionen speichern: //ω
//α
// wird aufgerufen in lauf
void hhcl::virtVorgbAllg()
{
	hLog(violetts+Tx[T_virtVorgbAllg]+schwarz); //ω
	dhcl::virtVorgbAllg(); //α
} // void hhcl::virtVorgbAllg

// wird aufgerufen in lauf
void hhcl::pvirtVorgbSpeziell()
{
	hLog(violetts+Tx[T_pvirtVorgbSpeziell]+schwarz);
	virtMusterVorgb(); //ω
	dhcl::pvirtVorgbSpeziell(); //α
} // void hhcl::pvirtVorgbSpeziell

// wird aufgerufen in lauf
void hhcl::virtinitopt()
{ //ω
	opn<<new optcl(/*pptr*/&anhl,/*art*/puchar,T_st_k,T_stop_l,/*TxBp*/&Tx,/*Txi*/T_DPROG_anhalten,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1); //α //ω
	opn<<new optcl(/*pptr*/&dszahl,/*art*/pdez,T_n_k,T_dszahl_l,/*TxBp*/&Tx,/*Txi*/T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/1); //α //ω
	opn<<new optcl(/*pname*/"bdtvz",/*pptr*/&bdtvz,/*art*/pverz,T_bdtvz_k,T_bdtvz_l,/*TxBp*/&Tx,/*Txi*/T_Verzeichnis_der_BDT_Dateien,/*wi*/0,/*Txi2*/-1,/*rottxt*/string(),/*wert*/-1,/*woher*/!bdtvz.empty(),Tx[T_Verzeichnis_der_BDT_Dateien ]);
	opn<<new optcl(/*pname*/"dbname",/*pptr*/&dbname,/*art*/pstri,T_dbn_k,T_dbn_l,/*TxBp*/&Tx,/*Txi*/T_Name_der_Datenbank,/*wi*/0,/*Txi2*/-1,/*rottxt*/string(),/*wert*/-1,/*woher*/!bdtvz.empty(),Tx[T_Name_der_Datenbank]);
	dhcl::virtinitopt(); //α
} // void hhcl::virtinitopt

// wird aufgerufen in lauf
void hhcl::pvirtmacherkl()
{
	hLog(violetts+Tx[T_virtmacherkl_Tx_lgn]+schwarz+ltoan(Tx.lgn));
//	erkl<<violett<<DPROG<<blau<<Txk[T_tut_dieses_und_jenes]<<schwarz; //ω 
} // void hhcl::pvirtmacherkl //α
//ω
//α
// wird aufgerufen in lauf
void hhcl::virtMusterVorgb()
{
	hLog(violetts+Tx[T_virtMusterVorgb]+schwarz); //ω
	dhcl::virtMusterVorgb(); //α
} // void hhcl::MusterVorgb

// wird aufgerufen in lauf
void hhcl::pvirtvorzaehler()
{ //ω
} // void hhcl::virtvorzaehler() //α
//ω
// wird aufgerufen in lauf //α
void hhcl::virtzeigversion(const string& ltiffv/*=nix*/)
{
	dhcl::virtzeigversion(ltiffv);  //ω
} // void hhcl::virtzeigversion //α
//ω
//α
// wird aufgerufen in lauf
void hhcl::pvirtvorrueckfragen()
{
	hLog(violetts+Tx[T_pvirtvorrueckfragen]+schwarz); //ω
} // void hhcl::pvirtvorrueckfragen //α

//α
// wird aufgerufen in lauf
void hhcl::virtpruefweiteres()
{
	fLog(violetts+Tx[T_virtpruefweiteres]+schwarz,obverb,oblog); //ω
	// if (initDB()) exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab])); //α //ω
	hcl::virtpruefweiteres(); // z.Zt. leer //α
} // void hhcl::virtpruefweiteres

// wird aufgerufen in lauf
void hhcl::virtzeigueberschrift()
{ //ω
	// hier ggf. noch etwas an 'uebers' anhaengen //α
	hcl::virtzeigueberschrift();
} // void hhcl::virtzeigueberschrift
//ω
//α
// Parameter -st / --stop
// wird aufgerufen in: main
void hhcl::anhalten()
{
	hLog(violetts+Tx[T_anhalten]+schwarz);
	// crontab
	/*
	setztmpcron();
	for(int iru=0;iru<1;iru++) {
		const string befehl=
			"bash -c 'grep \""+saufr[iru]+"\" -q <(crontab -l)&&{ crontab -l|sed \"/"+zsaufr[iru]+"/d\">"+tmpcron+";crontab "+tmpcron+";};:'";
		systemrueck(befehl,obverb,oblog,*//*rueck=*//*0,*//*obsudc=*//*1);
	} // 	for(int iru=0;iru<2;iru++)
  */
	pruefcron("0"); // soll vor Log(Tx[T_Verwende ... stehen
	fLog(blaus+Tx[T_Cron_Aufruf_von]+schwarz+mpfad+blau+Tx[T_gestoppt]+schwarz,1,oblog); //ω
} // void hhcl::anhalten() //α
//ω
//α
void hhcl::pvirtnachrueckfragen()
{
	// if (initDB()) exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab]));  //ω
} // void hhcl::pvirtnachrueckfragen //α
//ω

void hhcl::prueftbl()
{
	const size_t aktc{0};
	if (!My) initDB();
	pruefdatbdt(My, aktc, obverb, oblog, /*direkt*/0);
}

// wird aufgerufen in: virtpruefweiteres
void hhcl::pruefdatbdt(DB *My, const size_t aktc, const int obverb, const int oblog, const uchar direkt/*=0*/)
{
	hLog(violetts+Tx[T_pruefdatbdt]+schwarz);
	if (!direkt) {
		Feld felder[] = {
			Feld("ID","int","10","",Tx[T_eindeutige_Identifikation],1,1,1,string(),1),
			Feld("Pfad","varchar","60","",Tx[T_Pfad_ohne_Dateinamen],/*obind*/1,/*obauto*/0,/*nnull*/1,/*vdef*/string()),
			Feld("Datei","varchar","10","",Tx[T_Dateiname],/*obind*/1,/*obauto*/0,/*nnull*/1,/*vdef*/string()),
			Feld("verarbeitet","datetime","0","0",Tx[T_verarbeitet],0,0,1),
		};
		Feld ifelder0[]{Feld("Pfad"),Feld("Datei")}; Index i0("Pfad",ifelder0,elemzahl(ifelder0));
		Feld ifelder1[]{Feld("Datei")};    Index i1("Datei",ifelder1,elemzahl(ifelder1));
		Feld ifelder2[]{Feld("verarbeitet")};    Index i2("verarbeitet",ifelder2,elemzahl(ifelder2));
		Index indices[]{i0,i1,i2};
		// auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
		Tabelle taba(My,tdatbdt,felder,sizeof felder/sizeof* felder,indices,sizeof indices/sizeof *indices,0,0,Tx[T_datbdt]/*//,"InnoDB","utf8","utf8_general_ci","DYNAMIC"*/);
		if (taba.prueftab(aktc,obverb)) {
			fLog(rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+tdatbdt,1,1);
			exit(11);
		}
	} // if (!direkt)
} // int pruefdatbdt(DB *My, string touta, int obverb, int oblog, uchar direkt=0)


void hhcl::lese()
{
	const string datei{"*.bdt"};
	const size_t aktc{0};
	svec erg;
	systemrueck("find \""+bdtvz+"\" -iname "+datei+" -print0 | /usr/bin/xargs -0 ls -l --time-style=full-iso | sort -k6,7|rev|cut -d/ -f1|rev",obverb,oblog,&erg);
	for(size_t i=0;i<erg.size();i++) {
//		fLog(violetts+erg[i]+schwarz,1,1);
		string sql= "SELECT 0 FROM "+tdatbdt+" WHERE pfad=\""+bdtvz+"\" AND datei=\""+erg[i]+"\"";
	  RS rtb(My,sql,aktc,ZDB);
		if (!rtb.obqueryfehler) {
			char*** cerg{0};
			uchar gef{0};
			while (cerg=rtb.HolZeile(),cerg?*cerg:0) {
				gef=1;
				break;
			}
			if (!gef) {
				mdatei bdt(bdtvz+"/"+erg[i],ios::in|ios::binary);
				if (bdt.is_open()) {
					string zeile, xml;
					uchar stand{0};
					while (getline(bdt,zeile)) {
           if (!stand && zeile.substr(3,4)=="6299" && zeile.find("AMTS:MP")!=string::npos) {
						 stand=1;
						 xml=zeile; 
					 } else if (stand==1 && zeile.substr(3,13)=="6298IsPrinted") {
						 stand=2;
					 } else if (stand==2 && zeile.substr(3,4)=="6299") {
						 if (zeile.substr(7)=="false") {
						  stand=0;
						 } else {
							 stand=3;
						 }
					 } else if (stand==3 && zeile.substr(3,4)=="6324") {
						 stand=0;
						 if (zeile.find("#CGM BMP gedruckt#")!=string::npos) {
//							 caus<<xml<<endl;
               svec mpv,mpp;
							 aufSplit(&mpv,xml,"<AMTS:");
							 for(size_t k=0;k<mpv.size();k++) {
								 const string li{mpv[k].substr(0,2)};
								 if (li=="S "||li=="M "||li=="R "||li=="X "||li=="W ") {
//									 caus<<" "<<k<<" "<<mpv[k]<<endl;
									 size_t pp{mpv[k].find(" p=\"")};
                   if (pp!=string::npos) {
										 pp+=4;
										 const size_t pe{mpv[k].find("\"",pp)};
										 mpp<<mpv[k].substr(pp,pe-pp);
									 } else {
										 mpp<<"";
									 }
								 }
							 }
							 for (size_t m=0;m<mpp.size();m++) {
								 caus<<m<<" "<<mpp[m]<<endl;
							 }
//							 caus<<zeile<<endl;
							 ulong p1{zeile.find("$\\TurboMed")+10}, p2{zeile.find("#pdf#")-p1};
							 string bdtf{"/DATA/turbomed"+ersetze(zeile.substr(p1,p2).c_str(),"\\","/")};
							 svec pdfv;
							 systemrueck("pdftotext -bbox \""+bdtf+"\" -",1,1,&pdfv);
							 for(size_t j=0;j<pdfv.size();j++) {
								 caus<<j<<" "<<pdfv[j]<<endl;
							 }
						 }
					 }
					}
				}
				if (0) {
				RS rins(My,tdatbdt); // muss fuer sammeln vor while stehen
				auto start = std::chrono::system_clock::now();
				std::time_t jetzt = std::chrono::system_clock::to_time_t(start);
				vector<instyp> einf;
				einf.push_back(/*2*/instyp(My->DBS,"Pfad",bdtvz));
				einf.push_back(/*2*/instyp(My->DBS,"Datei",erg[i]));
				einf.push_back(/*2*/instyp(My->DBS,"verarbeitet",&jetzt));
				svec eindfeld; eindfeld<<"id";
				rins.tbins(&einf,aktc,/*sammeln=*/0,/*obverb=*/ZDB,/*idp=*/0,/*eindeutig=*/0,eindfeld); 
				if (rins.fnr) {
					fLog(Tx[T_Fehler_af]+drots+ltoan(rins.fnr)+schwarz+Txk[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,1);
				} else {
					caus<<erg[i]<<" eingefuegt: "<<erg[i]<<endl;
				}
				}
			}
		}
		if (My->fehnr) {
			fLog(rots+ltoan(My->fehnr)+schwarz+Tx[T_Fehler_beim_Oeffnen_der_Datenbank]+dbname,obverb,oblog);
		} // 	if (My->fehnr)

		//		systemrueck("cat \"/"+erg[i]+"\"",1);
	} // 	for(size_t i=0;i<erg.size();i++)
} // void hhcl::lese

void hhcl::pvirtfuehraus() //α
{ //ω
	prueftbl();
	lese();
} // void hhcl::pvirtfuehraus  //α


// wird aufgerufen in lauf
void hhcl::virtschlussanzeige()
{   //ω
	dhcl::virtschlussanzeige(); //α
} // void hhcl::virtschlussanzeige
 
// wird aufgerufen in: main
void hhcl::virtautokonfschreib()
{
// const int altobverb=obverb;
// obverb=1;
	hLog(violetts+Txk[T_autokonfschreib]+schwarz+", "+Txk[T_zu_schreiben]+((rzf||hccd.obzuschreib)?Txk[T_ja]:Txk[T_nein])); //ω
	struct stat kstat{0}; //α
	if (lstat(akonfdt.c_str(),&kstat))
		hccd.obzuschreib=1;
	if (rzf||hccd.obzuschreib) {
		hLog(gruens+Txk[T_schreibe_Konfiguration]+schwarz);
		// restliche Erklaerungen festlegen
		////    agcnfA.setzbem("language",sprachstr);
		hcl::virtautokonfschreib(); //ω
	} // if (rzf||hccd.obzuschreib) //α
// obverb=altobverb;
} // void hhcl::virtautokonfschreib

hhcl::~hhcl() 
{ //ω
} // hhcl::~hhcl //α

// wird nur im Fall obhilfe==3 nicht aufgerufen
void hhcl::virtlieskonfein()
{
	const int altobverb=obverb;
	//	obverb=1;
	hLog(violetts+Txk[T_virtlieskonfein]+schwarz);
	hcl::virtlieskonfein(); //ω
	hLog(violetts+Txk[T_Ende]+Txk[T_virtlieskonfein]+schwarz); //α
	obverb=altobverb;
} // void hhcl::virtlieskonfein() //ω
int main(int argc,char** argv) //α
{
	if (argc>1) { //ω
	} //α
	hhcl hhi(argc,argv); // hiesige Hauptinstanz, mit lngzuw, setzlog und pruefplatte
	hhi.lauf(); // Einleitungsteil mit virtuellen Funktionen, 
	// mit virtVorgbAllg,pvirtVorgbSpeziell,initopt,parsecl,pvirtmacherkl,zeighilfe,virtlieskonfein,verarbeitkonf,lieszaehlerein,MusterVorgb,dovi,dovs,virtzeigversion
	// virtautokonfschreib,update,
	return hhi.retu;
} // int main 

void hhcl::virttesterg()
{
} //ω
