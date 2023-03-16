/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information.
 *
 */

#ifdef UA_ARCHITECTURE_AZURERTOS

#include <open62541/types.h>

/* Global malloc singletons */
#ifdef UA_ENABLE_MALLOC_SINGLETON
UA_EXPORT UA_THREAD_LOCAL void * (*UA_mallocSingleton)(size_t size) = malloc;
UA_EXPORT UA_THREAD_LOCAL void (*UA_freeSingleton)(void *ptr) = free;
UA_EXPORT UA_THREAD_LOCAL void * (*UA_callocSingleton)(size_t nelem, size_t elsize) = calloc;
UA_EXPORT UA_THREAD_LOCAL void * (*UA_reallocSingleton)(void *ptr, size_t size) = realloc;
#endif

unsigned int UA_socket_set_blocking(UA_SOCKET sockfd){
  INT iMode = 0;
  if(nx_bsd_ioctl(sockfd, FIONBIO, &iMode) != NX_SOC_OK)
    return UA_STATUSCODE_BADINTERNALERROR;
  return UA_STATUSCODE_GOOD;
}

unsigned int UA_socket_set_nonblocking(UA_SOCKET sockfd){
  INT iMode = 1;
  if(nx_bsd_ioctl(sockfd, FIONBIO, &iMode) != NX_SOC_OK)
    return UA_STATUSCODE_BADINTERNALERROR;
  return UA_STATUSCODE_GOOD;
}

void UA_initialize_architecture_network(void){

}

void UA_deinitialize_architecture_network(void){
  
}

#define HOSTNAME "AzureRTOS"
int UA_gethostname(char *name, size_t len) {
    memcpy(name, HOSTNAME, sizeof(HOSTNAME));
    return NX_SOC_OK;
}

#endif /* UA_ARCHITECTURE_AZURERTOS */
