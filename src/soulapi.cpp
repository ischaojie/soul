#include "soulapi.h"
#include "urlencode.h"

const String SOUL_API_PSYCHOLOGY_URL =
    "http://soul.shiniao.fun/api/v1/psychologies/daily";
const String SOUL_API_WORD_URL =
    "http://soul.shiniao.fun/api/v1/words/daily";

const String SOUL_API_LOGIN_URL = "http://soul.shiniao.fun/api/v1/login";

Token Soul::GetToken(String email, String password) {
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

PsychologyDaily Soul::GetPsychologyDaily(String token) {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient httpClient;
    PsychologyDaily result;
    String requestUrl = SOUL_API_PSYCHOLOGY_URL;

    Serial.println(requestUrl);

    if (token != "") {
        if (httpClient.begin(requestUrl)) {
            String auth = "Bearer " + token;
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

WordDaily Soul::GetWordDaily(String token) {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient httpClient;
    WordDaily result;
    String requestUrl = SOUL_API_WORD_URL;

    Serial.println(requestUrl);

    if (token != "") {
        if (httpClient.begin(requestUrl)) {
            String auth = "Bearer " + token;
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