#include <stdio.h>

#include "hazelcast_c_client.h"

int main(void) {
    printf("main\n");

    printf("creating config\n");
    Hazelcast_ClientConfig_t *clientConfig = Hazelcast_ClientConfig_create();

    printf("adding address");
    Hazelcast_ClientConfig_add_address(clientConfig, "10.1.21.255", 5701);

    printf("connecting");
    Hazelcast_Client_t *client = Hazelcast_Client_create(clientConfig);

    Hazelcast_Client_destroy(client);

    printf("destroying config\n");
    Hazelcast_ClientConfig_destroy(clientConfig);

    return 0;
}


// int main() {
// std::cout << "############ bla\n";

//   ClientConfig clientConfig;
//   Address address( "10.1.21.255", 5701 );
//   clientConfig.addAddress( address );

//   HazelcastClient hazelcastClient( clientConfig );


// std::cout << "################  done\n";

//   IMap<int,int> myMap = hazelcastClient.getMap<int ,int>( "myIntMap" );
//   myMap.put( 1,3 );

// std::cout << "################  map end\n";

//   boost::shared_ptr<int> value = myMap.get( 1 );
//   if( value.get() != NULL ) {
//     //process the item
// std::cout << "############## getting value\n";
//   } else {
// std::cout << "############# value NOT FOUND\n";
// }

//   return 0;
// }
