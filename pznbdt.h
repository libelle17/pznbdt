#define DPROG "pznbdt"
// fuer verschiedene Sprachen //α
enum T_      
{
	T_virtVorgbAllg,
	T_pvirtVorgbSpeziell,
	T_virtMusterVorgb,
	T_pvirtvorrueckfragen,
	T_virtrueckfragen,
	T_virtpruefweiteres,
	T_virtmacherkl_Tx_lgn,
	T_Fehler_beim_Pruefen_von,
	T_st_k,
	T_stop_l,
	T_DPROG_anhalten,
	T_anhalten,
	T_Cron_Aufruf_von,
	T_gestoppt,
	T_n_k,
	T_dszahl_l,
	T_del_k,
	T_del_l,
	T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt,
	T_bdt_Tabellen_vorher_loeschen,
	T_Datenbank_nicht_initialisierbar_breche_ab,
	T_Fuege_ein, //ω
	T_pruefbdtdat,
	T_pruefbdtnachw,
	T_pruefbdtpdf,
	T_lese,
	T_eindeutige_Identifikation,
	T_Bezug_auf_bdtdat,
	T_Bezug_auf_bdtpdf,
	T_Patienten_ID,
	T_CreationDate_eMP,
	T_Medikament,
	T_MedAnf,
	T_Wirkstoff,
	T_PZN,
	T_Znr,
	T_medz,
	T_pznz,
  T_Pfad_ohne_Dateinamen,
	T_Dateiname,
	T_geaendert,
	T_verarbeitet,
	T_Datei_samt_Pfad,
	T_bdtdat,
	T_bdtnachw,
	T_bdtpdf,
	T_bdtvz_k,
	T_bdtvz_l,
	T_Verzeichnis_der_BDT_Dateien,
	T_Fehler_beim_Oeffnen_der_Datenbank,
	T_dbn_k,
	T_dbn_l,
	T_nd_k,
	T_nd_l,
	T_Name_der_Datenbank,
	T_parse_nur_Datei,
	T_MAX //α
}; // enum T_ //ω
//α
class hhcl:public dhcl
{
	private: 
		uchar anhl=0;    // <DPROG> anhalten
		string dszahl="30"; // Datensatzzahl fuer Tabellenausgaben
		int mitloe{0}; // Tabellen vorher loeschen
		const string nurdatei; // nur diese Datei einlesen
		string tbdtnachw="bdtnachw";
		string tbdtdat="bdtdat";
		string tbdtpdf="bdtpdf";
		string bdtvz="/DATA/eigene Dateien/TMExport";   // Verzeichnis der Labordateien
		string dbname="quelle"; // Name der Datenbank
		//ω
	protected: //α
		string p1;
		int p2;
		string p3;
		uchar oblista=0;
		long listz=30; //ω
	public: //α //ω
	private: //α //ω
		void virttesterg(); //α
		void virtlieskonfein();
		void virtautokonfschreib();
		void anhalten(); //ω
		void prueftbl();
		void pruefbdtdat(DB *My, const size_t aktc, const int obverb, const int oblog, const uchar direkt=0);
		void pruefbdtnachw(DB *My, const size_t aktc, const int obverb, const int oblog, const uchar direkt=0);
		void pruefbdtpdf(DB *My, const size_t aktc, const int obverb, const int oblog, const uchar direkt=0);
	protected: //α
		// void virtlgnzuw(); // wird aufgerufen in: virtrueckfragen, parsecl, lieskonfein, hcl::hcl nach holsystemsprache
		void virtVorgbAllg();
		void pvirtVorgbSpeziell()
#ifdef VOMHAUPTCODE
			__attribute__((weak)) // implementationsspezifische Vorgaben, Modul vgb.cpp)
#endif
			;
		void virtinitopt(); // (programm-)spezifische Optionen
		void pvirtmacherkl();
		void virtMusterVorgb();
		void pvirtvorzaehler();
		void virtzeigversion(const string& ltiffv=nix);
		void pvirtvorrueckfragen();
		void pvirtnachrueckfragen();
		void virtpruefweiteres();
		void virtzeigueberschrift();
		void pvirtfuehraus();
		void virtschlussanzeige();
		void zeigdienste(); //ω
	public: //α
		void lese();
		hhcl(const int argc, const char *const *const argv);
		~hhcl();
		friend class fsfcl;
}; // class hhcl //ω
