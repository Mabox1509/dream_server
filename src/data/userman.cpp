// [INCLUDES]
#include "../../inc/data/userman.hpp"

#include <cstring>
#include <stdexcept>
#include <unordered_map>

#include "../../inc/utils/log.hpp"

#include "../../inc/utils/process.hpp"
#include "../../inc/utils/filesys.hpp"
#include "../../inc/utils/string_utils.hpp"

//[DEFINES]
#define DATA_VERSION 1


// [NAMESPACE]
namespace Userman
{
    // =========================
    // [INTERNAL STORAGE MOCK]
    // =========================
    static std::unordered_map<std::string, std::weak_ptr<User>> users;
    static std::mutex users_mutex;

    static std::unordered_map<session_id, session_t> sessions;
    static std::mutex sessions_mutex;
    static session_id next_session_id = 1;

    
    // =========================
    // [USER IMPLEMENTATION]
    // =========================
    #pragma region 
    const void User::CheckOwnership() const
    {
        if (!m_open || m_owner != std::this_thread::get_id())
        {
            throw std::runtime_error("User object is not opened by this thread");
        }
    }

    User::User(const std::string& _user,
               const std::string& _nick,
               const std::string& _password)
        : data_version(DATA_VERSION),
          username(_user),
          nickname(_nick),
          password(_password),
          role(UserRole::COMMON),
          creation_date(std::chrono::system_clock::now())
    {
        std::memset(profile_picture, 0, sizeof(profile_picture));
    }

    User::User(const std::string& _user)
        : username(_user)
    {
        uint16_t _datver = 1;
        switch (_datver)
        {
        case 1:
            /* code */
            break;
        
        default:
            break;
        }
    }

    User::~User()
    {
        if (m_open)
        {
            throw std::runtime_error("User object destroyed while still opened"); 
        }

        //If ewverithing is ok, open the object and save
        Open();
        Save();
        Close();
    }

    void User::Open()
    {
        m_mutex.lock();
        m_owner = std::this_thread::get_id();
        m_open = true;
    }

    void User::Close()
    {
        CheckOwnership();
        m_open = false;
        m_owner = {};
        m_mutex.unlock();
    }

    void User::Save()
    {
        CheckOwnership();
        // TODO: serializar a disco / DB
    }

    const std::string& User::GetUsername() const
    {
        return username;
    }

    const std::string& User::GetNickname() const
    {
        CheckOwnership();
        return nickname;
    }

    void User::SetNickname(const std::string& _nick)
    {
        CheckOwnership();
        nickname = _nick;
    }

    bool User::CheckPassword(const std::string& _password) const
    {
        CheckOwnership();
        return password == _password;
    }

    void User::SetPassword(const std::string& _password)
    {
        CheckOwnership();
        password = _password;
    }

    UserRole User::GetRole() const
    {
        CheckOwnership();
        return role;
    }

    void User::SetRole(const UserRole _role)
    {
        CheckOwnership();
        role = _role;
    }

    const std::string User::PngProfilePicture() const
    {
        CheckOwnership();
        // Placeholder: aquí usarías tu sistema PNG
        return "profile.png";
    }

    const uint8_t* User::RawProfilePicture() const
    {
        CheckOwnership();
        return profile_picture;
    }

    void User::SetProfilePicture(const uint8_t* _data)
    {
        CheckOwnership();
        std::memcpy(profile_picture, _data, PFP_DATA);
    }

    const std::chrono::system_clock::time_point& User::GetCreationDate() const
    {
        return creation_date;
    }
    #pragma endregion




    // =========================
    // [USERMAN API]
    // =========================    
    #pragma region 
    void Initialize()
    {
        Log::Message("Initializing user manager...");

        auto _userspath = Process::GetStaticDataDirectory() + "users";
        if(!FileSys::DirectoryExists(_userspath))
        {
            Log::Message("(USERMAN) Creating users directory...");
            FileSys::CreateDirectory(_userspath);
            return;
        }

        Log::Message("(USERMAN) Loading users...");
        auto _files = FileSys::ListFiles(_userspath, false);
        for (const auto& _path : _files)
        {
            //CHECK EXTENSION
            if(!StringUtils::EndsWith(_path, ".usr"))
            {
                Log::Warning("A no user file is alocated in user folder: %s", _path.c_str());
                continue;
            }

            //GET FILENAME
            auto _parts = StringUtils::Split(_path, '/');
            std::string _fname = _parts.back();

    
            std::string _usrname = StringUtils::Replace(_fname, ".usr", "");


            //ADD A NULL USER POINTER TO THE MAP
            users[_usrname] = std::weak_ptr<User>{}; 

            Log::Message("(USERMAN) User found: %s", _usrname.c_str());
        }
    }
    
    bool CreateUser(const std::string& _user, const std::string& _nick, const std::string& _password)
    {
        //LOCK MUTEX
        std::lock_guard<std::mutex> lock(users_mutex);
    }
    bool DeleteUser(const std::string& _user)
    {
        return false;
    }

    std::shared_ptr<User> LoadUser(const std::string& _user)
    {
        return nullptr;
    }

    bool Login(const std::string& _user, const std::string& _password, session_id& _out_session)
    {
        return false;
    }
    bool Logout(const session_id)
    {
        return false;
    }

    void Tick()
    {
        // Limpieza de sesiones, timeouts, etc.
    }
    #pragma endregion
}
