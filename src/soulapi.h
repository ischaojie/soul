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

class Soul{
    public:

        PsychologyDaily GetPsychologyDaily(String token);
        Token GetToken(String email, String password);
        WordDaily GetWordDaily(String token);
};

#endif