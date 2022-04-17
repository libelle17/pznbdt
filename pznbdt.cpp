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
	// T_del_k
	{"d","d"},
	// T_del_l
	{"delete","delete"},
	// T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt
	{"Zahl der aufzulistenden Datensaetze = <zahl> statt","No. of listed entries = <no> instead of"},
	// 	T_bdt_Tabellen_vorher_loeschen,
	{"bdt-Tabellen vorher löschen","empty bdt-tables before"},
	// T_Datenbank_nicht_initialisierbar_breche_ab
	{"Datenbank nicht initialisierbar, breche ab","database init failed, stopping"},
	// T_Fuege_ein
	{"Fuege ein: ","Inserting: "}, //ω
	// T_pruefbdtdat,
	{"pruefbdtdat()","testbdtdat()"},
	// T_pruefbdtnachw,
	{"pruefbdtnachw()","testbdtproof()"},
	// T_pruefbdtpdf,
	{"pruefbdtpdf()","testbdtpdf()"},
	// T_lese
	{"lese()","reade()"},
	// T_eindeutige_Identifikation
	{"eindeutige Identifikation","distinct identification"},
	// T_Bezug_auf_bdtdat
	{"Bezug auf bdtdat","relation to bdtdat"},
	// T_Bezug_auf_bdtpdf
	{"Bezug auf bdtpdf","relation to bdtpdf"},
	// T_Patienten_ID
	{"Patienten-ID","patient id"},
	// T_CreationDate_eMP
	{"CreationDate_eMP","CreationDate_eMP"},
	// T_Medikament
	{"Medikament","medication"},
	// T_MedAnf
	{"MedAnfang","med initial"},
	// T_Wirkstoff
	{"Wirkstoff","active substance"},
  // T_PZN
	{"PZN","PCN"},
	// T_Znr
	{"Zeile der PDF-Datei-Benennung innerhalb der BDT-Datei","line of the citation of the pdf file within then bdt file"},
	// T_medz,
	{"Zahl der Medikamente in der PDF-Datei","No. of medicaments within the pdf-file"},
	// T_pznz,
	{"Zahl der PZN in der BDT-Zeile","No. of pcn within the bdt line"},
	// T_Pfad_ohne_Dateinamen
	{"Pfad ohne Dateinamen","path without file name"},
	// T_Dateiname
	{"Dateiname","file name"},
	// T_geaendert
	{"geaendert","last modified"},
	// T_verarbeitet
	{"verarbeitet","processed"},
	// T_Datei_samt_Pfad
	{"Datei samt Pfad","file incl. path"},
	// T_bdtdat
	{"für PZN-Ermittlung verarbeitete BDT-Dateien","bdt files processed to find the pzns"},
	// T_bdtnachw
	{"Nachweis einer PZN-Zuordnung innerhalb eines Medplanes","proof of a pzn-assignment within a medication plan"},
	// T_bdtpdf
	{"PDF-Dateien, aus denen die Medikamentennamen gezogen werden","pdf-files, from whicht the names of the medications are pulled"}, 
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
	// T_nd_k
	{"nd","of"},
	// T_nd_l
	{"nurdatei","onlyfile"},
	// T_Name_der_Datenbank,
	{"Name der Datebank","name of the database"},
	// T_parse_nur_Datei
	{"parse nur Datei","parse only file"},
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
	opn<<new optcl(/*pname*/string(),/*pptr*/&nurdatei,/*art*/pstri,T_nd_k,T_nd_l,/*TxBp*/&Tx,/*Txi*/T_parse_nur_Datei,/*wi*/0,/*Txi2*/-1,/*rottxt*/string(),/*wert*/-1,/*woher*/!bdtvz.empty(),Tx[T_parse_nur_Datei]);
	opn<<new optcl(/*pptr*/&mitloe,/*art*/puchar,T_del_k,T_del_l,/*TxBp*/&Tx,/*Txi*/T_bdt_Tabellen_vorher_loeschen,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1); //α //ω
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
	if (mitloe) {
		string sql= "DROP TABLE "+tbdtnachw;
		RS loenachw(My,sql,aktc,ZDB);
		sql= "DROP TABLE "+tbdtdat;
		RS loedat(My,sql,aktc,ZDB);
		sql= "DROP TABLE "+tbdtpdf;
		RS loepdf(My,sql,aktc,ZDB);
	}
	pruefbdtdat(My, aktc, obverb, oblog, /*direkt*/0);
	pruefbdtpdf(My, aktc, obverb, oblog, /*direkt*/0);
	pruefbdtnachw(My, aktc, obverb, oblog, /*direkt*/0); // Reihenfolge wichtig wegen Fremdschlüssel
}

// wird aufgerufen in: virtpruefweiteres
void hhcl::pruefbdtdat(DB *My, const size_t aktc, const int obverb, const int oblog, const uchar direkt/*=0*/)
{
	hLog(violetts+Tx[T_pruefbdtdat]+schwarz);
	if (!direkt) {
		Feld felder[] = {
			Feld("ID","int","10","",Tx[T_eindeutige_Identifikation],1,1,1,string(),1),
			Feld("Pfad","varchar","60","",Tx[T_Pfad_ohne_Dateinamen],/*obind*/1,/*obauto*/0,/*nnull*/1,/*vdef*/string()),
			Feld("Datei","varchar","10","",Tx[T_Dateiname],/*obind*/1,/*obauto*/0,/*nnull*/1,/*vdef*/string()),
			Feld("geaendert","datetime","0","0",Tx[T_geaendert],0,0,1),
			Feld("verarbeitet","datetime","0","0",Tx[T_verarbeitet],0,0,1),
		};
		Feld ifelder0[]{Feld("Pfad"),Feld("Datei"),Feld("geaendert")}; Index i0("Pfad",ifelder0,elemzahl(ifelder0));
		Feld ifelder1[]{Feld("Datei")};    Index i1("Datei",ifelder1,elemzahl(ifelder1));
		Feld ifelder2[]{Feld("verarbeitet")};    Index i2("verarbeitet",ifelder2,elemzahl(ifelder2));
		Index indices[]{i0,i1,i2};
		// auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
		Tabelle taba(My,tbdtdat,felder,sizeof felder/sizeof* felder,indices,sizeof indices/sizeof *indices,0,0,Tx[T_bdtdat]/*//,"InnoDB","utf8","utf8_general_ci","DYNAMIC"*/);
		if (taba.prueftab(aktc,obverb)) {
			fLog(rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+tbdtdat,1,1);
			exit(11);
		}
	} // if (!direkt)
} // int pruefbdtdat(DB *My, string touta, int obverb, int oblog, uchar direkt=0)

// wird aufgerufen in: virtpruefweiteres
void hhcl::pruefbdtnachw(DB *My, const size_t aktc, const int obverb, const int oblog, const uchar direkt/*=0*/)
{
	hLog(violetts+Tx[T_pruefbdtnachw]+schwarz);
	if (!direkt) {
		Feld felder[] = {
			Feld("ID","int","10","",Tx[T_eindeutige_Identifikation],1,1,1,string(),1),
			Feld("bdid","int","10","",Tx[T_Bezug_auf_bdtdat],1,0,1,string(),/*unsig*/1),
			Feld("pdfid","int","10","",Tx[T_Bezug_auf_bdtpdf],1,0,1,string(),/*unsig*/1),
			Feld("PID","varchar","7","",Tx[T_Patienten_ID],/*obind*/1,/*obauto*/0,/*nnull*/1,/*vdef*/string()),
			Feld("MPDatum","datetime","0","0",Tx[T_CreationDate_eMP],1,0,1),
			Feld("Medikament","varchar","60","",Tx[T_Medikament],/*obind*/1,/*obauto*/0,/*nnull*/1,/*vdef*/string()),
			Feld("MedAnfang","varchar","30","",Tx[T_MedAnf],/*obind*/1,/*obauto*/0,/*nnull*/1,/*vdef*/string()),
			Feld("Wirkstoff","varchar","50","",Tx[T_Wirkstoff],/*obind*/1,/*obauto*/0,/*nnull*/1,/*vdef*/string()),
			Feld("PZN","varchar","12","",Tx[T_PZN],/*obind*/1,/*obauto*/0,/*nnull*/1,/*vdef*/string()),
			Feld("Znr","int","14","",Tx[T_Znr],/*obind*/1,/*obauto*/0,/*nnull*/1,/*vdef*/string(),/*unsig*/1),
			Feld("medz","int","14","",Tx[T_medz],/*obind*/1,/*obauto*/0,/*nnull*/1,/*vdef*/string(),/*unsig*/1),
			Feld("pznz","int","14","",Tx[T_pznz],/*obind*/1,/*obauto*/0,/*nnull*/1,/*vdef*/string(),/*unsig*/1),
			Feld("verarbeitet","datetime","0","0",Tx[T_verarbeitet],0,0,1),
		};
		Feld ifelder0[]{Feld("bdid"),Feld("PID"),Feld("PZN")}; Index i0("bdid_PID_PZN",ifelder0,elemzahl(ifelder0));
		Feld ifelder2[]{Feld("verarbeitet")};    Index i2("verarbeitet",ifelder2,elemzahl(ifelder2));
		Index indices[]{i0,i2};
		Constraint csts[]{
			Constraint(tbdtnachw+tbdtdat,new Feld{Feld("bdid")},1,tbdtdat,new Feld{Feld("ID")},1,cascade,cascade),
			Constraint(tbdtnachw+tbdtpdf,new Feld{Feld("pdfid")},1,tbdtpdf,new Feld{Feld("ID")},1,cascade,cascade),
		};
		// auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
		Tabelle taba(My,tbdtnachw,felder,sizeof felder/sizeof* felder,indices,sizeof indices/sizeof *indices,csts,sizeof csts/sizeof *csts,Tx[T_bdtnachw]/*//,"InnoDB","utf8","utf8_general_ci","DYNAMIC"*/);
		if (taba.prueftab(aktc,obverb)) {
			fLog(rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+tbdtnachw,1,1);
			exit(11);
		}
	} // if (!direkt)
} // int pruefbdtdat(DB *My, string touta, int obverb, int oblog, uchar direkt=0)

// wird aufgerufen in: virtpruefweiteres
void hhcl::pruefbdtpdf(DB *My, const size_t aktc, const int obverb, const int oblog, const uchar direkt/*=0*/)
{
	hLog(violetts+Tx[T_pruefbdtpdf]+schwarz);
	if (!direkt) {
		Feld felder[] = {
			Feld("ID","int","10","",Tx[T_eindeutige_Identifikation],1,1,1,string(),1),
			Feld("Datei","varchar","128","",Tx[T_Datei_samt_Pfad],1,0,1,string()),
		};
		Index indices[]{};
		// auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
		Tabelle taba(My,tbdtpdf,felder,sizeof felder/sizeof* felder,indices,sizeof indices/sizeof *indices,0,0,Tx[T_bdtpdf]/*//,"InnoDB","utf8","utf8_general_ci","DYNAMIC"*/);
		if (taba.prueftab(aktc,obverb)) {
			fLog(rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+tbdtpdf,1,1);
			exit(11);
		}
	} // if (!direkt)
} // int pruefbdtdat(DB *My, string touta, int obverb, int oblog, uchar direkt=0)
string GetMed(string Lang, size_t einrueck=0)
{
	string links,GMed{boost::locale::to_upper(Lang,loc)};
	if (!Lang.empty()) {
		size_t lzpos{GMed.find(" ",1+einrueck)};
		if (lzpos!=0) {
			links=GMed.substr(0,lzpos-1);
			if (links=="ACCU"||links=="ACCU-CHEK"||links=="HUMALOG"||links=="LIPROLOG"||links=="INSUMAN"
					||links=="BERLINSULIN"||links=="HUMINSULIN"||links=="INSULIN") {
				lzpos=GMed.find(" ",1+(links.length()+1>einrueck?links.length()+1:einrueck));
				if (lzpos!=string::npos) while (GMed.substr(lzpos,1)==" "&&lzpos<=GMed.length()) lzpos++;
			}
			if (links=="ACCU"||links.find("®")!=string::npos) {
				lzpos=GMed.find(" ",1+(lzpos>einrueck?lzpos:einrueck));
				if (lzpos!=string::npos) while (GMed.substr(lzpos,1)==" "&&lzpos<=GMed.length()) lzpos++;
			}
			if (lzpos!=0&&lzpos<GMed.length()) GMed.resize(lzpos);
			gtrim(&GMed);
		}
	}
 return GMed; 
} // string GetMed(string Lang, size_t einrueck=0)

void hhcl::lese()
{
	hLog(violetts+Tx[T_lese]+schwarz);
	const string datei{"*.bdt"};
	const size_t aktc{0}; 
	const uchar scharf{1};
	string creatd,creatt,pid,bdid,pdfid;
	set<size_t> patn;
	uchar obcd{0},obct{0};
	svec erg;
//	systemrueck("find \""+bdtvz+"\" -iname "+datei+" -print0 | /usr/bin/xargs -0 ls -l --time-style=full-iso | sort -k6,7|rev|cut -d/ -f1|rev",obverb,oblog,&erg);
	systemrueck("find \""+bdtvz+"\" -iname "+datei+" -printf \"%f//%TY-%Tm-%Td %TT\n\"|rev|cut -d. -f2-|rev",obverb,oblog,&erg);
	for(size_t i=0;i<erg.size();i++) {
		vector<string> tok;
		aufSplit(&tok,erg[i],"//");
		if (tok.size()!=2) continue;
//		caus<<bdtvz<<endl;
//    for(size_t j=0;j<tok.size();j++) caus<<"j: "<<j<<", tok["<<j<<"]: "<<tok[j]<<endl;
//		fLog(violetts+erg[i]+schwarz,1,1);
		if (!nurdatei.empty() && tok[0]!=nurdatei) continue;
		const string sql= "SELECT 0 FROM "+tbdtdat+" WHERE pfad=\""+bdtvz+"\" AND datei=\""+tok[0]+"\" AND geaendert=\""+tok[1]+"\"";
	  RS rtb(My,sql,aktc,ZDB);
		if (!rtb.obqueryfehler) {
			char*** cerg{0};
			int gef{0};
			while (cerg=rtb.HolZeile(),cerg?*cerg:0) {
				gef=1;
				break;
			}
			if (!gef) {
				mdatei bdt(bdtvz+"/"+tok[0],ios::in|ios::binary);
				if (bdt.is_open()) {
					caus<<"BDT ist offen: "<<blau<<bdtvz<<"/"<<tok[0]<<schwarz<<endl;
					pid.clear();
					if (scharf) {
						RS rins(My,tbdtdat); // muss fuer sammeln vor while stehen
						const auto start{std::chrono::system_clock::now()};
						const std::time_t jetzt = std::chrono::system_clock::to_time_t(start);
						vector<instyp> einf;
						einf.push_back(/*2*/instyp(My->DBS,"Pfad",bdtvz));
						einf.push_back(/*2*/instyp(My->DBS,"Datei",tok[0]));
						einf.push_back(/*2*/instyp(My->DBS,"geaendert",tok[1]));
						einf.push_back(/*2*/instyp(My->DBS,"verarbeitet",&jetzt));
						svec eindfeld; eindfeld<<"id";
						rins.tbins(&einf,aktc,/*sammeln=*/0,/*obverb=*/ZDB,/*idp=*/&bdid,/*eindeutig=*/0,eindfeld); 
						if (rins.fnr) {
							fLog(Tx[T_Fehler_af]+drots+ltoan(rins.fnr)+schwarz+Txk[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,1);
						} else {
							caus<<blau<<"in "<<tbdtdat<<" eingefuegt: "<<violett<<erg[i]<<schwarz<<endl;
						}
					} // if (0)
					string zeile, xml;
					 int obcaus{0}; // bei Untersuchung einer PZN => 0
					 const char* const suchpzn{"10042212"};
					uchar stand{0};
					size_t bznr{0};
					while (getline(bdt,zeile)) {
						bznr++;
						if (zeile.substr(3,4)=="3000") {
							pid=zeile.substr(7);
						} else if (zeile.substr(3,16)=="6298CreationDate") {
							obcd=1;
						} else if (obcd) {
							if (zeile.substr(3,4)=="6299") {
								creatd=zeile.substr(13,4)+'-'+zeile.substr(10,2)+'-'+zeile.substr(7,2);
							}
							obcd=0;
						} else if (zeile.substr(3,16)=="6298CreationTime") {
							obct=1;
						} else if (obct) {
							if (zeile.substr(3,4)=="6299") {
								creatt=zeile.substr(7);
							}
							obct=0;
						//						caus<<"Stand: "<<(int)stand<<" "<<gruen<<zeile<<schwarz<<endl;
						// es können mehrere Pläne hintereinander kommen vor der PDF-Datei
						} else if (/*stand<2 && */zeile.substr(3,4)=="6299" && zeile.find("AMTS:MP")!=string::npos) {
							stand=1;
							if(obcaus>=0){if (zeile.find(suchpzn)!=string::npos) obcaus=1; else obcaus=0;}
							if (obcaus>0) caus<<rot<<bznr<<" "<<blau<<"Stand 1, Zeile: "<<violett<<zeile<<schwarz<<endl;
							xml=zeile; 
						} else if (stand==1 && zeile.substr(3,13)=="6298IsPrinted") {
							stand=2;
							if (obcaus>0) caus<<rot<<bznr<<" "<<blau<<"Stand 2, Zeile: "<<schwarz<<zeile<<endl;
						} else if (stand==2 && zeile.substr(3,4)=="6299") {
							if (zeile.substr(7,4)=="true") {
								if(obcaus>0) {
									caus<<gruen<<"----------"<<zeile.substr(7,4)<<"--------"<<schwarz<<endl;
									caus<<rot<<bznr<<" "<<blau<<"Stand 3, Zeile: "<<schwarz<<zeile<<endl;
								}
								stand=3;
							} else {
								stand=0;
							}
						} else if (stand==3 && zeile.substr(3,18)=="6298OriginalFormat") { // ganze Zeile vergleichen schlägt fehl
							stand=4;
						} else if (stand==4) {
							stand=5; // 0126299EMP
						} else if (stand==5) {
							if (zeile.substr(3,15)=="6298PDFFilePath") stand=6; else stand=0;
						} else if (stand==6 && zeile.substr(3,4)=="6324") {
							if (obcaus>0) caus<<rot<<bznr<<" "<<blau<<"Stand 6, Zeile: "<<schwarz<<zeile<<endl;
							stand=0;
							if (zeile.find("#CGM BMP gedruckt#")!=string::npos) {
								//							 caus<<xml<<endl;
								svec bdmpzl,pzv;
								aufSplit(&bdmpzl,xml,"<AMTS:");
								for(size_t k=0;k<bdmpzl.size();k++) {
									const string li{bdmpzl[k].substr(0,2)};
									if (li=="S "||li=="M "||li=="R "||li=="X ") { // ||li=="W ")
										//									 caus<<" "<<k<<" "<<blau<<bdmpzl[k]<<schwarz<<endl;
										size_t pp{bdmpzl[k].find(" p=\"")};
										if (pp!=string::npos) {
											pp+=4;
											const size_t pe{bdmpzl[k].find("\"",pp)}; // z.B. Moxonidin 0228074 statt 228074, Doxepin 0461706 statt 461706
											string pze{bdmpzl[k].substr(pp,pe-pp)};
											//										 while (pze.length()<7) pze='0'+pze;
											pzv<<pze;
											size_t xpos{pp};
											while ((xpos=bdmpzl[k].find(" x=\"",xpos))!=string::npos) {pzv<<"";xpos++;} // Zusatzzeilen hinter dem Medikament, z.B. /DATA/turbomed/Dokumente/Sonstiges/202108/Haertl19400724-1292-908F6826-76C0-4f1f-A1C4-F3BA0A508727.pdf
										} else {
											pzv<<"";
										}
									}
								} // 							 for(size_t k=0;k<bdmpzl.size();k++) KLA
								//							 caus<<zeile<<endl;
								const ulong p1{zeile.find("$\\TurboMed")+10}, p2{zeile.find("#")-p1};
								const char ue[]{(char)129,0},oe[]{(char)148,0},Oe[]{(char)153,0},ae[]{(char)132,0};
								string bdtf{"/DATA/turbomed"+ersetze(ersetze(ersetze(ersetze(ersetze(zeile.substr(p1,p2).c_str(),"\\","/").c_str(),ue,"ü").c_str(),oe,"ö").c_str(),Oe,"Ö").c_str(),ae,"ä")};
								if (obcaus>0||obverb) caus<<rot<<"Zeile "<<bznr<<schwarz<<": "<<blau<<bdtf<<schwarz<<":"<<endl;
								pdfid={};
								string sql= "SELECT id FROM "+tbdtpdf+" WHERE datei=\""+bdtf+"\"";
								RS rpdf(My,sql,aktc,ZDB);
								if (!rpdf.obqueryfehler) {
									char*** cerg{0};
									while (cerg=rtb.HolZeile(),cerg?*cerg:0) {
										pdfid=*(*cerg+0);
										break;
									}
								}
								if (pdfid.empty()) {
									RS rins(My,tbdtpdf); // muss fuer sammeln vor while stehen
									vector<instyp> einf;
									einf.push_back(/*2*/instyp(My->DBS,"Datei",bdtf));
									svec eindfeld; eindfeld<<"id";
									rins.tbins(&einf,aktc,/*sammeln=*/0,/*obverb=*/ZDB,/*idp=*/&pdfid,/*eindeutig=*/0,eindfeld); 
								}
								svec pdfv;
								string befehl{"pdftotext -bbox \""+bdtf+"\" -"};
								if (!systemrueck(befehl,0,0,&pdfv)) {
									struct ykandcl
									{
										size_t y;
										string inh;
										ykandcl(size_t y,string inh):y(y),inh(inh){}
										bool operator< (const ykandcl & vgl) const {return(y<vgl.y);}
									} ;
									size_t seite{0};
									set<ykandcl> yve;
									for(size_t j=0;j<pdfv.size();j++) {
										if (pdfv[j].find("</page>")!=string::npos) seite++;
										size_t px{pdfv[j].find(" xMin=\"")};
										if (px!=string::npos) {
											px+=7;
											const size_t pxe{pdfv[j].find("\"",px)};
											const double x{atof(pdfv[j].substr(px,pxe-px).c_str())};
											size_t py{pdfv[j].find(" yMin=\"",pxe)};
											if (py!=string::npos) {
												py+=7;
												const size_t pye{pdfv[j].find("\"",py)};
												const double y{atof(pdfv[j].substr(py,pye-py).c_str())};
												//												if (x==27||x==47||x==140) KLA // z.B. bei Einrückung um einen Buchstaben ist es nicht mehr genau
												if (x<200) {
													const size_t pwa{pdfv[j].find(">",pye)+1}, pwe{pdfv[j].find("<",pwa)};
													const string word{!pwa||pwe==string::npos?"":pdfv[j].substr(pwa,pwe-pwa)};
													yve.insert(ykandcl(y+seite*1000,word));
												}
											}
										}
									}
									long lypos{0};
									struct mzeile {
										size_t yab;
										string wi,han; 
									};
									vector<mzeile> mve;
									for (const auto &akty: yve) {
										if (obverb) caus<<"ypos: "<<blau<<akty.y<<", ypos-lypos: "<<akty.y-lypos<<schwarz;
										if ((akty.y % 1000)>170 && (akty.y % 1000)<541 && akty.y-lypos>14) {
											if (obverb) caus<<violett<<", dazu: "<<akty.y-4<<schwarz;
											mve.push_back(mzeile{akty.y-4,string(),string()});
										} else {
											if (obverb) caus<<"            ";
										}
										if (obverb) caus<<" "<<akty.inh<<endl;
										lypos=akty.y;
									}
									seite=0;
									for(size_t j=0;j<pdfv.size();j++) {
										if (pdfv[j].find("</page>")!=string::npos) seite++;
										size_t px{pdfv[j].find(" xMin=\"")};
										if (px!=string::npos) {
											px+=7;
											const size_t pxe{pdfv[j].find("\"",px)};
											const double x{atof(pdfv[j].substr(px,pxe-px).c_str())};
											size_t py{pdfv[j].find(" yMin=\"",pxe)};
											if (py!=string::npos) {
												py+=7;
												const size_t pye{pdfv[j].find("\"",py)};
												const double y{atof(pdfv[j].substr(py,pye-py).c_str())};
												if (y>170 && y<541) {
													size_t pkz{pdfv[j].find(">",pye)};
													if (pkz!=string::npos) {
														pkz+=1;
														const size_t pka{pdfv[j].find("<",pkz)};
														const string inh{pdfv[j].substr(pkz,pka-pkz)};
														int art{0};
														if (x>=27 && x<140) art=1; else if (x>=140 && x<265) art=2;
														int znr{-1};
														for(int zl=mve.size()-1;zl>=0;zl--) {
															////		caus<<"Stelle 58, zl: "<<zl<<", mve.size(): "<<mve.size()<<", seite: "<<seite<<endl;
															if (y+1000*seite>=mve[zl].yab) {znr=zl;break;}
														}
														if (znr!=-1) {
															////		caus<<"Stelle 60, znr: "<<znr<<", art: "<<art<<endl;
															if (art==1) {
																mve[znr].wi+=x==27&&mve[znr].wi.empty()?"":" ";
																if (x!=27) mve[znr].wi+=" ";
																else if (mve[znr].wi.empty());
																else if (((inh[0]>='A'&&inh[0]<='Z')||inh[0]==*(char*)"Ä"||inh[0]==*(char*)"Ö"||inh[0]==*(char*)"Ü")&&
																		mve[znr].wi[mve[znr].wi.size()-1]!='-') mve[znr].wi+=" ";
																else if (mve[znr].wi[mve[znr].wi.size()-1]>='0' && mve[znr].wi[mve[znr].wi.size()-1]<='9') mve[znr].wi+=" ";
																mve[znr].wi+=inh;
															} else if (art==2) {
																if (x!=140) mve[znr].han+=" ";
																else if (mve[znr].han.empty());
																else if (((inh[0]>='A'&&inh[0]<='Z')||inh[0]==*(char*)"Ä"||inh[0]==*(char*)"Ö"||inh[0]==*(char*)"Ü") &&
																		mve[znr].han[mve[znr].han.size()-1]!='-') mve[znr].han+=" ";
																else if (mve[znr].han[mve[znr].han.size()-1]>='0' && mve[znr].han[mve[znr].han.size()-1]<='9') mve[znr].han+=" ";
																/* if ((((inh[0]<'a'||inh[0]>'z')&&
																	 ((int)(uchar)inh[0]!=195||
																	 ((int)(uchar)inh[1]!=164&&(int)(uchar)inh[1]!=182&&(int)(uchar)inh[1]!=188&&
																	 (int)(uchar)inh[1]!=159&&(int)(uchar)inh[1]!=169&&(int)(uchar)inh[1]!=168&&(int)(uchar)inh[1]!=160)))||
																	 x>xletzt[ypos])&&
																	 han[ypos]!="") */
																mve[znr].han+=inh;
															}
														}
													} // 											 if (pkz!=string::npos)
												} //                        if (y>170 && y<541)
											} // 										 if (py!=string::npos)
										} // 									 if (px!=string::npos)
									} // 								 for(size_t j=0;j<pdfv.size();j++)
									if (obverb)
										for(size_t znr=0;znr<mve.size()&&znr<pzv.size();znr++) {
											printf("Znr: %2lu, PZN: %9s",znr,(znr<pzv.size()?pzv[znr].c_str():""));
											printf(", y: %4lu Wi: %-52s Han: %-40s\n",mve[znr].yab,mve[znr].wi.c_str(),mve[znr].han.c_str());
										}
									//								 if (obcaus>0) caus<<"pzv.size(): "<<blau<<pzv.size()<<schwarz<<endl;
									if (pzv.size()==mve.size()) // Pat. 63056
										for (size_t znr=0;znr<pzv.size();znr++) {
											//										if (znr>=mve.size()) break;
											//									 if (pzv[m]!="")
											const string ma{GetMed(mve[znr].han)};
											if (obcaus>0) cout<<znr<<" "<<pzv[znr]<<" "<<blau<<mve[znr].wi<<schwarz<<" "<<ma<<" "<<gruen<<mve[znr].han<<schwarz<<" "<<endl;
											const my_ulonglong pzn{(my_ulonglong)atol(pzv[znr].c_str())};
											if (scharf && pzn) {
												sql="SET FOREIGN_KEY_CHECKS=0;";

												RS rins(My,tbdtnachw); // muss fuer sammeln vor while stehen
												const auto start{chrono::system_clock::now()};
												const time_t jetzt{chrono::system_clock::to_time_t(start)};
												vector<instyp> einf;
												einf.push_back(/*2*/instyp(My->DBS,"bdid",&bdid));
												einf.push_back(/*2*/instyp(My->DBS,"pdfid",&pdfid));
												einf.push_back(/*2*/instyp(My->DBS,"PID",&pid));
												const string creatdt{creatd+" "+creatt};
												einf.push_back(/*2*/instyp(My->DBS,"MPDatum",&creatdt));
												einf.push_back(/*2*/instyp(My->DBS,"Medikament",mve[znr].han));
												einf.push_back(/*2*/instyp(My->DBS,"MedAnfang",ma));
												einf.push_back(/*2*/instyp(My->DBS,"Wirkstoff",mve[znr].wi));
												einf.push_back(/*2*/instyp(My->DBS,"PZN",pzv[znr]));
												einf.push_back(/*2*/instyp(My->DBS,"Znr",bznr));
												einf.push_back(/*2*/instyp(My->DBS,"medz",mve.size()));
												einf.push_back(/*2*/instyp(My->DBS,"pznz",pzv.size()));
												einf.push_back(/*2*/instyp(My->DBS,"verarbeitet",&jetzt));
												svec eindfeld; eindfeld<<"id";
												rins.tbins(&einf,aktc,/*sammeln=*/0,/*obverb=*/ZDB,/*idp=*/0,/*eindeutig=*/0,eindfeld); 
												if (rins.fnr) {
													fLog(Tx[T_Fehler_af]+drots+ltoan(rins.fnr)+schwarz+Txk[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,1);
												} else {
													//											 if (obcaus>0) caus<<blau<<"in "<<tbdtnachw<<" eingefuegt: "<<violett<<erg[i]<<schwarz<<endl;
												}

												RS vupd(My,sql,aktc,ZDB);
												if (ma!="UNBEKANNTE") {
													patn.insert(atol(pid.c_str()));
													sql="UPDATE medplan SET Medikament=\""+mve[znr].han+"\",MedAnfang=\""+ma+"\",Wirkstoff=\""+mve[znr].wi+"\",ergaenzt=1 "
														"WHERE PZN="+pzv[znr]; // +" AND Medikament=''"; // am 23.3.22 entfernt, 
													// da PZN 17414467 falsch vergeben war für L-Thyrox Hexal 75 statt Toujeo
													RS upd(My,sql,aktc,ZDB);
												}
												sql="SET FOREIGN_KEY_CHECKS=1;";
												RS nupd(My,sql,aktc,ZDB);
											} // 									 if (scharf && pzn)
										} // 								 for (size_t m=0;m<pzv.size();m++)
								} // 							 if (!systemrueck(befehl,0,0,&pdfv))
							} // 						 if (zeile.find("#CGM BMP gedruckt#")!=string::npos)
						} // 					  else if (stand==3 && zeile.substr(3,4)=="6324")
					} // 					while (getline(bdt,zeile))
				} // 				if (bdt.is_open())
			} // 			if (!gef)
		} else {
			cout<<rot<<"rtb.obqueryfehler: "<<rtb.obqueryfehler<<schwarz<<endl;
		} // 		if (!rtb.obqueryfehler)
		if (My->fehnr) {
			fLog(rots+ltoan(My->fehnr)+schwarz+Tx[T_Fehler_beim_Oeffnen_der_Datenbank]+dbname,obverb,oblog);
		} // 	if (My->fehnr)
		//		systemrueck("cat \"/"+erg[i]+"\"",1);
	} // 	for(size_t i=0;i<erg.size();i++)
	if (obverb) { 
		caus<<"Passe Therapiearten an für Pat.: "<<blau;
		uchar beg{0};
		for(const auto &it:patn){if(beg)caus<<",";caus<<it;beg=1;}
		caus<<schwarz<<":"<<endl;
	}
	for(const auto &it:patn){
		string sql{"call fuellThaP("+ltoan(it)+")"};
		RS tha(My,sql,aktc,ZDB);
	}
	caus<<blau<<"Fertig mit lese()"<<schwarz<<endl;
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
