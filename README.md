# EncodingStuff
##### A collection about encoding converting, like unicode to utf8. I only use it to deal with mojibake on windows.
##### when I want to print Chinese on windows cmd, I got mojibake. then I learned that, windows cmd's default code page is 936, that's for ascii, so I write these things: a class to change the default code page to utf8, conv_unicode_to_utf8_string() to get a utf8 std::string, not std::u8string. then conv_unicode_to_ascii_string() to just get a std::string which could be printed with code page 936.
