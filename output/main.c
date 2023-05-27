#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int population;       
    int universities;     
    char name[50];        
    int students;         
} cityInfo;

void sortCities(cityInfo* cities, int numCities) {
    int i, j;
    for (i = 0; i < numCities - 1; i++) {
        for (j = 0; j < numCities - i - 1; j++) {
            if ((double)cities[j].students / cities[j].population < (double)cities[j + 1].students / cities[j + 1].population) {
                cityInfo temp = cities[j];
                cities[j] = cities[j + 1];
                cities[j + 1] = temp;
            }
        }
    }
}

int readDataFromFile(const char* filename, cityInfo** cities, int* numCities) {
    FILE* inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        printf("Помилка відкриття файлу %s\n", filename);
        return 0;
    }

    fscanf(inputFile, "%d", numCities);   
    *cities = (cityInfo*)malloc(*numCities * sizeof(cityInfo));  
    if (*cities == NULL) {
        printf("Помилка виділення пам'яті\n");
        fclose(inputFile);
        return 1;
    }

    for (int i = 0; i < *numCities; i++) {
        fscanf(inputFile, "%s %d %d %d", (*cities)[i].name, &(*cities)[i].population, &(*cities)[i].universities, &(*cities)[i].students);
    }

    fclose(inputFile);
    return 0;
}

int main() {
    int numCities;
    cityInfo* cities;

    if (readDataFromFile("input.txt", &cities, &numCities) == 1) {
        return 1;
    }

    sortCities(cities, numCities);  

    printf("Список міст (відсортовано за відношенням кількості студентів до населення):\n");
    for (int i = 0; i < numCities; i++) {
        printf("Місто: %s, Відношення студентів/населення: %.2f\n",
               cities[i].name,
               (double)cities[i].students / cities[i].population);
    }

    free(cities);   

    return 0;
}
