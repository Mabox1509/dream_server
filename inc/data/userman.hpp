#ifndef _USERMAN_HPP
#define _USERMAN_HPP
//[INCLUDES]
#include <string>
#include <chrono>
#include <mutex>
#include <thread>
#include <memory>
#include <shared_mutex>

//[NAMESPACE]
namespace Userman
{
    //DEFINES
    #define PFP_SIZE 32
    #define PFP_DATA (PFP_SIZE*PFP_SIZE) / 2

    //[TYPES]
    enum class UserRole : uint8_t
    {
        ADMIN,
        DEVELOPER,
        TESTER,
        COMMON
    };

    class User
    {
    private:
        //[VARIABLES]
        uint16_t data_version;

        std::string username;

        std::string nickname;
        std::string password;

        UserRole role;

        uint8_t profile_picture[PFP_DATA];

        std::chrono::system_clock::time_point creation_date;

        //Mutex
        std::mutex m_mutex;
        std::thread::id m_owner;
        bool m_open = false;

    public:
        //[CONSTRUCTOR]
        User(const std::string& _user, const std::string& _nick, const std::string& _password); //Create new user
        User(const std::string& _user); //Load existing user
        ~User();


        //[FUNCTIONS]
        const void CheckOwnership() const;

        void Open();  //Lock user for editing
        void Close(); //Unlock user

        void Save(); //Save user data

        const std::string& GetUsername() const;

        const std::string& GetNickname() const;
        void SetNickname(const std::string& _nick);

        bool CheckPassword(const std::string& _password) const;
        void SetPassword(const std::string& _password);

        UserRole GetRole() const;
        void SetRole(const UserRole _role);

        const std::string PngProfilePicture() const;
        const uint8_t* RawProfilePicture() const;
        void SetProfilePicture(const uint8_t* _data);

        const std::chrono::system_clock::time_point& GetCreationDate() const;
    };

    typedef struct session_t
    {
        std::shared_ptr<User> user;
        std::chrono::system_clock::time_point last_active;

        std::shared_mutex mutex;
    } session_t; 
    typedef unsigned int session_id;

    //[FUCTIONS]
    void Initialize();

    bool CreateUser(const std::string& _user, const std::string& _nick, const std::string& _password);
    bool DeleteUser(const std::string& _user);
    
    std::shared_ptr<User> LoadUser(const std::string& _user);

    bool Login(const std::string& _user, const std::string& _password, session_id& _out_session);
    bool Logout(const session_id _session);

    void Tick();
}
#endif