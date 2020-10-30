#include <stdio.h>
#include <stdlib.h>

#define MAX_IP_LEN 16
#define MAX_CLASS_STR_LEN 8

#define CHAR_TO_INT(chr) (chr - 48)

#define STRLEN(string) ({ \
    int count = 0;        \
    char *tmp = string;   \
    while (*tmp != '\0')  \
    {                     \
        count++;          \
        tmp++;            \
    }                     \
    count;                \
})

#define MEMSET(array, value, length) ({ \
    int tmp = length;                   \
    while (tmp--)                       \
    {                                   \
        array[tmp] = value;             \
    }                                   \
})

#define TOINTEGER(str) ({                        \
    char *temp = str;                            \
    int len = STRLEN(temp);                      \
    int num = 0;                                 \
    while (temp && len--)                        \
        num = (num * 10) + CHAR_TO_INT(*temp++); \
    num;                                         \
})

int copyString(char *dest, char *src, int destLen)
{
    int lenSrc = STRLEN(src);
    if (lenSrc >= destLen)
    {
        printf("%s\n", "src len is more than dest len");
        return -1;
    }
    char *tmp = dest;
    while (lenSrc-- && (*dest++ = *src++))
        ;
    *dest = '\0';
    dest = tmp;
    return 0;
}

#define ClassA "Class A"
#define ClassB "Class B"
#define ClassC "Class C"
#define ClassD "Class D"
#define ClassE "Class E"

// static char **classesArr = {ClassA, ClassB, ClassC, ClassD, ClassE};

// typedef enum {
//     classA = 0,
//     classB,
//     classC,
//     classD,
//     classE
// } classes_e;

typedef struct ipaddr
{
    char _ip_addr[MAX_IP_LEN];
    char *(*getIpAddr)(struct ipaddr *this);
    void (*setIpAddr)(struct ipaddr *this, char *ip_addr);
    void (*extractFirstOctet)(struct ipaddr *this, int *firstOctet);
    void (*getClassFromOctet)(struct ipaddr *this, int *firstOctet, char *class);
} ipaddr_t;

char *_getIpAddr(ipaddr_t *this)
{
    //add checks here
    if (!(STRLEN(this->_ip_addr) > 0))
    {
        printf("ip_addr not present\n");
        return "IP N/A";
    }
    return this->_ip_addr;
}

void _setIpAddr(ipaddr_t *this, char *ip_addr)
{
    MEMSET(this->_ip_addr, '\0', MAX_IP_LEN);
    copyString(this->_ip_addr, ip_addr, MAX_IP_LEN);
}

void _extractFirstOctet(ipaddr_t *this, int *firstOctet)
{
    char *ip_addr_tmp = this->getIpAddr(this);
    char *prev = NULL, *next = NULL;
    prev = next = ip_addr_tmp;
    while (*++next != '.')
        ;
    *next = '\0';
    // printf("prev is -> %s\n", prev);
    *firstOctet = TOINTEGER(prev);
    // copyString(firstOctet, prev, 4);
}

void _getClassFromOctet(ipaddr_t *this, int *firstOctet, char *class){
    if(*firstOctet>=1 && *firstOctet<=127) copyString(class, ClassA, MAX_CLASS_STR_LEN);
    else if(*firstOctet>=128 && *firstOctet<=191) copyString(class, ClassB, MAX_CLASS_STR_LEN);
    else if(*firstOctet>=192 && *firstOctet<=223) copyString(class, ClassC, MAX_CLASS_STR_LEN);
    else if(*firstOctet>=224 && *firstOctet<=239) copyString(class, ClassD, MAX_CLASS_STR_LEN);
    else if(*firstOctet>=240 && *firstOctet<=255) copyString(class, ClassE, MAX_CLASS_STR_LEN);            
}

int main(int argc, char const *argv[])
{
    char *ip_addr_input = malloc(MAX_IP_LEN * sizeof(char));
    MEMSET(ip_addr_input, '\0', MAX_IP_LEN);
    printf("Enter IP Address :- ");
    scanf("%s", ip_addr_input);
    getchar();

    ipaddr_t *ipAddrPtr = malloc(sizeof(ipaddr_t));
    ipAddrPtr->getIpAddr = _getIpAddr;
    ipAddrPtr->setIpAddr = _setIpAddr;
    ipAddrPtr->extractFirstOctet = _extractFirstOctet;
    ipAddrPtr->getClassFromOctet = _getClassFromOctet;

    ipAddrPtr->setIpAddr(ipAddrPtr, ip_addr_input);

    int firstOctet = 0;
    ipAddrPtr->extractFirstOctet(ipAddrPtr, &firstOctet);
    printf("first octet is -> %d\n", firstOctet);

    char *class = malloc(MAX_CLASS_STR_LEN);
    MEMSET(class, '\0', MAX_CLASS_STR_LEN);
    ipAddrPtr->getClassFromOctet(ipAddrPtr, &firstOctet, class);
    printf("class is -> %s\n", class);

    free(class);
    free(ipAddrPtr);
    free(ip_addr_input);

    return 0;
}
