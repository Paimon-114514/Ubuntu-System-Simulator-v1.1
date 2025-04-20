#include<bits/stdc++.h>
using namespace std;

// 跨平台清屏命令
string cl = "clear";
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

const string VERSION = "Ubuntu Server 22.04 LTS - Simulator";
map<string, string> password_db = {{"root", "qwq_114514"}};

void sleep_ms(int ms) {
    #ifdef _WIN32
    Sleep(ms);
    #else
    usleep(ms * 1000);
    #endif
}

void boot_animation() {
    cout << "Ubuntu DOS Version 1.0\n";
    cout << "       Ubuntu Server 模拟终端\n\n";
    cout << "正在启动";
    for(int i=0; i<10;i++) {
        cout << ".";
        cout.flush();
        sleep_ms(500);
    }
    system(cl.c_str());
}

bool login() {
    string user, password;
    int attempts = 0;
    
    while(attempts < 3) {
        cout << "\nUbuntu Server login: ";
        cin >> user;
        cout << "Password: ";
        
        // 密码输入隐藏
        #ifndef _WIN32
        termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        termios newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        #endif
        
        cin >> password;
        
        #ifndef _WIN32
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        #endif
        
        if(password_db.count(user) && password_db[user] == password) {
            cout << "\nLast login: " << __DATE__ << " " << __TIME__ << endl;
            sleep_ms(1000);
            system(cl.c_str());
            return true;
        }
        cout << "\nLogin incorrect\n";
        attempts++;
    }
    return false;
}

void show_help() {
    cout << "DOS模拟命令列表:\n";
    cout << "dir       - 显示当前目录\n";
    cout << "help      - 显示帮助\n";
    cout << "clear     - 清屏\n";
    cout << "net user  - 用户管理\n";
    cout << "ubuntu    - 显示系统信息\n";
    cout << "exit      - 退出\n";
}

void dos_prompt(const string& user) {
    string path = "C:\\Users\\" + user + ">";
    while(true) {
        cout << path;
        string cmd;
        cin >> cmd;
        
        if(cmd == "help") show_help();
        else if(cmd == "clear") system(cl.c_str());
        else if(cmd == "ubuntu") {
            cout << VERSION << endl;
            cout << "内核版本: 5.15.0-76-generic (模拟)\n";
        }
        else if(cmd == "exit") {
            cout << "正在注销...";
            sleep_ms(1000);
            break;
        }
        else {
            cout << "'" << cmd << "' 不是内部或外部命令，也不是可运行的程序\n";
        }
    }
}

int main() {
    boot_animation();
    
    if(!login()) {
        cout << "登录失败，系统将关闭\n";
        return 1;
    }
    
    dos_prompt("root");
    return 0;
}