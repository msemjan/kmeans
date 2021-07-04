#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>
#define MAX_ITER 100000

typedef std::tuple<double, double, double> point;

void print(point a)
{
  std::cout << "(" << std::get<0>(a) << ", " << std::get<1>(a) << ", " << std::get<2>(a) << ")";
}

// Generate a random 3D point
point get_random_point()
{
  return std::make_tuple(std::rand(), std::rand(), std::rand());
}

// Read data from a CSV file
std::vector<point> readcsv(std::string filename)
{
  std::vector<point> points;
  std::string line;
  std::ifstream file(filename);

  while (std::getline(file, line)) {
    std::stringstream lineStream(line);
    std::string bit;
    double x, y, z;
    std::getline(lineStream, bit, ',');
    x = std::stof(bit);
    std::getline(lineStream, bit, ',');
    y = std::stof(bit);
    std::getline(lineStream, bit, '\n');
    z = std::stof(bit);

    points.push_back(std::make_tuple(x, y, z));
  }
  return points;
}

// Function that returns Euclidian distance between two points
double distance(point a, point b)
{
  return (std::get<0>(a) - std::get<0>(b)) * (std::get<0>(a) - std::get<0>(b))
      + (std::get<1>(a) - std::get<1>(b)) * (std::get<1>(a) - std::get<1>(b))
      + (std::get<2>(a) - std::get<2>(b)) * (std::get<2>(a) - std::get<2>(b));
}

// Add two points
point add(point& a, point& b)
{
  return std::make_tuple(std::get<0>(a) + std::get<0>(b),
      std::get<1>(a) + std::get<1>(b),
      std::get<2>(a) + std::get<2>(b));
}

// Divide all components of a point by a number
point div(const point& a, double b)
{
  return std::make_tuple(std::get<0>(a) / b,
      std::get<1>(a) / b,
      std::get<2>(a) / b);
}

// K-Means algorithm classifier
class Kmeans {
  private:
  unsigned int k;
  std::vector<point> centroids;

  public:
  Kmeans(unsigned int k)
  {
    this->k = k;
    centroids.resize(k);
    for(int i = 0; i < k; i++){
      centroids[i] = std::make_tuple(0.0, 0.0, 0.0);
    }
  }

  unsigned int getK() { return this->k; }

  std::vector<point> getCentroids()
  {
    return this->centroids;
  };

  void train(std::vector<point>& datapoints)
  {
    std::cout << "Starting to train...\n";

    // Assign a random cluster to each point
    std::vector<std::tuple<point, int>> data;

    for (const auto& p : datapoints) {
      int cluster = std::rand() % k;
      data.push_back(std::make_tuple(p, cluster));
    }

    // Update clusters until there is nothing to update or max iterations
    bool test = true;
    int counter = 0;
    while (test || counter < MAX_ITER) {
      counter++;
      test = false;
      std::vector<int> num_points_per_centroid(this->k);

      // Recalculate position of each centroid
      for(int i = 0; i < k; i++){
        centroids[i] = std::make_tuple(0.0, 0.0, 0.0);
      }
      
      for (const auto& p : data) {
        int cluster = std::get<1>(p);
        point po = std::get<0>(p);
        this->centroids[cluster] = add(this->centroids[cluster], po);
        num_points_per_centroid[cluster]++;
      }

      for(int i = 0; i < k; i++){
        this->centroids[i] = div(this->centroids[i], (double) num_points_per_centroid[i]);
      }

      // Updating each point
      for (auto& p : data) {
        int cluster = std::get<1>(p);
        point po = std::get<0>(p);
        double dist_to_cluster = distance(po, this->centroids[cluster]);

        for (int i = 0; i < this->k; i++) {
          // Skip its actual cluster
          if (cluster == i)
            continue;

          // If any centroid is closer than the current one, change to it
          double new_dist = distance(po, this->centroids[i]);
          if (new_dist < dist_to_cluster) {

            std::get<1>(p) = i;
            dist_to_cluster = new_dist;
            test = true;
          }
        } // for - all clusters
      }   // for - all points
    }     // while

    // Outputing labels for training points
    std::ofstream file("training_labels.txt");
    for (auto& p : data) {
      int cluster = std::get<1>(p);
      file << cluster << "\n";
    }

    std::cout << "Finished after " << counter << " steps.\n";
  }

  std::vector<int> predict(std::vector<point>& datapoints)
  {
    std::vector<int> predictions(datapoints.size());

    for (int i = 0; i < datapoints.size(); i++) {
      predictions[i] = 0;
      double dist_to_cluster = distance(datapoints[i], this->centroids[predictions[i]]);
      for (int j = 1; j < this->k; j++) {
        double new_dist = distance(datapoints[i], this->centroids[j]);
        if (dist_to_cluster > new_dist) {
          predictions[i] = j;
          dist_to_cluster = new_dist;
        }
      }
    }
    return predictions;
  }

  void print_centroids(){
    for(auto& centroid: this->centroids){
      print(centroid);
      std::cout << ", ";
    }
    std::cout << "\n";
  }
};

int main()
{
  // Use current time as seed for random generator
  std::srand(std::time(nullptr)); 

  // int k = 2;
  // for(int i = 0; i < 32; i++){
  //   int cluster = std::rand() % k;
  //   std::cout << cluster << "\n";
  // }

  // Load data
  std::vector<point> data_train = readcsv("data_train.csv");
  std::vector<point> data_test = readcsv("data_test.csv");
  
  // Create a classifier with k=2
  Kmeans classifier(2);
  
  // Train
  classifier.train(data_train);
  
  classifier.print_centroids();
  
  // Make predictions
  auto predictions = classifier.predict(data_test);
  
  // Write predictions to a file
  std::ofstream file("predictions.txt");
  for(auto& p: predictions){
    file << p << "\n";
  }
  file.close();
    
  return 0;
}
