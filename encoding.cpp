#include <iostream>
#include <string>
#include <memory>
#include <cstdint>

#ifdef _WIN32
#include <Windows.h>

/*
    on my computer, windows cmd's default code page is 936, that means ascii,
    so when I want to print the Chinese or Japanese, I will always get mojibake.
    C++'s locale can't give me a help, so change the code page to utf8 seems a 
    good choice. this class does this thing, and it will reset the code page when
    the program exits.
*/
class WinCmdUtf8Setup{
    unsigned int codePage;
    unsigned int outputCodePage;
public:
    WinCmdUtf8Setup(){
        codePage = GetConsoleCP();
        outputCodePage = GetConsoleOutputCP();

        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    }

    ~WinCmdUtf8Setup(){
        SetConsoleCP(codePage);
        SetConsoleOutputCP(outputCodePage);
    }
};

/*
    example:

    int main(){
        WinCmdUtf8Setup setup;
        std::wstring wstr = L"这是测试用的数据, はつね みく";
        std::cout << conv_unicode_to_utf8_string(wstr) << "\n";
    }
*/
std::string conv_unicode_to_utf8_string(const std::wstring& wstr){
    std::string result;

    for (wchar_t c : wstr) {
        auto i = static_cast<uint32_t>(c);   // as you can see, the parameter could also be u32string.
        
        if (i < 0x80) {
            result += static_cast<char>(i);
        }
        else if(i < 0x800) {
            result += static_cast<char>(0xc0 | (i >> 6));
            result += static_cast<char>(0x80 | (i & 0x3f));
        }
        else if(i < 0x10000 ) {
            result += static_cast<char>(0xe0 | (i >> 12));
            result += static_cast<char>(0x80 | ((i >> 6) & 0x3f));
            result += static_cast<char>(0x80 | (i & 0x3f));
        }
        else if(i < 0x200000 ) {
            result += static_cast<char>(0xf0 | (i >> 18));
            result += static_cast<char>(0x80 | ((i >> 12) & 0x3f));
            result += static_cast<char>(0x80 | ((i >> 6) & 0x3f));
            result += static_cast<char>(0x80 | (i & 0x3f));
        }
        else {
            result += static_cast<char>(0xf8 | (i >> 24));
            result += static_cast<char>(0x80 | ((i >> 18) & 0x3f));
            result += static_cast<char>(0x80 | ((i >> 12) & 0x3f));
            result += static_cast<char>(0x80 | ((i >> 6) & 0x3f));
            result += static_cast<char>(0x80 | (i & 0x3f));
        }
    }

    return result;
}

/*
    example:

    int main(){
        std::wstring wstr = L"这是测试用的数据, はつね みく";
        std::cout << conv_unicode_to_ascii_string(wstr) << "\n";
    }
*/
std::string conv_unicode_to_ascii_string(const std::wstring& wstr){
    size_t len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    auto buf = std::make_unique<char[]>(len);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, buf.get(), len, nullptr, nullptr);

    std::string result;
    result.assign(buf.get());
    return result;
}

#endif

int main() {
    
}
