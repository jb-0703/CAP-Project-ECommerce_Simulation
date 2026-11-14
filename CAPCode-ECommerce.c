# include <stdio.h>
# include <stdbool.h>

typedef struct{
    const char *region;
    int local_stock;
} StoreServer;

typedef enum{
    STORE_CP,
    STORE_AP
} StoreSystemType;

typedef struct{
    StoreServer us_east;
    StoreServer us_west;
    int true_stock;
    bool is_network_partitioned;
    StoreSystemType system_type;
} StorePlatform;

bool place_order(StorePlatform *store, StoreServer *server, const char *customer){
    printf("\n>> [%s] %s attempts to place order (1 unit)...\n", server->region, customer);

    if(store->is_network_partitioned){
        if(store->system_type == STORE_CP){
            printf("\n>> ERROR-Service Unavailable: Checkout paused. Cannot verify warehouse stock.\n"
                "We apologize for the inconvenience.\n");
            return false;
    }
        else{
            if(server->local_stock > 0){
                server->local_stock--;
                store->true_stock--;
                if(store->true_stock < 0){
                    printf("\n>> SUCCESS (Oversold): Order accepted locally for %s, but warehouse stock is depleted.\n", customer);
                    printf(">> ALERT: Oversold by %d unit(s)! Triggering refund workflow...\n", -store->true_stock);
                    printf("\n-------------------------------------------------------\n");
                    printf("[REFUND INITIATED]\n");
                    printf("Affected customer : %s\n", customer);
                    printf("Server            : %s\n", server->region);
                    printf("Warehouse Deficit : %d unit(s) oversold\n", -store->true_stock);
                    printf("Action            : Refunding %d unit(s)\n", -store->true_stock);
                    printf("Status            : Order voided");
                    printf("\n-------------------------------------------------------\n");
                }
                else{
                    printf("\n>> SUCCESS: Order placed successfully for %s!\n", customer);
                }
                return true;
            }
            else{
                printf("\n>> DECLINED: 0 local stock for %s server.\n", server->region);
                return false;
            }
        }
    }
}
void simulation(const StorePlatform *store){
    printf("\n============E-Commerce Inventory Simulation============\n");
    printf("System Type: %s | Warehouse Stock: %d\n",
        store->system_type == STORE_CP ? "CP" : "AP", 
        store->true_stock);
    printf("US East Stock: %d | US West Stock: %d",
        store->us_east.local_stock,
        store->us_west.local_stock);
    printf("\n=======================================================\n");
    printf("1. Order on US-East Server as Alice\n");
    printf("2. Order on US-West Server as Bob\n");
    printf("3. Switch System Type (CP <-> AP)\n");
    printf("4. Reset Simulation\n");
    printf("0. Exit Simulation\n");
    printf("Select an option: ");

}

int main(){
    StorePlatform store = {
        {"US East", 1},
        {"US West", 1},
        1,
        true,
        STORE_CP
    };
    int choice;

    while(true){
        simulation(&store);

        if(scanf("%d", &choice) != 1){
            while(getchar() != '\n');
            continue;
        }
        if(choice == 0){
            printf("\n>> Exiting simulation...\n");
            break;
        }

        switch(choice){
            case 1:
                place_order(&store, &store.us_east, "Alice");
                break;
            case 2:
                place_order(&store, &store.us_west, "Bob");
                break;
            case 3:
                store.system_type = (store.system_type == STORE_CP) ? STORE_AP : STORE_CP;
                printf("\n>> Switched to %s system.\n",
                    store.system_type == STORE_CP ? "CP (Guarantee Consistency)" : "AP (Guarantee Availability)");
                break;
            case 4:
                store = (StorePlatform){
                    {"US East", 1},
                    {"US West", 1},
                    1,
                    true,
                    store.system_type
                };
                printf("\n>> Local and true stock reset to 1.\n");
                break;
            default:
                printf("\n>> Invalid option. Please try again.\n");
        }
    }
    
    return 0;
}