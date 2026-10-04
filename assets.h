#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 100

typedef struct {
    char assetID[20];
    char assetName[80];
    char assetType[40];
    double purchaseValue;
    char department[60];
    char condition[30];
} Asset;

extern Asset assets[MAX_ASSETS];
extern int assetCount;

void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAsset(void);

#endif
