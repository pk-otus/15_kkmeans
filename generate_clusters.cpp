#include <fstream>
#include <dlib/rand.h>

using namespace std;
using namespace dlib;

void log(ofstream& fout, double x, double y)
{
	fout << x << ';' << y << '\n';
}

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: generate_clusters <filename>";
		return 1;
	}

	double x, y;

	dlib::rand rnd;

	// we will make 50 points from each class
	const long num = 50;

	ofstream fout(argv[1]);

	// make some samples near the origin
	double radius = 0.5;
	for (long i = 0; i < num; ++i)
	{
		double sign = 1;
		if (rnd.get_random_double() < 0.5)
			sign = -1;
		x = 2 * radius*rnd.get_random_double() - radius;
		y = sign * sqrt(radius*radius - x*x);

		log(fout, x, y);
		
	}

	// make some samples in a circle around the origin but far away
	radius = 10.0;
	for (long i = 0; i < num; ++i)
	{
		double sign = 1;
		if (rnd.get_random_double() < 0.5)
			sign = -1;
		x = 2 * radius*rnd.get_random_double() - radius;
		y = sign * sqrt(radius*radius - x * x);

		log(fout, x, y);
	}

	// make some samples in a circle around the point (25,25) 
	radius = 4.0;
	for (long i = 0; i < num; ++i)
	{
		double sign = 1;
		if (rnd.get_random_double() < 0.5)
			sign = -1;
		x = 2 * radius*rnd.get_random_double() - radius;
		y = sign * sqrt(radius*radius - x * x);

		// translate this point away from the origin
		x += 25;
		y += 25;

		log(fout, x, y);
	}
	fout.close();
	return 0;
}