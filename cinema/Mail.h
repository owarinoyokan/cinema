#ifndef MAIL_H
#define MAIL_H

#define _CRT_SECURE_NO_WARNINGS     // Игнорирование ошибки
#include <curl/curl.h>  // Для отправки на почту
#include <iostream>
#include <string>

using namespace std;

void SendingToMail() {
    CURL* curl;
    CURLcode res;

    string email;
    wcout << L"Введите адресс элктронной почты: ";
    getline(cin,email);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, L"smtp://smtp.gmail.com:587");
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_USERNAME, L"kino4pmi@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, L"pbej czfb qbks bjfn");
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, L"<kino4pmi@gmail.com>");

        struct curl_slist* recipients = nullptr;
        recipients = curl_slist_append(recipients, "<kirill2759418@gmail.com>");
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        FILE* file = fopen("check.txt", "rb");
        if (!file) {
            wcerr << L"Ошибка открытия файла\n";
        }
        curl_easy_setopt(curl, CURLOPT_READDATA, file);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            wcerr << L"Ошибка: " << curl_easy_strerror(res) << L"\n";

        fclose(file);
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}

#endif // MAIL_H