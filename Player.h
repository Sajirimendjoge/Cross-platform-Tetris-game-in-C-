#ifndef _PLAYER_
#define _PLAYER_

#ifdef _WIN32
	#define OS_DEP_CLEAR "cls"
#else
	#define OS_DEP_CLEAR "clear"
#endif


bool display_menu(class Player*);

class Player{
	public:
        Player();
        ~Player();
		friend bool display_menu(class Player*);
		std::string get_name();
		unsigned int get_max_score();
		void set_max_score(unsigned int);

	private:
		bool register_player();
		bool verify_player_cred();
		void get_credentials();

		std::string username;
		std::string password;
		unsigned int max_score;
};

#endif
