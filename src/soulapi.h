#ifndef _SOULAPI_H
#define _SOULAPI_H


#include <Arduino.h>
#include <Vector>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <string>

using namespace std;

struct PsychologyDaily {
    String classify;
    string knowledge;
    String id;
    String created_at;
    String updated_at;
};

struct WordDaily{
    string origin;
    string pronunciation;
    string translation;
};

struct Token{
    String access_token;
    String token_type;
};

struct Lunar{
    String date;
    String ganzhi_year;
    String ganzhi_month;
    String ganzhi_day;
    String shengxiao;
};

class SoulAPI{
    private:
        String _token;
    public:
        void SetToken(String token);
        void Config(String token);
        // 获取 token 
        Token GetToken(String email, String password);
        // 获取心理学知识点
        PsychologyDaily GetPsychologyDaily();
        // 获取每日单词
        WordDaily GetWordDaily();
        // 获取农历信息
        Lunar GetLunar();
};

#endif