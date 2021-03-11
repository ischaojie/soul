#include "soulapi.h"

#include "urlencode.h"

const String SOUL_API_PSYCHOLOGY_URL =
    "http://soul.shiniao.fun/api/v1/psychologies/daily";
const String SOUL_API_WORD_URL =
    "http://soul.shiniao.fun/api/v1/words/daily";

const String SOUL_API_LOGIN_URL = "http://soul.shiniao.fun/api/v1/login";
const String SOUL_API_LUNAR_URL = "http://soul.shiniao.fun/api/v1/utils/lunar";

void SoulAPI::Config(String token) {
    SetToken(token);
}
void SoulAPI::SetToken(String token) {
    _token = token;
}

Token SoulAPI::GetToken(String email, String password) {
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient httpClient;
    Token result;
    String requestUrl = SOUL_API_LOGIN_URL;

    httpClient.begin(requestUrl);
    httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded",
                         false, true);
    int httpCode =
        httpClient.POST("username=admin@example.com&password=123456");

    if (httpCode == HTTP_CODE_OK) {
        String payload = httpClient.getString();
        Serial.println(payload);
        DynamicJsonDocument token(1024);
        deserializeJson(token, payload);
        result.access_token = token["access_token"].as<String>();
        result.token_type = token["token_type"].as<String>();
    } else {
        Serial.printf(
            "Soul api auth failed, the http status code "
            "is:%d\n",
            httpCode);
    }

    httpClient.end();
    client.stop();
    return result;
}

PsychologyDaily SoulAPI::GetPsychologyDaily() {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient httpClient;
    PsychologyDaily result;
    String requestUrl = SOUL_API_PSYCHOLOGY_URL;

    Serial.println(requestUrl);

    if (_token != "") {
        if (httpClient.begin(requestUrl)) {
            String auth = "Bearer " + _token;
            httpClient.addHeader("Authorization", auth, false, true);
            int httpCode = httpClient.GET();

            if (httpCode == HTTP_CODE_OK ||
                httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                String payload = httpClient.getString();
                Serial.println(payload);
                DynamicJsonDocument psychology(1024);
                deserializeJson(psychology, payload);

                String classify = psychology["classify"].as<String>();

                if (classify == "society") {
                    result.classify = "社会心理学";
                } else if (classify == "education") {
                    result.classify = "教育心理学";
                } else if (classify == "experiment") {
                    result.classify = "实验心理学";
                } else if (classify == "normal") {
                    result.classify = "普通心理学";
                } else {
                    result.classify = classify;
                }

                result.knowledge = psychology["knowledge"].as<string>();
                result.id = psychology["id"].as<String>();
                result.created_at = psychology["created_at"].as<String>();
                result.updated_at = psychology["updated_at"].as<String>();
            } else {
                Serial.printf(
                    "Get psychology daily failed, the http status code "
                    "is:%d\n",
                    httpCode);
            }
        } else {
            Serial.println("Get psychology daily failed");
        }
    }

    httpClient.end();
    client.stop();
    return result;
}

WordDaily SoulAPI::GetWordDaily() {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient httpClient;
    WordDaily result;
    String requestUrl = SOUL_API_WORD_URL;

    Serial.println(requestUrl);

    if (_token != "") {
        if (httpClient.begin(requestUrl)) {
            String auth = "Bearer " + _token;
            httpClient.addHeader("Authorization", auth, false, true);
            int httpCode = httpClient.GET();

            if (httpCode == HTTP_CODE_OK ||
                httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                String payload = httpClient.getString();
                Serial.println(payload);
                DynamicJsonDocument words(1024);
                deserializeJson(words, payload);
                result.origin = words["origin"].as<string>();
                result.pronunciation = words["pronunciation"].as<string>();
                result.translation = words["translation"].as<string>();
            } else {
                Serial.printf(
                    "Get word daily failed, the http status code "
                    "is:%d\n",
                    httpCode);
            }
        } else {
            Serial.println("Get word daily failed");
        }
    }

    httpClient.end();
    client.stop();
    return result;
}

Lunar SoulAPI::GetLunar() {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient httpClient;
    Lunar result;
    String requestUrl = SOUL_API_LUNAR_URL;

    Serial.println(requestUrl);

    if (_token != "") {
        if (httpClient.begin(requestUrl)) {
            String auth = "Bearer " + _token;
            httpClient.addHeader("Authorization", auth, false, true);
            int httpCode = httpClient.GET();

            if (httpCode == HTTP_CODE_OK ||
                httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                String payload = httpClient.getString();
                Serial.println(payload);
                DynamicJsonDocument lunar(1024);
                deserializeJson(lunar, payload);
                result.date = lunar["date"].as<String>();
                result.ganzhi_year = lunar["ganzhi_year"].as<String>();
                result.ganzhi_month = lunar["ganzhi_month"].as<String>();
                result.ganzhi_day = lunar["ganzhi_day"].as<String>();

            } else {
                Serial.printf(
                    "Get lunar failed, the http status code "
                    "is:%d\n",
                    httpCode);
            }
        } else {
            Serial.println("Get lunar failed");
        }
    }

    httpClient.end();
    client.stop();
    return result;
}