#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * \brief Ship data structure
 *
 * \details A ship is composed of three fields:
 *          - name: the human readable name of the ship
 *          - weight: the weight of the ship in tonnes. The weight does not need to be an integer.
 *          - cargo: an array of strings that contains human
 *                   readable names of the cargo. The number
 *                   different cargo can be assumed known in advance
 *                   (e.g. 10). The cargo names will not change during the
 *                   program execution.
 *
 * \note You can deduce the structure requirements by inpecting the main
 * function below.
 *
 */
struct Ship
{
  // declare the structure members here
  char* name;
  double weight;
  char** cargo;
};

/**
 * \brief Clears the cargo of the ship vessel by setting its cargo names
 * to NULL.
 *
 * \param vessel  The vessel of which cargo will be cleared.
 */
void clear_cargo(struct Ship *vessel)
{
  vessel->cargo = (char**)calloc(10,sizeof(char*));
  for (int i=0; i<4; i++) {
    vessel->cargo[i] = NULL;
  }
}

/**
 * \brief Adds the specified cargo to the ship vessel.
 *
 * \param vessel The ship that the cargo will be assigned
 * \param cargo The name of the cargo to be assigned
 */
void add_cargo(struct Ship *vessel, const char *cargo)
{
  for (int i=0; i<4; i++) {
    if (vessel->cargo[i] == NULL) {
      vessel->cargo[i] = (char*)malloc(strlen(cargo)+1*sizeof(char));
      strcpy(vessel->cargo[i], cargo);
      break;
    }
  }
}

int main(void)
{
    struct Ship vessel_1 = {"Tanker", 100000, {NULL}};

    clear_cargo(&vessel_1);
    add_cargo(&vessel_1, "Gasoline");
    add_cargo(&vessel_1, "Oil");
    add_cargo(&vessel_1, "Diesel");

    struct Ship vessel_2;
    vessel_2.name = "Fun boat";
    vessel_2.weight = 1.25;
    clear_cargo(&vessel_2);
    add_cargo(&vessel_2, "Food basket");
    add_cargo(&vessel_2, "Sunscreen");
    add_cargo(&vessel_2, "Very good lemonade");
    add_cargo(&vessel_2, "Frankfurters");

    struct Ship ships[2];
    ships[0] = vessel_1;
    ships[1] = vessel_2;

    for (int i = 0; i < 2; i++)
    {
        printf("Name: %s  / Weight %.2f tonnes\n", ships[i].name, ships[i].weight);
        printf("Cargo:\n");
        for (int j = 0; ships[i].cargo[j] != NULL; j++)
        {
            printf("* %s\n", ships[i].cargo[j]);
        }
        printf("----------\n");
    }

    return 0;
}
