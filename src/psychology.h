#ifndef _PSYCHOLOGY_H
#define _PSYCHOLOGY_H


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

struct Token{
    String access_token;
    String token_type;
};

class Psychology{
    public:

        PsychologyDaily GetPsychologyDaily();
        Token GetToken(String email, String password);
};

#endif