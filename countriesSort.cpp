/* Section 8.2.3 Page 267 */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

struct Country
{
    string name;
    int area;
    int population;

    double calculateDensity()
    {
        return (double) population/area;
    }
};

int main()
{
    string header_string;
    int index = 0;
    Country countries[250];
   // store data in three arrays
   // array of strings to hold the country names
   string names[250];

   // array of ints, to hold the population
   int population[250];

   // array of ints, to hold the area
   int areas[250];

   // read data from the file into the arrays
   ifstream in_file;
   in_file.open("world_population.csv");

   if (in_file.is_open())
   {
      // read lines from the file
      cout << "we found the file" << endl;
      getline(in_file, header_string);
      cout << header_string << endl;

      index = 0;

      char my_char;
      string temp_name;
      while (in_file.get(my_char))
      {
        Country temp_country;

         // Afghanistan,38928346,652860
         if (my_char == ',')
         {
            // cout << "comma found!" << endl;
            cout << temp_name << endl;
            names[index] = temp_name;
            temp_country.name = temp_name;
            temp_name = "";

            // at this point we have 38928346,652860 left in the stream for the line
            int temp_pop; 
            in_file >> temp_pop;
            cout << "population " << temp_pop << endl;
            population[index] = temp_pop;
            temp_country.population = temp_pop;

            // at this point we have ,652860 left in the stream for the line
            in_file.get(my_char);

            // at this point we have 652860 left in the stream for the line
            int temp_area;
            in_file >> temp_area;
            areas[index] = temp_area;
            cout << "area " << temp_area << endl;
            temp_country.area = temp_area;

            // clears out newline character
            // on windows... there are TWO newline characters?!?!.... so replace this with a getline call.
            string garbage = "";
            getline(in_file, garbage);
            countries[index] = temp_country;
            index++;

         } else{
            // copy the character into a string
            temp_name += my_char;
         }
      }

   } else{
      cout << "Can't find the file" << endl;
   }

    ofstream out_file;
    out_file.open("pop_dense.csv");

    out_file << header_string << ", Population Density (Population/Km^2" << endl;

    for (int i = 0;i < index;i++)
    {
        out_file << countries[i].name << "," << countries[i].population << "," << countries[i].area << "," << countries[i].calculateDensity() << endl;
    }

    return 0;
}
