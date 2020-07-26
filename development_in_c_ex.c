#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define IP "XX.XX.XX.XX"
#define ROOT_URL "https://" IP "/DevMgmt"
#define EMAIL_URL ROOT_URL "/Email"
#define COMMON_SERVER_DYN EMAIL_URL "/CommonEmailServerDyn.xml"

typedef struct{
    char *ip;
    char *root_url;
    char *email_url;
}url_components_t;

typedef struct{
    char *url;
    url_components_t urlComps;
    void (*getUrl)();
}url_t;

void get_url(url_t *this){
    printf("url from struct is -> %s\n\n", this->url);
}

int main()
{
    url_components_t *url_info = NULL;
    url_t *ptr_url = malloc(sizeof(url_t));
    memset(ptr_url, 0, sizeof(url_t));
    
    url_info = &ptr_url->urlComps;
    
    ptr_url->url = COMMON_SERVER_DYN;
    
    ptr_url->urlComps.ip = IP;
    ptr_url->urlComps.root_url = ROOT_URL;
    ptr_url->urlComps.email_url = EMAIL_URL;
    
    ptr_url->getUrl = get_url;
    

    printf("url from url_info is -> ip : %s, root : %s, email : %s\n\n", url_info->ip, url_info->root_url, url_info->email_url);
    
    ptr_url->getUrl(ptr_url);
    
    printf("HTTPS request is %s.\n",COMMON_SERVER_DYN);

    return 0;
}
