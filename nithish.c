#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Material {
    char name[50];
    float quantity;
    float cost_per_unit;
};

struct Batch {
    int batch_id;
    float eggshell_used;
    float starch_used;
    float glycerol_used;
    float vinegar_used;
    float total_cost;
};

struct Material materials[MAX];
struct Batch batches[MAX];

int material_count = 0;
int batch_count = 0;

int findMaterial(char name[]) {
    for(int i = 0; i < material_count; i++) {
        if(strcmp(materials[i].name, name) == 0)
            return i;
    }
    return -1;
}

void addMaterial() {
    if(material_count >= MAX) {
        printf("Material storage full!\n");
        return;
    }

    printf("\nEnter Material Name: ");
    scanf("%49s", materials[material_count].name);

    printf("Enter Quantity: ");
    scanf("%f", &materials[material_count].quantity);

    printf("Enter Cost per Unit: ");
    scanf("%f", &materials[material_count].cost_per_unit);

    material_count++;
    printf("Material added successfully!\n");
}

void viewMaterials() {
    if(material_count == 0) {
        printf("\nNo materials available!\n");
        return;
    }

    printf("\n---- Raw Material Inventory ----\n");
    for(int i = 0; i < material_count; i++) {
        printf("%d. %s | Quantity: %.2f | Cost/Unit: %.2f\n",
               i+1,
               materials[i].name,
               materials[i].quantity,
               materials[i].cost_per_unit);
    }
}

float calculateCost(float qty, float cost_per_unit) {
    return qty * cost_per_unit;
}

void createBatch() {
    if(material_count == 0) {
        printf("No materials available! Add materials first.\n");
        return;
    }

    if(batch_count >= MAX) {
        printf("Batch storage full!\n");
        return;
    }

    struct Batch b;
    b.batch_id = batch_count + 1;

    printf("\nEnter Eggshell Powder Used: ");
    scanf("%f", &b.eggshell_used);

    printf("Enter Starch Used: ");
    scanf("%f", &b.starch_used);

    printf("Enter Glycerol Used: ");
    scanf("%f", &b.glycerol_used);

    printf("Enter Vinegar Used: ");
    scanf("%f", &b.vinegar_used);

    float total = 0;

    int e = findMaterial("eggshell");
    int s = findMaterial("starch");
    int g = findMaterial("glycerol");
    int v = findMaterial("vinegar");

    if(e == -1 || s == -1 || g == -1 || v == -1) {
        printf("Required materials not found! Please add eggshell, starch, glycerol, vinegar.\n");
        return;
    }

    if(materials[e].quantity < b.eggshell_used ||
       materials[s].quantity < b.starch_used ||
       materials[g].quantity < b.glycerol_used ||
       materials[v].quantity < b.vinegar_used) {
        printf("Insufficient material quantity!\n");
        return;
    }

    total += calculateCost(b.eggshell_used, materials[e].cost_per_unit);
    total += calculateCost(b.starch_used, materials[s].cost_per_unit);
    total += calculateCost(b.glycerol_used, materials[g].cost_per_unit);
    total += calculateCost(b.vinegar_used, materials[v].cost_per_unit);

    materials[e].quantity -= b.eggshell_used;
    materials[s].quantity -= b.starch_used;
    materials[g].quantity -= b.glycerol_used;
    materials[v].quantity -= b.vinegar_used;

    b.total_cost = total;
    batches[batch_count] = b;
    batch_count++;

    printf("Batch created successfully! Total Cost: %.2f\n", b.total_cost);
}

void viewBatches() {
    if(batch_count == 0) {
        printf("\nNo batches created yet!\n");
        return;
    }

    printf("\n---- Production Batches ----\n");
    for(int i = 0; i < batch_count; i++) {
        printf("Batch ID: %d | Eggshell: %.2f | Starch: %.2f | Glycerol: %.2f | Vinegar: %.2f | Cost: %.2f\n",
               batches[i].batch_id,
               batches[i].eggshell_used,
               batches[i].starch_used,
               batches[i].glycerol_used,
               batches[i].vinegar_used,
               batches[i].total_cost);
    }
}

int main() {
    int choice;

    while(1) {
        printf("\n===== Eggshell Bioplastic Production Management System =====\n");
        printf("1. Add Raw Material\n");
        printf("2. View Raw Materials\n");
        printf("3. Create Production Batch\n");
        printf("4. View Production Batches\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addMaterial(); break;
            case 2: viewMaterials(); break;
            case 3: createBatch(); break;
            case 4: viewBatches(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
