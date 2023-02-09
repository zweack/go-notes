#include <windows.h>
#include <winhttp.h>
#include <string>

int main() {
    HINTERNET hSession = WinHttpOpen(L"Example",
                                      WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                      WINHTTP_NO_PROXY_NAME,
                                      WINHTTP_NO_PROXY_BYPASS, 0);
    HINTERNET hConnect = WinHttpConnect(hSession, L"www.example.com",
                                        INTERNET_DEFAULT_HTTP_PORT, 0);
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/path",
                                            NULL, WINHTTP_NO_REFERER,
                                            WINHTTP_DEFAULT_ACCEPT_TYPES,
                                            0);
    std::wstring headers = L"Content-Type: application/x-www-form-urlencoded\r\n";
    headers += L"Content-Length: 11\r\n";
    BOOL bResults = WinHttpSendRequest(hRequest, headers.c_str(), headers.length(),
                                       L"key=value", 11, 11, 0);
    if (!bResults) {
        // handle error
    }
    bResults = WinHttpReceiveResponse(hRequest, NULL);
    if (!bResults) {
        // handle error
    }
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
    return 0;
}
