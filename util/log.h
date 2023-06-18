#pragma once
#include <stdio.h>

#define okay(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)
#define warn(msg, ...) printf("[*] " msg "\n", ##__VA_ARGS__)
#define err(msg, ...) printf("[-] " msg "\n", ##__VA_ARGS__)
